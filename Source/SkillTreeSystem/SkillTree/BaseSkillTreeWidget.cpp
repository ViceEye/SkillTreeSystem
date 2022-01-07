// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkillTreeWidget.h"

#include "BaseSkillTreeNodeWidget.h"
#include "SkillTreeComponent.h"


// Debug Tool / Notice Tool //
static void GlobalNoticing_Imp(const FString& Msg)
{
	USkillTreeComponent::GlobalNoticing(TEXT("UBaseSkillTreeWidget"), Msg, FColor::Orange);	
}
// Debug Tool / Notice Tool //


void UBaseSkillTreeWidget::RegisterAllNodes(TArray<UWidget*> NodesArray)
{
	NodesList = NodesArray;
	for (UWidget* Node : NodesList)
	{
		UBaseSkillTreeNodeWidget* SkillTreeNode = Cast<UBaseSkillTreeNodeWidget>(Node);
		SkillTreeNode->NodeActivation.AddDynamic(
			this,
			&UBaseSkillTreeWidget::ListenToNodeActivation);
		GlobalNoticing_Imp(TEXT("Register ") + SkillTreeNode->Name);
	}
}


void UBaseSkillTreeWidget::ListenToNodeActivation()
{
	GlobalNoticing_Imp(TEXT("Activation Recieved"));
	SaveAllNodeWidgets();
}


void UBaseSkillTreeWidget::LoadAllNodeWidgets_Implementation()
{
	if (NodesList.Num() > 0)
	{
		TMap<FString, UBaseSkillTreeNodeWidget*> NodeList;
		for (UWidget* Node : NodesList)
		{
			UBaseSkillTreeNodeWidget* SkillTreeNode = Cast<UBaseSkillTreeNodeWidget>(Node);
			NodeList.Add(SkillTreeNode->Name, SkillTreeNode);
		}
		UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
		USkillTreeGameInstance* GameInstance = Cast<USkillTreeGameInstance>(Instance);
		if (GameInstance != nullptr)
		{
			for (TTuple<FString, bool> NodeTuple : GameInstance->SaveGameData->SkillTreeNodesMap)
			{
				if (NodeList.Contains(NodeTuple.Key))
				{
					UBaseSkillTreeNodeWidget* NodeWidget = *NodeList.Find(NodeTuple.Key);
					NodeWidget->SetActive(NodeTuple.Value);
					NodeTuple.Value ? 
					GlobalNoticing_Imp(NodeTuple.Key + TEXT(" is load true！")):
					GlobalNoticing_Imp(NodeTuple.Key + TEXT(" is load false！"));
				}
			}
		}
		else
		{
			GlobalNoticing_Imp(TEXT("Load Failed"));
		}
		GlobalNoticing_Imp(TEXT("Loaded"));
	}
	else
	{
		GlobalNoticing_Imp(TEXT("NodesList Un-Inistialized"));
	}
}


void UBaseSkillTreeWidget::SaveAllNodeWidgets_Implementation()
{
	if (NodesList.Num() > 0)
	{
		UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
		USkillTreeGameInstance* GameInstance = Cast<USkillTreeGameInstance>(Instance);
		if (GameInstance != nullptr)
		{
			GameInstance->SaveGameData->SkillTreeNodesMap.Empty();
			for (UWidget* Node : NodesList)
			{
				UBaseSkillTreeNodeWidget* SkillTreeNode = Cast<UBaseSkillTreeNodeWidget>(Node);
				if (SkillTreeNode != nullptr)
				{
					SkillTreeNode->IsActive ? 
					GlobalNoticing_Imp(SkillTreeNode->Name + TEXT(" is save true")):
					GlobalNoticing_Imp(SkillTreeNode->Name + TEXT(" is save false"));
					GameInstance->SaveGameData->SkillTreeNodesMap.Add(SkillTreeNode->Name, SkillTreeNode->IsActive);
				}
			}
			GameInstance->SaveMyGame();
		}
		else
		{
			GlobalNoticing_Imp(TEXT("Save Failed"));
		}
		GlobalNoticing_Imp(TEXT("Saved"));
	}
	else
	{
		GlobalNoticing_Imp(TEXT("NodesList Un-Inistialized"));
	}
}

