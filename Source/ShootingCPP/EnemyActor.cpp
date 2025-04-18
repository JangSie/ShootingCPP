// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
// 서치 안에 actor 포함되려고 PlayerPawn을 갖고 온다?

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	
	//-------------------Collision-------------------------
	// Project Settings > Engine > Collision > Preset(프리셋) 이름과 제대로 맞아야함
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));
	// 문자열로 비교하는 건 예민한 문제 -> Const로 선언하고 해두는게 안전함 
	//-----------------------------------------------------


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetupAttachment(BoxComp); // BoxComp에 자식으로 들어감

}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 뽑은 결과 = 1~100 사이 랜덤 값 저장
	int32 DrawResult = FMath::RandRange(1, 100);

	if (DrawResult <= TracePate)
	{
		// 플레이어 방향으로 바라보게 한다
		// 플레이어 초기값 변수를 GetWorld() 안에서 찾음(서칭) 
		// Actor중에 범위를 <APlayerPawn> 으로 지정해줌 => PlayerPawn이 들어올 거임
		// APlayerPawn : 타입의 엑터만 반복 대상이 된다
		// GetWorld() : 어디에서 찾을지 범위에 해당한다
		// => GetWorld() 안에 있는 AplayerPawn 타입을 순차적으로 순회한다
		for (TActorIterator<APlayerPawn> Player(GetWorld()); Player; ++Player) // Player가 존재한다 = i
		{
			// Contains tEXT()와 값 비교 
			// APlayerPawn 타입이면서 (for문에서 걸러짐)
			// 이름에 BP_PlayerPawn 이라는 문구가 포함 되어 있다면 ("포함"이기 대문에 뒤에 1,2,3 이런 거 붙어도 true)
			if (Player->GetName().Contains(TEXT("BP_PlayerPawn")))
			{
				// (상대방 좌표 - 나의 좌표).Normalize == 내가 상대방을 바라보는 방향
				// Direction = 플레이어의 좌표 - 나 자신 즉, 애너미의 좌표 
				Direction = Player->GetActorLocation() - GetActorLocation();
				Direction.Normalize();
			}
		}

	}
	else
	{
		// 정면 벡터를 변수에 저장
		Direction = GetActorForwardVector();
	}

	//---------델리게이트---------
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);

}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation() + (Direction * MoveSpeed * DeltaTime);

	SetActorLocation(NewLocation);
	// 계산된 MoveSpeed *DeltaTime 만큼 이동 
}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

	if (Player != nullptr)
	{
		Player->Destroy();
	}

	Destroy();
}

