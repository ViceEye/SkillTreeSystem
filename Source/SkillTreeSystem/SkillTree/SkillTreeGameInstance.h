// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "SaveGameObject.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SkillTreeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SKILLTREESYSTEM_API USkillTreeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void SaveMyGame();

	/** For Multiplayer implementation **/
	UFUNCTION(BlueprintCallable)
	void DoSaveMyGame(int UserIndex);
	
	UFUNCTION(BlueprintCallable)
	void ClearMyGame();
	
	/** For Multiplayer implementation **/
	UFUNCTION(BlueprintCallable)
	void DoClearMyGame(int UserIndex);

	UPROPERTY(BlueprintReadOnly)
	USaveGameObject* SaveGameData;
	
protected:
	FString SlotName = TEXT("SkillTreeSavedData");
};
