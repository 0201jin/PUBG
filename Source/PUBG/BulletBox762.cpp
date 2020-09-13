// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletBox762.h"
#include "Engine.h"

// Sets default values
ABulletBox762::ABulletBox762()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletBoxMesh(TEXT("StaticMesh'/Game/Model/BulletBox/BulletBox762.BulletBox762'"));
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> BulletBoxMat(TEXT("Material'/Game/Model/BulletBox/Mmm762.Mmm762'"));

	mBulletBox = NewObject<UStaticMeshComponent>(this, TEXT("BulletBox"));
	RootComponent = mBulletBox;
	mBulletBox->SetStaticMesh(BulletBoxMesh.Object);
	//mBulletBox->SetMaterial(0, BulletBoxMat.Object);
	mBulletBox->RelativeScale3D = FVector(2, 2, 2);
	mBulletBox->SetCollisionProfileName("OverlapOnlyPawn");
	mBulletBox->bGenerateOverlapEvents = true;
	mBulletBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletBox762::BeginOverlap);
	mBulletBox->OnComponentEndOverlap.AddDynamic(this, &ABulletBox762::EndOverlap);
	iCount = 30;
}

// Called when the game starts or when spawned
void ABulletBox762::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABulletBox762::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int ABulletBox762::GetItemCount()
{
	return iCount;
}

void ABulletBox762::SetItemCount(int g_count)
{
	iCount = g_count;
}

int ABulletBox762::GetCheckItem()
{
	return 0;
}

void ABulletBox762::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SetPlayer(OtherActor);
	bOverlap = true;
}

void ABulletBox762::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bOverlap = false;
}

void ABulletBox762::PickUp()
{
	if (!Player->InvenMap.Find("7.62mm"))
	{
		Player->InvenMap.Add("7.62mm", iCount);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("7.62mm");
	*count += iCount;
	Player->InvenMap.Add("7.62mm", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, -1000));
}

// Called every frame
void ABulletBox762::Tick(float DeltaTime)
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

FString ABulletBox762::GetItemName()
{
	return "7.62mm";
}

