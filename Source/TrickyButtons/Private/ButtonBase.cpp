// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "ButtonBase.h"

AButtonBase::AButtonBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
}

void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

