// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimelineAnimationComponent.h"
#include "ButtonBase.generated.h"


UENUM(BlueprintType)
enum class EButtonState : uint8
{
	Normal,
	Transition,
	Pressed,
	Disabled
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChangedSignature, EButtonState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReversedSignature);

/**
 * A base button class with the most basic functionality.
 */
UCLASS()
class TRICKYBUTTONS_API AButtonBase : public AActor
{
	GENERATED_BODY()

public:
	AButtonBase();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category="Button")
	FOnStateChangedSignature OnStateChanged;

	UPROPERTY(BlueprintAssignable, Category="Button")
	FOnButtonReversedSignature OnReversed;

	/**
	 * Toggles if the button enabled or disabled.
	 */
	UFUNCTION(BlueprintCallable, Category="Button")
	void SetIsEnabled(const bool bIsEnabled);

	/**
	 * Initiates button logic.
	 */
	UFUNCTION(BlueprintCallable, Category="Button")
	bool Press();

protected:
	/**
	 * Called when the button changed state.
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<USceneComponent> ButtonRootComponent = nullptr;

	/**
	 * Called when the button animation was reversed.
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UTimelineAnimationComponent> ButtonAnimationComponent = nullptr;

	/**
	 * The initial state of the button.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button", meta=(AllowPrivateAccess))
	EButtonState InitialState = EButtonState::Normal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Button", meta=(AllowPrivateAccess))
	EButtonState CurrentState = EButtonState::Normal;

	UPROPERTY(BlueprintReadOnly, Category="Button", meta=(AllowPrivateAccess))
	EButtonState PreviousState = EButtonState::Normal;

	/**
	 * Toggles if the button animation can be reversed.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button", meta=(AllowPrivateAccess))
	bool bIsReversible = false;

	/**
	 * If true, the button will stay in the pressed state for some time.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button", meta=(AllowPrivateAccess))
	bool bIsPressedTemporary = false;

	/**
	 * How long the button will state in pressed state.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Button",
		meta=(AllowPrivateAccess, EditCondition="bIsPressedTemporary", ClampMin="0"))
	float PressedStateDuration = 0.f;

	UPROPERTY(BlueprintReadOnly, Category="Button")
	FTimerHandle PressedStateDurationTimer;

	/**
	 * Called when the button changed its current state.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonStateChanged(EButtonState NewState);

	/**
	 * Called when the button animation was reversed.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonReversed();

	/**
	 * Called when the button was disabled.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonDisabled();

	/**
	 * Called when the button was enabled.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonEnabled();

	UFUNCTION()
	void ChangeState(const ETimelineAnimationState NewAnimationState);

private:
	void Press_Wrapper();
};
