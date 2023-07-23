// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
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

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AWeapon, bWeaponOverlapped, COND_OwnerOnly);
}

void AWeapon::OnRep_WeaponOverlapped()
{
	PickupWidget->SetVisibility(bWeaponOverlapped);

	if (!bWeaponOverlapped)
	{
		Owner =  nullptr;
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	PickupComponent->OnStartOverlap.AddDynamic(this, &AWeapon::OnWeaponStartOverlapped);
	PickupComponent->OnEndOverlap.AddDynamic(this, &AWeapon::OnWeaponEndOverlapped);
	PickupWidget->SetVisibility(false);
}

void AWeapon::OnWeaponStartOverlapped(ABlasterCharacter* BlasterCharacter)
{
	Owner =  BlasterCharacter;
	bWeaponOverlapped = true;
	
	if (BlasterCharacter->IsLocallyControlled())
	{
		PickupWidget->SetVisibility(bWeaponOverlapped);
	}
}

void AWeapon::OnWeaponEndOverlapped(ABlasterCharacter* BlasterCharacter)
{
	bWeaponOverlapped = false;
	
	if (BlasterCharacter->IsLocallyControlled())
	{
		PickupWidget->SetVisibility(bWeaponOverlapped);
		Owner = nullptr;
	}
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

