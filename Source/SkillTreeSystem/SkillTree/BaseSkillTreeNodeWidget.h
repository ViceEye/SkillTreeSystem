// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "SkillTreeActor.h"
#include "Blueprint/UserWidget.h"
#include "BaseSkillTreeNodeWidget.generated.h"

UENUM(BlueprintType)
enum ERespond
{
	PREVIOUS_NODE_NOT_ACTIVE			UMETA(DisplayName = "PreviousNodeNotActive"),
	REQUIRE_SKILL_POINT_NOT_ENOUGH		UMETA(DisplayName = "RequireSkillPointNotEnough"),
	REQUIRE_GRADE_LEVEL_NOT_ENOUGH		UMETA(DisplayName = "RequireGradeLevelNotEnough"),
	SUCCESS_ACTIVATED					UMETA(DisplayName = "NodeSuccessActivated"),
	DEBUG_FAIL							UMETA(DisplayName = "DebugFailed"),
	DEBUG_OKAY							UMETA(DisplayName = "DebugOkay"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNodeActivationSignature, UUserWidget*, NodeWidget);

/**
 * 
 */
UCLASS()
class SKILLTREESYSTEM_API UBaseSkillTreeNodeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = UIDelegates)
	FNodeActivationSignature NodeActivation;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UIFunctions)
	void SetActive(bool Active);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	UBaseSkillTreeNodeWidget* PreviousNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	UTexture2D* Icon;
	
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
	TEnumAsByte<ERespond> TryActive(ASkillTreeActor* SkillTreeActor);
};
