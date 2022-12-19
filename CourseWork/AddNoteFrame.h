#pragma once
#include <wx/wx.h>
#include "Repository.h"
#include "App.h"

class AddNoteFrame: public wxFrame
{
public:
	AddNoteFrame(App* app, Repository* repository);
	~AddNoteFrame() {
		this->app = nullptr;
		this->repository = nullptr;
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

