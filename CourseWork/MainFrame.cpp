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
#include "DashboardFrame.h"

MainFrame::MainFrame(App* app, std::vector<std::function<bool(Note)>> filters,Repository* repository): wxFrame(nullptr, wxID_ANY, "Home")
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

	this->addNoteButton = new wxButton(panel, wxID_ANY, "Add Note", wxPoint(50, 50), wxSize(100, 55));
	this->addTagButton = new wxButton(panel, wxID_ANY, "Add Tag", wxPoint(250, 50), wxSize(100, 55));
	this->filterButton = new wxButton(panel, wxID_ANY, "Filter", wxPoint(450, 50), wxSize(100, 55));
	this->dashboardButton = new wxButton(panel, wxID_ANY, "Dashboard", wxPoint(650, 50), wxSize(100, 55));
	this->notesList = new wxListBox(panel, wxID_ANY, wxPoint(150, 150), wxSize(500, 150), {}, wxLB_SINGLE);
	this->noteWindow = new NoteWindow(panel, wxPoint(100, 350), onRemoveCallback, onUpdateCallback);

	this->notes = this->repository->findAllNotes(filters);

	this->UpdateList();

	this->notesList->Bind(wxEVT_LISTBOX, &MainFrame::OnSelectItem, this);
	this->addNoteButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddNote, this);
	this->addTagButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddTag, this);
	this->filterButton->Bind(wxEVT_BUTTON, &MainFrame::OnAdjustFilters, this);
	this->dashboardButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpenDashboard, this);
}

void MainFrame::OnAddNote(wxCommandEvent& evt)
{
	app->switchToFrame(new AddNoteFrame(app, this->repository));
}

void MainFrame::OnAddTag(wxCommandEvent& evt)
{
	app->switchToFrame(new AddTagFrame(app, this->repository));
}

void MainFrame::OnAdjustFilters(wxCommandEvent& evt)
{
	app->switchToFrame(new FilterFrame(app, this->repository));
}

void MainFrame::OnOpenDashboard(wxCommandEvent& evt)
{
	app->switchToFrame(new DashboardFrame(app, this->repository));
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
