#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

AMyPlayer::AMyPlayer()
{
    PrimaryActorTick.bCanEverTick = true;
}

// --- IMPLEMENTACIÓN DE DAÑO ---
void AMyPlayer::TakeCustomDamage(float DamageAmount)
{
    // Restamos el daño a la vida actual
    CurrentHealth -= DamageAmount;

    // Aseguramos que la vida no baje de 0
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

    // Feedback visual en el log para pruebas
    UE_LOG(LogTemp, Warning, TEXT("Vida recibida: %f. Vida actual: %f"), DamageAmount, CurrentHealth);

    // Opcional: Trigger de muerte si llega a 0
    if (CurrentHealth <= 0.0f)
    {
        UE_LOG(LogTemp, Error, TEXT("El jugador ha muerto"));
    }
}

void AMyPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 1. LÓGICA DE CONSUMO / RECUPERACIÓN
    if (bIsSprinting && GetVelocity().Size() > 0.0f && !bIsExhausted)
    {
        CurrentStamina -= 15.0f * DeltaTime;

        if (CurrentStamina <= 0.0f)
        {
            CurrentStamina = 0.0f;
            bIsExhausted = true;
            bIsSprinting = false;

            GetWorld()->GetTimerManager().SetTimer(
                ExhaustionTimerHandle,
                this,
                &AMyPlayer::ResetExhaustion,
                10.0f,
                false
            );
        }
    }
    else if (!bIsExhausted && !bIsSprinting)
    {
        CurrentStamina += 10.0f * DeltaTime;
    }

    CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);

    // 2. CONTROL DE VELOCIDADES
    if (bIsExhausted)
    {
        GetCharacterMovement()->MaxWalkSpeed = 100.0f;
        GetCharacterMovement()->MaxAcceleration = 100.0f;
    }
    else if (bIsSprinting && CurrentStamina > 0.0f)
    {
        GetCharacterMovement()->MaxWalkSpeed = 600.0f;
        GetCharacterMovement()->MaxAcceleration = 2200.0f;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 400.0f;
        GetCharacterMovement()->MaxAcceleration = 2000.0f;
    }
}

void AMyPlayer::ResetExhaustion()
{
    bIsExhausted = false;
}