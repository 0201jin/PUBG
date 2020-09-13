// Fill out your copyright notice in the Description page of Project Settings.

#include "UAZ.h"

// Sets default values
AUAZ::AUAZ()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMove = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	mMove->MaxSpeed = 9000;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Vehicle(TEXT("StaticMesh'/Game/Model/UAZ/UAZ.UAZ'"));
	mVehicle = NewObject<UStaticMeshComponent>(this, TEXT("CharacterWeaponMesh"));
	RootComponent = mVehicle;
	mVehicle->SetStaticMesh(Vehicle.Object);
	mVehicle->SetRelativeRotation(FRotator(0, 180, 0));
	mVehicle->SetSimulatePhysics(true);
	mVehicle->SetCollisionProfileName("Vehicle");
	//mVehicle->SetMassOverrideInKg(NAME_None, 1500.0f, true);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(mVehicle);
	Box->RelativeLocation = FVector(10, 0, 10);
	Box->RelativeScale3D = FVector(4, 2.5, 0.5);
	Box->SetCollisionProfileName("OverlapAll");

	mVehicle->bGenerateOverlapEvents = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->RelativeLocation = FVector(130.0f, 0.0f, 200.0f);
	CameraBoom->RelativeRotation = FRotator(-10, -180, 0);
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	mMyCharacter = nullptr;
	fSpeed = 0;
}

// Called when the game starts or when spawned
void AUAZ::BeginPlay()
{
	Super::BeginPlay();

}

void AUAZ::FB_Move(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && !bBrake && bCanMove)
	{
		if (fSpeed < 30 && fSpeed > -90)
		{
			fSpeed -= ((value * 15) + (fBooster * value)) * GetWorld()->GetDeltaSeconds();
		}

		return;
	}
	fSpeed = FMath::FInterpTo(fSpeed, 0, GetWorld()->GetDeltaSeconds(), 1);
	//fSpeed = FMath::Clamp(value, -0.0f, 0.0f);
}

void AUAZ::LR_Move(float value)
{
	if (bCanMove)
	{
		RotVector.Yaw = FMath::Clamp(value * 4, -50.0f, 50.0f);
	}
}

void AUAZ::Yaw(float value)
{
	float a = value * 50;
	//AddControllerYawInput(a * GetWorld()->GetDeltaSeconds());
	CameraBoom->AddRelativeRotation(FRotator(0, a * GetWorld()->GetDeltaSeconds(), 0));
}

void AUAZ::Pitch(float value)
{
	float a = value * 50;
	//AddControllerPitchInput(a * GetWorld()->GetDeltaSeconds());
	CameraBoom->AddRelativeRotation(FRotator((a * GetWorld()->GetDeltaSeconds()) * -1, 0, 0));
}

void AUAZ::Inven()
{
	mMyCharacter->Inven();
}

void AUAZ::GetOut()
{
	if (fCanGetOut > 0.75)
	{
		bCharRide = false;
		mMyCharacter->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		mMyCharacter->SetActorHiddenInGame(false);

		FVector RightVector = GetActorRightVector() * 200 + GetActorLocation();

		if (RightVector.Z + 125 <= GetActorLocation().Z)
		{
			Controller->Possess(mMyCharacter);
			mMyCharacter->SetActorLocation(GetActorUpVector() * -200 + GetActorLocation());
			mMyCharacter->SetActorEnableCollision(true);
			mMyCharacter->ResetCanRide();
			mMyCharacter = nullptr;
			return;
		}

		Controller->Possess(mMyCharacter);
		mMyCharacter->SetActorLocation(GetActorRightVector() * 200 + GetActorLocation());
		mMyCharacter->LaunchCharacter(FVector(0, 0, 300) + GetActorForwardVector() * fSpeed * 10, true, false);
		mMyCharacter->SetActorEnableCollision(true);
		mMyCharacter->ResetCanRide();
		mMyCharacter = nullptr;
		return;
	}
}

void AUAZ::Brake(float value)
{
	if (value != 0 && bCanMove)
	{
		fSpeed = FMath::FInterpTo(fSpeed, 0, GetWorld()->GetDeltaSeconds(), 2);
		bBrake = true;
		return;
	}
	bBrake = false;
}

void AUAZ::Booster()
{
	fBooster = 1;
}

void AUAZ::BoosterRelease()
{
	fBooster = 0;
}

// Called every frame
void AUAZ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	fCanGetOut += DeltaTime;

	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, FString::Printf(TEXT("%f"), fSpeed));

	FHitResult Hit;
	FCollisionQueryParams Collision;
	Collision.AddIgnoredActor(this);
	Collision.AddIgnoredActor(mMyCharacter);

	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() - FVector(0, 0, 45), ECollisionChannel::ECC_WorldDynamic, Collision))
	{
		bCanMove = true;
	}
	else
	{
		bCanMove = false;
	}

	AddActorWorldOffset(GetActorForwardVector() * fSpeed);

	//AddMovementInput(GetActorForwardVector(), fSpeed);
	if (fSpeed > 5 || fSpeed < -5)
	{
		//AddActorLocalRotation(RotVector);
		AddActorWorldRotation(RotVector);
	}

	/*if (bCharRide && fGetOutTime < 0.5)
	{
		mMyCharacter->SetActorLocation(GetActorLocation());
		fGetOutTime += DeltaTime;
	}*/

	if (bCharRide)
	{
		mMyCharacter->SetActorEnableCollision(false);
		mMyCharacter->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 75));
		mMyCharacter->SetActorRotation(FRotator(0, GetActorRotation().Yaw - 180, 0));
		return;
	}

	fSpeed = FMath::FInterpTo(fSpeed, 0, GetWorld()->GetDeltaSeconds(), 1);
}

// Called to bind functionality to input
void AUAZ::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("FB_Move", this, &AUAZ::FB_Move);
	PlayerInputComponent->BindAxis("LR_Move", this, &AUAZ::LR_Move);

	PlayerInputComponent->BindAxis("Turn_Rate", this, &AUAZ::Yaw);
	PlayerInputComponent->BindAxis("LookUp_Rate", this, &AUAZ::Pitch);

	PlayerInputComponent->BindAxis("Brake", this, &AUAZ::Brake);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AUAZ::GetOut);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AUAZ::Booster);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AUAZ::BoosterRelease);

	PlayerInputComponent->BindAction("Inven", IE_Pressed, this, &AUAZ::Inven);
}

void AUAZ::SetCharacter(AMyCharacter * g_MyCharacter)
{
	mMyCharacter = g_MyCharacter;
	mMyCharacter->SetActorHiddenInGame(true);
	bCharRide = true;
	fCanGetOut = 0;
}

