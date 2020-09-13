// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Gun.h"
#include "mm762.h"

#include "CoreMinimal.h"

/**
 * 
 */
struct Parts
{
	
};

class PUBG_API M24C : public Gun
{
protected:
	UStaticMesh* mWeaponMesh;
	UClass* mBullet;
	FVector BulletStart;
	Amm762* BulletSpeed;
	int iBulletCount;
	int iMaxBulletCount;
	bool HoloGram;
	int iShootMode = 0;

public:
	M24C();
	~M24C();

	void Init();
	void DeclineBullet();
	void AddBullet(int g_BulletCount);
	UClass* GetBullet();
	UStaticMesh* GetStaticMesh();
	FVector GetBulletStart();
	FVector GetGunLocation();
	FVector GetZooomCameraLocation();
	int GetBulletCount();
	int GetReloadBulletCount();
	bool GetCanReload();
	FString GetBulletName();
	void SetHoloGram(bool g_holo);
	bool GetHoloGram();
	FString GetGunName();
	FVector GetHologramLocation();
	float GetTimeBetweenShoot();
	void ChangeShootMode();
	int GetShootMode();
	float GetDamage();
};
