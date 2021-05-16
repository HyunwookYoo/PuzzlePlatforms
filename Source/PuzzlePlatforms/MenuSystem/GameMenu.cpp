// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"

#include "Components/Button.h"

bool UGameMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UGameMenu::QuitToMainMenu);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UGameMenu::CancelPressed);

	return true;
}


void UGameMenu::QuitToMainMenu()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Quit();
	}
}

void UGameMenu::CancelPressed()
{
	Teardown();
}