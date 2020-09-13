// Fill out your copyright notice in the Description page of Project Settings.

#include "mm762.h"
#include "CharacterMgr.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"

float BulletSpeed762 = 0;

// Sets default values
Amm762::Amm762()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> BloodParticle(TEXT("ParticleSystem'/Game/Effect/Particle/BloodEffect.BloodEffect'"));
	BloodFx = BloodParticle.Object;

	static ConstructorHelpers::FObjectFinder<UClass> EffectTexture(TEXT("Class'/Script/PUBG.BulletHole'"));
	Effect = EffectTexture.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M24/mm762.mm762'"));
	mBulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	RootComponent = mBulletMesh;
	mBulletMesh->SetStaticMesh(lWeaponMesh.Object);
	mBulletMesh->SetSimulatePhysics(true);
	//mBulletMesh->SetMassOverrideInKg(NAME_All, 0.008f, true);
	mBulletMesh->SetCollisionProfileName("BlockAll");

	BulletMovement->UpdatedComponent = RootComponent;
	BulletMovement->MaxSpeed = 0.f;
	BulletMovement->InitialSpeed = BulletSpeed762;
	BulletMovement->bRotationFollowsVelocity = false;
	BulletMovement->bShouldBounce = true;
	BulletMovement->Bounciness = 0.0001f;
	BulletMovement->Velocity = FVector(0.0f, 0.0f, 1.0f);

	LifeTime = 0;
}

void Amm762::Init(float Speed)
{
	BulletSpeed762 = Speed;
}

// Called when the game starts or when spawned
void Amm762::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	BulletMovement->InitialSpeed = 0;
}

// Called every frame
void Amm762::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime += DeltaTime;
	FHitResult Hit;
	FCollisionQueryParams Collision;
	Collision.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, GetActorLocation(), ECollisionChannel::ECC_WorldDynamic, Collision))
	{
		ACharacterMgr* ch = Cast<ACharacterMgr>(Hit.GetActor());
		if (ch)
		{
			ch->Damage(fDamage);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodFx, FTransform(UKismetMathLibrary::FindLookAtRotation(Hit.ImpactPoint + Hit.ImpactNormal, Hit.ImpactPoint), Hit.ImpactPoint, FVector(1, 1, 1)), true);
			GetWorld()->SpawnActor<AActor>(Effect, FTransform(UKismetMathLibrary::FindLookAtRotation(Hit.ImpactPoint + Hit.ImpactNormal, Hit.ImpactPoint), Hit.ImpactPoint, FVector(1, 1, 1)))->AttachToActor(ch, FAttachmentTransformRules::KeepRelativeTransform);
			Destroy();
			return;
		}
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, FTransform(UKismetMathLibrary::FindLookAtRotation(Hit.ImpactPoint + Hit.ImpactNormal, Hit.ImpactPoint), Hit.ImpactPoint, FVector(1, 1, 1)), true);
		GetWorld()->SpawnActor<AActor>(Effect, FTransform(UKismetMathLibrary::FindLookAtRotation(Hit.ImpactPoint + Hit.ImpactNormal, Hit.ImpactPoint), Hit.ImpactPoint, FVector(1, 1, 1)));
		Destroy();
	}

	else if (LifeTime >= 6)
	{
		Destroy();
	}

	StartLocation = GetActorLocation();
}

float Amm762::GetDamage()
{
	return fDamage;
}

void Amm762::SetDamage(float g_damage)
{
	fDamage = g_damage;
}

