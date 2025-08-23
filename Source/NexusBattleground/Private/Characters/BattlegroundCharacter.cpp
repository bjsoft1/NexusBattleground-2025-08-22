// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlegroundCharacter.h"

// Sets default values
ABattlegroundCharacter::ABattlegroundCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattlegroundCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattlegroundCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattlegroundCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

