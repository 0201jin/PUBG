// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "BulletBox556.h"
#include "BulletBox762.h"
#include "M4A1.h"
#include "M24.h"
#include "M4A1C.h"
#include "Vehicle/Vehicle.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 350.0f; //300
	GetCharacterMovement()->MaxWalkSpeed = 880.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 170.0f;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	GetCharacterMovement()->MaxSwimSpeed = 170.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonMesh"));
	SkeletonMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Skeleton(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimClass(TEXT("/Game/AnimStarterPack/Anim.Anim_C"));
	SkeletonMesh->SetSkeletalMesh(Skeleton.Object);
	SkeletonMesh->bCastDynamicShadow = false;
	SkeletonMesh->bGenerateOverlapEvents = true;
	SkeletonMesh->CastShadow = true;
	SkeletonMesh->RelativeRotation = FRotator(0.0f, 270.0f, 0.0f);
	SkeletonMesh->RelativeLocation = FVector(0.0f, 0.0f, -97.0f);
	SkeletonMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SkeletonMesh->AnimClass = AnimClass.Object;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->RelativeLocation = FVector(0.0f, 45.0f, 70.0f);

	//CameraBoom->RelativeLocation = FVector(226.041107, -28.248505, -7.421104);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ShootAnim(TEXT("AnimMontage'/Game/AnimStarterPack/Fire_Rifle_Hip_Montage.Fire_Rifle_Hip_Montage'"));
	ShootAnimation = ShootAnim.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ProneShootAnim(TEXT("AnimMontage'/Game/AnimStarterPack/Prone_Fire_1_Montage.Prone_Fire_1_Montage'"));
	ProneShootAnimation = ProneShootAnim.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ReloadAnim(TEXT("AnimMontage'/Game/AnimStarterPack/Reload_Rifle_Hip_Montage.Reload_Rifle_Hip_Montage'"));
	ReloadAnimation = ReloadAnim.Object;

	mWeaponMesh = NewObject<UGunMgr>(this, TEXT("CharacterWeaponMesh"));
	mWeaponMesh->SetStaticMesh(mWeaponMesh->GetStaticMesh());
	mWeaponMesh->AttachTo(SkeletonMesh, TEXT("Weapon"));
	mWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mWeaponMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	mWeaponMesh->SetRelativeLocation(mWeaponMesh->GetGunLocation());
	mWeaponMesh->bCastDynamicShadow = false;

	Sight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	Sight->SetupAttachment(mWeaponMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SHolo(TEXT("StaticMesh'/Game/Model/M4A1/Mesh/hologram.hologram'"));
	SHoloGram = SHolo.Object;
	//Sight->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	mWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Sight->SetStaticMesh(SHoloGram);

	ProjectileClass = mWeaponMesh->GetBullet();

	BulletStart = CreateDefaultSubobject<USceneComponent>(TEXT("BulletStart"));
	BulletStart->AttachTo(mWeaponMesh, TEXT("BulletStartL"));
	BulletStart->SetRelativeLocation(mWeaponMesh->GetBulletStart());

	ZoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));
	ZoomCamera->AttachTo(mWeaponMesh, TEXT("Zoom"));
	ZoomCamera->RelativeLocation = mWeaponMesh->GetZooomCameraLocation();
	ZoomCamera->RelativeRotation = FRotator(0, -90.0f, 0);
	ZoomCamera->FieldOfView = 80;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("TabBox"));
	Box->SetupAttachment(SkeletonMesh);
	Box->RelativeLocation = FVector(0, 0, 65);
	Box->RelativeScale3D = FVector(4.0f, 4.0f, 2);
	Box->bGenerateOverlapEvents = true;
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::BeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::EndOverlap);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ShootFireEffect(TEXT("ParticleSystem'/Game/Effect/Particle/ShootFireEffect.ShootFireEffect'"));
	ShootFireFx = ShootFireEffect.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> UTM4A1(TEXT("Texture2D'/Game/Texture/M4.M4'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> UTM24(TEXT("Texture2D'/Game/Texture/M24.M24'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> UT762(TEXT("Texture2D'/Game/Texture/762mm.762mm'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> UT556(TEXT("Texture2D'/Game/Texture/556mm.556mm'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> UTHolo(TEXT("Texture2D'/Game/Texture/HoloGramSight.HoloGramSight'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> UTHotBull(TEXT("Texture2D'/Game/Texture/HotBull.HotBull'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> UTM16(TEXT("Texture2D'/Game/Texture/M16.M16'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> UTMedicine(TEXT("Texture2D'/Game/Texture/Medicine.Medicine'"));

	TmIcons.Add("M4A1", UTM4A1.Object);
	TmIcons.Add("M24", UTM24.Object);
	TmIcons.Add("5.56mm", UT556.Object);
	TmIcons.Add("7.62mm", UT762.Object);
	TmIcons.Add("HoloGramSight", UTHolo.Object);
	TmIcons.Add("EnergyDrink", UTHotBull.Object);
	TmIcons.Add("M16", UTM16.Object);
	TmIcons.Add("Medicine", UTMedicine.Object);

	GunArray[0] = nullptr;
	GunArray[1] = nullptr;
}

bool AMyCharacter::GetDoubleZoom()
{
	return DoubleZoom;
}

bool AMyCharacter::GetHoldBreath()
{
	if (HoldBreathTime < 3)
	{
		return true;
	}
	return false;
}

float AMyCharacter::GetHoldBreathTime()
{
	return HoldBreathTime;
}

float AMyCharacter::GetEnergy()
{
	return fEnergy;
}

int AMyCharacter::GetShootMode()
{
	return mWeaponMesh->GetShootMode();
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	hud = Cast<ACrossHair>(PlayerController->GetHUD());
}

void AMyCharacter::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AItem* Item = Cast<AItem>(OtherActor);
	if (Item)
	{
		FarmingList.Add(Item);

		FString name = Item->GetItemName() + FString::Printf(TEXT(" X %d"), Item->GetItemCount());

		hud->AddFarmingItem(Widget(Icon(name, TmIcons[Item->GetItemName()])), Item);

		ItemMap.Add(Item->GetItemName(), Item);
	}
}

void AMyCharacter::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//TabFarming.Remove(OtherActor->GetName());
	AItem* Item = Cast<AItem>(OtherActor);
	if (Item)
	{
		//TabFarming.Add(OtherActor->GetName(), 1);
		//Item->RemoveItem();
		FarmingList.Remove(Item);

		hud->RemoveFarmingItem(Item);
	}
}

void AMyCharacter::FB_Move(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		const FVector FrontVector = GetActorForwardVector();

		AddMovementInput(FrontVector, value * run * EnergyRun);
	}
}

void AMyCharacter::LR_Move(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		const FVector RightVector = GetActorRightVector();

		AddMovementInput(RightVector, value * run * EnergyRun);
	}
}

void AMyCharacter::ShootAuto(float value)
{
	if (value != 0 && mWeaponMesh->GetShootMode() > 1)
	{
		if (mWeaponMesh->GetBulletCount() > 0 && !bReload && !IsInvenDraw && mWeaponMesh->GetTimeBetweenShoot() <= TimeBetweenShoot)
		{
			if (!ProneCheck)
			{
				UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
				Animation->Montage_Play(ShootAnimation, 1.0f);
				GetWorld()->SpawnActor<ABulletMgr>(ProjectileClass, BulletStart->GetComponentLocation(), mWeaponMesh->GetComponentRotation() + FRotator(0, 0, -90))->SetDamage(mWeaponMesh->GetDamage());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootFireFx, BulletStart->GetComponentLocation());
				mWeaponMesh->DeclineBullet();
				TimeBetweenShoot = 0;
				return;
			}

			UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
			Animation->Montage_Play(ShootAnimation, 1.0f);
			GetWorld()->SpawnActor<ABulletMgr>(ProjectileClass, BulletStart->GetComponentLocation(), mWeaponMesh->GetComponentRotation() + FRotator(0, 0, -90))->SetDamage(mWeaponMesh->GetDamage());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootFireFx, BulletStart->GetComponentLocation());
			mWeaponMesh->DeclineBullet();
			TimeBetweenShoot = 0;
			return;
		}
	}
}

void AMyCharacter::Squat()
{
	if (bGetGun)
	{
		if (!CrouchCheck)
		{
			CameraBoom->SetRelativeLocation(FVector(0.0f, 45.0f, 25.0f), false, nullptr, ETeleportType::TeleportPhysics);
			memrun = 0.5;
			CrouchCheck = true;
			ProneCheck = false;
			CrouchUpdate.Broadcast(true);
			ProneUpdate.Broadcast(false);
			MoveBlock = true;
		}
		else
		{
			CameraBoom->SetRelativeLocation(FVector(0.0f, 45.0f, 70.0f), false, nullptr, ETeleportType::TeleportPhysics);
			CrouchCheck = false;
			ProneCheck = false;
			CrouchUpdate.Broadcast(false);
			ProneUpdate.Broadcast(false);
			MoveBlock = true;
			if (ZoomCheck)
			{
				memrun = 0.5;
				return;
			}
			memrun = 1;
		}
	}
}

void AMyCharacter::Prone()
{
	if (bGetGun)
	{
		if (!ProneCheck)
		{
			CameraBoom->SetRelativeLocation(FVector(0.0f, 25.0f, -50.0f), false, nullptr, ETeleportType::TeleportPhysics);
			ProneCheck = true;
			CrouchCheck = false;
			memrun = 0;
			ProneUpdate.Broadcast(true);
			CrouchUpdate.Broadcast(false);
			MoveBlock = true;
		}
		else
		{
			CameraBoom->SetRelativeLocation(FVector(0.0f, 45.0f, 70.0f), false, nullptr, ETeleportType::TeleportPhysics);
			ProneCheck = false;
			CrouchCheck = false;
			ProneUpdate.Broadcast(false);
			CrouchUpdate.Broadcast(false);
			MoveBlock = true;
			if (ZoomCheck)
			{
				memrun = 0.5;
				return;
			}
			memrun = 1;
		}
	}
}

void AMyCharacter::Shoot()
{
	if (ProjectileClass != nullptr)
	{
		if (mWeaponMesh->GetBulletCount() > 0 && !bReload && !IsInvenDraw && mWeaponMesh->GetTimeBetweenShoot() <= TimeBetweenShoot && mWeaponMesh->GetShootMode() == 0)
		{
			GetWorld()->SpawnActor<ABulletMgr>(ProjectileClass, BulletStart->GetComponentLocation(), mWeaponMesh->GetComponentRotation() + FRotator(0, 0, -90))->SetDamage(mWeaponMesh->GetDamage());
			if (!ProneCheck)
			{
				UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
				Animation->Montage_Play(ShootAnimation, 1.0f);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootFireFx, BulletStart->GetComponentLocation());
			}
			else
			{
				UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
				Animation->Montage_Play(ProneShootAnimation, 1.0f);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootFireFx, BulletStart->GetComponentLocation());
			}
			mWeaponMesh->DeclineBullet();
			TimeBetweenShoot = 0;
			return;
		}
		else if (mWeaponMesh->GetBulletCount() > 0 && !bReload && !IsInvenDraw && mWeaponMesh->GetTimeBetweenShoot() <= TimeBetweenShoot && mWeaponMesh->GetShootMode() == 1)
		{
			bBurst = true;
			return;
		}
	}
}

void AMyCharacter::ShootRelease()
{

}

void AMyCharacter::Zoom()
{
	if (FreeCheck && !ZoomCheck && !IsInvenDraw)
	{
		CameraBoom->TargetArmLength = 100.0f;
		ZoomCheck = true;
		ZoomUpdate.Broadcast(true);
		if (!ProneCheck)
		{
			run = 0.5;
			//memrun = 1;
		}
	}

	if (ZoomTime <= 0.15 && !IsInvenDraw)
	{
		ZoomCamera->Activate();
		FollowCamera->Deactivate();
		ZoomTime = 1;
		DoubleZoom = true;
	}

	if (IsInvenDraw)
	{
		hud->MouseRightClick();
	}
}

void AMyCharacter::ZoomRelease()
{
	FollowCamera->Activate();
	ZoomCamera->Deactivate();
	CameraBoom->TargetArmLength = 150.0f;
	DoubleZoom = false;
	ZoomCheck = false;
	ZoomUpdate.Broadcast(false);
	ZoomTime = 0;
	if (ProneCheck || CrouchCheck)
	{
		run = memrun;
		return;
	}
	run = 1;
}

void AMyCharacter::Run()
{
	if (!ProneCheck && !CrouchCheck && !ZoomCheck)
	{
		run = 2.5;
	}
	else if (DoubleZoom && CanHoldBreath)
	{
		HoldBreath.Broadcast(true);
		HoldingBreath = true;
		CanHoldBreath = false;
	}
}

void AMyCharacter::RunRelease()
{
	if (!ProneCheck && !CrouchCheck && !ZoomCheck)
	{
		run = 1;
	}
	HoldBreath.Broadcast(false);
	HoldingBreath = false;
}

void AMyCharacter::Free()
{
	FreeCheck = false;
	bUseControllerRotationYaw = false;
	CRotation = GetController()->GetControlRotation();
	FreeUpdate.Broadcast(true);
}

void AMyCharacter::FreeRelease()
{
	FreeCheck = true;
	bUseControllerRotationYaw = true;
	GetController()->SetControlRotation(CRotation);
	FreeUpdate.Broadcast(false);
}

void AMyCharacter::Jump()
{
	if (!GetCharacterMovement()->IsFalling() && runDelay >= 0.9 && !ProneCheck && !CrouchCheck)
	{
		ACharacter::Jump();
		JumpUpdate.Broadcast(true);
		runDelay = 0;
	}
}

void AMyCharacter::JumpRelease()
{
	ACharacter::StopJumping();
	JumpUpdate.Broadcast(false);
}

void AMyCharacter::Reload()
{
	if (mWeaponMesh->GetCanReload() && InvenMap.Find(mWeaponMesh->GetBulletName()))
	{
		UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
		Animation->Montage_Play(ReloadAnimation, 1.0f);
		bReload = true;
	}
}
void AMyCharacter::Inven()
{
	if (IsInvenDraw)
	{
		IsInvenDraw = false;
		hud->SetDrawInven(IsInvenDraw);
		PlayerController->bShowMouseCursor = false;
		return;
	}
	IsInvenDraw = true;
	hud->SetDrawInven(IsInvenDraw);
	PlayerController->bShowMouseCursor = true;
	ZoomRelease();
}

void AMyCharacter::BeginPickUp()
{
	FVector Start = FollowCamera->GetComponentLocation();

	FVector ViewF;
	ViewF = FollowCamera->GetForwardVector() * 350;

	FVector End = ViewF + Start;

	FHitResult hit;

	FCollisionQueryParams Collision;
	Collision.AddIgnoredActor(this);

	GetWorld()->SweepSingleByChannel(hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, FCollisionShape::MakeSphere(40), Collision);

	AVehicle* Vehicle = Cast<AVehicle>(hit.GetActor());

	if (Vehicle && fCanRide > 0.75)
	{
		AttachToActor(Vehicle, FAttachmentTransformRules::KeepWorldTransform);
		Controller->Possess(Vehicle);
		Vehicle->SetCharacter(this);
		fCanRide = 0;
		return;
	}

	AItem* Item = Cast<AItem>(hit.GetActor());
	if (Item)
	{
		if (Item->GetCheckItem() == 1)
		{
			if (GunArray[iSelectGun] != nullptr)
			{
				GunArray[iSelectGun]->SetActorHiddenInGame(false);
				GunArray[iSelectGun]->SetActorLocation(GetTargetLocation() - FVector(0, 0, 97.0) + FVector(0, 0, 10));
			}
			hud->GetGunValue(iSelectGun);
			FString name = Item->GetItemName();
			Widget w = Widget(Icon(name, TmIcons[name]));
			w.Item = Item;
			hud->SetGun(w, iSelectGun);
			hud->RemoveFarmingItem(Item);		
			Item->SetActorHiddenInGame(true);
			Item->SetActorLocation(FVector(0, 0, -1000));
			return;
		}

		Item->SetPlayer(this);
		Item->PickUp();

		hud->EmptyInven();

		for (TMap<FString, int>::TIterator it = InvenMap.CreateIterator(); it; ++it)
		{
			FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);
			hud->AddInvenItem(Widget(Icon(name, TmIcons[it->Key])), *ItemMap.Find(it->Key));
		}
	}
}

void AMyCharacter::EndPickUp()
{
	bPickUp = false;
}

void AMyCharacter::Yaw(float value)
{
	if (IsInvenDraw)
	{
		hud->MouseMove();
		return;
	}
	float a = value * 50;
	AddControllerYawInput(a * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::Pitch(float value)
{
	if (IsInvenDraw)
	{
		hud->MouseMove();
		return;
	}
	float a = value * 50;
	AddControllerPitchInput(a * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::Clickced()
{
	if (IsInvenDraw)
	{
		hud->MouseClick();
	}
}

void AMyCharacter::ChangeShootMode()
{
	mWeaponMesh->ChangeShootMode();
}

void AMyCharacter::SetSelectGun1()
{
	iSelectGun = 0;
	SetGun(GunArray[iSelectGun], iSelectGun);
	if (GunArray[iSelectGun] != nullptr)
	{
		SetHologram(GunArray[iSelectGun]->GetHoloGram(), iSelectGun);
		return;
	}
	SetHologram(false, iSelectGun);
}

void AMyCharacter::SetSelectGun2()
{
	iSelectGun = 1;
	SetGun(GunArray[iSelectGun], iSelectGun);
	if (GunArray[iSelectGun] != nullptr)
	{
		SetHologram(GunArray[iSelectGun]->GetHoloGram(), iSelectGun);
		return;
	}
	SetHologram(false, iSelectGun);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerController->SetInputMode(FInputModeGameOnly());
	fCanRide += DeltaTime;
	runDelay += DeltaTime;
	ZoomTime += DeltaTime;
	TimeBetweenShoot += DeltaTime;
	if (bBurst && mWeaponMesh->GetShootMode() == 1)
	{
		if (iBurstCount < 3 && fShootTime > 0.016)
		{
			if (mWeaponMesh->GetBulletCount() <= 0)
			{
				iBurstCount++;
			}
			else if (!ProneCheck)
			{
				UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
				Animation->Montage_Play(ShootAnimation, 1.0f);
				GetWorld()->SpawnActor<ABulletMgr>(ProjectileClass, BulletStart->GetComponentLocation(), mWeaponMesh->GetComponentRotation() + FRotator(0, 0, -90))->SetDamage(mWeaponMesh->GetDamage());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootFireFx, BulletStart->GetComponentLocation());
				mWeaponMesh->DeclineBullet();
				iBurstCount++;
			}
			else
			{
				UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
				Animation->Montage_Play(ShootAnimation, 1.0f);
				GetWorld()->SpawnActor<ABulletMgr>(ProjectileClass, BulletStart->GetComponentLocation(), mWeaponMesh->GetComponentRotation() + FRotator(0, 0, -90))->SetDamage(mWeaponMesh->GetDamage());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootFireFx, BulletStart->GetComponentLocation());
				mWeaponMesh->DeclineBullet();
				iBurstCount++;
			}
			fShootTime = 0;
		}
		else if (fShootTime <= 0.016)
		{
			fShootTime += DeltaTime;
		}
		else
		{
			TimeBetweenShoot = 0;
			iBurstCount = 0;
			bBurst = false;
		}
	}

	if (fEnergy > 0)
	{
		fEnergy -= 1 * DeltaTime;
	}
	else
	{
		fEnergy = 0;
	}

	if (fEnergy >= 50)
	{
		EnergyRun = 1.75;
	}
	else
	{
		EnergyRun = 1;
	}

	if (MoveBlock && time < 0.5)
	{
		time += DeltaTime;
		run = 0;
	}
	else if (MoveBlock && time >= 0.5)
	{
		time = 0;
		MoveBlock = false;
		run = memrun;
	}

	if (HoldingBreath && HoldBreathTime > 0)
	{
		HoldBreathTime -= DeltaTime;
	}

	else if (HoldingBreath && HoldBreathTime <= 0)
	{
		HoldBreath.Broadcast(false);
		HoldingBreath = false;
	}

	if (!HoldingBreath && HoldBreathTime <= 3)
	{
		HoldBreathTime += DeltaTime;
	}

	if (!HoldingBreath && HoldBreathTime >= 1.5)
	{
		CanHoldBreath = true;
	}

	UAnimInstance* Animation = SkeletonMesh->GetAnimInstance();
	if (!Animation->IsAnyMontagePlaying() && bReload)
	{
		int value = (int)*InvenMap.Find(mWeaponMesh->GetBulletName());
		if (value > mWeaponMesh->GetReloadBulletCount())
		{
			int a = value - mWeaponMesh->GetReloadBulletCount();
			mWeaponMesh->AddBullet(mWeaponMesh->GetReloadBulletCount());
			InvenMap.Add(mWeaponMesh->GetBulletName(), a);
		}
		else
		{
			mWeaponMesh->AddBullet(value);
			InvenMap.Remove(mWeaponMesh->GetBulletName());
		}

		hud->EmptyInven();

		for (TMap<FString, int>::TIterator it = InvenMap.CreateIterator(); it; ++it)
		{
			FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);
			hud->AddInvenItem(Widget(Icon(name, TmIcons[it->Key])), *ItemMap.Find(it->Key));
		}

		bReload = false;
	}
	float fE = fEnergy / 100;
	EnergyUpdate.Broadcast(fE);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("FB_Move", this, &AMyCharacter::FB_Move);
	PlayerInputComponent->BindAxis("LR_Move", this, &AMyCharacter::LR_Move);

	PlayerInputComponent->BindAxis("Turn_Rate", this, &AMyCharacter::Yaw);
	PlayerInputComponent->BindAxis("LookUp_Rate", this, &AMyCharacter::Pitch);

	PlayerInputComponent->BindAxis("ShootAuto", this, &AMyCharacter::ShootAuto);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::JumpRelease);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::Shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyCharacter::ShootRelease);

	PlayerInputComponent->BindAction("Squat", IE_Pressed, this, &AMyCharacter::Squat);
	PlayerInputComponent->BindAction("Prone", IE_Pressed, this, &AMyCharacter::Prone);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AMyCharacter::Zoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AMyCharacter::ZoomRelease);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::RunRelease);

	PlayerInputComponent->BindAction("Free", IE_Pressed, this, &AMyCharacter::Free);
	PlayerInputComponent->BindAction("Free", IE_Released, this, &AMyCharacter::FreeRelease);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyCharacter::Reload);

	PlayerInputComponent->BindAction("Inven", IE_Pressed, this, &AMyCharacter::Inven);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AMyCharacter::BeginPickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &AMyCharacter::EndPickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Repeat, this, &AMyCharacter::EndPickUp);

	PlayerInputComponent->BindAction("WeaponSwap1", IE_Pressed, this, &AMyCharacter::SetSelectGun1);
	PlayerInputComponent->BindAction("WeaponSwap2", IE_Pressed, this, &AMyCharacter::SetSelectGun2);

	PlayerInputComponent->BindAction("InvenClick", IE_Pressed, this, &AMyCharacter::Clickced);

	PlayerInputComponent->BindAction("ChangeShootMode", IE_Pressed, this, &AMyCharacter::ChangeShootMode);
}

int AMyCharacter::GetBulletCount()
{
	if (ProjectileClass != nullptr)
	{
		return mWeaponMesh->GetBulletCount();
	}
	return 0;
}

int AMyCharacter::GetInvenBulletCount()
{
	if (InvenMap.Find(mWeaponMesh->GetBulletName()) != nullptr && ProjectileClass != nullptr)
	{
		return (int)*InvenMap.Find(mWeaponMesh->GetBulletName());
	}
	return 0;
}

void AMyCharacter::Damage(float g_Damage)
{
}

void AMyCharacter::SetHologram(bool g_holo, int g_num)
{
	if (GunArray[g_num] == nullptr)
	{
		Sight->SetStaticMesh(nullptr);
		return;
	}
	if (g_holo && iSelectGun == g_num)
	{
		Sight->SetStaticMesh(SHoloGram);
		Sight->RelativeLocation = mWeaponMesh->GetHologramLocation();
		return;
	}

	Sight->SetStaticMesh(mWeaponMesh->GetScopeMesh());
	Sight->RelativeLocation = FVector(0,0,0);
}

void AMyCharacter::SetGun(AItem * g_gun, int g_num)
{
	GunArray[g_num] = g_gun;
	if (iSelectGun == g_num)
	{
		if (GunArray[g_num] == nullptr)
		{
			mWeaponMesh->SetStaticMesh(nullptr);
			ProjectileClass = nullptr;
			GunUpdate.Broadcast(false);
			bGetGun = false;
			return;
		}
		mWeaponMesh->SetGun(GunArray[g_num]->GetItemName());
		mWeaponMesh->SetStaticMesh(mWeaponMesh->GetStaticMesh());
		mWeaponMesh->RelativeLocation = mWeaponMesh->GetGunLocation();
		ZoomCamera->RelativeLocation = mWeaponMesh->GetZooomCameraLocation();
		BulletStart->RelativeLocation = mWeaponMesh->GetBulletStart();
		ProjectileClass = mWeaponMesh->GetBullet();
		GunUpdate.Broadcast(true);
		bGetGun = true;
	}
}

void AMyCharacter::AddEnergy(float g_energy)
{
	fEnergy += g_energy;
	if (fEnergy >= 100)
	{
		fEnergy = 100;
	}
}

void AMyCharacter::ResetCanRide()
{
	fCanRide = 0;
}
