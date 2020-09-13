// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Gun.h"

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GunMgr.generated.h"

/**
 * 
 */
class Gun;
UCLASS()
class PUBG_API UGunMgr : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* mWeaponMesh;

public:
	UGunMgr();

	UStaticMesh* GetStaticMesh();

	UClass* GetBullet();

	FVector GetBulletStart();

	FVector GetGunLocation();

	FVector GetZooomCameraLocation();

	FVector GetHologramLocation();

	void SetGun(FString g_gun);

	void DeclineBullet();

	void AddBullet(int g_BulletCount);

	int GetBulletCount();

	int GetReloadBulletCount();

	bool GetCanReload();

	FString GetBulletName();

	void SetHoloGram(bool g_holo);

	bool GetHoloGram();

	float GetTimeBetweenShoot();

	void ChangeShootMode();

	int GetShootMode();

	UStaticMesh* GetScopeMesh();

	float GetDamage();

protected:
	Gun* gun;
	Gun* gunlist[4];
};
