// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkillTreeNodeWidget.h"

#include "SkillTreeSystemCharacter.h"

TEnumAsByte<ERespond> UBaseSkillTreeNodeWidget::TryActive()
{
	ACharacter* APlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ASkillTreeSystemCharacter* PlayerCharacter = Cast<ASkillTreeSystemCharacter>(APlayerCharacter);
	if (PreviousNode != nullptr)
	{
		if (PreviousNode->IsActive)
		{
			if (PlayerCharacter->AvailableSkillPoints >= SkillPointNeeded)
			{
				PlayerCharacter->AvailableSkillPoints -= SkillPointNeeded;
			}
		}
		else
		{
			return PREVIOUS_NODE_NOT_ACTIVE;
		}
	}
	else
	{
		IsActive = true;
		return SUCCESS_ACTIVATED;
	}
	return SUCCESS_ACTIVATED;
}
