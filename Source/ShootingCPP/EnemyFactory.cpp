// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "EnemyActor.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 적 생성 시간이 지났다면 -> 생성과 생성시간 초기화
	if (CurrentTime > DelayTime)
	{
		// 적 생성할 예정, 초기화 위해 0 저장
		CurrentTime = 0;

		// 적 생성
		AEnemyActor* Enemy = GetWorld()->SpawnActor<AEnemyActor>(EnemyClass, GetActorLocation(), GetActorRotation());

	}
	else
	{
		CurrentTime += DeltaTime;
	}

}

