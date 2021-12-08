// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseSkillTreeWidget.h"
#include "SkillTreeGameInstance.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillTreeComponent.generated.h"

class USkillTreeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTickSignature);

UCLASS( ClassGroup=(SkillTreeComponent), meta=(BlueprintSpawnableComponent) )
class SKILLTREESYSTEM_API USkillTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillTreeComponent();

	/** Similar to native OnStart but fire by DoStart(Active) **/
	UPROPERTY(BlueprintAssignable, Category = STDelegates, meta=(DisplayName="OnStart", ScriptName="OnStart"))
	FOnStartSignature OnStart;

	/** Active Component **/
	UFUNCTION(BlueprintCallable, Category = STFunctions)
	void DoStart();
	
	/** Similar to native OnTick but with custom rate **/
	UPROPERTY(BlueprintAssignable, Category = STDelegates, meta=(DisplayName="OnTick", ScriptName="OnTick"))
	FOnTickSignature OnTick;

	/** Delegate Caller **/
	void DoTick();

	/** Sync and Update local data and storage data **/
	UFUNCTION(BlueprintCallable, Category = STFunctions)
	void SyncLocalDataAndStoredData();

	///////////////////////////
	// Getters and Setters
	int GetAvailableSkillPoints() const
	{
		return AvailableSkillPoints;
	}

	void SetAvailableSkillPoints(int Point)
	{
		this->AvailableSkillPoints = Point;
	}

	int GetCurrentPlayerExp() const
	{
		return CurrentPlayerExp;
	}

	void SetCurrentPlayerExp(int Exp)
	{
		this->CurrentPlayerExp = Exp;
	}
	// Getters and Setters
	///////////////////////////

protected:
	
	UFUNCTION(BlueprintCallable, Category=STFunctions)
	void OpenSkillTree();
	
	UPROPERTY(BlueprintReadOnly, Category = STVariables)
	FTimerHandle TimerHandler;

	UPROPERTY(BlueprintReadWrite, Category = STVariables)
	float TimerTickRate = 0.2f;

	UPROPERTY(BlueprintReadWrite, Category = STVariables)
	UBaseSkillTreeWidget* SkillTreeUI;
	
	UPROPERTY(BlueprintReadWrite, Category = STVariables)
	bool IsSkillTreeVisible;

	UPROPERTY(BlueprintReadOnly, Category = STVariables)
	USkillTreeGameInstance* SkillTreeInstance;
	
	UPROPERTY(BlueprintReadOnly, Category = STVariables)
	int AvailableSkillPoints;
	
	UPROPERTY(BlueprintReadOnly, Category = STVariables)
	int CurrentPlayerExp;

	UPROPERTY(BlueprintReadOnly, Category = STVariables)
	TMap<FString, float> PropertiesMap;
	
	UPROPERTY(BlueprintReadOnly, Category = STVariables)
	TMap<FString, bool> SkillTreeNodesMap;
		
	static void DebugMsg(const FString& Msg);
};
