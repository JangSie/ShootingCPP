// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	// 확률 지정 변수
	UPROPERTY(EditAnywhere)
	int32 TracePate = 50;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 800.0f;

	//---------델리게이트---------
	UFUNCTION() // 반드시 써줘야 델리게이트 사용 가능  /UPrimitiveComponent, OnComponentBeginOverlap,  맨 압줄에서 제거
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	// 방향 벡터 변수
	FVector Direction = FVector::ZeroVector; //::ZeroVector = FVector(0,0,0) = 초기화

};
