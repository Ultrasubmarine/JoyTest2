// Copyright Epic Games, Inc. All Rights Reserved.

#include "JoyTestCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"


#include "JoyTestGameMode.h"
#include "PickableActor.h"
#include "Items/Item.h"
#include "Items/WeaponItem.h"
#include "Items/HealthItem.h"
//////////////////////////////////////////////////////////////////////////
// AJoyTestCharacter


AJoyTestCharacter::AJoyTestCharacter()
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

	//// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
;

	PickableBox = CreateDefaultSubobject<UBoxComponent>("PickableBox");
	PickableBox->SetCollisionProfileName(FName("Custom"));
	PickableBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickableBox->SetCollisionObjectType(ECC_Pawn);
	PickableBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	PickableBox->SetupAttachment(RootComponent);
	PickableBox->SetGenerateOverlapEvents(true);

	//GetMesh()->GetAnimClass()->Set
	healthCurrent = health;
	SetState(CharacterState::Live);

	// Create a follow camera
	
	/*FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), USpringArmComponent::SocketName); */// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
//	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
//	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJoyTestCharacter::PickUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "PICKUP");
	if (_pickableObjects.Num() > 0)
	{
		UItem* i = Cast<UItem>(_pickableObjects[_pickableObjects.Num() - 1]->GetItem()->GetDefaultObject() );
		
		switch (i->GetType())
		{
		case ItemType::ITEM_GUN:
		{
			auto wi = Cast<UWeaponItem>(i);
			if (wi)
			{
				SetWeapon(wi);
			}

			break;
		}
		case ItemType::ITEM_HEALTH:
		{
			auto hi = Cast<UHealthItem>(i);
			if (hi)
			{
				healthCurrent += hi->GetHealthValue();

				if (healthCurrent > health)
					healthCurrent = health;

				OnChangeHealth.Broadcast(health, healthCurrent);
			}

			break;
		}
		default:
			break;
		}
	

		_pickableObjects[_pickableObjects.Num() - 1]->Destroy();
	}

}

void AJoyTestCharacter::OnPickableCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{

	if (OtherActor == this)
		return;

	
	if (APickableActor* pa = Cast<APickableActor>(OtherActor))
	{

		_pickableObjects.Add(pa);

		if (_pickableObjects.Num() == 1)
			OnChangePickUpAbility.Broadcast(true);
	}

}

void AJoyTestCharacter::OnPickableCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;

	if (APickableActor* pa = Cast<APickableActor>(OtherActor))
	{
		_pickableObjects.Remove(pa);

		if (_pickableObjects.Num() == 0)
			OnChangePickUpAbility.Broadcast(false);
	}
}

void AJoyTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJoyTestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJoyTestCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJoyTestCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJoyTestCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJoyTestCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJoyTestCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AJoyTestCharacter::OnResetVR);

	PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &AJoyTestCharacter::PickUp);	

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AJoyTestCharacter::OnFireStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AJoyTestCharacter::OnFireEnd);

}


void AJoyTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	PickableBox->OnComponentBeginOverlap.AddDynamic(this, &AJoyTestCharacter::OnPickableCapsuleBeginOverlap);
	PickableBox->OnComponentEndOverlap.AddDynamic(this, &AJoyTestCharacter::OnPickableCapsuleEndOverlap);
	
	playerController = static_cast<APlayerController*>(this->GetController());

}

void AJoyTestCharacter::Respawn()
{
	SetState(CharacterState::Live);
	healthCurrent = health;
	OnChangeHealth.Broadcast(health,healthCurrent);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "I'm live");
}


void AJoyTestCharacter::SetWeapon(UWeaponItem* weapon)
{
	if (currentWeapon)
		currentWeapon->Destroy();

	currentWeapon = GetWorld()->SpawnActor<AWeaponActor>(weapon->GetWeaponActor(), GetMesh()->GetSocketTransform(FName("hand_r")));	
	currentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r"));

	OnWeaponChange.Broadcast(weapon);
}

void AJoyTestCharacter::OnFireStart()
{
	if (currentWeapon)
	{
		OnWeaponFire.Broadcast(true);
		Fire(true);
	}
}

void AJoyTestCharacter::OnFireEnd()
{
	if (currentWeapon)
	{
		OnWeaponFire.Broadcast(false);
		Fire(false);
	}
}

void AJoyTestCharacter::Damage(int value)
{
	if (state == CharacterState::Death)
		return;

	healthCurrent -= value;
	
	if (healthCurrent <= 0)
	{
		healthCurrent = 0;
		SetState(CharacterState::Death);
	}
	
	OnChangeHealth.Broadcast(health, healthCurrent);
}

void AJoyTestCharacter::SetState(CharacterState newState)
{
	if (newState == state)
		return;

	state = newState;
	
	//playerController->GetInputMode
	switch (state)
	{
	case CharacterState::Live:
	{		
		playerController->SetInputMode(FInputModeGameOnly());
		break;
	}
	case CharacterState::Death:
	{
		playerController->SetInputMode(FInputModeUIOnly());
		playerController->PostNetReceiveVelocity(FVector{ 0,0,0 });
		break;
	}

	default:
		break;
	}

	OnChangeCharacterState.Broadcast(state);
}

CharacterState AJoyTestCharacter::GetState()
{
	return state;
}

void AJoyTestCharacter::OnResetVR()
{
	// If JoyTest is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in JoyTest.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AJoyTestCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AJoyTestCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AJoyTestCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJoyTestCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJoyTestCharacter::MoveForward(float Value)
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

void AJoyTestCharacter::MoveRight(float Value)
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
