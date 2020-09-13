// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Item.h"
#include "Engine/Canvas.h"
#include "Engine.h"
#include "StructHeader.h"

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossHair.generated.h"

namespace CrossHairDirection
{
	enum Type
	{
		Center = 0,
		Top = 1,
		Bottom = 2,
		Left = 3,
		Right = 4,
	};
};

UCLASS()
class PUBG_API ACrossHair : public AHUD
{
	GENERATED_BODY()

	virtual void DrawHUD() override;
	bool InvenDraw;

public:
	ACrossHair();
	void SetDrawInven(bool g_InvenDraw);
	void AddInvenItem(Widget g_widget, AItem* g_Item);
	void AddFarmingItem(Widget g_widget, AItem* g_Item);
	void RemoveFarmingItem(AItem* g_Item);

	void SetGun(Widget g_gun, int g_array);
	void RemoveGun(Widget g_gun, int g_array);

	void EmptyInven();
	void MouseClick();
	void MouseMove();
	void MouseRightClick();

	void GetGunValue(int g_array);
	//void SetPlayer(AMyCharacter* g_player);

protected:
	UPROPERTY()
		
	FCanvasIcon mCrossHair[5];
	FCanvasIcon mBreath;
	UTexture2D* mInventexture;
	UFont* mFont;
	Widget* LastWidget;
	AItem* LastItem;
	FVector2D StartPos;
	int iSelectGun;
	FString SShootMode;

	TArray<Widget> widgets;
	TArray<Widget> Farmingwidgets;

	Widget FfGun[2];
	Widget mGunParts[2];

	void DrawAlignedIcon(const FCanvasIcon& pIcon, const int pX, const int pY, const CrossHairDirection::Type pAlign, const float pScale = 1.0f);
};
