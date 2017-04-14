/*
 * GPS Navigation ---An open source GPS navigation core software
 *
 *
 * Copyright (c) 2016  Aisin AW, Ltd
 *
 * This program is dual licensed under GPL version 2 or a commercial license.
 * See the LICENSE file distributed with this source file.
 */
#ifndef GENIVI_NAVICORE_H
#define GENIVI_NAVICORE_H

#include <dbus-c++/dbus.h>
#include "genivi-navigationcore-session_adaptor.h"
#include "genivi-navigationcore-routing_adaptor.h"
#include "genivi-navigationcore-mapmatchedposition_adaptor.h"
#include "genivi-navigationcore-guidance_adaptor.h"
#include "genivi-navigationcore-constants.h"
#include "glview.h"

class  NavigationCoreSession:
        public org::genivi::navigation::navigationcore::Session_adaptor
{
public:
    NavigationCoreSession(){}
    ::DBus::Struct< uint16_t, uint16_t, uint16_t, std::string > GetVersion();
};

class  Routing:
        public org::genivi::navigation::navigationcore::Routing_adaptor
{
public:
    Routing(){}
    ::DBus::Struct< uint16_t, uint16_t, uint16_t, std::string > GetVersion();
};

class  MapMatchedPosition:
        public org::genivi::navigation::navigationcore::MapMatchedPosition_adaptor
{
public:
    MapMatchedPosition(){}
    ::DBus::Struct< uint16_t, uint16_t, uint16_t, std::string > GetVersion();
};

class  Guidance:
        public org::genivi::navigation::navigationcore::Guidance_adaptor
{
public:
    Guidance(){}
    ::DBus::Struct< uint16_t, uint16_t, uint16_t, std::string > GetVersion();
};

class Navicore :
        public NavigationCoreSession,
        public Routing,
        public MapMatchedPosition,
        public Guidance,
        public DBus::IntrospectableAdaptor,
        DBus::ObjectAdaptor
{
    public:
        Navicore( DBus::Connection &connection );

        //-------------------------------
        //Session interface
        //-------------------------------
        void CreateSession(const std::string& client, int32_t& error, uint32_t& sessionHandle);
        int32_t DeleteSession(const uint32_t& sessionHandle);
        int32_t GetSessionStatus(const uint32_t& sessionHandle);
        std::vector< ::DBus::Struct< uint32_t, std::string > > GetAllSessions();

        //-------------------------------
        //Routing interface
        //-------------------------------
        void CreateRoute(const uint32_t& sessionHandle, int32_t& error, uint32_t& routeHandle);
        int32_t DeleteRoute(const uint32_t& sessionHandle, const uint32_t& routeHandle);
        int32_t SetCostModel(const uint32_t& sessionHandle, const uint32_t& routeHandle, const int32_t& costModel);
        int32_t GetCostModel(const uint32_t& routeHandle);
        std::vector< int32_t > GetSupportedCostModels();
        int32_t SetRoutePreferences(const uint32_t& sessionHandle, const uint32_t& routeHandle, const std::string& countryCode, const std::vector< ::DBus::Struct< int32_t, int32_t > >& roadPreferenceList, const std::vector< ::DBus::Struct< int32_t, int32_t > >& conditionPreferenceList);
        void GetRoutePreferences(const uint32_t& routeHandle, const std::string& countryCode, std::vector< ::DBus::Struct< int32_t, int32_t > >& roadPreferenceList, std::vector< ::DBus::Struct< int32_t, int32_t > >& conditionPreferenceList);
        void GetSupportedRoutePreferences(std::vector< ::DBus::Struct< int32_t, int32_t > >& routePreferencesList, std::vector< ::DBus::Struct< int32_t, int32_t > >& conditionPreferenceList);
        void SetRouteSchedule(const uint32_t& sessionHandle, const uint32_t& routeHandle, const std::map< int32_t, uint32_t >& routeSchedule);
        std::map< int32_t, uint32_t > GetRouteSchedule(const uint32_t& routeHandle, const std::vector< int32_t >& valuesToReturn);
        int32_t SetTransportationMeans(const uint32_t& sessionHandle, const uint32_t& routeHandle, const std::vector< int32_t >& transportationMeansList);
        std::vector< int32_t > GetTransportationMeans(const uint32_t& routeHandle);
        std::vector< int32_t > GetSupportedTransportationMeans();
        int32_t SetExcludedAreas(const uint32_t& sessionHandle, const uint32_t& routeHandle, const std::vector< std::vector< ::DBus::Struct< double, double > > >& excludedAreas);
        std::vector< std::vector< ::DBus::Struct< double, double > > > GetExcludedAreas(const uint32_t& routeHandle);
        int32_t SetWaypoints(const uint32_t& sessionHandle, const uint32_t& routeHandle, const bool& startFromCurrentPosition, const std::vector< std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > >& waypointsList);
        void GetWaypoints(const uint32_t& routeHandle, bool& startFromCurrentPosition, std::vector< std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > >& waypointsList);
        int32_t CalculateRoute(const uint32_t& sessionHandle, const uint32_t& routeHandle);
        void CancelRouteCalculation(const uint32_t& sessionHandle, const uint32_t& routeHandle);
        void CalculateAlternativeRoutes(const uint32_t& sessionHandle, const uint32_t& calculatedRoute, const uint16_t& numberOfAlternativeRoutes, int32_t& error, std::vector< uint32_t >& alternativeRoutesList);
        void GetRouteSegments(const uint32_t& routeHandle, const int16_t& detailLevel, const std::vector< int32_t >& valuesToReturn, const uint32_t& numberOfSegments, const uint32_t& offset, uint32_t& totalNumberOfSegments, std::vector< std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > >& routeSegments);
        std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > GetRouteOverview(const uint32_t& routeHandle, const std::vector< int32_t >& valuesToReturn);
        ::DBus::Struct< ::DBus::Struct< double, double >, ::DBus::Struct< double, double > > GetRouteBoundingBox(const uint32_t& routeHandle);
        std::vector< uint32_t > GetAllRoutes();
        void SetBlockedRouteStretches(const uint32_t& sessionHandle, const uint32_t& routeHandle, const std::vector< ::DBus::Struct< uint32_t, uint32_t > >& blockParameters);
        std::vector< ::DBus::Struct< uint32_t, uint32_t > > GetBlockedRouteStretches(const uint32_t& routeHandle);

        //-------------------------------
        //MapMatchedPosition interface
        //-------------------------------
        void SetSimulationMode(const uint32_t& sessionHandle, const bool& activate);
        int32_t GetSimulationStatus();
        bool subscribeForsimulationStatusChangedSelective();
        void unsubscribeFromsimulationStatusChangedSelective();
        void SetSimulationSpeed(const uint32_t& sessionHandle, const uint8_t& speedFactor);
        uint8_t GetSimulationSpeed();
        bool subscribeForsimulationSpeedChangedSelective();
        void unsubscribeFromsimulationSpeedChangedSelective();
        void StartSimulation(const uint32_t& sessionHandle);
        void PauseSimulation(const uint32_t& sessionHandle);
        void GetPosition(const std::vector< int32_t >& valuesToReturn, int32_t& error, std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > >& position);
        void SetPosition(const uint32_t& sessionHandle, const std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > >& position);
        void GetCurrentAddress(const std::vector< int32_t >& valuesToReturn, int32_t& error, std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > >& address);
        std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > GetPositionOnSegment(const std::vector< int32_t >& valuesToReturn);
        std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > GetStatus(const std::vector< int32_t >& valuesToReturn);

        //-------------------------------
        //Guidance interface
        //-------------------------------
        void StartGuidance(const uint32_t& sessionHandle, const uint32_t& routeHandle);
        void StopGuidance(const uint32_t& sessionHandle);
        int32_t SetVoiceGuidance(const bool& activate, const std::string& voice);
        void GetGuidanceDetails(bool& voiceGuidance, bool& vehicleOnTheRoad, bool& isDestinationReached, int32_t& maneuver);
        int32_t PlayVoiceManeuver();
        void GetWaypointInformation(const uint16_t& requestedNumberOfWaypoints, uint16_t& numberOfWaypoints, std::vector< ::DBus::Struct< uint32_t, uint32_t, int32_t, int32_t, int16_t, int16_t, bool, uint16_t > >& waypointsList);
        void GetDestinationInformation(uint32_t& offset, uint32_t& travelTime, int32_t& direction, int32_t& side, int16_t& timeZone, int16_t& daylightSavingTime);
        void GetManeuversList(const uint16_t& requestedNumberOfManeuvers, const uint32_t& maneuverOffset, int32_t& error, uint16_t& numberOfManeuvers, std::vector< ::DBus::Struct< std::vector< ::DBus::Struct< std::string, std::vector< ::DBus::Struct< int32_t, std::string > >, std::string > >, std::string, std::string, std::string, std::string, uint16_t, int32_t, uint32_t, std::vector< ::DBus::Struct< uint32_t, uint32_t, int32_t, int32_t, std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > > > > >& maneuversList);
        void SetRouteCalculationMode(const uint32_t& sessionHandle, const int32_t& routeCalculationMode);
        int32_t SkipNextManeuver(const uint32_t& sessionHandle);
        void GetGuidanceStatus(int32_t& guidanceStatus, uint32_t& routeHandle);
        int32_t SetVoiceGuidanceSettings(const int32_t& promptMode);
        int32_t GetVoiceGuidanceSettings();

        enum IconIndex
        {
            FLAG_START_IDX = 0,
            FLAG_DEST_IDX = 1,
            FLAG_PIN_IDX = 2
        };

        enum IconNum
        {
            FLAG_START_NUM = 21,
            FLAG_DEST_NUM = 22,
            FLAG_PIN_NUM = 3
        };

        enum SimulationStatus
        {
            SIMULATION_STATUS_NO_SIMULATION     = 544,
            SIMULATION_STATUS_RUNNING           = 545,
            //SIMULATION_STATUS_PAUSED          = 546, /* not supported yet */
            SIMULATION_STATUS_FIXED_POSITION    = 547
        };

    private:
        uint32_t CreateSession_internal(void);
        void SetIconVisibilityCoord(IconIndex index, bool visible,
            double lat = 0.0, double lon = 0.0, bool commit = false);
        void SetIconVisibility(IconIndex index, bool visible, bool commit = false);
        void FixSimulationStatus();

        uint32_t lastSession;
        std::string client;
        uint32_t lastRoute;
        bool IsSimulationMode;
        SimulationStatus SimulationStatus;
        std::vector< std::map< int32_t, ::DBus::Struct< uint8_t, ::DBus::Variant > > > route;
};

#endif // GENIVI_NAVICORE_H
