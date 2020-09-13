// Fill out your copyright notice in the Description page of Project Settings.

#include "M24C.h"
#include "Engine.h"

M24C::M24C()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> lWeaponMesh(TEXT("StaticMesh'/Game/Model/M24/M24.M24'"));
	mWeaponMesh = lWeaponMesh.Object;

	BulletSpeed->Init(79000);
	//BulletSpeed->SetDamage(84);

	static ConstructorHelpers::FObjectFinder<UClass> Bullet(TEXT("Class'/Script/PUBG.mm762'"));
	mBullet = Bullet.Object;

	BulletStart = FVector(0, -70, 7.6);

	iBulletCount = 0;
	iMaxBulletCount = 5;
}

M24C::~M24C()
{
}

void M24C::Init()
{
	
}

void M24C::DeclineBullet()
{
	iBulletCount -= 1;
}

void M24C::AddBullet(int g_BulletCount)
{
	iBulletCount += g_BulletCount;
}

UClass * M24C::GetBullet()
{
	return mBullet;
}

UStaticMesh * M24C::GetStaticMesh()
{
	return mWeaponMesh;
}

FVector M24C::GetBulletStart()
{
	return BulletStart;
}

FVector M24C::GetGunLocation()
{
	return FVector(-36.0f, 0.2f, 5.0f);
}

FVector M24C::GetZooomCameraLocation()
{
	//return FVector(0.0f, 45.1f, 11.9f);
	return FVector(0.0f, 45.1f, 11.9f);
}

int M24C::GetBulletCount()
{
	return iBulletCount;
}

int M24C::GetReloadBulletCount()
{
	return iMaxBulletCount - iBulletCount;
}

bool M24C::GetCanReload()
{
	if (iBulletCount < iMaxBulletCount)
	{
		return true;
	}
	return false;
}

FString M24C::GetBulletName()
{
	return "7.62mm";
}

void M24C::SetHoloGram(bool g_holo)
{
	HoloGram = g_holo;
}

bool M24C::GetHoloGram()
{
	return HoloGram;
}

FString M24C::GetGunName()
{
	return "M24";
}

FVector M24C::GetHologramLocation()
{
	return FVector(0, 18, 8);
}

float M24C::GetTimeBetweenShoot()
{
	return 1.8f;
}

void M24C::ChangeShootMode()
{
}

int M24C::GetShootMode()
{
	return 0;
}

float M24C::GetDamage()
{
	return 84.0f;
}

