// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageZone.h"
#include "JoyTestCharacter.h"

// Sets default values
ADamageZone::ADamageZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickableCapsule = CreateDefaultSubobject<UBoxComponent>("TriggerZone");
	PickableCapsule->SetCollisionProfileName(FName("Custom"));
	PickableCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickableCapsule->SetCollisionObjectType(ECC_Pawn);
	PickableCapsule->SetCollisionResponseToAllChannels(ECR_Overlap);
	PickableCapsule->SetupAttachment(RootComponent);
	PickableCapsule->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ADamageZone::BeginPlay()
{
	Super::BeginPlay();

	PickableCapsule->OnComponentBeginOverlap.AddDynamic(this, &ADamageZone::OnBeginOverlap);
	PickableCapsule->OnComponentEndOverlap.AddDynamic(this, &ADamageZone::OnEndOverlap);
	
}

void ADamageZone::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{

	if (OtherActor == this)
		return;

	if (AJoyTestCharacter* c = Cast<AJoyTestCharacter>(OtherActor))
	{
		_damagedCharacters.Add(c, FDamagedCharacter{ c, delayDelta});
	}

}

void ADamageZone::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AJoyTestCharacter* c = Cast<AJoyTestCharacter>(OtherActor))
	{
		_damagedCharacters.Remove(c);
	}
}

void ADamageZone::Damage(FDamagedCharacter& c)
{
	c.Character->Damage(damageValue);
	c.LastDamageTime = 0;
}


// Called every frame
void ADamageZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for ( TPair<AJoyTestCharacter*, FDamagedCharacter>& o : _damagedCharacters)
	{
		o.Value.LastDamageTime += DeltaTime;

		if (o.Value.LastDamageTime > delayDelta)
		{
			Damage(o.Value);
		}
	}
}

