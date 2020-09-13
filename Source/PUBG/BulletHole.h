// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletHole.generated.h"

UCLASS()
class PUBG_API ABulletHole : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* Plane;
	
public:	
	// Sets default values for this actor's properties
	ABulletHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float time;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
