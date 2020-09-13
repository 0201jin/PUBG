// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"
#include "Engine.h"
#include "Bullet/BulletMgr.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonMesh"));
	SkeletonMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Skeleton(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimClass(TEXT("/Game/AnimStarterPack/Anim.Anim_C"));
	SkeletonMesh->SetSkeletalMesh(Skeleton.Object);
	SkeletonMesh->bCastDynamicShadow = false;
	SkeletonMesh->bGenerateOverlapEvents = true;
	SkeletonMesh->CastShadow = true;
	SkeletonMesh->RelativeRotation = FRotator(0.0f, 270.0f, 0.0f);
	SkeletonMesh->RelativeLocation = FVector(0.0f, 0.0f, -97.0f);
	SkeletonMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SkeletonMesh->AnimClass = AnimClass.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathAnim(TEXT("AnimMontage'/Game/AnimStarterPack/Death_1_Montage.Death_1_Montage'"));
	DeathAnimation = DeathAnim.Object;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	fDeathTime += DeltaTime;

	/*AddMovementInput(GetActorForwardVector(), 0.5 * FMath::FRandRange(0, 1));
	AddActorLocalRotation(FRotator(0, FMath::FRandRange(-10, 10), 0));*/

	if (bDeath && fDeathTime > 1.5)
	{
		Destroy();
	}
}

void ATarget::Damage(float g_Damage)
{
	Health -= g_Damage;

	if (Health <= 0 && !bDeath)
	{
		Death();
		bDeath = true;
	}
}

void ATarget::Death()
{
	UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
	Animation->Montage_Play(DeathAnimation, 1.0f);
	fDeathTime = 0;
}

