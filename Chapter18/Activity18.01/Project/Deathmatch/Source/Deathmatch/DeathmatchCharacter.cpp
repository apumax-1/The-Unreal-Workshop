#include "DeathmatchCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADeathmatchCharacter::ADeathmatchCharacter()
{
	// Initialize the camera component and attach it to the skeletal mesh in the Camera socket

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetMesh(), "Camera");

	// Set the max walk speed to 800 and the jump z velocity to 600

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	// This character doesn’t need to tick

	PrimaryActorTick.bCanEverTick = false;
}

void ADeathmatchCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Only the authority can go from this point on

	if (!HasAuthority())
		return;

	// Initialize Health with the value of MaxHealth

	SetHealth(MaxHealth);
}

void ADeathmatchCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the action mappings

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADeathmatchCharacter::OnPressedJump);

	// Bind the axis mappings

	PlayerInputComponent->BindAxis("Move Forward", this, &ADeathmatchCharacter::OnAxisMoveForward);
	PlayerInputComponent->BindAxis("Move Right", this, &ADeathmatchCharacter::OnAxisMoveRight);
	PlayerInputComponent->BindAxis("Look Up", this, &ADeathmatchCharacter::OnAxisLookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ADeathmatchCharacter::OnAxisTurn);
}

void ADeathmatchCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ADeathmatchCharacter, Health, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ADeathmatchCharacter, Armor, COND_OwnerOnly);
}

void ADeathmatchCharacter::OnPressedJump()
{
	Jump();
}

void ADeathmatchCharacter::OnAxisMoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ADeathmatchCharacter::OnAxisMoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ADeathmatchCharacter::OnAxisLookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ADeathmatchCharacter::OnAxisTurn(float Value)
{
	AddControllerYawInput(Value);
}

void ADeathmatchCharacter::ArmorAbsorbDamage(float& Damage)
{
	// Calculate how much damage was absorbed and subtract that from the Armor

	const float AbsorbedDamage = Damage * ArmorAbsorption;
	const float RemainingArmor = Armor - AbsorbedDamage;

	SetArmor(RemainingArmor);

	// Recalculate the damage

	Damage = (Damage * (1 - ArmorAbsorption)) - FMath::Min(RemainingArmor, 0.0f);
}
