// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LimPlayerController.generated.h"

class APlayerCharacter;
class ALimPlayerCameraManager;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(PlayerController, Log, All);

/**
 * 
 */
UCLASS()
class LIMIT_API ALimPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	//コンストラクタ
	ALimPlayerController();

	//初フレーム処理
	void BeginPlay()override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//InputComponentのセットアップ
	virtual void SetupInputComponent()override;

	// オリジナルメソッド /////////////////////////////////////////////////////

public:


	//--------------------------------------------
	// ゲッター・セッター
	//--------------------------------------------
public:


	//--------------------------------------------
	// 更新処理  void (float _deltaTime)
	//--------------------------------------------
protected:

	//--------------------------------------------
	// イベント関数 void (  )
	//--------------------------------------------
public:

	//プレイヤーが死亡した時のイベント
	void OnDeadPlayerEvent();

	//入力バインド関数
public:

	//移動入力
	void InputMoveDirection(const FInputActionValue& _Value);

	//移動入力終了
	void InputMoveDirectionFin(const FInputActionValue& _Value);

	//カメラ入力
	void InputCameraAngleMouse(const FInputActionValue& _Value);

	//カメラ入力
	void InputCameraAngleGamePad(const FInputActionValue& _Value);

	//カメラ入力終了
	void InputCameraAngleMouseFin(const FInputActionValue& _Value);

	//カメラ入力終了
	void InputCameraAngleGamePadFin(const FInputActionValue& _Value);

	//ブレーキ入力
	void InputBrake(const FInputActionValue& _Value);

	//ブースト入力
	void InputBoost(const FInputActionValue& _Value);

protected:

	// オリジナルプロパティ /////////////////////////////////////////////////////

	//--------------------------------------------
	// BPで設定 UPROPERTY()
	//--------------------------------------------
public:



	//--------------------------------------------
	// コンポーネント * UPROPERTY()
	//--------------------------------------------
protected:

	//マッピングコンテキスト
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* m_pDefaultInputMappingContext;

	//インプットアクション

	//移動アクション
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_moveAction;

	//カメラアクションマウス
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_cameraAngleMouseAction;

	//カメラアクションゲームパッド
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_cameraAngleGamePadAction;

	//ブレーキアクション
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_brakeAction;

	//ブーストアクション
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_boostAction;

	//--------------------------------------------
	// データ
	//--------------------------------------------
protected:

	//プレイヤー
	UPROPERTY()
	APlayerCharacter* m_pPlayer;

	//カメラマネージャー
	UPROPERTY()
	ALimPlayerCameraManager* m_pCameraManager;

	//--------------------------------------------
	// フラグ bool
	//--------------------------------------------
protected:


};
