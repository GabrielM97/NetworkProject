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
		OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnSphereOverlap);
	}

}

void UPickupComponent::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor))
	{
		OnPickUp.Broadcast(BlasterCharacter);
	}
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

