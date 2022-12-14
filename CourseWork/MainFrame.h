#pragma once
#include <wx/wx.h>
#include "Repository.h"
#include <vector>
#include "App.h"
#include "NoteWindow.h"

class MainFrame : public wxFrame {
public:
	MainFrame(
		App* app,
		const wxString& title,
		std::vector<std::function<bool(Note)>> filters,
		Repository* repository
	);
	~MainFrame() {

	}
private:
	App* app;
	Repository* repository;
	wxPanel* panel;
	wxButton* addNoteButton;
	wxButton* addTagButton;
	wxButton* filterButton;
	wxButton* dashboardButton;
	wxListBox* notesList;
	NoteWindow* noteWindow;
	std::function<void(int)> onRemoveCallback;
	std::function<void(Note)> onUpdateCallback;
	std::vector<Note> notes;
	void OnAddNote(wxCommandEvent& evt);
	void OnAddTag(wxCommandEvent& evt);
	void OnAdjustFilters(wxCommandEvent& evt);
	void OnOpenDashboard(wxCommandEvent& evt);
	void OnSelectItem(wxCommandEvent& evt);
	void UpdateList();
};