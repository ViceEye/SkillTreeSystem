// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeActor.h"

ASkillTreeActor::ASkillTreeActor()
{
	SkillTreeComponent = CreateDefaultSubobject<USkillTreeComponent>(TEXT("SkillTreeComponent"));
}

/////////// Exp ///////////
/** Get Player's Current Grade **/
int ASkillTreeActor::GetCurrentGrade_Implementation()
{
	int TempExp = SkillTreeComponent->GetCurrentPlayerExp();
	int Grade = 1;
	while (TempExp >= Grade * BaseExpIncrement)
	{
		TempExp -= Grade * BaseExpIncrement;
		Grade++;
	}
	return Grade;
}
	
/** Get Player's Current Exp for UI bar **/
int ASkillTreeActor::GetNowExp_Implementation()
{
	int TempExp = SkillTreeComponent->GetCurrentPlayerExp();
	int Grade = 1;
	while (TempExp >= Grade * BaseExpIncrement)
	{
		TempExp -= Grade * BaseExpIncrement;
		Grade++;
	}
	return TempExp;
}
	
/** Get Player's Max Exp for UI bar **/
int ASkillTreeActor::GetMaxExp_Implementation()
{
	return GetCurrentGrade() * BaseExpIncrement;
}

/** Reduce Player's Exp **/
bool ASkillTreeActor::ReduceExp_Implementation(int Exp)
{
	SkillTreeComponent->SetCurrentPlayerExp(SkillTreeComponent->GetCurrentPlayerExp() - Exp);
	return true;
}

/** Set Player's Exp **/
bool ASkillTreeActor::SetExp_Implementation(int Exp)
{
	SkillTreeComponent->SetCurrentPlayerExp(Exp);
	return true;
}

/** Set Player's Grade **/
bool ASkillTreeActor::SetGrade_Implementation(int Grade)
{
	SkillTreeComponent->SetCurrentPlayerExp(Grade * BaseExpIncrement);
	return true;
}
/////////// Exp ///////////

	
////////// Token //////////
/** Get Player's Available Skill Point **/
int ASkillTreeActor::GetSkillPoints_Implementation()
{
	return SkillTreeComponent->GetAvailableSkillPoints();
}
	
/** Reduce Player's Available Skill Point **/
bool ASkillTreeActor::ReduceSkillPoints_Implementation(int Point)
{
	SkillTreeComponent->SetAvailableSkillPoints(SkillTreeComponent->GetAvailableSkillPoints() - Point);
	return true;
}
	
/** Set Player's Available Skill Point **/
bool ASkillTreeActor::SetSkillPoints_Implementation(int Point)
{
	SkillTreeComponent->SetAvailableSkillPoints(Point);
	return true;
}
////////// Token //////////