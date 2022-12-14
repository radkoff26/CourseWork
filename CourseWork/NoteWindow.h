#pragma once
#include <wx/wx.h>
#include "Note.h"

class NoteWindow: public wxWindow
{
private:
	Note note;
	wxTextCtrl* titleView;
	wxTextCtrl* textView;
	wxTextCtrl* authorView;
	wxStaticText* tagsView;
	wxStaticText* creationTimeView;
	wxStaticText* modificationTimeView;
	wxButton* buttonUpdate;
	wxButton* buttonRemove;
	std::function<void(int)> onRemoveCallback;
	std::function<void(Note)> onUpdateCallback;
public:
	NoteWindow(
		wxWindow* parent,
		wxPoint position,
		std::function<void(int)> onRemoveCallback,
		std::function<void(Note)> onUpdateCallback
	);
	void setNote(Note note);
	void clear();
	void OnRemove(wxCommandEvent& evt);
	void OnUpdate(wxCommandEvent& evt);
};

