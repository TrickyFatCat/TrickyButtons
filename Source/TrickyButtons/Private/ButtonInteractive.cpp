// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "ButtonInteractive.h"

#include "InteractionTriggers/SphereInteractionTrigger.h"

AButtonInteractive::AButtonInteractive()
{
	InteractionTrigger = CreateDefaultSubobject<USphereInteractionTrigger>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
}

void AButtonInteractive::BeginPlay()
{
	Super::BeginPlay();
}

bool AButtonInteractive::Interact_Implementation(AActor* OtherActor)
{
	return Press();
}
