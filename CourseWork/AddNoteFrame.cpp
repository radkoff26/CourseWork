#include "AddNoteFrame.h"
#include "MainFrame.h"
#include <vector>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "Repository.h"
#include "Utils.h"

AddNoteFrame::AddNoteFrame(App* app, wxWindow* parent, const wxString& title): wxFrame(parent, wxID_ANY, title)
{
	this->app = app;
	this->repository = new Repository();
	this->panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));
	this->titleInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 100), wxSize(100, 100), wxTE_MULTILINE);
	this->textInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 250), wxSize(100, 100), wxTE_MULTILINE);
	this->tagsList = new wxListBox(panel, wxID_ANY, wxPoint(300, 100), wxSize(100, 400), {}, wxLB_MULTIPLE);
	this->submitButton = new wxButton(panel, wxID_ANY, "Add Note", wxPoint(100, 400), wxSize(90, 50));

	this->tags = repository->findAllTags();

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
	std::vector<Tag> selectedTags;
	for (int i = 0; i < tags.size(); i++)
	{
		if (tagsList->IsSelected(i)) {
			selectedTags.push_back(tags.at(i));
		}
	}
	if (title.length() > 0 && text.length() > 0) {
		this->repository->addNote(Note(0, title, text, selectedTags, 0, 0));
		this->app->switchToFrame(new MainFrame(this->app, "Main Frame"));
	}
}
