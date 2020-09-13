// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MyCharacter.h"
#include "Item.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M16.generated.h"

UCLASS()
class PUBG_API AM16 : public AItem
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* mWeaponMesh;
	
public:	
	// Sets default values for this actor's properties
	AM16();

protected:
	AMyCharacter* Player;
	bool bOverlap = false;
	bool bHoloGram = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString GetItemName();
	void PickUp();
	void SetPlayer(AActor* g_Player);
	int GetItemCount();
	void SetItemCount(int g_count);
	int GetCheckItem();

	void SetHoloGram(bool g_holo);
	bool GetHoloGram();
	
};
