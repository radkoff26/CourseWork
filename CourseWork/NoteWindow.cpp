#include "NoteWindow.h"
#include "Note.h"
#include <vector>
#include "Utils.h"

const std::string tagsPrefix = "Tags: ";
const std::string creationTimePrefix = "Creation time: ";
const std::string modificationTimePrefix = "Modification time: ";

NoteWindow::NoteWindow(
	wxWindow* parent,
	wxPoint position,
	std::function<void(int)> onRemoveCallback,
	std::function<void(Note)> onUpdateCallback)
	: 
	wxWindow(parent, wxID_ANY, position, wxSize(600, 230))
{
	wxStaticText* titleText = new wxStaticText(this, wxID_ANY, "Title: ", wxPoint(0, 0), wxSize(50, -1));
	wxStaticText* textText = new wxStaticText(this, wxID_ANY, "Text: ", wxPoint(0, 30), wxSize(50, -1));
	wxStaticText* authorText = new wxStaticText(this, wxID_ANY, "Author: ", wxPoint(0, 90), wxSize(50, -1));
	this->titleView = nullptr;
	this->textView = nullptr;
	this->authorView = nullptr;
	this->tagsView = new wxStaticText(this, wxID_ANY, tagsPrefix, wxPoint(0, 120), wxSize(600, 30));
	this->creationTimeView = new wxStaticText(this, wxID_ANY, creationTimePrefix, wxPoint(0, 150), wxSize(600, 30));
	this->modificationTimeView = new wxStaticText(this, wxID_ANY, modificationTimePrefix, wxPoint(0, 180), wxSize(600, 30));
	this->buttonUpdate = nullptr;
	this->buttonRemove = nullptr;
	this->onRemoveCallback = onRemoveCallback;
	this->onUpdateCallback = onUpdateCallback;
}

void NoteWindow::setNote(Note note)
{
	if (buttonUpdate != nullptr) {
		delete[] buttonUpdate;
	}
	this->buttonUpdate = new wxButton(this, wxID_ANY, "Update", wxPoint(0, 210), wxSize(80, 20));
	this->buttonUpdate->Bind(wxEVT_BUTTON, &NoteWindow::OnUpdate, this);

	if (buttonRemove != nullptr) {
		delete[] buttonRemove;
	}
	this->buttonRemove = new wxButton(this, wxID_ANY, "Remove", wxPoint(100, 210), wxSize(80, 20));
	this->buttonRemove->Bind(wxEVT_BUTTON, &NoteWindow::OnRemove, this);

	this->note = note;

	if (titleView != nullptr) {
		delete[] titleView;
	}
	this->titleView = new wxTextCtrl(this, wxID_ANY, "", wxPoint(50, 0), wxSize(550, 30));

	if (textView != nullptr) {
		delete[] textView;
	}
	this->textView = new wxTextCtrl(this, wxID_ANY, "", wxPoint(50, 30), wxSize(550, 60), wxTE_MULTILINE);

	if (authorView != nullptr) {
		delete[] authorView;
	}
	this->authorView = new wxTextCtrl(this, wxID_ANY, "", wxPoint(50, 90), wxSize(550, 30));

	this->titleView->SetValue(note.getTitle());
	this->textView->SetValue(note.getText());
	this->tagsView->SetLabelText(tagsPrefix + note.getTagsStringified());
	this->creationTimeView->SetLabelText(creationTimePrefix + timeToString(note.getCreationTime()));
	this->modificationTimeView->SetLabelText(modificationTimePrefix + timeToString(note.getModificationTime()));
	this->authorView->SetValue(note.getAuthor());
}

void NoteWindow::clear()
{
	if (buttonUpdate != nullptr) {
		buttonUpdate->Unbind(wxEVT_BUTTON, &NoteWindow::OnUpdate, this);
		delete[] buttonUpdate;
		buttonUpdate = nullptr;
	}

	if (buttonRemove != nullptr) {
		buttonRemove->Unbind(wxEVT_BUTTON, &NoteWindow::OnRemove, this);
		delete[] buttonRemove;
		buttonRemove = nullptr;
	}

	if (titleView != nullptr) {
		delete[] titleView;
		titleView = nullptr;
	}

	if (textView != nullptr) {
		delete[] textView;
		textView = nullptr;
	}

	if (authorView != nullptr) {
		delete[] authorView;
		authorView = nullptr;
	}

	this->tagsView->SetLabelText(tagsPrefix);
	this->creationTimeView->SetLabelText(creationTimePrefix);
	this->modificationTimeView->SetLabelText(modificationTimePrefix);
}

void NoteWindow::OnRemove(wxCommandEvent& evt)
{
	onRemoveCallback(note.getId());
	clear();
}

void NoteWindow::OnUpdate(wxCommandEvent& evt)
{
	if (titleView->GetValue().size() > 0 && textView->GetValue().size() > 0) {
		note.setTitle((std::string)titleView->GetValue());
		note.setText((std::string)textView->GetValue());
		note.setModificationTime(time(NULL));
		note.setAuthor((std::string)authorView->GetValue());
		onUpdateCallback(note);
		modificationTimeView->SetLabelText(modificationTimePrefix + timeToString(note.getModificationTime()));
	}
}
