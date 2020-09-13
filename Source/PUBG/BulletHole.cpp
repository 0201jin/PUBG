// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletHole.h"
#include "Engine.h"


// Sets default values
ABulletHole::ABulletHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> lPlane(TEXT("StaticMesh'/Game/Model/Plane.Plane'"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> lMaterial(TEXT("Material'/Game/Effect/MAterial/BulletHoleMat.BulletHoleMat'"));
	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	RootComponent = Plane;
	Plane->SetStaticMesh(lPlane.Object);
	//Plane->SetMaterial(0, lMaterial.Object);
	Plane->SetCollisionProfileName("NoCollision");
	Plane->RelativeRotation = FRotator(0, 90, 90);
	Plane->RelativeScale3D = FVector(0.1, 0.1, 0.1);

	time = 0;
}

// Called when the game starts or when spawned
void ABulletHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (time > 5)
	{
		Destroy();
	}
	time += DeltaTime;
}

