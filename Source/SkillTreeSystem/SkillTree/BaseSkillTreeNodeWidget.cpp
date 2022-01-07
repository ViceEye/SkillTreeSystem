// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkillTreeNodeWidget.h"

TEnumAsByte<ERespond> UBaseSkillTreeNodeWidget::TryActive(ASkillTreeActor* SkillTreeActor)
{
	if (SkillTreeActor == nullptr)
	{
		return DEBUG_FAIL;
	}
	
	if (PreviousNode != nullptr)
	{
		if (!PreviousNode->IsActive)
		{
			return PREVIOUS_NODE_NOT_ACTIVE;
		}
	}

	if (SkillTreeActor->GetCurrentGrade() < LevelNeeded)
	{
		return REQUIRE_GRADE_LEVEL_NOT_ENOUGH;
	}

	if (SkillTreeActor->GetSkillPoints() < SkillPointNeeded)
	{
		return REQUIRE_SKILL_POINT_NOT_ENOUGH;
	}

	SkillTreeActor->SetSkillPoints(SkillTreeActor->GetSkillPoints() - SkillPointNeeded);
	return SUCCESS_ACTIVATED;
}
