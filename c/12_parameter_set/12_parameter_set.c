/*!
 * @copyright SmartRay GmbH (www.smartray.com)
 */

#include <string.h>
#include <stdbool.h>

#include <sr_api/sr_api.h>
#include "../util/util.h"



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

    sZILCounter += (uint32_t) aHeight;

    printf( "ZIL callback: received %4d profiles, overall: %u\n", aHeight, sZILCounter );

    return 0;
}


int statusMessage( SRSensor*       aSensor
                 , MessageType     aMsgType
                 , SubMessageType  aSubMsgType
                 , int             aMsgData
                 , char*           aMsg )
{
    const char*  strMsgType = NULL;
    const char*  strSubMsgType = NULL;
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
    
    char messageBuffer[1024] = "<<< Status message: ";
    if ( NULL != aSensor )
    {
        const int32_t camIndex = aSensor->cam_index;
        const size_t msgLen = strlen( messageBuffer );
        sprintf( messageBuffer + msgLen, "CamIdx %d ", camIndex );
    }

    const size_t msgLen = strlen( messageBuffer );
    sprintf( messageBuffer + msgLen, "[%s/%s] - %s (Data: %d) >>>", strMsgType, strSubMsgType, aMsg, aMsgData );

    printf( "%s\n", messageBuffer );

    return 0;
}



int main()
{
    printf( "Initializing API (SR_API_Initalize)\n" );

    const int32_t initStatusCode    = SR_API_Initalize( statusMessage );
    const bool    isApiInitialized  = ( SUCCESS <= initStatusCode );
    if ( ! isApiInitialized )
    {
        printf( "SR_API_Initalize failed with error: %d\n", initStatusCode );
    }

    bool status = isApiInitialized;

    SRSensor sensor;
    memset( &sensor, 0, sizeof( sensor ) );

    bool isSensorConnected = false;
    if ( status )
    {
        printf( "Connecting to sensor (SR_API_ConnectSensor)\n" );

        strcpy( sensor.IPAdr, DEFAULT_IP_ADR );
        sensor.portnum   = DEFAULT_PORT_NUM;
        sensor.cam_index = 0;

        const uint32_t timeoutInSeconds = 20;
        const int32_t connectStatusCode = SR_API_ConnectSensor( &sensor, timeoutInSeconds );
        isSensorConnected               = ( SUCCESS <= connectStatusCode );
        if ( ! isSensorConnected )
        {
            printf( "SR_API_ConnectSensor failed with error: %d\n", connectStatusCode );
        }
        status = isSensorConnected;
    }
    if ( status )
    {
        printf( "Loading parameter set file (SR_API_LoadParameterSetFromFile)\n" );

        const int32_t loadStatusCode = SR_API_LoadParameterSetFromFile( &sensor, "parameter_set.json" );
        const bool    isLoaded       = ( SUCCESS <= loadStatusCode );
        if ( ! isLoaded )
        {
            printf( "SR_API_LoadParameterSetFromFile failed with error: %d\n", loadStatusCode );
        }
        status = isLoaded;
    }

    if ( status )
    {
        printf( "Sending parameter set to sensor (SR_API_SendParameterSetToSensor)\n" );

        const int32_t sendStatusCode = SR_API_SendParameterSetToSensor( &sensor );
        const bool    isSent         = ( SUCCESS <= sendStatusCode );
        if ( ! isSent )
        {
            printf( "SR_API_SendParameterSetToSensor failed with error: %d\n", sendStatusCode );
        }
        status = isSent;
    }

    bool isAcquisitionStarted = false;
    if ( status )
    {
        printf( "Starting acquisition (SR_API_StartAcquisition)\n" );

        const int32_t  startAcquisitionStatus = SR_API_StartAcquisition( &sensor );
        isAcquisitionStarted                  = ( SUCCESS <= startAcquisitionStatus );
        if ( ! isAcquisitionStarted )
        {
            printf( "SR_API_StartAcquisition failed with error: %d\n", startAcquisitionStatus );
        }
        status = isAcquisitionStarted;
    }

    if ( status )
    {
        printf( "Waiting for data sent from other threads.\n" );

        // NOTE This is just an example, in practice you should use a more reasonable exit condition.
        sleepFor( 5 );
    }

        if ( isAcquisitionStarted )
    {
        printf( "Stopping acquisition (SR_API_StopAcquisition)\n" );
        const int32_t  stopAcquisitionStatus = SR_API_StopAcquisition( &sensor );
        status = status && ( SUCCESS <= stopAcquisitionStatus );
        if ( ! status )
        {
            printf( "SR_API_StopAcquisition failed with error: %d\n", stopAcquisitionStatus );
        }
    }

        if ( isSensorConnected )
    {
        printf( "Disconnecting from sensor (SR_API_DisconnectSensor)\n" );

        const int32_t disconnectStatusCode = SR_API_DisconnectSensor( &sensor );
        const bool isSensorDisconnected    = ( SUCCESS <= disconnectStatusCode );
        if ( ! isSensorDisconnected )
        {
            printf( "SR_API_DisconnectSensor failed with error: %d\n", disconnectStatusCode );
        }
        status = status && isSensorDisconnected;
    }
    if ( isApiInitialized )
    {
        printf( "Shutting down application (SR_API_Exit)\n" );
        const int32_t exitStatusCode = SR_API_Exit();
        const bool    isApiExited    = ( SUCCESS <= exitStatusCode );
        if ( ! isApiExited )
        {
            printf( "SR_API_Exit failed with error: %d\n", exitStatusCode );
        }
        status = status && isApiExited;
    }

    return status ? 0 : -1;
}
