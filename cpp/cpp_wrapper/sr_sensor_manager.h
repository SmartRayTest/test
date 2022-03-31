/*!
 * @copyright SmartRay GmbH (www.smartray.com)
 */

#pragma once

#include <vector>

#include <sr_api/sr_api.h>
#include "sr_sensor.h"



class SensorManager
{
public:
    static int32_t init( const Callback_StatusMessage aCallback );
    static int32_t shutdown();

    static int32_t getAPIVersion( char*& aOutVersion );
    static int32_t getErrorMsg( const int32_t aErrorCode, char*& aOutErrMsg );

    static int32_t registerLiveImageCallback( const Callback_LiveImage aCallback );
    static int32_t registerPilImageCallback( const Callback_PilImage aCallback );
    static int32_t registerZilImageCallback( const Callback_ZilImage aCallback );
    static int32_t registerPointCloudCallback( const Callback_PointCloud aCallback );
    static int32_t registerMSRPointCloudCB( const Callback_MSRPointCloud aCallback );

    static int32_t createAndConnect( const char* const aIpAddress,
                                     const uint16_t    aUdpPort,
                                     const uint32_t    aCameraIndex,
                                     const uint32_t    aTimeoutSeconds,
                                     Sensor*&          aOutSensor );

    static int32_t disconnectAndDestroy( Sensor*& aInOutSensor );

    static int32_t applyTransportResolutionOffset( const float       aXCoordinateOffset
                                                 , SR_3DPOINT* const aWorld
                                                 , const int32_t     aSize );

    static int32_t MSR_EnableRegistration( const bool8_t aEnable );
    static int32_t MSR_LoadRegistrationFile( const char* const aFilePath );
    static int32_t MSR_SetZmapResolution( const double aTransportResolution,
                                          const double aLateralResolution,
                                          const double aVerticalResolution );
    static int32_t MSR_GetZmapResolution( double& aOutTransportResolution
                                        , double& aOutLateralResolution
                                        , double& aOutVerticalResolution );
    static int32_t MSR_CheckSettings();

    static int32_t MSR_SetZmapMergeMode( const MSRMergeModeType aMode );
    static int32_t MSR_GetZmapMergeMode( MSRMergeModeType& aOutMode );

    static int32_t meanFilter( const uint32_t        aKernelSizeX
                             , const uint32_t        aKernelSizeY
                             , const uint32_t        aExcludeZeros
                             , const uint32_t        aImageWidth
                             , const uint32_t        aImageHeight
                             , const uint16_t* const aInputData
                             ,       uint16_t* const aResultData );

    static int32_t medianFilter( const uint32_t        aKernelSizeX
                               , const uint32_t        aKernelSizeY
                               , const uint32_t        aExcludeZeros
                               , const uint32_t        aImageWidth
                               , const uint32_t        aImageHeight
                               , const uint16_t* const aInputData
                               ,       uint16_t* const aResultData );

    static int32_t outlierFilter_2DHeight( const uint32_t        aKernelSizeX
                                         , const uint32_t        aKernelSizeY
                                         , const uint32_t        aOutlierHeight
                                         , const double          aNeighbourRatio
                                         , const uint32_t        aImageWidth
                                         , const uint32_t        aImageHeight
                                         , const uint16_t* const aInputData
                                         ,       uint16_t* const aResultData );

    static int32_t smoothImage( uint16_t* const         aData
                              , const uint32_t          aWidth
                              , const uint32_t          aHeight
                              , const SmoothingPresets  aPreset );

    static int32_t enableFileLogging( const bool8_t aEnable, const char* const aFolderPath );
    static int32_t enableConsoleLogging( const bool8_t aEnable );

private:
    SensorManager();
};



SensorManager::SensorManager()
{
}


inline int32_t SensorManager::init( const Callback_StatusMessage aCallcack )
{
    const int32_t status = SR_API_Initalize( aCallcack );
    return status;
}

inline int32_t SensorManager::shutdown()
{
    const int32_t status = SR_API_Exit();
    return status;
}

inline int32_t SensorManager::getAPIVersion( char*& aOutVersion )
{
    return SR_API_GetAPIVersion( &aOutVersion );
}

inline int32_t SensorManager::getErrorMsg( const int32_t aErrorCode, char*& aOutErrMsg )
{
    return SR_API_GetErrorMsg( aErrorCode, &aOutErrMsg );
}

inline int32_t SensorManager::registerLiveImageCallback( const Callback_LiveImage aCallback )
{
    return SR_API_RegisterLiveImageCB( aCallback );
}

inline int32_t SensorManager::registerPilImageCallback( const Callback_PilImage aCallback )
{
    return SR_API_RegisterPilImageCB( aCallback );
}

inline int32_t SensorManager::registerZilImageCallback( const Callback_ZilImage aCallback )
{
    return SR_API_RegisterZilImageCB( aCallback );
}

inline int32_t SensorManager::registerPointCloudCallback( const Callback_PointCloud aCallback )
{
    return SR_API_RegisterPointCloudCB( aCallback );
}

inline int32_t SensorManager::registerMSRPointCloudCB( const Callback_MSRPointCloud aCallback )
{
    return SR_API_RegisterMSRPointCloudCB( aCallback );
}


inline int32_t SensorManager::createAndConnect( const char* const aIpAddress,
                                                const uint16_t    aUdpPort,
                                                const uint32_t    aCameraIndex,
                                                const uint32_t    aTimeoutSeconds,
                                                Sensor*&          aOutSensor )
{
    aOutSensor = nullptr;

    SRSensor* sensor = new SRSensor();
    memset( sensor, 0, sizeof( SRSensor ) );

    int32_t statusCode = ( nullptr == aIpAddress ) ? ERR_SR_API_ARG_NULLPOINTER : SUCCESS;
    if ( SUCCESS <= statusCode )
    {
 #if defined( _MSC_VER )
        strcpy_s( sensor->IPAdr, sizeof( sensor->IPAdr ), aIpAddress );
#else
        strcpy( sensor->IPAdr, aIpAddress );
#endif
    
        sensor->portnum   = aUdpPort;
        sensor->cam_index = aCameraIndex;

        statusCode = SR_API_ConnectSensor( sensor, aTimeoutSeconds );
    }

    if ( SUCCESS <= statusCode )
    {
        aOutSensor = new Sensor( sensor );
    }
    else
    {
        delete sensor;
        sensor = nullptr;
    }

    return statusCode;
}


inline int32_t SensorManager::disconnectAndDestroy( Sensor*& aInOutSensor )
{
    int32_t statusCode = ( nullptr == aInOutSensor ) ? ERR_SR_API_SRSENSOR_NULLPOINTER : SUCCESS;
    if ( SUCCESS <= statusCode )
    {
        statusCode = SR_API_DisconnectSensor( aInOutSensor->mSensor );
    }

    if ( SUCCESS <= statusCode )
    {
        delete aInOutSensor;
        aInOutSensor = nullptr;
    }
    
    return statusCode;
}

inline int32_t SensorManager::applyTransportResolutionOffset( const float       aXCoordinateOffset
                                                            , SR_3DPOINT* const aWorld
                                                            , const int32_t     aSize )
{
    return SR_API_ApplyTransportResolutionOffset( aXCoordinateOffset, aWorld, aSize );
}

inline int32_t SensorManager::MSR_EnableRegistration( const bool8_t aEnable )
{
    return SR_API_MSR_EnableRegistration( aEnable );
}

inline int32_t SensorManager::MSR_LoadRegistrationFile( const char* const aFilePath )
{
    return SR_API_MSR_LoadRegistrationFile( aFilePath );
}

inline int32_t SensorManager::MSR_SetZmapResolution( const double aTransportResolution
                                                   , const double aLateralResolution
                                                   , const double aVerticalResolution )
{
    return SR_API_MSR_SetZmapResolution( aTransportResolution, aLateralResolution, aVerticalResolution );
}

inline int32_t SensorManager::MSR_GetZmapResolution( double& aOutTransportResolution
                                                   , double& aOutLateralResolution
                                                   , double& aOutVerticalResolution )
{
    return SR_API_MSR_GetZmapResolution( &aOutTransportResolution, &aOutLateralResolution, &aOutVerticalResolution );
}

inline int32_t SensorManager::MSR_CheckSettings()
{
    return SR_API_MSR_CheckSettings();
}

inline int32_t SensorManager::MSR_SetZmapMergeMode( const MSRMergeModeType aMode )
{
    return SR_API_MSR_SetZmapMergeMode( aMode );
}

inline int32_t SensorManager::MSR_GetZmapMergeMode( MSRMergeModeType& aOutMode )
{
    return SR_API_MSR_GetZmapMergeMode( &aOutMode );
}

inline int32_t SensorManager::meanFilter( const uint32_t        aKernelSizeX
                                        , const uint32_t        aKernelSizeY
                                        , const uint32_t        aExcludeZeros
                                        , const uint32_t        aImageWidth
                                        , const uint32_t        aImageHeight
                                        , const uint16_t* const aInputData
                                        ,       uint16_t* const aResultData )
{
    return SR_API_MeanFilter( aKernelSizeX
                            , aKernelSizeY
                            , aExcludeZeros
                            , aImageWidth
                            , aImageHeight
                            , aInputData
                            , aResultData );
}

inline int32_t SensorManager::medianFilter( const uint32_t        aKernelSizeX
                                          , const uint32_t        aKernelSizeY
                                          , const uint32_t        aExcludeZeros
                                          , const uint32_t        aImageWidth
                                          , const uint32_t        aImageHeight
                                          , const uint16_t* const aInputData
                                          ,       uint16_t* const aResultData )
{
    return SR_API_MedianFilter( aKernelSizeX
                              , aKernelSizeY
                              , aExcludeZeros
                              , aImageWidth
                              , aImageHeight
                              , aInputData
                              , aResultData );
}

inline int32_t SensorManager::outlierFilter_2DHeight( const uint32_t        aKernelSizeX
                                                    , const uint32_t        aKernelSizeY
                                                    , const uint32_t        aOutlierHeight
                                                    , const double          aNeighbourRatio
                                                    , const uint32_t        aImageWidth
                                                    , const uint32_t        aImageHeight
                                                    , const uint16_t* const aInputData
                                                    ,       uint16_t* const aResultData )
{
    return SR_API_OutlierFilter_2DHeight( aKernelSizeX
                                        , aKernelSizeY
                                        , aOutlierHeight
                                        , aNeighbourRatio
                                        , aImageWidth
                                        , aImageHeight
                                        , aInputData
                                        , aResultData );
}

inline int32_t SensorManager::smoothImage( uint16_t* const        aData
                                         , const uint32_t         aWidth
                                         , const uint32_t         aHeight
                                         , const SmoothingPresets aPreset )
{
    return SR_API_SmoothImage( aData, aWidth, aHeight, aPreset );
}

inline int32_t SensorManager::enableFileLogging( const bool8_t aEnable, const char* const aFolderPath )
{
    return SR_API_EnableFileLogging( aEnable, aFolderPath );
}

inline int32_t SensorManager::enableConsoleLogging( const bool8_t aEnable )
{
    return SR_API_EnableConsoleLogging( aEnable );
}