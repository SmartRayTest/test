/*!
 * @copyright SmartRay GmbH (www.smartray.com)
 */

#include <string.h>
#include <stdbool.h>

#include <sr_api/sr_api.h>
#include "../util/util.h"



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
