// Fill out your copyright notice in the Description page of Project Settings.


#include "LimPlayerCameraManager.h"

DEFINE_LOG_CATEGORY(CameraManager);

//コンストラクタ
ALimPlayerCameraManager::ALimPlayerCameraManager()
{

}

//BeginPlay
void ALimPlayerCameraManager::BeginPlay()
{
    Super::BeginPlay();


    //ViewTarget指摘しつつ生成
    m_pCamera = NewObject<UCameraComponent>(ViewTarget.Target);

    if (m_pCamera)
    {
        UE_LOG(CameraManager, Log, TEXT("Create Complete CameraComp"));
    }
    else
    {
        UE_LOG(CameraManager, Warning, TEXT("Faled Create CameraComp"));
        return;
    }
    m_pCamera->RegisterComponent();

    UE_LOG(CameraManager, Log, TEXT("Initializing Complete"));
}

// オリジナルメソッド /////////////////////////////////////////////////////



//--------------------------------------------
// ゲッター・セッター
//--------------------------------------------

//カメラの取得
UCameraComponent* ALimPlayerCameraManager::GetCamera()
{
    return m_pCamera;
}

//カメラ回転入力設定用
void ALimPlayerCameraManager::SetCameraAngleInputVal(FVector2D _inputVal)
{
    m_cameraAngleInputVal = _inputVal;
}

//カメラの入力タイプ設定
void ALimPlayerCameraManager::SetCameraInputType(ECameraInputType _inputType)
{
    m_eInputType = _inputType;
}

//カメラリセットフラグ設定
void ALimPlayerCameraManager::SetIsCameraReset(bool _isReset)
{

}

//--------------------------------------------
// 更新処理
//--------------------------------------------

//カメラの更新
void ALimPlayerCameraManager::UpdateCamera(float _deltaTime)
{
    Super::UpdateCamera(_deltaTime);

    if (!m_pCamera)
    {
        UE_LOG(CameraManager, Warning, TEXT("Camera Is None : UpdateCamera"));
        return;
    }

    UpdateCameraAngle(_deltaTime);
}

//プレイヤーカメラの回転更新
void ALimPlayerCameraManager::UpdateCameraAngle(float _deltaTime)
{
    //UE_LOG(CameraManager, Log, TEXT("Input : x : %f , y : %f"), m_cameraAngleInputVal.X, m_cameraAngleInputVal.Y);


}

//--------------------------------------------
// イベント関数
//--------------------------------------------

