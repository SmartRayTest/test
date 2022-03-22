/*!
 * @copyright SmartRay GmbH (www.smartray.com)
 */

#pragma once

#include <sr_api/sr_api.h>



class Sensor
{
    friend class SensorManager;

public:
    Sensor( SRSensor* const aSensor );
    ~Sensor();

    int32_t loadCalibrationData();
    int32_t loadParametersFromFile( const char* filename );
    int32_t sendParametersToSensor();

    int32_t setMetaDataExportEnabled( const bool aEnabled );
    int32_t setRoi( const int32_t aOffsetX, const int32_t aWidth, const int32_t aOffsetY, const int32_t aHeight );
    int32_t setExposureTime( const int32_t aExposureIndex, const int32_t aExposureTimeMicroSec );
    int32_t setNumberOfExposureTimes( const int32_t aNumberOfExposureTimes );
    int32_t setMultiExposureMode( const MultipleExposureMergeModeType aMode );
    int32_t setMultiExposureMergeModeOptimalValue( const MultiExposureMergeModeOptimalValueType aType, const uint32_t aValue );
    int32_t setAcquisitionType( const ImageAquisitionType aType );

    int32_t setDataTriggerMode( const DataTriggerMode aMode );
    int32_t setDataTriggerInternalFrequency( const uint16_t aInternalFrequency );
    int32_t setStartTrigger( const StartTriggerSource aInput, const bool aEnable, const TriggerEdgeMode aMode );

    int32_t startAcquisition();
    int32_t stopAcquisition();

private:
    Sensor( const Sensor& aSensor ) = delete;
    Sensor( Sensor&& aSensor ) = delete;

    Sensor& operator=( const Sensor& aSensor ) = delete;
    Sensor& operator=( Sensor&& aSensor ) = delete;

    SRSensor* const mSensor{ nullptr };
};



Sensor::Sensor( SRSensor* const aSensor )
    : mSensor( aSensor )
{
}

Sensor::~Sensor()
{
    delete mSensor;
}


int32_t Sensor::loadCalibrationData()
{
    return SR_API_LoadCalibrationDataFromSensor( mSensor );
}

int32_t Sensor::loadParametersFromFile( const char* filename )
{
    return SR_API_LoadParameterSetFromFile( mSensor, filename );
}

int32_t Sensor::sendParametersToSensor()
{
    return SR_API_SendParameterSetToSensor( mSensor );
}

int32_t Sensor::setMetaDataExportEnabled( const bool aEnabled )
{
    return SR_API_SetMetaDataExportEnabled( mSensor, aEnabled );
}

int32_t Sensor::setRoi( const int32_t aOffsetX, const int32_t aWidth, const int32_t aOffsetY, const int32_t aHeight )
{
    return SR_API_SetROI( mSensor, aOffsetX, aWidth, aOffsetY, aHeight );
}

int32_t Sensor::setExposureTime( const int32_t aExposureIndex, const int32_t aExposureTimeMicroSec )
{
    return SR_API_SetExposureTime( mSensor, aExposureIndex, aExposureTimeMicroSec );
}

int32_t Sensor::setNumberOfExposureTimes( const int32_t aNumberOfExposureTimes )
{
    return SR_API_SetNumberOfExposureTimes( mSensor, aNumberOfExposureTimes );
}

int32_t Sensor::setMultiExposureMode( const MultipleExposureMergeModeType aMode )
{
    return SR_API_SetMultiExposureMode( mSensor, aMode );
}

int32_t Sensor::setMultiExposureMergeModeOptimalValue( const MultiExposureMergeModeOptimalValueType aType, uint32_t aValue )
{
    return SR_API_SetMultiExposureMergeModeOptimalValue( mSensor, aType, aValue );
}

int32_t Sensor::setAcquisitionType( const ImageAquisitionType aType )
{
    return SR_API_SetImageAcquisitionType( mSensor, aType );
}

int32_t Sensor::setDataTriggerMode( const DataTriggerMode aMode )
{
    return SR_API_SetDataTriggerMode( mSensor, aMode );
}

int32_t Sensor::setDataTriggerInternalFrequency( const uint16_t aInternalFrequency )
{
    return SR_API_SetDataTriggerInternalFrequency( mSensor, aInternalFrequency );
}

int32_t Sensor::setStartTrigger( const StartTriggerSource aInput, const bool aEnable, const TriggerEdgeMode aMode )
{
    return SR_API_SetStartTrigger( mSensor, aInput, aEnable, aMode );
}

int32_t Sensor::startAcquisition()
{
    return SR_API_StartAcquisition( mSensor );
}

int32_t Sensor::stopAcquisition()
{
    return SR_API_StopAcquisition( mSensor );
}
