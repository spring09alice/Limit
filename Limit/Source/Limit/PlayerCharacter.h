// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FighterCharacter.h"

#include "PlayerCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(PlayerChara, Log, All);

UCLASS()
class LIMIT_API APlayerCharacter : public AFighterCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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



	//--------------------------------------------
	// フラグ bool
	//--------------------------------------------
protected:


};
