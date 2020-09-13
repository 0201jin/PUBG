// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Vehicle.h"
#include "MyCharacter.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UAZ.generated.h"

UCLASS()
class PUBG_API AUAZ : public AVehicle
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* mVehicle;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UFloatingPawnMovement* mMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UBoxComponent* Box;

public:
	// Sets default values for this pawn's properties
	AUAZ();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AMyCharacter* mMyCharacter;

	FRotator RotVector;

	float fSpeed = 0;
	float fFBvalue = 0;
	bool bCharRide;
	float fGetOutTime = 100;
	bool bBrake;
	float fBooster = 0;
	bool bCanMove;

	float fCanGetOut;

	void FB_Move(float value);
	void LR_Move(float value);

	void Yaw(float value);
	void Pitch(float value);

	void Inven();

	void GetOut();
	void Brake(float value);

	void Booster();
	void BoosterRelease();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetCharacter(AMyCharacter* g_MyCharacter);
};
