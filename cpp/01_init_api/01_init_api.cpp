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
    const char*  strMsgType     = nullptr;
    const char*  strSubMsgType  = nullptr;
    switch ( aMsgType )
    {
        case MessageType_Connection:
        {
            strMsgType = "CONNECTION";
            switch ( aSubMsgType )
            {
                case SubMessageType_Connection_SensorDisconnected   : { strSubMsgType = "Connection_SensorDisconnected";    break; }
                case SubMessageType_Connection_SensorConnected      : { strSubMsgType = "Connection_SensorConnected";       break; }
                default                                             : { strSubMsgType = "unknown";                          break; }
            }
            break;
        }
        case MessageType_Info:
        {
            strMsgType = "INFO";
            switch ( aSubMsgType )
            {
                case SubMessageType_Info_Status                         : { strSubMsgType = "Info_Status";                          break; }
                case SubMessageType_Info_Api                            : { strSubMsgType = "Info_Api";                             break; }
                case SubMessageType_Info_ParameterReceived              : { strSubMsgType = "Info_ParameterReceived";               break; }
                case SubMessageType_Info_ParameterFlashRewritten        : { strSubMsgType = "Info_ParameterFlashRewritten";         break; }
                case SubMessageType_Info_ReflectionFilterSucccess       : { strSubMsgType = "Info_ReflectionFilterSucccess";        break; }
                case SubMessageType_Info_CalibrationFileHeaderReceived  : { strSubMsgType = "Info_CalibrationFileHeaderReceived";   break; }
                case SubMessageType_Info_CalibrationFileDataReceived    : { strSubMsgType = "Info_CalibrationFileDataReceived";     break; }
                // case SubMessageType_Info_ApiInitialized                 : { strSubMsgType = "Info_ApiInitialized";                  break; }
                // case SubMessageType_Info_StatusReply                    : { strSubMsgType = "Info_StatusReply";                     break; }
                default                                                 : { strSubMsgType = "unknown";                              break; }
            }
            break;
        }
        case MessageType_Error:
        {
            strMsgType = "ERROR";
            switch ( aSubMsgType )
            {
                case SubMessageType_Error_SoftwareApplicationError        : { strSubMsgType = "Error_SoftwareApplicationError";         break; }
                case SubMessageType_Error_HardwareApplicationError        : { strSubMsgType = "Error_HardwareApplicationError";         break; }
                case SubMessageType_Error_Api                             : { strSubMsgType = "Error_Api";                              break; }
                case SubMessageType_Error_CalibrationFileNoDataInFlash    : { strSubMsgType = "Error_CalibrationFileNoDataInFlash";     break; }
                case SubMessageType_Error_CalibrationFileSendDataOverflow : { strSubMsgType = "Error_CalibrationFileSendDataOverflow";  break; }
                case SubMessageType_Error_CalibrationFileHeaderCorrupt    : { strSubMsgType = "Error_CalibrationFileHeaderCorrupt";     break; }
                case SubMessageType_Error_CalibrationFileDataCorrupt      : { strSubMsgType = "Error_CalibrationFileDataCorrupt";       break; }
                case SubMessageType_Error_CalibrationFileDataInvalid      : { strSubMsgType = "Error_CalibrationFileDataInvalid";       break; }
                default                                                   : { strSubMsgType = "unknown";                                break; }
            }
            break;
        }
        case MessageType_Data:
        {
            strMsgType = "DATA";
            switch ( aSubMsgType )
            {
                case SubMessageType_Data_Io                 : { strSubMsgType = "Data_Io";                break; }
                case SubMessageType_Data_SensorTemperature  : { strSubMsgType = "Data_SensorTemperature"; break; }
                case SubMessageType_Data_SystemParameter    : { strSubMsgType = "Data_SystemParameter";   break; }
                case SubMessageType_Data_MachineParameter   : { strSubMsgType = "Data_MachineParameter";  break; }
                default                                     : { strSubMsgType = "unknown";                break; }
            }
            break;
        }
        default:
        {
            strMsgType = "unknown";
            strSubMsgType = "unknown";
            break;
        }
    }

    std::cout << "<<< Status message: ";
    if ( NULL != aSensor )
    {
        std::cout << "CamIdx " << aSensor->cam_index << " ";
    }
    std::cout << "[" << strMsgType << "/" << strSubMsgType << "] - " << aMsg << ", (Data: " << aMsgData << ") >>>" << std::endl;

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
