#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StructUtils/InstancedStruct.h"
#include "WeaponCreateDataAsset.generated.h"

class UAnimMontage;
class USkeletalMesh;
class UStaticMesh;

/** レアリティ列挙型 */
UENUM(BlueprintType)
enum class ERarelity :uint8
{
	Common,
	Rare,
	Origin
};

/** 変形アニメーションと変形後の武器名称のセット*/
USTRUCT(BlueprintType)
struct LIMIT_API FLIMWeaponModeChangeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "変形アニメーション"))
	TSoftObjectPtr<UAnimMontage> ModeChangeMontage;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "変形先武器名称"))
	FName TargetWeaponName;
};

/** 武器制作 / 保存用構造体*/
USTRUCT(BlueprintType)
struct LIMIT_API FLIMWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "レアリティ"))
	ERarelity Rarelity = ERarelity::Common;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "武器アニメーションの有無"))
	bool bUseWeaponAnim = true;

	UPROPERTY(EditAnywhere, Category = "WeaponMesh", meta = (DisplayName = "武器メッシュ", EditCondition = "bUseWeaponAnim == true", EditConditionHides))
	TSoftObjectPtr<USkeletalMesh> WeaponSkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "WeaponMesh", meta = (DisplayName = "武器メッシュ", EditCondition = "bUseWeaponAnim == false", EditConditionHides))
	TSoftObjectPtr<UStaticMesh> WeaponStaticMesh;

	UPROPERTY(EditAnywhere, Category = "AttackAnimation", meta = (DisplayName = "通常攻撃Animation"))
	TArray<TSoftObjectPtr<UAnimMontage>> DefaultAttackMontages;

	UPROPERTY(EditAnywhere, Category = "AttackAnimation", meta = (DisplayName = "スキル攻撃Animation"))
	TArray<TSoftObjectPtr<UAnimMontage>> SpecialAttackMontages;
};

/** 変形可能武器制作 / 保存用構造体*/
USTRUCT(BlueprintType)
struct LIMIT_API FLIMModeChangeWeaponData :public FLIMWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "ModeChange", meta = (DisplayName = "変形情報"))
	TArray<FLIMWeaponModeChangeData> ModeChangeDatas;
};

/** 武器制作用データアセット*/
UCLASS()
class LIMIT_API ULIMWeaponEditDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "武器情報",BaseStruct = "/Script/LIMIT.LIMWeaponData"))
	TMap<FName, FInstancedStruct> WeaponDatas;
};
