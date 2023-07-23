// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"

#include "BlasterCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SphereRadius = 100.f;
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnSphereStartOverlap);
		OnComponentEndOverlap.AddDynamic(this, &UPickupComponent::OnSphereEndOverlap);
	}
}

void UPickupComponent::OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor))
	{
		OnStartOverlap.Broadcast(BlasterCharacter);
	}
}

void UPickupComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor))
	{
		OnEndOverlap.Broadcast(BlasterCharacter);
	}
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

