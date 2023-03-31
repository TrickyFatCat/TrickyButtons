// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "ButtonBase.h"
#include "TimelineAnimationComponent.h"
#include "TimerManager.h"

AButtonBase::AButtonBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ButtonRootComponent = CreateDefaultSubobject<USceneComponent>("ButtonRoot");
	SetRootComponent(ToRawPtr(ButtonRootComponent));

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

	case EButtonState::Transition:
		InitialState = EButtonState::Normal;
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

	if (CurrentState == EButtonState::Disabled)
	{
		PreviousState = EButtonState::Normal;
		SetIsEnabled(false);
	}
}

void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AButtonBase::SetIsEnabled(const bool bIsEnabled)
{
	if (bIsEnabled && CurrentState == EButtonState::Disabled)
	{
		CurrentState = PreviousState;
	}
	else if (!bIsEnabled && CurrentState != EButtonState::Disabled)
	{
		PreviousState = CurrentState;
		CurrentState = EButtonState::Disabled;
	}

	bIsEnabled ? OnButtonEnabled() : OnButtonDisabled();

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

bool AButtonBase::Press()
{
	bool bIsSuccess = false;

	switch (CurrentState)
	{
	case EButtonState::Normal:
	case EButtonState::Pressed:
		CurrentState = EButtonState::Transition;
		ButtonAnimationComponent->Start();
		OnButtonStateChanged(CurrentState);
		OnStateChanged.Broadcast(CurrentState);
		bIsSuccess = true;
		break;

	case EButtonState::Transition:
		if (bIsReversible)
		{
			ButtonAnimationComponent->Reverse();
			OnButtonReversed();
			OnReversed.Broadcast();
			bIsSuccess = true;
		}
		break;

	default:
		break;
	}

	return bIsSuccess;
}

void AButtonBase::ChangeState(const ETimelineAnimationState NewAnimationState)
{
	PreviousState = CurrentState;

	switch (NewAnimationState)
	{
	case ETimelineAnimationState::Begin:
		CurrentState = EButtonState::Normal;
		OnButtonStateChanged(CurrentState);
		OnStateChanged.Broadcast(CurrentState);
		break;

	case ETimelineAnimationState::End:
		CurrentState = EButtonState::Pressed;
		OnButtonStateChanged(CurrentState);
		OnStateChanged.Broadcast(CurrentState);
		
		if (bIsPressedTemporary)
		{
			GetWorldTimerManager().SetTimer(PressedStateDurationTimer,
			                                this,
			                                &AButtonBase::Press_Wrapper,
			                                PressedStateDuration);
			SetIsEnabled(false);
		}
		break;

	default:
		break;
	}
}

void AButtonBase::Press_Wrapper()
{
	SetIsEnabled(true);
	Press();
}
