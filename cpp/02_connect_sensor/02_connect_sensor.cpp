/*!
 * @copyright SmartRay GmbH (www.smartray.com)
 */

#include <array>
#include <chrono>
#include <iostream>
#include <thread>

#include "../cpp_wrapper/sr_sensor.h"
#include "../cpp_wrapper/sr_sensor_manager.h"



int statusMessage( SRSensor*       aSensor
                 , MessageType     aMsgType
                 , SubMessageType  aSubMsgType
                 , int             aMsgData
                 , char*           aMsg )
{
    const char*  strMsgType = NULL;
    switch ( aMsgType )
    {
        case MessageType_Connection: { strMsgType = "CONNECTION"; break; }
        case MessageType_Info      : { strMsgType = "INFO";       break; }
        case MessageType_Error     : { strMsgType = "ERROR";      break; }
        case MessageType_Data      : { strMsgType = "DATA";       break; }
        default                    : { strMsgType = "unknown";    break; }
    }

    const char*  strSubMsgType = NULL;
    switch ( aSubMsgType )
    {
        case SubMessageType_Info_Status                           : { strSubMsgType = "Info_Status";                            break; }
        case SubMessageType_Info_Api                              : { strSubMsgType = "Info_Api";                               break; }
        case SubMessageType_Info_ParameterReceived                : { strSubMsgType = "Info_ParameterReceived";                 break; }
        case SubMessageType_Info_ParameterFlashRewritten          : { strSubMsgType = "Info_ParameterFlashRewritten";           break; }
        case SubMessageType_Info_ReflectionFilterSucccess         : { strSubMsgType = "Info_ReflectionFilterSucccess";          break; }
        case SubMessageType_Info_CalibrationFileHeaderReceived    : { strSubMsgType = "Info_CalibrationFileHeaderReceived";     break; }
        case SubMessageType_Info_CalibrationFileDataReceived      : { strSubMsgType = "Info_CalibrationFileDataReceived";       break; }

        case SubMessageType_Error_CalibrationFileNoDataInFlash    : { strSubMsgType = "Error_CalibrationFileNoDataInFlash";     break; }
        case SubMessageType_Error_CalibrationFileSendDataOverflow : { strSubMsgType = "Error_CalibrationFileSendDataOverflow";  break; }
        case SubMessageType_Error_CalibrationFileHeaderCorrupt    : { strSubMsgType = "Error_CalibrationFileHeaderCorrupt";     break; }
        case SubMessageType_Error_CalibrationFileDataCorrupt      : { strSubMsgType = "Error_CalibrationFileDataCorrupt";       break; }
        case SubMessageType_Error_CalibrationFileDataInvalid      : { strSubMsgType = "Error_CalibrationFileDataInvalid";       break; }
        case SubMessageType_Connection_SensorDisconnected         : { strSubMsgType = "Connection_SensorDisconnected";          break; }

        default                                                   : { strSubMsgType = "unknown";                                break; }
    }

    std::cout << "<<< Status message: ";
    if ( NULL != aSensor )
    {
        std::cout << aSensor->cam_index;
    }
    std::cout << "[" << strMsgType << "/" << strSubMsgType << "] - " << aMsg << ",Data: " << aMsgData << std::endl;

    return 0;
}



int main()
{
    std::cout << "Initializing" << std::endl;

    const int32_t initStatus    = SensorManager::init( statusMessage );
    const bool    isInitialized = ( SUCCESS <= initStatus );
    if ( ! isInitialized )
    {
        std::cout << "SensorManager::init() failed with error: " << initStatus << std::endl;
    }
    bool status = isInitialized;

    Sensor* sensor = nullptr;

    if ( status )
    {
        std::cout << "Connecting to sensor" << std::endl;

        const char* const ipAddress      = DEFAULT_IP_ADR;
        const uint16_t    udpPort        = DEFAULT_PORT_NUM;
        const uint32_t    cameraIndex    = 0;
        const uint32_t    timeoutSeconds = 10;
        const int32_t     connectStatus  = SensorManager::createAndConnect( ipAddress, udpPort, cameraIndex, timeoutSeconds, sensor );
        
        const bool isSensorConnected     = ( SUCCESS <= connectStatus );
        if ( ! isSensorConnected )
        {
            std::cout << "SensorManager::createAndConnect() failed with error: " << connectStatus << std::endl;
        }

        status = isSensorConnected;
    }

    if ( nullptr != sensor )
    {
        std::cout << "Disconnecting from sensor" << std::endl;

        const int32_t disconnectStatus     = SensorManager::disconnectAndDestroy( sensor );
        const bool    isSensorDisconnected = ( SUCCESS <= disconnectStatus );
        if ( ! isSensorDisconnected )
        {
            std::cout << "SensorManager::disconnectAndDestroy() failed with error: " << disconnectStatus << std::endl;
        }

        status = status && isSensorDisconnected;
    }

    if ( isInitialized )
    {
        std::cout << "Shutting down" << std::endl;

        const int32_t closeStatus = SensorManager::shutdown();
        const bool    isClosed    = ( SUCCESS <= closeStatus );
        if ( ! isClosed )
        {
            std::cout << "SensorManager::shutdown() failed with error: " << closeStatus << std::endl;
        }

        status = status && isClosed;
    }
    
    return status ? 0 : -1;
}
