// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeGameInstance.h"

void USkillTreeGameInstance::Init()
{
	Super::Init();
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		SaveGameData = Cast<USaveGameObject>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	else
		SaveGameData = Cast<USaveGameObject>(UGameplayStatics::CreateSaveGameObject(USaveGameObject::StaticClass()));
}

void USkillTreeGameInstance::SaveMyGame()
{
	DoSaveMyGame(0);
}

void USkillTreeGameInstance::DoSaveMyGame(int UserIndex)
{
	UGameplayStatics::SaveGameToSlot(SaveGameData, SlotName, UserIndex);
}

void USkillTreeGameInstance::ClearMyGame()
{
	DoClearMyGame(0);
}

void USkillTreeGameInstance::DoClearMyGame(int UserIndex)
{
	UGameplayStatics::DeleteGameInSlot(SlotName, UserIndex);
	SaveGameData->ClearAllData();
}

