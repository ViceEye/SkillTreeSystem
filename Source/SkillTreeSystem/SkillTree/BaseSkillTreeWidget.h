// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "BaseSkillTreeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SKILLTREESYSTEM_API UBaseSkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* Test;
	
	/*Responsible for open and close Skill Tree*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = UI)
	void OpenOrCloseST(bool open);
};
