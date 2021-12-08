// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillTreeComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillTreeActor.generated.h"

UCLASS()
class SKILLTREESYSTEM_API ASkillTreeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillTreeActor();

	/////////// Exp ///////////
	/** Get Player's Current Grade **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	int GetCurrentGrade();
	
	/** Get Player's Current Exp for UI bar **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	int GetNowExp();
	
	/** Get Player's Max Exp for UI bar **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	int GetMaxExp();

	/** Reduce Player's Exp **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	bool ReduceExp(int Exp);

	/** Set Player's Exp **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	bool SetExp(int Exp);

	/** Set Player's Grade **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	bool SetGrade(int Grade);
	/////////// Exp ///////////

	
	////////// Token //////////
	/** Get Player's Available Skill Point **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	int GetSkillPoints();
	
	/** Reduce Player's Available Skill Point **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	bool ReduceSkillPoints(int Point);
	
	/** Set Player's Available Skill Point **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = STFunctions)
	bool SetSkillPoints(int Point);
	////////// Token //////////
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = STVariables)
	USkillTreeComponent* SkillTreeComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = STVariables)
	int BaseExpIncrement = 100;
};
