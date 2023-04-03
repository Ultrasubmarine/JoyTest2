// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JoyTestCharacter.generated.h"

class UBoxComponent;
class APickableActor;
class AWeaponActor;

UENUM(BlueprintType)
enum class CharacterState : uint8
{
	Live,
	Death,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeHealth, int, fullValue, int, newValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeCharacterState, CharacterState, newState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangePickUpAbility, bool, abilityState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponChange, UWeaponItem*, weapon);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponFire, bool, fire);

UCLASS(config=Game)
class AJoyTestCharacter : public ACharacter
{
	GENERATED_BODY()


	///** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	/** Follow camera */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
//	class UCameraComponent* FollowCamera;
public:
	AJoyTestCharacter();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Respawn();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickable")
	UBoxComponent* PickableBox;

	APlayerController* playerController;

// WEAPON
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeaponActor* currentWeapon;

	UFUNCTION(BlueprintCallable)
	void SetWeapon(UWeaponItem* weapon);

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FWeaponChange OnWeaponChange;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FWeaponFire OnWeaponFire;

protected:

	UFUNCTION()
	void OnFireStart();

	UFUNCTION()
	void OnFireEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void Fire(bool isActive);

// HEALTH
public:

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FChangeHealth OnChangeHealth;

	UFUNCTION(BlueprintCallable)
	void Damage(int value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int health = 100;

	int healthCurrent;

protected:

// CHARACTER STATE
	CharacterState state;

	void SetState( CharacterState newState);

public:

	UFUNCTION(BlueprintCallable)
	CharacterState GetState();

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FChangeCharacterState OnChangeCharacterState;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

// PICK_UP_OBJECTS
public:
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FChangePickUpAbility OnChangePickUpAbility;

protected:

	TArray<APickableActor*> _pickableObjects;

	UFUNCTION()
	void PickUp();

	UFUNCTION()
	void OnPickableCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPickableCapsuleEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

//public:
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
//	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

