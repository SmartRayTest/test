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

    if ( ( nullptr != aExtData ) && ( sizeof( SR_MetaData ) == aNumExtData ) )
    {
        const SR_MetaData* metadata = static_cast<const SR_MetaData*>( aExtData );

        std::cout << "Metadata export: " << std::endl;
	    for( int i = 0; i < aHeight; ++i )
	    {
		    std::cout << "----------------------- " << std::endl;
			std::cout << "Start trigger number  : " << metadata->StartTriggerNb         << std::endl;
			std::cout << "Data trigger number   : " << metadata->DataTriggerNb          << std::endl;
			std::cout << "Profile number        : " << metadata->ProfileNb              << std::endl;
			std::cout << "Timestamp             : " << metadata->TimeStamp              << std::endl;
			std::cout << "TimeStampSequence     : " << metadata->TimeStampSequence      << std::endl;
			std::cout << "Input_0_State         : " << metadata->Input_0_State          << std::endl;
			std::cout << "Input_1_State         : " << metadata->Input_1_State          << std::endl;
			std::cout << "QuadStepCountFiltered : " << metadata->QuadStepCountFiltered  << std::endl;
			std::cout << "QuadStepCountRaw      : " << metadata->QuadStepCountRaw       << std::endl;
			std::cout << "TriggerOverflow       : " << metadata->TriggerOverflow        << std::endl;
			std::cout << "OutputStatus          : " << metadata->OutputStatus           << std::endl;
			std::cout << "DataTriggerOverflowCnt: " << metadata->DataTriggerOverflowCnt << std::endl;

            ++metadata;
	    }
    }

    return 0;
}


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

    if ( status )
    {
        std::cout << "Loading calibration data" << std::endl;

        const int32_t loadCalibDataResult = sensor->loadCalibrationData();
        const bool    isCalibrated        = ( SUCCESS <= loadCalibDataResult );
        if ( ! isCalibrated )
        {
            std::cout << "Sensor::loadCalibrationData() failed with error: " << loadCalibDataResult << std::endl;
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

        const int32_t setTypeStatus = sensor->setAcquisitionType( ImageAquisitionType_ZMapIntensityLaserLineThickness );
        const bool    isTypeSet     = ( SUCCESS <= setTypeStatus );
        if ( ! isTypeSet )
        {
            std::cout << "Sensor::setAcquisitionType() failed with error: " << setTypeStatus << std::endl;
        }

        status = isTypeSet;
    }

    if ( status )
    {
        std::cout << "Enabling metadata export" << std::endl;

        const int32_t enableMetaStatus = sensor->setMetaDataExportEnabled( true );
        const bool    isMetaEnabled    = ( SUCCESS <= enableMetaStatus );
        if ( ! isMetaEnabled )
        {
            std::cout << "Sensor::setMetaDataExportEnabled() failed with error: " << enableMetaStatus << std::endl;
        }

        status = isMetaEnabled;
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