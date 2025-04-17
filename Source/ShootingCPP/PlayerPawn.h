// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

//#include "Components/BoxComponent.h"

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
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;
	
	// ------------------Inputs 연관 변수 선언------------------------
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 500.0f; // 속력 변수

	UPROPERTY(EditAnywhere)
	class UArrowComponent* FirePosition;
	// 방향이랑 위치 나타내는 컴포넌트

	// TSubClassOf <> 안에 들어간 클래스와 그 클래스의 자식까지 여기에 할당 가능
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletFactory; // 언리얼에서 드래그 앤 드롭으로 할당 가능?

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_PlayerInput;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Horizontal;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Vertical;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Fire;


private:
	float Horizontal = 0.0f; //초기화
	float Vertical = 0.0f;
	


private:
	// 입력 이벤트 발생 시 실행할 함수
	void OnInputHorizontal(const struct FInputActionValue& value); // struct형태/ FInputActionValue를 참조로 갖고옴
	// 이 함수는 언리얼에서 지정해둠, class(전방선언) 사용 불가(=형식 유지 필요) => include 필요(InputActionValue.h)
	void OnInputVertical(const struct FInputActionValue& value);

	// 총알 발사 입력 처리 함수
	void Fire();
};
