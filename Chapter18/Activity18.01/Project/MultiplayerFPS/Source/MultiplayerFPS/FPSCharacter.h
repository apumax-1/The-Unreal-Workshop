#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class MULTIPLAYERFPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPS Character")
	class UCameraComponent* Camera;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPS Character")
	float Health = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	float MaxHealth = 100.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPS Character")
	float Armor = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	float MaxArmor = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	float ArmorAbsorption = 0.5;

	AFPSCharacter();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnPressedJump();
	void OnAxisMoveForward(float Value);
	void OnAxisMoveRight(float Value);
	void OnAxisLookUp(float Value);
	void OnAxisTurn(float Value);

	void AddHealth(float Amount) { SetHealth(Health + Amount); }
	void RemoveHealth(float Amount) { SetHealth(Health - Amount); }
	void SetHealth(float NewHealth) { Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth); }
	bool IsDead() const { return Health == 0.0f; }

	void AddArmor(float Amount) { SetArmor(Armor + Amount); }
	void SetArmor(float Amount) { Armor = FMath::Clamp(Amount, 0.0f, MaxArmor); }
	void ArmorAbsorbDamage(float& Damage);

};
