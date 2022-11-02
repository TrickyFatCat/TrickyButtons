// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "ButtonBase.h"
#include "TimelineAnimationComponent.h"

AButtonBase::AButtonBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ButtonRootComponent = CreateDefaultSubobject<USceneComponent>("ButtonRoot");
	SetRootComponent(ButtonRootComponent);

	ButtonAnimationComponent = CreateDefaultSubobject<UTimelineAnimationComponent>("ButtonAnimation");
}

void AButtonBase::OnConstruction(const FTransform& Transform)
{
	switch (InitialState)
	{
	case EButtonState::Normal:
		ButtonAnimationComponent->InitialState = ETimelineAnimationState::Begin;
		break;

	case EButtonState::Pressed:
		ButtonAnimationComponent->InitialState = ETimelineAnimationState::End;
		break;

	default:
		break;
	}
	
	Super::OnConstruction(Transform);
}

void AButtonBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentState = InitialState;
	PreviousState = CurrentState;

	ButtonAnimationComponent->OnAnimationFinished.AddDynamic(this, &AButtonBase::ChangeState);
}

void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AButtonBase::SetIsEnabled(const bool bIsEnabled)
{
	CurrentState = bIsEnabled ? PreviousState : EButtonState::Disabled;

	switch (CurrentState)
	{
	case EButtonState::Transition:
		if (ButtonAnimationComponent->GetCurrentState() == ETimelineAnimationState::Pause)
		{
			ButtonAnimationComponent->Resume();
		}
		break;

	case EButtonState::Disabled:
		if (ButtonAnimationComponent->GetCurrentState() == ETimelineAnimationState::Transition)
		{
			ButtonAnimationComponent->Pause();
		}
		break;

	default:
		break;
	}
}

void AButtonBase::Press()
{
	switch (CurrentState)
	{
	case EButtonState::Normal:
	case EButtonState::Pressed:
		CurrentState = EButtonState::Transition;
		ButtonAnimationComponent->Start();
		break;

	case EButtonState::Transition:
		if (bIsReversible)
		{
			ButtonAnimationComponent->Reverse();
		}
		break;

	default:
		break;
	}
}

void AButtonBase::ChangeState(const ETimelineAnimationState NewAnimationState)
{
	PreviousState = CurrentState;

	switch (NewAnimationState)
	{
	case ETimelineAnimationState::Begin:
		CurrentState = EButtonState::Normal;
		break;

	case ETimelineAnimationState::End:
		CurrentState = EButtonState::Pressed;
		break;

	default:
		break;
	}
}
