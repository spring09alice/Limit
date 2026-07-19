#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StructUtils/InstancedStruct.h"
#include "LIMResourceLoader.generated.h"

class ULIMWeaponEditDataAsset;
enum class ERarelity :uint8;

/** 変形アニメーションと変形後の武器名称のセット*/
USTRUCT(BlueprintType)
struct LIMIT_API FLIMWeaponModeChangeLoadData
{
	GENERATED_BODY()

public:
	TSoftObjectPtr<UAnimMontage> ModeChangeMontage;

	FName TargetWeaponName;
};

/** 武器制作 / 保存用構造体*/
USTRUCT(BlueprintType)
struct LIMIT_API FLIMWeaponLoadData
{
	GENERATED_BODY()

public:
	ERarelity Rarelity;

	bool bUseWeaponAnim = true;

	TSoftObjectPtr<USkeletalMesh> WeaponSkeletalMesh;

	TSoftObjectPtr<UStaticMesh> WeaponStaticMesh;

	TArray<TSoftObjectPtr<UAnimMontage>> DefaultAttackMontages;

	TArray<TSoftObjectPtr<UAnimMontage>> SpecialAttackMontages;
};

/** 変形可能武器制作 / 保存用構造体*/
USTRUCT(BlueprintType)
struct LIMIT_API FLIMModeChangeWeaponLoadData :public FLIMWeaponLoadData
{
	GENERATED_BODY()

public:
	TArray<FLIMWeaponModeChangeLoadData> ModeChangeDatas;
};

/** データロード用クラス*/
UCLASS()
class LIMIT_API ULIMResourceLoader : public UObject
{
	GENERATED_BODY()

public:
	void LoadWeaponDataAsset(const TSoftObjectPtr<ULIMWeaponEditDataAsset>& InWeaponDataAsset);

	void LoadUseWeaponData(const FName& InName);
private:
	TObjectPtr<ULIMWeaponEditDataAsset> WeaponLoadedDataAsset;

	TMap<FName, FInstancedStruct> WeaponLoadedDataMap;
};
