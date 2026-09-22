// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"

#include "Camera/CameraComponent.h"

#include "LimPlayerCameraManager.generated.h"

enum ECameraInputType
{
	Mouse = 0,
	GamePad = 1
};

DECLARE_LOG_CATEGORY_EXTERN(CameraManager, Log, All);

/**
 * 
 */
UCLASS()
class LIMIT_API ALimPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	//コンストラクタ
	ALimPlayerCameraManager();

	//BeginPlay
	void BeginPlay()override;

	//カメラの更新
	void UpdateCamera(float _deltaTime)override;

	// オリジナルメソッド /////////////////////////////////////////////////////

public:


	//--------------------------------------------
	// ゲッター・セッター
	//--------------------------------------------
public:

	//カメラの取得
	UCameraComponent* GetCamera();

	//カメラ回転入力設定用
	void SetCameraAngleInputVal(FVector2D _inputVal);

	//カメラの入力タイプ設定
	void SetCameraInputType(ECameraInputType _inputType);

	//カメラリセットフラグ設定
	void SetIsCameraReset(bool _isReset);

	//--------------------------------------------
	// 更新処理  void (float _deltaTime)
	//--------------------------------------------
protected:

	//更新関数
	void CameraManagerTick(float _deltaTime);

	//プレイヤーカメラの回転更新
	void UpdateCameraAngle(float _deltaTime);

	//--------------------------------------------
	// イベント関数 void (  )
	//--------------------------------------------
public:


protected:

	// オリジナルプロパティ /////////////////////////////////////////////////////

	//--------------------------------------------
	// BPで設定 UPROPERTY()
	//--------------------------------------------
public:

	//カメラ

	//マウスでのカメラ回転速度
	UPROPERTY(EditAnywhere)
	float CameraRotationSpeed_Mouse;

	//カメラ回転のPitch下限
	UPROPERTY(EditAnywhere)
	float CameraPitchMin;
	//カメラ回転のPitch上限
	UPROPERTY(EditAnywhere)
	float CameraPitchMax;

	//カメラの線形補間の速度
	UPROPERTY(EditAnywhere)
	float CameraLearpAlpha;

	//--------------------------------------------
	// コンポーネント * UPROPERTY()
	//--------------------------------------------
protected:

public:
	//カメラ
	UPROPERTY(EditAnywhere)
	UCameraComponent* m_pCamera;

	//--------------------------------------------
	// データ
	//--------------------------------------------
protected:

	//カメラ回転入力値
	//この値でカメラ回転更新時の回転量を決める
	FVector2D m_cameraAngleInputVal;

	//ターゲットアクター
	AActor* m_pTargetActor;

	//カメラの現在の回転速度
	float m_cameraSpeed;

	//入力タイプ列挙型
	ECameraInputType m_eInputType;

	//--------------------------------------------
	// フラグ bool
	//--------------------------------------------
protected:


};
