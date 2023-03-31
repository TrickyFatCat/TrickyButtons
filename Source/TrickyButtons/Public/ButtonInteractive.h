// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "ButtonBase.h"
#include "InteractionInterface.h"
#include "InteractionLibrary.h"
#include "ButtonInteractive.generated.h"

class USphereComponent;

/**
 * A button which requires interaction. Good for levers, switches, valves, etc.
 */
UCLASS()
class TRICKYBUTTONS_API AButtonInteractive : public AButtonBase, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AButtonInteractive();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Button")
	FInteractionData InteractionData;

	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<USphereComponent> InteractionTriggerComponent = nullptr;

private:
	virtual void StartInteraction_Implementation(AActor* OtherActor) override;

	virtual bool FinishInteraction_Implementation(AActor* OtherActor) override;

	virtual void StopInteraction_Implementation(AActor* OtherActor) override;

	UFUNCTION()
	void OnInteractionTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                      AActor* OtherActor,
	                                      UPrimitiveComponent* OtherComp,
	                                      int32 OtherBodyIndex,
	                                      bool bFromSweep,
	                                      const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
	                                    AActor* OtherActor,
	                                    UPrimitiveComponent* OtherComp,
	                                    int32 OtherBodyIndex);
};
