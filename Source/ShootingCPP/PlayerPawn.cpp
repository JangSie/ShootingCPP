// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

