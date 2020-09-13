// Fill out your copyright notice in the Description page of Project Settings.

#include "M16C.h"
#include "Engine.h"

M16C::M16C()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M16/M16_Box002.M16_Box002'"));
	mWeaponMesh = lWeaponMesh.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> lDefaultScope(TEXT("StaticMesh'/Game/Model/M16/M16_Object001.M16_Object001'"));
	mDefaultScope = lDefaultScope.Object;

	BulletSpeed->Init(90000);
	//BulletSpeed->SetDamage(41);
	//BulletSpeed->Init(0);

	static ConstructorHelpers::FObjectFinder<UClass> Bullet(TEXT("Class'/Script/PUBG.mm556'"));
	mBullet = Bullet.Object;

	BulletStart = FVector(0.004131, -44.614067, 4.208681);

	iBulletCount = 0;
	iMaxBulletCount = 30;
}

M16C::~M16C()
{
}

void M16C::Init()
{
}

void M16C::DeclineBullet()
{
	iBulletCount -= 1;
}

void M16C::AddBullet(int g_BulletCount)
{
	iBulletCount += g_BulletCount;
}

UClass * M16C::GetBullet()
{
	return mBullet;
}

UStaticMesh * M16C::GetStaticMesh()
{
	return mWeaponMesh;
}

FVector M16C::GetBulletStart()
{
	return BulletStart;
}

FVector M16C::GetGunLocation()
{
	return FVector(-27.133472, 0.627750, 6.406910);
}

FVector M16C::GetZooomCameraLocation()
{
	return FVector(-0.29, 36, 11);
}

int M16C::GetBulletCount()
{
	return iBulletCount;
}

int M16C::GetReloadBulletCount()
{
	return iMaxBulletCount - iBulletCount;
}

bool M16C::GetCanReload()
{
	if (iBulletCount < iMaxBulletCount)
	{
		return true;
	}
	return false;
}

FString M16C::GetBulletName()
{
	return "5.56mm";
}

void M16C::SetHoloGram(bool g_holo)
{
	HoloGram = g_holo;
}

bool M16C::GetHoloGram()
{
	return HoloGram;
}

FString M16C::GetGunName()
{
	return "M16";
}

FVector M16C::GetHologramLocation()
{
	return FVector(-0.22, 18.781569, 7.5);
}

float M16C::GetTimeBetweenShoot()
{
	return 0.075f;
}

void M16C::ChangeShootMode()
{
	if (iShootMode == 0)
	{
		iShootMode = 1;
		return;
	}
	iShootMode = 0;
}

int M16C::GetShootMode()
{
	return iShootMode;
}

UStaticMesh * M16C::GetScopeMesh()
{
	return mDefaultScope;
}

float M16C::GetDamage()
{
	return 41.0f;
}
