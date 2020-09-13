// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
#include "Item.h"

#include "CoreMinimal.h"

struct Icon 
{
	FString name;    
	UTexture2D* tex;  

	Icon() 
	{ 
		name = "UNKNOWN ICON"; 
		tex = 0; 
	}    

	Icon(FString& iName, UTexture2D* iTex)
	{ 
		name = iName;        
		tex = iTex; 
	} 
};

struct Widget 
{ 
	Icon icon;   
	FVector2D pos, size, start;
	AItem* Item;
	Widget(Icon iicon) { icon = iicon; } 
	float left() { return pos.X; }
	float right() { return pos.X + size.X * 3.5; }
	float top() { return pos.Y; }  
	float bottom() { return pos.Y + size.Y; } 
	int type;
	bool click(FVector2D g_Click)
	{
		return g_Click.X > left() && g_Click.X < right() && g_Click.Y > top() && g_Click.Y < bottom();
	}

	Widget() {}
};

/**
 * 
 */
class PUBG_API StructHeader
{
public:
	StructHeader();
	~StructHeader();
};
