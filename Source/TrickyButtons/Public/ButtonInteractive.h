// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "ButtonBase.h"
#include "InteractionInterface.h"
#include "ButtonInteractive.generated.h"

class USphereInteractionTrigger;

/**
 * 
 */
UCLASS()
class TRICKYBUTTONS_API AButtonInteractive : public AButtonBase, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AButtonInteractive();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereInteractionTrigger* InteractionTrigger = nullptr;

private:
	virtual bool Interact_Implementation(AActor* OtherActor) override;
};
