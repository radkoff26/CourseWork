#pragma once
#include <wx/wx.h>
#include "Repository.h"
#include "App.h"

class AddNoteFrame: public wxFrame
{
public:
	AddNoteFrame(App* app, wxWindow* parent, const wxString& title, Repository* repository);
	~AddNoteFrame() {

	}
private:
	Repository* repository;
	App* app;
	wxPanel* panel;
	wxTextCtrl* titleInput;
	wxTextCtrl* textInput;
	wxTextCtrl* authorInput;
	std::vector<Tag> tags;
	wxListBox* tagsList;
	wxButton* submitButton;
	void OnSubmit(wxCommandEvent& evt);
};

