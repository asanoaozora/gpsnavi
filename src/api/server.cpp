/*
 * GPS Navigation ---An open source GPS navigation core software
 *
 *
 * Copyright (c) 2016  Aisin AW, Ltd
 *
 * This program is dual licensed under GPL version 2 or a commercial license.
 * See the LICENSE file distributed with this source file.
 */
#include <stdio.h>
#include <signal.h>
#include "NaviTrace.h"
#include "server.h"
#include <pthread.h>

#include "genivi-navicore.h"
#include "genivi-mapviewer.h"

void dbusServerLoop(Navicore **naviCore, Mapviewer **mapViewer);

DBus::BusDispatcher dispatcher;

static pthread_t g_dbus_thread;
void *dbus_api_server(void *vp);

void leave_signal_handler(int sig)
{
    dispatcher.leave();
}

void dbusServerLoop(Navicore **naviCore, Mapviewer **mapViewer)
{
    signal(SIGTERM, leave_signal_handler);
    signal(SIGINT, leave_signal_handler);

    DBus::default_dispatcher = &dispatcher;
    DBus::Connection conn = DBus::Connection::SessionBus();
#ifdef STANDALONE
    conn.request_name("org.genivi.navigation");
#else
    conn.request_name("org.agl.gpsnavi");
#endif

    *naviCore = new Navicore(conn);
    *mapViewer = new Mapviewer(conn);
    TRACE_DEBUG("DBus server loop initialized");
    int32_t error;
    uint32_t sessionHandle;
    ::DBus::Struct< uint16_t, uint16_t > mapViewSize;
    int32_t mapViewType;
    uint32_t mapViewInstanceHandle;
#ifndef STANDALONE
    (*naviCore)->CreateSession(std::string("dummy"),error,sessionHandle);
#endif
    // Create an instance of mapviewer because it's done by default in the main()
    // it's necessary to be consistent !
    // TODO: creation of the mapview to be moved in CreateMapViewInstance
    (*mapViewer)->CreateSession(std::string("dummy"),error,sessionHandle);
    mapViewSize._1=0; //to be fixed
    mapViewSize._2=0; //to be fixed
    mapViewType=0; //to be fixed
    (*mapViewer)->CreateMapViewInstance(sessionHandle,mapViewSize,mapViewType,error,mapViewInstanceHandle);

    dispatcher.enter();
}

void *dbus_api_server(void *vp)
{
	Navicore  *naviCore;
	Mapviewer *mapViewer;
	
	dbusServerLoop(&naviCore, &mapViewer);
	
    delete naviCore;
    delete mapViewer;
    
    pthread_exit(0);
}

void CreateAPIServer(void)
{
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&g_dbus_thread, &attr, dbus_api_server, NULL);	
	pthread_attr_destroy(&attr);
}
