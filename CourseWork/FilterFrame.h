#pragma once
#include <wx/wx.h>
#include <vector>
#include "Note.h"
#include "Repository.h"
#include "App.h"

class FilterFrame: public wxFrame
{
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
public:
	FilterFrame(App* app, wxWindow* parent, Repository* repository);
};

