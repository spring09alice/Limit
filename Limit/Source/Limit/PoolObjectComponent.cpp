// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolObjectComponent.h"

// Sets default values for this component's properties
UPoolObjectComponent::UPoolObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPoolObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPoolObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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