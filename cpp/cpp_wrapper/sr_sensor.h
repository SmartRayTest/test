/*!
 * @copyright SmartRay GmbH (www.smartray.com)
 */

#pragma once

#include <sr_api/sr_api.h>



class Sensor
{
    friend class SensorManager;

public:
    ~Sensor();

    int32_t setROI( const int32_t aOffsetX, const int32_t aWidth, const int32_t aOffsetY, const int32_t aHeight );
    int32_t getROI( int32_t& aOutOriginX, int32_t& aOutWidth, int32_t& aOutOriginY, int32_t& aOutHeight );
    int32_t getSensorGranularity( int32_t&  aOutRoiGranularityX, int32_t&  aOutRoiGranularityY );
    int32_t getSensorMaxDimensions( int32_t& aOutWidth, int32_t& aOutHeight );
    int32_t getSensorOrigin( int32_t& aOutOriginX, int32_t& aOutOriginY );

    int32_t setSmartXpress( const bool aEnable );
    int32_t getSmartXpress( bool& aOutEnable );
    int32_t setSmartXpressConfiguration( const char* const aConfigurationFilePath );
    int32_t getSmartXpressConfiguration( char* const aConfigurationFilePath, const uint32_t aBufferLength );

    int32_t enableSmartXtract( const bool aEnable );
    int32_t isEnabledSmartXtract( bool& aOutEnabled );
    int32_t archiveSmartXtractData( char const* const aFilename );
    int32_t disableArchiveSmartXtractData();
    int32_t setSmartXtractPreset( char const* const aSmartXtractPresetFilename );
    int32_t setSmartXtract3DDataGenerationMode( const DataGeneration3DModeType aMode );
    int32_t getSmartXtract3DDataGenerationMode( DataGeneration3DModeType& aOutMode );
    int32_t setSmartXtractAlgorithm( const SmartXtractAlgorithmType aMode );
    int32_t getSmartXtractAlgorithm( SmartXtractAlgorithmType& aOutMode );

    int32_t setExposureTime( const int32_t aExposureIndex, const int32_t aExposureTimeMicroSec );
    int32_t getExposureTime( const int32_t aExpIndex, int32_t& aOutExpTimeMicroS );
    int32_t setNumberOfExposureTimes( const int32_t aNumberOfExposureTimes );
    int32_t getNumberOfExposureTimes( int32_t& aOutNumberOfExposureTimes );
    int32_t setMultiExposureMode( const MultipleExposureMergeModeType aMode );
    int32_t getMultiExposureMode( MultipleExposureMergeModeType& aOutMultiExposureMergeMode );
    int32_t setMultiExposureMergeModeOptimalValue( const MultiExposureMergeModeOptimalValueType aType, const uint32_t aValue );
    int32_t getMultiExposureMergeModeOptimalValue( MultiExposureMergeModeOptimalValueType& aOutOptimalValueType, uint32_t& aOutOptimalValue );

    int32_t setGain( const bool aEnable, const int32_t aGainValue );
    int32_t getGain( bool& aOutEnable, int32_t& aOutGainValue );
    int32_t setPrefilterDefault();
    int32_t setPrefilterLaserLineThickness( const uint16_t aMin, const uint16_t aMax );
    int32_t getPrefilterLaserLineThickness( uint16_t& aOutMin, uint16_t& aOutMax );

    int32_t setStartTrigger( const StartTriggerSource aInput, const bool aEnable, const TriggerEdgeMode aMode );
    int32_t getStartTrigger( StartTriggerSource& aOutSource, bool& aOutEnable, TriggerEdgeMode& aOutCondition );
    int32_t setReadyForAcquisitionStatus( const int32_t aOutputChannel, const bool aEnable );
    int32_t getReadyForAcquisitionStatus( const int32_t aOutputChannel, bool& aOutEnable );

    int32_t setDataTriggerMode( const DataTriggerMode aMode );
    int32_t getDataTriggerMode( DataTriggerMode& aOutMode );
    int32_t setDataTriggerInternalFrequency( const uint16_t aInternalFrequency );
    int32_t getDataTriggerInternalFrequency( int32_t& aOutInternalFrequencyHz );
    int32_t setDataTriggerExternalTriggerSource( const DataTriggerSource aExternalTriggerSource );
    int32_t getDataTriggerExternalTriggerSource( DataTriggerSource& aOutExternalTriggerSource );
    int32_t setDataTriggerExternalTriggerParameters( const int32_t aTriggerDivider, const int32_t aTriggerDelay, const TriggerEdgeMode aTriggerDirection );
    int32_t getDataTriggerExternalTriggerParameters( int32_t& aOutTriggerDivider, int32_t& aOutTriggerDelay, TriggerEdgeMode& aOutTriggerDirection );
    int32_t getExternalTriggerRate( int32_t& aOutExternalTriggerRateHz );

    int32_t setLaserPower( const bool aPower );
    int32_t getLaserPower( bool& aOutPower );
    int32_t setLaserMode( const LaserMode aMode );
    int32_t getLaserMode( LaserMode& aOutMode );
    int32_t setLaserBrightness( const int32_t aLaserBrightnessPercent );
    int32_t getLaserBrightness( int32_t& aOutLaserBrightnessPercent );

    int32_t loadParametersFromFile( const char* const aFilename );
    int32_t sendParametersToSensor();
    int32_t saveParameterSet( const char* const aFileName );
    int32_t setImageAcquisitionType( const ImageAquisitionType aType );
    int32_t getImageAcquisitionType( ImageAquisitionType& aOutImageAcquisitionType );
    int32_t setAcquisitionMode( const AcquisitionMode aAcquisitionMode );
    int32_t getAcquisitionMode( AcquisitionMode& aOutAcquisitionMode );
    int32_t setNumberOfProfilesToCapture( const uint32_t aNumberOfProfiles );
    int32_t getNumberOfProfilesToCapture( uint32_t& aOutNumberOfProfiles );
    int32_t set3DLaserLineBrightnessThreshold( const int32_t aExposureIndex, const int32_t aThreshold );
    int32_t get3DLaserLineBrightnessThreshold( int32_t aExposureIndex, int32_t& aOutThreshold );
    int32_t setReflectionFilter( const bool aEnable, const int32_t aAlgorithm, const int32_t aPreset );
    int32_t getReflectionFilter( bool& aOutEnable, int32_t& aOutAlgorithm, int32_t& aOutPreset );

    int32_t getScanRate( int32_t& aOutScanRateHz, int32_t& aOutTriggerOverflow );
    int32_t getMaximumScanRate( int32_t& aOutMaxScanRateHz );
    int32_t getTransmissionRate( int32_t& aOutTransmissionRateHz );
    int32_t setPacketSize( const uint32_t aPacketSize );
    int32_t getPacketSize( uint32_t& aOutPacketSize );
    int32_t setPacketTimeOut( const uint32_t aPacketTimeOut );
    int32_t getPacketTimeOut( uint32_t& aOutPacketTimeOut );

    int32_t startAcquisition();
    int32_t stopAcquisition();

    int32_t setMetaDataExportEnabled( const bool aEnabled );        
    int32_t getMetaDataTimeStampPeriod( uint64_t& aOutTimeStamp );
    int32_t getSensorTemperature( float& aOutTemperature );

    int32_t loadCalibrationDataFromFile( char* const aFileName );
    int32_t loadCalibrationDataFromSensor();
    int32_t isCalibrationDataAvailableOnSensor( bool& aOutAvailable );

    int32_t createPointCloudSingleProfile( uint16_t* const      aProfile
                                         , const int32_t        aOriginX
                                         , const int32_t        aWidth
                                         , SR_3DPOINT* const    aPointCloud );
    int32_t createPointCloudMultipleProfile( uint16_t* const    aProfiles
                                           , const int32_t      aOriginX
                                           , const int32_t      aWidth
                                           , const int32_t      aNumberOfProfiles
                                           , SR_3DPOINT* const  aPointCloud );
    int32_t applyTransportResolution( SR_3DPOINT* const aWorld
                                    , const int32_t     aWidth
                                    , const int32_t     aHeight );
    
    int32_t getZmapDimensions( const int32_t    aOriginX
                             , const int32_t    aWidth
                             , const float      aLateralResolution
                             , const float      aVerticalResolution
                             , uint32_t&        aOutZMapWidth
                             , float&           aOutFovRange
                             , float&           aOutFovStartPos
                             , float&           aOutFovEndPos );
    int32_t createZMap( const uint32_t  aOriginX
                      , const uint32_t  aWidth
                      , const uint32_t  aHeight
                      , const float     aLateralResolution
                      , const float     aVerticalResolution
                      , uint16_t* const aProfile
                      , uint16_t* const aIntensity
                      , uint16_t* const aLlt
                      , uint32_t&       aOutZmapWidth
                      , uint16_t* const aZMap
                      , uint16_t* const aIntensityZMap
                      , uint16_t* const aLltZmap );
    int32_t setZmapResolution( const float aLateralResolution, const float aVerticalResolution );
    int32_t getZmapResolution( float& aOutLateralResolution, float& aOutVerticalResolution );
    int32_t getMeasurementRange( int32_t& aOutMin, int32_t& aOutMax );
    int32_t setTiltCorrectionPitch( const float aDegree );
    int32_t getTiltCorrectionPitch( float& aOutDegree );
    int32_t setTiltCorrectionYaw( const float aDegree );
    int32_t getTiltCorrectionYaw( float& aOutDegree );
    int32_t setTransportResolution( const float aTransportResolution );
    int32_t getTransportResolution( float& aOutTransportResolution );

    int32_t setSmartXactMode( const int32_t aMode );
    int32_t getSmartXactMode( int32_t& aOutMode );

    int32_t getSensorLicenseFeatures( char*&    aOutFeatures
                                    , const uint32_t  aNumberOfFeatures
                                    , const uint32_t  aBufferSize );

    int32_t getSensorNumberOfLicenseFeatures( uint32_t& aOutNumberOfFeatures
                                            , uint32_t& aOutMaxBufferSize );

    int32_t getSensorModelName( char* const aModelName, char* const aPartNumber );
    int32_t getSensorPartNumber( char* const aPartNumber );
    int32_t getSensorPartNumberRevision( uint16_t& aOutPartNumberRevision );
    int32_t getSensorSerialNumber( char* const aSerialNumber );
    int32_t getSensorFirmwareVersion( char* const aVersion );
    int32_t getSensorMacAddress( char* const aMacAddress );
    int32_t setSensorSubnetMask( const char* const aSubnetMask );
    int32_t getSensorSubnetMask( char* const aSubnetMask );
    int32_t setSensorNetworkGateway( const char* const aGateway );
    int32_t getSensorNetworkGateway( char* const aGateway );
    int32_t changeSensorIpAddress( unsigned char* const aIpAddress, const uint16_t aPortNumber );
    int32_t updateSensorFirmware( char* const aFileName );

    int32_t setDigitalOutput( const DigitalOutput aChannel, const bool aEnable );

private:
    Sensor( SRSensor* const aSensor );

    Sensor( const Sensor& aSensor ) = delete;
    Sensor( Sensor&& aSensor ) = delete;

    Sensor& operator=( const Sensor& aSensor ) = delete;
    Sensor& operator=( Sensor&& aSensor ) = delete;


    SRSensor* const mSensor{ nullptr };
};



inline Sensor::Sensor( SRSensor* const aSensor )
    : mSensor( aSensor )
{
}

inline Sensor::~Sensor()
{
    delete mSensor;
}



inline int32_t Sensor::setROI( const int32_t aOffsetX, const int32_t aWidth, const int32_t aOffsetY, const int32_t aHeight )
{
    return SR_API_SetROI( mSensor, aOffsetX, aWidth, aOffsetY, aHeight );
}

inline int32_t Sensor::getROI( int32_t& aOutOriginX, int32_t& aOutWidth, int32_t& aOutOriginY, int32_t& aOutHeight )
{
    return SR_API_GetROI( mSensor, &aOutOriginX, &aOutWidth, &aOutOriginY, &aOutHeight );
}

inline int32_t Sensor::getSensorGranularity( int32_t& aOutRoiGranularityX, int32_t& aOutRoiGranularityY )
{
    return SR_API_GetSensorGranularity( mSensor, &aOutRoiGranularityX, &aOutRoiGranularityY );
}

inline int32_t Sensor::getSensorMaxDimensions( int32_t& aOutWidth, int32_t& aOutHeight )
{
    return SR_API_GetSensorMaxDimensions( mSensor, &aOutWidth, &aOutHeight );
}

inline int32_t Sensor::getSensorOrigin( int32_t& aOutOriginX, int32_t& aOutOriginY )
{
    return SR_API_GetSensorOrigin( mSensor, &aOutOriginX, &aOutOriginY );
}

inline int32_t Sensor::setSmartXpress( const bool aEnable )
{
    return SR_API_SetSmartXpress( mSensor, aEnable );
}

inline int32_t Sensor::getSmartXpress( bool& aOutEnable )
{
    return SR_API_GetSmartXpress( mSensor, &aOutEnable );
}

inline int32_t Sensor::setSmartXpressConfiguration( const char* const aConfigurationFilePath )
{
    return SR_API_SetSmartXpressConfiguration( mSensor, aConfigurationFilePath );
}

inline int32_t Sensor::getSmartXpressConfiguration( char* const aConfigurationFilePath, const uint32_t aBufferLength )
{
    return SR_API_GetSmartXpressConfiguration( mSensor, aConfigurationFilePath, aBufferLength );
}

inline int32_t Sensor::enableSmartXtract( const bool aEnable )
{
    return SR_API_EnableSmartXtract( mSensor, aEnable );
}

inline int32_t Sensor::isEnabledSmartXtract( bool& aOutEnabled )
{
    return SR_API_IsEnabledSmartXtract( mSensor, &aOutEnabled );
}

inline int32_t Sensor::archiveSmartXtractData( char const* const aFilename )
{
    return SR_API_ArchiveSmartXtractData( mSensor, aFilename );
}

inline int32_t Sensor::disableArchiveSmartXtractData()
{
    return SR_API_DisableArchiveSmartXtractData( mSensor );
}

inline int32_t Sensor::setSmartXtractPreset( char const* const aSmartXtractPresetFilename )
{
    return SR_API_SetSmartXtractPreset( mSensor, aSmartXtractPresetFilename );
}

inline int32_t Sensor::setSmartXtract3DDataGenerationMode( const DataGeneration3DModeType aMode )
{
    return SR_API_SetSmartXtract3DDataGenerationMode( mSensor, aMode );
}

inline int32_t Sensor::getSmartXtract3DDataGenerationMode( DataGeneration3DModeType& aOutMode )
{
    return SR_API_GetSmartXtract3DDataGenerationMode( mSensor, &aOutMode );
}

inline int32_t Sensor::setSmartXtractAlgorithm( const SmartXtractAlgorithmType aMode )
{
    return SR_API_SetSmartXtractAlgorithm( mSensor, aMode );
}

inline int32_t Sensor::getSmartXtractAlgorithm( SmartXtractAlgorithmType& aOutMode )
{
    return SR_API_GetSmartXtractAlgorithm( mSensor, &aOutMode );
}

inline int32_t Sensor::setExposureTime( const int32_t aExposureIndex, const int32_t aExposureTimeMicroSec )
{
    return SR_API_SetExposureTime( mSensor, aExposureIndex, aExposureTimeMicroSec );
}

inline int32_t Sensor::getExposureTime( const int32_t aExpIndex, int32_t& aOutExpTimeMicroS )
{
    return SR_API_GetExposureTime( mSensor, aExpIndex, &aOutExpTimeMicroS );
}

inline int32_t Sensor::setNumberOfExposureTimes( const int32_t aNumberOfExposureTimes )
{
    return SR_API_SetNumberOfExposureTimes( mSensor, aNumberOfExposureTimes );
}

inline int32_t Sensor::getNumberOfExposureTimes( int32_t& aOutNumberOfExposureTimes )
{
    return SR_API_GetNumberOfExposureTimes( mSensor, &aOutNumberOfExposureTimes );
}

inline int32_t Sensor::setMultiExposureMode( const MultipleExposureMergeModeType aMode )
{
    return SR_API_SetMultiExposureMode( mSensor, aMode );
}

inline int32_t Sensor::getMultiExposureMode( MultipleExposureMergeModeType& aOutMultiExposureMergeMode )
{
    return SR_API_GetMultiExposureMode( mSensor, &aOutMultiExposureMergeMode );
}

inline int32_t Sensor::setMultiExposureMergeModeOptimalValue( const MultiExposureMergeModeOptimalValueType aType, const uint32_t aValue )
{
    return SR_API_SetMultiExposureMergeModeOptimalValue( mSensor, aType, aValue );
}

inline int32_t Sensor::getMultiExposureMergeModeOptimalValue( MultiExposureMergeModeOptimalValueType& aOutOptimalValueType, uint32_t& aOutOptimalValue )
{
    return SR_API_GetMultiExposureMergeModeOptimalValue( mSensor, &aOutOptimalValueType, &aOutOptimalValue );
}

inline int32_t Sensor::setGain( const bool aEnable, const int32_t aGainValue )
{
    return SR_API_SetGain( mSensor, aEnable, aGainValue );
}

inline int32_t Sensor::getGain( bool& aOutEnable, int32_t& aOutGainValue )
{
    return SR_API_GetGain( mSensor, &aOutEnable, &aOutGainValue );
}

inline int32_t Sensor::setPrefilterDefault()
{
    return SR_API_SetPrefilterDefault( mSensor );
}

inline int32_t Sensor::setPrefilterLaserLineThickness( const uint16_t aMin, const uint16_t aMax )
{
    return SR_API_SetPrefilterLaserLineThickness( mSensor, aMin, aMax );
}

inline int32_t Sensor::getPrefilterLaserLineThickness( uint16_t& aOutMin, uint16_t& aOutMax )
{
    return SR_API_GetPrefilterLaserLineThickness( mSensor, &aOutMin, &aOutMax );
}

inline int32_t Sensor::setStartTrigger( const StartTriggerSource aInput, const bool aEnable, const TriggerEdgeMode aMode )
{
    return SR_API_SetStartTrigger( mSensor, aInput, aEnable, aMode );
}

inline int32_t Sensor::getStartTrigger( StartTriggerSource& aOutSource, bool& aOutEnable, TriggerEdgeMode& aOutCondition )
{
    return SR_API_GetStartTrigger( mSensor, &aOutSource, &aOutEnable, &aOutCondition );
}

inline int32_t Sensor::setReadyForAcquisitionStatus( const int32_t aOutputChannel, const bool aEnable )
{
    return SR_API_SetReadyForAcquisitionStatus( mSensor, aOutputChannel, aEnable );
}

inline int32_t Sensor::getReadyForAcquisitionStatus( const int32_t aOutputChannel, bool& aOutEnable )
{
    return SR_API_GetReadyForAcquisitionStatus( mSensor, aOutputChannel, &aOutEnable );
}

inline int32_t Sensor::setDataTriggerMode( const DataTriggerMode aMode )
{
    return SR_API_SetDataTriggerMode( mSensor, aMode );
}

inline int32_t Sensor::getDataTriggerMode( DataTriggerMode& aOutMode )
{
    return SR_API_GetDataTriggerMode( mSensor, &aOutMode );
}

inline int32_t Sensor::setDataTriggerInternalFrequency( const uint16_t aInternalFrequency )
{
    return SR_API_SetDataTriggerInternalFrequency( mSensor, aInternalFrequency );
}

inline int32_t Sensor::getDataTriggerInternalFrequency( int32_t& aOutInternalFrequencyHz )
{
    return SR_API_GetDataTriggerInternalFrequency( mSensor, &aOutInternalFrequencyHz );
}

inline int32_t Sensor::setDataTriggerExternalTriggerSource( const DataTriggerSource aExternalTriggerSource )
{
    return SR_API_SetDataTriggerExternalTriggerSource( mSensor, aExternalTriggerSource );
}

inline int32_t Sensor::getDataTriggerExternalTriggerSource( DataTriggerSource& aOutExternalTriggerSource )
{
    return SR_API_GetDataTriggerExternalTriggerSource( mSensor, &aOutExternalTriggerSource );
}

inline int32_t Sensor::setDataTriggerExternalTriggerParameters( const int32_t aTriggerDivider, const int32_t aTriggerDelay, const TriggerEdgeMode aTriggerDirection )
{
    return SR_API_SetDataTriggerExternalTriggerParameters( mSensor, aTriggerDivider, aTriggerDelay, aTriggerDirection );
}

inline int32_t Sensor::getDataTriggerExternalTriggerParameters( int32_t& aOutTriggerDivider, int32_t& aOutTriggerDelay, TriggerEdgeMode& aOutTriggerDirection )
{
    return SR_API_GetDataTriggerExternalTriggerParameters( mSensor, &aOutTriggerDivider, &aOutTriggerDelay, &aOutTriggerDirection );
}

inline int32_t Sensor::getExternalTriggerRate( int32_t& aOutExternalTriggerRateHz )
{
    return SR_API_GetExternalTriggerRate( mSensor, &aOutExternalTriggerRateHz );
}

inline int32_t Sensor::setLaserPower( const bool aPower )
{
    return SR_API_SetLaserPower( mSensor, aPower );
}

inline int32_t Sensor::getLaserPower( bool& aOutPower )
{
    return SR_API_GetLaserPower( mSensor, &aOutPower );
}

inline int32_t Sensor::setLaserMode( const LaserMode aMode )
{
    return SR_API_SetLaserMode( mSensor, aMode );
}

inline int32_t Sensor::getLaserMode( LaserMode& aOutMode )
{
    return SR_API_GetLaserMode( mSensor, &aOutMode );
}

inline int32_t Sensor::setLaserBrightness( const int32_t aLaserBrightnessPercent )
{
    return SR_API_SetLaserBrightness( mSensor, aLaserBrightnessPercent );
}

inline int32_t Sensor::getLaserBrightness( int32_t& aOutLaserBrightnessPercent )
{
    return SR_API_GetLaserBrightness( mSensor, &aOutLaserBrightnessPercent );
}

inline int32_t Sensor::loadParametersFromFile( const char* const aFilename )
{
    return SR_API_LoadParameterSetFromFile( mSensor, aFilename );
}

inline int32_t Sensor::sendParametersToSensor()
{
    return SR_API_SendParameterSetToSensor( mSensor );
}

inline int32_t Sensor::saveParameterSet( const char* const aFileName )
{
    return SR_API_SaveParameterSet( mSensor, aFileName );
}

inline int32_t Sensor::setImageAcquisitionType( const ImageAquisitionType aType )
{
    return SR_API_SetImageAcquisitionType( mSensor, aType );
}

inline int32_t Sensor::getImageAcquisitionType( ImageAquisitionType& aOutImageAcquisitionType )
{
    return SR_API_GetImageAcquisitionType( mSensor, &aOutImageAcquisitionType );
}

inline int32_t Sensor::setAcquisitionMode( const AcquisitionMode aAcquisitionMode )
{
    return SR_API_SetAcquisitionMode( mSensor, aAcquisitionMode );
}

inline int32_t Sensor::getAcquisitionMode( AcquisitionMode& aOutAcquisitionMode )
{
    return SR_API_GetAcquisitionMode( mSensor, &aOutAcquisitionMode );
}

inline int32_t Sensor::setNumberOfProfilesToCapture( const uint32_t aNumberOfProfiles )
{
    return SR_API_SetNumberOfProfilesToCapture( mSensor, aNumberOfProfiles );
}

inline int32_t Sensor::getNumberOfProfilesToCapture( uint32_t& aOutNumberOfProfiles )
{
    return SR_API_GetNumberOfProfilesToCapture( mSensor, &aOutNumberOfProfiles );
}

inline int32_t Sensor::set3DLaserLineBrightnessThreshold( const int32_t aExposureIndex, const int32_t aThreshold )
{
    return SR_API_Set3DLaserLineBrightnessThreshold( mSensor, aExposureIndex, aThreshold );
}

inline int32_t Sensor::get3DLaserLineBrightnessThreshold( const int32_t aExposureIndex, int32_t& aOutThreshold )
{
    return SR_API_Get3DLaserLineBrightnessThreshold( mSensor, aExposureIndex, &aOutThreshold );
}

inline int32_t Sensor::setReflectionFilter( const bool aEnable, const int32_t aAlgorithm, const int32_t aPreset )
{
    return SR_API_SetReflectionFilter( mSensor, aEnable, aAlgorithm, aPreset );
}

inline int32_t Sensor::getReflectionFilter( bool& aOutEnable, int32_t& aOutAlgorithm, int32_t& aOutPreset )
{
    return SR_API_GetReflectionFilter( mSensor, &aOutEnable, &aOutAlgorithm, &aOutPreset );
}

inline int32_t Sensor::getScanRate( int32_t& aOutScanRateHz, int32_t& aOutTriggerOverflow )
{
    return SR_API_GetScanRate( mSensor, &aOutScanRateHz, &aOutTriggerOverflow );
}

inline int32_t Sensor::getMaximumScanRate( int32_t& aOutMaxScanRateHz )
{
    return SR_API_GetMaximumScanRate( mSensor, &aOutMaxScanRateHz );
}

inline int32_t Sensor::getTransmissionRate( int32_t& aOutTransmissionRateHz )
{
    return SR_API_GetTransmissionRate( mSensor, &aOutTransmissionRateHz );
}

inline int32_t Sensor::setPacketSize( const uint32_t aPacketSize )
{
    return SR_API_SetPacketSize( mSensor, aPacketSize );
}

inline int32_t Sensor::getPacketSize( uint32_t& aOutPacketSize )
{
    return SR_API_GetPacketSize( mSensor, &aOutPacketSize );
}

inline int32_t Sensor::setPacketTimeOut( const uint32_t aPacketTimeOut )
{
    return SR_API_SetPacketTimeOut( mSensor, aPacketTimeOut );
}

inline int32_t Sensor::getPacketTimeOut( uint32_t& aOutPacketTimeOut )
{
    return SR_API_GetPacketTimeOut( mSensor, &aOutPacketTimeOut );
}

inline int32_t Sensor::startAcquisition()
{
    return SR_API_StartAcquisition( mSensor );
}

inline int32_t Sensor::stopAcquisition()
{
    return SR_API_StopAcquisition( mSensor );
}

inline int32_t Sensor::setMetaDataExportEnabled( const bool aEnabled )
{
    return SR_API_SetMetaDataExportEnabled( mSensor, aEnabled );
}

inline int32_t Sensor::getMetaDataTimeStampPeriod( uint64_t& aOutTimeStamp )
{
    return SR_API_GetMetaDataTimeStampPeriod( mSensor, &aOutTimeStamp );
}

inline int32_t Sensor::getSensorTemperature( float& aOutTemperature )
{
    return SR_API_GetSensorTemperature( mSensor, &aOutTemperature );
}

inline int32_t Sensor::loadCalibrationDataFromFile( char* const aFileName )
{
    return SR_API_LoadCalibrationDataFromFile( mSensor, aFileName );
}

inline int32_t Sensor::loadCalibrationDataFromSensor()
{
    return SR_API_LoadCalibrationDataFromSensor( mSensor );
}

inline int32_t Sensor::isCalibrationDataAvailableOnSensor( bool& aOutAvailable )
{
    return SR_API_IsCalibrationDataAvailableOnSensor( mSensor, &aOutAvailable );
}

inline int32_t Sensor::createPointCloudSingleProfile( uint16_t*   const aProfile
                                                    , const int32_t     aOriginX
                                                    , const int32_t     aWidth
                                                    , SR_3DPOINT* const aPointCloud )
{
    return SR_API_CreatePointCloudSingleProfile( mSensor
                                               , aProfile
                                               , aOriginX
                                               , aWidth
                                               , aPointCloud );
}
inline int32_t Sensor::createPointCloudMultipleProfile( uint16_t*   const aProfiles
                                                      , const int32_t     aOriginX
                                                      , const int32_t     aWidth
                                                      , const int32_t     aNumberOfProfiles
                                                      , SR_3DPOINT* const aPointCloud )
{
    return SR_API_CreatePointCloudMultipleProfile( mSensor
                                                 , aProfiles
                                                 , aOriginX
                                                 , aWidth
                                                 , aNumberOfProfiles
                                                 , aPointCloud );
}

inline int32_t Sensor::applyTransportResolution( SR_3DPOINT* const aWorld
                                               , const int32_t     aWidth
                                               , const int32_t     aHeight )
{
    return SR_API_ApplyTransportResolution( mSensor, aWorld, aWidth, aHeight );
}
    
inline int32_t Sensor::getZmapDimensions( const int32_t aOriginX
                                        , const int32_t aWidth
                                        , const float   aLateralResolution
                                        , const float   aVerticalResolution
                                        , uint32_t&     aOutZMapWidth
                                        , float&        aOutFovRange
                                        , float&        aOutFovStartPos
                                        , float&        aOutFovEndPos )
{
    return SR_API_GetZmapDimensions( mSensor
                                   , aOriginX
                                   , aWidth
                                   , aLateralResolution
                                   , aVerticalResolution
                                   , &aOutZMapWidth
                                   , &aOutFovRange
                                   , &aOutFovStartPos
                                   , &aOutFovEndPos );
}

inline int32_t Sensor::createZMap( const uint32_t  aOriginX
                                 , const uint32_t  aWidth
                                 , const uint32_t  aHeight
                                 , const float     aLateralResolution
                                 , const float     aVerticalResolution
                                 , uint16_t* const aProfile
                                 , uint16_t* const aIntensity
                                 , uint16_t* const aLlt
                                 , uint32_t&       aOutZmapWidth
                                 , uint16_t* const aZMap
                                 , uint16_t* const aIntensityZMap
                                 , uint16_t* const aLltZmap )
{
    return SR_API_CreateZMap( mSensor
                            , aOriginX
                            , aWidth
                            , aHeight
                            , aLateralResolution
                            , aVerticalResolution
                            , aProfile
                            , aIntensity
                            , aLlt
                            , &aOutZmapWidth
                            , aZMap
                            , aIntensityZMap
                            , aLltZmap );
}

inline int32_t Sensor::setZmapResolution( const float aLateralResolution, const float aVerticalResolution )
{
    return SR_API_SetZmapResolution( mSensor, aLateralResolution, aVerticalResolution );
}

inline int32_t Sensor::getZmapResolution( float& aOutLateralResolution, float& aOutVerticalResolution )
{
    return SR_API_GetZmapResolution( mSensor, &aOutLateralResolution, &aOutVerticalResolution );
}

inline int32_t Sensor::getMeasurementRange( int32_t& aOutMin, int32_t& aOutMax )
{
    return SR_API_GetMeasurementRange( mSensor, &aOutMin, &aOutMax );
}

inline int32_t Sensor::setTiltCorrectionPitch( const float aDegree )
{
    return SR_API_SetTiltCorrectionPitch( mSensor, aDegree );
}

inline int32_t Sensor::getTiltCorrectionPitch( float& aOutDegree )
{
    return SR_API_GetTiltCorrectionPitch( mSensor, &aOutDegree );
}

inline int32_t Sensor::setTiltCorrectionYaw( const float aDegree )
{
    return SR_API_SetTiltCorrectionYaw( mSensor, aDegree );
}

inline int32_t Sensor::getTiltCorrectionYaw( float& aOutDegree )
{
    return SR_API_GetTiltCorrectionYaw( mSensor, &aOutDegree );
}

inline int32_t Sensor::setTransportResolution( const float aTransportResolution )
{
    return SR_API_SetTransportResolution( mSensor, aTransportResolution );
}

inline int32_t Sensor::getTransportResolution( float& aOutTransportResolution )
{
    return SR_API_GetTransportResolution( mSensor, &aOutTransportResolution );
}

inline int32_t Sensor::setSmartXactMode( const int32_t aMode )
{
    return SR_API_SetSmartXactMode( mSensor, aMode );
}

inline int32_t Sensor::getSmartXactMode( int32_t& aOutMode )
{
    return SR_API_GetSmartXactMode( mSensor, &aOutMode );
}

inline int32_t Sensor::getSensorLicenseFeatures( char*&    aOutFeatures
                                               , const uint32_t  aNumberOfFeatures
                                               , const uint32_t  aBufferSize )
{
    return SR_API_GetSensorLicenseFeatures( mSensor, &aOutFeatures, aNumberOfFeatures, aBufferSize );
}

inline int32_t Sensor::getSensorNumberOfLicenseFeatures( uint32_t& aOutNumberOfFeatures
                                                       , uint32_t& aOutMaxBufferSize )
{
    return SR_API_GetSensorNumberOfLicenseFeatures( mSensor, &aOutNumberOfFeatures, &aOutMaxBufferSize );
}

inline int32_t Sensor::getSensorModelName( char* const aModelName, char* const aPartNumber )
{
    return SR_API_GetSensorModelName( mSensor, aModelName, aPartNumber );
}

inline int32_t Sensor::getSensorPartNumber( char* const aPartNumber )
{
    return SR_API_GetSensorPartNumber( mSensor, aPartNumber );
}

inline int32_t Sensor::getSensorPartNumberRevision( uint16_t& aOutPartNumberRevision )
{
    return SR_API_GetSensorPartNumberRevision( mSensor, &aOutPartNumberRevision );
}

inline int32_t Sensor::getSensorSerialNumber( char* const aSerialNumber )
{
    return SR_API_GetSensorSerialNumber( mSensor, aSerialNumber );
}

inline int32_t Sensor::getSensorFirmwareVersion( char* const aVersion )
{
    return SR_API_GetSensorFirmwareVersion( mSensor, aVersion );
}

inline int32_t Sensor::getSensorMacAddress( char* const aMacAddress )
{
    return SR_API_GetSensorMacAddress( mSensor, aMacAddress );
}

inline int32_t Sensor::setSensorSubnetMask( const char* const aSubnetMask )
{
    return SR_API_SetSensorSubnetMask( mSensor, aSubnetMask );
}

inline int32_t Sensor::getSensorSubnetMask( char* const aSubnetMask )
{
    return SR_API_GetSensorSubnetMask( mSensor, aSubnetMask );
}

inline int32_t Sensor::setSensorNetworkGateway( const char* const aGateway )
{
    return SR_API_SetSensorNetworkGateway( mSensor, aGateway );
}

inline int32_t Sensor::getSensorNetworkGateway( char* const aGateway )
{
    return SR_API_GetSensorNetworkGateway( mSensor, aGateway );
}

inline int32_t Sensor::changeSensorIpAddress( unsigned char* const aIpAddress, const uint16_t aPortNumber )
{
    return SR_API_ChangeSensorIpAddress( mSensor, aIpAddress, aPortNumber );
}

inline int32_t Sensor::updateSensorFirmware( char* const aFileName )
{
    return SR_API_UpdateSensorFirmware( mSensor, aFileName );
}

inline int32_t Sensor::setDigitalOutput( const DigitalOutput aChannel, const bool aEnable )
{
    return SR_API_SetDigitalOutput( mSensor, aChannel, aEnable );
}
