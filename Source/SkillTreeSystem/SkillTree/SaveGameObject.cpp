// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameObject.h"

void USaveGameObject::ClearAllData()
{
	AvailableSkillPoints = 0;
	CurrentPlayerExp = 0;
	PropertiesMap.Empty();
	SkillTreeNodesMap.Empty();
}
