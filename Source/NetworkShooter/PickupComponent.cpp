// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"

#include "BlasterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	OverlappingCharacter = nullptr;
	SphereRadius = 100.f;
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnSphereStartOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UPickupComponent::OnSphereEndOverlap);
}

void UPickupComponent::OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor))
	{
		if (GetOwner()->HasAuthority())
		{
			OnStartOverlap.Broadcast(BlasterCharacter);
		}
		
		OverlappingCharacter = BlasterCharacter;
		
		if (BlasterCharacter->IsLocallyControlled())
		{
			BindPickupContext(BlasterCharacter);
		}
	}
}

void UPickupComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor))
	{
		if (GetOwner()->HasAuthority())
		{
			OnEndOverlap.Broadcast(BlasterCharacter);
		}

		if (BlasterCharacter->IsLocallyControlled())
		{
			UnBindPickupContext(BlasterCharacter);
		}
		
		OverlappingCharacter = nullptr;
	}
}

void UPickupComponent::BindPickupContext(const ABlasterCharacter* BlasterCharacter)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(BlasterCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(PickUpMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered, this, &UPickupComponent::ServerPickUp);
		}
	}
}

void UPickupComponent::UnBindPickupContext(const ABlasterCharacter* BlasterCharacter) const
{
	if (!BlasterCharacter)
	{
		return;
	}
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(BlasterCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(PickUpMappingContext);
		}
	}
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickupComponent::PickUpMulticast_Implementation()
{
	// Unregister from the Overlap Event so it is no longer triggered
	OnComponentBeginOverlap.RemoveAll(this);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UPickupComponent::ServerPickUp_Implementation()
{
	OnPickup.Broadcast(OverlappingCharacter);
	PickUpMulticast();
}


