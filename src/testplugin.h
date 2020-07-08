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

#pragma once

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <util/platform.h>

#include "plugin-macros.generated.h"

#include <QtCore/QObject>
#include <QtCore/QTimer>

class TestPlugin: public QObject
{
	Q_OBJECT
public:
	TestPlugin ();
	~TestPlugin ();
	
protected:
	// QObject
	void timerEvent (QTimerEvent *event);
	
public slots:
	void timerCallback ();
	
	
private:
	static void handleOBSEvent (enum obs_frontend_event event, void* handler);
	
	QTimer testTimer;
	int testTimerId;
};
