#include "ScreenSystemDialog.h"
#include "../global.h"
#include "../Views/FramePanel.h"
#include "../Xml.h"

using namespace std;

ScreenSystemDialog::ScreenSystemDialog()
{
	popup = true;
	SetTransitionTime(0.5, 0.2);

	contentView = NULL;
	inputView = NULL;
}

ScreenSystemDialog::~ScreenSystemDialog()
{
	if (contentView != NULL)
		delete contentView;
	contentView = NULL;
}

bool ScreenSystemDialog::Initialize()
{
	contentView = new FramePanel();
	contentView->SetSize(Size(SIZE_FILL_PARENT, SIZE_FILL_PARENT));

	try
	{
		Xml xml;
		contentView->AddChildView(xml.LoadView("data/system/systemMenu.xml"));
		contentView->InitializeAll(this);
		contentView->CalculateLayout(screenManager->GetDisplaySize());
		contentView->CalculateAbsolutePosition(Position(0, 0));

		View* v = contentView->GetChildViewById("inputView");
		if (v != NULL)
		{
			inputView = dynamic_cast<ISelectionHandler*>(v);
			if (inputView == NULL)
			{
				throw runtime_error("This view cannot be used as an inputView. An inputView must implement ISelectionHandler.");
			}
		}

		selectionLabel = dynamic_cast<Label*>(contentView->GetChildViewById("selectionLabel"));

		if (inputView != NULL)
			inputView->SelectByIndex(1);
	}
	catch (exception& ex)
	{
		lastError = ex.what();
		return false;
	}

	return true;
}

void ScreenSystemDialog::HandleInput(InputState* input)
{
	if (inputView != NULL)
		inputView->HandleInput(input);

	if (input->GameKeyJustPressed(GAMEKEY_B) || input->GameKeyJustPressed(GAMEKEY_START))
		OnEvent(NULL, EventTypeGoBack, "");
}

void ScreenSystemDialog::Update(bool otherScreenHasFocus, bool coveredByOtherScreen)
{
	Screen::Update(otherScreenHasFocus, coveredByOtherScreen);

	if (IsActive())
	{
		//
	}
}

void ScreenSystemDialog::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xA0 * (1 - transitionPosition));
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

	if (contentView != NULL && screenstate != TransitionOff) // Hide immediately when transitioning off
		contentView->Draw();
}

void ScreenSystemDialog::OnEvent(View* sender, EventType eventType, string eventValue, vector<string> eventArgs)
{
	// FIXME catch exceptions for everything in this method

	switch (eventType)
	{
	case EventTypeAction:
		{
			if (eventValue == "shutdown")
			{
				// TODO shutdown
			}
			else if (eventValue == "reboot")
			{
				// TODO reboot
			}
			else if (eventValue == "exit")
			{
				screenManager->Exit();
			}
			else if (eventValue == "info")
			{
				// TODO launch info screen
			}

			break;
		}

	case EventTypeGoBack:
		{
			ExitScreen();
			break;
		}

	case EventTypeSelectionChanged:
		{
			if (selectionLabel != NULL)
				selectionLabel->SetText(sender->GetName());

			break;
		}
	}
}
