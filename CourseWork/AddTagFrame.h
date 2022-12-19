#pragma once
#include <wx/wx.h>
#include "Repository.h"
#include "App.h"

class AddTagFrame : public wxFrame
{
public:
	AddTagFrame(App* app, Repository* repository);
	~AddTagFrame() {
		this->app = nullptr;
		this->repository = nullptr;
	}
private:
	Repository* repository;
	App* app;
	wxPanel* panel;
	wxTextCtrl* titleInput;
	wxButton* submitButton;
	void OnSubmit(wxCommandEvent& evt);
};