// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Gun.h"
#include "Engine.h"

#include "CoreMinimal.h"

/**
 * 
 */
class PUBG_API Punch : public Gun
{
public:
	Punch();
	~Punch();

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

protected:
	bool HoloGram;
};
