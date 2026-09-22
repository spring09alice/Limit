// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolBase.h"
#include "PoolObjectInterface.h"
#include "PoolObjectComponent.h"

DEFINE_LOG_CATEGORY(ObjectPool);

void UObjectPoolBase::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);



    UE_LOG(ObjectPool, Warning, TEXT("Subsystem Initialize"));
}

void UObjectPoolBase::Deinitialize()
{
    UE_LOG(ObjectPool, Warning, TEXT("Subsystem Deinitialize"));



    Super::Deinitialize();
}

bool UObjectPoolBase::IsTickable() const
{
    return true;
}

// オリジナルメソッド /////////////////////////////////////////////////////

//引数のオブジェクトをプールに登録する
void UObjectPoolBase::RegisterPoolObject(AActor* _actor)
{
    //重複チェック
    if (m_poolObjects.Contains(_actor))
    {
        UE_LOG(ObjectPool, Warning, TEXT("RegisterPoolObject() : this Acter is Contain"));
        return;
    }

    //インターフェイス確認
    if (!_actor->Implements<UPoolObjectInterface>())
    {
        UE_LOG(ObjectPool, Warning, TEXT("RegisterPoolObject() : this Actor is not UPoolObjectInterface"));
        return;
    }

    //コンポーネント確認
    //コンポーネント
    UPoolObjectComponent* poolComp = _actor->FindComponentByClass<UPoolObjectComponent>();

    if (!poolComp)
    {
        UE_LOG(ObjectPool, Warning, TEXT("RegisterPoolObject() : UPoolObjectComponent is none"));
        return;
    }
    //デリゲート登録
    poolComp->mf_returnToPool.AddUObject(this, &UObjectPoolBase::ReturnToPool);

    //登録
    m_poolObjects.Add(_actor);
}

//引数のオブジェクトをオブジェクトプールに戻す
void UObjectPoolBase::ReturnToPool(AActor* _actor)
{
    //整合性チェック
    if (!m_poolObjects.Contains(_actor))
    {
        UE_LOG(ObjectPool, Warning, TEXT("ReturnToPool() : this Acter is not Contain"));
        return;
    }

    //インターフェイス確認
    if (!_actor->Implements<UPoolObjectInterface>())
    {
        UE_LOG(ObjectPool, Warning, TEXT("RegisterPoolObject() : this Actor is not UPoolObjectInterface"));
        return;
    }

    IPoolObjectInterface* poolObject = Cast<IPoolObjectInterface>(_actor);

    //非アクティブ化
    poolObject->SetisActive(false);
}


//--------------------------------------------
// ゲッター・セッター
//--------------------------------------------

TStatId UObjectPoolBase::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UObjectPoolBase, STATGROUP_Tickables);
}

//--------------------------------------------
// 更新処理
//--------------------------------------------

void UObjectPoolBase::Tick(float DeltaTime)
{
    UE_LOG(ObjectPool, Log, TEXT("Tick %f"), DeltaTime);

    // 毎フレーム処理
    for (int i = 0; i < m_poolObjects.Num(); ++i)
    {
        IPoolObjectInterface* poolObject = Cast<IPoolObjectInterface>(m_poolObjects[i]);

        poolObject->PoolUpdate(DeltaTime);
    }
}

//--------------------------------------------
// イベント関数
//--------------------------------------------