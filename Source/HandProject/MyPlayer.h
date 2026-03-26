#pragma once

#include "CoreMinimal.h"
#include "HandProjectCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayer.generated.h"

UCLASS()
class HANDPROJECT_API AMyPlayer : public AHandProjectCharacter
{
	GENERATED_BODY()

public:
	AMyPlayer();

	// --- ESTAMINA ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurrentStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina = 100.0f;

	// --- VIDA ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	// --- FUNCIÓN DE DAÑO ---
	// La marcamos como BlueprintCallable para poder usarla en tus nodos de Blueprints
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeCustomDamage(float DamageAmount);

	// --- LÓGICA DE MOVIMIENTO Y SPRINT ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	bool bIsSprinting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	bool bIsExhausted = false;

	void ResetExhaustion();

protected:
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ExhaustionTimerHandle;
};