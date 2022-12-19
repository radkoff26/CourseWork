#pragma once
#include <wx/wx.h>
#include <map>
#include "App.h"
#include "Repository.h"

class DashboardFrame: public wxFrame
{
public:
	DashboardFrame(App* app, Repository* repository);
	~DashboardFrame() {
		this->app = nullptr;
		this->repository = nullptr;
	}
private:
	App* app;
	Repository* repository;
	void OnBack(wxCommandEvent& evt);
};

