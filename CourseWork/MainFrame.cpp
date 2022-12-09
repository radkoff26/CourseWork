#include "MainFrame.h"
#include <iostream>
#include <string>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "Repository.h"
#include "AddNoteFrame.h"

MainFrame::MainFrame(App* app, const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	this->app = app;

	this->repository = new Repository();

	this->panel = new wxPanel(this);

	this->addNoteButton = new wxButton(panel, wxID_ANY, "Add Note", wxPoint(65, 50), wxSize(170, 55));
	this->addTagButton = new wxButton(panel, wxID_ANY, "Add Tag", wxPoint(315, 50), wxSize(170, 55));
	this->filterButton = new wxButton(panel, wxID_ANY, "Filter", wxPoint(565, 50), wxSize(170, 55));
	this->notesList = new wxListCtrl(panel, wxID_ANY, wxPoint(150, 150), wxSize(500, -1), wxLC_LIST | wxLC_SINGLE_SEL);

	this->notes = repository->findAllNotes();

	for (int i = 0; i < notes.size(); i++)
	{
		this->notesList->InsertItem(i, notes.at(i).getText());
	}

	this->notesList->Bind(wxEVT_LIST_ITEM_SELECTED, &MainFrame::OnSelectItem, this);
	this->addNoteButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddNote, this);
}

void MainFrame::OnAddNote(wxCommandEvent& evt)
{
	app->switchToFrame(new AddNoteFrame(app, nullptr, "Add Note"));
}

void MainFrame::OnSelectItem(wxCommandEvent& evt)
{
	int id = ((wxListEvent&) evt).GetIndex();
	this->notesList->SetItem(id, 0, std::to_string(id));
}


