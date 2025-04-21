// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼(ButtonRestart, ButtonQuit) 입력 이벤트(OnClicked)에 대응하는 함수(Restatr, Quit) 연결
	ButtonRestart->OnClicked.AddDynamic(this, &UMenuWidget::Restatr);
	ButtonQuit->OnClicked.AddDynamic(this, &UMenuWidget::Quit);
}

void UMenuWidget::Restatr()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

void UMenuWidget::Quit()
{
	UWorld* CurrentWorld = GetWorld();

	UKismetSystemLibrary::QuitGame(CurrentWorld, CurrentWorld->GetFirstPlayerController(),
		EQuitPreference::Quit, false); // false : 특정 플랫폼의 제한 무시=>종료
}
