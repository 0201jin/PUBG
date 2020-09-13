// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PUBG_API Gun
{
public:
	Gun();
	~Gun();

	virtual void Init();
	virtual UStaticMesh* GetStaticMesh();
	virtual UClass* GetBullet();
	virtual FVector GetBulletStart();
	virtual FVector GetGunLocation();
	virtual FVector GetZooomCameraLocation();
	virtual void DeclineBullet();
	virtual void AddBullet(int g_BulletCount);
	virtual int GetBulletCount();
	virtual int GetReloadBulletCount();
	virtual bool GetCanReload();
	virtual FString GetBulletName();
	virtual void SetHoloGram(bool g_holo);
	virtual bool GetHoloGram();
	virtual FString GetGunName();
	virtual FVector GetHologramLocation();
	virtual float GetTimeBetweenShoot();
	virtual void ChangeShootMode();
	virtual int GetShootMode();
	virtual UStaticMesh* GetScopeMesh();
	virtual float GetDamage();
};
