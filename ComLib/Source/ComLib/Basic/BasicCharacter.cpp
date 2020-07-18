#include "BasicCharacter.h"
#include "Maths.h"
#include "Functions.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ABasicCharacter

ABasicCharacter::ABasicCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	ControlMethod = ECharacterControlType::FPS;
	// SpeedSwitch
	EnableSpeedSwitch = true;
	ToQuietlySpeedEventName = "ToQuietlyMoving";
	ToRunningSpeedEventName = "ToRunningMoving";
	QuietingSpeed = 100;
	WalkingSpeed = 300;
	RunningSpeed = 600;
	GetCharacterMovement()->MaxWalkSpeedCrouched = QuietingSpeed;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	//Moving
	EnableComputerMoving = true;
	FrontBackMovingEventName = "MoveForward";
	LeftRightMovingEventName = "MoveRight";
	//Looking
	EnableComputerLooking = true;
	UpDownlookingEventName = "LookUp";
	LeftRightlookingEventName = "Turn";
	//RateLooking
	EnableComputerRatelooking = true;
	UpDownRatelookingEventName = "LookUpRate";
	LeftRightRatelookingEventName = "TurnRate";
	// set our turn rates for input
	LeftRightLookingRate = 45.f;
	UpDownLookingRate = 45.f;
	//Jump
	EnableComputerJumping = true;
	JumpingEventName = "Jump";
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	//Crouch
	EnableComputerCrouching = true;
	StartCrouchingEventName = "Crouch";
	EndCrouchingEventName = "UnCrouch";
	//Crawl
	EnableComputerCrawling = false;
	StartCrawlingEventName = "Crawl";
	EndCrawlingEventName = "UnCrawl";
	//Moblie Look
	EnableMoblieLooking = true;
	MoblieLookingRate = 0.5f;
	//Moblie Move
	EnableMoblieMoving = true;

	ExpectStatus = ECharacterStatus::IDLE;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Interal initital
	MTOCR_AllowRightControl = false;
	MTOCR_IsRightStart = false;
	MTOCR_RightRepeatLastPoint = FVector::ZeroVector;
	MTOCR_SaveRightFingerIndex = ETouchIndex::Type::CursorPointerIndex;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABasicCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (EnableSpeedSwitch)
	{
		PlayerInputComponent->BindAction(ToQuietlySpeedEventName, IE_Pressed, this, &ABasicCharacter::E_StartToQuietlySpeed);
		PlayerInputComponent->BindAction(ToQuietlySpeedEventName, IE_Released, this, &ABasicCharacter::E_EndToQuietlySpeed);
		PlayerInputComponent->BindAction(ToRunningSpeedEventName, IE_Pressed, this, &ABasicCharacter::E_StartToRunningSpeed);
		PlayerInputComponent->BindAction(ToRunningSpeedEventName, IE_Released, this, &ABasicCharacter::E_EndToRunningSpeed);
	}
	switch (ControlMethod)
	{
	case ECharacterControlType::FPS:
		if (EnableComputerMoving)
		{
			PlayerInputComponent->BindAxis(FrontBackMovingEventName, this, &ABasicCharacter::E_FPS_FrontBackMoving);
			PlayerInputComponent->BindAxis(LeftRightMovingEventName, this, &ABasicCharacter::E_FPS_LeftRightMoving);
		}
		if (EnableComputerLooking)
		{
			PlayerInputComponent->BindAxis(UpDownlookingEventName, this, &ABasicCharacter::E_FPS_UpDownlooking);
			PlayerInputComponent->BindAxis(LeftRightlookingEventName, this, &ABasicCharacter::E_FPS_LeftRightlooking);
		}
		if (EnableComputerRatelooking)
		{
			PlayerInputComponent->BindAxis(UpDownRatelookingEventName, this, &ABasicCharacter::E_FPS_UpDownRatelooking);
			PlayerInputComponent->BindAxis(LeftRightRatelookingEventName, this, &ABasicCharacter::E_FPS_LeftRightRatelooking);
		}
		if (EnableComputerJumping)
		{
			PlayerInputComponent->BindAction(JumpingEventName, IE_Pressed, this, &ABasicCharacter::E_FPS_StartJumping);
			PlayerInputComponent->BindAction(JumpingEventName, IE_Released, this, &ABasicCharacter::E_FPS_EndJumping);
		}
		if (EnableComputerCrouching)
		{
			PlayerInputComponent->BindAction(StartCrouchingEventName, IE_Pressed, this, &ABasicCharacter::E_FPS_StartCrouching);
			PlayerInputComponent->BindAction(EndCrouchingEventName, IE_Pressed, this, &ABasicCharacter::E_FPS_EndCrouching);
		}
		if (EnableComputerCrawling)
		{
			PlayerInputComponent->BindAction(StartCrawlingEventName, IE_Pressed, this, &ABasicCharacter::E_FPS_StartCrawling);
			PlayerInputComponent->BindAction(EndCrawlingEventName, IE_Pressed, this, &ABasicCharacter::E_FPS_EndCrawling);
		}
		break;
	case ECharacterControlType::MOBILE_TOUCH_ONLY_CONTROL_ROTATION:
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABasicCharacter::E_MTOCR_Pressed);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ABasicCharacter::E_MTOCR_Released);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABasicCharacter::E_MTOCR_Repeat);
		break;
	case ECharacterControlType::MOBILE_TOUCH_CONTROL_ROTATION_AND_MOVING:
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABasicCharacter::E_MTCRAM_Pressed);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ABasicCharacter::E_MTCRAM_Released);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABasicCharacter::E_MTCRAM_Repeat);
		break;
	default:
		break;
	}
}

void ABasicCharacter::StartQuietly()
{
	E_StartToQuietlySpeed();
}

void ABasicCharacter::EndQuietly()
{
	E_EndToQuietlySpeed();
}

void ABasicCharacter::StartRunning()
{
	E_StartToRunningSpeed();
}

void ABasicCharacter::EndRunning()
{
	E_EndToRunningSpeed();
}

void ABasicCharacter::E_StartToQuietlySpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = QuietingSpeed;
	ExpectStatus = ECharacterStatus::QUIET_MOVING;
}

void ABasicCharacter::E_EndToQuietlySpeed()
{
	if (ExpectStatus == ECharacterStatus::QUIET_MOVING)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		ExpectStatus = ECharacterStatus::WALK_MOVING;
	}
}

void ABasicCharacter::E_StartToRunningSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	ExpectStatus = ECharacterStatus::RUN_MOVING;
}

void ABasicCharacter::E_EndToRunningSpeed()
{
	if (ExpectStatus == ECharacterStatus::RUN_MOVING)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		ExpectStatus = ECharacterStatus::WALK_MOVING;
	}
}

void ABasicCharacter::E_FPS_FrontBackMoving(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABasicCharacter::E_FPS_LeftRightMoving(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABasicCharacter::E_FPS_UpDownlooking(float Value)
{
	AddControllerPitchInput(Value);
}

void ABasicCharacter::E_FPS_LeftRightlooking(float Value)
{
	AddControllerYawInput(Value);
}

void ABasicCharacter::E_FPS_UpDownRatelooking(float Value)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Value * UpDownLookingRate * GetWorld()->GetDeltaSeconds());
}

void ABasicCharacter::E_FPS_LeftRightRatelooking(float Value)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Value * LeftRightLookingRate * GetWorld()->GetDeltaSeconds());
}

void ABasicCharacter::E_FPS_StartJumping()
{
	Jump();
}

void ABasicCharacter::E_FPS_EndJumping()
{
	StopJumping();
}

void ABasicCharacter::E_FPS_StartCrouching()
{
	Crouch();
}

void ABasicCharacter::E_FPS_EndCrouching()
{
	UnCrouch();
}

void ABasicCharacter::E_FPS_StartCrawling()
{
	//TO DO
}

void ABasicCharacter::E_FPS_EndCrawling()
{
	//TO DO
}

void ABasicCharacter::E_MTOCR_Pressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (!EnableMoblieLooking)return;
	//When it's not activated for right
	if (!MTOCR_AllowRightControl)
	{
		FVector2D ScreenLocation(Location.X, Location.Y);
		bool IsRightHalfScreen = !UFunctions::IsLeftHalfScreen(GetWorld(), ScreenLocation);
		if (IsRightHalfScreen)
		{
			MTOCR_SaveRightFingerIndex = FingerIndex;
			MTOCR_AllowRightControl = true;
		}
	}
}

void ABasicCharacter::E_MTOCR_Released(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (!EnableMoblieLooking)return;
	//When it's activated and match finger index  for right
	if (MTOCR_AllowRightControl && FingerIndex == MTOCR_SaveRightFingerIndex)
	{
		MTOCR_IsRightStart = false;
		MTOCR_AllowRightControl = false;
	}
}

void ABasicCharacter::E_MTOCR_Repeat(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (!EnableMoblieLooking)return;
	if (MTOCR_AllowRightControl && FingerIndex == MTOCR_SaveRightFingerIndex)
	{
		if (!MTOCR_IsRightStart)
		{
			MTOCR_RightRepeatLastPoint = Location;
			MTOCR_IsRightStart = true;
			return;
		}
		FVector UnitVactor = UMaths::CalculateUnitVector(Location, MTOCR_RightRepeatLastPoint);
		MTOCR_RightRepeatLastPoint = Location;
		E_FPS_LeftRightlooking(UnitVactor.X * MoblieLookingRate);
		E_FPS_UpDownlooking(UnitVactor.Y * MoblieLookingRate);
	}
}

void ABasicCharacter::E_MTCRAM_Pressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	E_MTOCR_Pressed(FingerIndex, Location);
	if (!EnableMoblieMoving)return;
	//TO DO
}

void ABasicCharacter::E_MTCRAM_Released(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	E_MTOCR_Released(FingerIndex, Location);
	if (!EnableMoblieMoving)return;
	//TO DO
}

void ABasicCharacter::E_MTCRAM_Repeat(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	E_MTOCR_Repeat(FingerIndex, Location);
	if (!EnableMoblieMoving)return;
	//TO DO
}