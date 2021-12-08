// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegateSignature);

UCLASS()
class SKILLTREESYSTEM_API ATestActor : public AActor
{
    GENERATED_BODY()

public: 
    // Sets default values for this actor's properties
    ATestActor();
    
    UPROPERTY(BlueprintAssignable)
    FTestDelegateSignature TestDelegate;
    
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* VisualMesh;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public: 
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
