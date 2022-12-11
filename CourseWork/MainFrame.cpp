#include "MainFrame.h"
#include <iostream>
#include <string>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "Repository.h"
#include "AddNoteFrame.h"
#include "AddTagFrame.h"

MainFrame::MainFrame(App* app, const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	this->app = app;

	this->repository = new Repository();

	Repository* repo = this->repository;

	this->onRemoveCallback = [this, repo](int id) {
		repo->deleteNote(id);
		this->notes = repo->findAllNotes();
		this->UpdateList();
	};

	this->onUpdateCallback = [this, repo](Note note) {
		repo->updateNote(note);
		this->notes = repo->findAllNotes();
		this->UpdateList();
	};

	this->panel = new wxPanel(this);

	this->addNoteButton = new wxButton(panel, wxID_ANY, "Add Note", wxPoint(65, 50), wxSize(170, 55));
	this->addTagButton = new wxButton(panel, wxID_ANY, "Add Tag", wxPoint(315, 50), wxSize(170, 55));
	this->filterButton = new wxButton(panel, wxID_ANY, "Filter", wxPoint(565, 50), wxSize(170, 55));
	this->notesList = new wxListBox(panel, wxID_ANY, wxPoint(150, 150), wxSize(500, 150), {}, wxLB_SINGLE);
	this->noteWindow = new NoteWindow(panel, wxPoint(100, 350), onRemoveCallback, onUpdateCallback);

	this->notes = repository->findAllNotes();

	this->UpdateList();

	this->notesList->Bind(wxEVT_LISTBOX, &MainFrame::OnSelectItem, this);
	this->addNoteButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddNote, this);
	this->addTagButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddTag, this);
}

void MainFrame::OnAddNote(wxCommandEvent& evt)
{
	app->switchToFrame(new AddNoteFrame(app, nullptr, "Add Note"));
}

void MainFrame::OnAddTag(wxCommandEvent& evt)
{
	app->switchToFrame(new AddTagFrame(app, nullptr, "Add Tag"));
}

void MainFrame::OnSelectItem(wxCommandEvent& evt)
{
	int index = evt.GetInt();
	this->noteWindow->setNote(this->notes[index]);
}

void MainFrame::UpdateList() {
	this->notesList->Clear();
	for (int i = 0; i < notes.size(); i++)
	{
		this->notesList->Insert(notes.at(i).getText(), i);
	}
}


