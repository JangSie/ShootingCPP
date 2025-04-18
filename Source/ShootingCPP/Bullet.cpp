// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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

