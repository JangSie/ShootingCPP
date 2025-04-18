// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBa.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"

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
