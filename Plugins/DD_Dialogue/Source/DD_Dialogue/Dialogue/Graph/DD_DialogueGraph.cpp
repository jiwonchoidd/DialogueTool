// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialogueGraph.h"

#include "DD_Dialogue/Dialogue/DD_DialogueData.h"

class UDD_DialogueData* UDD_DialogueGraph::GetDialogueData() const
{
	return CastChecked<UDD_DialogueData>(GetOuter());
}
