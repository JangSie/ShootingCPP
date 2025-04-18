// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	BoxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
	
	//-------------------Collision-------------------------
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));
	//-----------------------------------------------------

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetupAttachment(BoxComp); // BoxComp에 자식으로 들어감
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	//-------------------델리게이트-------------------------
	// 함수를 변수화 시켰다고 생각할 수 있다
	// 델리게이트의 법칙 : 파라미터를 모두 맞춰줘야 이 델리게이트에 함수를 넣을 수 있다
	// OnComponentBeginOverlap 에 동적으로 함수(OnBulletOverlap) 할당 
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
	// => BoxComp 가 충돌됐을 때 한번(Begin) 실행
	//-----------------------------------------------------

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * MoveSpeed *DeltaTime);
	// GetActorLocation : 월드 기준 내 location 좌표로 가져옴
	// GetActorForwardVector : x 좌표의 방향 벡터 (= 바라보고 있는 방향) 

	SetActorLocation(NewLocation);
	// 계산된 MoveSpeed *DeltaTime 만큼 이동 
}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("총알이 적과 충돌했습니다"));
	
	// OtherActor : 충돌한 Actor값 받아옴 
	AEnemyActor* Enemy = Cast<AEnemyActor>(OtherActor);
	
	if (Enemy != nullptr)
	{
		// 충돌한 Enemy Actor 파괴
		Enemy->Destroy();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
			ExplosionFX, GetActorLocation(), GetActorRotation());
	}

	// this 생략되어 있다
	// 나 자신을 파괴한다 = 자신의 오브젝트 파괴 = 충돌 시 총알 파괴 
	Destroy();

}

