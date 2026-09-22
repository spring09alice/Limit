#include "LimInGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "LimPlayerController.h"
#include "PlayerCharacter.h"

DEFINE_LOG_CATEGORY(LiminGameMode);

void ALimInGameMode::BeginPlay()
{
	Super::BeginPlay();

	//プレイヤーコントローラー初期化フェーズ
	ALimPlayerController* pc = Cast<ALimPlayerController>(GetWorld()->GetFirstPlayerController());

	if (!pc)
	{
		UE_LOG(LiminGameMode, Warning, TEXT("PlayerController Is None"));
	}
}