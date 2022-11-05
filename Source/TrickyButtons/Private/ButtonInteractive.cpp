// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "ButtonInteractive.h"

#include "InteractionTriggers/SphereInteractionTrigger.h"

AButtonInteractive::AButtonInteractive()
{
	InteractionTrigger = CreateDefaultSubobject<USphereInteractionTrigger>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
	InteractionTrigger->SetInteractionSettings(FInteractionData{this, true, "Interact", 0, 0.f, true});
}

void AButtonInteractive::BeginPlay()
{
	Super::BeginPlay();
}

void AButtonInteractive::StartInteraction_Implementation(AActor* OtherActor)
{
	if (bIsReversible && !InteractionTrigger->GetInteractionSettings().bCallInteractFunction)
	{
		Press();
	}
}

bool AButtonInteractive::Interact_Implementation(AActor* OtherActor)
{
	return Press();
}

void AButtonInteractive::StopInteraction_Implementation(AActor* OtherActor)
{
	if (CurrentState != EButtonState::Transition)
	{
		return;
	}

	if (bIsReversible && !InteractionTrigger->GetInteractionSettings().bCallInteractFunction)
	{
		Press();
	}
}
