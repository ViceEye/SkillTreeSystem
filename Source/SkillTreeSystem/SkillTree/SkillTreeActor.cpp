// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeActor.h"

ASkillTreeActor::ASkillTreeActor()
{
	SkillTreeComponent = CreateDefaultSubobject<USkillTreeComponent>(TEXT("SkillTreeComponent"));
}


// Debug Tool / Notice Tool //
static void GlobalNoticing_Imp(const FString& Msg)
{
	USkillTreeComponent::GlobalNoticing(TEXT("ASkillTreeActor"), Msg, FColor::Green);	
}
// Debug Tool / Notice Tool //


////////// Base //////////
void ASkillTreeActor::DoLoad_Implementation()
{
	GlobalNoticing_Imp(TEXT("CPP Functioning"));
	if (SkillTreeWidgetClass != nullptr)
	{
		UUserWidget* MyWidget = CreateWidget<UUserWidget>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		SkillTreeWidgetClass
		);
		MyWidget->AddToViewport();
		
		SkillTreeComponent->OnTick.AddDynamic(SkillTreeComponent, &USkillTreeComponent::SyncLocalDataAndStoredData);
		SkillTreeComponent->DoStart(MyWidget);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillTreeWidgetClass of SkillTreeActor not defined."));
	}
}
////////// Base //////////


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

/** Add Player's Exp **/
bool ASkillTreeActor::AddExp_Implementation(int Exp)
{
	SkillTreeComponent->SetCurrentPlayerExp(SkillTreeComponent->GetCurrentPlayerExp() + Exp);
	return true;
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
	SkillTreeComponent->SetCurrentPlayerExp(Grade / 2 * (1 + Grade) * BaseExpIncrement);
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