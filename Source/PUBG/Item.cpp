// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"


// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

FString AItem::GetItemName()
{
	return "";
}

void AItem::PickUp()
{
}

void AItem::SetPlayer(AActor* g_Player)
{
}

int AItem::GetItemCount()
{
	return 0;
}

void AItem::SetItemCount(int g_count)
{
}

int AItem::GetCheckItem()
{
	return 0;
}

void AItem::SetHoloGram(bool g_holo)
{
}

bool AItem::GetHoloGram()
{
	return false;
}

void AItem::UseItem()
{
}
