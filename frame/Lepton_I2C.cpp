#include "Lepton_I2C.h"
#include <stdio.h>

#include "leptonSDKEmb32PUB/LEPTON_SDK.h"
#include "leptonSDKEmb32PUB/LEPTON_SYS.h"
#include "leptonSDKEmb32PUB/LEPTON_Types.h"
#include "leptonSDKEmb32PUB/LEPTON_AGC.h"


LEP_SYS_FPA_TEMPERATURE_CELCIUS_T lepton_get_aux_temperature();
LEP_SYS_FPA_TEMPERATURE_CELCIUS_T lepton_get_fpa_temperature();


bool _connected;

LEP_CAMERA_PORT_DESC_T _port;



int lepton_connect() {
	LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
	_connected = true;
	return 0;
}

void GetAgcEnableState()
{
	
	if(!_connected) {
		lepton_connect();
	}


	//printf("\nSetting: %d",LEP_SetAgcEnableState(&_port, LEP_AGC_DISABLE));
	
	LEP_AGC_ENABLE_TAG agcEnableStatePtr;
	printf("\nGetting: %d",LEP_GetAgcEnableState(&_port, &agcEnableStatePtr));
	

	if (agcEnableStatePtr == LEP_AGC_DISABLE)
		{
				printf("\nLEP_AGC_DISABLE\n");

		}


	if (agcEnableStatePtr == LEP_AGC_ENABLE)
		{
				printf("\nLEP_AGC_ENABLE\n");

		}


	if (agcEnableStatePtr == LEP_END_AGC_ENABLE)
		{
				printf("\nLEP_END_AGC_ENABLE\n");

		}

}


int LeptonEnableAgc() {
	

	if(!_connected) {
		lepton_connect();
	}



	
	LEP_AGC_ENABLE_E agcCalculationEnableState;
	
	agcCalculationEnableState = LEP_AGC_ENABLE;
	LEP_SetAgcCalcEnableState(&_port, agcCalculationEnableState );


	LEP_AGC_ENABLE_E agcEnableState;
	agcEnableState = LEP_AGC_ENABLE;

	return LEP_SetAgcEnableState(&_port, agcEnableState );


}


void lepton_disable_auto_ffc() {
	

	if(!_connected) {
		lepton_connect();
	}

	LEP_SYS_FFC_SHUTTER_MODE_OBJ_T smo;
//	smo.shutterMode = LEP_SYS_FFC_SHUTTER_MODE_AUTO;
	smo.shutterMode = LEP_SYS_FFC_SHUTTER_MODE_MANUAL;

	smo.tempLockoutState = LEP_SYS_SHUTTER_LOCKOUT_INACTIVE;
	smo.videoFreezeDuringFFC = LEP_SYS_ENABLE;
	smo.ffcDesired = LEP_SYS_DISABLE;
	smo.desiredFfcPeriod = (LEP_UINT32)9999000;
	smo.explicitCmdToOpen = (LEP_BOOL)1;
	smo.desiredFfcTempDelta = 0;
	smo.imminentDelay = 300;
	LEP_SetSysFfcShutterModeObj(&_port, smo);

	printf("\nShutterMOde: %d", smo.shutterMode);
}

void lepton_perform_ffc() {
	if(!_connected) {
		lepton_connect();
	}


	LEP_RunSysFFCNormalization(&_port);
	
	LEP_STATUS_T_PTR ss;
	LEP_GetSysStatus(&_port,ss);

//	 printf<< "Flat field System Status: " << ss;


}


//	LEP_SYS_FFC_SHUTTER_MODE_OBJ_T smo
//	LEP_STATUS_T_PTR ss;

//	LEP_GetSysStatus(&_port,ss);

//	qDebug() << "System Status: " << ss;



//	qDebug() << "Ping Lepton: " << LEP_RunSysPing(&_port);


//	LEP_SYS_CUST_SERIAL_NUMBER_T_PTR sysSerialNumberPtr;
//	LEP_GetSysCustSerialNumber(&_port,sysSerialNumberPtr);
//	qDebug() << "Customer Serial Number: " << sysSerialNumberPtr;


//	if(tel_enbl == LEP_OK && tel_location == LEP_OK){
//		return 0;
//	}else{
//		return -1;
//	}
//
//}

LEP_SYS_FPA_TEMPERATURE_CELCIUS_T lepton_get_aux_temperature() {
	LEP_SYS_FPA_TEMPERATURE_CELCIUS_T ret;

	if(!_connected){
		lepton_connect();
	}

	LEP_GetSysAuxTemperatureCelcius(&_port, &ret);
	return ret;
}

LEP_SYS_FPA_TEMPERATURE_CELCIUS_T lepton_get_fpa_temperature() {
	LEP_SYS_FPA_TEMPERATURE_CELCIUS_T ret;

	if(!_connected){
		lepton_connect();
	}

	LEP_GetSysFpaTemperatureCelcius(&_port, &ret);
	return ret;
}

//presumably more commands could go here if desired
