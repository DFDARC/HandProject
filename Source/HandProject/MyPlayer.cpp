#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h" // Necesario para el temporizador de 10s

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1. LÓGICA DE CONSUMO / RECUERACIÓN
	// Solo gasta si presiona Shift, se está moviendo y NO está agotado
	if (bIsSprinting && GetVelocity().Size() > 0.0f && !bIsExhausted)
	{
		CurrentStamina -= 15.0f * DeltaTime;

		// Si llega a 0, activar castigo de 10 segundos
		if (CurrentStamina <= 0.0f)
		{
			CurrentStamina = 0.0f;
			bIsExhausted = true;
			bIsSprinting = false;

			// Iniciar cronómetro de 10 segundos para resetear bIsExhausted
			GetWorld()->GetTimerManager().SetTimer(
				ExhaustionTimerHandle,
				this,
				&AMyPlayer::ResetExhaustion,
				10.0f,
				false
			);
		}
	}
	// Solo recupera si NO está agotado y NO está intentando correr
	else if (!bIsExhausted && !bIsSprinting)
	{
		CurrentStamina += 10.0f * DeltaTime;
	}

	CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);

	// 2. CONTROL DE VELOCIDADES (Walk Speed y Acceleration)
	if (bIsExhausted)
	{
		// Castigo: Velocidad y aceleración a 100
		GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		GetCharacterMovement()->MaxAcceleration = 100.0f;
	}
	else if (bIsSprinting && CurrentStamina > 0.0f)
	{
		// Sprint: Velocidad base + 200 (ajusta el 600 según tu base)
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GetCharacterMovement()->MaxAcceleration = 2200.0f;
	}
	else
	{
		// Normal: Valores por defecto
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		GetCharacterMovement()->MaxAcceleration = 2000.0f;
	}
}

void AMyPlayer::ResetExhaustion()
{
	bIsExhausted = false;
	// Al ser false, el Tick permitirá que la estamina suba de nuevo
}