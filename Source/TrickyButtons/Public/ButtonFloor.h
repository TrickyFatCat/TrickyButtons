// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "ButtonBase.h"
#include "ButtonFloor.generated.h"

class USphereComponent;

/**
 * A button which activated via a trigger. Good for buttons on floor.
 */
UCLASS()
class TRICKYBUTTONS_API AButtonFloor : public AButtonBase
{
	GENERATED_BODY()

public:
	AButtonFloor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereComponent> ActivationTriggerComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Button", meta=(ClampMin="0"))
	float ButtonPressDelay = 0.f;

public:
	UFUNCTION()
	void InitiatePress();

protected:
	UPROPERTY(BlueprintReadOnly, Category="Button")
	FTimerHandle ButtonPressDelayTimer;

	UFUNCTION(BlueprintNativeEvent, Category="Button")
	void OnActivationTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                     AActor* OtherActor,
	                                     UPrimitiveComponent* OtherComp,
	                                     int32 OtherBodyIndex,
	                                     bool bFromSweep,
	                                     const FHitResult& SweepResult);

	virtual void OnActivationTriggerBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
	                                                            AActor* OtherActor,
	                                                            UPrimitiveComponent* OtherComp,
	                                                            int32 OtherBodyIndex,
	                                                            bool bFromSweep,
	                                                            const FHitResult& SweepResult);


	UFUNCTION(BlueprintNativeEvent, Category="Button")
	void OnActivationTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
	                                   AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp,
	                                   int32 OtherBodyIndex);
	
	void OnActivationTriggerEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
	                                                 AActor* OtherActor,
	                                                 UPrimitiveComponent* OtherComp,
	                                                 int32 OtherBodyIndex);
};
