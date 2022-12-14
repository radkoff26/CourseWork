#pragma once
#include <wx/wx.h>
#include <map>
#include "App.h"
#include "Repository.h"

class DashboardFrame: public wxFrame
{
private:
	App* app;
	Repository* repository;
	void OnBack(wxCommandEvent& evt);
public:
	DashboardFrame(App* app, Repository* repository);
};

