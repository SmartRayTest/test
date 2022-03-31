/*!
 * @copyright SmartRay GmbH (www.smartray.com)
 */

#include <array>
#include <chrono>
#include <iostream>
#include <thread>

#include "../cpp_wrapper/sr_sensor.h"
#include "../cpp_wrapper/sr_sensor_manager.h"



static uint32_t  sZILCounter = 0;

int onZILData( SRSensor*      aSensor
             , ImageDataType  aImageType
             , int            aHeight
             , int            aWidth
             , float          aVerticalResolution
             , float          aHorizontalResolution
             , uint16_t*      aZMapImage
             , uint16_t*      aIntensityImage
             , uint16_t*      aLLTImage
             , float          aOriginYMillimeters
             , int            aNumExtData
             , void*          aExtData )
{
    (void)aSensor;
    (void)aImageType;
    (void)aHeight;
    (void)aWidth;
    (void)aVerticalResolution;
    (void)aHorizontalResolution;
    (void)aZMapImage;
    (void)aIntensityImage;
    (void)aLLTImage;
    (void)aOriginYMillimeters;
    (void)aNumExtData;
    (void)aExtData;

    sZILCounter += static_cast<uint32_t>( aHeight );

    std::cout << "ZIL callback: received " << aHeight << " profiles, "
              << "overall: " << sZILCounter << std::endl;

    return 0;
}


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

    if ( status )
    {
        std::cout << "Loading calibration data" << std::endl;

        const int32_t loadCalibDataResult = sensor->loadCalibrationDataFromSensor();
        const bool    isCalibrated        = ( SUCCESS <= loadCalibDataResult );
        if ( ! isCalibrated )
        {
            std::cout << "Sensor::loadCalibrationDataFromSensor() failed with error: " << loadCalibDataResult << std::endl;
        }
        status = isCalibrated;
    }

    if ( status )
    {
        std::cout << "Registering ZIL image callback" << std::endl;

        const int32_t registerStatus = SensorManager::registerZilImageCallback( onZILData );
        const bool    isRegistered   = ( SUCCESS <= registerStatus );
        if ( ! isRegistered )
        {
            std::cout << "SensorManager::registerZilImageCallback() failed with error: " << registerStatus << std::endl;
        }
        status = isRegistered;
    }

    if ( status )
    {
        std::cout << "Setting acquisition type" << std::endl;

        const int32_t setTypeStatus = sensor->setImageAcquisitionType( ImageAquisitionType_ZMapIntensityLaserLineThickness );
        const bool    isTypeSet     = ( SUCCESS <= setTypeStatus );
        if ( ! isTypeSet )
        {
            std::cout << "Sensor::setImageAcquisitionType() failed with error: " << setTypeStatus << std::endl;
        }

        status = isTypeSet;
    }

    const std::array<int32_t, 4> multiExposureTimes { 10, 100, 1000, 10000 };

    if ( status )
    {
        size_t exposureIndex = 0;
        for ( const int32_t exposureTime : multiExposureTimes )
        {
            std::cout << "Setting exposure index " << exposureIndex << " to " << exposureTime << " microsecs" << std::endl;

            const int32_t setExposureStatus = sensor->setExposureTime( static_cast<int32_t>( exposureIndex ), exposureTime );
            const bool    isExposureSet     = ( SUCCESS <= setExposureStatus );        
            if ( ! isExposureSet )
            {
                std::cout << "Sensor::setExposureTime() failed with error: " << setExposureStatus << std::endl;
            }
            status = isExposureSet;
            ++exposureIndex;
        }
    }

    if ( status )
    {
        std::cout << "Setting the number of multiexposure times to be used" << std::endl;

        const int32_t setExpTimesStatusCode = sensor->setNumberOfExposureTimes( static_cast<int32_t>( multiExposureTimes.size() ) );
        const bool    isExpTimesSet         = ( SUCCESS <= setExpTimesStatusCode );
        if ( ! isExpTimesSet )
        {
            std::cout << "Sensor::setNumberOfExposureTimes() failed with error: " << setExpTimesStatusCode << std::endl;
        }
        status = isExpTimesSet;
    }

    if ( status )
    {
        std::cout << "Setting multiexposure mode" << std::endl;

        const int32_t setModeStatusCode = sensor->setMultiExposureMode( MultipleExposureMergeModeType_Merge );
        const bool    isModeSet         = ( SUCCESS <= setModeStatusCode );
        if ( ! isModeSet )
        {
            std::cout << "Sensor::setMultiExposureMode() failed with error: " << setModeStatusCode << std::endl;
        }
        status = isModeSet;
    }

    if ( status )
    {
        std::cout << "Starting acquisition" << std::endl;

        const int32_t startStatus = sensor->startAcquisition();
        const bool    isStarted   = ( SUCCESS <= startStatus );
        if ( ! isStarted )
        {
            std::cout << "Sensor::startAcquisition() failed with error: " << startStatus << std::endl;
        }

        status = isStarted;
    }

    if ( status )
    {
        std::cout << "Waiting for data sent from other threads." << std::endl;

        // NOTE This is just an example, in practice you should use a more reasonable exit condition.
        using namespace std::chrono_literals;
        std::this_thread::sleep_for( 5000ms );
    }

    if ( status )
    {
        std::cout << "Stopping acquisition" << std::endl;

        const int32_t stopStatus = sensor->stopAcquisition();
        const bool    isStopped  = ( SUCCESS <= stopStatus );
        if ( ! isStopped )
        {
            std::cout << "Sensor::stopAcquisition() failed with error: " << stopStatus << std::endl;
        }

        status = isStopped;
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
