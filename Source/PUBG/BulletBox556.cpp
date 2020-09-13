// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletBox556.h"
#include "Engine.h"

// Sets default values
ABulletBox556::ABulletBox556()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletBoxMesh(TEXT("StaticMesh'/Game/Model/BulletBox/BulletBox556.BulletBox556'"));
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> BulletBoxMat(TEXT("Material'/Game/Model/BulletBox/Mmm556.Mmm556'"));

	mBulletBox = NewObject<UStaticMeshComponent>(this, TEXT("BulletBox"));
	RootComponent = mBulletBox;
	mBulletBox->SetStaticMesh(BulletBoxMesh.Object);
	//mBulletBox->SetMaterial(0, BulletBoxMat.Object);
	mBulletBox->RelativeScale3D = FVector(2, 2, 2);
	mBulletBox->SetCollisionProfileName("OverlapOnlyPawn");
	mBulletBox->bGenerateOverlapEvents = true;
	mBulletBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletBox556::BeginOverlap);
	mBulletBox->OnComponentEndOverlap.AddDynamic(this, &ABulletBox556::EndOverlap);
	iCount = 30;
}

// Called when the game starts or when spawned
void ABulletBox556::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABulletBox556::SetPlayer(AActor * g_Player)
{
	Player = Cast<AMyCharacter>(g_Player);
}

int ABulletBox556::GetItemCount()
{
	return iCount;
}

void ABulletBox556::SetItemCount(int g_count)
{
	iCount = g_count;
}

int ABulletBox556::GetCheckItem()
{
	return 0;
}

void ABulletBox556::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SetPlayer(OtherActor);
	bOverlap = true;
}

void ABulletBox556::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bOverlap = false;
}

void ABulletBox556::PickUp()
{
	if (!Player->InvenMap.Find("5.56mm"))
	{
		Player->InvenMap.Add("5.56mm", iCount);
		SetActorHiddenInGame(true);
		SetActorLocation(FVector(0, 0, -1000));
		return;
	}
	int* count = (int*)Player->InvenMap.Find("5.56mm");
	*count += iCount;
	Player->InvenMap.Add("5.56mm", *count);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, -1000));
}

// Called every frame
void ABulletBox556::Tick(float DeltaTime)
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

FString ABulletBox556::GetItemName()
{
	return "5.56mm";
}

