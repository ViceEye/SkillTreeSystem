// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "BaseSkillTreeWidget.h"
#include "SkillTreeGameInstance.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkillTreeSystemCharacter.generated.h"

UCLASS(config=Game)
class ASkillTreeSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
public:
	ASkillTreeSystemCharacter();

	//////////////////////////////////////////////////////////////////////////
	// Skill Tree Implementations

	UPROPERTY(BlueprintReadOnly, Category = UIVariables)
	FTimerHandle TimerHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIVariables)
	bool IsSkillTreeVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIVariables)
	UBaseSkillTreeWidget* SkillTreeUI;

	UPROPERTY(BlueprintReadOnly, Category = UIVariables)
	USkillTreeGameInstance* SkillTreeInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIVariables)
	int AvailableSkillPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIVariables)
	int CurrentPlayerExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIVariables)
	TMap<FString, float> PropertiesMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIVariables)
	TMap<FString, bool> SkillTreeNodesMap;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UIFunctions)
	int GetCurrentGrade();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UIFunctions)
	int GetNowExp();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UIFunctions)
	int GetMaxExp();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UIFunctions)
	bool ReduceExp(int Exp);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UIFunctions)
	bool SetExp(int Exp);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UIFunctions)
	bool SetGrade(int Grade);
	
	void OnStart();
	
	UFUNCTION(BlueprintImplementableEvent, Category = UIFunctions, meta=(DisplayName="OnStart", ScriptName="OnStart"))
	void BPOnStart();
	
	void OnTick();
	
	UFUNCTION(BlueprintImplementableEvent, Category = UIFunctions, meta=(DisplayName="OnTickPerSecond", ScriptName="OnTick"))
	void BPOnTick();

	UFUNCTION(BlueprintCallable, Category = UIFunctions)
	void SyncLocalDataAndStoredData();
	
	//////////////////////////////////////////////////////////////////////////

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	UFUNCTION(BlueprintCallable, Category=UI)
	void OnKeyPressed();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	static void DebugMsg(const FString& Msg);
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

