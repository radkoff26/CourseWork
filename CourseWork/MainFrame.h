#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Repository.h"
#include <vector>
#include "App.h"
#include "NoteWindow.h"

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
	wxListBox* notesList;
	NoteWindow* noteWindow;
	std::function<void(int)> onRemoveCallback;
	std::function<void(Note)> onUpdateCallback;
	std::vector<Note> notes;
	void OnAddNote(wxCommandEvent& evt);
	void OnAddTag(wxCommandEvent& evt);
	void OnSelectItem(wxCommandEvent& evt);
	void UpdateList();
};