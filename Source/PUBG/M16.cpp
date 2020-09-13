// Fill out your copyright notice in the Description page of Project Settings.

#include "M16.h"


// Sets default values
AM16::AM16()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M16/M16.M16'"));
	mWeaponMesh = NewObject<UStaticMeshComponent>(this, TEXT("CharacterWeaponMesh"));
	RootComponent = mWeaponMesh;
	mWeaponMesh->SetStaticMesh(lWeaponMesh.Object);
	mWeaponMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, -10.0f));
	mWeaponMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 3.0f));
	mWeaponMesh->SetCollisionProfileName("OverlapOnlyPawn");
	mWeaponMesh->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AM16::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AM16::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AM16::GetItemName()
{
	return "M16";
}

void AM16::PickUp()
{
	if (!Player->InvenMap.Find("M16"))
	{
		Player->InvenMap.Add("M16", 1);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("M16");
	*count += 1;
	Player->InvenMap.Add("M16", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, -1000));
}

void AM16::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int AM16::GetItemCount()
{
	return 1;
}

void AM16::SetItemCount(int g_count)
{
}

int AM16::GetCheckItem()
{
	return 1;
}

void AM16::SetHoloGram(bool g_holo)
{
	bHoloGram = g_holo;
}

bool AM16::GetHoloGram()
{
	return bHoloGram;
}

