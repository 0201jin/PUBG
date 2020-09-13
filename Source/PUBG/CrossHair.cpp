// Fill out your copyright notice in the Description page of Project Settings.

#include "CrossHair.h"
#include "Engine.h"
#include "MyCharacter.h"

ACrossHair::ACrossHair()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CHtexture(TEXT("Texture2D'/Game/HUD/Texture/CrossHair.CrossHair'"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> CHInvenTexture(TEXT("Texture2D'/Game/Texture/InventoryUi.InventoryUi'"));
	mInventexture = CHInvenTexture.Object;

	mCrossHair[CrossHairDirection::Center] = UCanvas::MakeIcon(CHtexture.Object, 0, 16, 6, 6);
	mCrossHair[CrossHairDirection::Top] = UCanvas::MakeIcon(CHtexture.Object, 0, 24, 6, 25);
	mCrossHair[CrossHairDirection::Bottom] = UCanvas::MakeIcon(CHtexture.Object, 8, 24, 6, 25);
	mCrossHair[CrossHairDirection::Left] = UCanvas::MakeIcon(CHtexture.Object, 0, 0, 25, 6);
	mCrossHair[CrossHairDirection::Right] = UCanvas::MakeIcon(CHtexture.Object, 0, 8, 25, 6);

	static ConstructorHelpers::FObjectFinder<UTexture2D> BreathTexture(TEXT("Texture2D'/Game/HUD/Texture/Breath.Breath'"));
	mBreath = UCanvas::MakeIcon(BreathTexture.Object, 0, 0, 128, 128);

	static ConstructorHelpers::FObjectFinder<UFont> lFont(TEXT("Font'/Engine/EngineFonts/Roboto.Roboto'"));
	mFont = lFont.Object;

	InvenDraw = false;

	LastWidget = NULL;
	LastItem = NULL;
}

void ACrossHair::SetDrawInven(bool g_InvenDraw)
{
	InvenDraw = g_InvenDraw;
}

void ACrossHair::AddInvenItem(Widget g_widget, AItem* g_Item)
{
	FVector2D start(275, 100);
	g_widget.size = FVector2D(32, 32);
	g_widget.pos = start;

	for (int c = 0; c < widgets.Num(); c++)
	{
		g_widget.pos.Y += g_widget.size.Y + 10;
	}
	g_widget.type = 0;
	g_widget.Item = g_Item;
	widgets.Add(g_widget);
}

void ACrossHair::AddFarmingItem(Widget g_widget, AItem* g_Item)
{
	FVector2D start(150, 100);
	g_widget.size = FVector2D(32, 32);
	g_widget.pos = start;

	for (int c = 0; c < Farmingwidgets.Num(); c++)
	{
		g_widget.pos.Y += g_widget.size.Y + 10;
	}
	g_widget.type = 1;
	g_widget.Item = g_Item;
	Farmingwidgets.Add(g_widget);
}

void ACrossHair::RemoveFarmingItem(AItem* g_Item)
{
	for (int c = 0; c < Farmingwidgets.Num(); c++)
	{
		if (Farmingwidgets[c].Item == g_Item)
		{
			Farmingwidgets.RemoveAt(c);

			for (int c = 0; c < Farmingwidgets.Num(); c++)
			{
				Farmingwidgets[c].pos.Y = ((Farmingwidgets[c].size.Y + 10) * c) + 100;
			}

			return;
		}
	}
}

void ACrossHair::SetGun(Widget g_gun, int g_array)
{
	AMyCharacter* player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		g_gun.type = 2;
		g_gun.size = FVector2D(32, 32);
		if (g_gun.icon.name == "UNKNOWN ICON")
		{
			FfGun[g_array] = Widget();
			player->SetGun(nullptr, g_array);
			player->SetHologram(false, g_array);
			return;
		}

		if (g_array == 0)
		{
			g_gun.pos = FVector2D(400, 150);
			g_gun.start = FVector2D(400, 150);
			FfGun[g_array] = g_gun;
			player->SetGun(FfGun[g_array].Item, g_array);
			player->SetHologram(FfGun[g_array].Item->GetHoloGram(), g_array);
			return;
		}
		g_gun.pos = FVector2D(400, 250);
		g_gun.start = FVector2D(400, 250);
		FfGun[g_array] = g_gun;
		player->SetGun(FfGun[g_array].Item, g_array);
		player->SetHologram(FfGun[g_array].Item->GetHoloGram(), g_array);
	}
}

void ACrossHair::RemoveGun(Widget g_gun, int g_array)
{
	AMyCharacter* player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (g_array == 0)
	{
		FfGun[g_array] = Widget();
		return;
	}
	FfGun[g_array] = Widget();;
}

void ACrossHair::EmptyInven()
{
	widgets.Empty();
}

void ACrossHair::MouseClick()
{
	FVector2D mouse;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(mouse.X, mouse.Y);
	LastWidget = NULL;
	LastItem = NULL;

	for (int c = 0; c < Farmingwidgets.Num(); c++)
	{
		if (Farmingwidgets[c].click(mouse))
		{
			LastWidget = &Farmingwidgets[c];
			LastItem = Farmingwidgets[c].Item;
			StartPos = Farmingwidgets[c].pos;
			return;
		}
	}

	for (int c = 0; c < widgets.Num(); c++)
	{
		if (widgets[c].click(mouse))
		{
			LastWidget = &widgets[c];
			LastItem = widgets[c].Item;
			StartPos = widgets[c].pos;
			return;
		}
	}

	if (FfGun[0].click(mouse))
	{
		LastWidget = &FfGun[0];
		LastItem = FfGun[0].Item;
		StartPos = FfGun[0].pos;
		iSelectGun = 0;
		return;
	}

	if (FfGun[1].click(mouse))
	{
		LastWidget = &FfGun[1];
		LastItem = FfGun[1].Item;
		StartPos = FfGun[1].pos;
		iSelectGun = 1;
		return;
	}

	if (mGunParts[0].click(mouse))
	{
		LastWidget = &mGunParts[0];
		LastItem = mGunParts[0].Item;
		StartPos = mGunParts[0].pos;
		iSelectGun = 0;
		return;
	}

	if (mGunParts[1].click(mouse))
	{
		LastWidget = &mGunParts[1];
		LastItem = mGunParts[1].Item;
		StartPos = mGunParts[1].pos;
		iSelectGun = 1;
		return;
	}
}

void ACrossHair::MouseMove()
{
	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(thisMouse.X, thisMouse.Y);
	dMouse = thisMouse - lastMouse;

	float time = GetWorld()->GetFirstPlayerController()->GetInputKeyTimeDown(EKeys::LeftMouseButton);

	AMyCharacter* player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player)
	{
		if (time > 0.f && LastWidget)
		{
			LastWidget->pos.X += dMouse.X;
			LastWidget->pos.Y += dMouse.Y;
		}

		if (LastWidget != NULL && time <= 0)
		{
			//여기서 부터는 총
			if (LastWidget->type != 0 && LastWidget->pos.X >= 400 && time <= 0 && LastWidget->Item->GetCheckItem() != 0)
			{
				if (LastWidget->pos.Y >= 100 && LastWidget->pos.Y < 200)
				{
					if (LastWidget->type == 2 && LastWidget->start == FVector2D(400, 250))
					{
						if (LastWidget->Item->GetCheckItem() == 2)
						{
							mGunParts[1] = mGunParts[0];
							mGunParts[0] = Widget();
							return;
						}
						Widget widget = FfGun[1];

						Widget Holowidget = mGunParts[1];
						mGunParts[1] = mGunParts[0];
						mGunParts[0] = Holowidget;

						mGunParts[0].pos = FVector2D(400, 110);
						mGunParts[1].pos = FVector2D(400, 210);

						SetGun(FfGun[0], 1);
						SetGun(widget, 0);

						LastWidget = NULL;
						return;
					}

					if (LastWidget->Item->GetCheckItem() == 2 && FfGun[0].icon.name != "UNKNOWN ICON")
					{
						FfGun[0].Item->SetHoloGram(true);

						player->SetHologram(FfGun[0].Item->GetHoloGram(), 0);

						LastWidget->pos = FVector2D(400, 110);
						LastWidget->type = 2;

						mGunParts[0] = *LastWidget;
						mGunParts[1] = Widget();

						LastItem->SetActorHiddenInGame(true);
						LastItem->SetActorLocation(FVector(0, 0, -1000));
						LastWidget = NULL;
						return;
					}
					else if (LastWidget->Item->GetCheckItem() == 2 && FfGun[0].icon.name == "UNKNOWN ICON")
					{
						LastWidget->pos = StartPos;
						LastWidget = NULL;
						return;
					}
					//Setgun 위에 아이템 들어오면 빠지는거 만드는 작업하기

					if (LastWidget->Item->GetCheckItem() == 1 && FfGun[0].icon.name != "UNKNOWN ICON")
					{
						/*AItem* aa = GetWorld()->SpawnActor<AItem>(FfGun[0].Item->GetClass(), player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z), FRotator(0, 0, 0));
						aa->SetHoloGram(FfGun[0].Item->GetHoloGram());*/

						FfGun[0].Item->SetActorHiddenInGame(false);
						FfGun[0].Item->SetActorLocation(player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z) + FVector(0, 0, 3));

						mGunParts[0] = Widget();

						player->SetHologram(false, 0);
					}

					SetGun(*LastWidget, 0);

					player->SetGun(LastItem, 0);

					player->SetHologram(FfGun[0].Item->GetHoloGram(), 0);

					RemoveFarmingItem(LastItem);

					if (mGunParts[0].icon.name == "UNKNOWN ICON" && FfGun[0].Item->GetHoloGram())
					{
						FString name = TEXT("HoloGramSight");
						mGunParts[0] = Widget(Icon(name, player->TmIcons["HoloGramSight"]));
						mGunParts[0].pos = FVector2D(400, 110);
						mGunParts[0].type = 2;
						mGunParts[0].Item = *player->ItemMap.Find("HoloGramSight");
					}

					LastItem->SetActorHiddenInGame(true);
					LastItem->SetActorLocation(FVector(0, 0, -1000));
					LastWidget = NULL;
					return;
				}

				if (LastWidget->pos.Y >= 200 && LastWidget->pos.Y < 300)
				{
					if (LastWidget->type == 2 && LastWidget->start == FVector2D(400, 150))
					{
						if (LastWidget->Item->GetCheckItem() == 2)
						{
							mGunParts[0] = mGunParts[1];
							mGunParts[1] = Widget();
							return;
						}
						Widget widget = FfGun[0];

						Widget Holowidget = mGunParts[0];
						mGunParts[0] = mGunParts[1];
						mGunParts[1] = Holowidget;

						mGunParts[1].pos = FVector2D(400, 210);
						mGunParts[0].pos = FVector2D(400, 110);

						SetGun(FfGun[1], 0);
						SetGun(widget, 1);

						LastWidget = NULL;
						return;
					}

					if (LastWidget->Item->GetCheckItem() == 2 && FfGun[1].icon.name != "UNKNOWN ICON")
					{
						FfGun[1].Item->SetHoloGram(true);					

						player->SetHologram(true, 1);

						LastWidget->pos = FVector2D(400, 210);
						LastWidget->type = 2;

						mGunParts[1] = *LastWidget;		
						mGunParts[0] = Widget();

						LastItem->SetActorHiddenInGame(true);
						LastItem->SetActorLocation(FVector(0, 0, -1000));
						LastWidget = NULL;
						return;
					}
					else if (LastWidget->Item->GetCheckItem() == 2 && FfGun[1].icon.name == "UNKNOWN ICON")
					{
						LastWidget->pos = StartPos;
						LastWidget = NULL;
						return;
					}
					//Setgun 위에 아이템 들어오면 빠지는거 만드는 작업하기

					if (LastWidget->Item->GetCheckItem() == 1 && FfGun[1].icon.name != "UNKNOWN ICON")
					{
						/*AItem* aa = GetWorld()->SpawnActor<AItem>(FfGun[1].Item->GetClass(), player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z), FRotator(0, 0, 0));
						aa->SetHoloGram(FfGun[1].Item->GetHoloGram());*/
						FfGun[1].Item->SetActorHiddenInGame(false);
						FfGun[1].Item->SetActorLocation(player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z) + FVector(0, 0, 3));
						mGunParts[1] = Widget();

						player->SetHologram(false, 1);
					}

					SetGun(*LastWidget, 1);

					player->SetGun(LastItem, 1);

					player->SetHologram(FfGun[1].Item->GetHoloGram(), 1);

					RemoveFarmingItem(LastItem);

					if (mGunParts[1].icon.name == "UNKNOWN ICON" && FfGun[1].Item->GetHoloGram())
					{
						FString name = TEXT("HoloGramSight");
						mGunParts[1] = Widget(Icon(name, player->TmIcons["HoloGramSight"]));
						mGunParts[1].pos = FVector2D(400, 210);
						mGunParts[1].type = 2;
						mGunParts[1].Item = *player->ItemMap.Find("HoloGramSight");
					}

					LastItem->SetActorHiddenInGame(true);
					LastItem->SetActorLocation(FVector(0, 0, -1000));
					LastWidget = NULL;
					return;
				}

				LastWidget->pos = StartPos;
				LastWidget = NULL;
				return;
			}

			if (LastWidget->type == 2 && LastWidget->pos.X < 400 && time <= 0 && LastWidget->Item->GetCheckItem() != 0)
			{
				if (LastWidget->Item->GetCheckItem() == 2 && FfGun[iSelectGun].icon.name != "UNKNOWN ICON")
				{
					//AItem* aa = GetWorld()->SpawnActor<AItem>(LastItem->GetClass(), player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z), FRotator(0, 0, 0));
					LastItem->SetActorHiddenInGame(false);
					LastItem->SetActorLocation(player->GetTargetLocation() - FVector(0, 0, 97.0) + FVector(0, 0, 5));
					FfGun[iSelectGun].Item->SetHoloGram(false);

					player->SetHologram(false, iSelectGun);

					mGunParts[iSelectGun] = Widget();

					LastWidget = NULL;
					return;
				}
				/*AItem* aa = GetWorld()->SpawnActor<AItem>(LastItem->GetClass(), player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z), FRotator(0, 0, 0));
				aa->SetHoloGram(FfGun[iSelectGun].Item->GetHoloGram());*/

				LastItem->SetActorHiddenInGame(false);
				LastItem->SetActorLocation((player->GetTargetLocation() - FVector(0, 0, 97.0) + FVector(0, 0, 10)));

				mGunParts[iSelectGun] = Widget();
				SetGun(Widget(), iSelectGun);
				/*player->SetGun(nullptr, iSelectGun);
				player->SetHologram(false, iSelectGun);*/

				RemoveGun(Widget(), iSelectGun);

				LastWidget->pos = StartPos;
				LastWidget = NULL;
				return;
			}

			//파밍
			if (LastWidget->type == 1 && LastWidget->pos.X >= 275 && LastWidget->pos.X < 400 && time <= 0 && LastWidget->Item->GetCheckItem() != 1)
			{
				RemoveFarmingItem(LastItem);

				if (player->InvenMap.Num() == 0)
				{
					EmptyInven();

					player->InvenMap.Add(LastItem->GetItemName(), LastItem->GetItemCount());

					FString name = LastItem->GetItemName() + FString::Printf(TEXT(" X %d"), LastItem->GetItemCount());

					AddInvenItem(Widget(Icon(name, player->TmIcons[LastItem->GetItemName()])), LastItem);

					LastItem->SetActorHiddenInGame(true);
					LastItem->SetActorLocation(FVector(0, 0, -1000));
					LastWidget = NULL;
					return;
				}

				if (!player->InvenMap.Find(LastItem->GetItemName()))
				{
					EmptyInven();

					player->InvenMap.Add(LastItem->GetItemName(), LastItem->GetItemCount());

					for (TMap<FString, int>::TIterator it = player->InvenMap.CreateIterator(); it; ++it)
					{
						FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);

						AddInvenItem(Widget(Icon(name, player->TmIcons[it->Key])), *player->ItemMap.Find(it->Key));
					}

					LastItem->SetActorHiddenInGame(true);
					LastItem->SetActorLocation(FVector(0, 0, -1000));
					LastWidget = NULL;
					return;
				}

				EmptyInven();

				int* count = (int*)player->InvenMap.Find(LastItem->GetItemName());
				*count += LastItem->GetItemCount();
				player->InvenMap.Add(LastItem->GetItemName(), *count);

				for (TMap<FString, int>::TIterator it = player->InvenMap.CreateIterator(); it; ++it)
				{
					FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);

					AddInvenItem(Widget(Icon(name, player->TmIcons[it->Key])), *player->ItemMap.Find(it->Key));
				}

				LastItem->SetActorHiddenInGame(true);
				LastItem->SetActorLocation(FVector(0, 0, -1000));
				LastWidget = NULL;
				return;
			}

			if (LastWidget->type == 0 && LastWidget->pos.X < 275 && time <= 0 && LastWidget->Item->GetCheckItem() != 1)
			{
				EmptyInven();

				/*AItem* aa = GetWorld()->SpawnActor<AItem>(LastItem->GetClass(), player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z), FRotator(0, 0, 0));

				aa->SetItemCount(*player->InvenMap.Find(LastItem->GetItemName()));*/

				LastItem->SetActorHiddenInGame(false);
				LastItem->SetActorLocation(player->GetTargetLocation() - FVector(0, 0, 97) + FVector(0, 0, 5));

				RemoveFarmingItem(LastItem);

				FString name = LastItem->GetItemName() + FString::Printf(TEXT(" X %d"), LastItem->GetItemCount());

				AddFarmingItem(Widget(Icon(name, player->TmIcons[LastItem->GetItemName()])), LastItem);

				player->InvenMap.Remove(LastItem->GetItemName());

				for (TMap<FString, int>::TIterator it = player->InvenMap.CreateIterator(); it; ++it)
				{
					FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);

					AddInvenItem(Widget(Icon(name, player->TmIcons[it->Key])), *player->ItemMap.Find(it->Key));
				}

				LastWidget = NULL;
				return;
			}

			if (LastWidget->type == 0 && LastWidget->pos != StartPos && time <= 0 && LastWidget->Item->GetCheckItem() != 1)
			{
				if (LastWidget->pos.X >= 400)
				{
					if (LastWidget->pos.Y >= 100 && LastWidget->pos.Y < 200)
					{
						if (LastWidget->Item->GetCheckItem() == 2 && FfGun[0].icon.name != "UNKNOWN ICON")
						{
							FfGun[0].Item->SetHoloGram(true);

							player->SetHologram(true, 0);

							LastWidget->pos = FVector2D(400, 110);
							LastWidget->type = 2;

							mGunParts[0] = *LastWidget;

							player->InvenMap.Remove(LastItem->GetItemName());

							EmptyInven();

							for (TMap<FString, int>::TIterator it = player->InvenMap.CreateIterator(); it; ++it)
							{
								FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);

								AddInvenItem(Widget(Icon(name, player->TmIcons[it->Key])), *player->ItemMap.Find(it->Key));
							}

							LastItem->SetActorHiddenInGame(true);
							LastItem->SetActorLocation(FVector(0, 0, -1000));
							LastWidget = NULL;
							return;
						}
						else if (LastWidget->Item->GetCheckItem() == 2 && FfGun[0].icon.name == "UNKNOWN ICON")
						{
							LastWidget->pos = StartPos;
							LastWidget = NULL;
							return;
						}
					}

					if (LastWidget->pos.Y >= 200 && LastWidget->pos.Y < 300)
					{
						if (LastWidget->Item->GetCheckItem() == 2 && FfGun[1].icon.name != "UNKNOWN ICON")
						{
							FfGun[1].Item->SetHoloGram(true);

							player->SetHologram(true, 1);

							LastWidget->pos = FVector2D(400, 210);
							LastWidget->type = 2;

							mGunParts[1] = *LastWidget;

							player->InvenMap.Remove(LastItem->GetItemName());

							EmptyInven();

							for (TMap<FString, int>::TIterator it = player->InvenMap.CreateIterator(); it; ++it)
							{
								FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);

								AddInvenItem(Widget(Icon(name, player->TmIcons[it->Key])), *player->ItemMap.Find(it->Key));
							}

							LastItem->SetActorHiddenInGame(true);
							LastItem->SetActorLocation(FVector(0, 0, -1000));
							LastWidget = NULL;
							return;
						}
						else if (LastWidget->Item->GetCheckItem() == 2 && FfGun[1].icon.name == "UNKNOWN ICON")
						{
							LastWidget->pos = StartPos;
							LastWidget = NULL;
							return;
						}
					}
				}
			}
			LastWidget->pos = StartPos;
			LastWidget = NULL;
			return;
		}
	}
	lastMouse = thisMouse;
}

void ACrossHair::MouseRightClick()
{
	FVector2D mouse;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(mouse.X, mouse.Y);
	LastWidget = NULL;
	LastItem = NULL;

	AMyCharacter* player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		for (int c = 0; c < widgets.Num(); c++)
		{
			if (widgets[c].click(mouse))
			{
				widgets[c].Item->UseItem();
				int value = (int)*player->InvenMap.Find(widgets[c].Item->GetItemName());
				if (value > widgets[c].Item->GetItemCount())
				{
					int a = value - widgets[c].Item->GetItemCount();
					player->InvenMap.Add(widgets[c].Item->GetItemName(), a);
				}
				else
				{
					player->InvenMap.Remove(widgets[c].Item->GetItemName());
				}

				EmptyInven();

				for (TMap<FString, int>::TIterator it = player->InvenMap.CreateIterator(); it; ++it)
				{
					FString name = it->Key + FString::Printf(TEXT(" X %d"), it->Value);
					AddInvenItem(Widget(Icon(name, player->TmIcons[it->Key])), *player->ItemMap.Find(it->Key));
				}
				return;
			}
		}
	}
}

void ACrossHair::GetGunValue(int g_array)
{
	if (FfGun[g_array].icon.name != "UNKNOWN ICON")
	{
		AMyCharacter* player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (player)
		{
			AItem* aa = GetWorld()->SpawnActor<AItem>(FfGun[g_array].Item->GetClass(), player->GetTargetLocation() - FVector(0, 0, player->GetTargetLocation().Z), FRotator(0, 0, 0));
			aa->SetHoloGram(FfGun[g_array].Item->GetHoloGram());

			player->SetHologram(false, g_array);

			mGunParts[g_array] = Widget();

			FfGun[g_array] = Widget();
		}
	}

	return;
}


void ACrossHair::DrawAlignedIcon(const FCanvasIcon & pIcon, const int pX, const int pY, const CrossHairDirection::Type pAlign, const float pScale)
{
	const int lWidth = static_cast<int>(pIcon.UL), lHeight = static_cast<int>(pIcon.VL);
	int lX = -lWidth / 2, lY = -lHeight / 2;
	switch (pAlign)
	{
	case CrossHairDirection::Top:
		lY = -lHeight;
		break;
	case CrossHairDirection::Bottom:
		lY = 0;
		break;
	case CrossHairDirection::Left:
		lX = -lWidth;
		break;
	case CrossHairDirection::Right:
		lX = 0;
		break;
	}
	Canvas->DrawIcon(pIcon, pX + lX, pY + lY, pScale);
}

void ACrossHair::DrawHUD()
{
	Super::DrawHUD();

	int lCrossHairSpread = 32;
	const int lWidth = static_cast<int>(Canvas->ClipX), lHeight = static_cast<int>(Canvas->ClipY);
	const int lCenterX = lWidth / 3 + lWidth / 7, lCenterY = lHeight / 2;

	AMyCharacter* player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		if (!player->GetDoubleZoom() == !InvenDraw)
		{
			Canvas->SetDrawColor(FColor(255, 255, 255, 255));
			for (int i = 0; i < 5; i++)
			{
				int lX = 0, lY = 0;
				switch (i)
				{
				case CrossHairDirection::Top:
					lY = -lCrossHairSpread;
					break;
				case CrossHairDirection::Bottom:
					lY = lCrossHairSpread;
					break;
				case CrossHairDirection::Left:
					lX = -lCrossHairSpread;
					break;
				case CrossHairDirection::Right:
					lX = lCrossHairSpread;
					break;
				}
				DrawAlignedIcon(mCrossHair[i], lCenterX + lX, lCenterY + lY, static_cast<CrossHairDirection::Type>(i));
			}
		}

		if (player->GetHoldBreath())
		{
			float time = 255 / ((player->GetHoldBreathTime() + 1.1));
			Canvas->SetDrawColor(FColor(255, 255 - time, 255 - time, 255));
			Canvas->DrawIcon(mBreath, lCenterX + lWidth / 10, lCenterY + lHeight / 3, 0.5);
		}
		switch (player->GetShootMode())
		{
		case 0:
			SShootMode = "Single | ";
			break;

		case 1:
			SShootMode = "Burst | ";
			break;

		case 2:
			SShootMode = "Auto | ";
			break;

		default:
			SShootMode = "";
			break;
		}
		DrawText(SShootMode + FString::Printf(TEXT("%d | %d"), player->GetBulletCount(), player->GetInvenBulletCount()), FLinearColor::White, lWidth / 2, lHeight * 0.8, mFont, 3.0f, false);
	}

	if (InvenDraw)
	{
		DrawTexture(mInventexture, 150, 100, 125, lHeight - 200, 0, 0, 1, 1);
		DrawTexture(mInventexture, 275, 100, 125, lHeight - 200, 0, 0, 1, 1);
		DrawTexture(mInventexture, 400, 100, 200, 100, 0, 0, 1, 1);
		DrawTexture(mInventexture, 400, 200, 200, 100, 0, 0, 1, 1);
		for (int c = 0; c < widgets.Num(); c++)
		{
			DrawTexture(widgets[c].icon.tex, widgets[c].pos.X, widgets[c].pos.Y, widgets[c].size.X, widgets[c].size.Y, 0, 0, 1, 1);
			DrawText(widgets[c].icon.name, FLinearColor::Black, widgets[c].pos.X + widgets[c].size.X, widgets[c].pos.Y, mFont, 1.2, false);
		}

		for (int c = 0; c < Farmingwidgets.Num(); c++)
		{
			DrawTexture(Farmingwidgets[c].icon.tex, Farmingwidgets[c].pos.X, Farmingwidgets[c].pos.Y, Farmingwidgets[c].size.X, Farmingwidgets[c].size.Y, 0, 0, 1, 1);
			DrawText(Farmingwidgets[c].icon.name, FLinearColor::Black, Farmingwidgets[c].pos.X + Farmingwidgets[c].size.X, Farmingwidgets[c].pos.Y, mFont, 1.2, false);
		}

		if (FfGun[0].icon.name != "UNKNOWN ICON")
		{
			DrawTexture(FfGun[0].icon.tex, FfGun[0].pos.X, FfGun[0].pos.Y, FfGun[0].size.X, FfGun[0].size.Y, 0, 0, 1, 1);
			DrawText(FfGun[0].icon.name, FLinearColor::Black, FfGun[0].pos.X + FfGun[0].size.X, FfGun[0].pos.Y, mFont, 1.2, false);
		}

		if (FfGun[1].icon.name != "UNKNOWN ICON")
		{
			DrawTexture(FfGun[1].icon.tex, FfGun[1].pos.X, FfGun[1].pos.Y, FfGun[1].size.X, FfGun[1].size.Y, 0, 0, 1, 1);
			DrawText(FfGun[1].icon.name, FLinearColor::Black, FfGun[1].pos.X + FfGun[1].size.X, FfGun[1].pos.Y, mFont, 1.2, false);
		}

		if (mGunParts[0].icon.name != "UNKNOWN ICON")
		{
			DrawTexture(mGunParts[0].icon.tex, mGunParts[0].pos.X, mGunParts[0].pos.Y, mGunParts[0].size.X, mGunParts[0].size.Y, 0, 0, 1, 1);
			DrawText(mGunParts[0].icon.name, FLinearColor::Black, mGunParts[0].pos.X + mGunParts[0].size.X, mGunParts[0].pos.Y, mFont, 1.2, false);
		}

		if (mGunParts[1].icon.name != "UNKNOWN ICON")
		{
			DrawTexture(mGunParts[1].icon.tex, mGunParts[1].pos.X, mGunParts[1].pos.Y, mGunParts[1].size.X, mGunParts[1].size.Y, 0, 0, 1, 1);
			DrawText(mGunParts[1].icon.name, FLinearColor::Black, mGunParts[1].pos.X + mGunParts[1].size.X, mGunParts[1].pos.Y, mFont, 1.2, false);
		}
	}
	//widgets.Empty();
}
