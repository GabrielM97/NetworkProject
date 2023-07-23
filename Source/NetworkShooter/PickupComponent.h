// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "PickupComponent.generated.h"


class ABlasterCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartOverlap, ABlasterCharacter*, PickUpCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndOverlap, ABlasterCharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NETWORKSHOOTER_API UPickupComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPickupComponent();
	
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnStartOverlap OnStartOverlap;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnEndOverlap OnEndOverlap;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
