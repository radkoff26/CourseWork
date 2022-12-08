#pragma once
#include <wx/wx.h>
#include "Repository.h"
#include "App.h"

class AddNoteFrame: public wxFrame
{
public:
	AddNoteFrame(App* app, wxWindow* parent, const wxString& title);
	~AddNoteFrame() {

	}
private:
	Repository* repository;
	App* app;
	wxPanel* panel;
	wxTextCtrl* titleInput;
	wxTextCtrl* textInput;
	wxButton* submitButton;
	void OnSubmit(wxCommandEvent& evt);
};

