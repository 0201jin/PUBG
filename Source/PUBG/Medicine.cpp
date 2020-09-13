// Fill out your copyright notice in the Description page of Project Settings.

#include "Medicine.h"


// Sets default values
AMedicine::AMedicine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DrinkMesh(TEXT("StaticMesh'/Game/Model/Medicine/Medicine.Medicine'"));

	mDrink = NewObject<UStaticMeshComponent>(this, TEXT("Medicine"));
	RootComponent = mDrink;
	mDrink->SetStaticMesh(DrinkMesh.Object);
	mDrink->RelativeScale3D = FVector(1, 1, 1);
	mDrink->SetCollisionProfileName("OverlapOnlyPawn");
	mDrink->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AMedicine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMedicine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AMedicine::GetItemName()
{
	return "Medicine";
}

void AMedicine::PickUp()
{
	if (!Player->InvenMap.Find("Medicine"))
	{
		Player->InvenMap.Add("Medicine", 1);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("Medicine");
	*count += 1;
	Player->InvenMap.Add("Medicine", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, -1000));
}

void AMedicine::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int AMedicine::GetItemCount()
{
	return 1;
}

void AMedicine::SetItemCount(int g_count)
{
}

int AMedicine::GetCheckItem()
{
	return 0;
}

void AMedicine::UseItem()
{
	Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->AddEnergy(60);
}

