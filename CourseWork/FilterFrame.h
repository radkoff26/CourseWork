#pragma once
#include <wx/wx.h>
#include <vector>
#include "Note.h"
#include "Repository.h"
#include "App.h"

class FilterFrame: public wxFrame
{
public:
	FilterFrame(App* app, Repository* repository);
	~FilterFrame() {
		this->app = nullptr;
		this->repository = nullptr;
	}
private:
	App* app;
	Repository* repository;
	wxPanel* panel;
	wxTextCtrl* authorInput;
	wxListBox* tagsList;
	wxCheckBox* lastThreeDaysCreationCheckbox;
	wxCheckBox* lastThreeDaysModificationCheckbox;
	wxButton* applyFiltersButton;
	std::vector<Tag> tags;
	void OnApply(wxCommandEvent& evt);
};

