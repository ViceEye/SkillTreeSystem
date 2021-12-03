// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseSkillTreeNodeWidget.generated.h"

UENUM(BlueprintType)
enum ERespond
{
	PREVIOUS_NODE_NOT_ACTIVE    UMETA(DisplayName = "PreviousNodeNotActive"),
	SUCCESS_ACTIVATED			UMETA(DisplayName = "NodeSuccessActivated"),
	FAIL						UMETA(DisplayName = "Failed"),
	OKAY						UMETA(DisplayName = "Okay"),
  };

/**
 * 
 */
UCLASS()
class SKILLTREESYSTEM_API UBaseSkillTreeNodeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	UBaseSkillTreeNodeWidget* PreviousNode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	FString Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	int SkillPointNeeded;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	int LevelNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	bool IsActive;
	
	UFUNCTION(BlueprintCallable, Category = NodeFunctions)
	TEnumAsByte<ERespond> TryActive();
};
