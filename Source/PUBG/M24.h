// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MyCharacter.h"
#include "Item.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M24.generated.h"

UCLASS()
class PUBG_API AM24 : public AItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* mWeaponMesh;
	
public:	
	// Sets default values for this actor's properties
	AM24();

protected:
	AMyCharacter* Player;
	bool bOverlap = false;
	bool bHoloGram = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

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

	Gun* GetGun();
};
