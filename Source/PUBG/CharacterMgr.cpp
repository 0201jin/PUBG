// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterMgr.h"


// Sets default values
ACharacterMgr::ACharacterMgr()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterMgr::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterMgr::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterMgr::Damage(float g_Damage)
{
}

