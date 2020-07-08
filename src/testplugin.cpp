/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include "testplugin.h"
#include <QtCore/QTimerEvent>
#include <QtConcurrent/QtConcurrent>

#include "moc_testplugin.cpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

TestPlugin* plugin = 0;

TestPlugin::TestPlugin ()
: testTimer (this),
  testTimerId (-1)
{
	blog (LOG_INFO, "Welcome to TestPlugin!");
	
	// get notified if any OBS events happen
	obs_frontend_add_event_callback (handleOBSEvent, this);
	
	// try getting QTimer callbacks...
	if(!connect (&testTimer, &QTimer::timeout, this, &TestPlugin::timerCallback))
	{
		blog (LOG_INFO, "QTimer::timeout connection failed");
	}
	testTimer.setInterval (2000);
	testTimer.start ();
	
	// also try just using QObject's startTimer ()
	testTimerId = startTimer (1000);
}

TestPlugin::~TestPlugin ()
{
	blog (LOG_INFO, "TestPlugin dtor ()");
	
	killTimer (testTimerId);
	
	obs_frontend_remove_event_callback (handleOBSEvent, this);
}

void TestPlugin::timerEvent (QTimerEvent* event)
{
	// This never seems to get hit!
	blog (LOG_INFO, "TestPlugin::timerEvent");
	if(event->timerId () == testTimerId)
	{
		blog (LOG_INFO, "+");
	}
}
	
void TestPlugin::timerCallback ()
{
	// This never seems to get hit!
	blog (LOG_INFO, "TestPlugin::timerCallback");
}

void TestPlugin::handleOBSEvent (enum obs_frontend_event event, void* handler)
{
	// I get these events!
	blog (LOG_INFO, "TestPlugin::handleOBSEvent %d", (int)event);
}

bool obs_module_load (void)
{
    blog (LOG_INFO, "plugin loaded successfully (version %s)", PLUGIN_VERSION);
	
	// Setup event handler to start the server once OBS is ready
	auto eventCallback = [](enum obs_frontend_event event, void *param) 
	{
		if(event == OBS_FRONTEND_EVENT_FINISHED_LOADING) 
		{
			blog (LOG_INFO, "OBS_FRONTEND_EVENT_FINISHED_LOADING, creating TestPlugin");
			   
			plugin = new TestPlugin ();
			obs_frontend_remove_event_callback ((obs_frontend_event_cb)param, nullptr);
		}
	};
	obs_frontend_add_event_callback (eventCallback, (void*)(obs_frontend_event_cb)eventCallback);
	
    return true;
}

void obs_module_unload ()
{
	delete plugin;
	plugin = 0;
	
    blog (LOG_INFO, "plugin unloaded");
}
