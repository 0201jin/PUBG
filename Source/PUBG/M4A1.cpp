// Fill out your copyright notice in the Description page of Project Settings.

#include "M4A1.h"
#include "Engine.h"


// Sets default values
AM4A1::AM4A1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M4A1/Mesh/M4A1_pCube1.M4A1_pCube1'"));
	mWeaponMesh = NewObject<UStaticMeshComponent>(this, TEXT("CharacterWeaponMesh"));
	RootComponent = mWeaponMesh;
	mWeaponMesh->SetStaticMesh(lWeaponMesh.Object);
	mWeaponMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, -10.0f));
	mWeaponMesh->RelativeLocation = FVector(0.0f, 0.0f, 5.5f);
	mWeaponMesh->SetCollisionProfileName("OverlapOnlyPawn");
	mWeaponMesh->bGenerateOverlapEvents = true;
	mWeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AM4A1::BeginOverlap);
	mWeaponMesh->OnComponentEndOverlap.AddDynamic(this, &AM4A1::EndOverlap);
}

// Called when the game starts or when spawned
void AM4A1::BeginPlay()
{
	Super::BeginPlay();
	
}

void AM4A1::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int AM4A1::GetItemCount()
{
	return 1;
}

void AM4A1::SetItemCount(int g_count)
{
}

int AM4A1::GetCheckItem()
{
	return 1;
}

void AM4A1::SetHoloGram(bool g_holo)
{
	bHoloGram = g_holo;
}

bool AM4A1::GetHoloGram()
{
	return bHoloGram;
}

void AM4A1::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetPlayer(OtherActor);
	bOverlap = true;
}

void AM4A1::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bOverlap = false;
}

void AM4A1::PickUp()
{
	if (!Player->InvenMap.Find("M4A1"))
	{
		Player->InvenMap.Add("M4A1", 1);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("M4A1");
	*count += 1;
	Player->InvenMap.Add("M4A1", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, -1000));
}

// Called every frame
void AM4A1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (Player != NULL)
	{
		if (Player->bPickUp && bOverlap)
		{
			PickUp();
		}
	}*/
}

FString AM4A1::GetItemName()
{
	return "M4A1";
}

