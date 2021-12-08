// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeComponent.h"

USkillTreeComponent::USkillTreeComponent()
{
	
}

void USkillTreeComponent::OpenSkillTree()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		SkillTreeUI->OpenOrCloseST(!IsSkillTreeVisible);
		if (IsSkillTreeVisible)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			PlayerController->SetShowMouseCursor(false);
		}
		else
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, SkillTreeUI, EMouseLockMode::LockOnCapture, false);
			PlayerController->SetShowMouseCursor(true);
		}
		IsSkillTreeVisible = !IsSkillTreeVisible;
	}
}

void USkillTreeComponent::DoStart()
{
	SkillTreeInstance = Cast<USkillTreeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DebugMsg(TEXT("Loaded up!"));
	OnStart.Broadcast();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &USkillTreeComponent::DoTick, TimerTickRate, true);
}

void USkillTreeComponent::DoTick()
{
	OnTick.Broadcast();
}

void USkillTreeComponent::SyncLocalDataAndStoredData()
{
	const USaveGameObject* Data = SkillTreeInstance->SaveGameData;
	this->AvailableSkillPoints = Data->AvailableSkillPoints;
	this->CurrentPlayerExp = Data->CurrentPlayerExp;
	this->PropertiesMap = Data->PropertiesMap;
	this->SkillTreeNodesMap = Data->SkillTreeNodesMap;
}

void USkillTreeComponent::DebugMsg(const FString& Msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Msg); 
}

