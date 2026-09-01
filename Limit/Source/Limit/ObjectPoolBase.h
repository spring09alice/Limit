// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ObjectPool, Log, All);

/**
 * 
 */
UCLASS()
class LIMIT_API UObjectPoolBase : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& _Collection) override;

	virtual void Deinitialize() override;

	virtual bool IsTickable() const override;
	
	// オリジナルメソッド /////////////////////////////////////////////////////

public:

	//引数のオブジェクトをプールに登録する
	void RegisterPoolObject(AActor* _actor);

	//引数のオブジェクトをオブジェクトプールに戻す
	void ReturnToPool(AActor* _actor);


	//--------------------------------------------
	// ゲッター・セッター
	//--------------------------------------------
public:

	virtual TStatId GetStatId() const override;

	//--------------------------------------------
	// 更新処理  void (float _deltaTime)
	//--------------------------------------------
protected:

	virtual void Tick(float _deltaTime) override;

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



	//--------------------------------------------
	// コンポーネント * UPROPERTY()
	//--------------------------------------------
protected:

	//--------------------------------------------
	// データ
	//--------------------------------------------
protected:

	TArray<AActor*> m_poolObjects;

	//--------------------------------------------
	// フラグ bool
	//--------------------------------------------
protected:



};
