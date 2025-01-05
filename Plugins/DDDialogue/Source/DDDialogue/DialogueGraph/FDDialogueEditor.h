
#pragma once
/**
 * 
 */
class FDDialogueEditor : public FAssetEditorToolkit
{
public:
	void OpenDialogueEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor);
	
	virtual FName GetToolkitFName() const override { return FName("DDDialogueEditor"); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("DD Dialogue Editor"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DDDialogueEditor"); }
private:
	class UDDDialogueGraph* EditingGraph = nullptr;
};
