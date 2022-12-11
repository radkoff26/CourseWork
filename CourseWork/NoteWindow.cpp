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
	wxWindow(parent, wxID_ANY, position, wxSize(600, 200))
{
	wxStaticText* titleText = new wxStaticText(this, wxID_ANY, "Title: ", wxPoint(0, 0), wxSize(30, -1));
	wxStaticText* textText = new wxStaticText(this, wxID_ANY, "Text: ", wxPoint(0, 30), wxSize(30, -1));
	this->titleView = nullptr;
	this->textView = nullptr;
	this->tagsView = new wxStaticText(this, wxID_ANY, tagsPrefix, wxPoint(0, 60), wxSize(600, 30));
	this->creationTimeView = new wxStaticText(this, wxID_ANY, creationTimePrefix, wxPoint(0, 90), wxSize(600, 30));
	this->modificationTimeView = new wxStaticText(this, wxID_ANY, modificationTimePrefix, wxPoint(0, 120), wxSize(600, 30));
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
	this->buttonUpdate = new wxButton(this, wxID_ANY, "Update", wxPoint(0, 150), wxSize(80, 50));
	this->buttonUpdate->Bind(wxEVT_BUTTON, &NoteWindow::OnUpdate, this);

	if (buttonRemove != nullptr) {
		delete[] buttonRemove;
	}
	this->buttonRemove = new wxButton(this, wxID_ANY, "Remove", wxPoint(100, 150), wxSize(80, 50));
	this->buttonRemove->Bind(wxEVT_BUTTON, &NoteWindow::OnRemove, this);

	this->note = note;

	if (titleView != nullptr) {
		delete[] titleView;
	}
	this->titleView = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 0), wxSize(570, 30));

	if (textView != nullptr) {
		delete[] textView;
	}
	this->textView = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 30), wxSize(570, 30), wxTE_MULTILINE);

	this->titleView->SetValue(note.getTitle());
	this->textView->SetValue(note.getText());
	this->tagsView->SetLabelText(tagsPrefix + note.getTagsStringified());
	this->creationTimeView->SetLabelText(creationTimePrefix + timeToString(note.getCreationTime()));
	this->modificationTimeView->SetLabelText(modificationTimePrefix + timeToString(note.getModificationTime()));
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
		onUpdateCallback(note);
		modificationTimeView->SetLabelText(modificationTimePrefix + timeToString(note.getModificationTime()));
	}
}
