#pragma once
#include <wx/wx.h>
#include "Repository.h"
#include "App.h"

class AddTagFrame : public wxFrame
{
public:
	AddTagFrame(App* app, wxWindow* parent, const wxString& title);
	~AddTagFrame() {

	}
private:
	Repository* repository;
	App* app;
	wxPanel* panel;
	wxTextCtrl* titleInput;
	wxButton* submitButton;
	void OnSubmit(wxCommandEvent& evt);
};