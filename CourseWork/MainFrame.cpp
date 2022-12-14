#include "MainFrame.h"
#include <iostream>
#include <string>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "Repository.h"
#include "AddNoteFrame.h"
#include "AddTagFrame.h"
#include "FilterFrame.h"

MainFrame::MainFrame(
	App* app, 
	const wxString& title, 
	std::vector<std::function<bool(Note)>> filters,
	Repository* repository
): wxFrame(nullptr, wxID_ANY, title)
{
	this->app = app;

	if (repository == nullptr) {
		this->repository = new Repository();
	}
	else {
		this->repository = repository;
	}

	Repository* repo = this->repository;

	this->onRemoveCallback = [this, repo, filters](int id) {
		repo->deleteNote(id);
		this->notes = repo->findAllNotes(filters);
		this->UpdateList();
	};

	this->onUpdateCallback = [this, repo, filters](Note note) {
		repo->updateNote(note);
		this->notes = repo->findAllNotes(filters);
		this->UpdateList();
	};

	this->panel = new wxPanel(this);

	this->addNoteButton = new wxButton(panel, wxID_ANY, "Add Note", wxPoint(65, 50), wxSize(170, 55));
	this->addTagButton = new wxButton(panel, wxID_ANY, "Add Tag", wxPoint(315, 50), wxSize(170, 55));
	this->filterButton = new wxButton(panel, wxID_ANY, "Filter", wxPoint(565, 50), wxSize(170, 55));
	this->notesList = new wxListBox(panel, wxID_ANY, wxPoint(150, 150), wxSize(500, 150), {}, wxLB_SINGLE);
	this->noteWindow = new NoteWindow(panel, wxPoint(100, 350), onRemoveCallback, onUpdateCallback);

	this->notes = this->repository->findAllNotes(filters);

	this->UpdateList();

	this->notesList->Bind(wxEVT_LISTBOX, &MainFrame::OnSelectItem, this);
	this->addNoteButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddNote, this);
	this->addTagButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddTag, this);
	this->filterButton->Bind(wxEVT_BUTTON, &MainFrame::OnAdjustFilters, this);
}

void MainFrame::OnAddNote(wxCommandEvent& evt)
{
	app->switchToFrame(new AddNoteFrame(app, nullptr, "Add Note", this->repository));
}

void MainFrame::OnAddTag(wxCommandEvent& evt)
{
	app->switchToFrame(new AddTagFrame(app, nullptr, "Add Tag", this->repository));
}

void MainFrame::OnAdjustFilters(wxCommandEvent& evt)
{
	app->switchToFrame(new FilterFrame(app, nullptr, this->repository));
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
		this->notesList->Insert(notes.at(i).toString(), i);
	}
}
