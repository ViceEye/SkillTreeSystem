// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeComponent.h"

USkillTreeComponent::USkillTreeComponent()
{
	
}


// Debug Tool / Notice Tool //
static void GlobalNoticing_Imp(const FString& Msg)
{
	USkillTreeComponent::GlobalNoticing(TEXT("USkillTreeComponent"), Msg, FColor::Magenta);	
}
// Debug Tool / Notice Tool //


void USkillTreeComponent::OpenSkillTree()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		if (SkillTreeUI != nullptr)	
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
		else
		{
			GlobalNoticing_Imp(TEXT("失败"));
		}
	}
	else
	{
	}
}

void USkillTreeComponent::DoStart(UUserWidget* Widget)
{
	SkillTreeInstance = Cast<USkillTreeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	SkillTreeUI = Cast<UBaseSkillTreeWidget>(Widget);
	GlobalNoticing(TEXT("USkillTreeComponent"), TEXT("Loaded up!"), FColor::Blue);
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
