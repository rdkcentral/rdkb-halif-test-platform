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

/**
* @file test_l2_platform_hal.c
* @page platform_hal Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the platform_hal APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/
#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ut_log.h>
#include <ut.h>
#include "platform_hal.h"


#define BUFFER_SIZE 1024
#define TOTAL_FLASH_MANUAL_VALUE 4096

extern int MaxEthPort;
extern int get_MaxEthPort(void);
extern int init_platform_hal_init(void);

/**
* @brief Test case to verify the functionality of platform_hal_GetTelnetEnable() and platform_hal_SetTelnetEnable()
*
* This test case will get the current Telnet Enable status using platform_hal_GetTelnetEnable(), set using platform_hal_SetTelnetEnable() and verify the
* set value using platform_hal_GetTelnetEnable()
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetTelnetEnable_SetTelnetEnable( void )
{
    UT_LOG("Entering test_l2_platform_hal_GetTelnetEnable_SetTelnetEnable...");
    BOOLEAN currentStatus = FALSE;
    INT returnValue = 0;

    UT_LOG("Invoking platform_hal_GetTelnetEnable with valid parameter");
    returnValue = platform_hal_GetTelnetEnable(&currentStatus);
    UT_LOG("Return status: %d, Telnet status: %d", returnValue, currentStatus);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
    if (currentStatus)
    {

        UT_LOG("Invoking platform_hal_SetTelnetEnable with input parameter: FALSE");
        returnValue = platform_hal_SetTelnetEnable(FALSE);
        UT_LOG("Return status: %d", returnValue);
        UT_ASSERT_EQUAL(returnValue, RETURN_OK);

        UT_LOG("Invoking platform_hal_GetTelnetEnable with valid output parameter.");
        returnValue = platform_hal_GetTelnetEnable(&currentStatus);
        UT_LOG("Return status: %d, Telnet status: %d", returnValue, currentStatus);
        UT_ASSERT_EQUAL(returnValue, RETURN_OK);
        UT_ASSERT_EQUAL(currentStatus, FALSE);
    }
    else
    {
        UT_LOG("Invoking platform_hal_SetTelnetEnable with input parameter: TRUE");
        returnValue = platform_hal_SetTelnetEnable(TRUE);
        UT_LOG(" Return status: %d", returnValue);
        UT_ASSERT_EQUAL(returnValue, RETURN_OK);

        UT_LOG("Invoking platform_hal_GetTelnetEnable with valid output parameter");
        returnValue = platform_hal_GetTelnetEnable(&currentStatus);
        UT_LOG("Return status: %d, Telnet status: %d", returnValue, currentStatus);
        UT_ASSERT_EQUAL(returnValue, RETURN_OK);
        UT_ASSERT_EQUAL(currentStatus, TRUE);
    }

    UT_LOG("Exiting test_l2_platform_hal_GetTelnetEnable_SetTelnetEnable...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetSSHEnable() and platform_hal_GetSSHEnable()
*
* This test case will get the current SSH enable status using platform_hal_GetSSHEnable(), set using platform_hal_SetSSHEnable() and verify the
* set value using platform_hal_GetSSHEnable()
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetSSHEnable_SetSSHEnable( void )
{
    UT_LOG("Entering test_l2_platform_hal_GetSSHEnable_SetSSHEnable...");
    BOOLEAN SSHStatus = FALSE;
    INT operationStatus = 0;

    UT_LOG("Invoking platform_hal_GetSSHEnable with output parameter (valid). ");
    operationStatus = platform_hal_GetSSHEnable(&SSHStatus);
    UT_LOG("Return status : %d ssh status : %d ", operationStatus,SSHStatus);
    UT_ASSERT_EQUAL(operationStatus, RETURN_OK);

    if(SSHStatus)
    {
        UT_LOG("Invoking platform_hal_SetSSHEnable to disable SSH. input parameter: false");
        operationStatus = platform_hal_SetSSHEnable(false);
        UT_LOG("Return status : %d ", operationStatus);
        UT_ASSERT_EQUAL(operationStatus, RETURN_OK);

        UT_LOG("Invoking platform_hal_GetSSHEnable with output parameter (valid). ");
        operationStatus = platform_hal_GetSSHEnable(&SSHStatus);
        UT_LOG("Return status : %d ssh status : %d ", operationStatus,SSHStatus);
        UT_ASSERT_EQUAL(operationStatus, RETURN_OK);
        UT_ASSERT_EQUAL(SSHStatus, false);
    }
    else
    {
        UT_LOG("Invoking platform_hal_SetSSHEnable to enable SSH. input = true");
        operationStatus = platform_hal_SetSSHEnable(true);
        UT_LOG("Return status : %d ", operationStatus);
        UT_ASSERT_EQUAL(operationStatus, RETURN_OK);

        UT_LOG("Invoking platform_hal_GetSSHEnable invoking with valid output parameter");
        operationStatus = platform_hal_GetSSHEnable(&SSHStatus);
        UT_LOG("Return status : %d ", operationStatus);
        UT_ASSERT_EQUAL(operationStatus, RETURN_OK);
        UT_ASSERT_EQUAL(SSHStatus, true);
    }
    UT_LOG("Exiting test_l2_platform_hal_GetSSHEnable_SetSSHEnable...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetSNMPEnable() and platform_hal_SetSNMPEnable()
*
* This test case will get the current SNMP Enable value from the device using platform_hal_GetSNMPEnable(), set using platform_hal_SetSNMPEnable() and verify the
* set value using platform_hal_GetSNMPEnable().
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetSNMPEnable_SetSNMPEnable_GetSNMPEnable(void)
{
    UT_LOG("Entering test_l2_platform_hal_GetSNMPEnable_SetSNMPEnable_GetSNMPEnable...");
    CHAR oldValue[32] = {0};
    CHAR newValue[32] = {0};
    INT result = 0;

    UT_LOG("Invoking platform_hal_GetSNMPEnable with valid output parameter");
    result = platform_hal_GetSNMPEnable(oldValue);
    UT_LOG("Return status : %d snmp enable value : %s", result,oldValue);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    if (strcmp(oldValue, "rgWan") == 0)
    {
        strncpy(newValue, "rgDualIp", sizeof(newValue)-1);
    }
    else if (strcmp(oldValue, "rgDualIp") == 0)
    {
        strncpy(newValue, "rgLanIp", sizeof(newValue)-1);
    }
    else if(strcmp(oldValue, "rgLanIp") == 0)
    {
        strncpy(newValue, "rgWan", sizeof(newValue)-1);
    }
    else
    {
        UT_LOG("Unable to determine value to toggle SNMP status to.");
        UT_FAIL("Invalid SNMP enable value");
    }
    UT_LOG("Invoking platform_hal_SetSNMPEnable with '%s' ",newValue);
    result = platform_hal_SetSNMPEnable(newValue);
    UT_LOG("Return status : %d " ,result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Invoking platform_hal_GetSNMPEnable with valid output parameter");
    result = platform_hal_GetSNMPEnable(oldValue);
    UT_LOG("Return status : %d SNMP enable value : %s ", result,oldValue);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    if(!strcmp(oldValue,newValue))
    {
        UT_LOG("platform_hal_GetSNMPEnable  and platform_hal_SetSNMPEnable validation success");
        UT_PASS("platform_hal_GetSNMPEnable  and platform_hal_SetSNMPEnable validation success");
    }
    else
    {
        UT_LOG("platform_hal_GetSNMPEnable  and platform_hal_SetSNMPEnable validation failed");
        UT_FAIL("platform_hal_GetSNMPEnable  and platform_hal_SetSNMPEnable validation failed");
    }
    UT_LOG("Exiting test_l2_platform_hal_GetSNMPEnable_SetSNMPEnable_GetSNMPEnable...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetWebUITimeout() and platform_hal_SetWebUITimeout()
*
* This test case will get the current WebUI timeout value using platform_hal_GetWebUITimeout(), set using platform_hal_SetWebUITimeout() and verify the
* set value using platform_hal_GetWebUITimeout()
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetWebUITimeout_SetWebUITimeout_GetWebUITimeout(void)
{
    UT_LOG("Entering test_l2_platform_hal_GetWebUITimeout_SetWebUITimeout_GetWebUITimeout...");
    ULONG timeoutValue = 0;
    INT returnValue = 0;
    ULONG newTimeoutValue = 0;

    UT_LOG("Invoked platform_hal_GetWebUITimeout with valid ULONG pointer");
    returnValue = platform_hal_GetWebUITimeout(&timeoutValue);
    UT_LOG("Return value: %d, Timeout value: %lu", returnValue, timeoutValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    if(timeoutValue == 300)
    {
        timeoutValue = 500;
    }
    else
    {
        timeoutValue = 300;
    }

    UT_LOG("Invoking  platform_hal_SetWebUITimeout with value: %lu ",timeoutValue);
    returnValue = platform_hal_SetWebUITimeout(timeoutValue);
    UT_LOG("Return status : %d ",returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    UT_LOG("Invoked platform_hal_GetWebUITimeout again with valid ULONG pointer");
    returnValue = platform_hal_GetWebUITimeout(&newTimeoutValue);
    UT_LOG("Return value: %d, New Timeout value: %lu", returnValue, newTimeoutValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
    UT_ASSERT_EQUAL(newTimeoutValue, timeoutValue);
    UT_LOG("Exiting test_l2_platform_hal_GetWebUITimeout_SetWebUITimeout_GetWebUITimeout...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetHardware() and platform_hal_GetHardware_MemUsed()
*
* This test case will get the total flash size of the hardware using platform_hal_GetHardware(), get total used memory of the flash using platform_hal_GetHardware_MemUsed()
* and verify that used memory will be less than or equal to total flash size.
*
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetHardware_GetHardware_MemUsed(void)
{
    UT_LOG("Entering test_l2_platform_hal_GetHardware_GetHardware_MemUsed...");
    INT returnValue = 0;
    CHAR totalFlash[BUFFER_SIZE] = {'\0'};
    CHAR usedMem[BUFFER_SIZE] = {'\0'};
    int total = 0;
    int used = 0;

    UT_LOG("Invoking platform_hal_GetHardware with valid output parameter");
    returnValue = platform_hal_GetHardware(totalFlash);
    UT_LOG("Returned value is %d, Output buffer is %s ", returnValue, totalFlash);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    UT_LOG("Invoking platform_hal_GetHardware_MemUsed with valid output parameter");
    returnValue = platform_hal_GetHardware_MemUsed(usedMem);
    UT_LOG("Returned value is %d, Output buffer is %s ", returnValue, usedMem);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    total = atoi(totalFlash);
    used = atoi(usedMem);

    if(used <= total)
    {
        UT_LOG("Used memory is less than or equal to total Flash. Test case passed...");
        UT_PASS("Used memory is less than or equal to total Flash. Test case passed...");
    }
    else
    {
        UT_LOG("Used memory is greater than total Flash. Test case failed...");
        UT_FAIL("Used memory is greater than total Flash. Test case failed...")
    }
    UT_LOG("Exiting test_l2_platform_hal_GetHardware_GetHardware_MemUsed...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetHardware() and platform_hal_GetHardware_MemFree()
*
* This test case will get the total flash size of the hardware using platform_hal_GetHardware(), get total available memory of the flash using platform_hal_GetHardware_MemFree()
* and verify that available memory is less than or equal to total flash size.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetHardware_GetHardware_MemFree( void )
{
    UT_LOG("Entering test_l2_platform_hal_GetHardware_GetHardware_MemFree...\n");
    INT hw_status = 0;
    INT mem_free_status = 0;
    CHAR flash_memory[256] = {'\0'};
    CHAR mem_free[1024] = {'\0'};
    uint32_t flash_memory_result = 0;
    uint32_t mem_free_result = 0;

    UT_LOG("Invoking platform_hal_GetHardware with valid buffer. ");
    hw_status = platform_hal_GetHardware(flash_memory);
    UT_LOG("Returned status is : %d ", hw_status);
    UT_ASSERT_EQUAL(RETURN_OK,hw_status);

    UT_LOG("Invoking platform_hal_GetHardware_MemFree with valid buffer");
    mem_free_status = platform_hal_GetHardware_MemFree(mem_free);
    UT_LOG("Returned status is %d ", mem_free_status);
    UT_ASSERT_EQUAL(RETURN_OK,mem_free_status);

    flash_memory_result = atoi(flash_memory);
    mem_free_result = atoi(mem_free);
    UT_LOG("Converted flash memory to integer %d and free memory to integer %d.\n", flash_memory_result, mem_free_result);
    if(mem_free_result <= flash_memory_result)
    {
        UT_LOG("Memory Free is less than or equal to total  flash.\n");
        UT_PASS("Memory Free is less than or equal to total  flash.\n")
    }
    else
    {
        UT_LOG("Free Memory is more than total  flash. Test failed.\n");
        UT_FAIL("Free Memory is more than total  flash. Test failed.\n");
    }


    UT_LOG("Exiting test_l2_platform_hal_GetHardware_GetHardware_MemFree...\n");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetHardware(), platform_hal_GetHardware_MemUsed() and platform_hal_GetHardware_MemFree()
*
* This test case will get the total flash size of the hardware using platform_hal_GetHardware(), get total used memory of the flash using platform_hal_GetHardware_MemUsed(),
* get total available memory of the flash using platform_hal_GetHardware_MemFree() and verify that sum of used memory and available memory is equal to total flash size.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree(void)
{
  UT_LOG("Entering test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree...");
  CHAR totalFlash[256] = {'\0'};
  CHAR usedMemory[1024] = {'\0'};
  CHAR freeMemory[1024] = {'\0'};
  INT status = 0;
  long totalCalculatedMemory = 0;
  long expectedTotalFlash = 0;

  UT_LOG("Invoking platform_hal_GetHardware with valid output buffer.");
  status = platform_hal_GetHardware(totalFlash);
  UT_LOG("Return status : %d Returned total flash size: %s ",status,totalFlash);
  UT_ASSERT_EQUAL(status, RETURN_OK);


  UT_LOG("Invoking platform_hal_GetHardware_MemUsed with valid output buffer\n");
  status = platform_hal_GetHardware_MemUsed(usedMemory);
  UT_LOG("Return status : %d Returned used memory size: %s",status,usedMemory);
  UT_ASSERT_EQUAL(status, RETURN_OK);


  UT_LOG("Invoking platform_hal_GetHardware_MemFree with vaild output buffer");
  status = platform_hal_GetHardware_MemFree(freeMemory);
  UT_LOG("Return status : %d Returned free memory size: %s ",status,freeMemory);
  UT_ASSERT_EQUAL(status, RETURN_OK);

  totalCalculatedMemory = strtol(usedMemory, NULL, 10) + strtol(freeMemory, NULL, 10);
  expectedTotalFlash = strtol(totalFlash, NULL, 10);


  if (totalCalculatedMemory == expectedTotalFlash)
  {
    UT_LOG("Test case test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree passed");
    UT_PASS("Test case test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree passed");
  }
  else
  {
    UT_LOG("Test case test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree Failed");
    UT_FAIL("Test case test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree Failed");
  }

  UT_LOG("Exiting test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetTotalMemorySize() and platform_hal_GetUsedMemorySize().
*
* This test case will get the total memory size of the DRAM using platform_hal_GetTotalMemorySize(), get the total used memory of the DRAM using platform_hal_GetUsedMemorySize()
* and verify that the used memory will be less than or equal to total memory size of the DRAM.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 008@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize( void )
{
    UT_LOG("Entering test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize...");
    ULONG totalMemorySize = 0;
    ULONG usedMemorySize = 0;
    INT getTotalMemoryRetVal = 0;
    INT getUsedMemoryRetVal = 0;


    UT_LOG("Invoked platform_hal_GetTotalMemorySize with valid output parameter");
    getTotalMemoryRetVal = platform_hal_GetTotalMemorySize(&totalMemorySize);
    UT_LOG("Return status: %d, TotalMemorySize: %lu", getTotalMemoryRetVal, totalMemorySize);
    UT_ASSERT_EQUAL(getTotalMemoryRetVal, RETURN_OK);

    UT_LOG("Invoked platform_hal_GetUsedMemorySize with valid output parameter");
    getUsedMemoryRetVal = platform_hal_GetUsedMemorySize(&usedMemorySize);
    UT_LOG("Return status : %d, UsedMemorySize: %lu", getUsedMemoryRetVal, usedMemorySize);
    UT_ASSERT_EQUAL(getUsedMemoryRetVal, RETURN_OK);

    if (usedMemorySize <= totalMemorySize)
    {
        UT_LOG("Test pass. UsedMemory: %lu, TotalMemory: %lu", usedMemorySize, totalMemorySize);
        UT_PASS("Test pass. Used Memory is smaller than Total Memory.");
    }
    else
    {
        UT_LOG("Test Failed. UsedMemory: %lu, TotalMemory: %lu", usedMemorySize, totalMemorySize);
        UT_FAIL("Test Failed. Used Memory is larger than Total Memory.");
    }

    UT_LOG("Exiting test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetTotalMemorySize() and platform_hal_GetFreeMemorySize().
*
* This test case will get the total memory size of the DRAM using platform_hal_GetTotalMemorySize(), get the total available memory of the DRAM using platform_hal_GetFreeMemorySize()
* and verify that the free memory will be less than or equal to total memory size of the DRAM.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 009@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetTotalMemorySize_GetFreeMemorySize(void)
{
    UT_LOG("Entering test_l2_platform_hal_GetTotalMemorySize_GetFreeMemorySize...");
    ULONG totalMemory = 0;
    ULONG freeMemory = 0;
    INT retVal1 = RETURN_ERR;
    INT retVal2 = RETURN_ERR;

    UT_LOG("Invoking platform_hal_GetTotalMemorySize with valid output parameter");
    retVal1 = platform_hal_GetTotalMemorySize(&totalMemory);
    UT_LOG("Return status: %d. Total Memory: %lu.", retVal1, totalMemory);
    UT_ASSERT_EQUAL(retVal1, RETURN_OK);

    UT_LOG("Invoking platform_hal_GetFreeMemorySize with valid output parameter");
    retVal2 = platform_hal_GetFreeMemorySize(&freeMemory);
    UT_LOG("Return status: %d. Free Memory: %lu.", retVal2, freeMemory);
    UT_ASSERT_EQUAL(retVal2, RETURN_OK);

    if(freeMemory <= totalMemory)
    {
        UT_LOG("Test Pass. freeMemory: %lu, TotalMemory: %lu", freeMemory, totalMemory);
        UT_PASS("Test Pass. free Memory is smaller than Total Memory.");
    }
    else
    {
        UT_LOG("Test Fail. freeMemory: %lu, TotalMemory: %lu", freeMemory, totalMemory);
        UT_PASS("Test Fail. free Memory is larger than Total Memory.");
    }
    UT_LOG("Exiting test_l2_platform_hal_GetTotalMemorySize_GetFreeMemorySize...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetTotalMemorySize(), platform_hal_GetUsedMemorySize() and platform_hal_GetFreeMemorySize().
*
* This test case will get the total memory size of the DRAM using platform_hal_GetTotalMemorySize(), get the total used memory of the DRAM using platform_hal_GetUsedMemorySize(),
* get the total available memory of the DRAM using platform_hal_GetFreeMemorySize() and verify that the sum of used memory and free memory equal to total memory size of the DRAM.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 010@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize_GetFreeMemorySize(void)
{
    UT_LOG("Entering test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize_GetFreeMemorySize...");

    INT ret = 0;
    ULONG totalMemorySize = 0;
    ULONG usedMemorySize = 0;
    ULONG freeMemorySize = 0;

    UT_LOG("Invoking platform_hal_GetTotalMemorySize with valid output parameter");
    ret = platform_hal_GetTotalMemorySize(&totalMemorySize);
    UT_LOG("return status %d and output value %lu", ret, totalMemorySize);
    UT_ASSERT_EQUAL(ret, RETURN_OK);

    UT_LOG("Invoking platform_hal_GetUsedMemorySize with valid output parameter");
    ret = platform_hal_GetUsedMemorySize(&usedMemorySize);
    UT_LOG("return status %d and output value %lu", ret, usedMemorySize);
    UT_ASSERT_EQUAL(ret, RETURN_OK);

    UT_LOG("Invoking platform_hal_GetFreeMemorySize with valid output parameter");
    ret = platform_hal_GetFreeMemorySize(&freeMemorySize);
    UT_LOG("return status %d and output value %lu", ret, freeMemorySize);
    UT_ASSERT_EQUAL(ret, RETURN_OK);

    if(totalMemorySize == (usedMemorySize + freeMemorySize))
    {
        UT_LOG("totalMemorySize = usedMemorySize + freeMemorySize  validation success");
        UT_PASS("totalMemorySize = usedMemorySize + freeMemorySize  validation success");
    }
    else
    {
        UT_LOG("totalMemorySize = usedMemorySize + freeMemorySize  validation Failed");
        UT_FAIL("totalMemorySize = usedMemorySize + freeMemorySize  validation Failed");
    }
    UT_LOG("Exiting test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize_GetFreeMemorySize...");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetFactoryResetCount() and platform_hal_ClearResetCount
*
* This test case will get the total number factory reset done on the device using platform_hal_GetFactoryResetCount(), reset the factory reset count on the device using
* platform_hal_ClearResetCount() and verify that the count is reset using platform_hal_GetFactoryResetCount()
*
* **Test Group ID:** 02@n
* **Test Case ID:** 011@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_GetFactoryResetCount_ClearResetCount_GetFactoryResetCount(void) {
    UT_LOG("Entering test_l2_platform_hal_GetFactoryResetCount_ClearResetCount_GetFactoryResetCount...");
    ULONG pulSizeBefore = 0;
    ULONG pulSizeAfter = 0;
    BOOLEAN bFlag = TRUE;
    INT resultCode;

    UT_LOG("Invoking platform_hal_GetFactoryResetCount with  valid output parameter");
    resultCode = platform_hal_GetFactoryResetCount(&pulSizeBefore);
    UT_LOG("return status %d and Factory Reset Count : %lu",resultCode,pulSizeBefore);
    UT_ASSERT_EQUAL(resultCode, RETURN_OK);

    UT_LOG("Invoking platform_hal_ClearResetCount with bFlag: TRUE");
    resultCode = platform_hal_ClearResetCount(bFlag);
    UT_LOG("Return status : %d",resultCode);
    UT_ASSERT_EQUAL(resultCode, RETURN_OK);

    UT_LOG("Invoking platform_hal_GetFactoryResetCount again with  valid output parameter");
    resultCode = platform_hal_GetFactoryResetCount(&pulSizeAfter);
    UT_LOG("return status %d and Factory Reset Count : %lu",resultCode,pulSizeAfter);

    UT_ASSERT_EQUAL(pulSizeAfter, 0);
    UT_ASSERT_EQUAL(resultCode, RETURN_OK);
    UT_LOG("Exiting test_l2_platform_hal_GetFactoryResetCount_ClearResetCount_GetFactoryResetCount...");
}
/**
* @brief Test case to verify the functionality of platform_hal_getFactoryCmVariant() and platform_hal_setFactoryCmVariant().
*
* This test case will get current FactoryCmVariant value of the the device using platform_hal_getFactoryCmVariant(), set FactoryCmVariant value using platform_hal_setFactoryCmVariant()
* and verify using platform_hal_getFactoryCmVariant().
*
* **Test Group ID:** 02@n
* **Test Case ID:** 012@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_getFactoryCmVariant_setFactoryCmVariant_getFactoryCmVariant( void ) {
    UT_LOG("Entering test_l2_platform_hal_getFactoryCmVariant_setFactoryCmVariant_getFactoryCmVariant...\n");
    CHAR preSetValue[512] = {'\0'};
    CHAR postSetValue[512] = {'\0'};
    CHAR knownValue[512] = "pc20";
    int preGetValueStatus = 0;
    int setValueStatus = 0;
    int postGetValueStatus = 0;

    UT_LOG("Invoking platform_hal_getFactoryCmVariant with valid output parameter");
    preGetValueStatus = platform_hal_getFactoryCmVariant(preSetValue);
    UT_LOG("return status: %d Factory Cm Variant : %S ",preGetValueStatus,preSetValue);
    UT_ASSERT_EQUAL(preGetValueStatus, RETURN_OK);

    if(!strcmp(preSetValue,"pc20"))
    {
        strcpy(knownValue,"pc20genband");
    }

    UT_LOG("Invoking platform_hal_setFactoryCmVariant() with input : %s ",knownValue);
    setValueStatus = platform_hal_setFactoryCmVariant(knownValue);
    UT_LOG("return status: %d ",setValueStatus);
    UT_ASSERT_EQUAL(setValueStatus, RETURN_OK);

    UT_LOG("Invoking platform_hal_getFactoryCmVariant with valid output parameter");
    postGetValueStatus = platform_hal_getFactoryCmVariant(postSetValue);
    UT_LOG("return status: %d Factory Cm Variant : %S ",postGetValueStatus,postSetValue);
    UT_ASSERT_EQUAL(postGetValueStatus, RETURN_OK);

    if(!strcmp(knownValue,postSetValue))
    {
        UT_LOG("platform_hal_setFactoryCmVariant validation success");
        UT_PASS("platform_hal_setFactoryCmVariant validation success");
    }
    else
    {
        UT_LOG("platform_hal_setFactoryCmVariant validation failed");
        UT_FAIL("platform_hal_setFactoryCmVariant validation failed");
    }

    UT_LOG("Exiting test_l2_platform_hal_getFactoryCmVariant_setFactoryCmVariant_getFactoryCmVariant...\n");
}
/**
* @brief Test case to verify the functionality of platform_hal_setLed() and platform_hal_getLed().
*
* This test sets the LED status to a valid value using platform_hal_setLed() and verify using platform_hal_getLed().
*
* **Test Group ID:** 02@n
* **Test Case ID:** 013@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_setLed_getLed(void)
{
    UT_LOG("Entering test_l2_platform_hal_setLed_getLed...\n");
    PLEDMGMT_PARAMS getLEDStatus = NULL;
    LEDMGMT_PARAMS setLEDStatus;
    setLEDStatus.LedColor = LED_BLUE;
    setLEDStatus.State = 1;
    setLEDStatus.Interval = 5;
    INT setResult = 0;
    INT getResult = 0;

    UT_LOG("Invoking platform_hal_setLed with LedColor=LED_BLUE, State=0, Interval=0.\n");
    setResult = platform_hal_setLed(&setLEDStatus);
    UT_LOG("Return status : %d ",setResult);
    UT_ASSERT_EQUAL(setResult, RETURN_OK);

    getLEDStatus = (PLEDMGMT_PARAMS) malloc(sizeof(LEDMGMT_PARAMS));
    if(getLEDStatus != NULL)
    {
        UT_LOG("Invoking platform_hal_getLed with valid output parameter");
        getResult = platform_hal_getLed(getLEDStatus);
        UT_LOG("Return status : %d ",getResult);

        UT_ASSERT_EQUAL(getResult, RETURN_OK);

        UT_ASSERT_EQUAL(getLEDStatus->LedColor, setLEDStatus.LedColor);
        UT_ASSERT_EQUAL(getLEDStatus->State, setLEDStatus.State);
        UT_ASSERT_EQUAL(getLEDStatus->Interval, setLEDStatus.Interval);
    }
    else
    {
        UT_LOG("malloc failed ");
        UT_FAIL("malloc failed ");
    }
    UT_LOG("Exiting test_l2_platform_hal_setLed_getLed...\n");
}
/**
* @brief Test case to verify the functionality of platform_hal_GetMACsecEnable() and platform_hal_SetMACsecEnable()
*
* This test case will get current MACsec enable status using platform_hal_GetMACsecEnable(), set MACsec enable status using platform_hal_SetMACsecEnable()
* and verify using platform_hal_GetMACsecEnable().
*
* **Test Group ID:** 02@n
* **Test Case ID:** 014@n
* **Priority:** Low@n
*
* **Test Procedure:**
* Refer to UT specification documentation [L2_TestSpecification.md](../../docs/pages/)
*/
void test_l2_platform_hal_MACsecEnableFunctions( void )
{
    UT_LOG("Entering test_l2_platform_hal_MACsecEnableFunctions...");
    INT ethPort = 0;
    INT ret = 0;
    BOOLEAN Flag = false;
    BOOLEAN NewFlag = false ;

    for(ethPort = 0; ethPort < MaxEthPort; ethPort++)
    {
        UT_LOG("Invoking platform_hal_GetMACsecEnable with valid ethPort. ethPort = %d ",ethPort);
        ret = platform_hal_GetMACsecEnable(ethPort, &Flag);
        UT_LOG("Return Status = %d",ret);
        UT_ASSERT_EQUAL(ret, RETURN_OK);

        Flag = !Flag;

        UT_LOG("Invoking platform_hal_SetMACsecEnable to toggle MACsec status. ethPort = %d, Flag = %d", ethPort,Flag);
        ret = platform_hal_SetMACsecEnable(ethPort, Flag);
        UT_LOG("Return Status = %d",ret);
        UT_ASSERT_EQUAL(ret, RETURN_OK);

        UT_LOG("Invoking platform_hal_GetMACsecEnable to validate new MACsec status. ethPort = %d",ethPort);
        ret = platform_hal_GetMACsecEnable(ethPort, &NewFlag);
        UT_LOG("Return Status = %d",ret);
        UT_ASSERT_EQUAL(ret, RETURN_OK);

        if(NewFlag == Flag)
        {
            UT_LOG("platform_hal_SetMACsecEnable validation success");
            UT_PASS("platform_hal_SetMACsecEnable validation success");
        }
        else
        {
            UT_LOG("platform_hal_SetMACsecEnable validation Failed");
            UT_FAIL("platform_hal_SetMACsecEnable validation Failed");
        }

    }
    UT_LOG("Exiting test_l2_platform_hal_MACsecEnableFunctions...");
}
static UT_test_suite_t * pSuite = NULL;
/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_platform_hal_l2_register(void)
{

    pSuite = UT_add_suite("[L2 platform_hal]", init_platform_hal_init, NULL);
    if (pSuite == NULL) {
        return -1;
    }

    UT_add_test( pSuite, "l2_platform_hal_GetTelnetEnable_SetTelnetEnable", test_l2_platform_hal_GetTelnetEnable_SetTelnetEnable);
    UT_add_test( pSuite, "l2_platform_hal_GetSSHEnable_SetSSHEnable", test_l2_platform_hal_GetSSHEnable_SetSSHEnable);
    UT_add_test( pSuite, "l2_platform_hal_GetSNMPEnable_SetSNMPEnable_GetSNMPEnable", test_l2_platform_hal_GetSNMPEnable_SetSNMPEnable_GetSNMPEnable);
    UT_add_test( pSuite, "l2_platform_hal_GetWebUITimeout_SetWebUITimeout_GetWebUITimeout", test_l2_platform_hal_GetWebUITimeout_SetWebUITimeout_GetWebUITimeout);
    UT_add_test( pSuite, "l2_platform_hal_GetHardware_GetHardware_MemUsed", test_l2_platform_hal_GetHardware_GetHardware_MemUsed);
    UT_add_test( pSuite, "l2_platform_hal_GetHardware_GetHardware_MemFree", test_l2_platform_hal_GetHardware_GetHardware_MemFree);
    UT_add_test( pSuite, "l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree", test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree);
    UT_add_test( pSuite, "l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize", test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize);
    UT_add_test( pSuite, "l2_platform_hal_GetTotalMemorySize_GetFreeMemorySize", test_l2_platform_hal_GetTotalMemorySize_GetFreeMemorySize);
    UT_add_test( pSuite, "l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize_GetFreeMemorySize", test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize_GetFreeMemorySize);
    UT_add_test( pSuite, "l2_platform_hal_GetFactoryResetCount_ClearResetCount_GetFactoryResetCount", test_l2_platform_hal_GetFactoryResetCount_ClearResetCount_GetFactoryResetCount);
    UT_add_test( pSuite, "l2_platform_hal_getFactoryCmVariant_setFactoryCmVariant_getFactoryCmVariant", test_l2_platform_hal_getFactoryCmVariant_setFactoryCmVariant_getFactoryCmVariant);
    UT_add_test( pSuite, "l2_platform_hal_setLed_getLed", test_l2_platform_hal_setLed_getLed);
    UT_add_test( pSuite, "l2_platform_hal_MACsecEnableFunctions", test_l2_platform_hal_MACsecEnableFunctions);
    return 0;
}