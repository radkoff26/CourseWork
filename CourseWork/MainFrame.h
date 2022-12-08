#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Repository.h"
#include "App.h"

class MainFrame : public wxFrame {
public:
	MainFrame(App* app, const wxString& title);
	~MainFrame() {

	}
private:
	App* app;
	Repository* repository;
	wxPanel* panel;
	wxButton* addNoteButton;
	wxButton* addTagButton;
	wxButton* filterButton;
	wxListCtrl* notesList;
	void OnAddNote(wxCommandEvent& evt);
	void OnSelectItem(wxCommandEvent& evt);
};