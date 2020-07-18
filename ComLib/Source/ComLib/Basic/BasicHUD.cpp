#include "BasicHUD.h"
#include "Asserts.h"
#include "Globals.h"

void ABasicHUD::SetSigthBeadTexture(UTexture* Texture)
{
	if (EnableSigthBead)
	{
		SigthBeadTexture = Texture;
	}
}

void ABasicHUD::SetSigthBeadLinearColor(FLinearColor LinearColor)
{
	if (EnableSigthBead)
	{
		SigthBeadLinearColor = LinearColor;
	}
}

void ABasicHUD::SetSigthBeadBlendMode(EBlendMode BlendMode)
{
	if (EnableSigthBead)
	{
		SigthBeadBlendMode = BlendMode;
	}
}

void ABasicHUD::SetSigthBeadScale(float Scale)
{
	if (EnableSigthBead && UAsserts::IsInRange_float(Scale, 1, 2, true, true))
	{
		SigthBeadScale = Scale;
	}
}


void ABasicHUD::SetSigthBeadRotator(float Rotator)
{
	if (EnableSigthBead && UAsserts::IsInRange_float(Rotator, -180, 180, true, true))
	{
		this->SigthBeadRotator = Rotator;
	}
}

void ABasicHUD::SetSigthBeadRotPivot(FVector2D RotPivot)
{
	if (EnableSigthBead)
	{
		this->SigthBeadRotPivot = RotPivot;
	}
}

ABasicHUD::ABasicHUD()
{
	EnableSigthBead = false;
	SigthBeadTexture = nullptr;
	SigthBeadLinearColor = FLinearColor::Red;
	SigthBeadScale = 1.f;
	SigthBeadRotator = 0.f;
	SigthBeadRotPivot = FVector2D::ZeroVector;

	SigthBeadBlendMode = EBlendMode::BLEND_Translucent;
}
void ABasicHUD::PostInitProperties()
{
	Super::PostInitProperties();
}
void ABasicHUD::DoReceiveDrawHUD(int32 SizeX, int32 SizeY)
{
	if (EnableSigthBead && SigthBeadTexture != nullptr)
	{
		float CenterX = SizeX / 2.f;
		float CenterY = SizeY / 2.f;
		float Width = SigthBeadTexture->GetSurfaceWidth() * SigthBeadScale;
		float Height = SigthBeadTexture->GetSurfaceHeight() * SigthBeadScale;
		if (Width == 0 && Height == 0)
		{
			return;
		}
		float LocationX = CenterX - (Width / 2.f);
		float LocationY = CenterY - (Height / 2.f);
		DrawTexture(SigthBeadTexture, LocationX, LocationY, Width, Height,
			1.f, 1.f, 1.f, 1.f, SigthBeadLinearColor, SigthBeadBlendMode, SigthBeadScale, false, SigthBeadRotator, SigthBeadRotPivot);
	}
}
