// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Init()
{
}

UStaticMesh * Gun::GetStaticMesh()
{
	return nullptr;
}

UClass * Gun::GetBullet()
{
	return nullptr;
}

FVector Gun::GetBulletStart()
{
	return FVector(0,0,0);
}

FVector Gun::GetGunLocation()
{
	return FVector();
}

FVector Gun::GetZooomCameraLocation()
{
	return FVector();
}

void Gun::DeclineBullet()
{
}

void Gun::AddBullet(int g_BulletCount)
{
}

int Gun::GetBulletCount()
{
	return 0;
}

int Gun::GetReloadBulletCount()
{
	return 0;
}

bool Gun::GetCanReload()
{
	return false;
}

FString Gun::GetBulletName()
{
	return FString();
}

void Gun::SetHoloGram(bool g_holo)
{
}

bool Gun::GetHoloGram()
{
	return false;
}

FString Gun::GetGunName()
{
	return FString();
}

FVector Gun::GetHologramLocation()
{
	return FVector();
}

float Gun::GetTimeBetweenShoot()
{
	return 0.0f;
}

void Gun::ChangeShootMode()
{
}

int Gun::GetShootMode()
{
	return 100;
}

UStaticMesh * Gun::GetScopeMesh()
{
	return nullptr;
}

float Gun::GetDamage()
{
	return 0.0f;
}
