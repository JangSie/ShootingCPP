// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Tick 함수를 사용할 때는 ture 사용 필요 (사용하겠다는 소리) p482


	// 오브젝트의 충돌을 담당하는 컴포넌트(기능)
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	// TEXT(컴포넌트 이름)
	SetRootComponent(BoxComp); // rootComponent 지정 
	// #include "Components/BoxComponent.h" - 써주지 않으면 찾지 못함/ 헤더는 class로 찾았지면 여긴 include 해줘야함
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	// 수기로 한 걸 스크립트에서 50, 50, 50으로 맞춰줄 수 있음(인자의 타입은 float)


	// 컴포넌트 생성하지 않으면 공간만 생성되고 컴포넌트는 생성x
	MeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("My Static Mesh"));
	MeshComp->SetupAttachment(BoxComp);
	// 컴포넌트를 계층 구조로 만들어줌
	// = 자식컴포넌트->SetupAttachment(부모될 컴포넌트);


}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Aplayer : 플레이어
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// GetWorld : 현재 켜져있는 월드 받아옴 
	// => 재생 눌렀을 때 플레이어를 받아옴
	
	// 예외처리 = 값 들어있을 때 true
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subSystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subSystem != nullptr)
		{
			// 입력 서브 시스템에 IMC파일 변수를 연결 (=플레이어와 연동)
			subSystem->AddMappingContext(IMC_PlayerInput, 0);
		}
	}
	
}

// Called every frame = 1프레임마다 호출됨(사용시 주의 필요)
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1프레임마다 플레이어가 나아갈 방향 
	// float 3개가 들어갈 수 있는 형태 = x, y, z로 xyz 컴포넌트 값을 초기화
	FVector Direction = FVector(0, Horizontal, Vertical);
	Direction.Normalize(); // Direction에 들어온 값을 정규화 하는 함수
	// 정규화 이유 : 대각선은 루트2(1.4---)의 값을 가짐 => 속도가 더 빨라지는 버그 -> 1로 정규화 필요

	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComp)
	{
		// ( 뭘 동작할지, 어떻게 동작될지, this(플레이어 pawn), 이 액션에 어떤 함수를 넣을 것인지 )
		EnhancedInputComp->BindAction(IA_Horizontal, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputHorizontal); //Triggered : 더할 때 (+)
		EnhancedInputComp->BindAction(IA_Horizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal); //Completed : 뺄 때 (-)
		EnhancedInputComp->BindAction(IA_Vertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical); //Triggered : 더할 때 (+)
		EnhancedInputComp->BindAction(IA_Vertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical); //Completed : 뺄 때 (-)
	}

}

void APlayerPawn::OnInputHorizontal(const FInputActionValue& value)
{
	Horizontal = value.Get<float>(); //<float> : float 형으로 값을 받겠다는 소리
	//UE_LOG(LogTemp, Warning, TEXT("Horizontal : %f"), Horizontal);
}

void APlayerPawn::OnInputVertical(const FInputActionValue& value)
{
	Vertical = value.Get<float>(); //<float> : float 형으로 값을 받겠다는 소리
	//UE_LOG(LogTemp, Warning, TEXT("Vertical : %f"), Vertical);
}

