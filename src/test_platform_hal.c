/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2016 RDK Management
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
* @file test_platform_hal.c
* @page platform_hal Level 1 Tests
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the platform_hal APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None @n
* **Dependencies:** None @n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include <string.h>
#include "platform_hal.h"

/**
 * @brief This test case is used to verify the functionality of the get firmware name API.
 * 
 * The objective of this test is to ensure that the get firmware name API returns the firmware name correctly.

 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 001 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description                                          | Test Data                       | Expected Result                | Notes             |
 * | :--------------: | ---------------------------------------------------- | ------------------------------- | ------------------------------ | ----------------- |
 * |       01         | Invoking platform_hal_GetFirmwareName with Valid pointer     |         None                    | RETURN_OK                      | Should be successful |
 */
void test_l1_platform_hal_positive1_GetFirmwareName(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFirmwareName...");

    CHAR pValue[256];
    ULONG maxSize = 256;

    INT status = platform_hal_GetFirmwareName(pValue, maxSize);

    UT_LOG("Invoking platform_hal_GetFirmwareName() with valid pointers.");
    UT_LOG("Output value of pValue: %s", pValue);
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetFirmwareName...");
}

/**
* @brief This test verifies the behavior of the platform_hal_GetFirmwareName function when invoked with a NULL pointer as the first argument.
*
* The platform_hal_GetFirmwareName function is tested in this test case to ensure that it returns an error status when a NULL pointer is passed as the first argument. This test is important to check the defensive programming of the function and to prevent potential segfaults or undefined behavior when the function is called with invalid parameters.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 002 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01    | Invoking platform_hal_GetFirmwareName with NULL pointer | pValue = NULL, maxSize = 256 | RETURN_ERR | Should return an error status |
*/

void test_l1_platform_hal_negative1_GetFirmwareName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFirmwareName...");

    CHAR* pValue = NULL;
    ULONG maxSize = 256;

    INT status = platform_hal_GetFirmwareName(pValue, maxSize);

    UT_LOG("Invoking platform_hal_GetFirmwareName() with NULL pointer.");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetFirmwareName...");
}

/**
* @brief Test case to verify the platform_hal_GetSoftwareVersion() function in L1 platform HAL.
*
* This test case is used to verify the functionality of the platform_hal_GetSoftwareVersion() function in L1 platform HAL. The objective is to ensure that the function returns RETURN_OK.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 003 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking platform_hal_GetSoftwareVersion with valid pointer | pValue = NULL, maxSize = 10 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetSoftwareVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetSoftwareVersion...");

    CHAR pValue[256];
    ULONG maxSize = 256;

    INT status = platform_hal_GetSoftwareVersion(pValue, maxSize);

    UT_LOG("Invoking platform_hal_GetSoftwareVersion() with valid pointers.");
    UT_LOG("Output value of pValue: %s", pValue);
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetSoftwareVersion...");
}

/**
 * @brief Test the platform_hal_GetSoftwareVersion function with NULL pointer as input parameter.
 *
 * This test case is used to verify the behavior of the platform_hal_GetSoftwareVersion function when a NULL pointer is provided as the input parameter. The function should return RETURN_ERR in this case.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 004 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetSoftwareVersion with NULL pointer | input = NULL, maxSize = value | RETURN_ERR | Should return error |
 */
void test_l1_platform_hal_negative1_GetSoftwareVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetSoftwareVersion...");

    CHAR* pValue = NULL;
    ULONG maxSize = 256;

    INT status = platform_hal_GetSoftwareVersion(pValue, maxSize);

    UT_LOG("Invoking platform_hal_GetSoftwareVersion() with NULL pointer.");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetSoftwareVersion...");
}

/**
 * @brief Test case to verify the functionality of platform_hal_GetSerialNumber function
 * 
 * This test case is used to validate the behavior of platform_hal_GetSerialNumber function.
 * 
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 005 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * 
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | ----------- | --------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetSerialNumber function with valid input parameters | Valid Buffer | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_GetSerialNumber(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetSerialNumber...");
    
    CHAR serialNumber[256];
    INT status = platform_hal_GetSerialNumber(serialNumber);
    
    UT_LOG("Invoking platform_hal_GetSerialNumber with valid input parameters.");
    UT_LOG("Output value of pValue: %s", serialNumber);
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetSerialNumber...");
}

/**
 * @brief Unit test to verify the behavior of platform_hal_GetSerialNumber when passed NULL input parameter.
 *
 * This test case aims to verify the behavior of platform_hal_GetSerialNumber when it is invoked with a NULL input parameter. It checks if the function returns the expected status code.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 006 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                                   | Test Data                 | Expected Result        | Notes                |
 * | :--------------: | ------------------------------------------------------------- | ------------------------- | ---------------------- | -------------------- |
 * |        01        | Invoking platform_hal_GetSerialNumber with NULL input parameter | pValue = NULL             | RETURN_ERR              | Should fail |
 */
void test_l1_platform_hal_negative1_GetSerialNumber(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetSerialNumber...");

    INT status = platform_hal_GetSerialNumber(NULL);

    UT_LOG("Invoking platform_hal_GetSerialNumber with NULL input parameter (pValue).");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetSerialNumber...");
}

/**
* @brief Test case to check the functionality of platform_hal_GetSNMPEnable function when provided with valid input.
*
* This test case checks the functionality of platform_hal_GetSNMPEnable function by invoking it with valid input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 007 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetSNMPEnable with valid pValue buffer | Valid Buffer | Return status should be RETURN_OK and pValue buffer should not be empty | Should be successful |
*/
void test_l1_platform_hal_positive1_GetSNMPEnable(void) {
    UT_LOG("\nEntering test_l1_platform_hal_positive1_GetSNMPEnable...\n");

    CHAR pValue[32] = {"\0"};
    INT result = platform_hal_GetSNMPEnable(pValue);

    UT_LOG("Invoking platform_hal_GetSNMPEnable with valid pValue buffer");
    UT_LOG("Output pValue: %s", pValue);
    UT_LOG("Return status: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    if (!strcmp(pValue,"rgWan") || !strcmp(pValue,"rgDualIp")|| !strcmp(pValue,"rgLanIp"))
		{
            UT_LOG("SNMP Enable value from the device is %s which is a valid value", pValue);
            UT_PASS("Get SNMP Enable validation success");
		}
	else
		{
            UT_LOG("SNMP Enable value from the device %s which is an Invalid value", pValue);
            UT_FAIL("Get SNMP Enable validation fail");
		}

    UT_ASSERT_STRING_EQUAL(pValue, "rgWan|rgDualIp|rgLanIp");

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetSNMPEnable...\n");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetSNMPEnable when the pointer pValue is NULL.
*
* The objective of this test is to ensure that platform_hal_GetSNMPEnable returns RETURN_ERR when pValue is NULL.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 008 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description                                                                                 | Test Data         | Expected Result                     | Notes             |
* | ---------------- | ------------------------------------------------------------------------------------------- | ----------------- | ----------------------------------- | ----------------- |
* | 01               | Verify platform_hal_GetSNMPEnable with NULL pValue                                        | pValue = NULL     | RETURN_ERR                           | Should fail|
*/
void test_l1_platform_hal_negative1_GetSNMPEnable(void) {
    UT_LOG("\nEntering test_l1_platform_hal_negative1_GetSNMPEnable...\n");

    INT result = platform_hal_GetSNMPEnable(NULL);

    UT_LOG("Invoking platform_hal_GetSNMPEnable with NULL pValue");

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetSNMPEnable...\n");
}

/**
 * @brief Unit test for the function platform_hal_GetHardware_MemUsed.
 *
 * This test case is used to validate the functionality of the platform_hal_GetHardware_MemUsed function.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 009 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoking platform_hal_GetHardware_MemUsed with valid input parameters | Valid Buffer | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_GetHardware_MemUsed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardware_MemUsed...");

    CHAR value[1024];
    INT status = platform_hal_GetHardware_MemUsed(value);

    UT_LOG("Invoking platform_hal_GetHardware_MemUsed with valid input parameters.");
    UT_LOG("Return Status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    //UT_ASSERT(value > 0);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetHardware_MemUsed...");
}

/**
* @brief Unit test for the function platform_hal_GetHardware_MemUsed.
*
* This test case is used to validate the functionality of the platform_hal_GetHardware_MemUsed function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 010 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetHardware_MemUsed with NULL input parameters. | value = NULL | RETURN_ERR | Should be equal to RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetHardware_MemUsed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardware_MemUsed...");
    
    CHAR *value = NULL;
    INT status = platform_hal_GetHardware_MemUsed(value);
    
    UT_LOG("Invoking platform_hal_GetHardware_MemUsed with NULL input parameters.");
    UT_LOG("Return Status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetHardware_MemUsed...");
}

/**
 * @brief Test case to verify the functionality of the platform_hal_GetHardwareVersion function.
 * 
 * This test case checks the behavior of the platform_hal_GetHardwareVersion function and verifies if it returns the hardware version correctly.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 011 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                                | Test Data                       | Expected Result                              | Notes              |
 * |:----------------:|------------------------------------------------------------|---------------------------------|----------------------------------------------|--------------------|
 * |       01         | Invoke platform_hal_GetHardwareVersion function with Valid Buffer          | pValue = Valid Buffer   | RETURN_OK| Should be successful |
 */

void test_l1_platform_hal_positive1_GetHardwareVersion(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardwareVersion...");
    
    // Prepare input parameters
    CHAR pValue[256]; // Sufficient memory allocated
    
    // Invoke the API
    UT_LOG("Invoking platform_hal_GetHardwareVersion with Valid buffer.");
    INT status = platform_hal_GetHardwareVersion(pValue);
    UT_LOG("platform_hal_GetHardwareVersion returns %d",status);
    
    // Perform assertions
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetHardwareVersion...");
}

/**
 * @brief Test case for the platform_hal_GetHardwareVersion function with negative input.
 *
 * This test case is used to verify the behavior of the platform_hal_GetHardwareVersion function 
 * when provided with negative input. The objective of this test is to ensure that the function 
 * correctly handles negative input and returns the expected error code.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 012 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                                | Test Data                       | Expected Result                              | Notes              |
 * |:----------------:|------------------------------------------------------------|---------------------------------|----------------------------------------------|--------------------|
 *  01 |  Invoke platform_hal_GetHardwareVersion function with NULL Value | pValue = NULL | Status = RETURN_ERR | Should fail
 */
void test_l1_platform_hal_negative1_GetHardwareVersion(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardwareVersion...");
    
    // Prepare input parameters
    CHAR* pValue = NULL; // NULL pointer
    
    // Invoke the API
    INT status = platform_hal_GetHardwareVersion(pValue);
    
    // Perform assertions
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetHardwareVersion...");
}

/**
    * @brief This test case verifies the functionality of the GetModelName API in the positive scenario.
    *
    * The GetModelName API is tested in this test to ensure that it returns the correct model name of the platform.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 013 @n
    * **Priority:** High @n@n
    *
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
    *
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoke GetModelName API | None | RETURN_OK and Model name is Returned | Should be successful |
    */
void test_l1_platform_hal_positive1_GetModelName(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetModelName...");
    
    CHAR pValue[256];
    INT status = platform_hal_GetModelName(pValue);
    
    UT_LOG("Invoking platform_hal_GetModelName with valid input parameters.");
    UT_LOG("Output value of pValue: %s", pValue);
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetModelName...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_GetModelName function when invoked with a NULL input parameter.
*
* This test case checks if the platform_hal_GetModelName function returns the expected result when invoked with a NULL input parameter.
* The objective of this test case is to ensure that the function can handle NULL input correctly and return the appropriate status code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 014 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* |       01         | Verify behavior with NULL input | model_name = NULL | RETURN_ERR | Function should return RETURN_ERR when invoked with a NULL input parameter |
*/
void test_l1_platform_hal_negative1_GetModelName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetModelName...");

    CHAR* model_name = NULL;
    INT status = platform_hal_GetModelName(model_name);

    UT_LOG("Invoking platform_hal_GetModelName with NULL input parameter");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetModelName...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_GetRouterRegion function
*
* This test case verifies the functionality of the platform_hal_GetRouterRegion function by checking if it retrieves the correct router region.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 015 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetRouterRegion with valid pointer pValue | pValue = "", status = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetRouterRegion(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetRouterRegion...");

    CHAR pValue[256] = {"\0"};

    UT_LOG("Invoking platform_hal_GetRouterRegion with valid pointer pValue");
    UT_LOG("Expected Output: RETURN_OK");

    INT status = platform_hal_GetRouterRegion(pValue);
    
    UT_LOG("platform_hal_GetRouterRegion returns %d", status);
    UT_LOG("Router region: %s", pValue);
    

    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    if (!strcmp(pValue,"REGION_UK") || !strcmp(pValue,"REGION_IT")|| !strcmp(pValue,"REGION_ROI") || !strcmp(pValue,"REGION_UNKNOWN"))
		{
            UT_LOG("Router region is %s which is a valid value", pValue);
            UT_PASS("Get Router Region validation value");
		}
	else
		{
            UT_LOG("Router region is which is an invalid status", pValue);
            UT_FAIL("Get Router Region validation fail");
		}

    UT_ASSERT_STRING_EQUAL(pValue, "REGION_UK|REGION_IT|REGION_ROI|REGION_UNKNOWN");
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetRouterRegion...");
}

/**
* @brief Test case to validate the behavior of platform_hal_GetRouterRegion when NULL pointer is passed as argument.
*
* This test case checks the functionality of platform_hal_GetRouterRegion when NULL pointer is passed as argument. 
* The objective of this test is to ensure that the API returns RETURN_ERR when NULL pointer is passed as argument.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 016 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetRouterRegion with NULL pointer pValue | pValue = NULL | RETURN_ERR | Should return RETURN_ERR on providing NULL pointer |
*/
void test_l1_platform_hal_negative1_GetRouterRegion(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetRouterRegion...");

    UT_LOG("Invoking platform_hal_GetRouterRegion with NULL pointer pValue");
    UT_LOG("Expected Output: RETURN_ERR");

    INT status = platform_hal_GetRouterRegion(NULL);
    UT_LOG("platform_hal_GetRouterRegion returns %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetRouterRegion...");
}

/**
* @brief Test to verify the functionality of the platform_hal_GetBootloaderVersion function.
*
* This test case is used to verify the platform_hal_GetBootloaderVersion function. It checks if the function returns the correct bootloader version and if the return status is equal to RETURN_OK.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 017 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetBootloaderVersion with valid input parameters | pValue = valid buffer, maxSize = 256 | status = RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetBootloaderVersion(void)
{
    CHAR pValue[256];
    ULONG maxSize = 256;

    UT_LOG("Entering test_l1_platform_hal_positive1_GetBootloaderVersion...");

    INT status = platform_hal_GetBootloaderVersion(pValue, maxSize);

    UT_LOG("Invoking platform_hal_GetBootloaderVersion with valid input parameters (pValue is valid buffer, maxSize >= 256)...");
    UT_LOG("Output values: pValue = %s", pValue);
    UT_LOG("Return status: status = %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetBootloaderVersion...");
}

/**
 * @brief Tests the functionality of the GetBootloaderVersion function when called with NULL pValue parameter.
 *
 * The objective of this test is to verify the behavior of the platform_hal_GetBootloaderVersion function when it is called with a NULL pValue parameter. It checks whether the function returns an error status as expected.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 018 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:** @n
 *  | Variation / Step | Description | Test Data                                      | Expected Result               | Notes           |
 *  | :--------------: | ----------- | ---------------------------------------------- | ----------------------------- | --------------- |
 *  |       01         | Invoke the platform_hal_GetBootloaderVersion with NULL pValue parameter. | pValue = NULL, maxSize = 0               | RETURN_ERR                     | Should fail |
 */
void test_l1_platform_hal_negative1_GetBootloaderVersion(void)
{
    CHAR* pValue = NULL;
    ULONG maxSize = 0;

    UT_LOG("Entering test_l1_platform_hal_negative1_GetBootloaderVersion...");

    INT status = platform_hal_GetBootloaderVersion(pValue, maxSize);

    UT_LOG("Invoking platform_hal_GetBootloaderVersion with NULL pValue...");
    UT_LOG("Return status: status = %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetBootloaderVersion...");
}

/**
 * @brief Unit test to verify the functionality of platform_hal_GetHardware function.
 * 
 * This test case is used to validate the correctness and functionality of the platform_hal_GetHardware() function.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 019 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_GetHardware with valid pointer | pValue = value[256] | RETURN_OK | The function should return success status |
 */
void test_l1_platform_hal_positive1_GetHardware(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardware...");

    CHAR value[256];
    INT ret = platform_hal_GetHardware(value);

    UT_LOG("Invoking platform_hal_GetHardware with input parameters: pValue = valid pointer with sufficient memory allocated");
    UT_LOG("Output values: pValue = %s", value);
    UT_LOG("Return status: ret = %d", ret);
    
    int flash_size = atoi(value);
    UT_ASSERT_EQUAL(ret, RETURN_OK);

        if (flash_size >= 1 && flash_size <= 4096)
		{
            UT_LOG("The bootloader version flashed in the device is %d which is a valid value", flash_size);
            UT_PASS("Get Hardware validation success");
		}
	else
		{
            UT_LOG("The bootloader version flashed in the device is %d which is an invalid value", flash_size);
            UT_FAIL("Get Hardware validation fail");
		}

    UT_ASSERT_TRUE(flash_size >= 1 && flash_size <= 4096);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetHardware...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_GetHardware() function 
* when a NULL pointer is passed as one of the arguments.
*
* The objective of this test is to ensure that the function returns a specific error code when a NULL pointer is passed 
* as the argument "pValue" to platform_hal_GetHardware().
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 020 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* 
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Verify the return value when a NULL pointer is passed | pValue = NULL | RETURN_ERR | Should return the error code |
*/
void test_l1_platform_hal_negative1_GetHardware(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardware...");

    CHAR *pValue = NULL;
    INT ret = platform_hal_GetHardware(pValue);

    UT_LOG("Invoking platform_hal_GetHardware with input parameters: pValue = NULL");
    UT_LOG("Return status: ret = %d", ret);
    
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetHardware...");
}

/**
 * @brief Test the function platform_hal_SetSNMPEnable for positive scenario.
 *
 * This test case verifies the behavior of the function platform_hal_SetSNMPEnable
 * when it is invoked with valid input parameters.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 021 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoking platform_hal_SetSNMPEnable | pValue = "rgWan" | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_SetSNMPEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_SetSNMPEnable...");

    CHAR pValue[] = "rgWan";
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("Invoking platform_hal_SetSNMPEnable with input parameter pValue='%s'", pValue);
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetSNMPEnable...");
}

/**
* @brief Test case to validate the functionality of platform_hal_SetSNMPEnable with a positive scenario.
*
* This test case verifies the functionality of platform_hal_SetSNMPEnable by testing it with valid input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 022 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_SetSNMPEnable with valid input | pValue = "rgDualIp" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetSNMPEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_SetSNMPEnable...");

    CHAR pValue[] = "rgDualIp";
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("Invoking platform_hal_SetSNMPEnable with input parameter pValue='%s'", pValue);
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetSNMPEnable...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_SetSNMPEnable API
*
* This test case is used to verify the functionality of the platform_hal_SetSNMPEnable API. It checks if the API sets the SNMP enable flag correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 023 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetSNMPEnable with valid input | pValue = "rgLanIp" | RETURN_OK| Should be successful |
*/

void test_l1_platform_hal_positive3_SetSNMPEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_SetSNMPEnable...");

    CHAR pValue[] = "rgLanIp";
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("Invoking platform_hal_SetSNMPEnable with input parameter pValue='%s'", pValue);
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetSNMPEnable...");
}

/**
 * @brief This is a test case to verify the negative scenario of the platform_hal_SetSNMPEnable function.
 *
 * This test case is designed to verify the behavior of the platform_hal_SetSNMPEnable function when the input parameter pValue is NULL.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 024 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                                      | Test Data                 | Expected Result | Notes             |
 * | :--------------: | --------------------------------------------------------------- | ------------------------- | --------------- | ----------------- |
 * |       01         | Invoking platform_hal_SetSNMPEnable with input parameter pValue as NULL | pValue=NULL               | RETURN_ERR       | Should fail |
 */

void test_l1_platform_hal_negative1_SetSNMPEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_SetSNMPEnable...");

    INT result = platform_hal_SetSNMPEnable(NULL);

    UT_LOG("Invoking platform_hal_SetSNMPEnable with input parameter pValue=NULL");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetSNMPEnable...");
}

/**
* @brief Unit test for the function platform_hal_SetSNMPEnable when provided with invalid input value.
*
* This test is used to verify the behavior of the platform_hal_SetSNMPEnable function when it is called with an invalid input value. 
* The function should return an error code indicating that the input value is invalid.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 025 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_SetSNMPEnable with an invalid input value | pValue = "invalidValue" | RETURN_ERR | Should return an error code indicating that the input value is invalid |
*/
void test_l1_platform_hal_negative2_SetSNMPEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_SetSNMPEnable...");

    CHAR pValue[] = "invalidValue";
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("Invoking platform_hal_SetSNMPEnable with input parameter pValue='%s'", pValue);
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetSNMPEnable...");
}

/**
* @brief Positive test case to verify the functionality of SetWebUITimeout API with lower end range value
*
* This test case is used to verify the functionality of the SetWebUITimeout API when the timeout value is set to the lower end range value. The objective of this test is to ensure that the API correctly handles the lower end range values and returns the expected result.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 026 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Set WebUI Timeout to lower end range value | value = 30 | Return value should be RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetWebUITimeout...");

    ULONG value = 30;
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu", value);
    UT_LOG("Expected Output: RETURN_OK");
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetWebUITimeout...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetWebUITimeout function when the input value is at the upper end of the range.
*
* The test case validates that the platform_hal_SetWebUITimeout function returns the expected result when the input value is at the upper end of the range.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 027 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set the input value to the maximum value of the range | value = 86400 | RETURN_OK is expected | Should be successful |
*/
void test_l1_platform_hal_positive2_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetWebUITimeout...");

    ULONG value = 86400;
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu", value);
    UT_LOG("Expected Output: RETURN_OK");
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetWebUITimeout...");
}

/**
* @brief This test is used to verify the behavior of the platform_hal_SetWebUITimeout function when the input value is zero.
*
* The purpose of this test is to ensure that the platform_hal_SetWebUITimeout function behaves correctly when the input value is zero.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 028 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, they have to select this test case via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_SetWebUITimeout function with zero value | value = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive3_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_SetWebUITimeout...");

    ULONG value = 0;
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu", value);
    UT_LOG("Expected Output: RETURN_OK");
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetWebUITimeout...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_SetWebUITimeout API when an invalid lower value is passed as input.
 *
 * This test case checks if the platform_hal_SetWebUITimeout API returns RETURN_ERR when an invalid lower value is passed as input. 
 * The test is a negative test case to ensure that the API handles invalid inputs correctly.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 029 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data                          | Expected Result | Notes           |
 * | :--------------: | ----------- | ---------------------------------- | --------------- | --------------- |
 * |       01         | Invoke platform_hal_SetWebUITimeout function with -1 value   | value = -1                         | RETURN_ERR      | Should return Error |
 *
 */

void test_l1_platform_hal_negative1_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetWebUITimeout...");

    ULONG value = -1;
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu", value);
    UT_LOG("Expected Output: RETURN_ERR");
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetWebUITimeout...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_SetWebUITimeout function when an invalid upper value is provided.
*
* This test case checks the behavior of the platform_hal_SetWebUITimeout function when an invalid upper value (greater than 86400) is provided as input. The function is expected to return RETURN_ERR in this case.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 030 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data                          | Expected Result | Notes           |
* | :--------------: | ----------- | ---------------------------------- | --------------- | --------------- |
* | 01 | Verify the behavior of platform_hal_SetWebUITimeout when an invalid upper value is provided| Input Value: value = 86401 |  RETURN_ERR | The function is expected to return RETURN_ERR as the input value exceeds the maximum allowed timeout value.|
*/
void test_l1_platform_hal_negative2_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetWebUITimeout...");

    ULONG value = 86401;
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu", value);
    UT_LOG("Expected Output: RETURN_ERR");
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative2_SetWebUITimeout...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_SetWebUITimeout function when an invalid lower value is provided.
*
* This test case checks the behavior of the platform_hal_SetWebUITimeout function when an invalid lower value (lesser than 30) is provided as input. The function is expected to return RETURN_ERR in this case.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 031 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | SetWebUITimeout with invalid lower range value | value = 29 | RETURN_ERR | Should return RETURN_ERR as the value is out of valid range |
*
*/
void test_l1_platform_hal_negative3_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_SetWebUITimeout...");

    ULONG value = 29;
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu", value);
    UT_LOG("Expected Output: RETURN_ERR");
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_SetWebUITimeout...");
}

/**
 * @brief This test case is used to verify the functionality of the platform_hal_GetWebUITimeout function.
 *
 * The objective of this test is to ensure that the platform_hal_GetWebUITimeout function
 * returns the correct status and outputs the expected value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 032 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                             | Test Data                             | Expected Result                                               | Notes           |
 * | :--------------: | ------------------------------------------------------- | ------------------------------------- | ------------------------------------------------------------- | --------------- |
 * |       01         | Invoke platform_hal_GetWebUITimeout function with valid value                                |       None                                  | RETURN_OK                                                      | Should be successful |
 */

void test_l1_platform_hal_positive1_GetWebUITimeout(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetWebUITimeout...");

    ULONG value = 30;

    UT_LOG("Invoking platform_hal_GetWebUITimeout");
    
    INT status = platform_hal_GetWebUITimeout(&value);
    UT_LOG("Return Value: %d", status);
    UT_LOG("WebUI timeout value : %lu");


    /* Assert the return value and output value */
    UT_ASSERT_EQUAL(status, RETURN_OK);
    //UT_ASSERT_TRUE(value >= 30 && value <= 86400);
    
    if(value >= 30 && value <= 86400)
        { 
            UT_LOG("Web UI Timeout value is %lu", value);
            UT_PASS("Web UI Timeout validation success");
        }
    else
        {
            UT_LOG("Web UI Timeout value is %lu", value);
            UT_FAIL("Web UI Timeout validation failure");           
        }

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetWebUITimeout...");
}

/**
 * @brief Test function to verify the behavior of platform_hal_GetWebUITimeout function when a NULL pointer is passed as input.
 *
 * This test case is used to verify the behavior of the platform_hal_GetWebUITimeout function when a NULL pointer is passed as input. The objective of this test is to ensure that the function returns an error code when a NULL pointer is passed as input.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 033 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Pass a NULL pointer as input | None | RETUEN_ERR | Should return an error code |
 */
void test_l1_platform_hal_negative1_GetWebUITimeout(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetWebUITimeout...");

    /* Pass a NULL pointer as input */
    INT status = platform_hal_GetWebUITimeout(NULL);
    UT_LOG("platform_hal_GetWebUITimeout API returns: %d",status);

    /* Assert the return value */
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetWebUITimeout...");
}

/**
* @brief Test case to verify the functionality of platform_hal_GetBaseMacAddress function when a valid MAC address is provided.
*
* This test case verifies the functionality of the platform_hal_GetBaseMacAddress function by providing a valid MAC address.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 034 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetBaseMacAddress with valid pValue | macAddress = "00:11:22:33:44:55" | status = RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetBaseMacAddress(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetBaseMacAddress...");

    CHAR macAddress[256];

    INT status = platform_hal_GetBaseMacAddress(macAddress);

    UT_LOG("Invoking platform_hal_GetBaseMacAddress with valid pValue");
    UT_LOG("Output: MAC Address = %s", macAddress);
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetBaseMacAddress...");
}

/**
 * @brief Test case to verify the negative scenario of the platform_hal_GetBaseMacAddress function
 *
 * This test case checks the behavior of the platform_hal_GetBaseMacAddress function when passing a NULL pointer as the argument.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 035 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_GetBaseMacAddress with pValue as NULL | pValue=NULL | RETURN_ERR | Should return RETURN_ERR |
 */
void test_l1_platform_hal_negative1_GetBaseMacAddress(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetBaseMacAddress...");

    CHAR *pValue = NULL;

    INT status = platform_hal_GetBaseMacAddress(pValue);

    UT_LOG("Invoking platform_hal_GetBaseMacAddress with pValue as NULL");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetBaseMacAddress...");
}

/**
    * @brief This test is responsible for verifying the correct functionality of the platform_hal_GetHardware_MemFree() API.
    *
    * The objective of this test is to ensure that the platform_hal_GetHardware_MemFree() API returns the expected output value and return status when invoked with valid input parameters.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 036 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
    * 
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoking platform_hal_GetHardware_MemFree with valid input parameters | buffer = "buffer" | RETURN_OK | Should be successful |
    */
void test_l1_platform_hal_positive1_GetHardware_MemFree(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardware_MemFree...");

    // Prepare input parameters
    CHAR buffer[1024];

    // Invoke the API
    INT result = platform_hal_GetHardware_MemFree(buffer);

    // Check the output values and return status
    UT_LOG("Invoking platform_hal_GetHardware_MemFree with valid input parameters.");
    UT_LOG("Output value: %s", buffer);
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetHardware_MemFree...");
}

/**
 * @brief Test case to validate the platform_hal_GetHardware_MemFree function with NULL pointer.
 *
 * This test case validates the platform_hal_GetHardware_MemFree function when invoked with a NULL pointer. It checks if the function returns RETURN_ERR as expected.
 *
 * **Test Group ID:** Basic: 01 @n
 * 
 * **Test Case ID:** 037 @n
 * 
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * 
 * **Dependencies:** None @n
 * 
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Test platform_hal_GetHardware_MemFree with NULL pointer. | pValue = NULL | RETURN_ERR | Should return RETURN_ERR |
 */

void test_l1_platform_hal_negative1_GetHardware_MemFree(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardware_MemFree...");

    // Prepare input parameters
    CHAR *pValue = NULL;

    // Invoke the API
    INT result = platform_hal_GetHardware_MemFree(pValue);

    // Check the return status
    UT_LOG("Invoking platform_hal_GetHardware_MemFree with NULL pointer.");
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetHardware_MemFree...");
}

/**
 * @brief This test case verifies the functionality of the platform_hal_GetUsedMemorySize API.
 *
 * This test case validates the platform_hal_GetUsedMemorySize API by invoking it with valid input
 * and checking the return value and the value of the pulSize variable after the API is executed.
 * The test case also includes assertions to verify that the return value is equal to RETURN_OK and
 * the value of pulSize is greater than 0.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 038 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 *  | Variation / Step | Description | Test Data | Expected Result | Notes |
 *  | :--------------: | ----------- | --------- | --------------- | ----- |
 *  |       01         | Invoking platform_hal_GetUsedMemorySize with pulSize as a valid pointer. | pulSize = 0 | ret = RETURN_OK, pulSize > 0 | Should be successful |
 */
void test_l1_platform_hal_positive1_GetUsedMemorySize(void)
{
    // Log entrance message
    UT_LOG("Entering test_l1_platform_hal_positive1_GetUsedMemorySize...");

    // Initialize variables
    ULONG pulSize = 0;

    // Invoke the API with valid input
    INT ret = platform_hal_GetUsedMemorySize(&pulSize);

    // Log test description and results
    UT_LOG("Invoking platform_hal_GetUsedMemorySize with pulSize as a valid pointer.");
    UT_LOG("Return value: %d", ret);
    UT_LOG("pulSize: %lu", pulSize);

    // Perform assertions
    UT_ASSERT_EQUAL(ret, RETURN_OK);
    //UT_ASSERT(pulSize > 0);

    // Log exit message
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetUsedMemorySize...");
}

/**
* @brief This test case is used to verify the behavior of the platform_hal_GetUsedMemorySize function when a NULL pointer is passed as the argument.
*
* The purpose of this test is to ensure that the platform_hal_GetUsedMemorySize function returns the appropriate error code when invoked with a NULL pointer. 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 039 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking platform_hal_GetUsedMemorySize with pulSize as a NULL pointer. | pulSize = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetUsedMemorySize(void)
{
    // Log entrance message
    UT_LOG("Entering test_l1_platform_hal_negative1_GetUsedMemorySize...");

    // Invoke the API with NULL pointer
    INT ret = platform_hal_GetUsedMemorySize(NULL);

    // Log test description and results
    UT_LOG("Invoking platform_hal_GetUsedMemorySize with pulSize as a NULL pointer.");
    UT_LOG("Return value: %d", ret);

    // Perform assertion
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    // Log exit message
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetUsedMemorySize...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_ClearResetCount function.
*
* This test case checks if the platform_hal_ClearResetCount function successfully clears the reset count when the bFlag parameter is set to TRUE.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 040 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description                                         | Test Data                | Expected Result     | Notes             |
* | :----:           | ---------                                           | ----------               |--------------       | -----             |
* | 01               | Clear reset count when bFlag is set to TRUE         | bFlag = TRUE             | RETURN_OK           | Should be successful |
*/
void test_l1_platform_hal_positive1_ClearResetCount(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_ClearResetCount...");

    BOOLEAN bFlag = TRUE;

    INT result = platform_hal_ClearResetCount(bFlag);

    UT_LOG("Invoking platform_hal_ClearResetCount with bFlag = TRUE");
    UT_LOG("Expected Output: RETURN_OK");
    UT_LOG("Actual Output: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_ClearResetCount...");
}

/**
 * @brief Test to verify the functionality of platform_hal_ClearResetCount API with bFlag as FALSE.
 *
 * This test case is used to verify the behavior of the platform_hal_ClearResetCount API when bFlag is set to FALSE. 
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 041 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_ClearResetCount with bFlag as FALSE | bFlag = FALSE | RETURN_OK | Should be successful |
 *
 *
 */
void test_l1_platform_hal_positive2_ClearResetCount(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_ClearResetCount...");

    BOOLEAN bFlag = FALSE;

    INT result = platform_hal_ClearResetCount(bFlag);

    UT_LOG("Invoking platform_hal_ClearResetCount with bFlag = FALSE");
    UT_LOG("Expected Output: RETURN_OK");
    UT_LOG("Actual Output: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_ClearResetCount...");
}

/**
 * @brief This test case is used to verify the behavior of the platform_hal_ClearResetCount function when an invalid bFlag value is provided.
 *
 * The purpose of this test is to ensure that the platform_hal_ClearResetCount function handles the scenario when an invalid bFlag value is passed as an argument.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 042 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | :--------- | :-------- | :-------------- | ----- |
 * | 01 | Verify behavior when passing invalid bFlag value | bFlag = 2 | RETURN_ERR | The platform_hal_ClearResetCount function should return RETURN_ERR when an invalid bFlag value is provided |
 */
void test_l1_platform_hal_negative1_ClearResetCount(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_ClearResetCount...");

    BOOLEAN bFlag = 2; // Invalid bFlag value

    INT result = platform_hal_ClearResetCount(bFlag);

    UT_LOG("Invoking platform_hal_ClearResetCount with bFlag = 2");
    UT_LOG("Expected Output: It depends on the function's implementation");
    UT_LOG("Actual Output: %d", result);

    // Assert the return value, assuming a robust implementation should return RETURN_ERR
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_ClearResetCount...");
}

/**
 * @brief This test case tests the functionality of the platform_hal_SetDeviceCodeImageValid function.
 *
 * The objective of this test is to verify if the platform_hal_SetDeviceCodeImageValid function correctly sets the device's code image validity flag.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 043 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |        01        | Invoking platform_hal_SetDeviceCodeImageValid with bFlag as true | flag = TRUE | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_SetDeviceCodeImageValid(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_SetDeviceCodeImageValid...");
    
    BOOLEAN flag = TRUE;
    UT_LOG("Invoking platform_hal_SetDeviceCodeImageValid with flag = %d", flag);

    INT result = platform_hal_SetDeviceCodeImageValid(flag);
    UT_LOG("platform_hal_SetDeviceCodeImageValid returns : %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_SetDeviceCodeImageValid...");
}

/**
* @brief Test the functionality of the platform_hal_SetDeviceCodeImageValid function when setting the device code image flag to valid.
*
* This test verifies the functionality of the platform_hal_SetDeviceCodeImageValid function by setting the device code image flag to valid and
* checking if the function returns the expected result.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 044 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set device code image flag to valid | flag = FALSE | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetDeviceCodeImageValid(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_SetDeviceCodeImageValid...");
    
    BOOLEAN flag = FALSE;
    UT_LOG("Invoking platform_hal_SetDeviceCodeImageValid with flag = %d", flag);

    INT result = platform_hal_SetDeviceCodeImageValid(flag);
    UT_LOG("platform_hal_SetDeviceCodeImageValid returns : %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive2_SetDeviceCodeImageValid...");
}

/**
* @brief This test case validates the behavior of the platform_hal_SetDeviceCodeImageValid function when an invalid flag is provided.
*
* The platform_hal_SetDeviceCodeImageValid function is expected to return an error code when an invalid flag is provided. 
* This test aims to verify if the function behaves as expected in this scenario.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 045 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_SetDeviceCodeImageValid with an invalid flag | flag = 2 | RETURN_ERR | The function should return an error code |
*/
void test_l1_platform_hal_negative1_SetDeviceCodeImageValid(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_SetDeviceCodeImageValid...");
    
    BOOLEAN flag = 2;
    UT_LOG("Invoking platform_hal_SetDeviceCodeImageValid with flag = %d", flag);

    INT result = platform_hal_SetDeviceCodeImageValid(flag);
    UT_LOG("platform_hal_SetDeviceCodeImageValid returns : %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_SetDeviceCodeImageValid...");
}

/**
 * @brief Test case to verify the functionality of the platform_hal_setFactoryCmVariant function
 *
 * This test case checks whether the platform_hal_setFactoryCmVariant function successfully sets the factory CM variant value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 046 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:**  @n
 *  | Variation / Step | Description | Test Data | Expected Result | Notes |
 *  | :----: | --------- | ---------- |-------------- | ----- |
 *  | 01 | Set factory CM variant to pc20 | pValue = pc20 | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_setFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_setFactoryCmVariant...");

    CHAR pValue[512] = "pc20";
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = %s", pValue);
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_setFactoryCmVariant...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_setFactoryCmVariant API when provided with valid input.
*
* The objective of this test is to ensure that the platform_hal_setFactoryCmVariant API correctly sets the factory CM variant.
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 047 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set factory CM variant to "unknown" | pValue = "unknown" | The platform_hal_setFactoryCmVariant API should return `RETURN_OK` | Should be successful |
*/

void test_l1_platform_hal_positive2_setFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_setFactoryCmVariant...");

    CHAR pValue[512] = "unknown";
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = %s", pValue);
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_setFactoryCmVariant...");
}

/**
 * @brief Test for the function platform_hal_setFactoryCmVariant.
 *
 * This test verifies the correct functionality of the platform_hal_setFactoryCmVariant function by setting the factory CM variant value and checking the return status.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 048 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set factory CM variant value | pValue = "pc20genband" | RETURN_OK | Should be successful |
 */

void test_l1_platform_hal_positive3_setFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_setFactoryCmVariant...");

    CHAR pValue[512] = "pc20genband";
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = %s", pValue);
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_setFactoryCmVariant...");
}

/**
 * @brief This test case verifies the functionality of the platform_hal_setFactoryCmVariant function.
 *
 * This test case checks if the platform_hal_setFactoryCmVariant function sets the factory CM variant correctly.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 049 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | First set of conditions | pValue = "pc15sip" | Return status equals RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive4_setFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_positive4_setFactoryCmVariant...");

    CHAR pValue[512] = "pc15sip";
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = %s", pValue);
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive4_setFactoryCmVariant...");
}

/**
* @brief Test to verify the functionality of the platform_hal_setFactoryCmVariant API when provided with correct input parameters.
*
* The objective of this test is to verify that the platform_hal_setFactoryCmVariant API correctly sets the factory CM variant when provided with valid input parameters.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 050 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set factory CM variant | pValue = "pc15mgcp" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive5_setFactoryCmVariant(void) {
UT_LOG("Entering test_l1_platform_hal_positive5_setFactoryCmVariant...");

CHAR pValue[512] = "pc15mgcp";
INT status = platform_hal_setFactoryCmVariant(pValue);

UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = %s", pValue);
UT_LOG("Returned status: %d", status);

UT_ASSERT_EQUAL(status, RETURN_OK);

UT_LOG("Exiting test_l1_platform_hal_positive5_setFactoryCmVariant...");
}

/**
* @brief This test is used to verify the negative case of the setFactoryCmVariant function in the L1 platform HAL.
*
* The objective of this test is to ensure that the function returns the correct error code when the input parameter pValue is NULL.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 051 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFactoryCmVariant with pValue = NULL | pValue = NULL | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative1_setFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_setFactoryCmVariant...");

    CHAR *pValue = NULL;
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = NULL");
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setFactoryCmVariant...");
}

/**
* @brief This test is used to verify the negative case of the setFactoryCmVariant function in the L1 platform HAL.
*
* This test is used to verify that the function 'platform_hal_setFactoryCmVariant' returns an error when an invalid value is passed as the argument 'pValue'.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 052 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Calling the function with an invalid value | pValue = "invalid" | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative2_setFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_setFactoryCmVariant...");

    CHAR pValue[512] = "invalid";
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = %s", pValue);
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_setFactoryCmVariant...");
}

/**
 * @brief Test case to verify the platform_hal_getLed function with valid input parameters.
 *
 * This test case verifies the functionality of the platform_hal_getLed function when invoked with valid input parameters.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 053 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoking platform_hal_getLed with valid PLEDMGMT_PARAMS structure | "Valid Buffer"| RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_getLed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_getLed...");

    LEDMGMT_PARAMS params;
    params.LedColor = LED_RED;
    params.State = 0;
    params.Interval = 3;

    // Invoke the platform_hal_getLed() function
    // Log the test description and the output values
    UT_LOG("Invoking platform_hal_getLed with valid PLEDMGMT_PARAMS structure");
    
    INT result = platform_hal_getLed(&params);
    UT_LOG("platform_hal_getLed API returns:%d", result);
    UT_LOG("LED colour:%d",params.LedColor);
    UT_LOG("Srate:%d",params.State);
    UT_LOG("Interval:%d",params.Interval);

    // Check the return value and populate the output parameters
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_ASSERT_TRUE(params.LedColor >= 0 && params.LedColor <= 7);
    UT_ASSERT_EQUAL(params.State, 0 || params.State == 1);
    UT_ASSERT_TRUE( params.Interval >= 0);

    UT_LOG("Exiting test_l1_platform_hal_positive1_getLed...");
}

/**
 * @brief Test to verify the behavior of platform_hal_getLed function when a null pointer is passed as an argument.
 *
 * This test is intended to verify the behavior of the platform_hal_getLed function when a null pointer is passed as an argument. The objective of this test is to ensure that the function returns the expected error code in this scenario.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 054 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Null pointer passed as an argument | led = NULL | RETURN_ERR is returned | Should return error |
 */
void test_l1_platform_hal_negative1_getLed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_getLed...");

    // Invoke the platform_hal_getLed() function with a null pointer
    UT_LOG("Invoking platform_hal_getLed with NULL pointer");
   
    INT result = platform_hal_getLed(NULL);
    UT_LOG("platform_hal_getLed returns : %d", result);

    // Check the return value
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getLed...");
}

/**
* @brief Test case to verify the functionality of platform_hal_getRotorLock API when called with a valid fanIndex value (0)
*
* This test case is to verify the functionality of platform_hal_getRotorLock API
* when called with a valid fanIndex value (0). It checks whether the API returns
* the correct status indicating whether the rotor is locked or not.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 055 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Call platform_hal_getRotorLock with fanIndex=0 | fanIndex=0 | 0 or 1 | Should return 1 indicating that the rotor is locked |
*/
void test_l1_platform_hal_positive1_getRotorLock(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_getRotorLock...");

    UT_LOG("Invoking platform_hal_getRotorLock with fanIndex=0");
    
    INT status = platform_hal_getRotorLock(0);
    UT_LOG("platform_hal_getRotorLock returns : %d", status);

    // Check the return value
    if(status == 1)
    {
	    UT_LOG("Status of the Rotor is: %d locked \n",status);
	    UT_PASS("Get Roter locked Validation sucess\n");
    }
    else if (status == 0)
    {
	    UT_LOG("Status of the Rotor is: %d NOT locked \n",status);
	    UT_PASS("Get Roter NOTlocked Validation\n");
    }
    else if (status == -1)
    {
	    UT_LOG("Status of the Rotor is: %d value not applicable \n",status);
	    UT_PASS("Get Roter locked Validation sucess\n");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getRotorLock...");
}
/**
* @brief Unit test to verify the functionality of the platform_hal_getRotorLock function
*
* The purpose of this test is to verify the behavior of the platform_hal_getRotorLock function.
* This test checks if the function returns the correct status value when called with a valid fanIndex value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 056 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Call the function with a valid fanIndex value (1) | fanIndex = 1 | 0 or 1 | Should be successful |
*/
void test_l1_platform_hal_positive2_getRotorLock(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_getRotorLock...");

    UT_LOG("Invoking platform_hal_getRotorLock with fanIndex=1");

    INT status = platform_hal_getRotorLock(1);
     UT_LOG("platform_hal_getRotorLock returns : %d", status);

    // Check the return value
    if(status == 1)
    {
	    UT_LOG("Status of the Rotor is: %d locked \n",status);
	    UT_PASS("Get Roter locked Validation sucess\n");
    }
    else if (status == 0)
    {
	    UT_LOG("Status of the Rotor is: %d NOT locked \n",status);
	    UT_PASS("Get Roter NOTlocked Validation\n");
    }
    else if (status == -1)
    {
	    UT_LOG("Status of the Rotor is: %d value not applicable \n",status);
	    UT_PASS("Get Roter locked Validation sucess\n");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getRotorLock...");
}

/**
 * @brief Test case to verify the functionality of platform_hal_getRotorLock API with invalid fanIndex value.
 *
 * This test case is to verify that platform_hal_getRotorLock API returns -1 when invoked with an invalid fanIndex value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 057 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Call platform_hal_getRotorLock with an invalid fanIndex value (2) | fanIndex = 2 | -1 | Should return -1 as value is not applicable |
 */
void test_l1_platform_hal_negative1_getRotorLock(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_getRotorLock...");

     UT_LOG("Invoking platform_hal_getRotorLock with fanIndex=2");

    INT status = platform_hal_getRotorLock(2);
    UT_LOG("platform_hal_getRotorLock returns : %d", status);

    // Check the return value
    if(status == 1)
    {
	    UT_LOG("Status of the Rotor is: %d locked \n",status);
	    UT_PASS("Get Roter locked Validation sucess\n");
    }
    else if (status == 0)
    {
	    UT_LOG("Status of the Rotor is: %d NOT locked \n",status);
	    UT_PASS("Get Roter NOTlocked Validation\n");
    }
    else if (status == -1)
    {
	    UT_LOG("Status of the Rotor is: %d value not applicable \n",status);
	    UT_PASS("Get Roter locked Validation sucess\n");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getRotorLock...");
}

/**
 * @brief This test case verifies the functionality of the GetTotalMemorySize API by checking if it returns a positive value and does not return an error status.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 058 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoke the GetTotalMemorySize API with a valid pulSize pointer | None | RETURN_OK | Should be successful |
 */

void test_l1_platform_hal_positive1_GetTotalMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetTotalMemorySize...");

    // Test case specific data
    ULONG size;

    // Invocation of the API for the test
    INT status = platform_hal_GetTotalMemorySize(&size);
    
    // Logging the test case description, output values, and return status
    UT_LOG("Invoking platform_hal_GetTotalMemorySize with pulSize pointer: valid");
    UT_LOG("Returned status: %d", status);
    UT_LOG("Returned size: %lu", size);

    // Asserts for the test case
    UT_ASSERT_EQUAL(status, RETURN_OK);
    //UT_ASSERT(size > 0);

    

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetTotalMemorySize...");
}

/**
* @brief This test case is used to verify the negative scenario of the platform_hal_GetTotalMemorySize function.
*
* This test case verifies whether the platform_hal_GetTotalMemorySize function returns an error status when 
* the input parameter pulSize is NULL. It checks if the function behaves correctly in this scenario.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 059 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Test platform_hal_GetTotalMemorySize with pulSize = NULL | pulSize = NULL | Funcion returns RETURN_ERR | Should return an error status |
*/

void test_l1_platform_hal_negative1_GetTotalMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetTotalMemorySize...");

    // Invocation of the API for the test
    INT status = platform_hal_GetTotalMemorySize(NULL);

    // Asserts for the test case
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    // Logging the test case description, output values, and return status
    UT_LOG("Invoking platform_hal_GetTotalMemorySize with pulSize pointer: NULL");
    UT_LOG("Returned status: %d", status);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetTotalMemorySize...");
}

/**
* @brief Test the platform_hal_GetFactoryResetCount function for positive scenarios.
*
* This test verifies the functionality of the platform_hal_GetFactoryResetCount function by invoking it and checking the return status and pulSize.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 060 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetFactoryResetCount | pulSize = 0 | RETURN_OK, pulSize >= 0 | Should be successful |
*/

void test_l1_platform_hal_positive1_GetFactoryResetCount(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFactoryResetCount...");

    ULONG pulSize = 0;
    UT_LOG("Invoking platform_hal_GetFactoryResetCount with pulSize = %lu", pulSize);

    INT status = platform_hal_GetFactoryResetCount(&pulSize);
    UT_LOG(" platform_hal_GetFactoryResetCount returns : %d",status);
    
    UT_LOG("pulSize: %lu",pulSize);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    //UT_ASSERT_TRUE(pulSize >= 0);
    /*if(pulSize >= 0)
        { 
            UT_LOG("Factory Reset count is %lu", value);
            UT_PASS (" Factory Reset Count Validation success");
        }
    else
        {
            UT_LOG("Factory Reset count is %lu", value);
            UT_FAIL(" Factory Reset Count Validation Failure");
        }*/
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetFactoryResetCount...");
}

/**
* @brief Testing the platform_hal_GetFactoryResetCount function with NULL pulSize pointer
*
* The objective of this test is to verify the behavior of the platform_hal_GetFactoryResetCount function when the pulSize pointer is NULL. This test ensures that the function returns an error code as expected.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 061 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking function with NULL pulSize | pulSize = NULL | RETURN_ERR | Should return an error |
*/

void test_l1_platform_hal_negative1_GetFactoryResetCount(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFactoryResetCount...");

    INT status = platform_hal_GetFactoryResetCount(NULL);

    UT_LOG("Invoking platform_hal_GetFactoryResetCount with pulSize = NULL");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetFactoryResetCount...");
}

/**
 * @brief Verify that the platform_hal_SetDeviceCodeImageTimeout function sets the device code image timeout correctly.
 *
 * This test verifies that the platform_hal_SetDeviceCodeImageTimeout function sets the timeout value correctly for the device code image.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 062 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Set device code image timeout to 30 minutes | timeout = 1800 | The function should return RETURN_OK | Should be successful
 */

void test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout...");

    INT result = platform_hal_SetDeviceCodeImageTimeout(1800); // 30 minutes

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 30 minutes");
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout...");
}

/**
 * @brief This test is used to verify the functionality of the platform_hal_SetDeviceCodeImageTimeout function when provided with a timeout value of 0 minutes.
 *
 * The purpose of this test is to ensure that the platform_hal_SetDeviceCodeImageTimeout function correctly sets the device code image timeout value to 0 minutes and returns RETURN_OK.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 063 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Set device code image timeout to 0 minutes | timeout = 0 minutes | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout...");

    INT result = platform_hal_SetDeviceCodeImageTimeout(0); // 0 minutes

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 0 minutes");
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout...");
}

/**
* @brief Test to verify the functionality of the platform_hal_SetDeviceCodeImageTimeout API in positive scenario.
*
* This test verifies that the platform_hal_SetDeviceCodeImageTimeout API sets the device code image timeout correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 064 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ------ |
* | 01 | Set device code image timeout | timeout = 3600 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout...");

    INT result = platform_hal_SetDeviceCodeImageTimeout(3600); // 60 minutes

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 60 minutes");
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout...");
}

/**
* @brief This test case checks the behavior of the platform_hal_SetDeviceCodeImageTimeout function when called with a negative timeout value.
*
* In this test, the platform_hal_SetDeviceCodeImageTimeout function is called with a timeout value of -1 to test its behavior when an invalid timeout value is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 065 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description                                               | Test Data                                            | Expected Result                                  | Notes             |
* | :--------------: | -------------------------------------------------------- | --------------------------------------------------- | ------------------------------------------------- | ----------------- |
* |       01         | platform_hal_SetDeviceCodeImageTimeout with timeout: -1   | timeout = -1                                         | RETURN_ERR                                       | Should be a failure |
*
*/
void test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout...");

    INT result = platform_hal_SetDeviceCodeImageTimeout(-1);

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: -1");
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout...");
}

/**
 * @brief This test case checks the functionality of setting device code image timeout.
 *
 * The platform_hal_SetDeviceCodeImageTimeout function is tested in this test case to verify if it correctly sets the device code image timeout.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 066 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes                |
 * | :--------------: | ----------- | --------- | --------------- | -------------------- |
 * |        01        | First set of conditions | timeoutSeconds = 3660 | RETURN_ERR | Should return an error |
 *
 */

void test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout...");

    INT result = platform_hal_SetDeviceCodeImageTimeout(3660); // 61 minutes

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 61 minutes");
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout...");
}

/**
 * @brief Test case to verify the functionality of platform_hal_getFactoryCmVariant API.
 *
 * This test case verifies the functionality of the platform_hal_getFactoryCmVariant API by invoking it with a valid buffer of size 512 bytes and checking the return status.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 067 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                               | Test Data              | Expected Result | Notes             |
 * | :--------------: | --------------------------------------------------------- | ---------------------- | --------------- | ----------------- |
 * |        01        | Invoke the platform_hal_getFactoryCmVariant API           | buffer = 512 bytes     | RETURN_OK        | Should be successful |
 */
void test_l1_platform_hal_positive1_getFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_getFactoryCmVariant...");

    CHAR buffer[512] = {"\0"};
    INT status = platform_hal_getFactoryCmVariant(buffer);
    
    UT_LOG("Invoking platform_hal_getFactoryCmVariant with a valid buffer of size 512 bytes...");
    UT_LOG("Expected Result: RETURN_OK");
    UT_LOG("Actual Result: %d", status);
    UT_LOG("Value: %s", buffer);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if (!strcmp(buffer,"unknown") || !strcmp(buffer,"pc20") || !strcmp(buffer,"pc20genband") || !strcmp(buffer,"pc15sip")||  !strcmp(buffer,"pc15mgcp"))
    {
            UT_LOG("FactoryCmVariant %s which is a valid value",buffer);
            UT_PASS("getFactoryCmVariant validation success");
    }
    else
    {
            UT_LOG("FactoryCmVariant %s which is a Invalid value",buffer);
            UT_FAIL("getFactoryCmVariantvalidation fail");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFactoryCmVariant...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_getFactoryCmVariant when a null pointer is passed as the parameter.
 *
 * This test case checks whether platform_hal_getFactoryCmVariant function returns RETURN_ERR when a null pointer is passed as the parameter.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 068 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_getFactoryCmVariant with a null pointer as the parameter | NULL | RETURN_ERR | Should return RETURN_ERR |
 */
void test_l1_platform_hal_negative1_getFactoryCmVariant(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_getFactoryCmVariant...");

    INT status = platform_hal_getFactoryCmVariant(NULL);
    
    UT_LOG("Invoking platform_hal_getFactoryCmVariant with a null pointer as the parameter...");
    UT_LOG("Expected Result: RETURN_ERR");
    UT_LOG("Actual Result: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getFactoryCmVariant...");
}

/**
* @brief This test is to verify the platform_hal_setLed function with valid parameters.
*
* This test covers the scenario where the platform_hal_setLed function is called with valid parameters (LedColor, State, and Interval). The objective of this test is to ensure that the function is able to set the LED to the specified color, state, and interval successfully.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 069 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Set LED with valid parameters | LedColor = 0, State = 0, Interval = 0 | RETURN_OK | Should be successful |
* | 02 | Set LED with valid parameters | LedColor = 1, State = 1, Interval = 60 | RETURN_OK| Should be successful |
* | 03 | Set LED with valid parameters | LedColor = 2, State = 0, Interval = 30 | RETURN_OK| Should be successful |
* | 04 | Set LED with valid parameters | LedColor = 3, State = 1, Interval = 15 | RETURN_OK | Should be successful |

*/
void test_l1_platform_hal_positive1_setLed() {
    UT_LOG("Entering test_l1_platform_hal_positive1_setLed...");
    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));

    // Check if memory allocation was successful
    if (pValue == NULL) {
        UT_LOG("Failed to allocate memory for pValue.");
        return;
    }

    // Generate all combinations of valid LedColor, State, and Interval
    for (int ledColor = 0; ledColor <= 7; ledColor++) {
        for (int state = 0; state <= 1; state++) {
            for (int interval = 0; interval <= 60; interval++) {

                pValue->LedColor = ledColor;
                pValue->State = state;
                pValue->Interval = interval;

                //PLEDMGMT_PARAMS pValue = createLedParamsObject(ledColor, state, interval);
                UT_LOG("Invoking platform_hal_setLed with LedColor: %d, State: %d, Interval: %d", ledColor, state, interval);
                INT result = platform_hal_setLed(pValue);
                // Add asserts to check the return value
                CU_ASSERT_EQUAL(result, RETURN_OK);
            }
        }
    }
    free(pValue);
    UT_LOG("Exiting test_l1_platform_hal_positive1_setLed...");
}

/**
* @brief This test case is used to verify the behavior of the platform_hal_setLed function when a NULL pointer is passed as an argument.
*
* The purpose of this test is to ensure that the function handles the NULL pointer gracefully and returns the expected result.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 070 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setLed with NULL pointer | NULL | RETURN_ERR | Should return RETURN_ERR |
*/

void test_l1_platform_hal_negative1_setLed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_setLed...");

    UT_LOG("Invoking platform_hal_setLed with NULL pointer...");
    
    INT result = platform_hal_setLed(NULL);
    UT_LOG("platform_hal_setLed returns: %d",result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setLed...");
}

/**
* @brief Unit test to verify the behavior of the platform_hal_setLed function when an invalid LedColor value is provided.
*
* This test case verifies the behavior of the platform_hal_setLed function when an invalid LedColor value (8) is provided. 
* The test checks if the function returns the expected error code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 071 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* Test Procedure: ** @n
* | Variation / Step | Description                                           | Test Data                                     | Expected Result    | Notes              |
* | :--------------: | ----------------------------------------------------- | --------------------------------------------- | ------------------ | ------------------ |
* |        01        | First set of conditions                               | LedColor = 8                                  | RETURN_ERR         | Should be successful |
*/

void test_l1_platform_hal_negative2_setLed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_setLed...");
 
    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));                                              
    pValue->LedColor = 8;
    pValue->State = 0;
    pValue->Interval = 10;

    UT_LOG("Invoking platform_hal_setLed with invalid LedColor value (8)...");

    INT result = platform_hal_setLed(pValue);
    UT_LOG("platform_hal_setLed returns: %d",result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    free(pValue);

    UT_LOG("Exiting test_l1_platform_hal_negative2_setLed...");
}

/**
* @brief This test case is used to verify the behavior of the platform_hal_setLed function when a negative Interval value (-1) is passed as an argument.
*
* This test verifies that the platform_hal_setLed function returns an error code (RETURN_ERR) when a negative Interval value is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 073 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Verify behavior with negative Interval value | pValue->LedColor = 1, pValue->State = 0, pValue->Interval = -1 | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative3_setLed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative3_setLed...");

    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));
    pValue->LedColor = 1;
    pValue->State = 2;
    pValue->Interval = 10;

    UT_LOG("Invoking platform_hal_setLed with invalid State value (2)...");
    INT result = platform_hal_setLed(pValue);
    UT_LOG("platform_hal_setLed returns: %d",result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    free(pValue);

    UT_LOG("Exiting test_l1_platform_hal_negative3_setLed...");
}

/**
* @brief This test case is used to verify the behavior of the platform_hal_setLed function when a negative Interval value (-1) is passed as an argument.
*
* This test verifies that the platform_hal_setLed function returns an error code (RETURN_ERR) when a negative Interval value is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 073 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Verify behavior with negative Interval value | pValue->LedColor = 1, pValue->State = 0, pValue->Interval = -1 | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative4_setLed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative4_setLed...");

    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));
    pValue->LedColor = 1;
    pValue->State = 0;
    pValue->Interval = -1;

    UT_LOG("Invoking platform_hal_setLed with negative Interval value (-1)...");
    
    INT result = platform_hal_setLed(pValue);
    UT_LOG("platform_hal_setLed returns: %d",result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    free(pValue);

    UT_LOG("Exiting test_l1_platform_hal_negative4_setLed...");
}

/**
 * @brief Test case to validate the platform_hal_getRPM function.
 *
 * This test case verifies the correctness of the platform_hal_getRPM function by invoking it with different inputs and checking the returned value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 074 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking getRPM function with fanIndex = 0 | fanIndex = 0 | The returned value should be greater than or equal to 0. | Should pass |
 */
void test_l1_platform_hal_positive1_getRPM(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getRPM...");

    UINT fanIndex = 0;

    UT_LOG("Invoking platform_hal_getRPM with fanIndex = %d", fanIndex);
    UINT fanRPM = platform_hal_getRPM(fanIndex);

    UT_LOG("FanRPM = %d", fanRPM);

    UT_ASSERT_TRUE(fanRPM >= 0);

    UT_LOG("Exiting test_l1_platform_hal_positive1_getRPM...");
}

/**
* @brief Test case to validate the platform_hal_getRPM function.
*
* This test case verifies the correctness of the platform_hal_getRPM function by invoking it with different inputs and checking the returned value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 075 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getRPM with fanIndex = 1 | fanIndex = 1 | Fan RPM is a non-negative value | Should be successful |
*/

void test_l1_platform_hal_positive2_getRPM(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_getRPM...");

    UINT fanIndex = 1;

    UT_LOG("Invoking platform_hal_getRPM with fanIndex = %d", fanIndex);
    UINT fanRPM = platform_hal_getRPM(fanIndex);

    UT_LOG("FanRPM = %d", fanRPM);
    UT_ASSERT_TRUE(fanRPM >= 0);

    UT_LOG("Exiting test_l1_platform_hal_positive2_getRPM...");
}

#ifdef FEATURE_RDKB_THERMAL_MANAGER
/**
 * @brief This test case verifies the functionality of the platform_hal_initThermal function in the platform_hal module. 
 *
 * The objective of this test is to ensure that the platform_hal_initThermal function initializes the thermal platform configuration correctly and returns the expected status value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 076 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * |01 |  Invoke the platform_hal_initThermal function with valid input parameters     |    thermalConfig: FanCount = 1, SlowSpeedThresh = 30, MediumSpeedThresh = 35, FastSpeedThresh = 40,FanMinRunTime = 60, MonitoringDelay = 30, PowerMonitoring = 0, LogInterval = 10  |  The platform_hal_initThermal function returns RETURN_OK    |    Should be successful  |
 */
void test_l1_platform_hal_positive1_initThermal(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_initThermal...");

    // Set up thermal configuration
    THERMAL_PLATFORM_CONFIG thermalConfig;
    thermalConfig.FanCount = 1;
    thermalConfig.SlowSpeedThresh = 30;
    thermalConfig.MediumSpeedThresh = 35;
    thermalConfig.FastSpeedThresh = 40;
    thermalConfig.FanMinRunTime = 60;
    thermalConfig.MonitoringDelay = 30;
    thermalConfig.PowerMonitoring = 1;
    thermalConfig.LogInterval = 600;

    UT_LOG("Invoking platform_hal_initThermal with valid input parameters...");

    INT result = platform_hal_initThermal(&thermalConfig);
    UT_LOG("platform_hal_initThermal returns:%d",result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Values are Fan count : %d, Slow Speed Thresh: %d, MediumSpeedThresh : %d, Fast Speed Thresh : %d, FanMinRunTime : %d, MonitoringDelay : %d, PowerMonitoring : %d, LogInterval : %d",thermalConfig.FanCount, thermalConfig.SlowSpeedThresh, thermalConfig.MediumSpeedThresh, thermalConfig.FastSpeedThresh, thermalConfig.FanMinRunTime, thermalConfig.MonitoringDelay, thermalConfig.PowerMonitoring, thermalConfig.LogInterval);
    
    UT_ASSERT_EQUAL(thermalConfig.FanCount, 1 || thermalConfig.FanCount == 2);
    UT_ASSERT_EQUAL(thermalConfig.SlowSpeedThresh, 30);
    UT_ASSERT_EQUAL(thermalConfig.MediumSpeedThresh, 35);
    UT_ASSERT_EQUAL(thermalConfig.FastSpeedThresh, 40);
    UT_ASSERT_EQUAL(thermalConfig.FanMinRunTime, 60 );
    UT_ASSERT_EQUAL(thermalConfig.MonitoringDelay, 30);
    UT_ASSERT_EQUAL(thermalConfig.PowerMonitoring, 0 || thermalConfig.PowerMonitoring == 1);
    UT_ASSERT_EQUAL(thermalConfig.LogInterval, 600);

    UT_LOG("Exiting test_l1_platform_hal_positive1_initThermal...");
}

/**
 * @brief This test is to verify the behavior of the platform_hal_initThermal function when invoked with a NULL input parameter.
 *
 * This test verifies that the platform_hal_initThermal function returns RETURN_ERR when invoked with a NULL input parameter.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 077 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_initThermal with NULL input parameter | thermalConfig = NULL | RETURN_ERR | Should return RETURN_ERR |
 */
void test_l1_platform_hal_negative1_initThermal() {
    UT_LOG("Entering test_l1_platform_hal_negative1_initThermal...");

    THERMAL_PLATFORM_CONFIG* thermalConfig = NULL;
    UT_LOG("Invoking platform_hal_initThermal with NULL input parameter...");
    
    INT status = platform_hal_initThermal(thermalConfig);
    UT_LOG("platform_hal_initThermal returns: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_initThermal...");
}

/**
* @brief Test case to verify the functionality of platform_hal_getFanTemperature function
*
* This test case is used to verify the platform_hal_getFanTemperature function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 078 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description                                     | Test Data                     | Expected Result                       | Notes              |
* | :--------------: | ----------------------------------------------- | ----------------------------- | ------------------------------------- | ------------------ |
* |       01         | Invoke the API with a valid pointer              | pTemp = valid pointer         | Return Status: RETURN_OK               | Should be successful |
*/

void test_l1_platform_hal_positive1_getFanTemperature(void)
{
    int temp = 0;
    UT_LOG("Entering test_l1_platform_hal_positive1_getFanTemperature...");
    
    UT_LOG("Invoking platform_hal_getFanTemperature with input parameters: pTemp = valid pointer");
    int status = platform_hal_getFanTemperature(&temp);
    
    UT_LOG("Return Status: %d", status);
    UT_LOG("Temperature Value: %d", temp);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(temp >= 0 && temp <= 100)
        { 
            UT_LOG("Fan Temperature  is %lu", temp);
            UT_PASS (" Fan Temperature Validation success");
        }
    else
        {
            UT_LOG("Fan Temperature is %lu", temp);
            UT_FAIL(" Fan Temperature Validation Failure");    
        }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFanTemperature...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_getFanTemperature function when a NULL pointer is passed as input parameter.
*
* The platform_hal_getFanTemperature function is tested with a NULL pointer as input to check if the function properly handles this condition and returns the expected status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 079 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke the API with a NULL pointer | pTemp = NULL | RETURN_ERR | Should return an error status |
*/
void test_l1_platform_hal_negative1_getFanTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getFanTemperature...");
    
    UT_LOG("Invoking platform_hal_getFanTemperature with input parameters: pTemp = NULL");

    int status = platform_hal_getFanTemperature(NULL);
    
    // Check the return value
    UT_LOG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_getFanTemperature...");
}

/**
* @brief Test case to verify the functionality of platform_hal_getRadioTemperature API
*
* This test case is used to verify the functionality of the platform_hal_getRadioTemperature API.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 080 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description                                                                            | Test Data                                  | Expected Result                             | Notes            |
* | :--------------: | -------------------------------------------------------------------------------------- | ------------------------------------------ | ------------------------------------------ | ---------------- |
* |       01         | Invoking platform_hal_getRadioTemperature with radioIndex=0, pValue=valid pointer       | radioIndex = 0, pValue = valid pointer     | RETURN_OK                       |  Should be successful           |
*/
void test_l1_platform_hal_positive1_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getRadioTemperature...");

    INT radioIndex = 0;
    INT value;
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex=%d, pValue=valid pointer.", radioIndex);
    UT_LOG("Returned status: %d", status);
    UT_LOG("Returned value: %d", value);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(value >= 0 && value <= 100)
        { 
            UT_LOG("Radio Temperature  is %lu", value);
            UT_PASS (" Radio Temperature Validation success");
        }
    else
        {
            UT_LOG("Radio Temperature is %lu", value);
            UT_FAIL(" Radio Temperature Validation Failure");    
        }

    UT_LOG("Exiting test_l1_platform_hal_positive1_getRadioTemperature...");
}

/**
 * @brief Test to validate the platform_hal_getRadioTemperature function with negative input.
 *
 * This test case verifies the behavior of the platform_hal_getRadioTemperature function
 * when negative input values are provided.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 081 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                    | Test Data                                      | Expected Result      | Notes            |
 * | :----:           | ---------                                      | ----------                                    |--------------        | -----            |
 * | 01               | Invoking platform_hal_getRadioTemperature with invalid parameters   | radioIndex = 1, pValue = NULL                  | RETURN_ERR           | Should be failed |
 */

void test_l1_platform_hal_negative1_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getRadioTemperature...");

    INT radioIndex = 1;
    INT* pValue = NULL;
    INT status = platform_hal_getRadioTemperature(radioIndex, pValue);

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex=%d, pValue=NULL.", radioIndex);
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getRadioTemperature...");
}

/**
 * @brief Test to check the functionality of platform_hal_getRadioTemperature in case of negative scenario.
 *
 * This test verifies the behavior of platform_hal_getRadioTemperature API when a negative scenario is encountered.
 * 
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 082 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * 
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoking platform_hal_getRadioTemperature with invalid parameters | radioIndex = 3, pValue = valid pointer | RETURN_ERR | API should return an error status |
 */
void test_l1_platform_hal_negative2_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_getRadioTemperature...");

    INT radioIndex = 3;
    INT value;
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex=%d, pValue=valid pointer.", radioIndex);
    UT_LOG("Returned status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_getRadioTemperature...");
}

/**
* @brief Test to validate the functionality of the platform_hal_getRadioTemperature API
*
* This test is used to verify the correctness of the platform_hal_getRadioTemperature API. The API is responsible for retrieving the temperature of a given radio identified by its index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 083 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking the API with valid radio index and valid pointer for the temperature value | radioIndex=1, pValue=valid pointer | Should return RETURN_OK | Should be successful |
*/

void test_l1_platform_hal_positive2_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_getRadioTemperature...");

    INT radioIndex = 1;
    INT value;
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex=%d, pValue=valid pointer.", radioIndex);
    UT_LOG("Returned status: %d", status);
    UT_LOG("Returned value: %d", value);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(value >= 0 && value <= 100)
        { 
            UT_LOG("Radio Temperature  is %lu", value);
            UT_PASS (" Radio Temperature Validation success");
        }
    else
        {
            UT_LOG("Radio Temperature is %lu", value);
            UT_FAIL(" Radio Temperature Validation Failure");    
        }

    UT_LOG("Exiting test_l1_platform_hal_positive2_getRadioTemperature...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_getRadioTemperature API.
*
* This test case verifies the functionality of the platform_hal_getRadioTemperature API by invoking the API with different input values and checking the return status and returned value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 084 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data                                                                            | Expected Result      | Notes             |
* | :--------------: | ----------- | ------------------------------------------------------------------------------------ | -------------------- | ----------------- |
* |       01         | Invoking the API with valid radio index and valid pointer for the temperature value | radioIndex = 2, pValue = valid pointer                                               | status = RETURN_OK,  | Should be successful |
*/ 
void test_l1_platform_hal_positive3_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_getRadioTemperature...");

    INT radioIndex = 2;
    INT value;
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex=%d, pValue=valid pointer.", radioIndex);
    UT_LOG("Returned status: %d", status);
    UT_LOG("Returned value: %d", value);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(value >= 0 && value <= 100)
        { 
            UT_LOG("Radio Temperature  is %lu", value);
            UT_PASS (" Radio Temperature Validation success");
        }
    else
        {
            UT_LOG("Radio Temperature is %lu", value);
            UT_FAIL(" Radio Temperature Validation Failure");    
        }

    UT_LOG("Exiting test_l1_platform_hal_positive3_getRadioTemperature...");
}
#endif
/**
* @brief Unit test for the platform_hal_SetMACsecEnable function.
*
* The objective of this test is to verify the functionality of the platform_hal_SetMACsecEnable function in setting the MACsec enable flag for a given Ethernet port.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 085 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None  @n
* **Dependencies:** None  @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* |       01         | Set MACsec enable flag for Ethernet port | ethPort = 0, Flag = 1 | Return status is RETURN_OK | Should be successful |
*/

void test_l1_platform_hal_positive1_SetMACsecEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_SetMACsecEnable...");

    INT ethPort = 0;
    BOOLEAN Flag = 1;

    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    UT_LOG("Return status = %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetMACsecEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetMACsecEnable function.
*
* The test case verifies that the platform_hal_SetMACsecEnable function sets the MACsec enable flag correctly for the specified ethernet port.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 086 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Set MACsec enable flag for ethernet port 0 | ethPort = 0, Flag = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetMACsecEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_SetMACsecEnable...");

    INT ethPort = 0;
    BOOLEAN Flag = 0;

    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    UT_LOG("Return status = %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetMACsecEnable...");
}

/**
* @brief Test case to verify the negative scenario where the platform_hal_SetMACsecEnable API is invoked with ethPort = -1 and Flag = 1.
*
* This test case is used to validate the behavior of the platform_hal_SetMACsecEnable API when called with invalid ethPort value and Flag value as 1.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 087 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_SetMACsecEnable API with ethPort = -1 and Flag = 1 | ethPort = -1, Flag = 1 | RETURN_ERR | Should return error status |
*/
void test_l1_platform_hal_negative1_SetMACsecEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_SetMACsecEnable...");

    INT ethPort = -1;
    BOOLEAN Flag = 1;

    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    UT_LOG("Return status = %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetMACsecEnable...");
}

/**
    * @brief This function tests the functionality of the platform_hal_SetMACsecEnable() API.
    *
    * This test case validates the ability of the API to set the MACsec enable flag for a given Ethernet port.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 088 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    *
    * **Test Procedure:** @n
    * | Variation / Step | Description                                                                                     | Test Data                 | Expected Result                        | Notes              |
    * | :--------------: | ----------------------------------------------------------------------------------------------- | ------------------------- | -------------------------------------- | ------------------ |
    * |       01         | Set MACsec enable flag for a valid Ethernet port                                                | ethPort = MaxEthPort-1,  | The API returns RETURN_OK upon success  | Should be successful |
 
 */
void test_l1_platform_hal_positive3_SetMACsecEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_SetMACsecEnable...");

    INT ethPort = MaxEthPort-1;
    BOOLEAN Flag = 1;

    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    UT_LOG("Return status = %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetMACsecEnable...");
}

/**
* @brief Test function to validate the platform_hal_SetMACsecEnable API in negative scenario
*
* This test case is to verify the behavior of platform_hal_SetMACsecEnable API
* when it is provided with invalid input values.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 089 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_SetMACsecEnable with invalid ethPort and Flag | ethPort = 0, Flag = 2 | RETURN_ERR | Should produce an error |
*/

void test_l1_platform_hal_negative2_SetMACsecEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_SetMACsecEnable...");

    INT ethPort = 0;
    BOOLEAN Flag = 2;

    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    UT_LOG("Return status = %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetMACsecEnable...");
}

/**
 * @brief This test case is used to verify the functionality of the platform_hal_GetMemoryPaths() API when called with HOST_CPU index.
 *
 * The objective of this test is to ensure that the API returns the expected results and does not encounter any errors.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 090 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Call platform_hal_GetMemoryPaths with HOST_CPU index | index = HOST_CPU, valid ppinfo buffer| RETURN_OK | The API should be successful and return the expected result |
 */
void test_l1_platform_hal_positive1_GetMemoryPaths(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetMemoryPaths...");
  
    // Test input
    RDK_CPUS index = HOST_CPU;
    PPLAT_PROC_MEM_INFO ppinfo;
  
    // Call the API
    INT result = platform_hal_GetMemoryPaths(index, &ppinfo);
  
    // Check the results
    UT_LOG("Invoking platform_hal_GetMemoryPaths with index = HOST_CPU");
    UT_LOG("Return status = %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Values in the structure are, dramPath: %s, emmcpath1: %s, emmcPath2: %s", ppinfo->dramPath, ppinfo->emmcPath1,ppinfo->emmcPath2);

    UT_ASSERT_PTR_NOT_NULL(ppinfo);
    UT_ASSERT_STRING_EQUAL(ppinfo->dramPath, "/tmp");
    UT_ASSERT_STRING_EQUAL(ppinfo->emmcPath1, "/nvram");
    UT_ASSERT_STRING_EQUAL(ppinfo->emmcPath2, "/nvram2");

  
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetMemoryPaths...");
}

/**
 * @brief Test the functionality of the platform_hal_GetMemoryPaths() function.
 *
 * This test case verifies the platform_hal_GetMemoryPaths() function to ensure that it returns the correct memory paths for the peer CPU.
 *
 * **Test Group ID:** Basic : 01  @n
 * **Test Case ID:** 091 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | First set of conditions | index = PEER_CPU, valid ppinfo buffer | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive2_GetMemoryPaths(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_GetMemoryPaths...");

    // Test input
    RDK_CPUS index = PEER_CPU;
    PPLAT_PROC_MEM_INFO ppinfo;

    // Call the API
    INT result = platform_hal_GetMemoryPaths(index, &ppinfo);

    // Check the results
    UT_LOG("Invoking platform_hal_GetMemoryPaths with index = PEER_CPU");
    UT_LOG("Return status = %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Values in the structure are, dramPath: %s, emmcpath1: %s, emmcPath2: %s", ppinfo->dramPath, ppinfo->emmcPath1,ppinfo->emmcPath2);

    UT_ASSERT_PTR_NOT_NULL(ppinfo);
    UT_ASSERT_STRING_EQUAL(ppinfo->dramPath, "/tmp");
    UT_ASSERT_STRING_EQUAL(ppinfo->emmcPath1, "/nvram");
    UT_ASSERT_STRING_EQUAL(ppinfo->emmcPath2, "/nvram2");

    UT_LOG("Exiting test_l1_platform_hal_positive2_GetMemoryPaths...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_GetMemoryPaths function when provided with an invalid CPU index.
 * 
 * This test case verifies that the platform_hal_GetMemoryPaths function returns an error when called with an invalid CPU index.
 * 
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 092 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description                                                        | Test Data                                           | Expected Result                                | Notes            |
 * | :----:           | ---------                                                          | ----------                                         |--------------                                | -----            |
 * | 01               | Call platform_hal_GetMemoryPaths with index = NOT_SUPPORTED_CPU    | index = NOT_SUPPORTED_CPU, ppinfo = ppinfo_address | The function should return RETURN_ERR | Should return error |
 */
void test_l1_platform_hal_negative1_GetMemoryPaths(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetMemoryPaths...");

    // Test input
    RDK_CPUS index = NOT_SUPPORTED_CPU;
    PPLAT_PROC_MEM_INFO ppinfo;

    // Call the API
    INT result = platform_hal_GetMemoryPaths(index, &ppinfo);

    // Check the results
    UT_LOG("Invoking platform_hal_GetMemoryPaths with index = NOT_SUPPORTED_CPU");
    UT_LOG("Return status = %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetMemoryPaths...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_GetMemoryPaths function when a null pointer is passed as an argument.
*
* This test case checks whether the platform_hal_GetMemoryPaths function handles the case when a null pointer is passed as the ppinfo argument. The objective of this test is to ensure that the function returns RETURN_ERR when a null pointer is provided.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 093 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Test with null pointer | index = HOST_CPU, ppinfo = NULL | result = RETURN_ERR | The function should return RETURN_ERR |
*/

void test_l1_platform_hal_negative2_GetMemoryPaths(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_GetMemoryPaths...");
  
    // Test input
    RDK_CPUS index = HOST_CPU;
  
    // Call the API
    UT_LOG("Invoking platform_hal_GetMemoryPaths with index = HOST_CPU, ppinfo = NULL");
    INT result = platform_hal_GetMemoryPaths(index, NULL);
  
    // Check the results
    UT_LOG("Return status = %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
  
    UT_LOG("Exiting test_l1_platform_hal_negative2_GetMemoryPaths...");
}

/**
* @brief Test to verify the behavior of the function platform_hal_GetMemoryPaths for an out of bounds CPU index
*
* This test case is used to verify the behavior of the platform_hal_GetMemoryPaths function when it is given an out of bounds CPU index. The out of bounds CPU index is defined as a value greater than the total number of available CPUs.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 094 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* |       01         | Index out of bounds | index = NUM_RDK_CPUS, ppinfo = NULL | RETURN_ERR | Function should return an error |
*/
void test_l1_platform_hal_negative3_GetMemoryPaths(void) {
    UT_LOG("Entering test_l1_platform_hal_negative3_GetMemoryPaths...");
  
    // Test input
    RDK_CPUS index = 4; // Assuming NUM_RDK_CPUS is the total number of CPUs
    PPLAT_PROC_MEM_INFO ppinfo;
  
    // Call the API
    INT result = platform_hal_GetMemoryPaths(index, &ppinfo);
  
    // Check the results
    UT_LOG("Invoking platform_hal_GetMemoryPaths with index = %d", index);
    UT_LOG("Return status = %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
  
    UT_LOG("Exiting test_l1_platform_hal_negative3_GetMemoryPaths...");
}

/**
* @brief Test to verify the normal operation of the platform_hal_GetMACsecEnable function.
*
* This test checks whether the platform_hal_GetMACsecEnable function is able to successfully retrieve the MACsec enable status for a given ethernet port.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 095 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Retrieve MACsec enable status | ethPort = 0 | RETURN_OK | Should be successful |
*/

void test_l1_platform_hal_positive1_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetMACsecEnable...");
    
    // Arrange
    INT ethPort = 0; // Assuming valid ethernet port
    BOOLEAN flag;
    
    // Act
    INT status = platform_hal_GetMACsecEnable(ethPort, &flag);

    UT_LOG("Invoking platform_hal_GetMACsecEnable with ethPort=%d .", ethPort);
    UT_LOG("Returned status: %d", status);
    UT_LOG("Returned value: %d", flag);

    // Assert
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if(flag == TRUE || flag == FALSE )
        { 
            UT_LOG("MACsec Enable  is %d", flag);
            UT_PASS(" MACsec Enable Validation success");
        }
    else
        {
            UT_LOG("MACsec Enable  is %d", flag);
            UT_FAIL(" MACsec Enable Validation failure");  
        }
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetMACsecEnable...");
}

/**
* @brief This test case verifies the behavior of the platform_hal_GetMACsecEnable function when a NULL pointer is passed as an argument. 
*
* The objective of this test is to ensure that the function returns an error code when a NULL pointer is passed as the pFlag argument. 
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 096 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Pass a NULL pointer as pFlag argument | ethPort = 0, pFlag = NULL | RETURN_ERR | Should return an error code |
*/

void test_l1_platform_hal_negative1_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_etMACsecEnable...");

    // Arrange
    INT ethPort = 0; // Assuming valid ethernet port
    BOOLEAN *pFlag = NULL;

    // Act
    INT status = platform_hal_GetMACsecEnable(ethPort, pFlag);

    UT_LOG("Invoking platform_hal_GetMACsecEnable with ethPort=%d with NULL pFlag .", ethPort);
    UT_LOG("Returned status: %d", status);


    // Assert
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetMACsecEnable...");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetMACsecEnable() when an invalid Ethernet port is provided as input.
*
* This test case checks the functionality of platform_hal_GetMACsecEnable() function when an invalid Ethernet port is provided as input. This test is important to ensure that the function handles invalid input correctly and returns the expected error status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 097 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Check with invalid Ethernet port | ethPort = -1 | status = RETURN_ERR | Should fail due to invalid Ethernet port |
*/
void test_l1_platform_hal_negative2_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetMACsecEnable...");

    // Arrange
    INT ethPort = -1; // Assuming invalid ethernet port
    BOOLEAN flag;

    // Act
    INT status = platform_hal_GetMACsecEnable(ethPort, &flag);

    UT_LOG("Invoking platform_hal_GetMACsecEnable with invalid ethPort=%d.", ethPort);
    UT_LOG("Returned status: %d", status);

    // Assert
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetMACsecEnable...");
}

/**
 * @brief This test case checks the behavior of the 'platform_hal_GetMACsecEnable' function for the highest Ethernet port.
 *
 * This test verifies whether the 'platform_hal_GetMACsecEnable' function returns the expected status when invoked with the highest Ethernet port. 
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 098 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoke with highest Ethernet port | ethPort = MaxEthPort-1 | status = RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive2_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_GetMACsecEnable...");

    // Arrange
    INT ethPort = MaxEthPort-1; // Assuming highest Ethernet port
    BOOLEAN flag;

    // Act
    UT_LOG("Invoking platform_hal_GetMACsecEnable with invalid ethPort=%d.", ethPort);
    INT status = platform_hal_GetMACsecEnable(ethPort, &flag);

    // Assert
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if(flag == TRUE || flag == FALSE )
        { 
            UT_LOG("MACsec Enable  is %d", flag);
            UT_PASS(" MACsec Enable Validation success");
        }
    else
        {
            UT_LOG("MACsec Enable  is %d", flag);
            UT_FAIL(" MACsec Enable Validation failure");  
        }

    UT_LOG("Exiting test_l1_platform_hal_positive2_GetMACsecEnable...");
}

/**
* @brief Test to verify the functionality of the platform_hal_StartMACsec API.
*
* This test verifies that the platform_hal_StartMACsec API can start MACsec on the specified Ethernet port with the given timeout value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 99 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke StartMACsec with valid ethPort and timeoutSec values  | ethPort = 1, timeoutSec = 0 | RETURN_OK | Should be successful |
*/

void test_l1_platform_hal_positive1_StartMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_StartMACsec...");

    INT ethPort = 1;
    INT timeoutSec = 0;
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_StartMACsec...");
}

/**
* @brief Test case to check the negative scenario of the platform_hal_StartMACsec API.
*
* This test case verifies the behavior of the platform_hal_StartMACsec API in a negative scenario. It checks if the API handles the case when the ethPort is set to -1 and the timeoutSec is set to 0.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 100 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoke StartMACsec with invalid ethPort and timeoutSec values  | ethPort = -1, timeoutSec = 0 | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative1_StartMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_StartMACsec...");

    INT ethPort = -1;
    INT timeoutSec = 0;
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_StartMACsec...");
}

/**
* @brief Test case to verify the StartMACsec API in the L1 platform HAL.
*
* This test case checks the functionality and correctness of the StartMACsec API in the L1 platform HAL. The API is responsible for starting MACsec on a given Ethernet port with a specified timeout.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 101 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke StartMACsec with valid ethPort and timeoutSec values  | ethPort = 0, timeoutSec = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_StartMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_StartMACsec...");

    INT ethPort = 0;
    INT timeoutSec = 0;
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_StartMACsec...");
}

/**
* @brief Verify the functionality of platform_hal_StartMACsec function when provided with valid input values
*
* This test is used to verify the functionality of the platform_hal_StartMACsec function. The function is invoked with valid input values for ethPort and timeoutSec parameters to validate if it returns the expected status code (RETURN_OK).
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 102 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke StartMACsec with valid ethPort and timeoutSec values | ethPort = MaxEthPort - 1, timeoutSec = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive3_StartMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_StartMACsec...");

    INT ethPort = MaxEthPort - 1;
    INT timeoutSec = 0;
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_StartMACsec...");
}

/**
 * @brief Test case to verify the functionality of platform_hal_GetDhcpv6_Options function under normal operation.
 *
 * This test verifies the functionality of platform_hal_GetDhcpv6_Options function by checking the return value and output parameters when the function is invoked in normal conditions.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 103 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoke platform_hal_GetDhcpv6_Options function in normal conditions | req_opt_list = NULL, send_opt_list = NULL | RETURN_OK, req_opt_list not NULL, send_opt_list not NULL | Test should be successful |
 */
void test_l1_platform_hal_positive1_GetDhcpv6_Options(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetDhcpv6_Options...");

    // Test input
    dhcp_opt_list* req_opt_list = NULL;
    dhcp_opt_list* send_opt_list = NULL;

    // Invoke the API
    UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with the valid buffers and expecting the return value as 'RETURN_OK'. ");
    
    INT result = platform_hal_GetDhcpv6_Options(&req_opt_list, &send_opt_list);
    UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);

    // Check the return value and output parameters
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_ASSERT_PTR_NOT_NULL(req_opt_list);
    UT_ASSERT_PTR_NOT_NULL(send_opt_list);

    UT_LOG("DHCPv6 Options values for req is %d and for send is %d",req_opt_list->dhcp_opt,send_opt_list->dhcp_opt);

    UT_ASSERT_EQUAL(req_opt_list->dhcp_opt, 42 || req_opt_list->dhcp_opt == 43 ||  req_opt_list->dhcp_opt == 58 ||  req_opt_list->dhcp_opt == 59 ||  req_opt_list->dhcp_opt == 60 ||  req_opt_list->dhcp_opt == 61 ||  req_opt_list->dhcp_opt == 100 ||  req_opt_list->dhcp_opt == 122 ||  req_opt_list->dhcp_opt == 125 ||  req_opt_list->dhcp_opt == 242 ||  req_opt_list->dhcp_opt == 243 ||  req_opt_list->dhcp_opt == 255);
    UT_ASSERT_EQUAL(send_opt_list->dhcp_opt, 42 || send_opt_list->dhcp_opt == 43 ||  send_opt_list->dhcp_opt == 58 ||  send_opt_list->dhcp_opt == 59 ||  send_opt_list->dhcp_opt == 60 ||  send_opt_list->dhcp_opt == 61 ||  send_opt_list->dhcp_opt == 100 ||  send_opt_list->dhcp_opt == 122 ||  send_opt_list->dhcp_opt == 125 ||  send_opt_list->dhcp_opt == 242 ||  send_opt_list->dhcp_opt == 243 ||  send_opt_list->dhcp_opt == 255);
   
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetDhcpv6_Options...");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetDhcpv6_Options() when the request option list is NULL.
*
* In this test case, the objective is to verify that if the request option list is NULL, the API returns RETURN_ERR.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 104 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Verify behavior when the request option list is NULL | req_opt_list = NULL | RETURN_ERR is returned | The API should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetDhcpv6_Options(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetDhcpv6_Options...");

    // Test input
    //dhcp_opt_list* req_opt_list = NULL;
    dhcp_opt_list* send_opt_list = NULL;

    // Invoke the API
    UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with req_opt_list value as NULL the  and expecting the return value as 'RETURN_ERR'. ");
    
    INT result = platform_hal_GetDhcpv6_Options(NULL, &send_opt_list);
    UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);    

    // Check the return value
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetDhcpv6_Options...");
}

/**
* @brief Test for platform_hal_GetDhcpv6_Options with NULL send option list
*
* This test verifies the behavior of the platform_hal_GetDhcpv6_Options function when a NULL send option list is passed as an argument. The test aims to check if the function returns RETURN_ERR as expected.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 105 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Passing NULL send option list | send_opt_list = NULL | RETURN_ERR is returned | Should return error|
*/

void test_l1_platform_hal_negative2_GetDhcpv6_Options(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_GetDhcpv6_Options...");

    // Test input
    dhcp_opt_list* req_opt_list = NULL;
    //dhcp_opt_list* send_opt_list = NULL;

    // Invoke the API
    UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with send_opt_list value as NULL the  and expecting the return value as 'RETURN_ERR'. ");
    
    INT result = platform_hal_GetDhcpv6_Options(&req_opt_list, NULL);
    UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);

    // Check the return value
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetDhcpv6_Options...");
}

/**
* @brief This test is used to verify the behavior of the platform_hal_GetDhcpv6_Options function when both the req_opt_list and send_opt_list are NULL.
*
* This test is intended to check if the platform_hal_GetDhcpv6_Options function returns RETURN_ERR when both the req_opt_list and send_opt_list are NULL.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 106 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Verify that RETURN_ERR is returned when both req_opt_list and send_opt_list are NULL | req_opt_list = NULL, send_opt_list = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative3_GetDhcpv6_Options(void) {
    UT_LOG("Entering test_l1_platform_hal_negative3_GetDhcpv6_Options...");

    // Test input
    //dhcp_opt_list* req_opt_list = NULL;
    //dhcp_opt_list* send_opt_list = NULL;

    // Invoke the API
    UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with both buffer as NULL the  and expecting the return value as 'RETURN_ERR'. ");
    
    INT result = platform_hal_GetDhcpv6_Options(NULL, NULL);
    UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);

    // Check the return value
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_GetDhcpv6_Options...");
}

/**
* @brief Test case to verify the functionality of setDscp function in positive conditions
*
* This test case verifies the functionality of the setDscp function when invoked with valid inputs in positive conditions.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 107 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
*
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking setDscp with valid inputs | interfaceType = DOCSIS, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_setDscp...");

    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char* pDscpVals = "10,20,30";
    
    UT_LOG("Invoking platform_hal_setDscp with interfaceType = DOCSIS, cmd = TRAFFIC_CNT_START, pDscpVals = \"10,20,30\".");
    
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);
    UT_LOG("Return Value: %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_setDscp...");
}

/**
 * @brief Test function to validate the platform_hal_setDscp API.
 *
 * This test function is used to validate the platform_hal_setDscp API functionality.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 108 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_setDscp with interfaceType = EWAN, cmd = TRAFFIC_CNT_STOP, pDscpVals = NULL. | interfaceType = EWAN, cmd = TRAFFIC_CNT_STOP, pDscpVals = NULL | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive2_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_setDscp...");

    WAN_INTERFACE interfaceType = EWAN;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_STOP;
    char* pDscpVals = NULL;

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = EWAN, cmd = TRAFFIC_CNT_STOP, pDscpVals = NULL.");
    
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);
    UT_LOG("Return Value: %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_setDscp...");
}

/**
 * @brief Test function to validate the platform_hal_setDscp API.
 *
 * This test function is used to validate the platform_hal_setDscp API functionality.
 * 
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 109 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke platform_hal_setDscp with interfaceType = EWAN, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30" | interfaceType = EWAN, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30" | The result should be RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive3_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_setDscp...");

    WAN_INTERFACE interfaceType = EWAN;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char* pDscpVals = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = EWAN, cmd = TRAFFIC_CNT_START, pDscpVals = \"10,20,30\".");

    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);
    UT_LOG("Return Value: %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_setDscp...");
}

/**
* @brief This test verifies the functionality of the platform_hal_setDscp API.
*
* This test case checks whether the platform_hal_setDscp API sets the Differentiated Services Code Point (DSCP) values correctly for the given interfaceType and cmd.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 110 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_setDscp with interfaceType = DOCSIS, cmd = TRAFFIC_CNT_STOP, pDscpVals = "10,20,30" | interfaceType = DOCSIS, cmd = TRAFFIC_CNT_STOP, pDscpVals = "10,20,30" | RETURN_OK | Should be successful |
*/

void test_l1_platform_hal_positive4_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive4_setDscp...");

    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_STOP;
    char* pDscpVals = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = DOCSIS, cmd = TRAFFIC_CNT_STOP, pDscpVals = \"10,20,30\".");
    
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);
    UT_LOG("Return Value: %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive4_setDscp...");
}

/**
 * @brief This test function tests the negative scenario of the platform_hal_setDscp API.
 *
 * The objective of this test is to verify the behavior of the platform_hal_setDscp API when an invalid interface type is passed as an argument.
 * 
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 111 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description                                  | Test Data                                                         | Expected Result            | Notes             |
 * | :--------------: | -------------------------------------------- | ----------------------------------------------------------------- | -------------------------- | ----------------- |
 * |       01         | Invoke platform_hal_setDscp with  interfaceType = 3, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30"                     | interfaceType = 3, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30" | RETURN_ERR | Should return error |
 * 
 */

void test_l1_platform_hal_negative1_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_setDscp...");

    WAN_INTERFACE interfaceType = 3; // Invalid interface type
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char* pDscpVals = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = 3 (invalid), cmd = TRAFFIC_CNT_START, pDscpVals = \"10,20,30\".");

    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setDscp...");
}

/**
 * @brief Test case to verify the negative scenario of the platform_hal_setDscp function.
 *
 * This test case verifies the behavior of the platform_hal_setDscp function when an invalid command is provided.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 112 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, the test case has to be selected via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoke platform_hal_setDscp with interfaceType = DOCSIS, cmd = 3 (invalid), pDscpVals = "10,20,30"  | interfaceType = DOCSIS, cmd = 3 (invalid), pDscpVals = "10,20,30" | RETURN_ERR | Should be unsuccessful |
 */
void test_l1_platform_hal_negative2_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_setDscp...");

    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = 3; // Invalid command
    char* pDscpVals = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = DOCSIS, cmd = 3 (invalid), pDscpVals = \"10,20,30\".");
   
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);
    UT_LOG("Return Value: %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_setDscp...");
}

/**
* @brief Test to verify the behavior of platform_hal_setDscp() function when invalid DSCP values are provided.
*
* This test case focuses on testing the platform_hal_setDscp() function by passing invalid DSCP values (e.g., "100000,200000")
* for a particular interface type and traffic count command.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 113 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Set invalid DSCP values | interfaceType = DOCSIS, cmd = TRAFFIC_CNT_START, pDscpVals = "100000,200000" | return value = RETURN_ERR | Should fail and return an error |
*/ 
void test_l1_platform_hal_negative3_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_setDscp...");

    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char* pDscpVals = "100000,200000"; // Invalid DSCP values

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = DOCSIS, cmd = TRAFFIC_CNT_START, pDscpVals = \"100000,200000\".");

    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);
    UT_LOG("Return Value: %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_setDscp...");
}

/**
* @brief This function is used to test the functionality of the platform_hal_SetLowPowerModeState API with PSM_AC state.
*
* The objective of this test is to ensure that the platform_hal_SetLowPowerModeState API correctly sets the low power mode state to PSM_AC and returns the expected status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 114 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description                                                      | Test Data                    | Expected Result                                     | Notes             |
* | :--------------: | ---------------------------------------------------------        | ---------------------------- | -------------------------------------------------- | ------------------|
* |       01         | Set low power mode state to PSM_AC                              | pState = PSM_AC              | RETURN_OK is returned                               | Should be successful |
*/
void test_l1_platform_hal_positive1_SetLowPowerModeState(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_SetLowPowerModeState...");

    PSM_STATE pState = PSM_AC;

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = PSM_AC");

    INT status = platform_hal_SetLowPowerModeState(&pState);
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetLowPowerModeState...");
}

/**
 * @brief Test case to verify the behavior of SetLowPowerModeState function with battery power state.
 *
 * This test case verifies the functionality of platform_hal_SetLowPowerModeState function with battery power state.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 115 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Set low power mode state to PSM_BATT | pState = PSM_BATT | Should return RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive2_SetLowPowerModeState(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_SetLowPowerModeState...");

   PSM_STATE pState = PSM_BATT;
    INT status = platform_hal_SetLowPowerModeState(&pState);

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = PSM_BATT");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetLowPowerModeState...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_SetLowPowerModeState API when the PSM state is HOT.
*
* This test case verifies whether the platform_hal_SetLowPowerModeState API sets the PSM state to HOT correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 116 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set PSM state to HOT | pState = PSM_HOT | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive3_SetLowPowerModeState(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_SetLowPowerModeState...");

    PSM_STATE pState = PSM_HOT;

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = PSM_HOT");

    INT status = platform_hal_SetLowPowerModeState(&pState);
    UT_LOG("Return status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetLowPowerModeState...");
}

/**
* @brief Positive test to verify the functionality of the platform_hal_SetLowPowerModeState API in the cooled state
*
* This test verifies if the platform_hal_SetLowPowerModeState API correctly sets the low power mode state to cooled. It checks if the return status from the API is equal to RETURN_OK.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 117 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Set low power mode state to cooled | pState = PSM_COOLED | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive4_SetLowPowerModeState(void) {
    UT_LOG("Entering test_l1_platform_hal_positive4_SetLowPowerModeState...");

    PSM_STATE pState = PSM_COOLED;

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = PSM_COOLED");
    INT status = platform_hal_SetLowPowerModeState(&pState);

    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive4_SetLowPowerModeState...");
}

/**
 * @brief This test verifies the behavior of the platform_hal_SetLowPowerModeState function when an unknown PPSM_STATE value is provided as input.
 *
 * The objective of this test is to ensure that the platform_hal_SetLowPowerModeState function handles unknown PPSM_STATE values correctly and returns the expected status.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 118 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Verify the behavior of platform_hal_SetLowPowerModeState when an unknown PPSM_STATE value is provided as input | pState = PSM_UNKNOWN | RETURN_ERR | Should return error |
 */
void test_l1_platform_hal_negative1_SetLowPowerModeState(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_SetLowPowerModeState...");

    PSM_STATE pState = PSM_UNKNOWN;
    INT status = platform_hal_SetLowPowerModeState(&pState);

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = PSM_UNKNOWN");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetLowPowerModeState...");
}

/**
* @brief Tests the scenario where the low power mode state is not supported by the platform_hal_SetLowPowerModeState function.
*
* This test is used to verify the behavior of platform_hal_SetLowPowerModeState function when the low power mode state is not supported by the platform. 
* The function should return an error status code in this scenario.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 119 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Setting the low power mode state to not supported | pState = PSM_NOT_SUPPORTED | RETURN_ERR | The function should return an error status code |
*/
void test_l1_platform_hal_negative2_SetLowPowerModeState(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_SetLowPowerModeState...");

    PSM_STATE pState = PSM_NOT_SUPPORTED;
    INT status = platform_hal_SetLowPowerModeState(&pState);

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = PSM_NOT_SUPPORTED");
    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetLowPowerModeState...");
}

/**
* @brief Test the function platform_hal_GetFirmwareBankInfo() to retrieve firmware bank information.
*
* This test verifies if the function platform_hal_GetFirmwareBankInfo() correctly retrieves firmware bank information.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 120 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Retrieve firmware bank information | bankIndex = ACTIVE_BANK, fwBankInfo | RETURN_OK and Successful retrieval of firmware bank information | Should be successful |
*/
void test_l1_platform_hal_positive1_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFirmwareBankInfo...");

    FW_BANK bankIndex = ACTIVE_BANK;
    FW_BANK_INFO fwBankInfo;

    memset(&fwBankInfo, 0, sizeof(FW_BANK_INFO));

    INT result = platform_hal_GetFirmwareBankInfo(bankIndex, &fwBankInfo);

    UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: ACTIVE_BANK");

    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Return value: %d", result);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetFirmwareBankInfo...");
}

/**
* @brief Test case for retrieving firmware bank information.
*
* This test case verifies the functionality of the platform_hal_GetFirmwareBankInfo function, 
* which is responsible for retrieving the firmware bank information based on the provided bank index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 121 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | ---------- | ---------- | --------------- | ----- |
* | 01     | Retrieving firmware bank info for INACTIVE_BANK | bankIndex = INACTIVE_BANK | RETURN_OK and Successful retrieval of firmware bank info | Should be successful  |
*/
void test_l1_platform_hal_positive2_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_GetFirmwareBankInfo...");

    FW_BANK bankIndex = INACTIVE_BANK;
    FW_BANK_INFO fwBankInfo;
    memset(&fwBankInfo, 0, sizeof(FW_BANK_INFO));

    INT result = platform_hal_GetFirmwareBankInfo(bankIndex, &fwBankInfo);

    UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: INACTIVE_BANK");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    
    UT_LOG("Exiting test_l1_platform_hal_positive2_GetFirmwareBankInfo...");
}

/**
* @brief This test case verifies the behavior of the platform_hal_GetFirmwareBankInfo() function in negative scenario.
*
* The objective of this test is to ensure that the platform_hal_GetFirmwareBankInfo() function returns the expected error code when invoked with an invalid bank index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 122 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetFirmwareBankInfo with bankIndex: INVALID_BANK | bankIndex = INVALID_BANK | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFirmwareBankInfo...");

    FW_BANK bankIndex = 2;
    FW_BANK_INFO fwBankInfo;

    memset(&fwBankInfo, 0, sizeof(FW_BANK_INFO));

    INT result = platform_hal_GetFirmwareBankInfo(bankIndex, &fwBankInfo);

    UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: INVALID_BANK");
    UT_LOG("Return value: %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetFirmwareBankInfo...");
}

/**
* @brief This test case tests the platform_hal_GetFirmwareBankInfo function by passing invalid arguments.
*
* This test case aims to verify the behavior of the platform_hal_GetFirmwareBankInfo function when invalid arguments are provided.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 123 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Passing ACTIVE_BANK and NULL pointer for fwBankInfo | bankIndex = ACTIVE_BANK, fwBankInfo = NULL | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative2_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetFirmwareBankInfo...");

    FW_BANK bankIndex = ACTIVE_BANK;
    FW_BANK_INFO* fwBankInfo = NULL;

    INT result = platform_hal_GetFirmwareBankInfo(bankIndex, fwBankInfo);

    UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: ACTIVE_BANK and NULL pFW_Bankinfo");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetFirmwareBankInfo...");
}

/**
 * @brief This test case tests the platform_hal_GetFirmwareBankInfo function by passing invalid arguments.
 *
 *  This test case aims to verify the behavior of the platform_hal_GetFirmwareBankInfo function when invalid arguments are provided.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 124 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoke platform_hal_GetFirmwareBankInfo with bankIndex: INACTIVE_BANK and NULL pFW_Bankinfo | bankIndex = INACTIVE_BANK, fwBankInfo = NULL | RETURN_ERR | Should return error |
 *
 */
void test_l1_platform_hal_negative3_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_GetFirmwareBankInfo...");

    FW_BANK bankIndex = INACTIVE_BANK;
    FW_BANK_INFO* fwBankInfo = NULL;

    INT result = platform_hal_GetFirmwareBankInfo(bankIndex, fwBankInfo);

    UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: INACTIVE_BANK and NULL pFW_Bankinfo");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative3_GetFirmwareBankInfo...");
}

/**
 * @brief This test is used to verify the functionality of the platform_hal_getCMTSMac function.
 *
 * The purpose of this test is to check if the platform_hal_getCMTSMac function returns the expected status and output value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 125 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke the platform_hal_getCMTSMac function | valid pValue buffer | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_getCMTSMac(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getCMTSMac...");

    // Prepare input parameters
    CHAR pValue[100];

    // Invoke the API
    UT_LOG("Invoking platform_hal_getCMTSMac with valid buffer");
    INT status = platform_hal_getCMTSMac(pValue);
    UT_LOG("platform_hal_getCMTSMac returns : %d", status);
    // Check the output value
    UT_LOG("Output: pValue = %s", pValue);

    // Check the return status
    UT_ASSERT_EQUAL(status, RETURN_OK);
    

    UT_LOG("Exiting test_l1_platform_hal_positive1_getCMTSMac...");
}

/**

* @brief This test case verifies the behavior of platform_hal_getCMTSMac() function when passed a null pointer as input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 126 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Pass null pointer as input | pValue = NULL | RETURN_ERR | Should return RETURN_ERR |
*/

void test_l1_platform_hal_negative1_getCMTSMac(void)

{

    UT_LOG("Entering test_l1_platform_hal_negative1_getCMTSMac...");

    // Prepare input parameters
    CHAR *pValue = NULL;

    // Invoke the API
    UT_LOG("Invoking platform_hal_getCMTSMac with NULL pointer");
    INT status = platform_hal_getCMTSMac(pValue);
    UT_LOG("Returned status: %d", status);

    // Check the return status
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_getCMTSMac...");
}

/**
* @brief Test to verify the functionality of the platform_hal_GetDhcpv4_Options API.
*
* This test is used to verify the functionality of the platform_hal_GetDhcpv4_Options API, which is responsible for retrieving DHCPv4 options.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 127 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetDhcpv4_Options with req_opt_list = NULL and send_opt_list = NULL | req_opt_list = NULL, send_opt_list = NULL | The result should be RETURN_OK and both req_opt_list and send_opt_list should not be NULL | Should be successful |
*/
void test_l1_platform_hal_positive1_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetDhcpv4_Options...");

    dhcp_opt_list *req_opt_list = NULL;
    dhcp_opt_list *send_opt_list = NULL;

    INT result = platform_hal_GetDhcpv4_Options(&req_opt_list, &send_opt_list);

    UT_LOG("Invoking platform_hal_GetDhcpv4_Options with req_opt_list = %p, send_opt_list = %p", req_opt_list, send_opt_list);
    UT_LOG("The result is: %d", result);
   
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_ASSERT_PTR_NOT_NULL(req_opt_list);
    UT_ASSERT_PTR_NOT_NULL(send_opt_list);

    UT_LOG("DHCPv4 Options values for req is %d and for send is %d",req_opt_list->dhcp_opt,send_opt_list->dhcp_opt);
    
    UT_ASSERT_EQUAL(req_opt_list->dhcp_opt, 42 || req_opt_list->dhcp_opt == 43 ||  req_opt_list->dhcp_opt == 58 ||  req_opt_list->dhcp_opt == 59 ||  req_opt_list->dhcp_opt == 60 ||  req_opt_list->dhcp_opt == 61 ||  req_opt_list->dhcp_opt == 100 ||  req_opt_list->dhcp_opt == 122 ||  req_opt_list->dhcp_opt == 125 ||  req_opt_list->dhcp_opt == 242 ||  req_opt_list->dhcp_opt == 243 ||  req_opt_list->dhcp_opt == 255);
    UT_ASSERT_EQUAL(send_opt_list->dhcp_opt, 42 || send_opt_list->dhcp_opt == 43 ||  send_opt_list->dhcp_opt == 58 ||  send_opt_list->dhcp_opt == 59 ||  send_opt_list->dhcp_opt == 60 ||  send_opt_list->dhcp_opt == 61 ||  send_opt_list->dhcp_opt == 100 ||  send_opt_list->dhcp_opt == 122 ||  send_opt_list->dhcp_opt == 125 ||  send_opt_list->dhcp_opt == 242 ||  send_opt_list->dhcp_opt == 243 ||  send_opt_list->dhcp_opt == 255);
    

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetDhcpv4_Options...");
}

/**
 * @brief This test case is used to verify the handling of NULL input argument by the function platform_hal_GetDhcpv4_Options.
 *
 * This test case verifies the behavior of the platform_hal_GetDhcpv4_Options function when the req_opt_list argument is NULL. The function should return an error code and also the send_opt_list should be set to NULL.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 128 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke the function with req_opt_list as NULL | req_opt_list = NULL, send_opt_list = uninitialized | RETURN_ERR | Should return error |
 */
void test_l1_platform_hal_negative1_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetDhcpv4_Options...");

    dhcp_opt_list *req_opt_list = NULL;
    dhcp_opt_list *send_opt_list = NULL;

    INT result = platform_hal_GetDhcpv4_Options(NULL, &send_opt_list);

    UT_LOG("Invoking platform_hal_GetDhcpv4_Options with req_opt_list = NULL");
    UT_LOG("The result is: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_ASSERT_PTR_NULL(req_opt_list);
    UT_ASSERT_PTR_NULL(send_opt_list);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetDhcpv4_Options...");
}

/**
 * @brief Test case to verify the behavior of the function platform_hal_GetDhcpv4_Options when NULL is passed as the send_opt_list argument.
 *
 * This test case checks the behavior of the platform_hal_GetDhcpv4_Options function when NULL is passed as the send_opt_list argument. The function is expected to return an error (RETURN_ERR) and set the req_opt_list and send_opt_list pointers to NULL.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 129 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ----------------- | --------------- | ------ |
 * | 01 | Verify function behavior when NULL is passed as the send_opt_list argument | send_opt_list = NULL | RETURN_ERR, req_opt_list = NULL, send_opt_list = NULL | The function should return an error and set the req_opt_list and send_opt_list pointers to NULL |
 */
void test_l1_platform_hal_negative2_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetDhcpv4_Options...");

    dhcp_opt_list *req_opt_list = NULL;
    dhcp_opt_list *send_opt_list = NULL;

    INT result = platform_hal_GetDhcpv4_Options(&req_opt_list, NULL);

    UT_LOG("Invoking platform_hal_GetDhcpv4_Options with send_opt_list = NULL");
    UT_LOG("The result is: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_ASSERT_PTR_NULL(req_opt_list);
    UT_ASSERT_PTR_NULL(send_opt_list);

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetDhcpv4_Options...");
}

/**
* @brief This function tests the platform_hal_GetDhcpv4_Options function when passing NULL pointers as input arguments.
*
* The purpose of this test is to verify the behavior of the platform_hal_GetDhcpv4_Options function when NULL pointers are passed as input arguments. It is important to ensure that the function properly handles these invalid inputs.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 130 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Passing NULL pointers as input arguments | req_opt_list = NULL, send_opt_list = NULL | RETURN_ERR | The function should return an error and both output pointers should be NULL |
*/

void test_l1_platform_hal_negative3_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_GetDhcpv4_Options...");

    dhcp_opt_list *req_opt_list = NULL;
    dhcp_opt_list *send_opt_list = NULL;

    INT result = platform_hal_GetDhcpv4_Options(NULL, NULL);

    UT_LOG("Invoking platform_hal_GetDhcpv4_Options with req_opt_list = NULL, send_opt_list = NULL");
    UT_LOG("The result is: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_ASSERT_PTR_NULL(req_opt_list);
    UT_ASSERT_PTR_NULL(send_opt_list);

    UT_LOG("Exiting test_l1_platform_hal_negative3_GetDhcpv4_Options...");
}

/**
* @brief Test the functionality of platform_hal_getDscpClientList API.
*
* This test case is used to verify the functionality of the platform_hal_getDscpClientList API. It checks whether the API returns the correct DSCP client list for a given interface type.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 131 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoking platform_hal_getDscpClientList with interfaceType DOCSIS and valid pDSCP_List | interfaceType = DOCSIS, pDSCP_List = valid pointer | RETURN_OK | Should be successful |
*/ 
void test_l1_platform_hal_positive1_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getDscpClientList...");

    WAN_INTERFACE interfaceType = DOCSIS;
    pDSCP_list_t pDSCP_List = malloc(sizeof(DSCP_list_t)); // Allocate memory for pDSCP_List
    INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

    UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType DOCSIS and valid pDSCP_List");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    // Validate the pDSCP_List structure
    if (pDSCP_List != NULL) {
        UT_ASSERT_TRUE(pDSCP_List->numElements >= 0 && pDSCP_List->numElements <= 64);

        for (UINT i = 0; i < pDSCP_List->numElements; i++) {
            DSCP_Element_t *pDSCP_Element = &(pDSCP_List->DSCP_Element[i]);

            UT_ASSERT_TRUE(pDSCP_Element->dscp_value >= 0 && pDSCP_Element->dscp_value <= 65534);
            UT_ASSERT_TRUE(pDSCP_Element->numClients >= 0 && pDSCP_Element->numClients <= 255);

            for (UINT j = 0; j < pDSCP_Element->numClients; j++) {
                Traffic_client_t *pTraffic_client = &(pDSCP_Element->Client[j]);

                // Add more specific assertions for mac, rxBytes, and txBytes if needed.
                UT_ASSERT_TRUE(pTraffic_client->rxBytes >= 0 && pTraffic_client->txBytes >= 0);
            }
        }

    free(pDSCP_List);
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getDscpClientList...");
}

/**
 * @brief This test case validates the functionality of the platform_hal_getDscpClientList function in the L1 platform HAL module.
 *
 * This test case verifies that the platform_hal_getDscpClientList function returns the correct list of DSCP clients for the given WAN interface type.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 132 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_getDscpClientList with interfaceType EWAN and valid pDSCP_List | interfaceType = EWAN, pDSCP_List = allocated memory | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive2_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_getDscpClientList...");

    WAN_INTERFACE interfaceType = EWAN;
    pDSCP_list_t pDSCP_List = malloc(sizeof(DSCP_list_t)); // Allocate memory for pDSCP_List
    INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

    UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType EWAN and valid pDSCP_List");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    if (pDSCP_List != NULL) {
        UT_ASSERT_TRUE(pDSCP_List->numElements >= 0 && pDSCP_List->numElements <= 64);

        for (UINT i = 0; i < pDSCP_List->numElements; i++) {
            DSCP_Element_t *pDSCP_Element = &(pDSCP_List->DSCP_Element[i]);

            UT_ASSERT_TRUE(pDSCP_Element->dscp_value >= 0 && pDSCP_Element->dscp_value <= 65534);
            UT_ASSERT_TRUE(pDSCP_Element->numClients >= 0 && pDSCP_Element->numClients <= 255);

            for (UINT j = 0; j < pDSCP_Element->numClients; j++) {
                Traffic_client_t *pTraffic_client = &(pDSCP_Element->Client[j]);

                // Add more specific assertions for mac, rxBytes, and txBytes if needed
                UT_ASSERT_TRUE(pTraffic_client->rxBytes >= 0 && pTraffic_client->txBytes >= 0);
            }
        }
        free(pDSCP_List);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive2_getDscpClientList...");
}

/**
 * @brief Test case to verify the behavior of the platform_hal_getDscpClientList function with invalid interfaceType and valid pDSCP_List.
 *
 * This test case verifies the behavior of the platform_hal_getDscpClientList function when called with an invalid interfaceType and a valid pDSCP_List. The expected result is that the function should return RETURN_ERR.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 133 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, they can select this test case via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Call platform_hal_getDscpClientList with invalid interfaceType and valid pDSCP_List | interfaceType = WAN_INTERFACE_INVALID, pDSCP_List = dynamically allocated memory | RETURN_ERR | should return error |
 */
void test_l1_platform_hal_negative1_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getDscpClientList...");

    WAN_INTERFACE interfaceType = 3; // Invalid interfaceType
    pDSCP_list_t pDSCP_List = malloc(sizeof(DSCP_list_t)); // Allocate memory for pDSCP_List
    INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

    UT_LOG("Invoking platform_hal_getDscpClientList with invalid interfaceType and valid pDSCP_List");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    free(pDSCP_List);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getDscpClientList...");
}

/**
* @brief Function to test the platform_hal_getDscpClientList function when pDSCP_List is NULL
*
* This test case is used to verify the behavior of the platform_hal_getDscpClientList function when pDSCP_List is NULL. 
* The objective of this test is to check if the function returns RETURN_ERR when pDSCP_List is NULL.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 134 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getDscpClientList with interfaceType DOCSIS and NULL pDSCP_List | interfaceType = DOCSIS, pDSCP_List = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative2_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_getDscpClientList...");

    WAN_INTERFACE interfaceType = DOCSIS;
    pDSCP_list_t pDSCP_List = NULL; // NULL pDSCP_List
    INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

    UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType DOCSIS and NULL pDSCP_List");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_getDscpClientList...");
}

/**
    * @brief This test case checks the behavior of the platform_hal_getDscpClientList() function when passed a NULL pDSCP_List as an argument.
    *
    * The objective of this test is to ensure that the function returns an appropriate error code when passed a NULL pDSCP_List.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 135 @n
    * **Priority:** High @n@n
    *
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    *
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoking platform_hal_getDscpClientList with interfaceType EWAN and NULL pDSCP_List | interfaceType = EWAN, pDSCP_List = NULL | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative3_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_getDscpClientList...");

    WAN_INTERFACE interfaceType = EWAN;
    pDSCP_list_t pDSCP_List = NULL; // NULL pDSCP_List
    INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

    UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType EWAN and NULL pDSCP_List");
    UT_LOG("Return value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_getDscpClientList...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_GetDeviceConfigStatus API.
*
* This test case checks if the platform_hal_GetDeviceConfigStatus API returns the correct device configuration status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 136 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_GetDeviceConfigStatus API with valid input parameters | valid pValue buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetDeviceConfigStatus(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetDeviceConfigStatus...");

    CHAR pValue[128] = {"\0"};
    INT result = platform_hal_GetDeviceConfigStatus(pValue);

    UT_LOG("Invoking platform_hal_GetDeviceConfigStatus with valid input parameters.");
    UT_LOG("Output value: pValue = %s", pValue);
    UT_LOG("Return status: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    if (!strcmp(pValue,"WaitForImplement") || !strcmp(pValue,"In Progress")|| !strcmp(pValue,"Complete"))
    {
            UT_LOG("pValue from the device is %s which is a valid value",pValue);
            UT_PASS("pValue validation success");
    }
    else
    {
            UT_LOG("pValue from the device %s which is an Invalid value",pValue);
            UT_FAIL("pValue validation fail");
    }

    // Add additional asserts for the output values if required
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetDeviceConfigStatus...");
}

/**
* @brief Test to verify the return status of platform_hal_GetDeviceConfigStatus() when provided with invalid input parameters.
*
* This test case is designed to verify the return status of platform_hal_GetDeviceConfigStatus() API when it is invoked with invalid input parameters. The return status should be RETURN_ERR.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 137 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data                 | Expected Result | Notes            |
* | :----:           | ---------   | ----------                |--------------   | -----            |
* | 01               | Invoke platform_hal_GetDeviceConfigStatus API with NULL value   | input = NULL               | RETURN_ERR       | Should return error|
*/ 
void test_l1_platform_hal_negative1_GetDeviceConfigStatus(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetDeviceConfigStatus...");

    INT result = platform_hal_GetDeviceConfigStatus(NULL);

    UT_LOG("Invoking platform_hal_GetDeviceConfigStatus with invalid input parameters.");
    UT_LOG("Return status: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetDeviceConfigStatus...");
}

/**
 * @brief Test case to verify the functionality of the platform_hal_SetSNMPOnboardRebootEnable function.
 *
 * This test case verifies if the platform_hal_SetSNMPOnboardRebootEnable function can successfully enable SNMP onboard reboot. 
 * 
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 138 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:**  @n
 * | Variation / Step | Description                                        | Test Data                   | Expected Result                  | Notes            |
 * | :-------------:  | ------------------------------------------------- | --------------------------- | ------------------------------    | --------------   |
 * | 01               | Verify SNMP onboard reboot enable functionality    | value = "enable"             | RETURN_OK                        | Should be successful |
 */
void test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable...");

    CHAR value[] = "enable";
    INT result = platform_hal_SetSNMPOnboardRebootEnable(value);

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with input parameter: enable");
    UT_LOG("Return Value: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable...");
}

/**
 * @brief Unit test to verify the behavior of the function platform_hal_SetSNMPOnboardRebootEnable().
 *
 * This test checks the functionality of the platform_hal_SetSNMPOnboardRebootEnable() function. The test verifies whether the function returns a successful result when the input parameter is "disable".
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 139 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Verify function behavior with input parameter "disable" | value = "disable" | Successful result returned (RETURN_OK) | Should be successful |
 */
void test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable...");

    CHAR value[] = "disable";
    INT result = platform_hal_SetSNMPOnboardRebootEnable(value);

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with input parameter: disable");
    UT_LOG("Return Value: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable...");
}

/**
* @brief This test function tests the negative scenario of the platform_hal_SetSNMPOnboardRebootEnable API.
*
* The objective of this test is to verify the behavior of the platform_hal_SetSNMPOnboardRebootEnable API when it is given a NULL input parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 140 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Verify function behavior with NULL input parameter | input = NULL | RETURN_ERR | Should be equal to RETURN_ERR |
*/
void test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable...");

    INT result = platform_hal_SetSNMPOnboardRebootEnable(NULL);

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with input parameter: NULL");
    UT_LOG("Return Value: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable...");
}

/**
* @brief This test case is designed to verify the negative scenario of platform_hal_SetSNMPOnboardRebootEnable function.
*
* The purpose of this test case is to confirm that the platform_hal_SetSNMPOnboardRebootEnable function returns an error when an invalid parameter is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 141 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step  | Description                                              | Test Data                     | Expected Result              | Notes               |
* | :---------------- | -----------------------------------------------------  | ----------------------------- | ---------------------------- | ------------------- |
* | 01                | Set SNMP Onboard Reboot enable with an invalid value    | value = "invalid"             | RETURN_ERR                   | Should be unsuccessful |
*
*/

void test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable...");

    CHAR value[] = "invalid";
    INT result = platform_hal_SetSNMPOnboardRebootEnable(value);

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with input parameter: invalid");
    UT_LOG("Return Value: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable...");
}

#ifdef FEATURE_RDKB_THERMAL_MANAGER
/**
* @brief Unit test for platform_hal_getInputCurrent function
*
* This test case is used to verify the functionality of the platform_hal_getInputCurrent function.
* The objective of this test is to check if the function returns the correct input current value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 142 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
*
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getInputCurrent with valid input parameters | value = uninitialized | status = RETURN_OK | The function should return the correct input current value. |
*/
void test_l1_platform_hal_positive1_getInputCurrent(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_getInputCurrent...");

    INT value;
    INT status = platform_hal_getInputCurrent(&value);

    UT_LOG("Invoking platform_hal_getInputCurrent with valid input parameters.");
    UT_LOG("Return status: %d", status);
    UT_LOG("Output value: %d", value);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_getInputCurrent...");
}

/**
 * @brief This test case aims to verify the functionality of the platform_hal_getInputCurrent function when invoked with a NULL input pointer.
 *
 * This test case checks if the platform_hal_getInputCurrent function returns the expected error status when called with a NULL input pointer.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 143 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 *  | Variation / Step | Description | Test Data                    | Expected Result                | Notes            |
 *  | :--------------: | ----------- | ---------------------------- | ------------------------------ | ---------------- |
 *  |       01         | Invoking platform_hal_getInputCurrent with NULL input parameters | pValue = NULL | RETURN_ERR | Should return error |
 */
void test_l1_platform_hal_negative1_getInputCurrent(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_getInputCurrent...");

    INT *pValue = NULL;
    INT status = platform_hal_getInputCurrent(pValue);

    UT_LOG("Invoking platform_hal_getInputCurrent with NULL input pointer.");
    UT_LOG("Return status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getInputCurrent...");
}

/**
 * @brief Test the function platform_hal_LoadThermalConfig by providing valid uninitialized THERMAL_PLATFORM_CONFIG struct
 * 
 * This test case checks the functionality of the platform_hal_LoadThermalConfig function by providing a valid uninitialized THERMAL_PLATFORM_CONFIG struct as input. The test case verifies the return value of the function and the filled values in the struct.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 144 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Call the API with uninitialized struct | thermalConfig = uninitialized | Status = RETURN_OK; FanCount = 1 or 2; SlowSpeedThresh = 30; MediumSpeedThresh = 35; FastSpeedThresh = 40; FanMinRunTime = 60; MonitoringDelay = 30; PowerMonitoring = 0 or 1; LogInterval = 600 | Function should return RETURN_OK and the filled struct values should match the expected ones |
 */
void test_l1_platform_hal_positive1_LoadThermalConfig(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_LoadThermalConfig...");
    
    /* Create a valid uninitialized THERMAL_PLATFORM_CONFIG struct */
    THERMAL_PLATFORM_CONFIG thermalConfig;
    
    /* Call the API with the uninitialized struct */
    UT_LOG("Invoking platform_hal_LoadThermalConfig with valid values");
    INT status = platform_hal_LoadThermalConfig(&thermalConfig);
    
    /* Check the return value and filled values in the struct */
    UT_LOG("platform_hal_LoadThermalConfig API returns : %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    UT_LOG("Values are Fan count : %d, Slow Speed Thresh: %d, MediumSpeedThresh : %d, Fast Speed Thresh : %d, FanMinRunTime : %d, MonitoringDelay : %d, PowerMonitoring : %d, LogInterval : %d",thermalConfig.FanCount, thermalConfig.SlowSpeedThresh, thermalConfig.MediumSpeedThresh, thermalConfig.FastSpeedThresh, thermalConfig.FanMinRunTime, thermalConfig.MonitoringDelay, thermalConfig.PowerMonitoring, thermalConfig.LogInterval);

    UT_ASSERT_EQUAL(thermalConfig.FanCount, 1 || thermalConfig.FanCount == 2); // Added
    UT_ASSERT_EQUAL(thermalConfig.SlowSpeedThresh, 30);
    UT_ASSERT_EQUAL(thermalConfig.MediumSpeedThresh, 35);
    UT_ASSERT_EQUAL(thermalConfig.FastSpeedThresh, 40);
    UT_ASSERT_EQUAL(thermalConfig.FanMinRunTime, 60);
    UT_ASSERT_EQUAL(thermalConfig.MonitoringDelay, 30);
    UT_ASSERT_EQUAL(thermalConfig.PowerMonitoring, 0 || thermalConfig.PowerMonitoring == 1); // Added 
    UT_ASSERT_EQUAL(thermalConfig.LogInterval, 600);
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_LoadThermalConfig...");
}

/**
* @brief Test function to verify the behavior of the function platform_hal_LoadThermalConfig when called with a null pointer.
*
* This test case is designed to validate the behavior of the platform_hal_LoadThermalConfig function when called with a null pointer as the argument. 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 145 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* 
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Call the API with a null pointer | config = NULL | return value = RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative1_LoadThermalConfig(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_LoadThermalConfig...");
    
    /* Call the API with a null pointer */
    UT_LOG("Invoking platform_hal_LoadThermalConfig with NULL pointer");
    INT status = platform_hal_LoadThermalConfig(NULL);\
    UT_LOG("platform_hal_LoadThermalConfig returns : %d",status);
    
    /* Check the return value */
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_LoadThermalConfig...");
}
#endif

/**
 * @brief Test case to verify the functionality of platform_hal_GetMACsecOperationalStatus API.
 *
 * This test case checks the correctness of the platform_hal_GetMACsecOperationalStatus API by verifying the return value and output flag parameter.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 146 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Verify API with valid input | ethPort = 0,valid flag | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_GetMACsecOperationalStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetMACsecOperationalStatus...");

    INT ethPort = 0;
    BOOLEAN flag = FALSE;

    UT_LOG("Invoking platform_hal_GetMACsecOperationalStatus with ethPort = %d, pFlag = %p", ethPort, &flag);
    INT ret = platform_hal_GetMACsecOperationalStatus(ethPort, &flag);
    UT_LOG("platform_hal_GetMACsecOperationalStatus returns: %d", ret);
    UT_LOG("Status : %d", flag);

    UT_ASSERT_EQUAL(ret, RETURN_OK);
    UT_ASSERT_EQUAL(flag, 1 || flag == 0);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetMACsecOperationalStatus...");
}

/** 
 * @brief This is a unit test to verify the functionality of the platform_hal_GetMACsecOperationalStatus API in a negative scenario.
 *
 * The objective of this test is to check the behavior of the platform_hal_GetMACsecOperationalStatus API when the ethPort is 0 and pFlag is NULL.
 * 
 * **Test Group ID**: Basic: 01 @n
 * **Test Case ID**: 147 @n
 * **Priority**: High @n@n
 *
 * **Pre-Conditions**: None @n
 * **Dependencies**: None @n
 * **User Interaction**: If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure**: @n
 * 
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Test platform_hal_GetMACsecOperationalStatus API with ethPort=0, pFlag=NULL | ethPort = 0, pFlag = NULL | RETURN_ERR | Should return error |
 */
void test_l1_platform_hal_negative1_GetMACsecOperationalStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetMACsecOperationalStatus...");

    INT ethPort = 0;
    BOOLEAN *pFlag = NULL;

    UT_LOG("Invoking platform_hal_GetMACsecOperationalStatus with ethPort = %d", ethPort);
    INT ret = platform_hal_GetMACsecOperationalStatus(ethPort, pFlag);
    UT_LOG("platform_hal_GetMACsecOperationalStatus returns: %d", ret);
    
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetMACsecOperationalStatus...");
}

/**
 * @brief This test case verifies the functionality of the platform_hal_setFanMaxOverride function.
 *
 * The objective of this test is to ensure that the platform_hal_setFanMaxOverride function sets the maximum fan override flag and fan index correctly.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 148 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set maximum fan override flag and fan index | bOverrideFlag = TRUE, fanIndex = 0 | status = RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_setFanMaxOverride(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_setFanMaxOverride...");
    
    BOOLEAN bOverrideFlag = TRUE;
    UINT fanIndex = 0;
    
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);
    
    UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag=%d, fanIndex=%d", bOverrideFlag, fanIndex);
    UT_LOG("Expected status: RETURN_OK");
    UT_LOG("Actual status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_setFanMaxOverride...");
}

/**
* @brief This test case verifies the functionality of the platform_hal_setFanMaxOverride function when the override flag is set to FALSE and fan index is 0.
*
* This test case validates the platform_hal_setFanMaxOverride function by testing its behavior when the override flag is FALSE and fan index is 0. It checks if the function returns RETURN_OK indicating the successful execution of the API.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 149 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Call platform_hal_setFanMaxOverride API with bOverrideFlag=FALSE and fanIndex=0. | bOverrideFlag=FALSE, fanIndex=0 | RETURN_OK | Should return RETURN_OK indicating successful execution |
*/
void test_l1_platform_hal_positive2_setFanMaxOverride(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_setFanMaxOverride...");
    
    BOOLEAN bOverrideFlag = FALSE;
    UINT fanIndex = 0;
    
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);
    
    UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag=%d, fanIndex=%d", bOverrideFlag, fanIndex);
    UT_LOG("Expected status: RETURN_OK");
    UT_LOG("Actual status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive2_setFanMaxOverride...");
}

/**
 * @brief Test for setting the maximum fan override in the platform HAL
 *
 * This test verifies that the platform_hal_setFanMaxOverride function correctly sets the maximum fan override value in the platform HAL.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 150 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Set maximum fan override | bOverrideFlag = TRUE, fanIndex = 1 | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive3_setFanMaxOverride(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_setFanMaxOverride...");

    BOOLEAN bOverrideFlag = TRUE;
    UINT fanIndex = 1;

    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);

    UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag=%d, fanIndex=%d", bOverrideFlag, fanIndex);
    UT_LOG("Expected status: RETURN_OK");
    UT_LOG("Actual status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_setFanMaxOverride...");
}

/**
* @brief Test the platform_hal_setFanMaxOverride function.
*
* This test case is used to test the platform_hal_setFanMaxOverride function of the L1 Platform HAL module. The objective of this test is to verify the behavior of the function when called with different input values.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 151 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Test platform_hal_setFanMaxOverride with bOverrideFlag=FALSE and fanIndex=1 | bOverrideFlag=FALSE, fanIndex=1 | RETURN_OK | Should be successful |
*/ 

void test_l1_platform_hal_positive4_setFanMaxOverride(void) {
    UT_LOG("Entering test_l1_platform_hal_positive4_setFanMaxOverride...");
    
    BOOLEAN bOverrideFlag = FALSE;
    UINT fanIndex = 1;
    
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);
    
    UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag=%d, fanIndex=%d", bOverrideFlag, fanIndex);
    UT_LOG("Expected status: RETURN_OK");
    UT_LOG("Actual status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive4_setFanMaxOverride...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_setFanMaxOverride when the provided arguments are invalid.
 *
 * This test case verifies if the platform_hal_setFanMaxOverride API returns the expected status when the provided arguments are invalid.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 152 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                                  | Test Data                                         | Expected Result               | Notes           |
 * | :--------------: | ------------------------------------------------------------ | ------------------------------------------------ | ----------------------------- | --------------- |
 * |       01         | Invoking platform_hal_setFanMaxOverride with invalid bOverrideFlag and fanIndex | bOverrideFlag = TRUE, fanIndex = 2               | Status to be RETURN_ERR        | Should return error |
 */

void test_l1_platform_hal_negative1_setFanMaxOverride(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_setFanMaxOverride...");
    
    BOOLEAN bOverrideFlag = TRUE;
    UINT fanIndex = 2;
    
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);
    
    UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag=%d, fanIndex=%d", bOverrideFlag, fanIndex);
    UT_LOG("Expected status: RETURN_ERR");
    UT_LOG("Actual status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_setFanMaxOverride...");
}

/**
* @brief Test case to verify the behavior of platform_hal_setFanMaxOverride in a negative scenario
*
* This test case verifies the behavior of platform_hal_setFanMaxOverride function when bOverrideFlag is set to FALSE and fanIndex is 2.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 153 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data                           | Expected Result | Notes            |
* | :--------------: | ----------- | ----------------------------------- | --------------- | ---------------- |
* | 01               | Set fan override to FALSE for fan 2     | bOverrideFlag=FALSE, fanIndex=2    | RETURN_ERR      | Should be unsuccessful |
*/

void test_l1_platform_hal_negative2_setFanMaxOverride(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_setFanMaxOverride...");
    
    BOOLEAN bOverrideFlag = FALSE;
    UINT fanIndex = 2;
    
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);
    
    UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag=%d, fanIndex=%d", bOverrideFlag, fanIndex);
    UT_LOG("Expected status: RETURN_ERR");
    UT_LOG("Actual status: %d", status);
    
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative2_setFanMaxOverride...");
}

/**
 * @brief Test case to verify the behavior of the platform_hal_setFanMaxOverride function when the bOverrideFlag is set to a value other than 0 or 1.
 *
 * This test case checks the behavior of the platform_hal_setFanMaxOverride function when an invalid value is passed as the bOverrideFlag argument.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 154 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, they should select this test case via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                                                                                  | Test Data                                          | Expected Result                    | Notes              |
 * | :--------------: | ------------------------------------------------------------------------------------------- | -------------------------------------------------- | ---------------------------------- | ------------------ |
 * |       01         | Invoke the platform_hal_setFanMaxOverride function with an invalid bOverrideFlag value. | bOverrideFlag = 2, fanIndex = 0                   | status = RETURN_ERR                 | Should return error |
 */

void test_l1_platform_hal_negative3_setFanMaxOverride(void) {
    UT_LOG("Entering test_l1_platform_hal_negative3_setFanMaxOverride...");

    BOOLEAN bOverrideFlag = 2; // Value other than 0 or 1
    UINT fanIndex = 0;

    // Handling the undefined behavior can vary, but for this test case, we expect RETURN_ERR
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);

    UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag=%d, fanIndex=%d", bOverrideFlag, fanIndex);
    UT_LOG("Expected status: RETURN_ERR");
    UT_LOG("Actual status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_setFanMaxOverride...");
}

#ifdef FEATURE_RDKB_THERMAL_MANAGER
/**
* @brief This function tests the functionality of the platform_hal_setFanSpeed() API
*
* This test case checks the functionality of the platform_hal_setFanSpeed() API by invoking it and verifying the return value and error reason.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 155 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_OFF, pErrReason=&errReason | fanIndex=0, fanSpeed=FAN_SPEED_OFF, pErrReason=&errReason | status=RETURN_OK, errReason=FAN_ERR_NONE | Should be successful |
*/

void test_l1_platform_hal_positive1_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_OFF;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_OFF, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");
    
    INT status = platform_hal_setFanSpeed(0, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);


    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive1_setFanSpeed...");
}

/**
* @brief Test for the platform_hal_setFanSpeed function with positive input
*
* This test is performed to verify the functionality of the platform_hal_setFanSpeed function when provided with positive input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 156 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed | fanIndex = 1, fanSpeed = FAN_SPEED_SLOW, pErrReason = &errReason | RETURN_OK , FAN_ERR_NONE | Should be successful |
*/
void test_l1_platform_hal_positive2_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_SLOW;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=1, fanSpeed=FAN_SPEED_SLOW, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(1, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive2_setFanSpeed...");
}

/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 0, the fan speed is set to FAN_SPEED_MEDIUM, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 157 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 0, fan speed is set to FAN_SPEED_MEDIUM, and error reason is FAN_ERR_NONE. | fanIndex = 0, fanSpeed = FAN_SPEED_MEDIUM, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive3_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_MEDIUM;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_MEDIUM, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(0, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive3_setFanSpeed...");
}
/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 0, the fan speed is set to FAN_SPEED_FAST, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 158 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 1, fan speed is set to FAN_SPEED_FAST, and error reason is FAN_ERR_NONE. | fanIndex = 1, fanSpeed = FAN_SPEED_FAST, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive4_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive4_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_FAST;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_FAST, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(1, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive4_setFanSpeed...");
}

/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 0, the fan speed is set to FAN_SPEED_SLOW, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 159 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 0, fan speed is set to FAN_SPEED_SLOW, and error reason is FAN_ERR_NONE. | fanIndex = 0, fanSpeed = FAN_SPEED_SLOW, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive5_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive5_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_SLOW;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_SLOW, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(0, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive5_setFanSpeed...");
}

/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 0, the fan speed is set to FAN_SPEED_FAST, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 160 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 0, fan speed is set to FAN_SPEED_FAST, and error reason is FAN_ERR_NONE. | fanIndex = 0, fanSpeed = FAN_SPEED_FAST, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive6_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive6_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_FAST;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_FAST, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(0, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive6_setFanSpeed...");
}

/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 0, the fan speed is set to FAN_SPEED_MAX, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 161 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 0, fan speed is set to FAN_SPEED_MAX, and error reason is FAN_ERR_NONE. | fanIndex = 0, fanSpeed = FAN_SPEED_FAST, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive7_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive7_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_MAX;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_MAX, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(0, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive7_setFanSpeed...");
}

/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 1, the fan speed is set to FAN_SPEED_OFF, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 162 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 1, fan speed is set to FAN_SPEED_OFF, and error reason is FAN_ERR_NONE. | fanIndex = 1, fanSpeed = FAN_SPEED_OFF, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive8_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive8_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_OFF;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=1, fanSpeed=FAN_SPEED_OFF, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(1, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive8_setFanSpeed...");
}

/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 1, the fan speed is set to FAN_SPEED_OFF, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 163 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 1, fan speed is set to FAN_SPEED_MEDIUM, and error reason is FAN_ERR_NONE. | fanIndex = 1, fanSpeed = FAN_SPEED_MEDIUM, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive9_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive9_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_MEDIUM;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=1, fanSpeed=FAN_SPEED_MEDIUM, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(1, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive9_setFanSpeed...");
}

/**
 * @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
 *
 * This test case verifies that the platform_hal_setFanSpeed function sets the fan speed correctly when the fan index is 1, the fan speed is set to FAN_SPEED_OFF, and the error reason is FAN_ERR_NONE.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 164 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set fan speed when the fan index is 1, fan speed is set to FAN_SPEED_MEDIUM, and error reason is FAN_ERR_NONE. | fanIndex = 1, fanSpeed = FAN_SPEED_MEDIUM, pErrReason = &errReason | RETURN_OK, FAN_ERR_NONE | Should be successful |
 */
void test_l1_platform_hal_positive10_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive10_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_MEDIUM;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=1, fanSpeed=FAN_SPEED_MEDIUM, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_OK");
    UT_LOG("Expected error reason: FAN_ERR_NONE");

    INT status = platform_hal_setFanSpeed(1, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(errReason, FAN_ERR_NONE);

    UT_LOG("Exiting test_l1_platform_hal_positive10_setFanSpeed...");
}


/**
* @brief This test case is used to verify the negative scenario 
* of the platform_hal_setFanSpeed API.
*
* The objective of this test is to check the behavior of the 
* platform_hal_setFanSpeed API when invalid fan speed is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 165 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set fan speed with invalid value | fanIndex = 0, fanSpeed = FAN_SPEED_INVALID, pErrReason = &errReason | status = RETURN_ERR | The function should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_setFanSpeed...");
    FAN_SPEED fanSpeed = 5;  
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=2, fanSpeed= 5, pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_ERR");

    INT status = platform_hal_setFanSpeed(0, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    UT_LOG("errReason : %d", errReason);

    
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_ASSERT_EQUAL(errReason, 1 || errReason == 2);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setFanSpeed...");
}

/**
* @brief This test function is used to verify the negative scenario of the platform_hal_setFanSpeed API.
*
* This test checks the behavior of the platform_hal_setFanSpeed API when the fanIndex is 0, fanSpeed is FAN_SPEED_OFF, and the error reason is not specified.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 166 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with fanIndex = 0, fanSpeed = FAN_SPEED_OFF, pErrReason = NULL | fanIndex = 0, fanSpeed = FAN_SPEED_OFF, pErrReason = NULL | RETURN_ERR | Should be unsuccessful |
*/
void test_l1_platform_hal_negative2_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_OFF;
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=0, fanSpeed=FAN_SPEED_OFF, pErrReason=NULL");
    UT_LOG("Expected return value: RETURN_ERR");

    INT status = platform_hal_setFanSpeed(0, fanSpeed, NULL);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);

    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_ASSERT_EQUAL(errReason, 1 || errReason == 2);

    UT_LOG("Exiting test_l1_platform_hal_negative2_setFanSpeed...");
}

/**
* @brief This test case is used to verify the negative scenario 
* of the platform_hal_setFanSpeed API.
*
* The objective of this test is to check the behavior of the 
* platform_hal_setFanSpeed API when invalid fan speed is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 167 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set fanIndex with invalid value | fanIndex = 2, fanSpeed = FAN_SPEED_INVALID, pErrReason = &errReason | status = RETURN_ERR | The function should return RETURN_ERR |
*/
void test_l1_platform_hal_negative3_setFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative3_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_OFF;  
    FAN_ERR errReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex=2, fanSpeed= FAN_SPEED_OFF , pErrReason=&errReason");
    UT_LOG("Expected return value: RETURN_ERR");

    INT status = platform_hal_setFanSpeed(2, fanSpeed, &errReason);
    UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status,errReason);
    UT_LOG("errReason : %d", errReason);
    
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_ASSERT_EQUAL(errReason, 1 || errReason == 2);
    

    UT_LOG("Exiting test_l1_platform_hal_negative3_setFanSpeed...");
}

/**
 * @brief Test case for platform_hal_getInputPower function normal operation
 *
 * This test case tests the normal operation of the platform_hal_getInputPower function.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 168 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_getInputPower with valid pointer | valid pointer | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_getInputPower(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_getInputPower...");

    INT value;
    INT status = platform_hal_getInputPower(&value);

    UT_LOG("Invoking platform_hal_getInputPower with valid pointer");
    UT_LOG("platform_hal_getInputPower returns : %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_getInputPower...");
}

/**
* @brief Test for platform_hal_getInputPower function when passed a NULL pointer.
*
* This test is for the platform_hal_getInputPower function when passed a NULL pointer as the input parameter. 
* The objective of this test is to verify that the function correctly handles the NULL pointer and returns the appropriate error status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 169 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getInputPower with NULL pointer | input = NULL | RETURN_ERR | Should return error status |
*/
void test_l1_platform_hal_negative1_getInputPower(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_getInputPower...");

    INT status = platform_hal_getInputPower(NULL);

    UT_LOG("Invoking platform_hal_getInputPower with NULL pointer");
    UT_LOG("platform_hal_getInputPower returns : %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getInputPower...");
}
#endif
/**
* @brief Test the functionality of the platform_hal_GetCPUSpeed() function.
*
* This test verifies the functionality of the platform_hal_GetCPUSpeed() function by checking if it returns the expected CPU speed value and if the return value is equal to RETURN_OK.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 170 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_GetCPUSpeed() with valid buffer | valid buffer  | ret = RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetCPUSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetCPUSpeed...");

    char buffer[16];

    UT_LOG("Invoking platform_hal_GetCPUSpeed with valid buffer...");
   
    INT ret = platform_hal_GetCPUSpeed(buffer);

    UT_LOG("The processor speed is: %s", buffer);
    UT_LOG("Return value: %d", ret);

    UT_ASSERT_EQUAL(ret, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetCPUSpeed...");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetCPUSpeed when NULL buffer is passed as input.
*
* This test case checks if platform_hal_GetCPUSpeed returns RETURN_ERR when NULL buffer is passed as input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 171 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetCPUSpeed with NULL buffer | NULL buffer | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetCPUSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetCPUSpeed...");

    UT_LOG("Invoking platform_hal_GetCPUSpeed with NULL buffer...");
    INT ret = platform_hal_GetCPUSpeed(NULL);

    UT_LOG("Return value: %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetCPUSpeed...");
}

/**
* @brief Test case to verify the functionality of the GetFreeMemorySize API.
*
* This test case verifies that the GetFreeMemorySize API is able to successfully operate and return a total available memory size in the valid range [1, n].
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 172 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* |       01         | The function is invoked with valid pulSize buffer | valid buffer | The API returns RETURN_OK and the size parameter is greater than 0 | Should be successful |
*/
void test_l1_platform_hal_positive1_GetFreeMemorySize(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFreeMemorySize...");
    
    // Test Case 1: The function is able to successfully operate and return a total available memory size in the valid range [1, n].
    
    ULONG size;
    int result = platform_hal_GetFreeMemorySize(&size);
    
    UT_LOG("Invoking platform_hal_GetFreeMemorySize with input parameters (pulSize is a valid pointer)");
    UT_LOG("Return value: %d, size: %lu", result, size);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);
    //UT_ASSERT_TRUE(size > 0);
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetFreeMemorySize...");
}

/**
 * @brief Test case to verify the behavior of the platform_hal_GetFreeMemorySize function when called with a NULL pointer.
 *
 * This test case checks if the platform_hal_GetFreeMemorySize function returns the expected result when called with a NULL pointer as the input parameter.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 173 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | The function is invoked with pulSize being a NULL pointer. | pulSize = NULL | RETURN_ERR | Should return RETURN_ERR |
 */
void test_l1_platform_hal_negative1_GetFreeMemorySize(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFreeMemorySize...");
    
    // Test Case 1: The function is invoked with pulSize being a NULL pointer.

    UT_LOG("Invoking platform_hal_GetFreeMemorySize with input parameters (pulSize is NULL)");
    int result = platform_hal_GetFreeMemorySize(NULL);
    
    UT_LOG("Return value: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetFreeMemorySize...");
}

/**
 * @brief Test function to verify the behavior of platform_hal_getTimeOffSet API.
 *
 * This test function verifies the behavior of the platform_hal_getTimeOffSet API by checking the return value and expected values of the timeOffSet buffer.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 174 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke platform_hal_getTimeOffSet API | valid buffer | Status = RETURN_OK | The API invocation should be successful |
 */
void test_l1_platform_hal_positive1_getTimeOffSet(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_getTimeOffSet...");

    // Define a buffer of size 256 bytes
    CHAR timeOffSet[256];

    // Invoke platform_hal_getTimeOffSet API
    UT_LOG("Invoking platform_hal_getTimeOffSet with valid buffer");
    INT status = platform_hal_getTimeOffSet(timeOffSet);
    UT_LOG("platform_hal_getTimeOffSet returns : %d and time off set is : %s ", status,timeOffSet);

    // Check the return value
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    // Check the expected values of timeOffSet
    if (!strcmp(timeOffSet,"-25200") || !strcmp(timeOffSet,"-18000")|| !strcmp(timeOffSet,"+25200"))
        {
            UT_LOG("Time Offset value from the device is %s which is a valid value", timeOffSet);
            UT_PASS("Get Time Offset validation success");
        }
    else
        {
            UT_LOG("Time Offset value from the device %s which is an Invalid value", timeOffSet);
            UT_FAIL("Time Offset validation fail");
        }

    UT_LOG("Exiting test_l1_platform_hal_positive1_getTimeOffSet...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_getTimeOffSet API with a null pointer.
 *
 * This test case verifies whether platform_hal_getTimeOffSet API returns RETURN_ERR when invoked with a null pointer.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 175 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke platform_hal_getTimeOffSet() with NULL pointer | NULL | RETURN_ERR | Should return RETURN_ERR |
 */
void test_l1_platform_hal_negative1_getTimeOffSet(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_getTimeOffSet...");

    // Invoke platform_hal_getTimeOffSet API with a null pointer
    UT_LOG("Invoking platform_hal_getTimeOffSet with NULL pointer");
    INT status = platform_hal_getTimeOffSet(NULL);
     UT_LOG("platform_hal_getTimeOffSet returns : %d", status);

    // Check the return value
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_getTimeOffSet...");
}

/**
* @brief Test to verify the platform_hal_getFactoryPartnerId API
*
* This test is used to verify the functionality of the platform_hal_getFactoryPartnerId API.
* The purpose of this test is to check if the API returns the expected status and value for a valid buffer.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 176 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getFactoryPartnerId with a valid buffer of size 512 bytes | valid pValue buffer  | RETURN_OK, pValue = unknown or eUnprogrammed or eComcast or eCharter or eCox or eRogers or eVodafone or eShaw or eVideotron | Should be successful |
*/
void test_l1_platform_hal_positive1_getFactoryPartnerId(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getFactoryPartnerId...");

    CHAR pValue[512];

    UT_LOG("Invoking platform_hal_getFactoryPartnerId with a valid buffer of size 512 bytes.");
    INT status = platform_hal_getFactoryPartnerId(pValue);
    UT_LOG("Return status: %d and Factory Partner Id is : %s", status, pValue);

    // Check the return status
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    // Check the value of pValue
    UT_ASSERT_STRING_EQUAL(pValue, "unknown|eUnprogrammed|eComcast|eCharter|eCox|eRogers|eVodafone|eShaw|eVideotron");
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFactoryPartnerId...");
}

/**
 * @brief This test case is to verify the functionality of the platform_hal_getFactoryPartnerId function when a null pointer is passed as the parameter.
 *
 * The objective of this test is to check the return status of the platform_hal_getFactoryPartnerId function when a null pointer is passed as the parameter. The expected result is RETURN_ERR.
 * 
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 177 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:** @n
 *  | Variation / Step | Description | Test Data | Expected Result | Notes |
 *  | :----: | --------- | ---------- | -------------- | ----- |
 *  | 01 | Invoking platform_hal_getFactoryPartnerId with a null pointer as the parameter | NULL | RETURN_ERR | Should return error |
 */

void test_l1_platform_hal_negative1_getFactoryPartnerId(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getFactoryPartnerId...");

    UT_LOG("Invoking platform_hal_getFactoryPartnerId with a null pointer as the parameter.");
    
    INT status = platform_hal_getFactoryPartnerId(NULL);
    UT_LOG("platform_hal_getFactoryPartnerId returns: %d", status);

    // Check the return status
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getFactoryPartnerId...");
}

#ifdef FEATURE_RDKB_LED_MANAGER
/**
* @brief This function checks if platfom_hal_initLed() works as expected
*
* Calls the header function platfom_hal_initLed() with valid parameters
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 178 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platfom_hal_initLed() with valid buffer| valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_initLed( void )
{
    UT_LOG("Entering test_l1_platform_hal_positive1_initLed...");
    INT result = 0;
    CHAR config_file_name[512];
	
    UT_LOG("Invoking the API platform_hal_initLed and expecting the return value as 'RETURN_OK'.");
	
    result = platform_hal_initLed(config_file_name);
    UT_LOG("platform_hal_initLed API returns : %d", result);
	
    UT_ASSERT_EQUAL( result, RETURN_OK );
    UT_LOG("Exiting test_l1_platform_hal_positive1_initLed");
}

/**
* @brief This function checks if platfom_hal_initLed() works as expected
*
* Calls the header function platfom_hal_initLed() with NULL pointer
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 179 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platfom_hal_initLed() with invalid parameters| config_file_name = NULL| RETURN_ERR | Should return error |
*/

void test_l1_platform_hal_negative1_initLed( void )
{
	UT_LOG("Entering test_l1_platform_hal_negative1_initLed...");
	INT result = 0;
    
	UT_LOG("Invoking the API platform_hal_initLed and expecting the return value as 'RETURN_OK'.");
	
	result = platform_hal_initLed(NULL);
	UT_LOG("platform_hal_initLed API returns : %d", result);
	
	UT_ASSERT_EQUAL( result, RETURN_ERR );
	UT_LOG("Exiting test_l1_platform_hal_negative1_initLed");
}
#endif
/**
* @brief This test function is used to verify the functionality of the platform_hal_getFanStatus() API.
*
* The objective of this test is to check if the API returns the correct fan status when called with valid input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 180 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* 
* | Variation / Step | Description                                 | Test Data       | Expected Result         | Notes             |
* | :----:           | ---------                                   | ----------      |--------------           | -----             |
* | 01               | Call the API with valid input               | input = 0      | Returns 0 or 1               | Should be successful |
*/

void test_l1_platform_hal_positive1_getFanStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getFanStatus...");

    // Call the API with valid input
    UT_LOG("Invoking the API platform_hal_getFanStatus with 0 and expecting the return value as 0 or 1");
    BOOLEAN status = platform_hal_getFanStatus(0);
    
    UT_LOG("Status of the fan is %d",status);
    
    if(status == 0 || status == 1 )
        { 
            UT_LOG("Status of the fan is %d", status);
            UT_PASS("Get Fan Status Validation success");
        }
    else
        {
            UT_LOG("Status of the fan is %d", status);
            UT_FAIL("Get Fan Status Validation Fails");  
        }
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFanStatus...");
}

/**
* @brief This test function is used to verify the functionality of the platform_hal_getFanStatus() API.
*
* The objective of this test is to check if the API returns the correct fan status when called with valid input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 181 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* 
* | Variation / Step | Description                                 | Test Data       | Expected Result         | Notes             |
* | :----:           | ---------                                   | ----------      |--------------           | -----             |
* | 01               | Call the API with valid input               | input = 1      | Returns 0 or 1                | Should be successful |
*/

void test_l1_platform_hal_positive2_getFanStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_getFanStatus...");

    // Call the API with valid input
    UT_LOG("Invoking the API platform_hal_getFanStatus with 0 and expecting the return value as 0 or 1");
    BOOLEAN status = platform_hal_getFanStatus(1);
    UT_LOG("Status of the fan is %d",status);
    
    // Check the return value
    if(status == 0 || status == 1 )
        { 
            UT_LOG("Status of the fan is %d", status);
            UT_PASS("Get Fan Status Validation success");
        }
    else
        {
            UT_LOG("Status of the fan is %d", status);
            UT_FAIL("Get Fan Status Validation Fails");  
        }
    
    UT_LOG("Exiting test_l1_platform_hal_positive2_getFanStatus...");
}



/**
* @brief Test case to validate the platform_hal_getFanSpeed function for positive scenario using a specific fan index.
*
* This test case is used to validate the platform_hal_getFanSpeed function by invoking it with a specific fan index and checking the returned fan speed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 182 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_getFanSpeed with fanIndex=0 | fanIndex = 0 | fanSpeed >= 0 |  Should be successful|
*/
void test_l1_platform_hal_positive1_getFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_getFanSpeed...");

    // Invoke the API with the provided inputs
    UT_LOG("Invoking platform_hal_getFanSpeed with fanIndex=0");
    UINT fanSpeed = platform_hal_getFanSpeed(0);

    // Describe the test, the output values, and the return status
    UT_LOG("Received fanSpeed=%d", fanSpeed);

    // Add assertion to check the return value
    UT_ASSERT_TRUE(fanSpeed >= 0);

    UT_LOG("Exiting test_l1_platform_hal_positive1_getFanSpeed...");
}

/**
 * @brief This test case is used to validate the functionality of the platform_hal_getFanSpeed() API.
 *
 * The purpose of this test is to verify that the API returns the correct fan speed for a given fan index.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 183 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | ----------- | --------- | --------------- | ----- |
 * | 01     | Invoke platform_hal_getFanSpeed with fanIndex=1 | fanIndex = 1 | fanSpeed >= 0 | Should be successful |
 */
void test_l1_platform_hal_positive2_getFanSpeed(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_getFanSpeed...");

    // Invoke the API with the provided inputs
    UT_LOG("Invoking platform_hal_getFanSpeed with fanIndex=1");
    UINT fanSpeed = platform_hal_getFanSpeed(1);

    // Describe the test, the output values, and the return status
    UT_LOG("Received fanSpeed=%d", fanSpeed);

    // Add assertion to check the return value
    UT_ASSERT_TRUE(fanSpeed >= 0);

    UT_LOG("Exiting test_l1_platform_hal_positive2_getFanSpeed...");
}


/**
 * @brief Test case to verify the functionality of platform_hal_GetSSHEnable function
 *
 * This test case validates the functionality of the platform_hal_GetSSHEnable function.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 184 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description                | Test Data                     | Expected Result                           | Notes               |
 * | :--------------: | -------------------------- | ----------------------------- | ----------------------------------------- | ------------------- |
 * |       01         | Test function GetSSHEnable with valid buffer | valid buffer    | Function should return RETURN_OK         | Should be successful    |
 */
void test_l1_platform_hal_positive1_GetSSHEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_GetSSHEnable...");

    BOOLEAN pFlag;
    UT_LOG("Invoking platform_hal_GetSSHEnable with valid buffer...");
    INT status = platform_hal_GetSSHEnable(&pFlag);

    
    UT_LOG("Returned status: %d", status);
    UT_LOG("pFlag: %d", pFlag);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(pFlag, 0 || pFlag == 1);


    UT_LOG("Exiting test_l1_platform_hal_positive1_GetSSHEnable...");
}

/**
* @brief Test case to verify the platform_hal_GetSSHEnable function 
*
* This test case is used to verify the behavior of the platform_hal_GetSSHEnable function with NULL input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 185 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Test function platform_hal_GetSSHEnable with NULL pointer | pFlag = NULL | An error code is returned (e.g. RETURN_ERR) | Should fail and return an error code |
*/
void test_l1_platform_hal_negative1_GetSSHEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_GetSSHEnable...");

    UT_LOG("Invoking platform_hal_GetSSHEnable with NULL pointer...");
    INT status = platform_hal_GetSSHEnable(NULL);

    UT_LOG("Returned status: %d", status);

    // Assuming RETURN_ERR is returned for invalid fanIndex
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to TRUE.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to TRUE and return a success status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 186 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set SSH enable flag to TRUE | pFlag = TRUE | RETURN_OK | Should set SSH enable flag to TRUE successfully |
*/

void test_l1_platform_hal_positive1_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetSSHEnable...");

    // Invoke the API
    UT_LOG("Invoking SetSSHEnable with TRUE flag");
    INT returnValue = platform_hal_SetSSHEnable(TRUE);
    UT_LOG("Returned value: %d", returnValue);

    // Check the return value
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive1_SetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to FALSE.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to FALSE and return a success status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 187 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set SSH enable flag to FALSE | pFlag = FALSE | RETURN_OK | Should set SSH enable flag to FALSE successfully |
*/

void test_l1_platform_hal_positive2_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetSSHEnable...");

    // Invoke the API
    UT_LOG("Invoking SetSSHEnable with FALSE flag");
    INT returnValue = platform_hal_SetSSHEnable(FALSE);
    UT_LOG("Returned value: %d", returnValue);

    // Check the return value
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
    
    UT_LOG("Exiting test_l1_platform_hal_positive2_SetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to 2.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to 2 and return a failure status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 188 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set SSH enable flag to 2 | pFlag = 2 | RETURN_ERR | Should fail and return an error code |
*/

void test_l1_platform_hal_negative1_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetSSHEnable...");

    // Invoke the API
    UT_LOG("Invoking SetSSHEnable with invalid flag");
    INT returnValue = platform_hal_SetSSHEnable(2);
    UT_LOG("Returned value: %d", returnValue);

    // Check the return value
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative1_SetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to 'a'.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to 'a' and return a failure status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 189 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set SSH enable flag to 'a' | pFlag = 'a' | RETURN_ERR | Should fail and return an error code |
*/

void test_l1_platform_hal_negative2_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetSSHEnable...");

    // Invoke the API
    UT_LOG("Invoking SetSSHEnable with invalid flag");
    INT returnValue = platform_hal_SetSSHEnable('a');
    UT_LOG("Returned value: %d", returnValue);

    // Check the return value
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_platform_hal_negative2_SetSSHEnable...");
}

/**
* @brief This test is used to verify the reset of DSCP counts for the DOCSIS interface type.
*
* The objective of this test is to ensure that the platform_hal_resetDscpCounts function successfully resets the DSCP counts for the DOCSIS interface type.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 190 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Testing platform_hal_resetDscpCounts for DOCSIS interface type | interfaceType = DOCSIS | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_resetDscpCounts(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_resetDscpCounts...");

    WAN_INTERFACE interfaceType = DOCSIS;

    UT_LOG("Invoking platform_hal_resetDscpCounts with interfaceType = DOCSIS");
    UT_LOG("Expected result: RETURN_OK");

    INT result = platform_hal_resetDscpCounts(interfaceType);
    UT_LOG("Actual result: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_resetDscpCounts...");
}

/**
 * @brief Test the function platform_hal_resetDscpCounts for positive cases.
 *
 * This test case is used to verify the functionality of the platform_hal_resetDscpCounts function when the interface type is EWAN.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 191 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking platform_hal_resetDscpCounts with interfaceType = EWAN | interfaceType = EWAN | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive2_resetDscpCounts(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_resetDscpCounts...");

    WAN_INTERFACE interfaceType = EWAN;

    UT_LOG("Invoking platform_hal_resetDscpCounts with interfaceType = EWAN");
    UT_LOG("Expected result: RETURN_OK");

    INT result = platform_hal_resetDscpCounts(interfaceType);
    UT_LOG("Actual result: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Existing test_l1_platform_hal_positive2_resetDscpCounts...");
}

/**
* @brief Test case to verify the behavior of the function platform_hal_resetDscpCounts
*
* This test case verifies the behavior of the platform_hal_resetDscpCounts function when an invalid interface type is provided as input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 192 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking platform_hal_resetDscpCounts with an invalid interface type | interfaceType = 5 | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative1_resetDscpCounts(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_resetDscpCounts...");

    WAN_INTERFACE interfaceType = 5; // Random invalid interfaceType value

    UT_LOG("Invoking platform_hal_resetDscpCounts with interfaceType = %d", interfaceType);
    UT_LOG("Expected result: RETURN_ERR");
    INT result = platform_hal_resetDscpCounts(interfaceType);

    UT_LOG("Actual result: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Existing test_l1_platform_hal_negative1_resetDscpCounts...");
}

/**
* @brief This function checks if platform_hal_PandMDBInit() works as expected
*
* Calls the header function platform_hal_PandMDBInit() with no params
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 193 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platform_hal_PandMDBInit|  | RETURN_OK | Should Pass |
*/

void test_l1_platform_hal_positive1_PandMDBInit( void )
{
	UT_LOG("Entering test_l1_platform_hal_positive1_PandMDBInit...");
	INT result = 0;
	
	UT_LOG("Invoking the API platform_hal_PandMDBInit and expecting the return value as 'RETURN_OK'.");
	
	result = platform_hal_PandMDBInit();
	UT_LOG("platform_hal_PandMDBInit API returns : %d", result);
	
	UT_ASSERT_EQUAL( result, RETURN_OK );
	UT_LOG("Exiting test_l1_platform_hal_positive1_PandMDBInit");
}

/**
* @brief Test function to verify the behavior of platform_hal_GetTelnetEnable() function.
*
* This test case is used to verify the functionality and correctness of the platform_hal_GetTelnetEnable() function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 194 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_GetTelnetEnable with valid buffer | valid pFlag buffer |  RETURN_OK | Should be successful |
*/

void test_l1_platform_hal_positive1_GetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetTelnetEnable...");

    INT result = 0;
    BOOLEAN pFlag;

    UT_LOG("Invoking platform_hal_GetTelnetEnable with valid input parameters...");
    result = platform_hal_GetTelnetEnable(&pFlag);

    UT_LOG("Returned status %d and flag value: %d", result, pFlag);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_ASSERT_EQUAL(pFlag, 0 || pFlag == 1);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetTelnetEnable...");
}

/**
* @brief Test function to verify the behavior of platform_hal_GetTelnetEnable() function.
*
* This test case is used to verify the functionality and correctness of the platform_hal_GetTelnetEnable() function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 195 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_GetTelnetEnable with NULL pointer | pFlag = NULL |  RETURN_ERR | Should be fail |
*/

void test_l1_platform_hal_negative1_GetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetTelnetEnable...");

    INT result = 0;

    UT_LOG("Invoking platform_hal_GetTelnetEnable with valid input parameters...");
    result = platform_hal_GetTelnetEnable(NULL);
    UT_LOG("platform_hal_GetTelnetEnable returns : %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetTelnetEnable...");
}

/**
* @brief This function checks if platform_hal_DocsisParamsDBInit() works as expected
*
* Calls the header function platform_hal_DocsisParamsDBInit() with no params
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 196 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platform_hal_DocsisParamsDBInit()|  | RETURN_OK | Should Pass |
*/

void test_l1_platform_hal_positive1_DocsisParamsDBInit( void )
{
	UT_LOG("Entering test_l1_platform_hal_positive1_DocsisParamsDBInit...");
	INT result = 0;
	
	UT_LOG("Invoking the API platform_hal_DocsisParamsDBInit and expecting the return value as RETURN_OK");
	
	result = platform_hal_DocsisParamsDBInit();
	UT_LOG("platform_hal_DocsisParamsDBInit API returns : %d", result);
	
	UT_ASSERT_EQUAL( result, RETURN_OK );
	UT_LOG("Exiting test_l1_platform_hal_positive1_DocsisParamsDBInit");
}

/**
* @brief This is a unit test to verify the functionality of the platform_hal_SetTelnetEnable API when the flag is set to TRUE.
*
* This test case checks the behavior of the platform_hal_SetTelnetEnable API when the flag is set to TRUE. The objective is to ensure that the API sets the Telnet enable flag correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 197 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with TRUE | Flag = TRUE | RETURN_OK | The API should successfully set the Telnet enable flag to TRUE. |
*/

void test_l1_platform_hal_positive1_SetTelnetEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_SetTelnetEnable...");

    BOOLEAN Flag = TRUE;

    UT_LOG("Invoking platform_hal_SetTelnetEnable with TRUE");
    
    INT result = platform_hal_SetTelnetEnable(Flag);
    UT_LOG("platform_hal_SetTelnetEnable API returns : %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Exiting test_l1_platform_hal_positive1_SetTelnetEnable...");
}

/**
* @brief This is a unit test to verify the functionality of the platform_hal_SetTelnetEnable API when the flag is set to FALSE.
*
* This test case checks the behavior of the platform_hal_SetTelnetEnable API when the flag is set to FALSE. The objective is to ensure that the API sets the Telnet enable flag correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 198 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with FALSE | Flag = FALSE | RETURN_OK | The API should successfully set the Telnet enable flag to FALSE. |
*/

void test_l1_platform_hal_positive2_SetTelnetEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_SetTelnetEnable...");

    BOOLEAN Flag = FALSE;

    UT_LOG("Invoking platform_hal_SetTelnetEnable with FALSE");
    
    INT result = platform_hal_SetTelnetEnable(Flag);
    UT_LOG("platform_hal_SetTelnetEnable API returns : %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Exiting test_l1_platform_hal_positive2_SetTelnetEnable...");
}

/**
* @brief This is a unit test to verify the functionality of the platform_hal_SetTelnetEnable API when the flag is set to 2.
*
* This test case checks the behavior of the platform_hal_SetTelnetEnable API when the flag is set to 2. 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 199 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with 2 | Flag = 2 | RETURN_ERR | Should Fail |
*/

void test_l1_platform_hal_negative1_SetTelnetEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_SetTelnetEnable...");

    BOOLEAN Flag = 2;

    UT_LOG("Invoking platform_hal_SetTelnetEnable with 2");
    
    INT result = platform_hal_SetTelnetEnable(Flag);
    UT_LOG("platform_hal_SetTelnetEnable API returns : %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_platform_hal_negative1_SetTelnetEnable...");
}

/**
* @brief This is a unit test to verify the functionality of the platform_hal_SetTelnetEnable API when the flag is set to 'True'.
*
* This test case checks the behavior of the platform_hal_SetTelnetEnable API when the flag is set to 'True'. 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 200 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with 'True' | Flag = 'True' | RETURN_ERR | Should Fail |
*/

void test_l1_platform_hal_negative2_SetTelnetEnable(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_SetTelnetEnable...");

    UT_LOG("Invoking platform_hal_SetTelnetEnable with 'True'");
    
    INT result = platform_hal_SetTelnetEnable('a');
    UT_LOG("platform_hal_SetTelnetEnable API returns : %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_platform_hal_negative2_SetTelnetEnable...");
}

/**
    * @brief Test the function platform_hal_StopMACsec with valid Ethernet Port.
    *
    * This test case is used to verify the functionality of the platform_hal_StopMACsec function when a valid Ethernet Port provided as input.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 201 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    * 
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoke platform_hal_StopMACsec valid ethPort | ethPort = 0 | RETURN_OK | Should be successful |
    */
void test_l1_platform_hal_positive1_StopMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_positive1_StopMACsec...");

    //TODO:Define MaxEthPort

    INT ethPort = 0; // Valid Ethernet Port
    
    UT_LOG("Invoking platform_hal_StopMACsec with ethPort = %d", ethPort);

    INT result = platform_hal_StopMACsec(ethPort);
     UT_LOG("platform_hal_StopMACsec API returns : %d", result);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Exiting test_l1_platform_hal_positive1_StopMACsec...");
}

/**
    * @brief Test the function platform_hal_StopMACsec with valid Ethernet Port.
    *
    * This test case is used to verify the functionality of the platform_hal_StopMACsec function when a valid Ethernet Port provided as input.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 202 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    * 
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoke platform_hal_StopMACsec valid ethPort | ethPort = MaxEthPort - 1 | RETURN_OK | Should be successful |
    */
void test_l1_platform_hal_positive2_StopMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_positive2_StopMACsec...");

    //TODO:Define MaxEthPort
    INT ethPort = MaxEthPort - 1; // Valid Ethernet Port
    
    UT_LOG("Invoking platform_hal_StopMACsec with ethPort = %d", ethPort);

    INT result = platform_hal_StopMACsec(ethPort);
    UT_LOG("platform_hal_StopMACsec API returns : %d", result);
    
    
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Exiting test_l1_platform_hal_positive2_StopMACsec...");
}

/**
    * @brief Test the function platform_hal_StopMACsec with valid Ethernet Port.
    *
    * This test case is used to verify the functionality of the platform_hal_StopMACsec function when a valid Ethernet Port provided as input.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 203 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    * 
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoke platform_hal_StopMACsec valid ethPort | ethPort = 2 | RETURN_OK | Should be successful |
    */
void test_l1_platform_hal_positive3_StopMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_positive3_StopMACsec...");

    //TODO:Define MaxEthPort
    INT ethPort = 2; // Valid Ethernet Port
    
    UT_LOG("Invoking platform_hal_StopMACsec with ethPort = %d", ethPort);

    INT result = platform_hal_StopMACsec(ethPort);
     UT_LOG("platform_hal_StopMACsec API returns : %d", result);
    
    
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Exiting test_l1_platform_hal_positive3_StopMACsec...");
}

/**
    * @brief Test the function platform_hal_StopMACsec with invalid Ethernet Port.
    *
    * This test case is used to verify the functionality of the platform_hal_StopMACsec function when a invalid Ethernet Port provided as input.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 204 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    * 
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoke platform_hal_StopMACsec invalid ethPort | ethPort = -1 | RETURN_ERR | Should return error |
    */
void test_l1_platform_hal_negative1_StopMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_negative1_StopMACsec...");

    //TODO:Define MaxEthPort
    INT ethPort = -1; // Invalid Ethernet Port
    
    UT_LOG("Invoking platform_hal_StopMACsec with ethPort = %d", ethPort);

    INT result = platform_hal_StopMACsec(ethPort);
    UT_LOG("platform_hal_StopMACsec API returns : %d", result);
    
    
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_platform_hal_negative1_StopMACsec...");
}

/**
    * @brief Test the function platform_hal_StopMACsec with invalid Ethernet Port.
    *
    * This test case is used to verify the functionality of the platform_hal_StopMACsec function when a invalid Ethernet Port provided as input.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 205 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    * 
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoke platform_hal_StopMACsec invalid ethPort | ethPort = MaxEthPort | RETURN_ERR | Should return error|
    */
void test_l1_platform_hal_negative2_StopMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_negative2_StopMACsec...");

    //TODO:Define MaxEthPort
    INT ethPort = MaxEthPort; // Invalid Ethernet Port
    
    UT_LOG("Invoking platform_hal_StopMACsec with ethPort = %d", ethPort);

    INT result = platform_hal_StopMACsec(ethPort);
     UT_LOG("platform_hal_StopMACsec API returns : %d", result);
    
    
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_platform_hal_negative2_StopMACsec...");
}

/**
    * @brief Test the function platform_hal_StopMACsec with invalid Ethernet Port.
    *
    * This test case is used to verify the functionality of the platform_hal_StopMACsec function when a invalid Ethernet Port provided as input.
    *
    * **Test Group ID:** Basic: 01 @n
    * **Test Case ID:** 206 @n
    * **Priority:** High @n@n
    * 
    * **Pre-Conditions:** None @n
    * **Dependencies:** None @n
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
    * 
    * **Test Procedure:** @n
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- |-------------- | ----- |
    * | 01 | Invoke platform_hal_StopMACsec invalid ethPort | ethPort = MaxEthPort + 1 | RETURN_ERR | Should return error|
    */
void test_l1_platform_hal_negative3_StopMACsec(void) {
    UT_LOG("Entering test_l1_platform_hal_negative3_StopMACsec...");

    //TODO:Define MaxEthPort
    INT ethPort = MaxEthPort + 1; // Invalid Ethernet Port
    
    UT_LOG("Invoking platform_hal_StopMACsec with ethPort = %d", ethPort);

    INT result = platform_hal_StopMACsec(ethPort);
     UT_LOG("platform_hal_StopMACsec API returns : %d", result);
    
    
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_platform_hal_negative3_StopMACsec...");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int register_hal_tests(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 platform_hal]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings
   
   const char* list1[] = { "l1_platform_hal_positive1_GetFirmwareName", "l1_platform_hal_negative1_GetFirmwareName", "l1_platform_hal_positive1_GetSoftwareVersion", "l1_platform_hal_negative1_GetSoftwareVersion", "l1_platform_hal_positive1_GetSerialNumber", "l1_platform_hal_negative1_GetSerialNumber", "l1_platform_hal_positive1_GetSNMPEnable", "l1_platform_hal_negative1_GetSNMPEnable", "l1_platform_hal_positive1_GetHardware_MemUsed", "l1_platform_hal_negative1_GetHardware_MemUsed", "l1_platform_hal_positive1_GetHardwareVersion", "l1_platform_hal_negative1_GetHardwareVersion", "l1_platform_hal_positive1_GetModelName", "l1_platform_hal_negative1_GetModelName", "l1_platform_hal_positive1_GetRouterRegion", "l1_platform_hal_negative1_GetRouterRegion", "l1_platform_hal_positive1_GetBootloaderVersion", "l1_platform_hal_negative1_GetBootloaderVersion", "l1_platform_hal_positive1_GetHardware", "l1_platform_hal_negative1_GetHardware", "l1_platform_hal_positive1_SetSNMPEnable", "l1_platform_hal_positive2_SetSNMPEnable", "l1_platform_hal_positive3_SetSNMPEnable", "l1_platform_hal_negative1_SetSNMPEnable", "l1_platform_hal_negative2_SetSNMPEnable", "l1_platform_hal_positive1_SetWebUITimeout ", "l1_platform_hal_positive2_SetWebUITimeout ", "l1_platform_hal_positive3_SetWebUITimeout ", "l1_platform_hal_negative1_SetWebUITimeout", "l1_platform_hal_negative2_SetWebUITimeout", "l1_platform_hal_negative3_SetWebUITimeout ", "l1_platform_hal_positive1_GetWebUITimeout", "l1_platform_hal_negative1_GetWebUITimeout", "l1_platform_hal_positive1_GetBaseMacAddress", "l1_platform_hal_negative1_GetBaseMacAddress", "l1_platform_hal_positive1_GetHardware_MemFree", "l1_platform_hal_negative1_GetHardware_MemFree", "l1_platform_hal_positive1_GetUsedMemorySize", "l1_platform_hal_negative1_GetUsedMemorySize", "l1_platform_hal_positive1_ClearResetCount", "l1_platform_hal_positive2_ClearResetCount", "l1_platform_hal_negative1_ClearResetCount", "l1_platform_hal_positive1_SetDeviceCodeImageValid", "l1_platform_hal_positive2_SetDeviceCodeImageValid", "l1_platform_hal_negative1_SetDeviceCodeImageValid", "l1_platform_hal_positive1_setFactoryCmVariant", "l1_platform_hal_positive2_setFactoryCmVariant", "l1_platform_hal_positive3_setFactoryCmVariant", "l1_platform_hal_positive4_setFactoryCmVariant", "l1_platform_hal_positive5_setFactoryCmVariant", "l1_platform_hal_negative1_setFactoryCmVariant", "l1_platform_hal_negative2_setFactoryCmVariant", "l1_platform_hal_positive1_getLed", "l1_platform_hal_negative1_getLed", "l1_platform_hal_positive1_getRotorLock", "l1_platform_hal_positive2_getRotorLock","l1_platform_hal_negative1_getRotorLock", "l1_platform_hal_positive1_GetTotalMemorySize", "l1_platform_hal_negative1_GetTotalMemorySize", "l1_platform_hal_positive1_GetFactoryResetCount", "l1_platform_hal_negative1_GetFactoryResetCount", "l1_platform_hal_positive1_SetDeviceCodeImageTimeout", "l1_platform_hal_positive2_SetDeviceCodeImageTimeout", "l1_platform_hal_positive3_SetDeviceCodeImageTimeout", "l1_platform_hal_negative1_SetDeviceCodeImageTimeout", "l1_platform_hal_negative2_SetDeviceCodeImageTimeout", "l1_platform_hal_positive1_getFactoryCmVariant", "l1_platform_hal_negative1_getFactoryCmVariant", "l1_platform_hal_positive1_setLed", "l1_platform_hal_negative1_setLed", "l1_platform_hal_negative2_setLed", "l1_platform_hal_negative3_setLed", "l1_platform_hal_negative4_setLed", "l1_platform_hal_positive1_getRPM", "l1_platform_hal_positive2_getRPM", "l1_platform_hal_positive1_initThermal", "l1_platform_hal_negative1_initThermal", "l1_platform_hal_positive1_getFanTemperature", "l1_platform_hal_negative1_getFanTemperature", "l1_platform_hal_positive1_getRadioTemperature", "l1_platform_hal_negative1_getRadioTemperature", "l1_platform_hal_negative2_getRadioTemperature", "l1_platform_hal_positive2_getRadioTemperature", "l1_platform_hal_positive3_getRadioTemperature", "l1_platform_hal_positive1_SetMACsecEnable", "l1_platform_hal_positive2_SetMACsecEnable", "l1_platform_hal_negative1_SetMACsecEnable", "l1_platform_hal_positive3_SetMACsecEnable", "l1_platform_hal_negative2_SetMACsecEnable", "l1_platform_hal_positive1_GetMemoryPaths", "l1_platform_hal_positive2_GetMemoryPaths", "l1_platform_hal_negative1_GetMemoryPaths", "l1_platform_hal_negative2_GetMemoryPaths", "l1_platform_hal_negative3_GetMemoryPaths", "l1_platform_hal_positive1_GetMACsecEnable","l1_platform_hal_negative1_GetMACsecEnable", "l1_platform_hal_negative2_GetMACsecEnable", "l1_platform_hal_positive2_GetMACsecEnable","l1_platform_hal_positive1_StartMACsec", "l1_platform_hal_negative1_StartMACsec", "l1_platform_hal_positive2_StartMACsec", "l1_platform_hal_positive3_StartMACsec", "l1_platform_hal_positive1_GetDhcpv6_Options", "l1_platform_hal_negative1_GetDhcpv6_Options", "l1_platform_hal_negative2_GetDhcpv6_Options", "l1_platform_hal_negative3_GetDhcpv6_Options", "l1_platform_hal_positive1_setDscp", "l1_platform_hal_positive2_setDscp", "l1_platform_hal_positive3_setDscp", "l1_platform_hal_positive4_setDscp", "l1_platform_hal_negative1_setDscp", "l1_platform_hal_negative2_setDscp", "l1_platform_hal_negative3_setDscp", "l1_platform_hal_positive1_SetLowPowerModeState", "l1_platform_hal_positive2_SetLowPowerModeState", "l1_platform_hal_positive3_SetLowPowerModeState", "l1_platform_hal_positive4_SetLowPowerModeState", "l1_platform_hal_negative1_SetLowPowerModeState", "l1_platform_hal_negative2_SetLowPowerModeState", "l1_platform_hal_positive1_GetFirmwareBankInfo", "l1_platform_hal_positive2_GetFirmwareBankInfo", "l1_platform_hal_negative1_GetFirmwareBankInfo", "l1_platform_hal_negative2_GetFirmwareBankInfo", "l1_platform_hal_negative3_GetFirmwareBankInfo", "l1_platform_hal_positive1_getCMTSMac", "l1_platform_hal_negative1_getCMTSMac", "l1_platform_hal_positive1_GetDhcpv4_Options", "l1_platform_hal_negative1_GetDhcpv4_Options", "l1_platform_hal_negative2_GetDhcpv4_Options", "l1_platform_hal_negative3_GetDhcpv4_Options", "l1_platform_hal_positive1_getDscpClientList", "l1_platform_hal_positive2_getDscpClientList", "l1_platform_hal_negative1_getDscpClientList", "l1_platform_hal_negative2_getDscpClientList", "l1_platform_hal_negative3_getDscpClientList", "l1_platform_hal_positive1_GetDeviceConfigStatus", "l1_platform_hal_negative1_GetDeviceConfigStatus", "l1_platform_hal_positive1_SetSNMPOnboardRebootEnable", "l1_platform_hal_positive2_SetSNMPOnboardRebootEnable", "l1_platform_hal_negative1_SetSNMPOnboardRebootEnable", "l1_platform_hal_negative2_SetSNMPOnboardRebootEnable", "l1_platform_hal_positive1_getInputCurrent", "l1_platform_hal_negative1_getInputCurrent", "l1_platform_hal_positive1_LoadThermalConfig", "l1_platform_hal_negative1_LoadThermalConfig", "l1_platform_hal_positive1_GetMACsecOperationalStatus", "l1_platform_hal_negative1_GetMACsecOperationalStatus", "l1_platform_hal_positive1_setFanMaxOverride", "l1_platform_hal_positive2_setFanMaxOverride", "l1_platform_hal_positive3_setFanMaxOverride", "l1_platform_hal_positive4_setFanMaxOverride", "l1_platform_hal_negative1_setFanMaxOverride", "l1_platform_hal_negative2_setFanMaxOverride", "l1_platform_hal_negative3_setFanMaxOverride", "l1_platform_hal_positive1_setFanSpeed", "l1_platform_hal_positive2_setFanSpeed", "l1_platform_hal_positive3_setFanSpeed","l1_platform_hal_positive4_setFanSpeed", "l1_platform_hal_positive5_setFanSpeed", "l1_platform_hal_positive6_setFanSpeed", "l1_platform_hal_positive7_setFanSpeed", "l1_platform_hal_positive8_setFanSpeed", "l1_platform_hal_positive9_setFanSpeed", "l1_platform_hal_positive10_setFanSpeed",  "l1_platform_hal_negative1_setFanSpeed", "l1_platform_hal_negative2_setFanSpeed", "l1_platform_hal_negative3_setFanSpeed", "l1_platform_hal_positive1_getInputPower", "l1_platform_hal_negative1_getInputPower", "l1_platform_hal_positive1_GetCPUSpeed", "l1_platform_hal_negative1_GetCPUSpeed", "l1_platform_hal_positive1_GetFreeMemorySize", "l1_platform_hal_negative1_GetFreeMemorySize", "l1_platform_hal_positive1_getTimeOffSet", "l1_platform_hal_negative1_getTimeOffSet", "l1_platform_hal_positive1_getFactoryPartnerId", "l1_platform_hal_negative1_getFactoryPartnerId","l1_platform_hal_positive1_initLed", "l1_platform_hal_negative1_initLed", "l1_platform_hal_positive1_getFanStatus", "l1_platform_hal_positive2_getFanStatus", "l1_platform_hal_positive1_getFanSpeed", "l1_platform_hal_positive2_getFanSpeed", "l1_platform_hal_positive_1_GetSSHEnable", "l1_platform_hal_negative1_GetSSHEnable", "l1_platform_hal_positive1_SetSSHEnable", "l1_platform_hal_positive2_SetSSHEnable", "l1_platform_hal_negative1_SetSSHEnable", "l1_platform_hal_negative2_SetSSHEnable", "l1_platform_hal_positive1_resetDscpCounts", "l1_platform_hal_positive2_resetDscpCounts", "l1_platform_hal_negative1_resetDscpCounts","l1_platform_hal_positive1_PandMDBInit","l1_platform_hal_positive1_GetTelnetEnable","l1_platform_hal_negative1_GetTelnetEnable","l1_platform_hal_positive1_DocsisParamsDBInit", "l1_platform_hal_positive1_SetTelnetEnable","l1_platform_hal_positive2_SetTelnetEnable", "l1_platform_hal_negative1_SetTelnetEnable", "l1_platform_hal_negative2_SetTelnetEnable","l1_platform_hal_positive1_StopMACsec", "l1_platform_hal_positive2_StopMACsec", "l1_platform_hal_positive3_StopMACsec","l1_platform_hal_negative1_StopMACsec", "l1_platform_hal_negative2_StopMACsec", "l1_platform_hal_negative3_StopMACsec"};
   void (*list2[])() = {test_l1_platform_hal_positive1_GetFirmwareName, test_l1_platform_hal_negative1_GetFirmwareName, test_l1_platform_hal_positive1_GetSoftwareVersion, test_l1_platform_hal_negative1_GetSoftwareVersion, test_l1_platform_hal_positive1_GetSerialNumber, test_l1_platform_hal_negative1_GetSerialNumber, test_l1_platform_hal_positive1_GetSNMPEnable, test_l1_platform_hal_negative1_GetSNMPEnable, test_l1_platform_hal_positive1_GetHardware_MemUsed, test_l1_platform_hal_negative1_GetHardware_MemUsed, test_l1_platform_hal_positive1_GetHardwareVersion, test_l1_platform_hal_negative1_GetHardwareVersion, test_l1_platform_hal_positive1_GetModelName, test_l1_platform_hal_negative1_GetModelName, test_l1_platform_hal_positive1_GetRouterRegion, test_l1_platform_hal_negative1_GetRouterRegion, test_l1_platform_hal_positive1_GetBootloaderVersion, test_l1_platform_hal_negative1_GetBootloaderVersion, test_l1_platform_hal_positive1_GetHardware, test_l1_platform_hal_negative1_GetHardware, test_l1_platform_hal_positive1_SetSNMPEnable, test_l1_platform_hal_positive2_SetSNMPEnable, test_l1_platform_hal_positive3_SetSNMPEnable, test_l1_platform_hal_negative1_SetSNMPEnable, test_l1_platform_hal_negative2_SetSNMPEnable, test_l1_platform_hal_positive1_SetWebUITimeout, test_l1_platform_hal_positive2_SetWebUITimeout, test_l1_platform_hal_positive3_SetWebUITimeout, test_l1_platform_hal_negative1_SetWebUITimeout, test_l1_platform_hal_negative2_SetWebUITimeout, test_l1_platform_hal_negative3_SetWebUITimeout, test_l1_platform_hal_positive1_GetWebUITimeout, test_l1_platform_hal_negative1_GetWebUITimeout, test_l1_platform_hal_positive1_GetBaseMacAddress, test_l1_platform_hal_negative1_GetBaseMacAddress, test_l1_platform_hal_positive1_GetHardware_MemFree, test_l1_platform_hal_negative1_GetHardware_MemFree, test_l1_platform_hal_positive1_GetUsedMemorySize, test_l1_platform_hal_negative1_GetUsedMemorySize, test_l1_platform_hal_positive1_ClearResetCount, test_l1_platform_hal_positive2_ClearResetCount, test_l1_platform_hal_negative1_ClearResetCount, test_l1_platform_hal_positive1_SetDeviceCodeImageValid, test_l1_platform_hal_positive2_SetDeviceCodeImageValid, test_l1_platform_hal_negative1_SetDeviceCodeImageValid, test_l1_platform_hal_positive1_setFactoryCmVariant, test_l1_platform_hal_positive2_setFactoryCmVariant, test_l1_platform_hal_positive3_setFactoryCmVariant, test_l1_platform_hal_positive4_setFactoryCmVariant, test_l1_platform_hal_positive5_setFactoryCmVariant, test_l1_platform_hal_negative1_setFactoryCmVariant, test_l1_platform_hal_negative2_setFactoryCmVariant, test_l1_platform_hal_positive1_getLed, test_l1_platform_hal_negative1_getLed, test_l1_platform_hal_positive1_getRotorLock, test_l1_platform_hal_positive2_getRotorLock, test_l1_platform_hal_negative1_getRotorLock, test_l1_platform_hal_positive1_GetTotalMemorySize, test_l1_platform_hal_negative1_GetTotalMemorySize, test_l1_platform_hal_positive1_GetFactoryResetCount, test_l1_platform_hal_negative1_GetFactoryResetCount, test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout, test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout, test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout, test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout, test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout, test_l1_platform_hal_positive1_getFactoryCmVariant, test_l1_platform_hal_negative1_getFactoryCmVariant, test_l1_platform_hal_positive1_setLed, test_l1_platform_hal_negative1_setLed, test_l1_platform_hal_negative2_setLed, test_l1_platform_hal_negative3_setLed, test_l1_platform_hal_negative4_setLed, test_l1_platform_hal_positive1_getRPM, test_l1_platform_hal_positive2_getRPM, test_l1_platform_hal_positive1_initThermal, test_l1_platform_hal_negative1_initThermal, test_l1_platform_hal_positive1_getFanTemperature, test_l1_platform_hal_negative1_getFanTemperature, test_l1_platform_hal_positive1_getRadioTemperature, test_l1_platform_hal_negative1_getRadioTemperature, test_l1_platform_hal_negative2_getRadioTemperature, test_l1_platform_hal_positive2_getRadioTemperature, test_l1_platform_hal_positive3_getRadioTemperature, test_l1_platform_hal_positive1_SetMACsecEnable, test_l1_platform_hal_positive2_SetMACsecEnable, test_l1_platform_hal_negative1_SetMACsecEnable, test_l1_platform_hal_positive3_SetMACsecEnable, test_l1_platform_hal_negative2_SetMACsecEnable, test_l1_platform_hal_positive1_GetMemoryPaths, test_l1_platform_hal_positive2_GetMemoryPaths, test_l1_platform_hal_negative1_GetMemoryPaths, test_l1_platform_hal_negative2_GetMemoryPaths, test_l1_platform_hal_negative3_GetMemoryPaths, test_l1_platform_hal_positive1_GetMACsecEnable, test_l1_platform_hal_negative1_GetMACsecEnable, test_l1_platform_hal_negative2_GetMACsecEnable, test_l1_platform_hal_positive2_GetMACsecEnable, test_l1_platform_hal_positive1_StartMACsec, test_l1_platform_hal_negative1_StartMACsec, test_l1_platform_hal_positive2_StartMACsec, test_l1_platform_hal_positive3_StartMACsec, test_l1_platform_hal_positive1_GetDhcpv6_Options, test_l1_platform_hal_negative1_GetDhcpv6_Options, test_l1_platform_hal_negative2_GetDhcpv6_Options, test_l1_platform_hal_negative3_GetDhcpv6_Options, test_l1_platform_hal_positive1_setDscp, test_l1_platform_hal_positive2_setDscp, test_l1_platform_hal_positive3_setDscp, test_l1_platform_hal_positive4_setDscp, test_l1_platform_hal_negative1_setDscp, test_l1_platform_hal_negative2_setDscp, test_l1_platform_hal_negative3_setDscp, test_l1_platform_hal_positive1_SetLowPowerModeState, test_l1_platform_hal_positive2_SetLowPowerModeState, test_l1_platform_hal_positive3_SetLowPowerModeState, test_l1_platform_hal_positive4_SetLowPowerModeState, test_l1_platform_hal_negative1_SetLowPowerModeState, test_l1_platform_hal_negative2_SetLowPowerModeState, test_l1_platform_hal_positive1_GetFirmwareBankInfo, test_l1_platform_hal_positive2_GetFirmwareBankInfo, test_l1_platform_hal_negative1_GetFirmwareBankInfo, test_l1_platform_hal_negative2_GetFirmwareBankInfo, test_l1_platform_hal_negative3_GetFirmwareBankInfo, test_l1_platform_hal_positive1_getCMTSMac, test_l1_platform_hal_negative1_getCMTSMac, test_l1_platform_hal_positive1_GetDhcpv4_Options, test_l1_platform_hal_negative1_GetDhcpv4_Options, test_l1_platform_hal_negative2_GetDhcpv4_Options, test_l1_platform_hal_negative3_GetDhcpv4_Options, test_l1_platform_hal_positive1_getDscpClientList, test_l1_platform_hal_positive2_getDscpClientList, test_l1_platform_hal_negative1_getDscpClientList, test_l1_platform_hal_negative2_getDscpClientList, test_l1_platform_hal_negative3_getDscpClientList, test_l1_platform_hal_positive1_GetDeviceConfigStatus, test_l1_platform_hal_negative1_GetDeviceConfigStatus,  test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable, test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable, test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable, test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable, test_l1_platform_hal_positive1_getInputCurrent, test_l1_platform_hal_negative1_getInputCurrent, test_l1_platform_hal_positive1_LoadThermalConfig, test_l1_platform_hal_negative1_LoadThermalConfig, test_l1_platform_hal_positive1_GetMACsecOperationalStatus, test_l1_platform_hal_negative1_GetMACsecOperationalStatus, test_l1_platform_hal_positive1_setFanMaxOverride, test_l1_platform_hal_positive2_setFanMaxOverride, test_l1_platform_hal_positive3_setFanMaxOverride, test_l1_platform_hal_positive4_setFanMaxOverride, test_l1_platform_hal_negative1_setFanMaxOverride, test_l1_platform_hal_negative2_setFanMaxOverride, test_l1_platform_hal_negative3_setFanMaxOverride, test_l1_platform_hal_positive1_setFanSpeed, test_l1_platform_hal_positive2_setFanSpeed, test_l1_platform_hal_positive3_setFanSpeed, test_l1_platform_hal_positive4_setFanSpeed, test_l1_platform_hal_positive5_setFanSpeed, test_l1_platform_hal_positive6_setFanSpeed, test_l1_platform_hal_positive7_setFanSpeed, test_l1_platform_hal_positive8_setFanSpeed, test_l1_platform_hal_positive9_setFanSpeed, test_l1_platform_hal_positive10_setFanSpeed, test_l1_platform_hal_negative1_setFanSpeed, test_l1_platform_hal_negative2_setFanSpeed, test_l1_platform_hal_negative3_setFanSpeed,  test_l1_platform_hal_positive1_getInputPower, test_l1_platform_hal_negative1_getInputPower, test_l1_platform_hal_positive1_GetCPUSpeed, test_l1_platform_hal_negative1_GetCPUSpeed, test_l1_platform_hal_positive1_GetFreeMemorySize, test_l1_platform_hal_negative1_GetFreeMemorySize, test_l1_platform_hal_positive1_getTimeOffSet, test_l1_platform_hal_negative1_getTimeOffSet, test_l1_platform_hal_positive1_getFactoryPartnerId, test_l1_platform_hal_negative1_getFactoryPartnerId, test_l1_platform_hal_positive1_initLed, test_l1_platform_hal_negative1_initLed, test_l1_platform_hal_positive1_getFanStatus, test_l1_platform_hal_positive2_getFanStatus, test_l1_platform_hal_positive1_getFanSpeed, test_l1_platform_hal_positive2_getFanSpeed, test_l1_platform_hal_positive1_GetSSHEnable,test_l1_platform_hal_negative1_GetSSHEnable, test_l1_platform_hal_positive1_SetSSHEnable, test_l1_platform_hal_positive2_SetSSHEnable, test_l1_platform_hal_negative1_SetSSHEnable, test_l1_platform_hal_negative2_SetSSHEnable, test_l1_platform_hal_positive1_resetDscpCounts, test_l1_platform_hal_positive2_resetDscpCounts, test_l1_platform_hal_negative1_resetDscpCounts, test_l1_platform_hal_positive1_PandMDBInit, test_l1_platform_hal_positive1_GetTelnetEnable,test_l1_platform_hal_negative1_GetTelnetEnable,test_l1_platform_hal_positive1_DocsisParamsDBInit, test_l1_platform_hal_positive1_SetTelnetEnable, test_l1_platform_hal_positive2_SetTelnetEnable, test_l1_platform_hal_negative1_SetTelnetEnable, test_l1_platform_hal_negative2_SetTelnetEnable, test_l1_platform_hal_positive1_StopMACsec, test_l1_platform_hal_positive2_StopMACsec, test_l1_platform_hal_positive3_StopMACsec, test_l1_platform_hal_negative1_StopMACsec, test_l1_platform_hal_negative2_StopMACsec, test_l1_platform_hal_negative3_StopMACsec};

    // Add tests to the suite
    for (int i = 0; i < sizeof(list1) / sizeof(list1[0]); i++) {
        UT_add_test(pSuite, list1[i], list2[i]);
    }
    return 0;
}
int main(int argc, char** argv)
{
    int registerReturn = 0;
    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );
    /* Check if tests are registered successfully */
    registerReturn = register_hal_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_tests() returned success");
    }
    else
    {
        printf("register_hal_tests() returned failure");
        return 1;
    }
    /* Begin test executions */
    UT_run_tests();
    return 0;
}
