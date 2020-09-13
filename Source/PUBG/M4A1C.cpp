// Fill out your copyright notice in the Description page of Project Settings.

#include "M4A1C.h"
#include "Engine.h"

M4A1C::M4A1C()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M4A1/Mesh/M4A1_pCube1.M4A1_pCube1'"));
	mWeaponMesh = lWeaponMesh.Object;

	BulletSpeed->Init(88000);
	//BulletSpeed->SetDamage(41);
	//BulletSpeed->Init(0);

	static ConstructorHelpers::FObjectFinder<UClass> Bullet(TEXT("Class'/Script/PUBG.mm556'"));
	mBullet = Bullet.Object;

	BulletStart = FVector(-2.755502, -49, 11.449567);

	iBulletCount = 0;
	iMaxBulletCount = 30;
}

M4A1C::~M4A1C()
{
}

void M4A1C::Init()
{
	
}

void M4A1C::DeclineBullet()
{
	iBulletCount -= 1;
}

void M4A1C::AddBullet(int g_BulletCount)
{
	iBulletCount += g_BulletCount;
}

UClass * M4A1C::GetBullet()
{
	return mBullet;
}

UStaticMesh * M4A1C::GetStaticMesh()
{
	return mWeaponMesh;
}

FVector M4A1C::GetBulletStart()
{
	return BulletStart;
}

FVector M4A1C::GetGunLocation()
{
	return FVector(-25.0f, 0.0f, 0.0f);
}

FVector M4A1C::GetZooomCameraLocation()
{
	return FVector(-2.74696, 35, 18);
}

int M4A1C::GetBulletCount()
{
	return iBulletCount;
}

int M4A1C::GetReloadBulletCount()
{
	return iMaxBulletCount - iBulletCount;
}

bool M4A1C::GetCanReload()
{
	if (iBulletCount < iMaxBulletCount)
	{
		return true;
	}
	return false;
}

FString M4A1C::GetBulletName()
{
	return "5.56mm";
}

void M4A1C::SetHoloGram(bool g_holo)
{
	HoloGram = g_holo;
}

bool M4A1C::GetHoloGram()
{
	return HoloGram;
}

FString M4A1C::GetGunName()
{
	return "M4A1";
}

FVector M4A1C::GetHologramLocation()
{
	return FVector(-2.775, 16, 14.5);
}

float M4A1C::GetTimeBetweenShoot()
{
	return 0.086f;
}

void M4A1C::ChangeShootMode()
{
	if (iShootMode == 0)
	{
		iShootMode = 2;
		return;
	}
	iShootMode = 0;
}

int M4A1C::GetShootMode()
{
	return iShootMode;
}

float M4A1C::GetDamage()
{
	return 41.0f;
}

