/*
 * GPS Navigation ---An open source GPS navigation core software
 *
 *
 * Copyright (c) 2016  Aisin AW, Ltd
 *
 * This program is dual licensed under GPL version 2 or a commercial license.
 * See the LICENSE file distributed with this source file.
 */
#ifndef GENIVI_MAPVIEWER_H
#define GENIVI_MAPVIEWER_H

#include <pthread.h>
#ifndef DBUS_HAS_RECURSIVE_MUTEX
#define DBUS_HAS_RECURSIVE_MUTEX
#endif
#include <dbus-c++/dbus.h>
#include "genivi-mapviewer-configuration_adaptor.h"
#include "genivi-mapviewer-session_adaptor.h"
#include "genivi-mapviewer-mapviewercontrol_adaptor.h"
#include "genivi-mapviewer-constants.h"

class  MapViewerSession
    : public org::genivi::navigation::mapviewer::Session_adaptor
{
        public:
        MapViewerSession(){}
        ::DBus::Struct< uint16_t, uint16_t, uint16_t, std::string > GetVersion();
};

class  Configuration
    : public org::genivi::navigation::mapviewer::Configuration_adaptor
{
        public:
        Configuration(){}
        ::DBus::Struct< uint16_t, uint16_t, uint16_t, std::string > GetVersion();
};

class  MapViewerControl
: public org::genivi::navigation::mapviewer::MapViewerControl_adaptor
{
        public:
        MapViewerControl(){}
        ::DBus::Struct< uint16_t, uint16_t, uint16_t, std::string > GetVersion();
};

class Mapviewer :
    public MapViewerSession,
        public Configuration,
        public MapViewerControl,
        public DBus::IntrospectableAdaptor,
        DBus::ObjectAdaptor
{
    public:
        Mapviewer( DBus::Connection &connection );

        //-------------------------------
        // Session interface
        //-------------------------------
        void CreateSession(const std::string& client, int32_t& error, uint32_t& sessionHandle);
        int32_t DeleteSession(const uint32_t& sessionHandle);
        int32_t GetSessionStatus(const uint32_t& sessionHandle);
        std::vector< ::DBus::Struct< uint32_t, std::string > > GetAllSessions();

        //-------------------------------
        // Configuration interface
        //-------------------------------
        void SetUnitsOfMeasurement(const std::map< int32_t, int32_t >& unitsOfMeasurementList);
        std::map< int32_t, int32_t > GetUnitsOfMeasurement();
        std::map< int32_t, std::vector< int32_t > > GetSupportedUnitsOfMeasurement();
        void SetTimeFormat(const int32_t& timeFormat);
        int32_t GetTimeFormat();
        std::vector< int32_t > GetSupportedTimeFormats();
        void SetCoordinatesFormat(const int32_t& coordinatesFormat);
        int32_t GetCoordinatesFormat();
        std::vector< int32_t > GetSupportedCoordinatesFormats();
        void SetLocale(const std::string& languageCode, const std::string& countryCode, const std::string& scriptCode);
        void GetLocale(std::string& languageCode, std::string& countryCode, std::string& scriptCode);
        std::vector< ::DBus::Struct< std::string, std::string, std::string > > GetSupportedLocales();

        //-------------------------------
        // Control interface
        //-------------------------------
        void CreateMapViewInstance(const uint32_t& sessionHandle, const ::DBus::Struct< uint16_t, uint16_t >& mapViewSize, const int32_t& mapViewType, int32_t& error, uint32_t& mapViewInstanceHandle);
        int32_t ReleaseMapViewInstance(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle);
        int32_t GetMapViewType(const uint32_t& mapViewInstanceHandle);
        std::vector< int32_t > GetSupportedMapViewTypes();
        void SetTargetPoint(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const ::DBus::Struct< double, double, double >& targetPoint);
        ::DBus::Struct< double, double, double > GetTargetPoint(const uint32_t& mapViewInstanceHandle);
        void SetFollowCarMode(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const bool& followCarMode);
        bool GetFollowCarMode(const uint32_t& mapViewInstanceHandle);
        void SetCameraPosition(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const ::DBus::Struct< double, double, double >& position);
        ::DBus::Struct< double, double, double > GetCameraPosition(const uint32_t& mapViewInstanceHandle);
        void SetCameraHeadingAngle(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& heading);
        void SetCameraHeadingToTarget(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const ::DBus::Struct< double, double >& target);
        void SetCameraHeadingTrackUp(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle);
        void GetCameraHeading(const uint32_t& mapViewInstanceHandle, int32_t& headingType, int32_t& headingAngle, ::DBus::Struct< double, double >& target);
        void SetCameraTiltAngle(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& tilt);
        int32_t GetCameraTiltAngle(const uint32_t& mapViewInstanceHandle);
        void SetCameraRollAngle(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& roll);
        int32_t GetCameraRollAngle(const uint32_t& mapViewInstanceHandle);
        void SetCameraDistanceFromTargetPoint(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const uint32_t& distance);
        uint32_t GetCameraDistanceFromTargetPoint(const uint32_t& mapViewInstanceHandle);
        void SetMapViewScaleMode(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& scaleMode);
        int32_t GetMapViewScaleMode(const uint32_t& mapViewInstanceHandle);
        std::vector< int32_t > GetSupportedMapViewScaleModes(const uint32_t& mapViewInstanceHandle);
        bool subscribeFormapViewScaleChangedSelective();
        void unsubscribeFrommapViewScaleChangedSelective();
        void SetCameraHeight(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const uint32_t& height);
        uint32_t GetCameraHeight(const uint32_t& mapViewInstanceHandle);
        void SetMapViewPerspective(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& perspective);
        int32_t GetMapViewPerspective(const uint32_t& mapViewInstanceHandle);
        std::vector< int32_t > GetSupportedMapViewPerspectives();
        void SetMapViewObjectVisibility(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::map< int32_t, bool >& objectVisibilityList);
        std::map< int32_t, bool > GetMapViewObjectVisibility(const uint32_t& mapViewInstanceHandle);
        std::vector< int32_t > GetSupportedMapViewObjectVisibilities(const uint32_t& mapViewInstanceHandle);
        std::vector< ::DBus::Struct< uint16_t, uint16_t, int32_t, uint32_t > > GetScaleList(const uint32_t& mapViewInstanceHandle);
        void SetMapViewScale(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const uint16_t& scaleID);
        void SetMapViewScaleByDelta(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int16_t& scaleDelta);
        void SetMapViewScaleByMetersPerPixel(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const double& metersPerPixel);
        void GetMapViewScale(const uint32_t& mapViewInstanceHandle, uint8_t& scaleID, int32_t& isMinMax);
        void SetMapViewBoundingBox(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const ::DBus::Struct< ::DBus::Struct< double, double >, ::DBus::Struct< double, double > >& boundingBox);
        ::DBus::Struct< ::DBus::Struct< double, double >, ::DBus::Struct< double, double > > GetMapViewBoundingBox(const uint32_t& mapViewInstanceHandle);
        void SetMapViewSaveArea(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const ::DBus::Struct< double, double, double, double >& saveArea);
        ::DBus::Struct< double, double, double, double > GetMapViewSaveArea(const uint32_t& mapViewInstanceHandle);
        void SetMapViewPan(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& panningAction, const std::vector< ::DBus::Struct< uint16_t, uint16_t > >& pixelCoordinates);
        std::vector< ::DBus::Struct< uint16_t, uint16_t > > GetMapViewPan(const uint32_t& mapViewInstanceHandle, const int32_t& valueToReturn);
        void SetMapViewRotation(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& rotationAngle, const int32_t& rotationAnglePerSecond);
        void GetMapViewRotation(const uint32_t& mapViewInstanceHandle, int32_t& rotationAngle, int32_t& rotationAnglePerFrame);
        void SetMapViewVisibilityMode(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& visibilityMode);
        int32_t GetMapViewVisibilityMode(const uint32_t& mapViewInstanceHandle);
        std::vector< int32_t > GetSupportedMapViewVisibilityModes();
        void SetMapViewPerformanceLevel(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& performanceLevel);
        int32_t GetMapViewPerformanceLevel(const uint32_t& mapViewInstanceHandle);
        std::vector< int32_t > GetSupportedMapViewPerformanceLevels();
        void DisplayRoute(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const uint32_t& routeHandle, const bool& highlighted);
        void HideRoute(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const uint32_t& routeHandle);
        std::vector< ::DBus::Struct< uint32_t, bool > > GetDisplayedRoutes(const uint32_t& mapViewInstanceHandle);
        std::vector< uint32_t > GetPoiCategoriesVisible(const uint32_t& mapViewInstanceHandle);
        void SetPoiCategoriesVisible(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::vector< uint32_t >& poiCategoryIds);
        void SetPoiCategoriesVisibleWithinLimits(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::vector< uint32_t >& poiCategoryIds, const uint8_t& minScaleID, const uint8_t& maxScaleID);
        void SetPoiCategoriesNotVisible(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::vector< uint32_t >& poiCategoryIds);
        void SetTrafficIncidentsVisibility(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const bool& visible);
        void SetMapViewTheme(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const int32_t& mapViewTheme);
        int32_t GetMapViewTheme(const uint32_t& mapViewInstanceHandle);
        std::vector< int32_t > GetSupportedMapViewThemes();
        void ConvertPixelCoordsToGeoCoords(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::vector< ::DBus::Struct< uint16_t, uint16_t > >& pixelCoordinates, int32_t& error, std::vector< ::DBus::Struct< double, double > >& geoCoordinates);
        void ConvertGeoCoordsToPixelCoords(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::vector< ::DBus::Struct< double, double > >& geoCoordinates, int32_t& error, std::vector< ::DBus::Struct< uint16_t, uint16_t > >& pixelCoordinates);
        std::vector< uint32_t > DisplayCustomElements(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::vector< ::DBus::Struct< std::string, std::string, ::DBus::Struct< double, double >, ::DBus::Struct< int16_t, int16_t > > >& customElements);
        void HideCustomElements(const uint32_t& sessionHandle, const uint32_t& mapViewInstanceHandle, const std::vector< uint32_t >& customElementHandles);
        std::map< uint32_t, ::DBus::Struct< std::string, std::string, ::DBus::Struct< double, double >, ::DBus::Struct< int16_t, int16_t > > > GetDisplayedCustomElements(const uint32_t& mapViewInstanceHandle);
        std::vector< ::DBus::Struct< int32_t, ::DBus::Struct< double, double >, ::DBus::Struct< uint8_t, ::DBus::Variant > > > SelectElementsOnMap(const uint32_t& mapViewInstanceHandle, const ::DBus::Struct< uint16_t, uint16_t >& pixelCoordinate, const std::vector< int32_t >& selectableTypes, const uint16_t& maxNumberOfSelectedElements);

private:
        std::vector< ::DBus::Struct< std::string, std::string, ::DBus::Struct< double, double >, ::DBus::Struct< int16_t, int16_t > > > CustomElementsStore;
        uint32_t lastSession, lastViewInstance;
        std::string client;
        pthread_t p;
};

#endif // GENIVI_MAPVIEWER_H
