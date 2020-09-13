// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class PUBG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	virtual FString GetItemName();
	virtual void PickUp();
	virtual void SetPlayer(AActor* g_Player);
	virtual int GetItemCount();
	virtual void SetItemCount(int g_count);
	virtual int GetCheckItem();
	virtual void SetHoloGram(bool g_holo);
	virtual bool GetHoloGram();
	virtual void UseItem();
};
