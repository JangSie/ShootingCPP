// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBa.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void AShootingGameModeBa::PrintScore()
{
	if (MainWidget != nullptr)
	{	
		// FText : String과 유사한 언리얼 문자 
		MainWidget->ScoreData->SetText(FText::AsNumber(CurrentScore));
	}
}

void AShootingGameModeBa::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetClass != nullptr)
	{
		// MainWidgetClass : BP_MainWidget_C 이 될 예정 (_C : 안에 있는 class 의미)
		MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);

		if (MainWidget != nullptr)
		{
			// 언리얼 Widget의 특징
			// AddToViewport() 해야 화면에 출력을 해준다
			MainWidget->AddToViewport();
		}
	}
}

void AShootingGameModeBa::AddScore(int32 Point)
{
	CurrentScore += Point;
	UE_LOG(LogTemp, Warning, TEXT("CurrentScore : %d"), CurrentScore);
	PrintScore();
}

void AShootingGameModeBa::ShowMenu()
{
	if (MenuWidgetClass != nullptr)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetWorld(),MenuWidgetClass);
		if (MenuWidget != nullptr)
		{
			MenuWidget->AddToViewport();

			// 게이을 일시 정지 상태로 만든다
			UGameplayStatics::SetGamePaused(GetWorld(), true); // 일시정지 : true, 실행 : flase
			// 일시 정지 상태에서 입력값을 받기는 힘들다

			// 플레어이어 컨트롤러에 마우스 커서를 화면에 보이게 한다
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}

	}
}
