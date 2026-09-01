// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolObjectComponent.generated.h"

//デリゲート

//
DECLARE_MULTICAST_DELEGATE_OneParam(
	FReturnToPoolDelegate,
	class AActor*
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMIT_API UPoolObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPoolObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

	//デリゲート//

public:
	//プールに戻すデリゲート
	FReturnToPoolDelegate mf_returnToPool;

	//--------------------------------------------
	// フラグ bool
	//--------------------------------------------
protected:

	//アクティブか？
	bool mb_isActive;
};
