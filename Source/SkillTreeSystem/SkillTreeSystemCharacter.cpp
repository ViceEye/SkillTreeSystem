// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkillTreeSystemCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ASkillTreeSystemCharacter

ASkillTreeSystemCharacter::ASkillTreeSystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Skill Tree Implementations
void ASkillTreeSystemCharacter::OnKeyPressed()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		SkillTreeUI->OpenOrCloseST(!IsSkillTreeVisible);
		if (IsSkillTreeVisible)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			PlayerController->SetShowMouseCursor(false);
		}
		else
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, SkillTreeUI, EMouseLockMode::LockOnCapture, false);
			PlayerController->SetShowMouseCursor(true);
		}
		IsSkillTreeVisible = !IsSkillTreeVisible;
	}
}

void ASkillTreeSystemCharacter::OnStart()
{
	SkillTreeInstance = Cast<USkillTreeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DebugMsg(TEXT("Loaded up!"));
	BPOnStart();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &ASkillTreeSystemCharacter::OnTick, 0.2, true);
}

void ASkillTreeSystemCharacter::OnTick()
{
	BPOnTick();
}

void ASkillTreeSystemCharacter::SyncLocalDataAndStoredData()
{
	const USaveGameObject* Data = SkillTreeInstance->SaveGameData;
	this->AvailableSkillPoints = Data->AvailableSkillPoints;
	this->CurrentPlayerExp = Data->CurrentPlayerExp;
	this->PropertiesMap = Data->PropertiesMap;
	this->SkillTreeNodesMap = Data->SkillTreeNodesMap;
}

void ASkillTreeSystemCharacter::DebugMsg(const FString& Msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Msg); 
}


//////////////////////////////////////////////////////////////////////////
// Input

void ASkillTreeSystemCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASkillTreeSystemCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASkillTreeSystemCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASkillTreeSystemCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASkillTreeSystemCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASkillTreeSystemCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASkillTreeSystemCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ASkillTreeSystemCharacter::OnResetVR);
}


void ASkillTreeSystemCharacter::OnResetVR()
{
	// If SkillTreeSystem is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in SkillTreeSystem.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASkillTreeSystemCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ASkillTreeSystemCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ASkillTreeSystemCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASkillTreeSystemCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASkillTreeSystemCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASkillTreeSystemCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
