// Fill out your copyright notice in the Description page of Project Settings.


#include "ForeverCharacter.h"
#include "GameFramework/Controller.h"

// Sets default values
AForeverCharacter::AForeverCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AForeverCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AForeverCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AController* PlayerController = GetController();
	if (PlayerController == nullptr)
	{
		bCanInteract = false;
		return;
	}

	FVector StartLocation;
	FRotator Rotation;
	PlayerController->GetPlayerViewPoint(StartLocation, Rotation);

	FVector End = StartLocation + Rotation.Vector() * InteractionRange;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractionRadius);

	FHitResult Hit;
	bool bHit = GetWorld()->SweepSingleByChannel(Hit, StartLocation, End, FQuat::Identity, ECC_GameTraceChannel1, Sphere);
	if (bHit)
	{
		bCanInteract = true;
		UE_LOG(LogTemp, Warning, TEXT("HIT: %f"), GetWorld()->TimeSeconds);
	}
	else
	{
		bCanInteract = false;
	}
}

// Called to bind functionality to input
void AForeverCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("WalkForward"), this, &AForeverCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("WalkRight"), this, &AForeverCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AForeverCharacter::SwitchShouldInteract);
}

bool AForeverCharacter::GetShouldInteract()
{
	return bShouldInteract;
}

void AForeverCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AForeverCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AForeverCharacter::SwitchShouldInteract()
{
	if (bCanInteract)
	{
		//bShouldInteract = !bShouldInteract;
		
		// INTERACT
	}
}

