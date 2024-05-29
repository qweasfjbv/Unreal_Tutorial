// Copyright Epic Games, Inc. All Rights Reserved.

#include "TutorialGameMode.h"
#include "TutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATutorialGameMode::ATutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
