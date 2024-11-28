/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2023 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "platform_hal.h"


INT platform_hal_GetDeviceConfigStatus(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetTelnetEnable(BOOLEAN* pFlag)
{
  /*TODO: Implement Me!*/
  (void)pFlag;
  return (INT)0;
}

INT platform_hal_SetTelnetEnable(BOOLEAN Flag)
{
  /*TODO: Implement Me!*/
  (void)Flag;
  return (INT)0;
}

INT platform_hal_GetSSHEnable(BOOLEAN* pFlag)
{
  /*TODO: Implement Me!*/
  (void)pFlag;
  return (INT)0;
}

INT platform_hal_SetSSHEnable(BOOLEAN Flag)
{
  /*TODO: Implement Me!*/
  (void)Flag;
  return (INT)0;
}

INT platform_hal_GetSNMPEnable(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_SetSNMPEnable(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetWebUITimeout(ULONG* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_SetWebUITimeout(ULONG value)
{
  /*TODO: Implement Me!*/
  (void)value;
  return (INT)0;
}

INT platform_hal_GetWebAccessLevel(INT userIndex, INT ifIndex, ULONG* pValue)
{
  /*TODO: Implement Me!*/
  (void)userIndex;
  (void)ifIndex;
  (void)pValue;
  return (INT)0;
}

INT platform_hal_SetWebAccessLevel(INT userIndex, INT ifIndex, ULONG value)
{
  /*TODO: Implement Me!*/
  (void)userIndex;
  (void)ifIndex;
  (void)value;
  return (INT)0;
}

INT platform_hal_PandMDBInit(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

INT platform_hal_DocsisParamsDBInit(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

INT platform_hal_GetModelName(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetRouterRegion(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetSerialNumber(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetHardwareVersion(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetSoftwareVersion(CHAR* pValue, ULONG maxSize)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  (void)maxSize;
  return (INT)0;
}

INT platform_hal_GetBootloaderVersion(CHAR* pValue, ULONG maxSize)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  (void)maxSize;
  return (INT)0;
}

INT platform_hal_GetFirmwareName(CHAR* pValue, ULONG maxSize)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  (void)maxSize;
  return (INT)0;
}

INT platform_hal_GetBaseMacAddress(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetHardware(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetHardware_MemUsed(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetHardware_MemFree(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetTotalMemorySize(ULONG* pulSize)
{
  /*TODO: Implement Me!*/
  (void)pulSize;
  return (INT)0;
}

INT platform_hal_GetUsedMemorySize(ULONG* pulSize)
{
  /*TODO: Implement Me!*/
  (void)pulSize;
  return (INT)0;
}

INT platform_hal_GetFreeMemorySize(ULONG* pulSize)
{
  /*TODO: Implement Me!*/
  (void)pulSize;
  return (INT)0;
}

INT platform_hal_GetFactoryResetCount(ULONG* pulSize)
{
  /*TODO: Implement Me!*/
  (void)pulSize;
  return (INT)0;
}

INT platform_hal_ClearResetCount(BOOLEAN bFlag)
{
  /*TODO: Implement Me!*/
  (void)bFlag;
  return (INT)0;
}

INT platform_hal_getTimeOffSet(CHAR* timeOffSet)
{
  /*TODO: Implement Me!*/
  (void)timeOffSet;
  return (INT)0;
}

INT platform_hal_SetDeviceCodeImageTimeout(INT seconds)
{
  /*TODO: Implement Me!*/
  (void)seconds;
  return (INT)0;
}

INT platform_hal_SetDeviceCodeImageValid(BOOLEAN flag)
{
  /*TODO: Implement Me!*/
  (void)flag;
  return (INT)0;
}

INT platform_hal_getFactoryPartnerId(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_getFactoryCmVariant(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_setFactoryCmVariant(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}
#ifdef FEATURE_RDKB_LED_MANAGER
int platform_hal_initLed(char* config_file_name)
{
  /*TODO: Implement Me!*/
  (void)config_file_name;
  return (int)0;
}
#endif
INT platform_hal_setLed(PLEDMGMT_PARAMS pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_getLed(PLEDMGMT_PARAMS pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

UINT platform_hal_getFanSpeed(UINT fanIndex)
{
  /*TODO: Implement Me!*/
  (void)fanIndex;
  return (UINT)0;
}

UINT platform_hal_getRPM(UINT fanIndex)
{
  /*TODO: Implement Me!*/
  (void)fanIndex;
  return (UINT)0;
}

INT platform_hal_getRotorLock(UINT fanIndex)
{
  /*TODO: Implement Me!*/
  (void)fanIndex;
  return (INT)0;
}

BOOLEAN platform_hal_getFanStatus(UINT fanIndex)
{
  /*TODO: Implement Me!*/
  (void)fanIndex;
  return (BOOLEAN)0;
}

INT platform_hal_setFanMaxOverride(BOOLEAN bOverrideFlag, UINT fanIndex)
{
  /*TODO: Implement Me!*/
  (void)bOverrideFlag;
  (void)fanIndex;
  return (INT)0;
}
#ifdef FEATURE_RDKB_THERMAL_MANAGER
INT platform_hal_initThermal(THERMAL_PLATFORM_CONFIG* pThermalPlatformConfig)
{
  /*TODO: Implement Me!*/
  (void)pThermalPlatformConfig;
  return (INT)0;
}

INT platform_hal_LoadThermalConfig(THERMAL_PLATFORM_CONFIG* pThermalPlatformConfig)
{
  /*TODO: Implement Me!*/
  (void)pThermalPlatformConfig;
  return (INT)0;
}

INT platform_hal_setFanSpeed(UINT fanIndex, FAN_SPEED fanSpeed, FAN_ERR* pErrReason)
{
  /*TODO: Implement Me!*/
  (void)fanIndex;
  (void)fanSpeed;
  (void)pErrReason;
  return (INT)0;
}

INT platform_hal_getFanTemperature(INT* pTemp)
{
  /*TODO: Implement Me!*/
  (void)pTemp;
  return (INT)0;
}

INT platform_hal_getInputCurrent(INT* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_getInputPower(INT* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_getRadioTemperature(INT radioIndex, INT* pValue)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)pValue;
  return (INT)0;
}

INT platform_hal_getEcoModeStatus(INT radioIndex, INT *pValue)
{
   /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)pValue;
  return (INT)0;
}
#endif
INT platform_hal_SetSNMPOnboardRebootEnable(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_GetMACsecEnable(INT ethPort, BOOLEAN* pFlag)
{
  /*TODO: Implement Me!*/
  (void)ethPort;
  (void)pFlag;
  return (INT)0;
}

INT platform_hal_SetMACsecEnable(INT ethPort, BOOLEAN Flag)
{
  /*TODO: Implement Me!*/
  (void)ethPort;
  (void)Flag;
  return (INT)0;
}

INT platform_hal_GetMACsecOperationalStatus(INT ethPort, BOOLEAN* pFlag)
{
  /*TODO: Implement Me!*/
  (void)ethPort;
  (void)pFlag;
  return (INT)0;
}

INT platform_hal_StartMACsec(INT ethPort, INT timeoutSec)
{
  /*TODO: Implement Me!*/
  (void)ethPort;
  (void)timeoutSec;
  return (INT)0;
}

INT platform_hal_StopMACsec(INT ethPort)
{
  /*TODO: Implement Me!*/
  (void)ethPort;
  return (INT)0;
}

INT platform_hal_GetMemoryPaths(RDK_CPUS index, PPLAT_PROC_MEM_INFO* ppinfo)
{
  /*TODO: Implement Me!*/
  (void)index;
  (void)ppinfo;
  return (INT)0;
}

INT platform_hal_GetDhcpv4_Options(dhcp_opt_list** req_opt_list, dhcp_opt_list** send_opt_list)
{
  /*TODO: Implement Me!*/
  (void)req_opt_list;
  (void)send_opt_list;
  return (INT)0;
}

INT platform_hal_GetDhcpv6_Options(dhcp_opt_list** req_opt_list, dhcp_opt_list** send_opt_list)
{
  /*TODO: Implement Me!*/
  (void)req_opt_list;
  (void)send_opt_list;
  return (INT)0;
}

INT platform_hal_SetLowPowerModeState(PPSM_STATE pState)
{
  /*TODO: Implement Me!*/
  (void)pState;
  return (INT)0;
}

INT platform_hal_getCMTSMac(CHAR* pValue)
{
  /*TODO: Implement Me!*/
  (void)pValue;
  return (INT)0;
}

INT platform_hal_setDscp(WAN_INTERFACE interfaceType, TRAFFIC_CNT_COMMAND cmd, char* pDscpVals)
{
  /*TODO: Implement Me!*/
  (void)interfaceType;
  (void)cmd;
  (void)pDscpVals;
  return (INT)0;
}

INT platform_hal_resetDscpCounts(WAN_INTERFACE interfaceType)
{
  /*TODO: Implement Me!*/
  (void)interfaceType;
  return (INT)0;
}

INT platform_hal_getDscpClientList(WAN_INTERFACE interfaceType, pDSCP_list_t pDSCP_List)
{
  /*TODO: Implement Me!*/
  (void)interfaceType;
  (void)pDSCP_List;
  return (INT)0;
}

INT platform_hal_GetCPUSpeed(char* cpuSpeed)
{
  /*TODO: Implement Me!*/
  (void)cpuSpeed;
  return (INT)0;
}

INT platform_hal_GetFirmwareBankInfo(FW_BANK bankIndex, PFW_BANK_INFO pFW_Bankinfo)
{
  /*TODO: Implement Me!*/
  (void)bankIndex;
  (void)pFW_Bankinfo;
  return (INT)0;
}

INT platform_hal_GetInterfaceStats(const char* ifname, PINTF_STATS pIntfStats)
{
  /*TODO: Implement Me!*/
  (void)ifname;
  (void)pIntfStats;
  return (INT)0;
}

INT platform_hal_GetPppUserName(CHAR* pUserName, ULONG maxSize)
{
   /*TODO: Implement Me!*/
  (void)pUserName;
  (void)maxSize;
  return (INT)0;
}

INT platform_hal_GetPppPassword(CHAR* pPassword, ULONG maxSize)
{
   /*TODO: Implement Me!*/
  (void)pPassword;
  (void)maxSize;
  return (INT)0;
}

INT platform_hal_qos_apply(const hal_network_params_t *params)
{
  /*TODO: Implement Me!*/
  (void)params;
  return (INT)0;
}
