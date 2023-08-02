// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "NetworkShooter/BlasterCharacter.h"
#include "NetworkShooter/Weapon/Weapon.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	BaseWalkSpeed = 600.f;
	AimWalkSpeed = 500.f;
}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (!BlasterCharacter || !WeaponToEquip)
	{
		return;
	}
	
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponStete(EWeaponState::EWS_Equipped);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	EquippedWeapon->AttachToComponent(BlasterCharacter->GetMesh(), AttachmentRules ,FName("hand_rSocket"));
	EquippedWeapon->SetOwner(BlasterCharacter);

	BlasterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	BlasterCharacter->bUseControllerRotationYaw = true;
	
	if (BlasterCharacter->HasAuthority())
	{
		BindWeaponEquippedMappingContext();
	}
	
}


void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, EquippedWeapon);
	DOREPLIFETIME(UCombatComponent, bIsAiming);
}

void UCombatComponent::ServerSetAiming_Implementation()
{
	bIsAiming = !bIsAiming;
	if (BlasterCharacter)
	{
		BlasterCharacter->GetCharacterMovement()->MaxWalkSpeed = bIsAiming? AimWalkSpeed : BaseWalkSpeed;
	}
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (BlasterCharacter)
	{
		BlasterCharacter->GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	}
}

void UCombatComponent::AimDownSights()
{
	bIsAiming = !bIsAiming;
	
	if (!BlasterCharacter->HasAuthority())
	{
		ServerSetAiming();
	}

	if (BlasterCharacter)
	{
		BlasterCharacter->GetCharacterMovement()->MaxWalkSpeed = bIsAiming? AimWalkSpeed : BaseWalkSpeed;
	}
}

void UCombatComponent::BindWeaponEquippedMappingContext()
{
	if (BlasterCharacter->IsLocallyControlled())
	{
		if (const APlayerController* PlayerController = Cast<APlayerController>(BlasterCharacter->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(WeaponEquippedMappingContext, 0);
			}

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				// Fire
				EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &UCombatComponent::AimDownSights);
			}
		}
	}
}

void UCombatComponent::OnRep_WeaponEquipped()
{
	BlasterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	BlasterCharacter->bUseControllerRotationYaw = true;
	BindWeaponEquippedMappingContext();
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

