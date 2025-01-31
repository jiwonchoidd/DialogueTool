#pragma once
#include "AssetTypeActions_Base.h"

class DD_DIALOGUEEDITOR_API FDD_Dialogue_AssetTypeActions : public FAssetTypeActions_Base
{
public:
	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual FText GetDisplayNameFromAssetData(const FAssetData& AssetData) const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;
	virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
};
