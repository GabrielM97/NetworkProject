// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class ABlasterCharacter;
class UPickupComponent;
class UWidgetComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),

	EWS_MAX  UMETA(DisplayName = "Defualt Max")
};

UCLASS()
class NETWORKSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

private:
	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	EWeaponState WeaponState;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	UWidgetComponent* PickupWidget;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	UPickupComponent* PickupComponent;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_WeaponOverlapped, Category="Weapon Properties")
	bool bWeaponOverlapped;

	UFUNCTION()
	void OnRep_WeaponOverlapped();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnWeaponStartOverlapped(ABlasterCharacter* BlasterCharacter);
	
	UFUNCTION()
	virtual void OnWeaponEndOverlapped(ABlasterCharacter* BlasterCharacter);

	UFUNCTION()
	virtual void OnWeaponPickedUp(ABlasterCharacter* BlasterCharacter);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWeaponStete(EWeaponState NewWeaponState) {WeaponState = NewWeaponState;};

};
