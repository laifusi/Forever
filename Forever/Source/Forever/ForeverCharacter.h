// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ForeverCharacter.generated.h"

UCLASS()
class FOREVER_API AForeverCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AForeverCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool GetShouldInteract();

private:
	UPROPERTY(EditAnywhere)
	float InteractionRange = 100;
	UPROPERTY(EditAnywhere)
	float InteractionRadius = 10;

	bool bCanInteract;
	bool bShouldInteract;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void SwitchShouldInteract();

};
