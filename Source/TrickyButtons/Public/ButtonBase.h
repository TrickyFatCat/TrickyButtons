// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimelineAnimationComponent.h"
#include "ButtonBase.generated.h"

class UTimelineAnimationComponent;

UENUM(BlueprintType)
enum class EButtonState : uint8
{
	Normal,
	Transition UMETA(Hidden),
	Pressed,
	Disabled
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChangedSignature, EButtonState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReversedSignature);

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
	FOnReversedSignature OnReversed;
	
	UFUNCTION(BlueprintCallable, Category="Button")
	void SetIsEnabled(const bool bIsEnabled);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* ButtonRootComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTimelineAnimationComponent* ButtonAnimationComponent = nullptr;
	
	UFUNCTION(BlueprintCallable, Category="Button")
	bool Press();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonStateChanged(EButtonState NewState);
	
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonReversed();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonDisabled();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Button")
	void OnButtonEnabled();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button", meta=(AllowPrivateAccess))
	EButtonState InitialState = EButtonState::Normal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Button", meta=(AllowPrivateAccess))
	EButtonState CurrentState = EButtonState::Normal;

	UPROPERTY(BlueprintReadOnly, Category="Button", meta=(AllowPrivateAccess))
	EButtonState PreviousState = EButtonState::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button", meta=(AllowPrivateAccess))
	bool bIsReversible = false;

	UFUNCTION()
	void ChangeState(const ETimelineAnimationState NewAnimationState);
};
