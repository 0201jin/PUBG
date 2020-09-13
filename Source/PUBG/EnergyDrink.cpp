// Fill out your copyright notice in the Description page of Project Settings.

#include "EnergyDrink.h"
#include "Engine.h"


// Sets default values
AEnergyDrink::AEnergyDrink()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DrinkMesh(TEXT("StaticMesh'/Game/Model/Drink/Drink.Drink'"));

	mDrink = NewObject<UStaticMeshComponent>(this, TEXT("Drink"));
	RootComponent = mDrink;
	mDrink->SetStaticMesh(DrinkMesh.Object);
	mDrink->RelativeScale3D = FVector(1, 1, 1);
	mDrink->SetCollisionProfileName("OverlapOnlyPawn");
	mDrink->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AEnergyDrink::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnergyDrink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AEnergyDrink::GetItemName()
{
	return "EnergyDrink";
}

void AEnergyDrink::PickUp()
{
	if (!Player->InvenMap.Find("EnergyDrink"))
	{
		Player->InvenMap.Add("EnergyDrink", 1);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("EnergyDrink");
	*count += 1;
	Player->InvenMap.Add("EnergyDrink", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0,0,-1000));
}

void AEnergyDrink::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int AEnergyDrink::GetItemCount()
{
	return 1;
}

void AEnergyDrink::SetItemCount(int g_count)
{
}

int AEnergyDrink::GetCheckItem()
{
	return 0;
}

void AEnergyDrink::UseItem()
{
	Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->AddEnergy(40);
}

