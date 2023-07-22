// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "NetworkShooter/BlasterCharacter.h"
#include "NetworkShooter/PickupComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates	= true;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SetRootComponent(WeaponMesh);
	
	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUp Widget"));
	PickupWidget->SetupAttachment(RootComponent);

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("Pickup Component"));
	PickupComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	PickupComponent->OnPickUp.AddDynamic(this, &AWeapon::OnWeaponOverlapped);
	PickupWidget->SetVisibility(false);
	
}

void AWeapon::OnWeaponOverlapped(ABlasterCharacter* BlasterCharacter)
{
	PickupWidget->SetVisibility(true);
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

