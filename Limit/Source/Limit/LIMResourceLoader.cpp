#include "LIMResourceLoader.h"
#include "Limit/DataCreate/Weapon/WeaponCreateDataAsset.h"
#include "Animation/AnimMontage.h"


void ULIMResourceLoader::LoadWeaponDataAsset(const TSoftObjectPtr<ULIMWeaponEditDataAsset>& InWeaponDataAsset)
{
	if (InWeaponDataAsset.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("未設定のSoftObjectPtrです:ULIMResourceLoader::LoadWeaponData :InWeaponDataAsset"));
		return;
	}
	if (InWeaponDataAsset.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("既にロードされています:ULIMResourceLoader::LoadWeaponData :InWeaponDataAsset"));
		return;
	}

	WeaponLoadedDataAsset = InWeaponDataAsset.LoadSynchronous();
}

void ULIMResourceLoader::LoadUseWeaponData(const FName& InName)
{
	if (!IsValid(WeaponLoadedDataAsset))
	{
		UE_LOG(LogTemp, Warning, TEXT("武器データアセットが未ロードです:ULIMResourceLoader::LoadUseWeaponData"));
		return;
	}

	FInstancedStruct* weaponData = WeaponLoadedDataAsset->WeaponDatas.Find(InName);
	if (!weaponData)
	{
		UE_LOG(LogTemp, Warning, TEXT("存在しない武器名です:%s"), *InName.ToString());
		return;
	}

	const FLIMModeChangeWeaponData* modeChangeWeaponData = weaponData->GetPtr<FLIMModeChangeWeaponData>();
	if (modeChangeWeaponData)
	{
		FLIMModeChangeWeaponLoadData newData;

		// 変形データのロード
		for (const FLIMWeaponModeChangeData& changeData : modeChangeWeaponData->ModeChangeDatas)
		{
			if (changeData.ModeChangeMontage.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器変更モーションが未設定:%s:%s"), *InName.ToString(), *changeData.TargetWeaponName.ToString());
				continue;
			}
			if (changeData.ModeChangeMontage.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器変更モーションがロード済み:%s:%s"), *InName.ToString(), *changeData.TargetWeaponName.ToString());
				continue;
			}

			FLIMWeaponModeChangeLoadData loadedChangeData;
			loadedChangeData.ModeChangeMontage = changeData.ModeChangeMontage.LoadSynchronous();
			loadedChangeData.TargetWeaponName = changeData.TargetWeaponName;

			newData.ModeChangeDatas.Add(loadedChangeData);
		}

		// 通常攻撃Montageのロード
		int attackIndex = -1;
		for (const TSoftObjectPtr<UAnimMontage>& defaultAttackMontage : modeChangeWeaponData->DefaultAttackMontages)
		{
			attackIndex++;

			if (defaultAttackMontage.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器の通常モーションが未設定:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}
			if (defaultAttackMontage.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器の通常モーションがロード済み:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}

			newData.DefaultAttackMontages.Add(defaultAttackMontage.LoadSynchronous());
		}

		// スキル攻撃Montageのロード
		int skillIndex = -1;
		for (const TSoftObjectPtr<UAnimMontage>& skillAttackMontage : modeChangeWeaponData->SpecialAttackMontages)
		{
			attackIndex++;

			if (skillAttackMontage.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のスキルモーションが未設定:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}
			if (skillAttackMontage.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のスキルモーションがロード済み:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}

			newData.SpecialAttackMontages.Add(skillAttackMontage.LoadSynchronous());
		}

		// 武器メッシュのロード
		// Static
		if (modeChangeWeaponData->bUseWeaponAnim == true)
		{
			const TSoftObjectPtr<USkeletalMesh>& mesh = modeChangeWeaponData->WeaponSkeletalMesh;
			if (mesh.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のSkeletalMeshが未設定:%s"), *InName.ToString());
			}
			else
			{
				if (mesh.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("武器のSkeletalMeshがロード済み:%s"), *InName.ToString());
				}
				else
				{
					newData.WeaponSkeletalMesh = mesh.LoadSynchronous();
				}
			}
		}
		// Skeletal
		else
		{
			const TSoftObjectPtr<UStaticMesh>& mesh = modeChangeWeaponData->WeaponStaticMesh;
			if (mesh.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のStaticMeshが未設定:%s"), *InName.ToString());
			}
			else
			{
				if (mesh.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("武器のStaticMeshがロード済み:%s"), *InName.ToString());
				}
				else
				{
					newData.WeaponStaticMesh = mesh.LoadSynchronous();
				}
			}
		}

		newData.bUseWeaponAnim = modeChangeWeaponData->bUseWeaponAnim;
		newData.Rarelity = modeChangeWeaponData->Rarelity;
		FInstancedStruct data = FInstancedStruct::Make(newData);
		WeaponLoadedDataMap.Add(InName, data);
		return;
	}

	//変形しない武器
	const FLIMWeaponData* simpleWeaponData = weaponData->GetPtr<FLIMWeaponData>();
	if (simpleWeaponData)
	{
		FLIMWeaponLoadData newData;
		// 通常攻撃Montageのロード
		int attackIndex = -1;
		for (const TSoftObjectPtr<UAnimMontage>& defaultAttackMontage : modeChangeWeaponData->DefaultAttackMontages)
		{
			attackIndex++;

			if (defaultAttackMontage.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器の通常モーションが未設定:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}
			if (defaultAttackMontage.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器の通常モーションがロード済み:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}

			newData.DefaultAttackMontages.Add(defaultAttackMontage.LoadSynchronous());
		}

		// スキル攻撃Montageのロード
		int skillIndex = -1;
		for (const TSoftObjectPtr<UAnimMontage>& skillAttackMontage : modeChangeWeaponData->SpecialAttackMontages)
		{
			attackIndex++;

			if (skillAttackMontage.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のスキルモーションが未設定:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}
			if (skillAttackMontage.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のスキルモーションがロード済み:%s:%d"), *InName.ToString(), attackIndex);
				continue;
			}

			newData.SpecialAttackMontages.Add(skillAttackMontage.LoadSynchronous());
		}

		// 武器メッシュのロード
		// Static
		if (modeChangeWeaponData->bUseWeaponAnim == true)
		{
			const TSoftObjectPtr<USkeletalMesh>& mesh = modeChangeWeaponData->WeaponSkeletalMesh;
			if (mesh.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のSkeletalMeshが未設定:%s"), *InName.ToString());
			}
			else
			{
				if (mesh.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("武器のSkeletalMeshがロード済み:%s"), *InName.ToString());
				}
				else
				{
					newData.WeaponSkeletalMesh = mesh.LoadSynchronous();
				}
			}
		}
		// Skeletal
		else
		{
			const TSoftObjectPtr<UStaticMesh>& mesh = modeChangeWeaponData->WeaponStaticMesh;
			if (mesh.IsNull())
			{
				UE_LOG(LogTemp, Warning, TEXT("武器のStaticMeshが未設定:%s"), *InName.ToString());
			}
			else
			{
				if (mesh.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("武器のStaticMeshがロード済み:%s"), *InName.ToString());
				}
				else
				{
					newData.WeaponStaticMesh = mesh.LoadSynchronous();
				}
			}
		}

		newData.bUseWeaponAnim = modeChangeWeaponData->bUseWeaponAnim;
		newData.Rarelity = modeChangeWeaponData->Rarelity;
		FInstancedStruct data = FInstancedStruct::Make(newData);
		WeaponLoadedDataMap.Add(InName, data);
		return;
	}
}

