// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseSkillTreeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SKILLTREESYSTEM_API UBaseSkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = UI)
	TArray<UWidget*> NodesList;

	UFUNCTION(BlueprintImplementableEvent, Category = UI)
	void RequestRegisterNodes();
	
	UFUNCTION(BlueprintCallable, Category = UI)
	void RegisterAllNodes(TArray<UWidget*> NodesArray);

	/*Responsible for load all nodes from storage*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = UI)
	void LoadAllNodeWidgets();

	/*Responsible for save all nodes | Name => Active? |*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = UI)
	void SaveAllNodeWidgets();

	UFUNCTION()
	void ListenToNodeActivation(UUserWidget* NodeWidget);
	
	/*Responsible for open and close Skill Tree*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void OpenOrCloseST(bool open);
	
};
