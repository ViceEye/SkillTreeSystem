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

void ASkillTreeSystemGameMode::BeginPlay()
{
	Super::BeginPlay();
	ASkillTreeSystemCharacter* PlayerCharacter = Cast<ASkillTreeSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacters.Add(PlayerCharacter);
	for (ASkillTreeSystemCharacter* Character : PlayerCharacters)
	{
		Character->OnStart();
	}
}

void ASkillTreeSystemGameMode::Tick(float DeltaSeconds)
{
	for (ASkillTreeSystemCharacter* Character : PlayerCharacters)
	{
		Character->OnTick();
	}
}
