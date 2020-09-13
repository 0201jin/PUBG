// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GunMgr.h"
#include "mm556.h"
#include "CrossHair.h"
#include "Item.h"
#include "Engine/Canvas.h"
#include "Engine.h"
#include "StructHeader.h"
#include "Bullet/BulletMgr.h"
#include "CharacterMgr.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateFree, const bool, KeyDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateJump, const bool, KeyDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateProne, const bool, KeyDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateCrouch, const bool, KeyDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateZoom, const bool, KeyDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateReload, const bool, KeyDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateHoldBreath, const bool, KeyDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEnergy, float, Engergy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateGun, const bool, HaveGun);

UCLASS()
class PUBG_API AMyCharacter : public ACharacterMgr
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UGunMgr* mWeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* Sight;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* SkeletonMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* BulletStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* ZoomCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly, Category = Effect)
		class UParticleSystem* ShootFireFx;

public:
	// Sets default values for this character's properties
	AMyCharacter();

	void SetHologram(bool g_holo, int g_num);

	void SetGun(AItem * g_gun, int g_num);

	void AddEnergy(float g_energy);

	void ResetCanRide();

	void Inven();

	bool GetDoubleZoom();

	bool GetHoldBreath();

	float GetHoldBreathTime();

	float GetEnergy();

	int GetShootMode();

	bool bPickUp = false;

	TMap<FString, int> InvenMap;

	TMap<FString, AItem*> ItemMap;

	TMap<FString, UTexture2D*> TmIcons;

	TArray<AItem*> FarmingList;

	AItem* GunArray[2];

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMesh* SHoloGram;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	APlayerController* PlayerController;

	ACrossHair* hud;

	float run = 1;
	float memrun = 1;
	float runDelay = 1;
	bool FreeCheck = true;
	bool ProneCheck = false;
	bool CrouchCheck = false;
	bool MoveBlock = false;
	bool ZoomCheck = false;
	bool DoubleZoom = false;
	float time = 0;
	FRotator CRotation;
	float ZoomTime = 1;
	float HoldBreathTime = 3;
	bool HoldingBreath = false;
	bool CanHoldBreath = true;
	bool IsInvenDraw = false;
	bool bReload = false;
	float TimeBetweenShoot = 0;
	float fEnergy = 0;
	bool bBurst = false;
	int iBurstCount = 0;
	float fShootTime = 0;
	bool bGetGun = false;
	float fCanRide;

	int iSelectGun = 0;
	int EnergyRun = 1;

	void FB_Move(float value);
	void LR_Move(float value);
	void ShootAuto(float value);

	void Shoot();
	void Squat();
	void Prone();
	void Zoom();
	void ZoomRelease();
	void Run();
	void RunRelease();
	void Free();
	void FreeRelease();
	void Jump();
	void JumpRelease();
	void ShootRelease();
	void Reload();
	void BeginPickUp();
	void EndPickUp();
	void Yaw(float value);
	void Pitch(float value);
	void Clickced();
	void ChangeShootMode();
	
	void SetSelectGun1();
	void SetSelectGun2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* ShootAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* ProneShootAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* ReloadAnimation;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateJump JumpUpdate;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateProne ProneUpdate;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateCrouch CrouchUpdate;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateZoom ZoomUpdate;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateReload ReloadUpdate;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateFree FreeUpdate;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateHoldBreath HoldBreath;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateEnergy EnergyUpdate;

	UPROPERTY(BluePrintAssignable, Category = "MyCharacter")
		FUpdateGun GunUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		TSubclassOf<class AActor> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	int GetBulletCount();

	int GetInvenBulletCount();

	void Damage(float g_Damage);
};
