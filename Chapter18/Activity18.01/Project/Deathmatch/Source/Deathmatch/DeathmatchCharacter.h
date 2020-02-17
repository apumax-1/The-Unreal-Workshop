#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DeathmatchCharacter.generated.h"

UCLASS()
class DEATHMATCH_API ADeathmatchCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Deathmatch Character")
	class UCameraComponent* Camera;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Deathmatch Character")
	float Health = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Deathmatch Character")
	float MaxHealth = 100.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Deathmatch Character")
	float Armor = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Deathmatch Character")
	float MaxArmor = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Deathmatch Character")
	float ArmorAbsorption = 0.5;

	ADeathmatchCharacter();
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
