// Fill out your copyright notice in the Description page of Project Settings.


#include "FDDialogueEditor.h"

#include "DDDialogueGraph.h"

void FDDialogueEditor::OpenDialogueEditor(const TArray<UObject*>& InObjects,
                                          TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EditingGraph = Cast<UDDDialogueGraph>(InObjects[0]);

	// 기본 레이아웃 설정
	const TSharedRef<FTabManager::FLayout> DefaultLayout = FTabManager::NewLayout("DDDialogueEditor_Layout")
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split(
				FTabManager::NewStack()
				->AddTab(GetToolkitFName(), ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		);

	InitAssetEditor(EToolkitMode::Standalone, EditWithinLevelEditor, FName("DDDialogueEditorApp"), DefaultLayout, true,
	                true, InObjects);
}
