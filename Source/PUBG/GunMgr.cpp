// Fill out your copyright notice in the Description page of Project Settings.

#include "GunMgr.h"
#include "Engine.h"
#include "M4A1C.h"
#include "M24C.h"
#include "Punch.h"
#include "M16C.h"

UGunMgr::UGunMgr()
{
	gunlist[0] = new M24C;
	gunlist[1] = new M4A1C;
	gunlist[2] = new Punch;
	gunlist[3] = new M16C;

	gun = gunlist[2];
}

UStaticMesh * UGunMgr::GetStaticMesh()
{
	return gun->GetStaticMesh();
}

UClass * UGunMgr::GetBullet()
{
	return gun->GetBullet();
}

FVector UGunMgr::GetBulletStart()
{
	return gun->GetBulletStart();
}

FVector UGunMgr::GetGunLocation()
{
	return gun->GetGunLocation();
}

FVector UGunMgr::GetZooomCameraLocation()
{
	return gun->GetZooomCameraLocation();
}

FVector UGunMgr::GetHologramLocation()
{
	return gun->GetHologramLocation();
}

void UGunMgr::SetGun(FString g_gun)
{
	for (int a = 0; a < 4; a++)
	{
		if (g_gun == gunlist[a]->GetGunName())
		{
			gun = gunlist[a];
		}
	}
}

void UGunMgr::DeclineBullet()
{
	gun->DeclineBullet();
}

void UGunMgr::AddBullet(int g_BulletCount)
{
	gun->AddBullet(g_BulletCount);
}

int UGunMgr::GetBulletCount()
{
	return gun->GetBulletCount();
}

int UGunMgr::GetReloadBulletCount()
{
	return gun->GetReloadBulletCount();
}

bool UGunMgr::GetCanReload()
{
	return gun->GetCanReload();
}

FString UGunMgr::GetBulletName()
{
	return gun->GetBulletName();
}

bool UGunMgr::GetHoloGram()
{
	return gun->GetHoloGram();
}

float UGunMgr::GetTimeBetweenShoot()
{
	return gun->GetTimeBetweenShoot();
}

void UGunMgr::ChangeShootMode()
{
	gun->ChangeShootMode();
}

int UGunMgr::GetShootMode()
{
	return gun->GetShootMode();
}

UStaticMesh * UGunMgr::GetScopeMesh()
{
	return gun->GetScopeMesh();;
}

float UGunMgr::GetDamage()
{
	return gun->GetDamage();
}

void UGunMgr::SetHoloGram(bool g_holo)
{
	return gun->SetHoloGram(g_holo);
}
