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

typedef struct {int width; int height;} window_t;

void dbusServerLoop(Navicore **naviCore, Mapviewer **mapViewer, window_t *window);

DBus::BusDispatcher dispatcher;

static pthread_t g_dbus_thread;
void *dbus_api_server(void *vp);

void leave_signal_handler(int sig)
{
    dispatcher.leave();
}

void dbusServerLoop(Navicore **naviCore, Mapviewer **mapViewer, window_t *window)
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

    // Sessions of navicore and mapviewer has been created into navi.c
    // so it's needed to register it by calling CreateSession manually
    // NB: in the test scripts do not try to do it, beacuse there's only one session managed at the moment
    (*naviCore)->CreateSession(std::string("Navicore main"),error,sessionHandle);
    (*mapViewer)->CreateSession(std::string("Mapviewer main"),error,sessionHandle);

    // A mapview has been created into navi.c
    // so it's needed to register it by calling CreateMapViewInstance manually
    mapViewSize._1=window->width;
    mapViewSize._2=window->height;
    mapViewType=GENIVI_MAPVIEWER_MAIN_MAP;
    (*mapViewer)->CreateMapViewInstance(sessionHandle,mapViewSize,mapViewType,error,mapViewInstanceHandle);

    dispatcher.enter();
}

void *dbus_api_server(void *vp)
{
	Navicore  *naviCore;
	Mapviewer *mapViewer;
    window_t *window = (window_t *)vp;
    dbusServerLoop(&naviCore, &mapViewer, window);
	
    delete naviCore;
    delete mapViewer;
    
    pthread_exit(0);
}

static window_t s_window;

void CreateAPIServer(const int width, const int height)
{
	pthread_attr_t attr;
	
    s_window.width=width;
    s_window .height=height;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&g_dbus_thread, &attr, dbus_api_server, &s_window);
	pthread_attr_destroy(&attr);
}
