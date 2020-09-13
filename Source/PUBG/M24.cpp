// Fill out your copyright notice in the Description page of Project Settings.

#include "M24.h"
#include "Engine.h"


// Sets default values
AM24::AM24()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M24/M24.M24'"));
	mWeaponMesh = NewObject<UStaticMeshComponent>(this, TEXT("CharacterWeaponMesh"));
	RootComponent = mWeaponMesh;
	mWeaponMesh->SetStaticMesh(lWeaponMesh.Object);
	mWeaponMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, -10.0f));
	mWeaponMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 3.0f));
	mWeaponMesh->SetCollisionProfileName("OverlapOnlyPawn");
	mWeaponMesh->bGenerateOverlapEvents = true;
	mWeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AM24::BeginOverlap);
	mWeaponMesh->OnComponentEndOverlap.AddDynamic(this, &AM24::EndOverlap);
}

// Called when the game starts or when spawned
void AM24::BeginPlay()
{
	Super::BeginPlay();
	
}

void AM24::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int AM24::GetItemCount()
{
	return 1;
}

void AM24::SetItemCount(int g_count)
{
}

int AM24::GetCheckItem()
{
	return 1;
}

void AM24::SetHoloGram(bool g_holo)
{
	bHoloGram = g_holo;
}

bool AM24::GetHoloGram()
{
	return bHoloGram;
}

void AM24::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SetPlayer(OtherActor);
	bOverlap = true;
}

void AM24::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bOverlap = false;
}

void AM24::PickUp()
{
	if (!Player->InvenMap.Find("M24"))
	{
		Player->InvenMap.Add("M24", 1);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("M24");
	*count += 1;
	Player->InvenMap.Add("M24", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, -1000));
}

// Called every frame
void AM24::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Player != NULL)
	//{
	//	if (Player->bPickUp && bOverlap)
	//	{
	//		PickUp();
	//	}
	//}
}

FString AM24::GetItemName()
{
	return "M24";
}

