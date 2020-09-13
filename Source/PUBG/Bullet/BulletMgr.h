// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletMgr.generated.h"

UCLASS()
class PUBG_API ABulletMgr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletMgr();

	virtual float GetDamage();
	virtual void SetDamage(float g_damage);
};
