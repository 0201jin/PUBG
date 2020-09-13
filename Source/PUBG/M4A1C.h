// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "mm556.h"
#include "Gun.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PUBG_API M4A1C : public Gun
{
protected:
	UStaticMesh* mWeaponMesh;
	UClass* mBullet;
	FVector BulletStart;
	Amm556* BulletSpeed;
	bool HoloGram;

	int iBulletCount;
	int iMaxBulletCount;
	int iShootMode = 0;

public:
	M4A1C();
	~M4A1C();

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
