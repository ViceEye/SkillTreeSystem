// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillTreeNodeData.generated.h"

/**
 * 
 */
UCLASS()
class SKILLTREESYSTEM_API USkillTreeNodeData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NodeVariables)
	FString PreviousNode;

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
};
