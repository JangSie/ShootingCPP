// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float DelayTime = 2.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> EnemyClass; // 오브젝트보다 클래스 개념에 가까움/ 그래서 class로 지정

private:
	// 현재시간 저장 용도
	float CurrentTime = 0;

};
