// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Bullet/BulletMgr.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "mm762.generated.h"

UCLASS()
class PUBG_API Amm762 : public ABulletMgr
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UProjectileMovementComponent* BulletMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* mBulletMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Effect)
		class UParticleSystem* BloodFx;
	
public:	
	// Sets default values for this actor's properties
	Amm762();
	void Init(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		TSubclassOf<class AActor> Effect;

	FVector StartLocation;

	float LifeTime;

	float fDamage = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetDamage();

	void SetDamage(float g_damage);
	
};
