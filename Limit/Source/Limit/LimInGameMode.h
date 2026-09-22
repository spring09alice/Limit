#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LimInGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LiminGameMode, Log, All);

UCLASS()
class LIMIT_API ALimInGameMode : public AGameMode
{
	GENERATED_BODY()
	
	//äJénéûèàóù
	virtual void BeginPlay() override;
};
