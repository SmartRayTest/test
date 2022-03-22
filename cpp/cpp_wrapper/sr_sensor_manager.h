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
    static int32_t init( Callback_StatusMessage aCallback );
    static int32_t shutdown();

    static int32_t registerLiveImageCallback( Callback_LiveImage aCallback );
    static int32_t registerPilImageCallback( Callback_PilImage aCallback );
    static int32_t registerZilImageCallback( Callback_ZilImage aCallback );
    static int32_t registerPointCloudCallback( Callback_PointCloud aCallback );

    static int32_t createAndConnect( const char* const aIpAddress,
                                     const uint16_t    aUdpPort,
                                     const uint32_t    aCameraIndex,
                                     const uint32_t    aTimeoutSeconds,
                                     Sensor*&          aOutSensor );

    static int32_t disconnectAndDestroy( Sensor*& aInOutSensor );

private:
    SensorManager();
};



SensorManager::SensorManager()
{
}


int32_t SensorManager::init( Callback_StatusMessage aCallcack )
{
    const int32_t status = SR_API_Initalize( aCallcack );
    return status;
}

int32_t SensorManager::shutdown()
{
    const int32_t status = SR_API_Exit();
    return status;
}


int32_t SensorManager::registerLiveImageCallback( Callback_LiveImage aCallback )
{
    return SR_API_RegisterLiveImageCB( aCallback );
}

int32_t SensorManager::registerPilImageCallback( Callback_PilImage aCallback )
{
    return SR_API_RegisterPilImageCB( aCallback );
}

int32_t SensorManager::registerZilImageCallback( Callback_ZilImage aCallback )
{
    return SR_API_RegisterZilImageCB( aCallback );
}

int32_t SensorManager::registerPointCloudCallback( Callback_PointCloud aCallback )
{
    return SR_API_RegisterPointCloudCB( aCallback );
}


int32_t SensorManager::createAndConnect( const char* const aIpAddress,
                                         const uint16_t    aUdpPort,
                                         const uint32_t    aCameraIndex,
                                         const uint32_t    aTimeoutSeconds,
                                         Sensor*&          aOutSensor )
{
    aOutSensor = nullptr;

    SRSensor* sensor = new SRSensor();
    memset( sensor, 0, sizeof( SRSensor ) );

 #if defined( _MSC_VER )
    strcpy_s( sensor->IPAdr, sizeof( sensor->IPAdr ), aIpAddress );
#else
    strcpy( sensor->IPAdr, aIpAddress );
#endif
    sensor->portnum   = aUdpPort;
    sensor->cam_index = aCameraIndex;

    const int32_t connectStatus = SR_API_ConnectSensor( sensor, aTimeoutSeconds );
    if ( SUCCESS <= connectStatus )
    {
        aOutSensor = new Sensor( sensor );
    }
    else
    {
        delete sensor;
        sensor = nullptr;
    }

    return connectStatus;
}


int32_t SensorManager::disconnectAndDestroy( Sensor*& aInOutSensor )
{
    if ( nullptr == aInOutSensor )
    {
        return ERR_SR_API_SRSENSOR_NULLPOINTER;
    }

    const int32_t disconnectStatus = SR_API_DisconnectSensor( aInOutSensor->mSensor );
    if ( SUCCESS <= disconnectStatus )
    {
        delete aInOutSensor;
        aInOutSensor = nullptr;
    }
    
    return disconnectStatus;
}
