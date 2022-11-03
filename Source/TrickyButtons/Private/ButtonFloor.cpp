// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


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
}

void AButtonFloor::BeginPlay()
{
	Super::BeginPlay();

	ActivationTriggerComponent->OnComponentBeginOverlap.
	                            AddDynamic(this, &AButtonFloor::OnActivationTriggerBeginOverlap);
	ActivationTriggerComponent->OnComponentEndOverlap.AddDynamic(this, &AButtonFloor::OnActivationTriggerEndOverlap);
}

void AButtonFloor::OnActivationTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
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
		Press();
		break;
	}
}

void AButtonFloor::OnActivationTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                 AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp,
                                                 int32 OtherBodyIndex)
{
	switch (CurrentState)
	{
	case EButtonState::Transition:
		if (bIsReversible)
		{
			Press();
		}
		break;
	}
}