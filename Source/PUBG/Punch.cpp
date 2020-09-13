// Fill out your copyright notice in the Description page of Project Settings.

#include "Punch.h"

Punch::Punch()
{
}

Punch::~Punch()
{
}

void Punch::Init()
{
}

void Punch::DeclineBullet()
{
}

void Punch::AddBullet(int g_BulletCount)
{
}

UClass * Punch::GetBullet()
{
	return nullptr;
}

UStaticMesh * Punch::GetStaticMesh()
{
	return nullptr;
}

FVector Punch::GetBulletStart()
{
	return FVector();
}

FVector Punch::GetGunLocation()
{
	return FVector();
}

FVector Punch::GetZooomCameraLocation()
{
	return FVector();
}

int Punch::GetBulletCount()
{
	return 0;
}

int Punch::GetReloadBulletCount()
{
	return 0;
}

bool Punch::GetCanReload()
{
	return false;
}

FString Punch::GetBulletName()
{
	return FString();
}

void Punch::SetHoloGram(bool g_holo)
{
}

bool Punch::GetHoloGram()
{
	return false;
}

FString Punch::GetGunName()
{
	return "UNKNOWN ICON";
}
