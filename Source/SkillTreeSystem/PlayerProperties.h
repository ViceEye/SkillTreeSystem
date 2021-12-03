// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerProperties.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EPlayerProperties
{
  Damage    UMETA(DisplayName = "Damage"),
  Defend    UMETA(DisplayName = "Defend"),
  Health    UMETA(DisplayName = "Health"),
};
