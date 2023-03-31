// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "ButtonInteractive.h"

#include "Components/SphereComponent.h"

AButtonInteractive::AButtonInteractive()
{
	InteractionTriggerComponent = CreateDefaultSubobject<USphereComponent>("InteractionTrigger");
	InteractionTriggerComponent->SetupAttachment(GetRootComponent());
	InteractionData.bRequireLineOfSight = true;
}

void AButtonInteractive::BeginPlay()
{
	Super::BeginPlay();

	InteractionTriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AButtonInteractive::OnInteractionTriggerBeginOverlap);
	InteractionTriggerComponent->OnComponentEndOverlap.AddDynamic(this, &AButtonInteractive::OnInteractionTriggerEndOverlap);
}

void AButtonInteractive::StartInteraction_Implementation(AActor* OtherActor)
{
	if (bIsReversible)
	{
		Press();
	}
}

bool AButtonInteractive::FinishInteraction_Implementation(AActor* OtherActor)
{
	return Press();
}

void AButtonInteractive::StopInteraction_Implementation(AActor* OtherActor)
{
	if (CurrentState != EButtonState::Transition)
	{
		return;
	}

	if (bIsReversible)
	{
		Press();
	}
}

void AButtonInteractive::OnInteractionTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                          AActor* OtherActor,
                                                          UPrimitiveComponent* OtherComp,
                                                          int32 OtherBodyIndex,
                                                          bool bFromSweep,
                                                          const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	UInteractionLibrary::AddToInteractionQueue(OtherActor, this, InteractionData);
}

void AButtonInteractive::OnInteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                        AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp,
                                                        int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	UInteractionLibrary::RemoveFromInteractionQueue(OtherActor, this);
}
