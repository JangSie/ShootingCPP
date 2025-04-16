// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "Components/BoxComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 인풋 관련 세팅 메서드


public:
	// 전방 선언
	// 이 뒤에 타입이 클래스 타입이란 걸 알려줬기 때문에
	// 컴파일러는 class라고 인지하고 통과시켜준다. (include가 주석이 되었는데도 오류 안뜸)
	// 그래서 왜 전방 선언을 하느냐, 의존성이 끊어진다
	// 의존성이 끊어진다는 건 PlayerPawn 클래스와 UBoxComponent 클래스가
	// 관계가 없어진다라고 표현할 수 있다 = 코드가 유연해진다(모듈화도 잘 됨)
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	// .h파일에선 웬만하면 전방 선언하는 편임 

	// 메시 컴포넌트 
	// 오브젝트에 그래픽 렌더링을 할 수 있게하는 기능 (표면 같은?
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

};
