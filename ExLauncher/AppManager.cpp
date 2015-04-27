#include "AppManager.h"

using namespace std;

AppManager::AppManager()
{
}

AppManager::~AppManager()
{
}

bool AppManager::LoadApps()
{
#ifdef HAS_LIBOPK
	// OPK CODE
#else
	// If no libopk, for example when compiling and testing with Visual Studio, just load example data

	std::vector<App*>* categoryGames = new std::vector<App*>();
	std::vector<App*>* categoryApplications = new std::vector<App*>();
	std::vector<App*>* categorySettings = new std::vector<App*>();
	std::vector<App*>* categoryEmulators = new std::vector<App*>();

	App* appGame1 = new App();
	appGame1->SetData("name", "SameGoo");
	categoryGames->push_back(appGame1);
	App* appGame2 = new App();
	appGame2->SetData("name", "UMG");
	categoryGames->push_back(appGame2);
	App* appGame3 = new App();
	appGame3->SetData("name", "Jet Set Radio Future");
	categoryGames->push_back(appGame3);
	App* appGame4 = new App();
	appGame4->SetData("name", "Halo");
	categoryGames->push_back(appGame4);
	App* appGame5 = new App();
	appGame5->SetData("name", "Crysis");
	categoryGames->push_back(appGame5);
	App* appGame6 = new App();
	appGame6->SetData("name", "Final Fantasy");
	categoryGames->push_back(appGame6);

	App* app4 = new App();
	app4->SetData("name", "Console");
	categoryApplications->push_back(app4);

	App* app5 = new App();
	app5->SetData("name", "Wireless");
	categorySettings->push_back(app5);
	App* app6 = new App();
	app6->SetData("name", "Shutdown");
	categorySettings->push_back(app6);

	App* app7 = new App();
	app7->SetData("name", "Snes9x");
	categorySettings->push_back(app7);

	apps["games"] = categoryGames;
	apps["applications"] = categoryApplications;
	apps["settings"] = categorySettings;
	apps["emulators"] = categoryEmulators;
#endif

	return true;
}

map<string, vector<App*>*>* AppManager::GetAllApps()
{
	return &apps;
}

vector<App*>* AppManager::GetApps(string category)
{
	if (apps.count(category) == 0)
		return NULL;

	return apps[category];
}