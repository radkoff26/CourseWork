#include "AddNoteFrame.h"
#include "MainFrame.h"
#include <vector>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "Repository.h"
#include "Utils.h"

AddNoteFrame::AddNoteFrame(App* app, Repository* repository): wxFrame(nullptr, wxID_ANY, "Add Note")
{
	this->app = app;
	if (repository == nullptr) {
		this->repository = new Repository();
	}
	else {
		this->repository = repository;
	}
	this->panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));
	wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "Title:", wxPoint(100, 100), wxSize(50, 30));
	this->titleInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 100), wxSize(350, 30));
	wxStaticText* textLabel = new wxStaticText(panel, wxID_ANY, "Text:", wxPoint(100, 150), wxSize(50, 30));
	this->textInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 150), wxSize(350, 80), wxTE_MULTILINE);
	wxStaticText* authorLabel = new wxStaticText(panel, wxID_ANY, "Author:", wxPoint(100, 250), wxSize(50, 30));
	this->authorInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 250), wxSize(350, 30));
	wxStaticText* tagsLabel = new wxStaticText(panel, wxID_ANY, "Tags:", wxPoint(100, 300), wxSize(50, 30));
	this->tagsList = new wxListBox(panel, wxID_ANY, wxPoint(150, 300), wxSize(250, 180), {}, wxLB_MULTIPLE);
	this->submitButton = new wxButton(panel, wxID_ANY, "Add Note", wxPoint(150, 500), wxSize(100, 50));

	this->tags = this->repository->findAllTags();

	for (int i = 0; i < tags.size(); i++)
	{
		tagsList->Insert(tags[i].getTitle(), i);
	}

	submitButton->Bind(wxEVT_BUTTON, &AddNoteFrame::OnSubmit, this);
}

void AddNoteFrame::OnSubmit(wxCommandEvent& evt)
{
	std::string title = (std::string) this->titleInput->GetValue();
	title = trim(title);
	std::string text = (std::string) this->textInput->GetValue();
	text = trim(text);
	std::string author = (std::string)this->authorInput->GetValue();
	author = trim(author);
	std::vector<Tag> selectedTags;
	for (int i = 0; i < tags.size(); i++)
	{
		if (tagsList->IsSelected(i)) {
			selectedTags.push_back(tags.at(i));
		}
	}
	if (title.length() > 0 && text.length() > 0 && author.size() > 0) {
		this->repository->addNote(Note(0, title, text, selectedTags, 0, 0, author));
		this->app->switchToFrame(new MainFrame(this->app, {}, nullptr));
	}
}
