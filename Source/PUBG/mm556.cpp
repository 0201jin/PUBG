// Fill out your copyright notice in the Description page of Project Settings.

#include "mm556.h"
#include "Engine.h"
#include "CharacterMgr.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
float BulletSpeed = 0;

Amm556::Amm556()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> BloodParticle(TEXT("ParticleSystem'/Game/Effect/Particle/BloodEffect.BloodEffect'"));
	BloodFx = BloodParticle.Object;

	static ConstructorHelpers::FObjectFinder<UClass> EffectTexture(TEXT("Class'/Script/PUBG.BulletHole'"));
	Effect = EffectTexture.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M4A1/Mesh/mm556.mm556'"));
	mBulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	RootComponent = mBulletMesh;
	mBulletMesh->SetStaticMesh(lWeaponMesh.Object);
	mBulletMesh->SetSimulatePhysics(true);
	//mBulletMesh->SetMassOverrideInKg(NAME_All, 0.004f, true);
	mBulletMesh->SetCollisionProfileName("BlockAll");

	BulletMovement->UpdatedComponent = RootComponent;
	BulletMovement->MaxSpeed = 0.f;
	BulletMovement->InitialSpeed = BulletSpeed;
	BulletMovement->bRotationFollowsVelocity = false;
	BulletMovement->bShouldBounce = true;
	BulletMovement->Bounciness = 0.0001f;
	BulletMovement->Velocity = FVector(0.0f, 0.0f, 1.0f);

	LifeTime = 0;
}

void Amm556::Init(float Speed)
{
	BulletSpeed = Speed;
}

// Called when the game starts or when spawned
void Amm556::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	BulletMovement->InitialSpeed = 0;
}

void Amm556::OnHit(UPrimitiveComponent * OtherComp, AActor * OtherActor, UPrimitiveComponent * Comp, FVector NormalImpulse, const FHitResult & Hit)
{
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, GetActorTransform(), true);
	Destroy();
}

// Called every frame
void Amm556::Tick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, FString::Printf(TEXT("%f"), mBulletMesh->GetMass()));
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

float Amm556::GetDamage()
{
	return fDamage;
}

void Amm556::SetDamage(float g_damage)
{
	fDamage = g_damage;
}

