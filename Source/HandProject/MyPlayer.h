#pragma once

#include "CoreMinimal.h"
#include "HandProjectCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" // Necesario para modificar velocidades
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

	// --- LÓGICA DE MOVIMIENTO Y SPRINT ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	bool bIsSprinting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	bool bIsExhausted = false;

	// Función para resetear el estado de agotamiento tras los 10 segundos
	void ResetExhaustion();

protected:
	virtual void Tick(float DeltaTime) override;

private:
	// Manejador para el temporizador de 10 segundos
	FTimerHandle ExhaustionTimerHandle;
};