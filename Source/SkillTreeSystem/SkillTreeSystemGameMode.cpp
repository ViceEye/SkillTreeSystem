// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkillTreeSystemGameMode.h"
#include "SkillTreeSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASkillTreeSystemGameMode::ASkillTreeSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
