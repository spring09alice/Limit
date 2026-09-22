// Fill out your copyright notice in the Description page of Project Settings.


#include "LimPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "LimPlayerCameraManager.h"
#include "PlayerCharacter.h"

DEFINE_LOG_CATEGORY(PlayerController);

//コンストラクタ
ALimPlayerController::ALimPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

//初フレーム処理
void ALimPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//プレイヤー
	m_pPlayer = Cast<APlayerCharacter>(GetPawn());

	if (m_pPlayer == nullptr)
	{
		UE_LOG(PlayerController, Warning, TEXT("Missing PlayerCharacter"));
		return;
	}

	//カメラの初期化
	m_pCameraManager = Cast<ALimPlayerCameraManager>(PlayerCameraManager);

	if (!m_pCameraManager)
	{
		UE_LOG(PlayerController, Warning, TEXT("Missing PlayerCameraManager"));
		return;
	}

	// 入力関係初期化 ////////////////////////////////////////////////////////////

	//ローカルプレイヤー
	ULocalPlayer* localPlayer = nullptr;
	//入力サブシステム
	UEnhancedInputLocalPlayerSubsystem* enhancedInputLocalPlayerSubSystem = nullptr;

	//ローカルプレイヤーを取得
	localPlayer = GetLocalPlayer();

	//ローカルプレイヤーが有効でなければ終了
	if (!localPlayer)
	{
		UE_LOG(PlayerController, Warning, TEXT("Missing LocalPlayer"));
		return;
	}

	//入力サブシステムを取得
	enhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);

	//入力サブシステムが有効でなければ終了
	if (!enhancedInputLocalPlayerSubSystem)
	{
		UE_LOG(PlayerController, Warning, TEXT("Missing EnhancedInputLocalPlayerSubsystem"));
		return;
	}
	//マッピングコンテキストが有効でなければ終了
	if (!m_pDefaultInputMappingContext)
	{
		UE_LOG(PlayerController, Warning, TEXT("Missing DefaultInputMappingContext"));
		return;
	}

	//入力サブシステムにマッピングコンテキストを追加
	enhancedInputLocalPlayerSubSystem->AddMappingContext(m_pDefaultInputMappingContext, 0);

	UE_LOG(PlayerController, Log, TEXT("Initializing Complete"));
}

// Called every frame
void ALimPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//InputComponentのセットアップ
void ALimPlayerController::SetupInputComponent()
{
	UE_LOG(PlayerController, Log, TEXT("Call Setup Input Component"));

	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (!enhancedInputComponent)
	{
		UE_LOG(PlayerController, Warning, TEXT("Missing EnhancedInputComponent"));
		return;
	}

	// BindAction //

	//カメラ回転の入力をバインド
	enhancedInputComponent->BindAction(IA_cameraAngleMouseAction, ETriggerEvent::Triggered, this, &ALimPlayerController::InputCameraAngleMouse);
	enhancedInputComponent->BindAction(IA_cameraAngleGamePadAction, ETriggerEvent::Triggered, this, &ALimPlayerController::InputCameraAngleGamePad);
	//カメラ回転の入力をバインド
	enhancedInputComponent->BindAction(IA_cameraAngleMouseAction, ETriggerEvent::Completed, this, &ALimPlayerController::InputCameraAngleMouseFin);
	enhancedInputComponent->BindAction(IA_cameraAngleGamePadAction, ETriggerEvent::Completed, this, &ALimPlayerController::InputCameraAngleGamePadFin);

	//移動入力をバインド
	enhancedInputComponent->BindAction(IA_moveAction, ETriggerEvent::Triggered, this, &ALimPlayerController::InputMoveDirection);
	enhancedInputComponent->BindAction(IA_moveAction, ETriggerEvent::Completed, this, &ALimPlayerController::InputMoveDirection);

	//ブレーキ入力をバインド
	enhancedInputComponent->BindAction(IA_brakeAction, ETriggerEvent::Started, this, &ALimPlayerController::InputBrake);

	//ブースト入力をバインド
	enhancedInputComponent->BindAction(IA_boostAction, ETriggerEvent::Started, this, &ALimPlayerController::InputBoost);


}

// オリジナルメソッド /////////////////////////////////////////////////////



//--------------------------------------------
// ゲッター・セッター
//--------------------------------------------



//--------------------------------------------
// 更新処理
//--------------------------------------------



//--------------------------------------------
// イベント関数
//--------------------------------------------

//プレイヤーが死亡した時のイベント
void ALimPlayerController::OnDeadPlayerEvent()
{

}

//入力バインド関数

//移動入力
void ALimPlayerController::InputMoveDirection(const FInputActionValue& _Value)
{

}

//移動入力終了
void ALimPlayerController::InputMoveDirectionFin(const FInputActionValue& _Value)
{

}

//カメラ入力
void ALimPlayerController::InputCameraAngleMouse(const FInputActionValue& _Value)
{
	m_pCameraManager->SetCameraInputType(ECameraInputType::Mouse);
	m_pCameraManager->SetCameraAngleInputVal(_Value.Get<FVector2D>());
}

//カメラ入力
void ALimPlayerController::InputCameraAngleGamePad(const FInputActionValue& _Value)
{
	m_pCameraManager->SetCameraInputType(ECameraInputType::GamePad);
	m_pCameraManager->SetCameraAngleInputVal(_Value.Get<FVector2D>());
}

//カメラ入力終了
void ALimPlayerController::InputCameraAngleMouseFin(const FInputActionValue& _Value)
{

}

//カメラ入力終了
void ALimPlayerController::InputCameraAngleGamePadFin(const FInputActionValue& _Value)
{

}

//ブレーキ入力
void ALimPlayerController::InputBrake(const FInputActionValue& _Value)
{

}

//ブースト入力
void ALimPlayerController::InputBoost(const FInputActionValue& _Value)
{

}