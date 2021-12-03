// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameObject.generated.h"

/**
 * 
 */
UCLASS()
class SKILLTREESYSTEM_API USaveGameObject : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AvailableSkillPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentPlayerExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, float> PropertiesMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, bool> SkillTreeNodesMap;
};
