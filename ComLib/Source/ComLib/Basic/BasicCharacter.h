
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterControlType :uint8
{
	NONE UMETA(DisplayName = "None Control"),
	FPS UMETA(DisplayName = "FPS Control Method"),
	MOBILE_TOUCH_ONLY_CONTROL_ROTATION UMETA(DisplayName = "Mobile Touch Only Control Rotation"),
	MOBILE_TOUCH_CONTROL_ROTATION_AND_MOVING UMETA(DisplayName = "Mobile Touch Control Rotation And Moving"),
};
UENUM(BlueprintType)
enum class ECharacterStatus :uint8
{
	CRAWL,
	CRAWL_MOVING,
	CROUCH,
	CROUCH_MOVING,
	JUMP,
	JUMP_MOVING,
	IDLE,
	QUIET_MOVING,
	WALK_MOVING,
	RUN_MOVING,
	OTHER,
};

UCLASS(config = Game)
class ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	ABasicCharacter();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected://Control Frame

	UPROPERTY(EditAnywhere, Category = "Control")
		ECharacterControlType ControlMethod;

	//SpeedSwitch

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod != ECharacterControlType::NONE"))
		bool EnableSpeedSwitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control", meta = (EditCondition = "ControlMethod != ECharacterControlType::NONE && EnableSpeedSwitch"))
		float WalkingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control", meta = (EditCondition = "ControlMethod != ECharacterControlType::NONE && EnableSpeedSwitch"))
		float QuietingSpeed;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod != ECharacterControlType::NONE && EnableSpeedSwitch"))
		FName ToQuietlySpeedEventName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control", meta = (EditCondition = "ControlMethod != ECharacterControlType::NONE && EnableSpeedSwitch"))
		float RunningSpeed;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod != ECharacterControlType::NONE && EnableSpeedSwitch"))
		FName ToRunningSpeedEventName;

	//ComputerMoving

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS"))
		bool EnableComputerMoving;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerMoving"))
		FName FrontBackMovingEventName;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerMoving"))
		FName LeftRightMovingEventName;

	//ComputerLooking

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS"))
		bool EnableComputerLooking;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerlooking"))
		FName UpDownlookingEventName;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerlooking"))
		FName LeftRightlookingEventName;

	//ComputerRatelooking

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS"))
		bool EnableComputerRatelooking;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerRatelooking"))
		FName UpDownRatelookingEventName;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerRatelooking"))
		FName LeftRightRatelookingEventName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0", UIMin = "0", EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerRatelooking"))
		float LeftRightLookingRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0", UIMin = "0", EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerRatelooking"))
		float UpDownLookingRate;

	//ComputerJumping

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS"))
		bool EnableComputerJumping;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerJumping"))
		FName JumpingEventName;

	//ComputerCrouching

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS"))
		bool EnableComputerCrouching;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerCrouching"))
		FName StartCrouchingEventName;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerCrouching"))
		FName EndCrouchingEventName;

	//ComputerCrawling

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS"))
		bool EnableComputerCrawling;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerCrawling"))
		FName StartCrawlingEventName;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::FPS && EnableComputerCrawling"))
		FName EndCrawlingEventName;

	//MoblieLooking

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::MOBILE_TOUCH_ONLY_CONTROL_ROTATION || ControlMethod == ECharacterControlType::MOBILE_TOUCH_CONTROL_ROTATION_AND_MOVING"))
		bool EnableMoblieLooking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0", UIMin = "0", EditCondition = "ControlMethod != ECharacterControlType::NONE && ControlMethod != ECharacterControlType::FPS && EnableMoblieLooking"))
		float MoblieLookingRate;

	//MoblieMoving

	UPROPERTY(EditAnywhere, Category = "Control", meta = (EditCondition = "ControlMethod == ECharacterControlType::MOBILE_TOUCH_CONTROL_ROTATION_AND_MOVING"))
		bool EnableMoblieMoving;

	UPROPERTY(BlueprintReadOnly, Category = "Control")
		ECharacterStatus ExpectStatus;

	UFUNCTION(BlueprintCallable, Category = "Control")
		void StartQuietly();

	UFUNCTION(BlueprintCallable, Category = "Control")
		void EndQuietly();

	UFUNCTION(BlueprintCallable, Category = "Control")
		void StartRunning();

	UFUNCTION(BlueprintCallable, Category = "Control")
		void EndRunning();
private:
	void E_StartToQuietlySpeed();

	void E_EndToQuietlySpeed();

	void E_StartToRunningSpeed();

	void E_EndToRunningSpeed();

	////////////////////////////////////
	//	FPS

	void E_FPS_FrontBackMoving(float Value);

	void E_FPS_LeftRightMoving(float Value);

	void E_FPS_UpDownlooking(float Value);

	void E_FPS_LeftRightlooking(float Value);

	void E_FPS_UpDownRatelooking(float Value);

	void E_FPS_LeftRightRatelooking(float Value);

	void E_FPS_StartJumping();

	void E_FPS_EndJumping();

	void E_FPS_StartCrouching();

	void E_FPS_EndCrouching();

	void E_FPS_StartCrawling();

	void E_FPS_EndCrawling();

	//////////////////////////////////////
	//	MOBILE_TOUCH_ONLY_CONTROL_ROTATION

	bool MTOCR_AllowRightControl;

	bool MTOCR_IsRightStart;

	ETouchIndex::Type MTOCR_SaveRightFingerIndex;

	FVector MTOCR_RightRepeatLastPoint;

	void E_MTOCR_Pressed(const ETouchIndex::Type FingerIndex, const FVector Location);

	void E_MTOCR_Released(const ETouchIndex::Type FingerIndex, const FVector Location);

	void E_MTOCR_Repeat(const ETouchIndex::Type FingerIndex, const FVector Location);

	//////////////////////////////////////
	//	MOBILE_TOUCH_CONTROL_ROTATION_AND_MOVING

	void E_MTCRAM_Pressed(const ETouchIndex::Type FingerIndex, const FVector Location);

	void E_MTCRAM_Released(const ETouchIndex::Type FingerIndex, const FVector Location);

	void E_MTCRAM_Repeat(const ETouchIndex::Type FingerIndex, const FVector Location);
};

