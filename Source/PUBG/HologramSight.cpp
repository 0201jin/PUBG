// Fill out your copyright notice in the Description page of Project Settings.

#include "HologramSight.h"
#include "Engine.h"

// Sets default values
AHologramSight::AHologramSight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletBoxMesh(TEXT("StaticMesh'/Game/Model/M4A1/Mesh/hologram.hologram'"));

	mHoloGram = NewObject<UStaticMeshComponent>(this, TEXT("HoloGram"));
	RootComponent = mHoloGram;
	mHoloGram->SetStaticMesh(BulletBoxMesh.Object);
	mHoloGram->RelativeScale3D = FVector(1, 1, 1);
	mHoloGram->SetCollisionProfileName("OverlapOnlyPawn");
	mHoloGram->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AHologramSight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHologramSight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AHologramSight::GetItemName()
{
	return "HoloGramSight";
}

void AHologramSight::PickUp()
{
	if (!Player->InvenMap.Find("HoloGramSight"))
	{
		Player->InvenMap.Add("HoloGramSight", 1);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("HoloGramSight");
	*count += 1;
	Player->InvenMap.Add("HoloGramSight", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, -1000));
}

void AHologramSight::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int AHologramSight::GetItemCount()
{
	return 1;
}

void AHologramSight::SetItemCount(int g_count)
{
}

int AHologramSight::GetCheckItem()
{
	return 2;
}

