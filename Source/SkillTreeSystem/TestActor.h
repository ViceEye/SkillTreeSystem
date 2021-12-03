// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProperties.h"
#include "TestActor.generated.h"

UCLASS()
class SKILLTREESYSTEM_API ATestActor : public AActor
{
    GENERATED_BODY()

public: 
    // Sets default values for this actor's properties
    ATestActor();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* VisualMesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EPlayerProperties)
    TEnumAsByte<EPlayerProperties> properties;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public: 
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
