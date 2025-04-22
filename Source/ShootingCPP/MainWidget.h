// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// meta = (BindWidget) : 특이한 속성
	// 위젯 블루프린트에서 동일한 이름을 가진 UTextBlock이 있다면 변수와 블루프린트를 자동으로 연결을 해준다
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText; // Text 블록 생성


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreData;
};
