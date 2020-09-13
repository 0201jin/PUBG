// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CharacterMgr.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Target.generated.h"

UCLASS()
class PUBG_API ATarget : public ACharacterMgr
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* SkeletonMesh;

	
	
public:	
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* DeathAnimation;

	float Health = 100;

	bool bDeath = false;
	float fDeathTime = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Damage(float g_Damage);

	void Death();

	
	
};
