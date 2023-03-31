// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "ButtonFloor.h"

#include "Components/SphereComponent.h"

AButtonFloor::AButtonFloor()
{
	ActivationTriggerComponent = CreateDefaultSubobject<USphereComponent>("ActivationTrigger");
	ActivationTriggerComponent->SetupAttachment(GetRootComponent());
	ActivationTriggerComponent->SetupAttachment(GetRootComponent());
	ActivationTriggerComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ActivationTriggerComponent->SetCollisionObjectType(ECC_WorldDynamic);
	ActivationTriggerComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ActivationTriggerComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	bIsReversible = true;
}

void AButtonFloor::BeginPlay()
{
	Super::BeginPlay();

	ActivationTriggerComponent->OnComponentBeginOverlap.
	                            AddDynamic(this, &AButtonFloor::OnActivationTriggerBeginOverlap);
	ActivationTriggerComponent->OnComponentEndOverlap.AddDynamic(this, &AButtonFloor::OnActivationTriggerEndOverlap);
}

void AButtonFloor::InitiatePress()
{
	Press();
}

void AButtonFloor::OnActivationTriggerBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                                  AActor* OtherActor,
                                                                  UPrimitiveComponent* OtherComp,
                                                                  int32 OtherBodyIndex,
                                                                  bool bFromSweep,
                                                                  const FHitResult& SweepResult)
{
	switch (CurrentState)
	{
	case EButtonState::Normal:
	case EButtonState::Pressed:
		if (ButtonPressDelay > 0.f)
		{
			GetWorldTimerManager().SetTimer(ButtonPressDelayTimer,
			                                this,
			                                &AButtonFloor::InitiatePress,
			                                ButtonPressDelay);
			return;
		}

		Press();
		break;

	case EButtonState::Transition:
		if (bIsReversible)
		{
			Press();
		}

	default:
		break;
	}
}

void AButtonFloor::OnActivationTriggerEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                                AActor* OtherActor,
                                                                UPrimitiveComponent* OtherComp,
                                                                int32 OtherBodyIndex)
{
	if (ButtonPressDelay > 0.f && GetWorldTimerManager().IsTimerActive(ButtonPressDelayTimer))
	{
		GetWorldTimerManager().ClearTimer(ButtonPressDelayTimer);
		return;
	}

	switch (CurrentState)
	{
	case EButtonState::Transition:
		if (bIsReversible)
		{
			Press();
		}
		break;

	default:
		break;
	}
}
