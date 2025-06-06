// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialoguePlayer.h"

#include "DD_DialogueData.h"

void UDD_DialoguePlayer::PlayDialogue(UDD_DialogueData* _Data)
{
	TArray<FString> test = _Data->GetDialogueInfo();
}
