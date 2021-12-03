// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SkillTreeSystemCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkillTreeSystemGameMode.generated.h"

UCLASS(minimalapi)
class ASkillTreeSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASkillTreeSystemGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	
	UPROPERTY(BlueprintReadOnly, Category = UIVariables)
	TArray<ASkillTreeSystemCharacter*> PlayerCharacters;
};



