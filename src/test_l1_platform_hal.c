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
* @file test_l1_platform_hal.c
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
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include "cJSON.h"
#include "platform_hal.h"

int MaxEthPort = 0;
char PartnerID[512] = { '\0' };
char** factoryCmVariant = NULL;
int num_FactoryCmVariant = 0;
RDK_CPUS *supportedCpus = NULL;
int num_SupportedCPUs = 0;
PSM_STATE *Supported_PSM_STATE = NULL;
int num_Supported_PSM_STATE = 0;
int *FanIndex = NULL;
int num_FanIndex = 0;
char** InterfaceNames = NULL;
int num_InterfaceNames = 0;

extern int init_platform_hal_init(void);

/**function to read the json config file and return its content as a string
*IN : json file name
*OUT : content of json file as string
**/
static char* read_file(const char *filename)
{
    FILE *file = NULL;
    long length = 0;
    char *content = NULL;
    size_t read_chars = 0;

    /* open in read mode */
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Please place platform_config file ,where your binary is placed\n");
        exit(1);
    }
    else
    {
        /* get the length */
        if (fseek(file, 0, SEEK_END) == 0)
        {
            length = ftell(file);
            if (length > 0)
            {
                if (fseek(file, 0, SEEK_SET) == 0)
                {
                    /* allocate content buffer */
                    content = (char*)malloc((size_t)length + sizeof(""));
                    if (content != NULL)
                    {
                        /* read the file into memory */
                        read_chars = fread(content, sizeof(char), (size_t)length, file);
                        if ((long)read_chars != length)
                        {
                            free(content);
                            content = NULL;
                        }
                        else
                            content[read_chars] = '\0';
                    }
                }
            }
            else
            {
                printf("platform_config file is empty. please add configuration\n");
                exit(1);
            }
        }
        fclose(file);
    }
    return content;
}

/**function to read the json config file and return its content as a json object
*IN : json file name
*OUT : content of json file as a json object
**/
static cJSON *parse_file(const char *filename)
{
    cJSON *parsed = NULL;
    char *content = read_file(filename);
    parsed = cJSON_Parse(content);

    if(content != NULL)
    {
        free(content);
    }

    return parsed;
}

/* get the MaxEthPort from configuration file */
int get_MaxEthPort(void)
{
    char configFile[] =  "./platform_config";
    cJSON *value = NULL;
    cJSON *json = NULL;
    UT_LOG("Checking MaxEthPort");
    json = parse_file(configFile);
    if(json == NULL)
    {
        printf("Failed to parse config\n");
        return -1;
    }
    value = cJSON_GetObjectItem(json, "MaxEthPort");
    // null check and object is number, value->valueint
    if((value != NULL) && (cJSON_IsNumber(value)))
    {
        MaxEthPort = value->valueint;
    }
    UT_LOG("MaxEthPort from config file is : %d",MaxEthPort);
    return 0;
}

/* get the PartnerID from configuration file */
int get_PartnerID(void)
{
    char configFile[] =  "./platform_config";
    cJSON *value = NULL;
    cJSON *json = NULL;
    UT_LOG("Checking PartnerID");
    json = parse_file(configFile);
    if(json == NULL)
    {
        printf("Failed to parse config\n");
        return -1;
    }
    value = cJSON_GetObjectItem(json, "PartnerID");
    // null check and object is string, value->valuestring
    if((value != NULL) && (cJSON_IsString(value)))
    {
       strcpy(PartnerID, value->valuestring);
    }
    UT_LOG("PartnerID from config file is : %s",PartnerID);
    return 0;
}

/* Free memory allocated for factoryCmVariant */
void freeFactoryCmVariant(void)
{
    int i = 0;
    if (factoryCmVariant != NULL)
    {
        for (i = 0; i < num_FactoryCmVariant; i++)
        {
            free(factoryCmVariant[i]);
        }
        free(factoryCmVariant);
    }
}

/* get the FactoryCmVariant from configuration file */
int get_FactoryCmVariant(void)
{
    char configFile[] = "./platform_config";
    cJSON* value = NULL;
    cJSON* json = NULL;
    cJSON* item = NULL;
    int i = 0;

    UT_LOG("Checking FactoryCmVariant");
    json = parse_file(configFile);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return -1;
    }
    value = cJSON_GetObjectItem(json, "FactoryCmVariant");
    // null check and object is Array, value->valuestring
    if ((value != NULL) && (cJSON_IsArray(value)))
    {
        num_FactoryCmVariant = cJSON_GetArraySize(value);
        printf("Number of FactoryCmVariant : %d \n", num_FactoryCmVariant);

        // Allocate memory for factoryCmVariant
        factoryCmVariant = (char**)malloc(num_FactoryCmVariant * sizeof(char*));
        if (factoryCmVariant == NULL)
	{
            printf("Memory allocation failed\n");
            cJSON_Delete(json);
            return -1;
        }
        cJSON_ArrayForEach(item, value)
        {
            if (i < num_FactoryCmVariant && cJSON_IsString(item))
            {
                // Allocate memory for each string and copy the content
                factoryCmVariant[i] = (char*)malloc((strlen(item->valuestring) + 1) * sizeof(char));
                if (factoryCmVariant[i] == NULL)
                {
                    printf("Memory allocation failed\n");
                    freeFactoryCmVariant();
                    cJSON_Delete(json);
                    return -1;
                }

                strcpy(factoryCmVariant[i], item->valuestring);
                i++;
            }
        }
    }
    // Free cJSON object as it is no longer needed
    cJSON_Delete(json);
    return 0;
}

/* get the Supported CPUs from configuration file */
int get_SupportedCPUs(void)
{
    char configFile[] = "./platform_config";
    cJSON* value = NULL;
    cJSON* json = NULL;
    int i = 0;
    UT_LOG("Checking SupportedCPUs");
    json = parse_file(configFile);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return -1;
    }
    value = cJSON_GetObjectItem(json, "Supported_CPUS");

    // Null check and object is an array
    if ((value != NULL) && (cJSON_IsArray(value)))
    {
        num_SupportedCPUs = cJSON_GetArraySize(value);
        printf("Number of SupportedCPUs : %d\n", num_SupportedCPUs);
        // Allocate memory for SupportedCPUs
        supportedCpus = (RDK_CPUS*)malloc(num_SupportedCPUs * sizeof(RDK_CPUS));
        if (!*supportedCpus)
        {
            printf("Memory allocation failed\n");
            cJSON_Delete(json);
            return -1;
        }

        for (i = 0; i < num_SupportedCPUs; i++)
        {
            cJSON *cpuItem = cJSON_GetArrayItem(value, i);
            if (!cJSON_IsNumber(cpuItem))
            {
                printf("Invalid CPU type in Supported_CPUS array\n"); // Invalid CPU type
                free(supportedCpus);
                cJSON_Delete(json);
                return 0;
            }
            supportedCpus[i] = (RDK_CPUS)cJSON_GetNumberValue(cpuItem);
        }
    }
    // Free cJSON object as it is no longer needed
    cJSON_Delete(json);
    return 0;
}

/* get the LowPowerModeStates from configuration file */
int get_LowPowerModeStates(void)
{
    char configFile[] = "./platform_config";
    cJSON* value = NULL;
    cJSON* json = NULL;
    int i = 0;
    UT_LOG("Checking LowPowerModeStates");
    json = parse_file(configFile);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return -1;
    }
    value = cJSON_GetObjectItem(json, "Supported_PSM_STATE");

    // Null check and object is an array
    if ((value != NULL) && (cJSON_IsArray(value)))
    {
        num_Supported_PSM_STATE = cJSON_GetArraySize(value);
        printf("Number of Supported_PSM_STATE : %d\n", num_Supported_PSM_STATE);

        // Allocate memory for SupportedCPUs
        Supported_PSM_STATE = (PSM_STATE*)malloc(num_Supported_PSM_STATE * sizeof(PSM_STATE));
        if (!*Supported_PSM_STATE)
        {
            printf("Memory allocation failed\n");
            cJSON_Delete(json);
            return -1;
        }
        for (i = 0; i < num_Supported_PSM_STATE; i++)
        {
            cJSON *PSMItem = cJSON_GetArrayItem(value, i);
            if (!cJSON_IsNumber(PSMItem))
            {
                printf("Invalid PSM state in Supported_PSM_STATE array\n"); // Invalid PSM state
                free(Supported_PSM_STATE);
                cJSON_Delete(json);
                return 0;
            }
            Supported_PSM_STATE[i] = (PSM_STATE)cJSON_GetNumberValue(PSMItem);
        }
    }
    // Free cJSON object as it is no longer needed
    cJSON_Delete(json);
    return 0;
}

/* get the FanIndex from configuration file */
int get_FanIndex(void)
{
    char configFile[] = "./platform_config";
    cJSON* value = NULL;
    cJSON* json = NULL;
    int i = 0;
    UT_LOG("Checking FanIndex");
    json = parse_file(configFile);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return -1;
    }
    value = cJSON_GetObjectItem(json, "FanIndex");

    // Null check and object is an array
    if ((value != NULL) && (cJSON_IsArray(value)))
    {
        num_FanIndex = cJSON_GetArraySize(value);
        printf("Number of FanIndex : %d\n", num_FanIndex);

        // Allocate memory for FanIndex
        FanIndex = (int*)malloc(num_FanIndex * sizeof(int));
        if (!*FanIndex)
        {
            printf("Memory allocation failed\n");
            cJSON_Delete(json);
            return -1;
        }
        for (i = 0; i < num_FanIndex; i++)
        {
            cJSON *FanItem = cJSON_GetArrayItem(value, i);
            if (!cJSON_IsNumber(FanItem))
            {
                printf("Invalid FanIndex in array\n"); // Invalid FanIndex
                free(FanIndex);
                cJSON_Delete(json);
                return 0;
            }
            FanIndex[i] = (int)cJSON_GetNumberValue(FanItem);
        }
    }
    // Free cJSON object as it is no longer needed
    cJSON_Delete(json);
    return 0;
}

/* Free memory allocated for InterfaceNames */
void freeInterfaceNames(void)
{
    int i = 0;
    if (InterfaceNames != NULL)
    {
        for (i = 0; i < num_InterfaceNames; i++)
        {
            free(InterfaceNames[i]);
        }
        free(InterfaceNames);
    }
}

/* get the InterfaceNames from configuration file */
int get_InterfaceNames(void)
{
    char configFile[] = "./platform_config";
    cJSON* value = NULL;
    cJSON* json = NULL;
    cJSON* item = NULL;
    int i = 0;

    UT_LOG("Checking InterfaceNames");
    json = parse_file(configFile);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return -1;
    }
    value = cJSON_GetObjectItem(json, "InterfaceNames");
    // null check and object is Array, value->valuestring
    if ((value != NULL) && (cJSON_IsArray(value)))
    {
        num_InterfaceNames = cJSON_GetArraySize(value);
        printf("Number of InterfaceNames : %d \n", num_InterfaceNames);

        // Allocate memory for InterfaceNames
        InterfaceNames = (char**)malloc(num_InterfaceNames * sizeof(char*));
        if (InterfaceNames == NULL)
	{
            printf("Memory allocation failed\n");
            cJSON_Delete(json);
            return -1;
        }
        cJSON_ArrayForEach(item, value)
        {
            if (i < num_InterfaceNames && cJSON_IsString(item))
            {
                // Allocate memory for each string and copy the content
                InterfaceNames[i] = (char*)malloc((strlen(item->valuestring) + 1) * sizeof(char));
                if (InterfaceNames[i] == NULL)
                {
                    printf("Memory allocation failed\n");
                    freeInterfaceNames();
                    cJSON_Delete(json);
                    return -1;
                }

                strcpy(InterfaceNames[i], item->valuestring);
                i++;
            }
        }
    }
    // Free cJSON object as it is no longer needed
    cJSON_Delete(json);
    return 0;
}

/**
* @brief This test case is used to verify the functionality of the get firmware name API.
*
* The objective of this test is to ensure that the get firmware name API returns the firmware name correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 001 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* | :-----: |------------|----------|----------------|------|
* |01 | Invoking platform_hal_GetFirmwareName() with pValue = valid buffer, maxSize = 256|pValue = valid buffer, maxSize = 256| RETURN_OK| Should Pass|
*/
void test_l1_platform_hal_positive1_GetFirmwareName(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFirmwareName...");

    CHAR pValue[256] = {"\0"};
    ULONG maxSize = 256;

    UT_LOG("Invoking platform_hal_GetFirmwareName() with pValue = valid buffer, maxSize = %lu.",maxSize);
    INT status = platform_hal_GetFirmwareName(pValue, maxSize);

    UT_LOG("Firmware Name: %s", pValue);
    UT_LOG("platform_hal_GetFirmwareName API returns: %d", status);
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
* | :----: |----------|----------|--------------|-----|
* | 01| Invoking platform_hal_GetFirmwareName with pValue = NULL, maxSize = 256| pValue = NULL, maxSize = 256 | RETURN_ERR | Should Fail |
*/
void test_l1_platform_hal_negative1_GetFirmwareName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFirmwareName...");

    CHAR* pValue = NULL;
    ULONG maxSize = 256;

    UT_LOG("Invoking platform_hal_GetFirmwareName() with pValue = NULL, maxSize = %lu.",maxSize);
    INT status = platform_hal_GetFirmwareName(pValue, maxSize);

    UT_LOG("platform_hal_GetFirmwareName API returns: %d", status);
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
* | 01 | Invoking platform_hal_GetSoftwareVersion with pValue = valid buffer, maxSize = 256 | pValue = valid buffer, maxSize = 256 | RETURN_OK | Should Pass |
*/
void test_l1_platform_hal_positive1_GetSoftwareVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetSoftwareVersion...");

    CHAR pValue[256] = {"\0"};
    ULONG maxSize = 256;

    UT_LOG("Invoking platform_hal_GetSoftwareVersion with pValue = valid buffer, maxSize = %lu.",maxSize);
    INT status = platform_hal_GetSoftwareVersion(pValue, maxSize);

    UT_LOG("SoftwareVersion : %s", pValue);
    UT_LOG("platform_hal_GetSoftwareVersion API returns: %d", status);

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
* | 01 | Invoking platform_hal_GetSoftwareVersion with pValue = NULL, maxSize = 256 | pValue = NULL, maxSize = 256 | RETURN_ERR | Should Fail |
*/
void test_l1_platform_hal_negative1_GetSoftwareVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetSoftwareVersion...");
    CHAR* pValue = NULL;
    ULONG maxSize = 256;

    UT_LOG("Invoking platform_hal_GetSoftwareVersion with pValue = NULL, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetSoftwareVersion(pValue, maxSize);

    UT_LOG("platform_hal_GetSoftwareVersion API returns: %d", status);
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoking platform_hal_GetSerialNumber function with serialNumber = valid Buffer | serialNumber = valid Buffer | RETURN_OK | Should Pass |
*/
void test_l1_platform_hal_positive1_GetSerialNumber(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetSerialNumber...");
    CHAR serialNumber[256] = {"\0"};

    UT_LOG("Invoking platform_hal_GetSerialNumber function with serialNumber = valid Buffer");
    INT status = platform_hal_GetSerialNumber(serialNumber);

    UT_LOG("Output value of serialNumber : %s", serialNumber);
    UT_LOG("platform_hal_GetSerialNumber API returns : %d", status);

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
* | Variation / Step | Description | Test Data | Expected Result| Notes|
* | :--------------: |----------| --------|----------|----------------------|
* |01| Invoking platform_hal_GetSerialNumber with serialNumber = NULL | serialNumber = NULL| RETURN_ERR| Should Fail|
*/
void test_l1_platform_hal_negative1_GetSerialNumber(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetSerialNumber...");
    CHAR *serialNumber = NULL;

    UT_LOG("Invoking platform_hal_GetSerialNumber with serialNumber = NULL.");
    INT status = platform_hal_GetSerialNumber(serialNumber);

    UT_LOG("platform_hal_GetSerialNumber API returns: %d", status);
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
* | 01 | Invoking platform_hal_GetSNMPEnable with valid pValue buffer| pValue = Valid Buffer| RETURN_OK  | Should be successful |
*/
void test_l1_platform_hal_positive1_GetSNMPEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetSNMPEnable...");
    CHAR pValue[32] = {"\0"};

    UT_LOG("Invoking platform_hal_GetSNMPEnable with valid pValue buffer");
    INT result = platform_hal_GetSNMPEnable(pValue);

    UT_LOG("Output of pValue: %s", pValue);
    UT_LOG("platform_hal_GetSNMPEnable API returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    if (!strcmp(pValue,"rgWan") || !strcmp(pValue,"rgDualIp")|| !strcmp(pValue,"rgLanIp"))
    {
        UT_LOG("SNMP Enable value from the device is %s which is a valid value", pValue);
        UT_PASS("Get SNMP Enable validation success");
    }
    else
    {
        UT_LOG("SNMP Enable value from the device %s which is an Invalid value", pValue);
        UT_FAIL("Get SNMP Enable validation failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetSNMPEnable...");
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :------: |---------|----------|-------------|---------|
* | 01| Verify platform_hal_GetSNMPEnable with NULL pValue| pValue = NULL| RETURN_ERR| Should fail|
*/
void test_l1_platform_hal_negative1_GetSNMPEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetSNMPEnable...");
    char *pValue = NULL;

    UT_LOG("Invoking platform_hal_GetSNMPEnable with NULL pValue");
    INT result = platform_hal_GetSNMPEnable(pValue);

    UT_LOG("platform_hal_GetSNMPEnable API returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetSNMPEnable...");
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
* | 01 | Invoking platform_hal_GetHardware_MemUsed with value = Valid Buffer| value = Valid Buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetHardware_MemUsed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardware_MemUsed...");
    CHAR value[1024] = {"\0"};
    int Mem_Used = 0;

    UT_LOG("Invoking platform_hal_GetHardware_MemUsed with value = Valid Buffer.");
    INT status = platform_hal_GetHardware_MemUsed(value);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_LOG("platform_hal_GetHardware_MemUsed returns: %d", status);

    Mem_Used = atoi(value);
    UT_LOG("Total used memory : %d", Mem_Used);
    if(Mem_Used > 0)
    {
        UT_LOG("Hardware Memory Used is %d which is a valid value.", Mem_Used);
        UT_PASS("Get Hardware Memory Used validation success");
    }
    else
    {
        UT_LOG("Hardware Memory Used is %d which is an invalid value.", Mem_Used);
        UT_FAIL("Get Hardware Memory Used validation failed");
    }
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
* | :----: | --------- | ---------- |--------------|-----|
* | 01 | Invoking platform_hal_GetHardware_MemUsed with  value = NULL | value = NULL | RETURN_ERR | Should be equal to RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetHardware_MemUsed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardware_MemUsed...");
    CHAR *value = NULL;

    UT_LOG("Invoking platform_hal_GetHardware_MemUsed with  value = NULL.");
    INT status = platform_hal_GetHardware_MemUsed(value);

    UT_LOG("platform_hal_GetHardware_MemUsed returns : %d", status);
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
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* |:-------:|-----------|---------|------------|-------|
* |01| Invoke platform_hal_GetHardwareVersion function with pValue = Valid Buffer| pValue = Valid Buffer|RETURN_OK| Should be successful|
*/
void test_l1_platform_hal_positive1_GetHardwareVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardwareVersion...");
    CHAR pValue[256] = {"\0"};

    UT_LOG("Invoking platform_hal_GetHardwareVersion with pValue = Valid Buffer.");
    INT status = platform_hal_GetHardwareVersion(pValue);

    UT_LOG("platform_hal_GetHardwareVersion returns :%d",status);
    UT_LOG("Hardware Version : %s",pValue);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetHardwareVersion...");
}

/**
* @brief Test case for the platform_hal_GetHardwareVersion function with negative input.
*
* This test case is used to verify the behavior of the platform_hal_GetHardwareVersion function when provided with negative input. The objective of this test is to ensure that the function correctly handles negative input and returns the expected error code.
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
* | Variation / Step | Description|Test Data| Expected Result| Notes|
* |:------:|----------|--------------|--------|-------|
* |01|Invoke platform_hal_GetHardwareVersion function with pValue = NULL| pValue = NULL | Status = RETURN_ERR|Should fail|
*/
void test_l1_platform_hal_negative1_GetHardwareVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardwareVersion...");
    CHAR* pValue = NULL;

    UT_LOG("Invoking platform_hal_GetHardwareVersion with pValue = NULL.");
    INT status = platform_hal_GetHardwareVersion(pValue);

    UT_LOG("platform_hal_GetHardwareVersion returns : %d",status);
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
* | 01| Invoke GetModelName API with pValue = Valid buffer | pValue = Valid buffer |RETURN_OK|Should be successful|
*/
void test_l1_platform_hal_positive1_GetModelName(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetModelName...");
    CHAR pValue[256] = {"\0"};

    UT_LOG("Invoking platform_hal_GetModelName with pValue = Valid buffer");
    INT status = platform_hal_GetModelName(pValue);

    UT_LOG("Model Name : %s", pValue);
    UT_LOG("platform_hal_GetModelName returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetModelName...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_GetModelName function when invoked with a NULL input parameter.
*
* This test case checks if the platform_hal_GetModelName function returns the expected result when invoked with a NULL input parameter. The objective of this test case is to ensure that the function can handle NULL input correctly and return the appropriate status code.
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
* | :------: | -------- | --------- | --------------- | ----- |
* | 01 | Invoking platform_hal_GetModelName with model_name = NULL| model_name = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetModelName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetModelName...");
    CHAR* model_name = NULL;

    UT_LOG("Invoking platform_hal_GetModelName with model_name = NULL");
    INT status = platform_hal_GetModelName(model_name);

    UT_LOG("platform_hal_GetModelName returns: %d", status);
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
* | 01 | Invoking platform_hal_GetRouterRegion with pValue = Valid buffer | pValue = Valid buffer| RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetRouterRegion(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetRouterRegion...");
    CHAR pValue[256] = {"\0"};

    UT_LOG("Invoking platform_hal_GetRouterRegion with pValue = Valid buffer");
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
        UT_LOG("Router region is %s which is an invalid value", pValue);
        UT_FAIL("Get Router Region validation failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetRouterRegion...");
}

/**
* @brief Test case to validate the behavior of platform_hal_GetRouterRegion when NULL pointer is passed as argument.
*
* This test case checks the functionality of platform_hal_GetRouterRegion when NULL pointer is passed as argument. The objective of this test is to ensure that the API returns RETURN_ERR when NULL pointer is passed as argument.
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
* | 01 | Invoking platform_hal_GetRouterRegion with pValue = NULL | pValue = NULL | RETURN_ERR | Should be successful |
*/
void test_l1_platform_hal_negative1_GetRouterRegion(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetRouterRegion...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_GetRouterRegion with pValue = NULL");
    INT status = platform_hal_GetRouterRegion(pValue);

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
* |01| Invoking platform_hal_GetBootloaderVersion with pValue = valid buffer, maxSize = 256| pValue = valid buffer, maxSize = 256| RETURN_OK | Should be successful|
*/
void test_l1_platform_hal_positive1_GetBootloaderVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetBootloaderVersion...");
    CHAR pValue[256] = {"\0"};
    ULONG maxSize = 256;

    UT_LOG("Invoking platform_hal_GetBootloaderVersion with pValue = valid buffer, maxSize = %lu.",maxSize);
    INT status = platform_hal_GetBootloaderVersion(pValue, maxSize);

    UT_LOG("Bootloader Version = %s", pValue);
    UT_LOG("platform_hal_GetBootloaderVersion returns = %d", status);
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
*  | Variation / Step | Description | Test Data| Expected Result| Notes|
*  | :--------: |-----------| -------- | --------| ---------|
*  |01| Invoke the platform_hal_GetBootloaderVersion with pValue = NULL, maxSize = 0| pValue = NULL, maxSize = 0| RETURN_ERR|Should fail|
*/
void test_l1_platform_hal_negative1_GetBootloaderVersion(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetBootloaderVersion...");
    CHAR* pValue = NULL;
    ULONG maxSize = 0;

    UT_LOG("Invoking platform_hal_GetBootloaderVersion with pValue = NULL, maxSize = 0.");
    INT status = platform_hal_GetBootloaderVersion(pValue, maxSize);

    UT_LOG("platform_hal_GetBootloaderVersion returns = %d", status);
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
* | 01 | Invoking platform_hal_GetHardware with value = valid buffer | value = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetHardware(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardware...");
    CHAR value[256] = {"\0"};
    int flash_size = 0;

    UT_LOG("Invoking platform_hal_GetHardware with value = valid buffer");
    INT ret = platform_hal_GetHardware(value);

    UT_LOG("Output value of pValue = %s", value);
    UT_LOG("platform_hal_GetHardware returns = %d", ret);

    flash_size = atoi(value);
    UT_ASSERT_EQUAL(ret, RETURN_OK);

    if (flash_size >= 1 && flash_size <= 4096)
    {
        UT_LOG("The hardware value of the device is %d which is a valid value", flash_size);
        UT_PASS("Get Hardware validation success");
    }
    else
    {
        UT_LOG("The hardware value  of the device is %d which is an invalid value", flash_size);
        UT_FAIL("Get Hardware validation failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetHardware...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_GetHardware() function when a NULL pointer is passed as one of the arguments.
*
* The objective of this test is to ensure that the function returns a specific error code when a NULL pointer is passed as the argument "pValue" to platform_hal_GetHardware().
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetHardware with pValue = NULL | pValue = NULL | RETURN_ERR | Should return the error code |
*/
void test_l1_platform_hal_negative1_GetHardware(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardware...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_GetHardware with pValue = NULL");
    INT ret = platform_hal_GetHardware(pValue);

    UT_LOG(" platform_hal_GetHardware returns = %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetHardware...");
}

/**
* @brief Test the function platform_hal_SetSNMPEnable for positive scenario.
*
* This test case verifies the behavior of the function platform_hal_SetSNMPEnable when it is invoked with valid input parameters.
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
* | 01 | Invoking platform_hal_SetSNMPEnable with pValue = "rgWan" | pValue = "rgWan" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_SetSNMPEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetSNMPEnable...");
    CHAR pValue[32] = "rgWan";

    UT_LOG("Invoking platform_hal_SetSNMPEnable with pValue = %s.",pValue);
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("platform_hal_SetSNMPEnable returns : %d", result);
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
* | 01 | Invoking platform_hal_SetSNMPEnable with pValue = "rgDualIp" | pValue = "rgDualIp" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetSNMPEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetSNMPEnable...");
    CHAR pValue[32] = "rgDualIp";

    UT_LOG("Invoking platform_hal_SetSNMPEnable with pValue = %s.",pValue);
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("platform_hal_SetSNMPEnable returns : %d", result);
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
* | 01 | Invoke platform_hal_SetSNMPEnable with pValue = "rgLanIp" | pValue = "rgLanIp" | RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive3_SetSNMPEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_SetSNMPEnable...");
    CHAR pValue[32] = "rgLanIp";

    UT_LOG("Invoke platform_hal_SetSNMPEnable with pValue = %s.",pValue);
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("platform_hal_SetSNMPEnable returns : %d", result);
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
* | Variation / Step | Description | Test Data| Expected Result |Notes|
* | :------: |------------| -----------| ----------| ------ |
* | 01| Invoking platform_hal_SetSNMPEnable with pValue = NULL | pValue = NULL| RETURN_ERR| Should fail |
*/
void test_l1_platform_hal_negative1_SetSNMPEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetSNMPEnable...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_SetSNMPEnable with pValue = NULL.");
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("platform_hal_SetSNMPEnable returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetSNMPEnable...");
}

/**
* @brief Unit test for the function platform_hal_SetSNMPEnable when provided with invalid input value.
*
* This test is used to verify the behavior of the platform_hal_SetSNMPEnable function when it is called with an invalid input value. The function should return an error code indicating that the input value is invalid.
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
* | 01 | Invoking platform_hal_SetSNMPEnable with pValue = "invalidValue" | pValue = "invalidValue" | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative2_SetSNMPEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetSNMPEnable...");
    CHAR pValue[32] = "invalidValue";

    UT_LOG("Invoking platform_hal_SetSNMPEnable with pValue = %s.",pValue);
    INT result = platform_hal_SetSNMPEnable(pValue);

    UT_LOG("platform_hal_SetSNMPEnable returns : %d", result);
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
* | 01 |Invoking platform_hal_SetWebUITimeout with value = 30 | value = 30 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetWebUITimeout...");
    ULONG value = 30;

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu.", value);
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("platform_hal_SetWebUITimeout returns: %d", result);
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
* | 01 | Invoking platform_hal_SetWebUITimeout with value = 86400 | value = 86400 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetWebUITimeout...");
    ULONG value = 86400;

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu.", value);
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("platform_hal_SetWebUITimeout returns : %d", result);
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
* | 01 | Invoking platform_hal_SetWebUITimeout with value = 0 | value = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive3_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_SetWebUITimeout...");
    ULONG value = 0;

    UT_LOG("Invoking platform_hal_SetWebUITimeout with value = %lu.", value);
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("platform_hal_SetWebUITimeout returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetWebUITimeout...");
}

/**
* @brief This test is used to verify the behavior of the platform_hal_SetWebUITimeout function when the input value is 100.
*
* The purpose of this test is to ensure that the platform_hal_SetWebUITimeout function behaves correctly when the input value is 100.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 029 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, they have to select this test case via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_SetWebUITimeout function with value = 100 | value = 100 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive4_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive4_SetWebUITimeout...");
    ULONG value = 100;

    UT_LOG("Invoking platform_hal_SetWebUITimeout function with value = %lu.",value);
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("platform_hal_SetWebUITimeout returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive4_SetWebUITimeout...");
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
* | Variation / Step | Description | Test Data | Expected Result |Notes|
* | :---------: | ----------- | ----------|----------|----------|
* | 01 | Invoking platform_hal_SetWebUITimeout with invalid value = 86401 | value = 86401 |  RETURN_ERR | Should return error|
*/
void test_l1_platform_hal_negative1_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetWebUITimeout...");
    ULONG value = 86401;

    UT_LOG("Invoking platform_hal_SetWebUITimeout with invalid value = %lu.", value);
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("platform_hal_SetWebUITimeout returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetWebUITimeout...");
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
* | 01 | Invoking platform_hal_SetWebUITimeout with invalid value = 29 | value = 29 | RETURN_ERR | Should return RETURN_ERR  |
*/
void test_l1_platform_hal_negative2_SetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetWebUITimeout...");
    ULONG value = 29;

    UT_LOG("Invoking platform_hal_SetWebUITimeout with invalid value = %lu.", value);
    INT result = platform_hal_SetWebUITimeout(value);

    UT_LOG("platform_hal_SetWebUITimeout returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetWebUITimeout...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_GetWebUITimeout function.
*
* The objective of this test is to ensure that the platform_hal_GetWebUITimeout function returns the correct status and outputs the expected value.
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
* | Variation / Step | Description | Test Data| Expected Result | Notes |
* | :----------: | --------| ------- | -----------| -------- |
* | 01| Invoke platform_hal_GetWebUITimeout function with valid buffer | value = valid buffer | RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive1_GetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetWebUITimeout...");
    ULONG value = 5;

    UT_LOG("Invoking platform_hal_GetWebUITimeout with valid buffer");
    INT status = platform_hal_GetWebUITimeout(&value);

    UT_LOG("platform_hal_GetWebUITimeout returns : %d", status);
    UT_LOG("WebUI timeout value : %lu", value);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if(value >= 30 && value <= 86400)
    {
        UT_LOG("Web UI Timeout value is %lu", value);
        UT_PASS("Web UI Timeout validation success");
    }
    else
    {
        UT_LOG("Web UI Timeout value is %lu", value);
        UT_FAIL("Web UI Timeout validation failed");
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
* | 01 | Invoking platform_hal_GetWebUITimeout with value = NULL | value = NULL| RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative1_GetWebUITimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetWebUITimeout...");
    ULONG *value = NULL;

    UT_LOG("Invoking platform_hal_GetWebUITimeout with value = NULL.");
    INT status = platform_hal_GetWebUITimeout(value);

    UT_LOG("platform_hal_GetWebUITimeout API returns :%d",status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetWebUITimeout...");
}

/**
* @brief Test case to verify the functionality of platform_hal_GetBaseMacAddress function when a valid buffer for MAC address is provided.
*
* This test case verifies the functionality of the platform_hal_GetBaseMacAddress function by providing a valid buffer for MAC address.
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
* | 01 | Invoking platform_hal_GetBaseMacAddress with macAddress = valid buffer | macAddress = valid buffer |RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetBaseMacAddress(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetBaseMacAddress...");
    CHAR macAddress[256] = {"\0"};
    int count = 0;
    int len = 0;
    int flag = 1;

    UT_LOG("Invoking platform_hal_GetBaseMacAddress with  macAddress = valid buffer");
    INT status = platform_hal_GetBaseMacAddress(macAddress);

    UT_LOG("platform_hal_GetBaseMacAddress returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_LOG("MAC Address = %s", macAddress);

    len = strlen(macAddress);
    if(len == 17)
    {
        for (int i = 0; macAddress[i] != '\0'; i++)
        {
            // Check for valid characters: 0-9, A-F, a-f, and ':'
            if (!(isdigit(macAddress[i]) || (macAddress[i] >= 'A' && macAddress[i] <= 'F') || (macAddress[i] >= 'a' && macAddress[i] <= 'f') || macAddress[i] == ':'))
            {
                flag = 0;
                break;
            }
            // Count colons
            if (macAddress[i] == ':')
            {
                count++;
            }
        }
        if (count == 5 && flag == 1)
        {
            UT_LOG("MAC string is %s which is valid MAC address.",macAddress);
            UT_PASS("Get CMTS MAC validation success");
        }
        else
        {
            UT_LOG(" MAC address string is %s which is invalid string value.", macAddress);
            UT_FAIL("Get CMTS MAC validation failed");
        }
    }
    else
    {
        UT_LOG(" MAC address string is %s which is invalid string length.", macAddress);
        UT_FAIL("Get CMTS MAC validation failed");
    }

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
* | 01 | Invoking platform_hal_GetBaseMacAddress with pValue as NULL | pValue = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetBaseMacAddress(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetBaseMacAddress...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_GetBaseMacAddress with pValue as NULL");
    INT status = platform_hal_GetBaseMacAddress(pValue);

    UT_LOG("platform_hal_GetBaseMacAddress returns: %d", status);
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
* | 01 | Invoking platform_hal_GetHardware_MemFree with buffer = Valid buffer| buffer = Valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetHardware_MemFree(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetHardware_MemFree...");
    CHAR buffer[1024] = {"\0"};
    int version = 0;

    UT_LOG("Invoking platform_hal_GetHardware_MemFree with buffer = Valid buffer.");
    INT result = platform_hal_GetHardware_MemFree(buffer);

    UT_LOG("Hardware Memory Free : %s", buffer);
    UT_LOG("platform_hal_GetHardware_MemFree returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    version = atoi(buffer);
    if(version > 0)
    {
        UT_LOG("Hardware Memory Free is %d which is a valid value.", version);
        UT_PASS("Get Hardware Memory Free  validation success");
    }
    else
    {
        UT_LOG("Hardware Memory Free is %d which is an invalid value.", version);
        UT_FAIL("Get Hardware Memory Free validation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetHardware_MemFree...");
}

/**
* @brief Test case to validate the platform_hal_GetHardware_MemFree function with NULL pointer.
*
* This test case validates the platform_hal_GetHardware_MemFree function when invoked with a NULL pointer. It checks if the function returns RETURN_ERR as expected.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 037 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Test platform_hal_GetHardware_MemFree with pValue = NULL | pValue = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetHardware_MemFree(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetHardware_MemFree...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_GetHardware_MemFree with pValue = NULL.");
    INT result = platform_hal_GetHardware_MemFree(pValue);

    UT_LOG(" platform_hal_GetHardware_MemFree returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetHardware_MemFree...");
}

/**
* @brief This test case verifies the functionality of the platform_hal_GetUsedMemorySize API.
*
* This test case validates the platform_hal_GetUsedMemorySize API by invoking it with valid inputand checking the return value and the value of the pulSize variable after the API is executed. The test case also includes assertions to verify that the return value is equal to RETURN_OK and the value of pulSize is greater than 0.
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
*  | :-------: | ------- | --------- | --------- | ----- |
*  |01| Invoking platform_hal_GetUsedMemorySize with pulSize = valid buffer | pulSize = valid buffer | RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive1_GetUsedMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetUsedMemorySize...");
    ULONG pulSize = 0;

    UT_LOG("Invoking platform_hal_GetUsedMemorySize with pulSize = valid buffer.");
    INT ret = platform_hal_GetUsedMemorySize(&pulSize);

    UT_LOG(" platform_hal_GetUsedMemorySize returns : %d", ret);
    UT_LOG("pulSize: %lu", pulSize);

    UT_ASSERT_EQUAL(ret, RETURN_OK);
    if (pulSize > 0 )
    {
        UT_LOG("Used Memory size is %lu which is valid value.", pulSize);
        UT_PASS ("Get Used Memory size validation success ");
    }
    else
    {
        UT_LOG("Used Memory size is %lu which is an invalid value.", pulSize);
        UT_FAIL ("Get Used Memory size validation failed");
    }

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
* | 01 | Invoking platform_hal_GetUsedMemorySize with pulSize = NULL | pulSize = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_GetUsedMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetUsedMemorySize...");
    ULONG *pulSize = NULL;

    UT_LOG("Invoking platform_hal_GetUsedMemorySize with pulSize = NULL.");
    INT ret = platform_hal_GetUsedMemorySize(pulSize);

    UT_LOG("platform_hal_GetUsedMemorySize returns: %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

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
* | Variation / Step | Description |Test Data | Expected Result | Notes|
* | :----: | ---------| --------- |--------------| -------|
* | 01| Invoking platform_hal_ClearResetCount with bFlag = TRUE| bFlag = TRUE | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_ClearResetCount(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_ClearResetCount...");
    BOOLEAN bFlag = TRUE;

    UT_LOG("Invoking platform_hal_ClearResetCount with bFlag = TRUE");
    INT result = platform_hal_ClearResetCount(bFlag);

    UT_LOG("platform_hal_ClearResetCount returns : %d", result);
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
* | 01 | Invoking platform_hal_ClearResetCount with bFlag = FALSE | bFlag = FALSE | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_ClearResetCount(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_ClearResetCount...");
    BOOLEAN bFlag = FALSE;

    UT_LOG("Invoking platform_hal_ClearResetCount with bFlag = FALSE");
    INT result = platform_hal_ClearResetCount(bFlag);

    UT_LOG(" platform_hal_ClearResetCount returns: %d", result);
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
* | :----: |--------- |--------|--------------| -----|
* | 01| Invoking platform_hal_ClearResetCount with invalid bFlag = 2 | bFlag = 2 | RETURN_ERR | should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_ClearResetCount(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_ClearResetCount...");
    BOOLEAN bFlag = 2;

    UT_LOG("Invoking platform_hal_ClearResetCount with invalid bFlag = 2");
    INT result = platform_hal_ClearResetCount(bFlag);

    UT_LOG("platform_hal_ClearResetCount returns : %d", result);
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
* | :-------: | ----------- | --------- | ---------| ----- |
* | 01| Invoking platform_hal_SetDeviceCodeImageValid with bFlag = TRUE | flag = TRUE | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_SetDeviceCodeImageValid(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetDeviceCodeImageValid...");
    BOOLEAN flag = TRUE;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageValid with bFlag = TRUE.");
    INT result = platform_hal_SetDeviceCodeImageValid(flag);

    UT_LOG("platform_hal_SetDeviceCodeImageValid returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetDeviceCodeImageValid...");
}

/**
* @brief Test the functionality of the platform_hal_SetDeviceCodeImageValid function when setting the device code image flag to valid.
*
* This test verifies the functionality of the platform_hal_SetDeviceCodeImageValid function by setting the device code image flag to valid and checking if the function returns the expected result.
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
* | 01 | Invoking platform_hal_SetDeviceCodeImageValid with flag = FALSE | flag = FALSE | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetDeviceCodeImageValid(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetDeviceCodeImageValid...");
    BOOLEAN flag = FALSE;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageValid with flag = FALSE");
    INT result = platform_hal_SetDeviceCodeImageValid(flag);

    UT_LOG("platform_hal_SetDeviceCodeImageValid returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetDeviceCodeImageValid...");
}

/**
* @brief This test case validates the behavior of the platform_hal_SetDeviceCodeImageValid function when an invalid flag is provided.
*
* The platform_hal_SetDeviceCodeImageValid function is expected to return an error code when an invalid flag is provided. This test aims to verify if the function behaves as expected in this scenario.
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
* | 01 | Invoking platform_hal_SetDeviceCodeImageValid with an invalid flag = 2  | flag = 2 | RETURN_ERR | The function should return an error code |
*/
void test_l1_platform_hal_negative1_SetDeviceCodeImageValid(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetDeviceCodeImageValid...");
    BOOLEAN flag = 2;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageValid with an invalid flag = 2.");
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
*  | 01 | Invoking platform_hal_setFactoryCmVariant with pValue values from config file  | pValue from config value | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_setFactoryCmVariant(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_setFactoryCmVariant...");
    INT status = 0;
    CHAR pValue[512] = {'\0'};
    int i = 0;
    UT_LOG("Number of FactoryCmVariant values : %d ", num_FactoryCmVariant);

    for (i = 0; i < num_FactoryCmVariant; i++ )
    {
        status = 0;
        memset(pValue, 0, sizeof(pValue));
        //FactoryCmVariant should be configured in platform_config file
        strcpy(pValue, factoryCmVariant[i]);
        UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = %s.",pValue);
        status = platform_hal_setFactoryCmVariant(pValue);

        UT_LOG("platform_hal_setFactoryCmVariant returns : %d", status);
        UT_ASSERT_EQUAL(status, RETURN_OK);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_setFactoryCmVariant...");
}

/**
* @brief This test is used to verify the negative case of the setFactoryCmVariant function in the L1 platform HAL.
*
* The objective of this test is to ensure that the function returns the correct error code when the input parameter pValue is NULL.
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
* | 01 | Invoking platform_hal_setFactoryCmVariant with pValue = NULL | pValue = NULL | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative1_setFactoryCmVariant(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_setFactoryCmVariant...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with pValue = NULL");
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("platform_hal_setFactoryCmVariant returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setFactoryCmVariant...");
}

/**
* @brief This test is used to verify the negative case of the setFactoryCmVariant function in the L1 platform HAL.
*
* This test is used to verify that the function 'platform_hal_setFactoryCmVariant' returns an error when an invalid value is passed as the argument 'pValue'.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 048 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 |Invoking platform_hal_setFactoryCmVariant with invalid pValue = "invalid"| pValue = "invalid" | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative2_setFactoryCmVariant(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_setFactoryCmVariant...");
    CHAR pValue[512] = "invalid";

    UT_LOG("Invoking platform_hal_setFactoryCmVariant with invalid pValue = %s", pValue);
    INT status = platform_hal_setFactoryCmVariant(pValue);

    UT_LOG("platform_hal_setFactoryCmVariant returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_setFactoryCmVariant...");
}

/**
* @brief Test case to verify the platform_hal_getLed function with valid input parameters.
*
* This test case verifies the functionality of the platform_hal_getLed function when invoked with valid input parameters.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 049 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getLed with params = valid structure | params = Valid structure| RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_getLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getLed...");
    PLEDMGMT_PARAMS params = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));
    if(params != NULL)
    {
        memset(params, 0, sizeof(LEDMGMT_PARAMS));
        UT_LOG("Invoking platform_hal_getLed with params = valid structure");
        INT result = platform_hal_getLed(params);
        if(result == RETURN_OK)
        {
            UT_LOG("platform_hal_getLed API returns:%d", result);
            UT_LOG("LED colour:%d",params->LedColor);
            UT_LOG("State:%d",params->State);
            UT_LOG("Interval:%d",params->Interval);

            UT_ASSERT_EQUAL(result, RETURN_OK);
            if((params->LedColor >= 0) && (params->LedColor <= 6))
            {
                UT_LOG("Led Color is %d which is a valid value", params->LedColor);
                UT_PASS("Led Color validation success");
            }
            else
            {
                UT_LOG("Led Color is  %d which is an invalid value", params->LedColor);
                UT_FAIL("Led Color validation failed");
            }
            if((params->State == 0) || (params->State == 1))
            {
                UT_LOG("State is %d which is a valid value", params->State);
                UT_PASS("State validation success");
            }
            else
            {
                UT_LOG("State is  %d which is an invalid value", params->State);
                UT_FAIL("State validation failed");
            }
            if (params->Interval >= 0)
            {
                UT_LOG("Interval is %d which is a valid value", params->Interval);
                UT_PASS("Interval validation success");
            }
            else
            {
                UT_LOG("Interval is  %d which is an invalid value", params->Interval);
                UT_FAIL("Interval validation failed");
            }
        }
	else
        {
            UT_LOG("platform_hal_getLed API returns:%d", result);
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getLed...");
}

/**
* @brief Test to verify the behavior of platform_hal_getLed function when a null pointer is passed as an argument.
*
* This test is intended to verify the behavior of the platform_hal_getLed function when a null pointer is passed as an argument. The objective of this test is to ensure that the function returns the expected error code in this scenario.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 050 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :-------: | ----------- | --------- | ---------| ----- |
* | 01| Invoking platform_hal_getLed with params = NULL | params = NULL | RETURN_ERR  | Should return error |
*/
void test_l1_platform_hal_negative1_getLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getLed...");
    PLEDMGMT_PARAMS params = NULL;

    UT_LOG("Invoking platform_hal_getLed with params = NULL");
    INT result = platform_hal_getLed(params);

    UT_LOG("platform_hal_getLed returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getLed...");
}

/**
* @brief Test case to verify the functionality of platform_hal_getRotorLock API when called with a valid fanIndex values.
*
* This test case is to verify the functionality of platform_hal_getRotorLock API when called with a valid fanIndex values from config file. It checks whether the API returns the correct status indicating whether the rotor is locked or not.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 051 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getRotorLock with valid fanIndex from config file | fanIndex from config file |Return can be 0 or 1 | Should be successful |
*/
void test_l1_platform_hal_positive1_getRotorLock(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getRotorLock...");
    int i = 0;
    INT status = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_getRotorLock with fanIndex = %d",FanIndex[i]);
        status = platform_hal_getRotorLock(FanIndex[i]);

        UT_LOG("platform_hal_getRotorLock returns : %d", status);
        if(status == 1)
        {
            UT_LOG("Status of the Rotor is: %d locked ",status);
            UT_PASS("Get Rotor locked Validation success");
        }
        else if (status == 0)
        {
            UT_LOG("Status of the Rotor is: %d NOT locked ",status);
            UT_PASS("Get Rotor NOT locked Validation success");
        }
        else if(status == -1)
        {
            UT_LOG("Status of the Rotor is: %d  which is an invalid value",status);
            UT_FAIL("Get Rotor Validation failed");
        }
        else
        {
            UT_LOG("Status of the Rotor is: %d  which is an invalid value",status);
            UT_FAIL("Get Rotor Validation failed");
        }
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_getRotorLock...");
}

/**
* @brief Test case to verify the functionality of platform_hal_getRotorLock API with invalid fanIndex value.
*
* This test case is to verify that platform_hal_getRotorLock API returns -1 when invoked with an invalid fanIndex value.
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
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getRotorLock with invalid fanIndex = 2 | fanIndex = 2 | Return -1 | Should return -1 as value is not applicable |
*/
void test_l1_platform_hal_negative1_getRotorLock(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getRotorLock...");
    int fanIndex = 2;

    UT_LOG("Invoking platform_hal_getRotorLock with invalid fanIndex = %d", fanIndex);
    INT status = platform_hal_getRotorLock(fanIndex);

    UT_LOG("platform_hal_getRotorLock returns : %d", status);
    if (status == -1)
    {
        UT_LOG("Status of the Rotor is: %d value not applicable ",status);
        UT_PASS("Get Rotor lock Validation success");
    }
    else if(status == 0 || status == 1)
    {
        UT_LOG("Status of the Rotor is: %d invalid value ",status);
        UT_FAIL("Get Rotor lock Validation Failed");
    }
    else
    {
        UT_LOG("Status of the Rotor is: %d  which is an invalid value",status);
        UT_FAIL("Get Rotor Validation failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_negative1_getRotorLock...");
}

/**
* @brief This test case verifies the functionality of the GetTotalMemorySize API by checking if it returns a positive value and does not return an error status.
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
* | :------: | ------- | --------- | ---------- | ----- |
* |01|Invoke the GetTotalMemorySize API with a valid buffer | size = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetTotalMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetTotalMemorySize...");
    ULONG size = 0;

    UT_LOG("Invoke the platform_hal_GetTotalMemorySize API with a valid buffer.");
    INT status = platform_hal_GetTotalMemorySize(&size);

    UT_LOG("platform_hal_GetTotalMemorySize returns : %d", status);
    UT_LOG("Returned total memory size: %lu", size);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(size > 0)
    {
        UT_LOG("Total Memory size is %lu which is a valid value.", size);
        UT_PASS("Get Total Memory size validation success");
    }
    else
    {
        UT_LOG("Total Memory size is %lu which is an invalid value.", size);
        UT_FAIL("Get Total Memory size validation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetTotalMemorySize...");
}

/**
* @brief This test case is used to verify the negative scenario of the platform_hal_GetTotalMemorySize function.
*
* This test case verifies whether the platform_hal_GetTotalMemorySize function returns an error status when the input parameter pulSize is NULL. It checks if the function behaves correctly in this scenario.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 054 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetTotalMemorySize with pulSize pointer = NULL | pulSize = NULL | RETURN_ERR | Should return an error status |
*/
void test_l1_platform_hal_negative1_GetTotalMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetTotalMemorySize...");
    ULONG *pulSize = NULL;

    UT_LOG("Invoking platform_hal_GetTotalMemorySize with pulSize pointer= NULL.");
    INT status = platform_hal_GetTotalMemorySize(pulSize);

    UT_LOG("platform_hal_GetTotalMemorySize returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetTotalMemorySize...");
}

/**
* @brief Test the platform_hal_GetFactoryResetCount function for positive scenarios.
*
* This test verifies the functionality of the platform_hal_GetFactoryResetCount function by invoking it and checking the return status and pulSize.
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
* | 01 | Invoking platform_hal_GetFactoryResetCount with pulSize = valid buffer | pulSize = valid buffer| RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive1_GetFactoryResetCount(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFactoryResetCount...");
    ULONG pulSize = 0;

    UT_LOG("Invoking platform_hal_GetFactoryResetCount with pulSize = valid buffer");
    INT status = platform_hal_GetFactoryResetCount(&pulSize);

    UT_LOG(" platform_hal_GetFactoryResetCount returns : %d",status);
    UT_LOG("pulSize: %lu",pulSize);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(pulSize >= 0)
    {
        UT_LOG("Factory Reset count is %lu", pulSize);
        UT_PASS (" Factory Reset Count Validation success");
    }
    else
    {
        UT_LOG("Factory Reset count is %lu", pulSize);
        UT_FAIL(" Factory Reset Count Validation Failure");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetFactoryResetCount...");
}

/**
* @brief Testing the platform_hal_GetFactoryResetCount function with NULL pulSize pointer
*
* The objective of this test is to verify the behavior of the platform_hal_GetFactoryResetCount function when the pulSize pointer is NULL. This test ensures that the function returns an error code as expected.
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
* | 01 | Invoking platform_hal_GetFactoryResetCount with pulSize = NULL| pulSize = NULL | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative1_GetFactoryResetCount(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFactoryResetCount...");
    ULONG *pulSize = NULL;

    UT_LOG("Invoking platform_hal_GetFactoryResetCount with pulSize = NULL");
    INT status = platform_hal_GetFactoryResetCount(pulSize);

    UT_LOG("platform_hal_GetFactoryResetCount returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetFactoryResetCount...");
}

/**
* @brief Verify that the platform_hal_SetDeviceCodeImageTimeout function sets the device code image timeout correctly.
*
* This test verifies that the platform_hal_SetDeviceCodeImageTimeout function sets the timeout value correctly for the device code image.
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
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01| Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value = 30 minutes(1800 sec) | timeout = 1800 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout...");
    INT timeout = 1800;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 30 minutes(1800 sec).");
    INT result = platform_hal_SetDeviceCodeImageTimeout(timeout);

    UT_LOG("platform_hal_SetDeviceCodeImageTimeout returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout...");
}

/**
* @brief This test is used to verify the functionality of the platform_hal_SetDeviceCodeImageTimeout function when provided with a timeout value of 0 minutes.
*
* The purpose of this test is to ensure that the platform_hal_SetDeviceCodeImageTimeout function correctly sets the device code image timeout value to 0 minutes and returns RETURN_OK.
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
* | :----: | --------- | ---------- | -----------| ----- |
* | 01 | Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 0 minutes| timeout = 0 minutes | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout...");
    INT timeout = 0;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 0 minutes");
    INT result = platform_hal_SetDeviceCodeImageTimeout(timeout);

    UT_LOG("platform_hal_SetDeviceCodeImageTimeout returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout...");
}

/**
* @brief Test to verify the functionality of the platform_hal_SetDeviceCodeImageTimeout API in positive scenario.
*
* This test verifies that the platform_hal_SetDeviceCodeImageTimeout API sets the device code image timeout correctly.
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
* | :----: | --------- | ---------- | -------------- | ------ |
* | 01 | Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 60 minutes(3600 sec) | timeout = 3600 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout...");
    INT timeout = 3600;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 60 minutes(3600 sec).");
    INT result = platform_hal_SetDeviceCodeImageTimeout(timeout);

    UT_LOG("platform_hal_SetDeviceCodeImageTimeout returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout...");
}

/**
* @brief This test case checks the behavior of the platform_hal_SetDeviceCodeImageTimeout function when called with a negative timeout value.
*
* In this test, the platform_hal_SetDeviceCodeImageTimeout function is called with a timeout value of -1 to test its behavior when an invalid timeout value is passed.
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
* | :-------: | --------- | --------- | --------- | ----------- |
* | 01| Invoking platform_hal_SetDeviceCodeImageTimeout with timeout = -1 | timeout = -1 | RETURN_ERR | Should be a failure |
*/
void test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout...");
    INT timeout = -1 ;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: -1");
    INT result = platform_hal_SetDeviceCodeImageTimeout(timeout);

    UT_LOG("platform_hal_SetDeviceCodeImageTimeout returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout...");
}

/**
* @brief This test case checks the functionality of setting device code image timeout.
*
* The platform_hal_SetDeviceCodeImageTimeout function is tested in this test case to verify if it correctly sets the device code image timeout.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes|
* | :--------: | --------- | --------- | --------- | -------- |
* | 01| Invoking platform_hal_SetDeviceCodeImageTimeout with timeout = 61 minutes | timeout = 3660 | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout...");
    INT timeout = 3660 ;

    UT_LOG("Invoking platform_hal_SetDeviceCodeImageTimeout with timeout value: 61 minutes");
    INT result = platform_hal_SetDeviceCodeImageTimeout(timeout);

    UT_LOG("platform_hal_SetDeviceCodeImageTimeout returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout...");
}

/**
* @brief Test case to verify the functionality of platform_hal_getFactoryCmVariant API.
*
* This test case verifies the functionality of the platform_hal_getFactoryCmVariant API by invoking it with a valid buffer of size 512 bytes and checking the return status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 062 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :-----------: | ----------- | ----------- | ---------| ------- |
* |01| Invoke the platform_hal_getFactoryCmVariant API buffer = valid buffer| buffer = valid buffer| RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive1_getFactoryCmVariant(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getFactoryCmVariant...");
    CHAR buffer[512] = {"\0"};

    UT_LOG("Invoking platform_hal_getFactoryCmVariant with a valid buffer ...");
    INT status = platform_hal_getFactoryCmVariant(buffer);

    UT_LOG("platform_hal_getFactoryCmVariant returns : %d", status);
    UT_LOG("Value of buffer : %s", buffer);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if (!strcmp(buffer,"unknown") || !strcmp(buffer,"pc20") || !strcmp(buffer,"pc20genband") || !strcmp(buffer,"pc15sip")||  !strcmp(buffer,"pc15mgcp"))
    {
        UT_LOG("FactoryCmVariant %s which is a valid value",buffer);
        UT_PASS("getFactoryCmVariant validation success");
    }
    else
    {
        UT_LOG("FactoryCmVariant %s which is a Invalid value",buffer);
        UT_FAIL("getFactoryCmVariantvalidation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFactoryCmVariant...");
}

/**
* @brief Test case to verify the behavior of platform_hal_getFactoryCmVariant when a null pointer is passed as the parameter.
*
* This test case checks whether platform_hal_getFactoryCmVariant function returns RETURN_ERR when a null pointer is passed as the parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 063 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getFactoryCmVariant with buffer = NULL | buffer = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_getFactoryCmVariant(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getFactoryCmVariant...");
    CHAR *buffer = NULL;

    UT_LOG("Invoking platform_hal_getFactoryCmVariant with buffer = NULL.");
    INT status = platform_hal_getFactoryCmVariant(buffer);

    UT_LOG("platform_hal_getFactoryCmVariant returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getFactoryCmVariant...");
}

/**
* @brief This test is to verify the platform_hal_setLed function with valid parameters.
*
* This test covers the scenario where the platform_hal_setLed function is called with valid parameters (LedColor, State, and Interval). The objective of this test is to ensure that the function is able to set the LED to the specified color, state, and interval successfully.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 064 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_setLed with valid params structure | LedColor = 0-6, State = 0-1, Interval = 0,1,3,5 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_setLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_setLed...");
    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));
    if (pValue != NULL)
    {
        for (int ledColor = 0; ledColor <= 6; ledColor++)
        {
            for (int state = 0; state <= 1; state++)
            {
                for (int interval = 0; interval <= 5; interval++)
                {
                    if(interval == 0 || interval == 1 ||interval == 3 || interval == 5)
                    {
                        pValue->LedColor = ledColor;
                        pValue->State = state;
                        pValue->Interval = interval;

                        UT_LOG("Invoking platform_hal_setLed with LedColor: %d, State: %d, Interval: %d", ledColor, state, interval);
                        INT result = platform_hal_setLed(pValue);
                        UT_LOG("platform_hal_setLed returns: %d",result);
                        UT_ASSERT_EQUAL(result, RETURN_OK);
                    }
                }
            }
        }
        free(pValue);
        pValue = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_setLed...");
}

/**
* @brief This test case is used to verify the behavior of the platform_hal_setLed function when a NULL pointer is passed as an argument.
*
* The purpose of this test is to ensure that the function handles the NULL pointer gracefully and returns the expected result.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setLed with pValue = NULL | pValue = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_setLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_setLed...");
    PLEDMGMT_PARAMS pValue = NULL;

    UT_LOG("Invoking platform_hal_setLed with pValue = NULL");
    INT result = platform_hal_setLed(pValue);

    UT_LOG("platform_hal_setLed returns: %d",result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setLed...");
}

/**
* @brief Unit test to verify the behavior of the platform_hal_setLed function when an invalid LedColor value is provided.
*
* This test case verifies the behavior of the platform_hal_setLed function when an invalid LedColor value (8) is provided. The test checks if the function returns the expected error code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 066 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* Test Procedure: ** @n
* | Variation / Step | Description | Test Data | Expected Result| Notes|
* | :---------: | ---------| -------------| -------- | ------- |
* |01| Invoking platform_hal_setLed with invalid LedColor value = 8, valid State = 0, valid Interval = 10|  LedColor = 8, State = 0, Interval = 10 | RETURN_ERR | Should be successful |
*/
void test_l1_platform_hal_negative2_setLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_setLed...");
    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));

    if (pValue != NULL)
    {
        pValue->LedColor = 8;
        pValue->State = 0;
        pValue->Interval = 10;
        UT_LOG("Invoking platform_hal_setLed with invalid LedColor value = %d,valid State = %d, valid Interval = %d.",pValue->LedColor, pValue->State, pValue->Interval);
        INT result = platform_hal_setLed(pValue);

        UT_LOG("platform_hal_setLed returns: %d",result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(pValue);
        pValue = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative2_setLed...");
}

/**
* @brief This test case is used to verify the behavior of the platform_hal_setLed function when an invalid state is passed as an argument.
*
* This test verifies that the platform_hal_setLed function returns an error code (RETURN_ERR) when an invalid state  value is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 067 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setLed with invalid State value = 2, valid LedColor = 1 and  valid Interval = 10 | LedColor = 1, State = 2, Interval = 10 | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative3_setLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_setLed...");
    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));
    if (pValue != NULL)
    {
        pValue->LedColor = 1;
        pValue->State = 2;
        pValue->Interval = 10;

        UT_LOG("Invoking platform_hal_setLed with invalid State value = 2, valid LedColor = 1 and  valid Interval = 10.");
        INT result = platform_hal_setLed(pValue);

        UT_LOG("platform_hal_setLed returns: %d",result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);
        free(pValue);
        pValue = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative3_setLed...");
}

/**
* @brief This test case is used to verify the behavior of the platform_hal_setLed function when a negative Interval value (-1) is passed as an argument.
*
* This test verifies that the platform_hal_setLed function returns an error code (RETURN_ERR) when a negative Interval value is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 068 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setLed with invalid Interval value = -1, LedColor = 1 and State = 0 | pValue->LedColor = 1, pValue->State = 0, pValue->Interval = -1 | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative4_setLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative4_setLed...");

    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));
    if(pValue != NULL)
    {
        pValue->LedColor = 1;
        pValue->State = 0;
        pValue->Interval = -1;

        UT_LOG("Invoking platform_hal_setLed with invalid Interval value = %d, valid LedColor = %d and State =%d",pValue->Interval,pValue->LedColor,pValue->State);
        INT result = platform_hal_setLed(pValue);

        UT_LOG("platform_hal_setLed returns: %d",result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);
        free(pValue);
        pValue = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative4_setLed...");
}

/**
* @brief This test is to verify the platform_hal_setLed function with invalid enum LedColour as NOT_SUPPORTED.
*
* This test covers the scenario where the platform_hal_setLed function is called with invalid Led colour enum as NOT_SUPPORTED , valid State, and Interval. The objective of this test is to ensure that the function is able to handle the invalid Led color successfully.
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
* | 01 | Invoking platform_hal_setLed with invalid Led colour enum as NOT_SUPPORTED , valid State, and Interval | LedColor = 7, State = 0-1, Interval = 0,1,3,5 | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative5_setLed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative5_setLed...");
    INT result = 0;
    PLEDMGMT_PARAMS pValue = (PLEDMGMT_PARAMS)malloc(sizeof(LEDMGMT_PARAMS));
    if (pValue != NULL)
    {
        pValue->LedColor = 7;
        for (int state = 0; state <= 1; state++)
        {
            for (int interval = 0; interval <= 5; interval++)
            {
                if(interval == 0 || interval == 1 ||interval == 3 || interval == 5)
                {
                    pValue->State = state;
                    pValue->Interval = interval;

                    UT_LOG("Invoking platform_hal_setLed with invalid LedColor: %d, valid State: %d, valid Interval: %d", pValue->LedColor, pValue->State, pValue->Interval);
                    result = platform_hal_setLed(pValue);
                    UT_LOG("platform_hal_setLed returns: %d",result);
                    UT_ASSERT_EQUAL(result, RETURN_ERR);
                    }
                }
            }
        free(pValue);
        pValue = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative5_setLed...");
}

/**
* @brief Test case to validate the platform_hal_getRPM function.
*
* This test case verifies the correctness of the platform_hal_getRPM function by invoking it with different fanIndex from config file and checking the returned value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 070 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking getRPM function with fanIndex from config file | fanIndex from config file | fanRPM >= 0 | Should pass |
*/
void test_l1_platform_hal_positive1_getRPM(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getRPM...");
    int i = 0;
    UINT fanRPM = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_getRPM with fanIndex = %d", FanIndex[i]);
        fanRPM = platform_hal_getRPM(FanIndex[i]);

        UT_LOG("FanRPM = %d", fanRPM);
        if(fanRPM >= 0)
        {
            UT_LOG("RPM is %d which is a valid value.", fanRPM);
            UT_PASS("Get RPM validation success");
        }
        else
        {
            UT_LOG("RPM is %d which is an invalid value.", fanRPM);
            UT_FAIL("Get RPM validation failed");
        }
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getRPM...");
}

#ifdef FEATURE_RDKB_THERMAL_MANAGER
/**
* @brief This test case verifies the functionality of the platform_hal_initThermal function in the platform_hal module.
*
* The objective of this test is to ensure that the platform_hal_initThermal function initializes the thermal platform configuration correctly and returns the expected status value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 071 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* |01 | Invoke the platform_hal_initThermal function with thermalConfig = valid structure | thermalConfig = valid structure | RETURN_OK | Should be successful|
*/
void test_l1_platform_hal_positive1_initThermal(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_initThermal...");
    THERMAL_PLATFORM_CONFIG *thermalConfig = (THERMAL_PLATFORM_CONFIG*)malloc(sizeof(THERMAL_PLATFORM_CONFIG));
    if(thermalConfig != NULL)
    {
        UT_LOG("Invoking platform_hal_initThermal with thermalConfig = valid structure ");
        INT result = platform_hal_initThermal(thermalConfig);

        UT_LOG("platform_hal_initThermal returns:%d",result);
        UT_ASSERT_EQUAL(result, RETURN_OK);

        UT_LOG("Values are Fan count : %d, Slow Speed Thresh: %d, MediumSpeedThresh : %d, Fast Speed Thresh : %d, FanMinRunTime : %d, MonitoringDelay : %d, PowerMonitoring : %d, LogInterval : %d",thermalConfig->FanCount, thermalConfig->SlowSpeedThresh, thermalConfig->MediumSpeedThresh, thermalConfig->FastSpeedThresh, thermalConfig->FanMinRunTime, thermalConfig->MonitoringDelay, thermalConfig->PowerMonitoring, thermalConfig->LogInterval);

        if (thermalConfig->FanCount == 1 || thermalConfig->FanCount == 2)
        {
            UT_LOG("Fan Count is %d which is a valid value", thermalConfig->FanCount);
            UT_PASS("Fan Count validation success");
        }
        else
        {
            UT_LOG("Fan Count is %d which is an invalid value", thermalConfig->FanCount);
            UT_FAIL("Fan Count validation failed");
        }

        if (thermalConfig->PowerMonitoring == 0 || thermalConfig->PowerMonitoring == 1)
        {
            UT_LOG("Power Monitoring is %d which is a valid value", thermalConfig->PowerMonitoring);
            UT_PASS("Power Monitoring validation success");
        }
        else
        {
            UT_LOG("Power Monitoring is %d which is an invalid value", thermalConfig->PowerMonitoring);
            UT_FAIL("Power Monitoring validation failed");
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_initThermal...");
}

/**
* @brief This test is to verify the behavior of the platform_hal_initThermal function when invoked with a NULL input parameter.
*
* This test verifies that the platform_hal_initThermal function returns RETURN_ERR when invoked with a NULL input parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 072 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_initThermal with thermalConfig = NULL | thermalConfig = NULL | RETURN_ERR | Should return RETURN_ERR |
*/
void test_l1_platform_hal_negative1_initThermal(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_initThermal...");
    THERMAL_PLATFORM_CONFIG* thermalConfig = NULL;

    UT_LOG("Invoking platform_hal_initThermal with thermalConfig = NULL.");
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
* **Test Case ID:** 073 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description| Test Data | Expected Result | Notes|
* | :----------: | ----------| ----------- | ------ | ------- |
* |01|Invoking platform_hal_getFanTemperature with a valid buffer | temp = valid buffer| RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_getFanTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getFanTemperature...");
    int temp = 0;

    UT_LOG("Invoking platform_hal_getFanTemperature with a valid buffer");
    int status = platform_hal_getFanTemperature(&temp);

    UT_LOG("platform_hal_getFanTemperature returns : %d", status);
    UT_LOG("Temperature Value: %d", temp);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(temp >= 0 && temp <= 100)
    {
        UT_LOG("Fan Temperature  is %d", temp);
        UT_PASS (" Fan Temperature Validation success");
    }
    else
    {
        UT_LOG("Fan Temperature is %d", temp);
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
* **Test Case ID:** 074 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getFanTemperature with temp = NULL | temp = NULL | RETURN_ERR | Should return an error status |
*/
void test_l1_platform_hal_negative1_getFanTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getFanTemperature...");
    INT *temp = NULL;
    UT_LOG("Invoking platform_hal_getFanTemperature with pTemp = NULL");
    int status = platform_hal_getFanTemperature(temp);

    UT_LOG("platform_hal_getFanTemperature returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getFanTemperature...");
}

/**
* @brief Test case to verify the functionality of platform_hal_getRadioTemperature API
*
* This test case is used to verify the functionality of the platform_hal_getRadioTemperature API.
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
* | Variation / Step | Description| Test Data| Expected Result| Notes |
* | :---------: | --------| --------| --------| --------|
* | 01| Invoking platform_hal_getRadioTemperature with radioIndex = 0, value = valid buffer| radioIndex = 0, value = valid buffer| RETURN_OK|  Should be successful|
*/
void test_l1_platform_hal_positive1_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getRadioTemperature...");
    INT radioIndex = 0;
    INT value = 0;

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex = %d, value = valid buffer.", radioIndex);
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("platform_hal_getRadioTemperature returns : %d", status);
    UT_LOG("Radio Temperature: %d", value);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if(value >= 0 && value <= 100)
    {
        UT_LOG("Radio Temperature  is %d", value);
        UT_PASS (" Radio Temperature Validation success");
    }
    else
    {
        UT_LOG("Radio Temperature is %d", value);
        UT_FAIL(" Radio Temperature Validation Failure");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_getRadioTemperature...");
}

/**
* @brief Test to validate the platform_hal_getRadioTemperature function with negative input.
*
* This test case verifies the behavior of the platform_hal_getRadioTemperature function when negative input values are provided.
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
* | Variation / Step | Description|Test Data| Expected Result| Notes|
* | :-------:| ---------| ----------|--------------| -----|
* | 01| Invoking platform_hal_getRadioTemperature with radioIndex = 1, value = NULL| radioIndex = 1, value = NULL| RETURN_ERR| Should be failed |
*/
void test_l1_platform_hal_negative1_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getRadioTemperature...");
    INT radioIndex = 1;
    INT* value = NULL;

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex = %d, value = NULL.", radioIndex);
    INT status = platform_hal_getRadioTemperature(radioIndex, value);

    UT_LOG("platform_hal_getRadioTemperature returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getRadioTemperature...");
}

/**
* @brief Test to check the functionality of platform_hal_getRadioTemperature in case of negative scenario.
*
* This test verifies the behavior of platform_hal_getRadioTemperature API when a negative scenario is encountered.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 077 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getRadioTemperature with invalid radioIndex = 3, value = valid buffer| radioIndex = 3, value = valid buffer | RETURN_ERR | API should return an error status |
*/
void test_l1_platform_hal_negative2_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_getRadioTemperature...");
    INT radioIndex = 3;
    INT value = 0 ;

    UT_LOG("Invoking platform_hal_getRadioTemperature with invalid radioIndex = %d, value = valid buffer.", radioIndex);
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("platform_hal_getRadioTemperature returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_getRadioTemperature...");
}

/**
* @brief Test to validate the functionality of the platform_hal_getRadioTemperature API
*
* This test is used to verify the correctness of the platform_hal_getRadioTemperature API. The API is responsible for retrieving the temperature of a given radio identified by its index.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* |01| Invoking platform_hal_getRadioTemperature with radioIndex = 1, value = valid buffer|radioIndex = 1, value = valid buffer|RETURN_OK|Should be successful|
*/
void test_l1_platform_hal_positive2_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_getRadioTemperature...");
    INT radioIndex = 1;
    INT value = 0;

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex = %d, value = valid buffer.", radioIndex);
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("platform_hal_getRadioTemperature returns: %d", status);
    UT_LOG("Radio Temperature: %d", value);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if(value >= 0 && value <= 100)
    {
        UT_LOG("Radio Temperature  is %d", value);
        UT_PASS (" Radio Temperature Validation success");
    }
    else
    {
        UT_LOG("Radio Temperature is %d", value);
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
* **Test Case ID:** 079 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step| Description | Test Data | Expected Result| Notes|
* | :-------: | ----------- | ----------- | ---------- | ------|
* | 01| Invoking platform_hal_getRadioTemperature with radioIndex = 2, value = valid buffer| radioIndex = 2, value = valid buffer| RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive3_getRadioTemperature(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_getRadioTemperature...");
    INT radioIndex = 2;
    INT value = 0;

    UT_LOG("Invoking platform_hal_getRadioTemperature with radioIndex = %d, value = valid buffer.", radioIndex);
    INT status = platform_hal_getRadioTemperature(radioIndex, &value);

    UT_LOG("platform_hal_getRadioTemperature returns: %d", status);
    UT_LOG("Radio Temperature: %d", value);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if(value >= 0 && value <= 100)
    {
        UT_LOG("Radio Temperature  is %d", value);
        UT_PASS (" Radio Temperature Validation success");
    }
    else
    {
        UT_LOG("Radio Temperature is %d", value);
        UT_FAIL(" Radio Temperature Validation Failure");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive3_getRadioTemperature...");
}

/**
 * @brief Test case to verify the platform_hal_getEcoModeStatus() function
 * for radioIndex 0 (2.4GHz WiFi) with ECO mode disabled.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 080 @n
 * **Priority:** High @n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_getEcoModeStatus() with radioIndex = 0 | radioIndex = 0 | RETURN_OK, pValue = 0 | ECO mode should be disabled for 2.4GHz WiFi |
 */
void test_l1_platform_hal_positive1_platform_hal_getEcoModeStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_platform_hal_getEcoModeStatus...");

    INT pValue = 0;
    INT radioIndex = 0;

    UT_LOG("Invoking platform_hal_getEcoModeStatus() with radioIndex = %d", radioIndex);
    INT status = platform_hal_getEcoModeStatus(radioIndex, &pValue);

    UT_LOG("ECO Mode Status: %d", pValue);
    UT_LOG("platform_hal_getEcoModeStatus API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(pValue, 0);  // ECO mode should be disabled

    UT_LOG("Exiting test_l1_platform_hal_positive1_platform_hal_getEcoModeStatus...");
}

/**
 * @brief Test case to verify the platform_hal_getEcoModeStatus() function
 * for radioIndex 1 (5GHz WiFi) with ECO mode enabled.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 081 @n
 * **Priority:** High @n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_getEcoModeStatus() with radioIndex = 1 | radioIndex = 1 | RETURN_OK, pValue = 1 | ECO mode should be enabled for 5GHz WiFi |
 */
void test_l1_platform_hal_positive2_platform_hal_getEcoModeStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_platform_hal_getEcoModeStatus...");

    INT pValue = 0;
    INT radioIndex = 1;

    UT_LOG("Invoking platform_hal_getEcoModeStatus() with radioIndex = %d", radioIndex);
    INT status = platform_hal_getEcoModeStatus(radioIndex, &pValue);

    UT_LOG("ECO Mode Status: %d", pValue);
    UT_LOG("platform_hal_getEcoModeStatus API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_ASSERT_EQUAL(pValue, 1);  // ECO mode should be enabled

    UT_LOG("Exiting test_l1_platform_hal_positive2_platform_hal_getEcoModeStatus...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_getEcoModeStatus() 
 * when a valid radio index is passed with a large pointer value for pValue.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 082 @n
 * **Priority:** Low @n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_getEcoModeStatus() with radioIndex = 0 and large pointer value | radioIndex = 0 | RETURN_OK, pValue = 0 | ECO mode should be disabled for 2.4GHz WiFi |
 */
void test_l1_platform_hal_positive3_platform_hal_getEcoModeStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_platform_hal_getEcoModeStatus...");

    INT pValue = 0;
    INT radioIndex = 0;  // Valid radio index

    UT_LOG("Invoking platform_hal_getEcoModeStatus() with radioIndex = %d", radioIndex);
    INT status = platform_hal_getEcoModeStatus(radioIndex, &pValue);

    UT_LOG("ECO Mode Status: %d", pValue);
    UT_LOG("platform_hal_getEcoModeStatus API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);  // Expected to return OK
    UT_ASSERT_EQUAL(pValue, 0);  // ECO mode should be disabled

    UT_LOG("Exiting test_l1_platform_hal_positive3_platform_hal_getEcoModeStatus...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_getEcoModeStatus() 
 * when an invalid radioIndex (2) is provided.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 083 @n
 * **Priority:** High @n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_getEcoModeStatus() with an invalid radioIndex | radioIndex = 2 | RETURN_ERR | Error should be returned due to invalid index |
 */
void test_l1_platform_hal_negative1_platform_hal_getEcoModeStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_platform_hal_getEcoModeStatus...");

    INT pValue = 0;
    INT radioIndex = 2;  // Invalid radio index

    UT_LOG("Invoking platform_hal_getEcoModeStatus() with radioIndex = %d", radioIndex);
    INT status = platform_hal_getEcoModeStatus(radioIndex, &pValue);

    UT_LOG("platform_hal_getEcoModeStatus API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);  // Error should be returned for invalid index

    UT_LOG("Exiting test_l1_platform_hal_negative1_platform_hal_getEcoModeStatus...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_getEcoModeStatus() 
 * when a NULL pointer is passed for pValue.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 084 @n
 * **Priority:** High @n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_getEcoModeStatus() with NULL pointer for pValue | pValue = NULL | RETURN_ERR | Error should be returned due to NULL pointer |
 */
void test_l1_platform_hal_negative2_platform_hal_getEcoModeStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_platform_hal_getEcoModeStatus...");

    INT radioIndex = 0;  // Valid radio index
    INT* pValue = NULL;  // NULL pointer for pValue

    UT_LOG("Invoking platform_hal_getEcoModeStatus() with radioIndex = %d", radioIndex);
    INT status = platform_hal_getEcoModeStatus(radioIndex, pValue);

    UT_LOG("platform_hal_getEcoModeStatus API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);  // Error should be returned due to NULL pointer

    UT_LOG("Exiting test_l1_platform_hal_negative2_platform_hal_getEcoModeStatus...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_getEcoModeStatus() 
 * when pValue is set to zero.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 085 @n
 * **Priority:** Medium @n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_getEcoModeStatus() with pValue = 0 | pValue = 0 | RETURN_OK | ECO mode should be enabled for 5GHz WiFi |
 */
void test_l1_platform_hal_negative3_platform_hal_getEcoModeStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_platform_hal_getEcoModeStatus...");

    INT pValue = 0;
    INT radioIndex = 1;  // Valid radio index

    UT_LOG("Invoking platform_hal_getEcoModeStatus() with radioIndex = %d", radioIndex);
    INT status = platform_hal_getEcoModeStatus(radioIndex, &pValue);

    UT_LOG("ECO Mode Status: %d", pValue);
    UT_LOG("platform_hal_getEcoModeStatus API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);  // Expected to return OK
    UT_ASSERT_EQUAL(pValue, 1);  // ECO mode should be enabled

    UT_LOG("Exiting test_l1_platform_hal_negative3_platform_hal_getEcoModeStatus...");
}

/**
 * @brief Test case to verify the behavior of platform_hal_getEcoModeStatus() 
 * when a negative radioIndex is passed.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 086 @n
 * **Priority:** High @n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_getEcoModeStatus() with a negative radioIndex | radioIndex = -1 | RETURN_ERR | Error should be returned for invalid negative index |
 */
void test_l1_platform_hal_negative4_platform_hal_getEcoModeStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative4_platform_hal_getEcoModeStatus...");

    INT pValue = 0;
    INT radioIndex = -1;  // Invalid negative radio index

    UT_LOG("Invoking platform_hal_getEcoModeStatus() with radioIndex = %d", radioIndex);
    INT status = platform_hal_getEcoModeStatus(radioIndex, &pValue);

    UT_LOG("platform_hal_getEcoModeStatus API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);  // Error should be returned due to invalid index

    UT_LOG("Exiting test_l1_platform_hal_negative4_platform_hal_getEcoModeStatus...");
}

#endif

/**
* @brief Unit test for the platform_hal_SetMACsecEnable function.
*
* The objective of this test is to verify the functionality of the platform_hal_SetMACsecEnable function in setting the MACsec enable flag for a given Ethernet port.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 087 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None  @n
* **Dependencies:** None  @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :-------: | ----------- | --------- | --------------- | ----- |
* |01| Invoking platform_hal_SetMACsecEnable with ethPort = 0, Flag = 1 | ethPort = 0, Flag = 1 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_SetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetMACsecEnable...");
    INT ethPort = 0;
    BOOLEAN Flag = 1;

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("platform_hal_SetMACsecEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetMACsecEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetMACsecEnable function.
*
* The test case verifies that the platform_hal_SetMACsecEnable function sets the MACsec enable flag correctly for the specified ethernet port.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_SetMACsecEnable with ethPort = 0, Flag = 0| ethPort = 0, Flag = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetMACsecEnable...");
    INT ethPort = 0;
    BOOLEAN Flag = 0;

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("platform_hal_SetMACsecEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetMACsecEnable...");
}

/**
* @brief Test case to verify the negative scenario where the platform_hal_SetMACsecEnable API is invoked with ethPort = -1 and Flag = 1.
*
* This test case is used to validate the behavior of the platform_hal_SetMACsecEnable API when called with invalid ethPort value and Flag value as 1.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 089 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 1|Invoking platform_hal_SetMACsecEnable API with invalid ethPort = -1 and Flag = 1| ethPort = -1, Flag = 1| RETURN_ERR|Should return error status|
*/
void test_l1_platform_hal_negative1_SetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetMACsecEnable...");
    INT ethPort = -1;
    BOOLEAN Flag = 1;

    UT_LOG("Invoking platform_hal_SetMACsecEnable with invalid ethPort = %d, Flag = %d", ethPort, Flag);
    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("platform_hal_SetMACsecEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetMACsecEnable...");
}

/**
* @brief This function tests the functionality of the platform_hal_SetMACsecEnable() API.
*
* This test case validates the ability of the API to set the MACsec enable flag for a given Ethernet port.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 090 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description| Test Data | Expected Result| Notes|
* | :---------: | -----------| ------------| ---------| -------|
* | 01| Invoking platform_hal_SetMACsecEnable with ethPort = MaxEthPort-1 ,Flag = 1| ethPort = MaxEthPort-1, Flag = 1| RETURN_OK| Should be successful|
*/
void test_l1_platform_hal_positive3_SetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_SetMACsecEnable...");
    //MaxEthPort should be configured in platform_config file
    INT ethPort = MaxEthPort-1;
    BOOLEAN Flag = 1;

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, Flag = %d", ethPort, Flag);
    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("platform_hal_SetMACsecEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_SetMACsecEnable...");
}

/**
* @brief Test function to validate the platform_hal_SetMACsecEnable API in negative scenario
*
* This test case is to verify the behavior of platform_hal_SetMACsecEnable API when it is provided with invalid input values.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 091 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01| Invoking platform_hal_SetMACsecEnable with ethPort = 0, invalid Flag = 2| ethPort = 0, Flag = 2| RETURN_ERR | Should produce an error |
*/
void test_l1_platform_hal_negative2_SetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetMACsecEnable...");
    INT ethPort = 0;
    BOOLEAN Flag = 2;

    UT_LOG("Invoking platform_hal_SetMACsecEnable with ethPort = %d, invalid Flag = %d.", ethPort, Flag);
    INT status = platform_hal_SetMACsecEnable(ethPort, Flag);

    UT_LOG("platform_hal_SetMACsecEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetMACsecEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_GetMemoryPaths() API when called with valid index from config file.
*
* The objective of this test is to ensure that the API returns the expected results and does not encounter any errors.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 092 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* |01| Invoking platform_hal_GetMemoryPaths with index from config file, ppinfo = valid pointer| index from config file, ppinfo = valid pointer| RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetMemoryPaths(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetMemoryPaths...");
    PPLAT_PROC_MEM_INFO ppinfo = (PPLAT_PROC_MEM_INFO)malloc(sizeof(PLAT_PROC_MEM_INFO));
    INT result = 0;
    int i = 0;
    if (ppinfo != NULL)
    {
        memset(ppinfo, 0, sizeof(PLAT_PROC_MEM_INFO));
        for(i=0;i<num_SupportedCPUs; i++)
        {
            //Supported_CPUS should be configured in platform_config file
            UT_LOG("Invoking platform_hal_GetMemoryPaths with index = %d, ppinfo = valid pointer",supportedCpus[i]);
            result = platform_hal_GetMemoryPaths(supportedCpus[i], &ppinfo);

            UT_LOG("platform_hal_GetMemoryPaths returns : %d", result);
            UT_ASSERT_EQUAL(result, RETURN_OK);
            UT_ASSERT_PTR_NOT_NULL(ppinfo);
            UT_LOG("Values in the structure are, dramPath: %s, emmcpath1: %s, emmcPath2: %s", ppinfo->dramPath, ppinfo->emmcPath1,ppinfo->emmcPath2);

            UT_ASSERT_STRING_EQUAL(ppinfo->dramPath, "/tmp");
            UT_ASSERT_STRING_EQUAL(ppinfo->emmcPath1, "/nvram");
            UT_ASSERT_STRING_EQUAL(ppinfo->emmcPath2, "/nvram2");

            free(ppinfo);
            ppinfo = NULL;
        }
    }
    else
    {
        UT_LOG("Malloc operation Failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetMemoryPaths...");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetMemoryPaths function when provided with an invalid CPU index.
*
* This test case verifies that the platform_hal_GetMemoryPaths function returns an error when called with an invalid CPU index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 093 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* | :----:| ---------| ----------|--------------| ----- |
* | 01| Invoking platform_hal_GetMemoryPaths with invalid index = NOT_SUPPORTED_CPU, ppinfo = valid pointer| index = NOT_SUPPORTED_CPU, ppinfo = valid pointer| RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetMemoryPaths(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetMemoryPaths...");
    RDK_CPUS index = NOT_SUPPORTED_CPU;

    PPLAT_PROC_MEM_INFO ppinfo = (PPLAT_PROC_MEM_INFO)malloc(sizeof(PLAT_PROC_MEM_INFO));
    if (ppinfo != NULL)
    {
        UT_LOG("Invoking platform_hal_GetMemoryPaths with invalid index = %d, ppinfo = valid pointer",index);
        INT result = platform_hal_GetMemoryPaths(index, &ppinfo);

        UT_LOG("platform_hal_GetMemoryPaths returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(ppinfo);
        ppinfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetMemoryPaths...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_GetMemoryPaths function when a null pointer is passed as an argument.
*
* This test case checks whether the platform_hal_GetMemoryPaths function handles the case when a null pointer is passed as the ppinfo argument. The objective of this test is to ensure that the function returns RETURN_ERR when a null pointer is provided.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 094 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01| Invoking platform_hal_GetMemoryPaths with index = HOST_CPU, ppinfo = NULL| index = HOST_CPU, ppinfo = NULL|RETURN_ERR | The function should return RETURN_ERR |
*/
void test_l1_platform_hal_negative2_GetMemoryPaths(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetMemoryPaths...");

    RDK_CPUS index = HOST_CPU;
    PPLAT_PROC_MEM_INFO *ppinfo = NULL;

    UT_LOG("Invoking platform_hal_GetMemoryPaths with index = %d, ppinfo = NULL",index);
    INT result = platform_hal_GetMemoryPaths(index, ppinfo);

    UT_LOG("platform_hal_GetMemoryPaths returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetMemoryPaths...");
}

/**
* @brief Test to verify the behavior of the function platform_hal_GetMemoryPaths for an out of bounds CPU index
*
* This test case is used to verify the behavior of the platform_hal_GetMemoryPaths function when it is given an out of bounds CPU index. The out of bounds CPU index is defined as a value greater than the total number of available CPUs.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 095 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :-------: | ------- |---------| ----------| -----|
* | 01| Invoking platform_hal_GetMemoryPaths with invalid index = 4, ppinfo = valid pointer| index = 4, ppinfo = valid pointer| RETURN_ERR | Function should return an error |
*/
void test_l1_platform_hal_negative3_GetMemoryPaths(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_GetMemoryPaths...");
    RDK_CPUS index = 4;
    PPLAT_PROC_MEM_INFO ppinfo = (PPLAT_PROC_MEM_INFO)malloc(sizeof(PLAT_PROC_MEM_INFO));
    if (ppinfo != NULL)
    {
        UT_LOG("Invoking platform_hal_GetMemoryPaths with invalid index = %d , ppinfo = valid pointer", index);
        INT result = platform_hal_GetMemoryPaths(index, &ppinfo);

        UT_LOG("platform_hal_GetMemoryPaths returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(ppinfo);
        ppinfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative3_GetMemoryPaths...");
}

/**
* @brief Test to verify the normal operation of the platform_hal_GetMACsecEnable function.
*
* This test checks whether the platform_hal_GetMACsecEnable function is able to successfully retrieve the MACsec enable status for a given ethernet port.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* |01| Invoking platform_hal_GetMACsecEnable with valid ethPort = 0 and flag = valid buffer | ethPort = 0 and flag = valid buffer| RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetMACsecEnable...");
    INT ethPort = 0;
    BOOLEAN flag = FALSE;

    UT_LOG("Invoking platform_hal_GetMACsecEnable with valid ethPort = %d and flag = valid buffer.", ethPort);
    INT status = platform_hal_GetMACsecEnable(ethPort, &flag);

    UT_LOG("platform_hal_GetMACsecEnable returns :  %d", status);
    UT_LOG("MACsec Enable: %d", flag);
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
* **Test Case ID:** 097 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetMACsecEnable with valid ethPort = 0 with NULL pFlag | ethPort = 0, pFlag = NULL | RETURN_ERR | Should return an error code |
*/
void test_l1_platform_hal_negative1_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_etMACsecEnable...");
    INT ethPort = 0;
    BOOLEAN *pFlag = NULL;

    UT_LOG("Invoking platform_hal_GetMACsecEnable with valid ethPort = %d with NULL pFlag .", ethPort);
    INT status = platform_hal_GetMACsecEnable(ethPort, pFlag);

    UT_LOG("platform_hal_GetMACsecEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetMACsecEnable...");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetMACsecEnable() when an invalid Ethernet port is provided as input.
*
* This test case checks the functionality of platform_hal_GetMACsecEnable() function when an invalid Ethernet port is provided as input. This test is important to ensure that the function handles invalid input correctly and returns the expected error status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 098 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 |Invoking platform_hal_GetMACsecEnable with invalid ethPort = -1, flag = valid buffer| ethPort = -1, flag = valid buffer|RETURN_ERR| Should return error|
*/
void test_l1_platform_hal_negative2_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetMACsecEnable...");
    INT ethPort = -1;
    BOOLEAN flag = FALSE;

    UT_LOG("Invoking platform_hal_GetMACsecEnable with invalid ethPort = %d, flag = valid buffer.", ethPort);
    INT status = platform_hal_GetMACsecEnable(ethPort, &flag);

    UT_LOG("platform_hal_GetMACsecEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetMACsecEnable...");
}

/**
* @brief This test case checks the behavior of the 'platform_hal_GetMACsecEnable' function for the highest Ethernet port.
*
* This test verifies whether the 'platform_hal_GetMACsecEnable' function returns the expected status when invoked with the highest Ethernet port.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 099 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking platform_hal_GetMACsecEnable with valid ethPort = MaxEthPort-1, flag = valid buffer| ethPort = MaxEthPort-1, flag = valid buffer |RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_GetMACsecEnable...");
    //MaxEthPort should be configured in platform_config file
    INT ethPort = MaxEthPort-1;
    BOOLEAN flag = FALSE;

    UT_LOG("Invoking platform_hal_GetMACsecEnable with valid ethPort = %d flag = valid buffer.", ethPort);
    INT status = platform_hal_GetMACsecEnable(ethPort, &flag);

    UT_LOG("platform_hal_GetMACsecEnable returns : %d", status);
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
* @brief This test case checks the behavior of the 'platform_hal_GetMACsecEnable' function for the highest Ethernet port.
*
* This test verifies whether the 'platform_hal_GetMACsecEnable' function returns the expected status when invoked with the highest Ethernet port.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 100 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking platform_hal_GetMACsecEnable with valid ethPort = valid value, flag = valid buffer | ethPort = valid value, flag = valid buffer |RETURN_OK |Should be successful|
*/
void test_l1_platform_hal_positive3_GetMACsecEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_GetMACsecEnable...");
    //MaxEthPort should be configured in platform_config file
    int ethPort = rand() % (MaxEthPort-1);
    BOOLEAN flag = FALSE;

    UT_LOG("Invoking platform_hal_GetMACsecEnable with valid ethPort = %d flag = valid buffer.", ethPort);
    INT status = platform_hal_GetMACsecEnable(ethPort, &flag);

    UT_LOG("platform_hal_GetMACsecEnable returns :  %d", status);
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

    UT_LOG("Exiting test_l1_platform_hal_positive3_GetMACsecEnable...");
}

/**
* @brief Test to verify the functionality of the platform_hal_StartMACsec API.
*
* This test verifies that the platform_hal_StartMACsec API can start MACsec on the specified Ethernet port with the given timeout value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 101 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_StartMACsec with ethPort = 1, timeoutSec = 0  | ethPort = 1, timeoutSec = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_StartMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_StartMACsec...");
    INT ethPort = 1;
    INT timeoutSec = 0;

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("platform_hal_StartMACsec returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_StartMACsec...");
}

/**
* @brief Test case to check the negative scenario of the platform_hal_StartMACsec API.
*
* This test case verifies the behavior of the platform_hal_StartMACsec API in a negative scenario. It checks if the API handles the case when the ethPort is set to -1 and the timeoutSec is set to 0.
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
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoke StartMACsec with invalid ethPort = -1 ,  timeoutSec = 0  | ethPort = -1, timeoutSec = 0 | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative1_StartMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_StartMACsec...");
    INT ethPort = -1;
    INT timeoutSec = 0;

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("platform_hal_StartMACsec returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_StartMACsec...");
}

/**
* @brief Test case to verify the StartMACsec API in the L1 platform HAL.
*
* This test case checks the functionality and correctness of the StartMACsec API in the L1 platform HAL. The API is responsible for starting MACsec on a given Ethernet port with a specified timeout.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 103 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01| Invoking platform_hal_StartMACsec with ethPort = 0, timeoutSec = 0| ethPort = 0, timeoutSec = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_StartMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_StartMACsec...");
    INT ethPort = 0;
    INT timeoutSec = 0;

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("platform_hal_StartMACsec returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_StartMACsec...");
}

/**
* @brief Verify the functionality of platform_hal_StartMACsec function when provided with valid input values
*
* This test is used to verify the functionality of the platform_hal_StartMACsec function. The function is invoked with valid input values for ethPort and timeoutSec parameters to validate if it returns the expected status code (RETURN_OK).
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 104 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01| Invoking platform_hal_StartMACsec with ethPort = MaxEthPort - 1, timeoutSec = 0 | ethPort = MaxEthPort - 1, timeoutSec = 0 |RETURN_OK| Should be successful|
*/
void test_l1_platform_hal_positive3_StartMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_StartMACsec...");
    //MaxEthPort should be configured in platform_config file
    INT ethPort = MaxEthPort - 1;
    INT timeoutSec = 0;

    UT_LOG("Invoking platform_hal_StartMACsec with ethPort = %d, timeoutSec = %d", ethPort, timeoutSec);
    INT status = platform_hal_StartMACsec(ethPort, timeoutSec);

    UT_LOG("platform_hal_StartMACsec returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_StartMACsec...");
}

/**
* @brief Test case to verify the functionality of platform_hal_GetDhcpv6_Options function under normal operation.
*
* This test verifies the functionality of platform_hal_GetDhcpv6_Options function by checking the return value and output parameters when the function is invoked in normal conditions.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 105 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----------: | ----------- | --------- | -------------| ----- |
* |01| Invoking the API platform_hal_GetDhcpv6_Options with req_opt_list = valid buffer, send_opt_list = valid buffer | req_opt_list = valid buffer, send_opt_list = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetDhcpv6_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetDhcpv6_Options...");
    dhcp_opt_list* req_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));
    dhcp_opt_list* send_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));

    if(req_opt_list != NULL && send_opt_list != NULL)
    {
        UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with req_opt_list = valid buffer, send_opt_list = valid buffer.");
        INT result = platform_hal_GetDhcpv6_Options(&req_opt_list, &send_opt_list);

        UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_OK);
        UT_ASSERT_PTR_NOT_NULL(req_opt_list);
        UT_ASSERT_PTR_NOT_NULL(send_opt_list);

        UT_LOG("DHCPv6 Options values for req is %d and for send is %d",req_opt_list->dhcp_opt,send_opt_list->dhcp_opt);

        if(req_opt_list->dhcp_opt == 82 || req_opt_list->dhcp_opt == 23 ||  req_opt_list->dhcp_opt == 95 ||  req_opt_list->dhcp_opt == 24 ||  req_opt_list->dhcp_opt == 83 ||  req_opt_list->dhcp_opt == 17 ||  req_opt_list->dhcp_opt == 31 ||  req_opt_list->dhcp_opt == 15 ||  req_opt_list->dhcp_opt == 16 ||  req_opt_list->dhcp_opt == 20)
        {
            UT_LOG("req_opt_list->dhcp_opt is %d which is a valid value.", req_opt_list->dhcp_opt);
            UT_PASS("Get Request DHCPV6 Options validation success");
        }
        else
        {
            UT_LOG("req_opt_list->dhcp_opt is %d which is an invalid value.", req_opt_list->dhcp_opt);
            UT_FAIL("Get Request DHCPV6 Options validation failed");
        }
        if(send_opt_list->dhcp_opt == 82 || send_opt_list->dhcp_opt == 23 ||  send_opt_list->dhcp_opt == 95 ||  send_opt_list->dhcp_opt == 24 ||  send_opt_list->dhcp_opt == 83 ||  send_opt_list->dhcp_opt == 17 ||  send_opt_list->dhcp_opt == 31 ||  send_opt_list->dhcp_opt == 15 ||  send_opt_list->dhcp_opt == 16 ||  send_opt_list->dhcp_opt == 20)
        {
            UT_LOG("send_opt_list->dhcp_opt is %d which is a valid value.", send_opt_list->dhcp_opt);
            UT_PASS("Get Send DHCPV6 Options validation success");
        }
        else
        {
            UT_LOG("send_opt_list->dhcp_opt is %d which is an invalid value.", send_opt_list->dhcp_opt);
            UT_FAIL("Get Send DHCPV6 Options validation failed");
        }
        free(req_opt_list);
        req_opt_list = NULL;
        free(send_opt_list);
        send_opt_list = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetDhcpv6_Options...");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetDhcpv6_Options() when the request option list is NULL.
*
* In this test case, the objective is to verify that if the request option list is NULL, the API returns RETURN_ERR.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 106 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the API platform_hal_GetDhcpv6_Options with req_opt_list = NULL, send_opt_list = valid buffer | req_opt_list = NULL, send_opt_list = valid buffer | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetDhcpv6_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetDhcpv6_Options...");
    dhcp_opt_list** req_opt_list = NULL;
    dhcp_opt_list* send_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));

    if(send_opt_list != NULL)
    {
        UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with req_opt_list = NULL, send_opt_list = valid buffer.");
        INT result = platform_hal_GetDhcpv6_Options(req_opt_list, &send_opt_list);

        UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(send_opt_list);
        send_opt_list = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetDhcpv6_Options...");
}

/**
* @brief Test for platform_hal_GetDhcpv6_Options with NULL send option list
*
* This test verifies the behavior of the platform_hal_GetDhcpv6_Options function when a NULL send option list is passed as an argument. The test aims to check if the function returns RETURN_ERR as expected.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking the API platform_hal_GetDhcpv6_Options with send_opt_list = NULL and req_opt_list = valid buffer| send_opt_list = NULL and req_opt_list = valid buffer| RETURN_ERR | Should return error|
*/
void test_l1_platform_hal_negative2_GetDhcpv6_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetDhcpv6_Options...");
    dhcp_opt_list* req_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));
    dhcp_opt_list** send_opt_list = NULL;

    if(req_opt_list != NULL)
    {
        UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with send_opt_list = NULL and req_opt_list = valid buffer.");
        INT result = platform_hal_GetDhcpv6_Options(&req_opt_list, send_opt_list);

        UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(req_opt_list);
        req_opt_list = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative2_GetDhcpv6_Options...");
}

/**
* @brief This test is used to verify the behavior of the platform_hal_GetDhcpv6_Options function when both the req_opt_list and send_opt_list are NULL.
*
* This test is intended to check if the platform_hal_GetDhcpv6_Options function returns RETURN_ERR when both the req_opt_list and send_opt_list are NULL.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 108 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* |01| Invoking the API platform_hal_GetDhcpv6_Options with req_opt_list = NULL, send_opt_list = NULL | req_opt_list = NULL, send_opt_list = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative3_GetDhcpv6_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_GetDhcpv6_Options...");
    dhcp_opt_list** req_opt_list = NULL;
    dhcp_opt_list** send_opt_list = NULL;

    UT_LOG("Invoking the API platform_hal_GetDhcpv6_Options with req_opt_list = NULL, send_opt_list = NULL.");
    INT result = platform_hal_GetDhcpv6_Options(req_opt_list,send_opt_list);

    UT_LOG("platform_hal_GetDhcpv6_Options API returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_GetDhcpv6_Options...");
}

/**
* @brief Test case to verify the functionality of setDscp function in positive conditions
*
* This test case verifies the functionality of the setDscp function when invoked with valid inputs in positive conditions.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_setDscp with interfaceType = DOCSIS, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30"| interfaceType = DOCSIS, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_setDscp...");
    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char pDscpVals[195] = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = %d, cmd = %d, pDscpVals = %s.", interfaceType, cmd, pDscpVals);
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);

    UT_LOG("platform_hal_setDscp returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_setDscp...");
}

/**
* @brief Test function to validate the platform_hal_setDscp API.
*
* This test function is used to validate the platform_hal_setDscp API functionality.
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
* |01| Invoking platform_hal_setDscp with interfaceType = EWAN, cmd = TRAFFIC_CNT_STOP, pDscpVals = NULL| interfaceType = EWAN, cmd = TRAFFIC_CNT_STOP, pDscpVals = NULL|RETURN_OK|Should be successful|
*/
void test_l1_platform_hal_positive2_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_setDscp...");
    WAN_INTERFACE interfaceType = EWAN;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_STOP;
    char* pDscpVals = NULL;

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = %d, cmd = %d, pDscpVals = NULL.",interfaceType, interfaceType );
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);

    UT_LOG("platform_hal_setDscp returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_setDscp...");
}

/**
* @brief Test function to validate the platform_hal_setDscp API.
*
* This test function is used to validate the platform_hal_setDscp API functionality.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* |01| Invoking platform_hal_setDscp with interfaceType = EWAN, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30"| interfaceType = EWAN, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30" | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive3_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_setDscp...");
    WAN_INTERFACE interfaceType = EWAN;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char pDscpVals[195] = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = %d , cmd = %d , pDscpVals = %s.", interfaceType, cmd, pDscpVals);
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);

    UT_LOG("platform_hal_setDscp returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive3_setDscp...");
}

/**
* @brief This test verifies the functionality of the platform_hal_setDscp API.
*
* This test case checks whether the platform_hal_setDscp API sets the Differentiated Services Code Point (DSCP) values correctly for the given interfaceType and cmd.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 112 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setDscp with interfaceType = DOCSIS, cmd = TRAFFIC_CNT_STOP, pDscpVals = "10,20,30" | interfaceType = DOCSIS, cmd = TRAFFIC_CNT_STOP, pDscpVals = "10,20,30" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive4_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive4_setDscp...");
    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_STOP;
    char pDscpVals[195] = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with interfaceType = %d, cmd = %d, pDscpVals = %s.", interfaceType, cmd, pDscpVals);
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);

    UT_LOG(" platform_hal_setDscp returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive4_setDscp...");
}

/**
* @brief This test function tests the negative scenario of the platform_hal_setDscp API.
*
* The objective of this test is to verify the behavior of the platform_hal_setDscp API when an invalid interface type is passed as an argument.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 113 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step| Description| Test Data| Expected Result| Notes|
* | :---------: | ------- | ---------| -----------| ------ |
* |01| Invoking platform_hal_setDscp with invalid interfaceType = 3, valid cmd = TRAFFIC_CNT_START and pDscpVals = "10,20,30"| interfaceType = 3, cmd = TRAFFIC_CNT_START, pDscpVals = "10,20,30" | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_setDscp...");
    WAN_INTERFACE interfaceType = 3;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char pDscpVals[195] = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with invalid interfaceType = %d, valid cmd = %d and  pDscpVals = %s.", interfaceType, cmd, pDscpVals);
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);

    UT_LOG("platform_hal_setDscp returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setDscp...");
}

/**
* @brief Test case to verify the negative scenario of the platform_hal_setDscp function.
*
* This test case verifies the behavior of the platform_hal_setDscp function when an invalid command is provided.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 114 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----------: | ------| --------- | ------------ | ----- |
* |01| Invoking platform_hal_setDscp with valid interfaceType = DOCSIS, invalid cmd = 3, valid pDscpVals = "10,20,30"| interfaceType = DOCSIS, cmd = 3, pDscpVals = "10,20,30"| RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative2_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_setDscp...");
    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = 3;
    char pDscpVals[195] = "10,20,30";

    UT_LOG("Invoking platform_hal_setDscp with valid interfaceType = %d, invalid cmd = %d , valid pDscpVals = %s.", interfaceType, cmd, pDscpVals);
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);

    UT_LOG("platform_hal_setDscp returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_setDscp...");
}

/**
* @brief Test to verify the behavior of platform_hal_setDscp() function when invalid DSCP values are provided.
*
* This test case focuses on testing the platform_hal_setDscp() function by passing invalid DSCP values (e.g., "100000,200000") for a particular interface type and traffic count command.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 115 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* | :----: | ---------| ---------- | -------------- | ----- |
* | 01| Invoking platform_hal_setDscp with valid interfaceType = DOCSIS and cmd = TRAFFIC_CNT_START, invalid pDscpVals = "100000,200000"| interfaceType = DOCSIS, cmd = TRAFFIC_CNT_START, pDscpVals = "100000,200000" |  RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative3_setDscp(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_setDscp...");
    WAN_INTERFACE interfaceType = DOCSIS;
    TRAFFIC_CNT_COMMAND cmd = TRAFFIC_CNT_START;
    char pDscpVals[195] = "100000,200000";

    UT_LOG("Invoking platform_hal_setDscp with valid interfaceType = %d and cmd = %d, invalid pDscpVals = %s.", interfaceType, cmd, pDscpVals);
    INT result = platform_hal_setDscp(interfaceType, cmd, pDscpVals);

    UT_LOG("platform_hal_setDscp returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_setDscp...");
}

/**
* @brief This function is used to test the functionality of the platform_hal_SetLowPowerModeState API with pState from config file.
*
* The objective of this test is to ensure that the platform_hal_SetLowPowerModeState API correctly sets the low power mode state value from config file and returns the expected status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 116 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* | :-------: | --------- | ---------| --------| -------|
* |01| Invoking platform_hal_SetLowPowerModeState with valid pState from config file | pState from config file | RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive1_SetLowPowerModeState(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetLowPowerModeState...");
    INT status = 0;
    int i = 0;

    for(i = 0;i < num_Supported_PSM_STATE; i++)
    {
        //Supported_PSM_STATE should be configured in platform_config file
        UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = %d.", Supported_PSM_STATE[i]);
        status = platform_hal_SetLowPowerModeState(&Supported_PSM_STATE[i]);

        UT_LOG("platform_hal_SetLowPowerModeState returns : %d", status);
        UT_ASSERT_EQUAL(status, RETURN_OK);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetLowPowerModeState...");
}

/**
* @brief This test verifies the behavior of the platform_hal_SetLowPowerModeState function when an unknown PPSM_STATE value is provided as input.
*
* The objective of this test is to ensure that the platform_hal_SetLowPowerModeState function handles unknown PPSM_STATE values correctly and returns the expected status.
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
* | 01 | Invoking platform_hal_SetLowPowerModeState with pState = PSM_UNKNOWN| pState = PSM_UNKNOWN| RETURN_ERR| Should return error |
*/
void test_l1_platform_hal_negative1_SetLowPowerModeState(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetLowPowerModeState...");
    PSM_STATE pState = PSM_UNKNOWN;

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = %d.", pState);
    INT status = platform_hal_SetLowPowerModeState(&pState);

    UT_LOG("Rplatform_hal_SetLowPowerModeState returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetLowPowerModeState...");
}

/**
* @brief Tests the scenario where the low power mode state is not supported by the platform_hal_SetLowPowerModeState function.
*
* This test is used to verify the behavior of platform_hal_SetLowPowerModeState function when the low power mode state is not supported by the platform. The function should return an error status code in this scenario.
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
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_SetLowPowerModeState with pState = PSM_NOT_SUPPORTED| pState = PSM_NOT_SUPPORTED| RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative2_SetLowPowerModeState(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetLowPowerModeState...");
    PSM_STATE pState = PSM_NOT_SUPPORTED;

    UT_LOG("Invoking platform_hal_SetLowPowerModeState with pState = %d.", pState);
    INT status = platform_hal_SetLowPowerModeState(&pState);

    UT_LOG("platform_hal_SetLowPowerModeState returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetLowPowerModeState...");
}

/**
* @brief Test the function platform_hal_GetFirmwareBankInfo() to retrieve firmware bank information.
*
* This test verifies if the function platform_hal_GetFirmwareBankInfo() correctly retrieves firmware bank information.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 119 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01| Invoking platform_hal_GetFirmwareBankInfo with bankIndex = ACTIVE_BANK, fwBankInfo = valid structure | bankIndex = ACTIVE_BANK, fwBankInfo = valid structure | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFirmwareBankInfo...");
    FW_BANK bankIndex = ACTIVE_BANK;
    PFW_BANK_INFO fwBankInfo = (PFW_BANK_INFO)malloc(sizeof(FW_BANK_INFO));
    if(fwBankInfo != NULL)
    {
        UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: %d , fwBankInfo = valid structure.", bankIndex);
        INT result = platform_hal_GetFirmwareBankInfo(bankIndex, fwBankInfo);

        UT_LOG("platform_hal_GetFirmwareBankInfo returns: %d", result);
        UT_LOG("Firmware name = %s and firmware state = %s of Firmware BankInfo.",fwBankInfo->fw_name, fwBankInfo->fw_state);
        UT_ASSERT_EQUAL(result, RETURN_OK);
        if(!strcmp(fwBankInfo->fw_state,"Confirmed") || strstr(fwBankInfo->fw_state,"TrialBoot#"))
        {
            UT_LOG(" Firmware state of Firmware BankInfo  is %s which is a valid string",fwBankInfo->fw_state);
            UT_PASS("Firmware state of Firmware BankInfo validation success");
        }
        else
        {
            UT_LOG("Firmware state of Firmware BankInfo %s which is an invalid value",fwBankInfo->fw_state);
            UT_FAIL("Firmware state of Firmware BankInfo validation failed");
        }

        free(fwBankInfo);
        fwBankInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetFirmwareBankInfo...");
}

/**
* @brief Test case for retrieving firmware bank information.
*
* This test case verifies the functionality of the platform_hal_GetFirmwareBankInfo function, which is responsible for retrieving the firmware bank information based on the provided bank index.
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
* | :----: | ---------- | ---------- | --------------- | ----- |
* | 01| Invoking platform_hal_GetFirmwareBankInfo with bankIndex = INACTIVE_BANK, fwBankInfo = valid structure | bankIndex = INACTIVE_BANK, fwBankInfo = valid structure | RETURN_OK | Should be successful  |
*/
void test_l1_platform_hal_positive2_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_GetFirmwareBankInfo...");
    FW_BANK bankIndex = INACTIVE_BANK;
    PFW_BANK_INFO fwBankInfo = (PFW_BANK_INFO)malloc(sizeof(FW_BANK_INFO));
    if(fwBankInfo != NULL)
    {
        UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: %d and , fwBankInfo = valid structure.",bankIndex);
        INT result = platform_hal_GetFirmwareBankInfo(bankIndex, fwBankInfo);

        UT_LOG("platform_hal_GetFirmwareBankInfo returns : %d", result);
        UT_LOG("Firmware name = %s and firmware state = %s of Firmware BankInfo.",fwBankInfo->fw_name, fwBankInfo->fw_state);
        UT_ASSERT_EQUAL(result, RETURN_OK);
        if(!strcmp(fwBankInfo->fw_state,"Confirmed") || strstr(fwBankInfo->fw_state,"TrialBoot#"))
        {
            UT_LOG(" Firmware state of Firmware BankInfo  is %s which is a valid string",fwBankInfo->fw_state);
            UT_PASS("Firmware state of Firmware BankInfo validation success");
        }
        else
        {
            UT_LOG("Firmware state of Firmware BankInfo %s which is an invalid value",fwBankInfo->fw_state);
            UT_FAIL("Firmware state of Firmware BankInfo validation failed");
        }

        free(fwBankInfo);
        fwBankInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive2_GetFirmwareBankInfo...");
}

/**
* @brief This test case verifies the behavior of the platform_hal_GetFirmwareBankInfo() function in negative scenario.
*
* The objective of this test is to ensure that the platform_hal_GetFirmwareBankInfo() function returns the expected error code when invoked with an invalid bank index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 121 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* |01| Invoking platform_hal_GetFirmwareBankInfo with invalid bankIndex = 2, fwBankInfo = valid structure| bankIndex = 2, fwBankInfo = valid structure | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFirmwareBankInfo...");
    FW_BANK bankIndex = 2;
    PFW_BANK_INFO fwBankInfo = (PFW_BANK_INFO)malloc(sizeof(FW_BANK_INFO));
    if(fwBankInfo != NULL)
    {
        UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with invalid bankIndex: %d, fwBankInfo = valid structure.", bankIndex);
        INT result = platform_hal_GetFirmwareBankInfo(bankIndex, fwBankInfo);

        UT_LOG("platform_hal_GetFirmwareBankInfo returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(fwBankInfo);
        fwBankInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetFirmwareBankInfo...");
}

/**
* @brief This test case tests the platform_hal_GetFirmwareBankInfo function by passing invalid arguments.
*
* This test case aims to verify the behavior of the platform_hal_GetFirmwareBankInfo function when invalid arguments are provided.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 122 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetFirmwareBankInfo with bankIndex = ACTIVE_BANK, fwBankInfo = NULL | bankIndex = ACTIVE_BANK, fwBankInfo = NULL | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative2_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetFirmwareBankInfo...");
    FW_BANK bankIndex = ACTIVE_BANK;
    FW_BANK_INFO* fwBankInfo = NULL;

    UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex: %d, fwBankInfo = NULL.", bankIndex);
    INT result = platform_hal_GetFirmwareBankInfo(bankIndex, fwBankInfo);

    UT_LOG("platform_hal_GetFirmwareBankInfo returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetFirmwareBankInfo...");
}

/**
* @brief This test case tests the platform_hal_GetFirmwareBankInfo function by passing invalid arguments.
*
*  This test case aims to verify the behavior of the platform_hal_GetFirmwareBankInfo function when invalid arguments are provided.
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
* | :---------: | ------- | --------- | --------| ----- |
* |01| Invoke platform_hal_GetFirmwareBankInfo with bankIndex: INACTIVE_BANK, fwBankInfo = NULL| bankIndex = INACTIVE_BANK, fwBankInfo = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative3_GetFirmwareBankInfo(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_GetFirmwareBankInfo...");
    FW_BANK bankIndex = INACTIVE_BANK;
    FW_BANK_INFO* fwBankInfo = NULL;

    UT_LOG("Invoking platform_hal_GetFirmwareBankInfo with bankIndex = %d , fwBankInfo = NULL.", bankIndex);
    INT result = platform_hal_GetFirmwareBankInfo(bankIndex, fwBankInfo);

    UT_LOG("platform_hal_GetFirmwareBankInfo returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_GetFirmwareBankInfo...");
}

/**
* @brief This test is used to verify the functionality of the platform_hal_getCMTSMac function.
*
* The purpose of this test is to check if the platform_hal_getCMTSMac function returns the expected status and output value.
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
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getCMTSMac with pValue = valid buffer | pValue = valid buffer | RETURN_OK | Should be successful |
 */
void test_l1_platform_hal_positive1_getCMTSMac(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getCMTSMac...");
    CHAR pValue[100] ={"\0"};
    int count = 0;
    int len = 0;
    int flag = 1;

    UT_LOG("Invoking platform_hal_getCMTSMac with pValue = valid buffer");
    INT status = platform_hal_getCMTSMac(pValue);

    UT_LOG("platform_hal_getCMTSMac returns : %d", status);
    UT_LOG("Mac Address = %s", pValue);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    len = strlen(pValue);
    if(len == 17)
    {
        for (int i = 0; pValue[i] != '\0'; i++)
        {
            // Check for valid characters: 0-9, A-F, a-f, and ':'
            if (!(isdigit(pValue[i]) || (pValue[i] >= 'A' && pValue[i] <= 'F') || (pValue[i] >= 'a' && pValue[i] <= 'f') || pValue[i] == ':'))
            {
                flag = 0;
                break;
            }
            // Count colons
            if (pValue[i] == ':')
            {
                count++;
            }
        }
        if (count == 5 && flag == 1)
        {
            UT_LOG("MAC string is %s which is valid MAC address.",pValue);
            UT_PASS("Get CMTS MAC validation success");
        }
        else
        {
            UT_LOG(" MAC address string is %s which is invalid string value.", pValue);
            UT_FAIL("Get CMTS MAC validation failed");
        }
    }
    else
    {
        UT_LOG(" MAC address string is %s which is invalid string length.", pValue);
        UT_FAIL("Get CMTS MAC validation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getCMTSMac...");
}

/**
* @brief This test case verifies the behavior of platform_hal_getCMTSMac() function when passed a null pointer as input.
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
* | 01 | Invoking platform_hal_getCMTSMac with pValue = NULL | pValue = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_getCMTSMac(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getCMTSMac...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_getCMTSMac with pValue = NULL.");
    INT status = platform_hal_getCMTSMac(pValue);

    UT_LOG("platform_hal_getCMTSMac returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getCMTSMac...");
}

/**
* @brief Test to verify the functionality of the platform_hal_GetDhcpv4_Options API.
*
* This test is used to verify the functionality of the platform_hal_GetDhcpv4_Options API, which is responsible for retrieving DHCPv4 options.
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
* |01| Invoking platform_hal_GetDhcpv4_Options with req_opt_list = valid buffer and send_opt_list = valid buffer| req_opt_list = valid buffer and send_opt_list = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetDhcpv4_Options...");
    dhcp_opt_list* req_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));
    dhcp_opt_list* send_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));

    if(req_opt_list != NULL && send_opt_list != NULL)
    {
        UT_LOG("Invoking platform_hal_GetDhcpv4_Options with req_opt_list = valid buffer and send_opt_list = valid buffer");
        INT result = platform_hal_GetDhcpv4_Options(&req_opt_list, &send_opt_list);

        UT_LOG("platform_hal_GetDhcpv4_Options returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_OK);
        UT_ASSERT_PTR_NOT_NULL(req_opt_list);
        UT_ASSERT_PTR_NOT_NULL(send_opt_list);
        UT_LOG("DHCPv4 Options values for req is %d and for send is %d",req_opt_list->dhcp_opt,send_opt_list->dhcp_opt);

        if(req_opt_list->dhcp_opt == 42 || req_opt_list->dhcp_opt == 43 ||  req_opt_list->dhcp_opt == 58 ||  req_opt_list->dhcp_opt == 59 ||  req_opt_list->dhcp_opt == 60 ||  req_opt_list->dhcp_opt == 61 ||  req_opt_list->dhcp_opt == 100 ||  req_opt_list->dhcp_opt == 122 ||  req_opt_list->dhcp_opt == 125 ||  req_opt_list->dhcp_opt == 242 ||  req_opt_list->dhcp_opt == 243 ||  req_opt_list->dhcp_opt == 255)
        {
            UT_LOG("req_opt_list->dhcp_opt is %d which is a valid value.", req_opt_list->dhcp_opt);
            UT_PASS("Get Request DHCPV4 Options validation success");
        }
        else
        {
            UT_LOG("req_opt_list->dhcp_opt is %d which is an invalid value.", req_opt_list->dhcp_opt);
            UT_FAIL("Get Request DHCPV4 Options validation failed");
        }
        if(send_opt_list->dhcp_opt == 42 || send_opt_list->dhcp_opt == 43 ||  send_opt_list->dhcp_opt == 58 ||  send_opt_list->dhcp_opt == 59 ||  send_opt_list->dhcp_opt == 60 ||  send_opt_list->dhcp_opt == 61 ||  send_opt_list->dhcp_opt == 100 ||  send_opt_list->dhcp_opt == 122 ||  send_opt_list->dhcp_opt == 125 ||  send_opt_list->dhcp_opt == 242 ||  send_opt_list->dhcp_opt == 243 ||  send_opt_list->dhcp_opt == 255)
        {
            UT_LOG("send_opt_list->dhcp_opt is %d which is a valid value.", send_opt_list->dhcp_opt);
            UT_PASS("Get Send DHCPV4 Options validation success");
        }
        else
        {
            UT_LOG("send_opt_list->dhcp_opt is %d which is an invalid value.", send_opt_list->dhcp_opt);
            UT_FAIL("Get Send DHCPV4 Options validation failed");
        }
        free(req_opt_list);
        req_opt_list = NULL;
        free(send_opt_list);
        send_opt_list = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetDhcpv4_Options...");
}

/**
* @brief This test case is used to verify the handling of NULL input argument by the function platform_hal_GetDhcpv4_Options.
*
* This test case verifies the behavior of the platform_hal_GetDhcpv4_Options function when the req_opt_list argument is NULL. The function should return an error code and also the send_opt_list should be set to NULL.
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
* |01| Invoking platform_hal_GetDhcpv4_Options with req_opt_list = NULL, send_opt_list = valid buffer | req_opt_list = NULL, send_opt_list = valid buffer | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetDhcpv4_Options...");
    dhcp_opt_list** req_opt_list = NULL;
    dhcp_opt_list* send_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));

    if(send_opt_list != NULL)
    {
        UT_LOG("Invoking platform_hal_GetDhcpv4_Options with req_opt_list = NULL, send_opt_list = valid buffer.");
        INT result = platform_hal_GetDhcpv4_Options(req_opt_list, &send_opt_list);

        UT_LOG("platform_hal_GetDhcpv4_Options returns: %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(send_opt_list);
        send_opt_list = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative1_GetDhcpv4_Options...");
}

/**
* @brief Test case to verify the behavior of the function platform_hal_GetDhcpv4_Options when NULL is passed as the send_opt_list argument.
*
* This test case checks the behavior of the platform_hal_GetDhcpv4_Options function when NULL is passed as the send_opt_list argument. The function is expected to return an error (RETURN_ERR) and set the req_opt_list and send_opt_list pointers to NULL.
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
* | :----: | --------- | ----------------- | --------------- | ------ |
* | 01 | Invoking platform_hal_GetDhcpv4_Options with send_opt_list = NULL, req_opt_list = valid buffer | send_opt_list = NULL, req_opt_list = valid buffer | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative2_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetDhcpv4_Options...");
    dhcp_opt_list** send_opt_list = NULL;
    dhcp_opt_list* req_opt_list = (dhcp_opt_list*)malloc(sizeof(dhcp_opt_list));

    if(req_opt_list != NULL)
    {
        UT_LOG("Invoking platform_hal_GetDhcpv4_Options with send_opt_list = NULL, req_opt_list = valid buffer");
        INT result = platform_hal_GetDhcpv4_Options(&req_opt_list,send_opt_list);

        UT_LOG("platform_hal_GetDhcpv4_Options returns :  %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);

        free(req_opt_list);
        req_opt_list = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative2_GetDhcpv4_Options...");
}

/**
* @brief This function tests the platform_hal_GetDhcpv4_Options function when passing NULL pointers as input arguments.
*
* The purpose of this test is to verify the behavior of the platform_hal_GetDhcpv4_Options function when NULL pointers are passed as input arguments. It is important to ensure that the function properly handles these invalid inputs.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* |01| Invoking platform_hal_GetDhcpv4_Options with req_opt_list = NULL, send_opt_list = NULL| req_opt_list = NULL, send_opt_list = NULL | RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative3_GetDhcpv4_Options(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_GetDhcpv4_Options...");
    dhcp_opt_list** req_opt_list = NULL;
    dhcp_opt_list** send_opt_list = NULL;

    UT_LOG("Invoking platform_hal_GetDhcpv4_Options with req_opt_list = NULL, send_opt_list = NULL");
    INT result = platform_hal_GetDhcpv4_Options(req_opt_list, send_opt_list);

    UT_LOG("platform_hal_GetDhcpv4_Options returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_GetDhcpv4_Options...");
}

/**
* @brief Test the functionality of platform_hal_getDscpClientList API.
*
* This test case is used to verify the functionality of the platform_hal_getDscpClientList API. It checks whether the API returns the correct DSCP client list for a given interface type.
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
* | :----: | ----------- | --------- | --------------- | ----- |
* | 1| Invoking platform_hal_getDscpClientList with interfaceType = DOCSIS, pDSCP_List = valid structure | interfaceType = DOCSIS, pDSCP_List = valid structure | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getDscpClientList...");
    WAN_INTERFACE interfaceType = DOCSIS;
    int len = 0;
    int count = 0;
    int flag = 1;
    pDSCP_list_t pDSCP_List = malloc(sizeof(DSCP_list_t));
    if(pDSCP_List != NULL)
    {
        UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType = %d, pDSCP_List = valid structure.", interfaceType);
        INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

        UT_LOG("platform_hal_getDscpClientList returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_OK);
        if (pDSCP_List != NULL)
        {
            if (pDSCP_List->numElements >= 0 && pDSCP_List->numElements <= 64)
            {
                UT_LOG("numElements is %d which is a valid value", pDSCP_List->numElements);
                UT_PASS("numElement validation success");
            }
            else
            {
                UT_LOG("numElements is %d which is an Invalid value", pDSCP_List->numElements);
                UT_FAIL("numElement validation failed");
            }
            for (UINT i = 0; i < pDSCP_List->numElements; i++)
            {
                DSCP_Element_t *pDSCP_Element = &(pDSCP_List->DSCP_Element[i]);
                if (pDSCP_Element->dscp_value >= 0 && pDSCP_Element->dscp_value <= 65534)
                {
                    UT_LOG("dscp_value is %d which is a valid value", pDSCP_Element->dscp_value);
                    UT_PASS("dscp_value validation success");
                }
                else
                {
                    UT_LOG("dscp_value is %d which is an Invalid value", pDSCP_Element->dscp_value);
                    UT_FAIL("dscp_value validation failed");
                }
                if (pDSCP_Element->numClients >= 0 && pDSCP_Element->numClients <= 255)
                {
                    UT_LOG("numClients is %d which is a valid value", pDSCP_Element->numClients);
                    UT_PASS("numClients validation success");
                }
                else
                {
                    UT_LOG("numClients is %d which is an Invalid value", pDSCP_Element->numClients);
                    UT_FAIL("numClients validation failed");
                }
                for (UINT j = 0; j < pDSCP_Element->numClients; j++)
                {
                    Traffic_client_t *pTraffic_client = &(pDSCP_Element->Client[j]);
                    len = strlen(pTraffic_client->mac);
                    if(len == 17)
                    {
                        count = 0;
                        flag = 1;
                        for (int i = 0; pTraffic_client->mac[i] != '\0'; i++)
                        {
                            // Check for valid characters: 0-9, A-F, a-f, and ':'
                            if (!(isdigit(pTraffic_client->mac[i]) || (pTraffic_client->mac[i] >= 'A' && pTraffic_client->mac[i] <= 'F') || (pTraffic_client->mac[i] >= 'a' && pTraffic_client->mac[i] <= 'f') || pTraffic_client->mac[i] == ':'))
                            {
                                flag = 0;
                                break;
                            }
                            // Count colons
                            if (pTraffic_client->mac[i] == ':')
                            {
                                count++;
                            }
                        }
                        if (count == 5 && flag == 1)
                        {
                            UT_LOG("MAC string is %s which is valid MAC address.",pTraffic_client->mac);
                            UT_PASS("Get CMTS MAC validation success");
                        }
                        else
                        {
                            UT_LOG(" MAC address string is %s which is invalid string value.", pTraffic_client->mac);
                            UT_FAIL("Get CMTS MAC validation failed");
                        }
                    }
                    else
                    {
                        UT_LOG(" MAC address string is %s which is invalid string length.", pTraffic_client->mac);
                        UT_FAIL("Get CMTS MAC validation failed");
                    }
                    if (pTraffic_client->rxBytes >= 0 && pTraffic_client->txBytes >= 0)
                    {
                        UT_LOG("rxBytes is: %d and txBytes is: %d which is a valid value", pTraffic_client->rxBytes,pTraffic_client->txBytes);
                        UT_PASS("rxBytes and txBytes validation success");
                    }
                    else
                    {
                        UT_LOG("rxBytes is: %d and txBytes is: %d which is an invalid value", pTraffic_client->rxBytes,pTraffic_client->txBytes);
                        UT_FAIL("rxBytes and txBytes validation failed");
                    }
                }
            }
            free(pDSCP_List);
            pDSCP_List = NULL;
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_getDscpClientList...");
}

/**
* @brief This test case validates the functionality of the platform_hal_getDscpClientList function in the L1 platform HAL module.
*
* This test case verifies that the platform_hal_getDscpClientList function returns the correct list of DSCP clients for the given WAN interface type.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 131 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getDscpClientList with interfaceType = EWAN, pDSCP_List = valid structure | interfaceType = EWAN, pDSCP_List = valid structure | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_getDscpClientList...");
    WAN_INTERFACE interfaceType = EWAN;
    pDSCP_list_t pDSCP_List = malloc(sizeof(DSCP_list_t));
    int count = 0;
    int len = 0;
    int flag = 1;
    if(pDSCP_List != NULL)
    {
        UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType = %d, pDSCP_List = valid structure.",interfaceType);
        INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

        UT_LOG("platform_hal_getDscpClientList returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_OK);

        if (pDSCP_List != NULL)
        {
            if (pDSCP_List->numElements >= 0 && pDSCP_List->numElements <= 64)
            {
                UT_LOG("numElements is %d which is a valid value", pDSCP_List->numElements);
                UT_PASS("numElement validation success");
            }
            else
            {
                UT_LOG("numElements is %d which is an Invalid value", pDSCP_List->numElements);
                UT_FAIL("numElement validation failed");
            }
            for (UINT i = 0; i < pDSCP_List->numElements; i++)
            {
                DSCP_Element_t *pDSCP_Element = &(pDSCP_List->DSCP_Element[i]);
                if (pDSCP_Element->dscp_value >= 0 && pDSCP_Element->dscp_value <= 65534)
                {
                    UT_LOG("dscp_value is %d which is a valid value", pDSCP_Element->dscp_value);
                    UT_PASS("dscp_value validation success");
                }
                else
                {
                    UT_LOG("dscp_value is %d which is an Invalid value", pDSCP_Element->dscp_value);
                    UT_FAIL("dscp_value validation failed");
                }
                if (pDSCP_Element->numClients >= 0 && pDSCP_Element->numClients <= 255)
                {
                    UT_LOG("numClients is %d which is a valid value", pDSCP_Element->numClients);
                    UT_PASS("numClients validation success");
                }
                else
                {
                    UT_LOG("numClients is %d which is an Invalid value", pDSCP_Element->numClients);
                    UT_FAIL("numClients validation failed");
                }
                for (UINT j = 0; j < pDSCP_Element->numClients; j++)
                {
                    Traffic_client_t *pTraffic_client = &(pDSCP_Element->Client[j]);
                    len = strlen(pTraffic_client->mac);
                    if(len == 17)
                    {
                        count = 0;
                        flag = 1;
                        for (int i = 0; pTraffic_client->mac[i] != '\0'; i++)
                        {
                            // Check for valid characters: 0-9, A-F, a-f, and ':'
                            if (!(isdigit(pTraffic_client->mac[i]) || (pTraffic_client->mac[i] >= 'A' && pTraffic_client->mac[i] <= 'F') || (pTraffic_client->mac[i] >= 'a' && pTraffic_client->mac[i] <= 'f') || pTraffic_client->mac[i] == ':'))
                            {
                                flag = 0;
                                break;
                            }
                            // Count colons
                            if (pTraffic_client->mac[i] == ':')
                            {
                                count++;
                            }
                        }
                        if (count == 5 && flag == 1)
                        {
                            UT_LOG("MAC string is %s which is valid MAC address.", pTraffic_client->mac);
                            UT_PASS("Get CMTS MAC validation success");
                        }
                        else
                        {
                            UT_LOG(" MAC address string is %s which is invalid string value.", pTraffic_client->mac);
                            UT_FAIL("Get CMTS MAC validation failed");
                        }
                    }
                    else
                    {
                        UT_LOG(" MAC address string is %s which is invalid string length.", pTraffic_client->mac);
                        UT_FAIL("Get CMTS MAC validation failed");
                    }
                    if (pTraffic_client->rxBytes >= 0 && pTraffic_client->txBytes >= 0)
                    {
                        UT_LOG("rxBytes is: %d and txBytes is: %d which is a valid value", pTraffic_client->rxBytes,pTraffic_client->txBytes);
                        UT_PASS("rxBytes and txBytes validation success");
                    }
                    else
                    {
                        UT_LOG("rxBytes is: %d and txBytes is: %d which is an invalid value", pTraffic_client->rxBytes,pTraffic_client->txBytes);
                        UT_FAIL("rxBytes and txBytes validation failed");
                    }
                }
            }
        }
        free(pDSCP_List);
        pDSCP_List = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive2_getDscpClientList...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_getDscpClientList function with invalid interfaceType and valid pDSCP_List.
*
* This test case verifies the behavior of the platform_hal_getDscpClientList function when called with an invalid interfaceType and a valid pDSCP_List. The expected result is that the function should return RETURN_ERR.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 132 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, they can select this test case via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Call platform_hal_getDscpClientList with invalid interfaceType = 3 and valid structure| interfaceType = 3, pDSCP_List = valid structure | RETURN_ERR | should return error |
*/
void test_l1_platform_hal_negative1_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getDscpClientList...");
    WAN_INTERFACE interfaceType = 3;
    pDSCP_list_t pDSCP_List = malloc(sizeof(DSCP_list_t));
    if(pDSCP_List != NULL)
    {
        UT_LOG("Invoking platform_hal_getDscpClientList with invalid interfaceType = %d and valid pDSCP_List.", interfaceType);
        INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

        UT_LOG("platform_hal_getDscpClientList returns : %d", result);
        UT_ASSERT_EQUAL(result, RETURN_ERR);
        free(pDSCP_List);
        pDSCP_List = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative1_getDscpClientList...");
}

/**
* @brief Function to test the platform_hal_getDscpClientList function when pDSCP_List is NULL
*
* This test case is used to verify the behavior of the platform_hal_getDscpClientList function when pDSCP_List is NULL. The objective of this test is to check if the function returns RETURN_ERR when pDSCP_List is NULL.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 133 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getDscpClientList with interfaceType = DOCSIS, pDSCP_List = NULL | interfaceType = DOCSIS, pDSCP_List = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative2_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_getDscpClientList...");
    WAN_INTERFACE interfaceType = DOCSIS;
    pDSCP_list_t pDSCP_List = NULL;

    UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType = %d, pDSCP_List = NULL.", interfaceType);
    INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

    UT_LOG("platform_hal_getDscpClientList returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_getDscpClientList...");
}

/**
* @brief This test case checks the behavior of the platform_hal_getDscpClientList() function when passed a NULL pDSCP_List as an argument.
*
* The objective of this test is to ensure that the function returns an appropriate error code when passed a NULL pDSCP_List.
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
* | :----: | --------- | ---------- |-------------- | ----- |
* |01| Invoking platform_hal_getDscpClientList with interfaceType = EWAN , pDSCP_List = NULL| interfaceType = EWAN, pDSCP_List = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative3_getDscpClientList(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_getDscpClientList...");
    WAN_INTERFACE interfaceType = EWAN;
    pDSCP_list_t pDSCP_List = NULL;

    UT_LOG("Invoking platform_hal_getDscpClientList with interfaceType = %d and pDSCP_List = NULL.",interfaceType);
    INT result = platform_hal_getDscpClientList(interfaceType, pDSCP_List);

    UT_LOG("platform_hal_getDscpClientList returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_getDscpClientList...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_GetDeviceConfigStatus API.
*
* This test case checks if the platform_hal_GetDeviceConfigStatus API returns the correct device configuration status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 135 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* |01| Invoke platform_hal_GetDeviceConfigStatus API with pValue = valid buffer | pValue = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetDeviceConfigStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetDeviceConfigStatus...");
    CHAR pValue[128] = {"\0"};

    UT_LOG("Invoking platform_hal_GetDeviceConfigStatus with pValue = valid buffer.");
    INT result = platform_hal_GetDeviceConfigStatus(pValue);

    UT_LOG(" Device Config Status = %s", pValue);
    UT_LOG("platform_hal_GetDeviceConfigStatus returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    if (!strcmp(pValue,"WaitForImplement") || !strcmp(pValue,"In Progress")|| !strcmp(pValue,"Complete"))
    {
        UT_LOG("Device Config Status is %s which is a valid value",pValue);
        UT_PASS("Device Config Status validation success");
    }
    else
    {
        UT_LOG("Device Config Status %s which is an Invalid value",pValue);
        UT_FAIL(" Get Device Config Status validation fail");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetDeviceConfigStatus...");
}

/**
* @brief Test to verify the return status of platform_hal_GetDeviceConfigStatus() when provided with invalid input parameters.
*
* This test case is designed to verify the return status of platform_hal_GetDeviceConfigStatus() API when it is invoked with invalid input parameters. The return status should be RETURN_ERR.
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
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* | :-------:| ---------| ----------|--------------| -----|
* | 01| Invoke platform_hal_GetDeviceConfigStatus API with pValue = NULL| pValue = NULL| RETURN_ERR|Should return error|
*/
void test_l1_platform_hal_negative1_GetDeviceConfigStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetDeviceConfigStatus...");
    CHAR *pValue = NULL;
    UT_LOG("Invoking platform_hal_GetDeviceConfigStatus with pValue = NULL.");
    INT result = platform_hal_GetDeviceConfigStatus(pValue);

    UT_LOG("platform_hal_GetDeviceConfigStatus returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetDeviceConfigStatus...");
}

/**
* @brief Test case to verify the functionality of the platform_hal_SetSNMPOnboardRebootEnable function.
*
* This test case verifies if the platform_hal_SetSNMPOnboardRebootEnable function can successfully enable SNMP onboard reboot.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 137 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:**  @n
* | Variation / Step | Description| Test Data| Expected Result|Notes|
* | :--------: | ------------| --------| --------- | --------|
* | 01| Invoking platform_hal_SetSNMPOnboardRebootEnable with value = "enable" | value = "enable" | RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable...");
    CHAR value[8] = "enable";

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with value = %s.", value);
    INT result = platform_hal_SetSNMPOnboardRebootEnable(value);

    UT_LOG("platform_hal_SetSNMPOnboardRebootEnable returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable...");
}

/**
* @brief Unit test to verify the behavior of the function platform_hal_SetSNMPOnboardRebootEnable().
*
* This test checks the functionality of the platform_hal_SetSNMPOnboardRebootEnable() function. The test verifies whether the function returns a successful result when the input parameter is "disable".
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 138 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01| Invoking platform_hal_SetSNMPOnboardRebootEnable with value = "disable" | value = "disable" | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable...");
    CHAR value[8] = "disable";

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with value = %s.", value);
    INT result = platform_hal_SetSNMPOnboardRebootEnable(value);

    UT_LOG("platform_hal_SetSNMPOnboardRebootEnable returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable...");
}

/**
* @brief This test function tests the negative scenario of the platform_hal_SetSNMPOnboardRebootEnable API.
*
* The objective of this test is to verify the behavior of the platform_hal_SetSNMPOnboardRebootEnable API when it is given a NULL input parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 139 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_SetSNMPOnboardRebootEnable with value = NULL| value = NULL | RETURN_ERR | Shouldreturn error |
*/
void test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable...");
    CHAR *value = NULL;

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with value = NULL");
    INT result = platform_hal_SetSNMPOnboardRebootEnable(value);

    UT_LOG("platform_hal_SetSNMPOnboardRebootEnable returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable...");
}

/**
* @brief This test case is designed to verify the negative scenario of platform_hal_SetSNMPOnboardRebootEnable function.
*
* The purpose of this test case is to confirm that the platform_hal_SetSNMPOnboardRebootEnable function returns an error when an invalid parameter is passed.
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
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* | :----------: |-------------| ---------| ---------| -------|
* | 01| Invoking platform_hal_SetSNMPOnboardRebootEnable with value = "invalid" | value = "invalid" | RETURN_ERR| Should return error |
*/
void test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable...");
    CHAR value[8] = "invalid";

    UT_LOG("Invoking platform_hal_SetSNMPOnboardRebootEnable with value = %s.", value);
    INT result = platform_hal_SetSNMPOnboardRebootEnable(value);

    UT_LOG("platform_hal_SetSNMPOnboardRebootEnable returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable...");
}

#ifdef FEATURE_RDKB_THERMAL_MANAGER
/**
* @brief Unit test for platform_hal_getInputCurrent function
*
* This test case is used to verify the functionality of the platform_hal_getInputCurrent function. The objective of this test is to check if the function returns the correct input current value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 141 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_getInputCurrent with valid buffer | value = valid buffer |  RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_getInputCurrent(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getInputCurrent...");
    INT value = 0;

    UT_LOG("Invoking platform_hal_getInputCurrent with valid buffer");
    INT status = platform_hal_getInputCurrent(&value);

    UT_LOG("platform_hal_getInputCurrent returns : %d", status);
    UT_LOG("Input Current : %d", value);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_getInputCurrent...");
}

/**
* @brief This test case aims to verify the functionality of the platform_hal_getInputCurrent function when invoked with a NULL input pointer.
*
* This test case checks if the platform_hal_getInputCurrent function returns the expected error status when called with a NULL input pointer.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 142 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
*  | Variation / Step | Description | Test Data | Expected Result| Notes|
*  | :---------: | ---------| -------------| --------- | ------- |
*  |01| Invoking platform_hal_getInputCurrent with pValue = NULL | pValue = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_getInputCurrent(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getInputCurrent...");
    INT *pValue = NULL;

    UT_LOG("Invoking platform_hal_getInputCurrent with pValue = NULL.");
    INT status = platform_hal_getInputCurrent(pValue);

    UT_LOG("platform_hal_getInputCurrent returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getInputCurrent...");
}

/**
* @brief Test the function platform_hal_LoadThermalConfig by providing valid uninitialized THERMAL_PLATFORM_CONFIG struct
*
* This test case checks the functionality of the platform_hal_LoadThermalConfig function by providing a valid uninitialized THERMAL_PLATFORM_CONFIG struct as input. The test case verifies the return value of the function and the filled values in the struct.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 143 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_LoadThermalConfig with thermalConfig = valid structure | thermalConfig = valid structure| RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_LoadThermalConfig(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_LoadThermalConfig...");
    THERMAL_PLATFORM_CONFIG *thermalConfig = (THERMAL_PLATFORM_CONFIG*)malloc(sizeof(THERMAL_PLATFORM_CONFIG));
    if(thermalConfig != NULL)
    {
        UT_LOG("Invoking platform_hal_LoadThermalConfig with thermalConfig = valid structure");
        INT status = platform_hal_LoadThermalConfig(thermalConfig);

        UT_LOG("platform_hal_LoadThermalConfig API returns : %d", status);
        UT_ASSERT_EQUAL(status, RETURN_OK);
        UT_LOG("Values are Fan count : %d, Slow Speed Thresh: %d, MediumSpeedThresh : %d, Fast Speed Thresh : %d, FanMinRunTime : %d, MonitoringDelay : %d, PowerMonitoring : %d, LogInterval : %d",thermalConfig->FanCount, thermalConfig->SlowSpeedThresh, thermalConfig->MediumSpeedThresh, thermalConfig->FastSpeedThresh, thermalConfig->FanMinRunTime, thermalConfig->MonitoringDelay, thermalConfig->PowerMonitoring, thermalConfig->LogInterval);

        if(thermalConfig->FanCount == 1 || thermalConfig->FanCount == 2)
        {
            UT_LOG("Fan Count is %d which is a valid value", thermalConfig->FanCount );
            UT_PASS("Fan Count validation success");
        }
        else
        {
            UT_LOG("Fan Count is %d which is a Invalid value", thermalConfig->FanCount);
            UT_PASS("Fan Count validation failed");
        }
        if(thermalConfig->PowerMonitoring == 0 || thermalConfig->PowerMonitoring == 1)
        {
            UT_LOG("Power monitoring is %d which is a valid value", thermalConfig->PowerMonitoring );
            UT_PASS("Power monitoring validation success");
        }
        else
        {
            UT_LOG("Power monitoring is %d which is a valid value", thermalConfig->PowerMonitoring);
            UT_PASS("Power monitoring validation failed");
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_LoadThermalConfig...");
}

/**
* @brief Test function to verify the behavior of the function platform_hal_LoadThermalConfig when called with a null pointer.
*
* This test case is designed to validate the behavior of the platform_hal_LoadThermalConfig function when called with a null pointer as the argument.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 144 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01| Invoking platform_hal_LoadThermalConfig with thermalConfig = NULL | thermalConfig = NULL |  RETURN_ERR | Should return an error |
*/
void test_l1_platform_hal_negative1_LoadThermalConfig(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_LoadThermalConfig...");
    THERMAL_PLATFORM_CONFIG *thermalConfig = NULL;

    UT_LOG("Invoking platform_hal_LoadThermalConfig with thermalConfig = NULL");
    INT status = platform_hal_LoadThermalConfig(thermalConfig);

    UT_LOG("platform_hal_LoadThermalConfig returns : %d",status);
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
* **Test Case ID:** 145 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetMACsecOperationalStatus with ethPort = 0 and flag = valid buffer | ethPort = 0, flag = valid buffer| RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetMACsecOperationalStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetMACsecOperationalStatus...");
    INT ethPort = 0;
    BOOLEAN flag = FALSE;

    UT_LOG("Invoking platform_hal_GetMACsecOperationalStatus with ethPort = %d and flag = valid buffer", ethPort);
    INT ret = platform_hal_GetMACsecOperationalStatus(ethPort, &flag);

    UT_LOG("platform_hal_GetMACsecOperationalStatus returns: %d", ret);
    UT_LOG("MAC sec Operational Status : %d", flag);
    UT_ASSERT_EQUAL(ret, RETURN_OK);
    if(flag == TRUE || flag == FALSE )
    {
        UT_LOG(" Get MAC sec Operational Status is %d", flag);
        UT_PASS("MAC sec Operational Status validation success");
    }
    else
    {
        UT_LOG("MAC sec Operational Status is %d", flag);
        UT_FAIL("MAC sec Operational Status validation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetMACsecOperationalStatus...");
}

/**
* @brief This is a unit test to verify the functionality of the platform_hal_GetMACsecOperationalStatus API in a negative scenario.
*
* The objective of this test is to check the behavior of the platform_hal_GetMACsecOperationalStatus API when the ethPort is 0 and pFlag is NULL.
*
* **Test Group ID**: Basic: 01 @n
* **Test Case ID**: 146 @n
* **Priority**: High @n@n
*
* **Pre-Conditions**: None @n
* **Dependencies**: None @n
* **User Interaction**: If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure**: @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01| Invoking platform_hal_GetMACsecOperationalStatus with ethPort = 0, pFlag = NULL | ethPort = 0, pFlag = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetMACsecOperationalStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetMACsecOperationalStatus...");
    INT ethPort = 0;
    BOOLEAN *pFlag = NULL;

    UT_LOG("Invoking platform_hal_GetMACsecOperationalStatus with ethPort = %d  and pFlag = NULL", ethPort);
    INT ret = platform_hal_GetMACsecOperationalStatus(ethPort, pFlag);

    UT_LOG("platform_hal_GetMACsecOperationalStatus returns: %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetMACsecOperationalStatus...");
}

/**
* @brief This test case verifies the functionality of the platform_hal_setFanMaxOverride function.
*
* The objective of this test is to ensure that the platform_hal_setFanMaxOverride function sets the maximum fan override flag and fan index  from config file correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 147 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFanMaxOverride with bOverrideFlag = TRUE, fanIndex from config file | bOverrideFlag = TRUE, fanIndex from config file | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_setFanMaxOverride(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_setFanMaxOverride...");
    BOOLEAN bOverrideFlag = TRUE;
    INT status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag = %d, fanIndex = %d", bOverrideFlag, FanIndex[i]);
        status = platform_hal_setFanMaxOverride(bOverrideFlag, FanIndex[i]);

        UT_LOG("platform_hal_setFanMaxOverride returns: %d", status);
        UT_ASSERT_EQUAL(status, RETURN_OK);
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_setFanMaxOverride...");
}

/**
* @brief This test case verifies the functionality of the platform_hal_setFanMaxOverride function when the override flag is set to FALSE and fan index from config file.
*
* This test case validates the platform_hal_setFanMaxOverride function by testing its behavior when the override flag is FALSE and fan index from config file. It checks if the function returns RETURN_OK indicating the successful execution of the API.
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
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking the platform_hal_setFanMaxOverride API with bOverrideFlag = FALSE and fanIndex from config file | bOverrideFlag = FALSE, fanIndex from config file | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_setFanMaxOverride(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_setFanMaxOverride...");
    BOOLEAN bOverrideFlag = FALSE;
    INT status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanMaxOverride with bOverrideFlag = %d, fanIndex = %d", bOverrideFlag, FanIndex[i]);
        status = platform_hal_setFanMaxOverride(bOverrideFlag, FanIndex[i]);

        UT_LOG("platform_hal_setFanMaxOverride returns: %d", status);
        UT_ASSERT_EQUAL(status, RETURN_OK);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive2_setFanMaxOverride...");
}

/**
* @brief Test case to verify the behavior of platform_hal_setFanMaxOverride when the provided arguments are invalid.
*
* This test case verifies if the platform_hal_setFanMaxOverride API returns the expected status when the provided arguments are invalid.
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
* | Variation / Step | Description| Test Data | Expected Result| Notes|
* | :--------: | ---------| -----------| ----------| -------- |
* |01| Invoking platform_hal_setFanMaxOverride with valid bOverrideFlag = TRUE, invalid fanIndex = 2| bOverrideFlag = TRUE, fanIndex = 2| Status to be RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_setFanMaxOverride(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_setFanMaxOverride...");
    BOOLEAN bOverrideFlag = TRUE;
    UINT fanIndex = 2;

    UT_LOG("Invoking platform_hal_setFanMaxOverride with valid bOverrideFlag = %d, invalid fanIndex = %d", bOverrideFlag, fanIndex);
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);

    UT_LOG("platform_hal_setFanMaxOverride returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_setFanMaxOverride...");
}

/**
* @brief Test case to verify the behavior of platform_hal_setFanMaxOverride in a negative scenario
*
* This test case verifies the behavior of platform_hal_setFanMaxOverride function when bOverrideFlag is set to FALSE and fanIndex is 2.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 150 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes|
* | :-------: | ------| ---------| -------| ----------|
* | 01| Invoking platform_hal_setFanMaxOverride with valid bOverrideFlag = FALSE, invalid fanIndex = 2 | bOverrideFlag = FALSE, fanIndex = 2 | RETURN_ERR| Should return error |
*/
void test_l1_platform_hal_negative2_setFanMaxOverride(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_setFanMaxOverride...");
    BOOLEAN bOverrideFlag = FALSE;
    UINT fanIndex = 2;

    UT_LOG("Invoking platform_hal_setFanMaxOverride with valid bOverrideFlag = %d, invalid fanIndex = %d", bOverrideFlag, fanIndex);
    INT status = platform_hal_setFanMaxOverride(bOverrideFlag, fanIndex);

    UT_LOG("platform_hal_setFanMaxOverride returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_setFanMaxOverride...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_setFanMaxOverride function when the bOverrideFlag is set to a value other than 0 or 1.
*
* This test case checks the behavior of the platform_hal_setFanMaxOverride function when an invalid value is passed as the bOverrideFlag argument.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 151 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, they should select this test case via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description| Test Data| Expected Result| Notes|
* | :--------: | --------- | --------| --------| --------- |
* |01| Invoke the platform_hal_setFanMaxOverride function with invalid bOverrideFlag = 2, valid fanIndex = 0 | bOverrideFlag = 2, fanIndex = 0| status = RETURN_ERR | Should return error|
*/
void test_l1_platform_hal_negative3_setFanMaxOverride(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_setFanMaxOverride...");
    BOOLEAN bOverrideFlag = 2;
    int i = 0;
    INT status = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanMaxOverride with invalid bOverrideFlag = %d, valid fanIndex = %d", bOverrideFlag, FanIndex[i]);
        status = platform_hal_setFanMaxOverride(bOverrideFlag, FanIndex[i]);

        UT_LOG("platform_hal_setFanMaxOverride returns: %d", status);
        UT_ASSERT_EQUAL(status, RETURN_ERR);
    }
    UT_LOG("Exiting test_l1_platform_hal_negative3_setFanMaxOverride...");
}

#ifdef FEATURE_RDKB_THERMAL_MANAGER
/**
* @brief This function tests the functionality of the platform_hal_setFanSpeed() API
*
* This test case checks the functionality of the platform_hal_setFanSpeed() API by invoking with fan index value from config file,fan speed value as FAN_SPEED_OFF, and a valid buffer for error reason.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 152 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------: | ----------- | --------- | --------------- | ----- |
* | 01| Invoking platform_hal_setFanSpeed with fanIndex from config file, fanSpeed = FAN_SPEED_OFF, pErrReason = valid buffer| fanIndex from config file, fanSpeed = FAN_SPEED_OFF, pErrReason = valid buffer | status = RETURN_OK, pErrReason = FAN_ERR_NONE | Should be successful |
*/
void test_l1_platform_hal_positive1_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_OFF;
    FAN_ERR pErrReason = FAN_ERR_NONE;
    int i = 0;
    INT status = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex = %d, fanSpeed = %d,pErrReason = valid buffer.", FanIndex[i], fanSpeed);
        status = platform_hal_setFanSpeed(FanIndex[i], fanSpeed, &pErrReason);

        UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status, pErrReason);
        UT_ASSERT_EQUAL(status, RETURN_OK);
        UT_ASSERT_EQUAL(pErrReason, FAN_ERR_NONE);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_setFanSpeed...");
}

/**
* @brief Test for the platform_hal_setFanSpeed function with positive input
*
* This test is performed to verify the functionality of the platform_hal_setFanSpeed API by invoking with fan index from config file, fan speed as FAN_SPEED_SLOW, and a valid buffer for error reason.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with fanIndex from config file, fanSpeed = FAN_SPEED_SLOW, pErrReason = valid buffer| fanIndex from config file, fanSpeed = FAN_SPEED_SLOW, pErrReason = valid buffer | status = RETURN_OK, pErrReason = FAN_ERR_NONE | Should be successful |
*/
void test_l1_platform_hal_positive2_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_SLOW;
    FAN_ERR pErrReason = FAN_ERR_NONE;
    int i = 0;
    INT status = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex = %d, fanSpeed = %d, pErrReason = valid buffer.", FanIndex[i], fanSpeed);
        status = platform_hal_setFanSpeed(FanIndex[i], fanSpeed, &pErrReason);

        UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status, pErrReason);
        UT_ASSERT_EQUAL(status, RETURN_OK);
        UT_ASSERT_EQUAL(pErrReason, FAN_ERR_NONE);
    }
    UT_LOG("Exiting test_l1_platform_hal_positive2_setFanSpeed...");
}

/**
* @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
*
* This test case verifies the functionality of the platform_hal_setFanSpeed API by invoking with fan index from config file, fan speed as FAN_SPEED_MEDIUM, and a valid buffer for error reason.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 154 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with fanIndex from config file, fanSpeed = FAN_SPEED_MEDIUM, pErrReason = valid buffer| fanIndex from config file, fanSpeed = FAN_SPEED_MEDIUM, pErrReason = valid buffer | status = RETURN_OK, pErrReason = FAN_ERR_NONE | Should be successful |
*/
void test_l1_platform_hal_positive3_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_MEDIUM;
    FAN_ERR pErrReason = FAN_ERR_NONE;
    INT status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex = %d, fanSpeed = %d, pErrReason = valid buffer.", FanIndex[i], fanSpeed);
        status = platform_hal_setFanSpeed(FanIndex[i], fanSpeed, &pErrReason);

        UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status, pErrReason);
        UT_ASSERT_EQUAL(status, RETURN_OK);
        UT_ASSERT_EQUAL(pErrReason, FAN_ERR_NONE);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive3_setFanSpeed...");
}

/**
* @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
*
* This test case verifies the functionality of the platform_hal_setFanSpeed API by invoking with fan index from config file, the fan speed as FAN_SPEED_FAST, and a valid buffer for error reason.
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
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with fanIndex from config file, fanSpeed = FAN_SPEED_FAST, pErrReason = valid buffer | fanIndex from config file, fanSpeed = FAN_SPEED_FAST, pErrReason = valid buffer | status = RETURN_OK, pErrReason = FAN_ERR_NONE | Should be successful |
*/
void test_l1_platform_hal_positive4_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive4_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_FAST;
    FAN_ERR pErrReason = FAN_ERR_NONE;
    INT status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex = %d, fanSpeed = %d, pErrReason = valid buffer", FanIndex[i], fanSpeed);
        status = platform_hal_setFanSpeed(FanIndex[i], fanSpeed, &pErrReason);

        UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status, pErrReason);
        UT_ASSERT_EQUAL(status, RETURN_OK);
        UT_ASSERT_EQUAL(pErrReason, FAN_ERR_NONE);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive4_setFanSpeed...");
}

/**
* @brief Test the functionality of the platform_hal_setFanSpeed function with a positive scenario.
*
* This test case verifies the functionality of the platform_hal_setFanSpeed API by invoking with fan index from config file, the fan speed as FAN_SPEED_MAX, and a valid buffer for error reason.
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
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with fanIndex from config file, fanSpeed = FAN_SPEED_MAX, pErrReason = valid buffer | fanIndex from config file, fanSpeed = FAN_SPEED_MAX, pErrReason = valid buffer | status = RETURN_OK, pErrReason = FAN_ERR_NONE  | Should be successful |
*/
void test_l1_platform_hal_positive5_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive5_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_MAX;
    FAN_ERR pErrReason = FAN_ERR_NONE;
    INT status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanSpeed with fanIndex = %d, fanSpeed = %d, pErrReason = valid buffer.", FanIndex[i], fanSpeed);
        status = platform_hal_setFanSpeed(FanIndex[i], fanSpeed, &pErrReason);

        UT_LOG("platform_hal_setFanSpeed API returns : %d, error reason: %d", status, pErrReason);
        UT_ASSERT_EQUAL(status, RETURN_OK);
        UT_ASSERT_EQUAL(pErrReason, FAN_ERR_NONE);
    }

    UT_LOG("Exiting test_l1_platform_hal_positive5_setFanSpeed...");
}

/**
* @brief This test case is used to verify the negative scenario of the platform_hal_setFanSpeed API.
*
* The objective of this test is to check the behavior of the platform_hal_setFanSpeed API when invalid fan speed is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 157 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with valid fanIndex from config file, invalid fanSpeed = 5, pErrReason = valid buffer | fanIndex from config file, fanSpeed = 5, pErrReason = valid buffer | status = RETURN_ERR , pErrReason = FAN_ERR_HW or FAN_ERR_MAX_OVERRIDE_SET | Should return error |
*/
void test_l1_platform_hal_negative1_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_setFanSpeed...");
    FAN_SPEED fanSpeed = 5;
    FAN_ERR pErrReason = FAN_ERR_NONE;
    INT status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanSpeed with valid fanIndex = %d, invalid fanSpeed = %d, pErrReason = valid buffer.", FanIndex[i], fanSpeed);
        status = platform_hal_setFanSpeed(FanIndex[i], fanSpeed, &pErrReason);

        UT_LOG("platform_hal_setFanSpeed API returns : %d", status);
        UT_LOG("pErrReason : %d", pErrReason);
        UT_ASSERT_EQUAL(status, RETURN_ERR);

        if(pErrReason == 1)
        {
            UT_LOG("Status of the Error is: %d  ",pErrReason);
            UT_PASS("platform_hal_setFanSpeed validation success with FAN_ERR_HW.");
        }
        else if (pErrReason == 2)
        {
            UT_LOG("Status of the Error is: %d  ",pErrReason);
            UT_PASS("platform_hal_setFanSpeed  validation success with FAN_ERR_MAX_OVERRIDE_SET.");
        }
        else
        {
            UT_LOG("Status of the Error is: %d ",pErrReason);
            UT_FAIL("platform_hal_setFanSpeed  validation failed with invalid errror reason.");
        }
    }
    UT_LOG("Exiting test_l1_platform_hal_negative1_setFanSpeed...");
}

/**
* @brief This test function is used to verify the negative scenario of the platform_hal_setFanSpeed API.
*
* This test checks the behavior of the platform_hal_setFanSpeed API when the fanIndex from config file, fanSpeed is FAN_SPEED_OFF, and the error reason is NULL.
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
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_setFanSpeed with fanIndex from config file, fanSpeed = FAN_SPEED_OFF, pErrReason = NULL | fanIndex = 0, fanSpeed = FAN_SPEED_OFF, pErrReason = NULL | RETURN_ERR | Should return error|
*/
void test_l1_platform_hal_negative2_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_setFanSpeed...");
    FAN_SPEED fanSpeed = FAN_SPEED_OFF;
    FAN_ERR *pErrReason = NULL;
    INT status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_setFanSpeed with valid fanIndex = %d and fanSpeed = %d , pErrReason = NULL.", FanIndex[i], fanSpeed);
        status = platform_hal_setFanSpeed(FanIndex[i], fanSpeed, pErrReason);

        UT_LOG("platform_hal_setFanSpeed API returns : %d", status);
        UT_ASSERT_EQUAL(status, RETURN_ERR);
    }

    UT_LOG("Exiting test_l1_platform_hal_negative2_setFanSpeed...");
}

/**
* @brief This test case is used to verify the negative scenario of the platform_hal_setFanSpeed API.
*
* The objective of this test is to check the behavior of the platform_hal_setFanSpeed API when invalid fan speed is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 159 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 |  Invoking platform_hal_setFanSpeed with invalid fanIndex = 2, valid fanSpeed = FAN_SPEED_OFF, pErrReason = valid buffer | fanIndex = 2, fanSpeed = FAN_SPEED_OFF, pErrReason = valid buffer | RETURN_ERR | The function should return RETURN_ERR |
*/
void test_l1_platform_hal_negative3_setFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_setFanSpeed...");
    INT fanIndex = 2;
    FAN_SPEED fanSpeed = FAN_SPEED_OFF;
    FAN_ERR pErrReason = FAN_ERR_NONE;

    UT_LOG("Invoking platform_hal_setFanSpeed with invalid fanIndex = %d, valid fanSpeed = %d, pErrReason = valid buffer.", fanIndex, fanSpeed);
    INT status = platform_hal_setFanSpeed(fanIndex, fanSpeed, &pErrReason);

    UT_LOG("platform_hal_setFanSpeed API returns : %d", status);
    UT_LOG("pErrReason : %d", pErrReason);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    if(pErrReason == 1)
    {
        UT_LOG("Status of the Error is: %d.",pErrReason);
        UT_PASS("platform_hal_setFanSpeed validation success with FAN_ERR_HW.");
    }
    else if (pErrReason == 2)
    {
        UT_LOG("Status of the Error is: %d.",pErrReason);
        UT_PASS("platform_hal_setFanSpeed  validation success with FAN_ERR_MAX_OVERRIDE_SET ");
    }
    else
    {
        UT_LOG("Status of the Error is: %d.",pErrReason);
        UT_FAIL("platform_hal_setFanSpeed  validation failed with invalid errror reason ");
    }
    UT_LOG("Exiting test_l1_platform_hal_negative3_setFanSpeed...");
}

/**
* @brief Test case for platform_hal_getInputPower function normal operation
*
* This test case tests the normal operation of the platform_hal_getInputPower function.
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
* | 01 | Invoking platform_hal_getInputPower with value = valid buffer | value = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_getInputPower(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getInputPower...");
    INT value = 0;

    UT_LOG("Invoking platform_hal_getInputPower with value = valid buffer");
    INT status = platform_hal_getInputPower(&value);

    UT_LOG("platform_hal_getInputPower returns : %d", status);
    UT_LOG("Input Power: %d", value);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if(value > 0)
    {
        UT_LOG("Input Power is %d which is a valid value", value);
        UT_PASS (" Get Input Power Validation success");
    }
    else
    {
        UT_LOG("Input Power is %d which is an invalid value", value);
        UT_FAIL(" Get Input Power Validation Failure");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_getInputPower...");
}

/**
* @brief Test for platform_hal_getInputPower function when passed a NULL pointer.
*
* This test is for the platform_hal_getInputPower function when passed a NULL pointer as the input parameter. The objective of this test is to verify that the function correctly handles the NULL pointer and returns the appropriate error status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 161 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_getInputPower with value = NULL | value = NULL | RETURN_ERR | Should return error status |
*/
void test_l1_platform_hal_negative1_getInputPower(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getInputPower...");
    INT *value = NULL;
    UT_LOG("Invoking platform_hal_getInputPower with value = NULL");
    INT status = platform_hal_getInputPower(value);

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
* **Test Case ID:** 162 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetCPUSpeed with buffer = valid buffer | buffer = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetCPUSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetCPUSpeed...");
    char buffer[16]= {"\0"};

    UT_LOG("Invoking platform_hal_GetCPUSpeed with buffer = valid buffer.");
    INT ret = platform_hal_GetCPUSpeed(buffer);

    UT_LOG("The processor speed is: %s", buffer);
    UT_LOG("platform_hal_GetCPUSpeed returns : %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetCPUSpeed...");
}

/**
* @brief Test case to verify the behavior of platform_hal_GetCPUSpeed when NULL buffer is passed as input.
*
* This test case checks if platform_hal_GetCPUSpeed returns RETURN_ERR when NULL buffer is passed as input.
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
* | 01 | Invoking platform_hal_GetCPUSpeed with value = NULL | value = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetCPUSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetCPUSpeed...");
    CHAR *value = NULL;

    UT_LOG("Invoking platform_hal_GetCPUSpeed with value = NULL");
    INT ret = platform_hal_GetCPUSpeed(value);

    UT_LOG("platform_hal_GetCPUSpeed returns : %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetCPUSpeed...");
}

/**
* @brief Test case to verify the functionality of the GetFreeMemorySize API.
*
* This test case verifies that the GetFreeMemorySize API is able to successfully operate and return a total available memory size in the valid range [1, n].
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
* | :--------: | ---------| ------ | -------------| ----- |
* | 01| Invoking platform_hal_GetFreeMemorySize with size = valid buffer | size = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetFreeMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetFreeMemorySize...");
    ULONG size = 0;

    UT_LOG("Invoking platform_hal_GetFreeMemorySize with size = valid buffer");
    int result = platform_hal_GetFreeMemorySize(&size);

    UT_LOG("platform_hal_GetFreeMemorySize returns : %d, size: %lu", result, size);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    if(size > 0)
    {
        UT_LOG("Free Memory Size  is %lu", size);
        UT_PASS (" Free Memory Size  Validation success");
    }
    else
    {
        UT_LOG("Free Memory Size  is %lu", size);
        UT_FAIL(" Free Memory Size Validation Failure");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetFreeMemorySize...");
}

/**
* @brief Test case to verify the behavior of the platform_hal_GetFreeMemorySize function when called with a NULL pointer.
*
* This test case checks if the platform_hal_GetFreeMemorySize function returns the expected result when called with a NULL pointer as the input parameter.
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
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetFreeMemorySize with pulSize = NULL| pulSize = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetFreeMemorySize(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetFreeMemorySize...");
    ULONG *pulSize = NULL;

    UT_LOG("Invoking platform_hal_GetFreeMemorySize with pulSize = NULL");
    int result = platform_hal_GetFreeMemorySize(pulSize);

    UT_LOG("platform_hal_GetFreeMemorySize returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetFreeMemorySize...");
}

/**
* @brief Test function to verify the behavior of platform_hal_getTimeOffSet API.
*
* This test function verifies the behavior of the platform_hal_getTimeOffSet API by checking the return value and expected values of the timeOffSet buffer.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 166 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_getTimeOffSet API with timeOffSet = valid buffer | timeOffSet = valid buffer | Status = RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_getTimeOffSet(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getTimeOffSet...");
    CHAR timeOffSet[256] = {"\0"};

    UT_LOG("Invoking platform_hal_getTimeOffSet with timeOffSet = valid buffer");
    INT status = platform_hal_getTimeOffSet(timeOffSet);

    UT_LOG("platform_hal_getTimeOffSet returns : %d and timeOffSet is : %s ", status,timeOffSet);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if (!strcmp(timeOffSet,"-25200") || !strcmp(timeOffSet,"-18000")|| !strcmp(timeOffSet,"+25200"))
    {
        UT_LOG("Time Offset value from the device is %s which is a valid value", timeOffSet);
        UT_PASS("Get Time Offset validation success");
    }
    else
    {
        UT_LOG("Time Offset value from the device %s which is an Invalid value", timeOffSet);
        UT_FAIL("Time Offset validation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getTimeOffSet...");
}

/**
* @brief Test case to verify the behavior of platform_hal_getTimeOffSet API with a null pointer.
*
* This test case verifies whether platform_hal_getTimeOffSet API returns RETURN_ERR when invoked with a null pointer.
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
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_getTimeOffSet() with timeOffSet = NULL | timeOffSet = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_getTimeOffSet(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getTimeOffSet...");
    CHAR *timeOffSet = NULL;

    UT_LOG("Invoking platform_hal_getTimeOffSet with timeOffSet = NULL");
    INT status = platform_hal_getTimeOffSet(timeOffSet);

    UT_LOG("platform_hal_getTimeOffSet returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_getTimeOffSet...");
}

/**
* @brief Test to verify the platform_hal_getFactoryPartnerId API
*
* This test is used to verify the functionality of the platform_hal_getFactoryPartnerId API. The purpose of this test is to check if the API returns the expected status and valid value from config file.
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
* | 01 | Invoking platform_hal_getFactoryPartnerId with valid pValue from config file| pValue  from config file  | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_getFactoryPartnerId(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getFactoryPartnerId...");
    CHAR pValue[512] = {"\0"};
    CHAR partnerID[512] = {"\0"};

    UT_LOG("Invoking platform_hal_getFactoryPartnerId with pValue = valid buffer.");
    INT status = platform_hal_getFactoryPartnerId(pValue);

    UT_LOG("platform_hal_getFactoryPartnerId returns : %d and Factory Partner Id is : %s", status, pValue);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    //PartnerID should be configured in platform_config file
    strcpy(partnerID, PartnerID);

    if (!strcmp(pValue,partnerID))
    {
        UT_LOG("Factory Patner ID from the device is %s which is a valid value", pValue);
        UT_PASS("Get Factory Patner ID validation success");
    }
    else
    {
        UT_LOG("Factory Patner ID  from the device %s which is an Invalid value", pValue);
        UT_FAIL("Get Factory Patner ID validation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFactoryPartnerId...");
}

/**
* @brief This test case is to verify the functionality of the platform_hal_getFactoryPartnerId function when a null pointer is passed as the parameter.
*
* The objective of this test is to check the return status of the platform_hal_getFactoryPartnerId function when a null pointer is passed as the parameter. The expected result is RETURN_ERR.
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
*  | Variation / Step | Description | Test Data | Expected Result | Notes |
*  | :----: | --------- | ---------- | -------------- | ----- |
*  | 01 | Invoking platform_hal_getFactoryPartnerId with pValue = NULL | pValue = NULL | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_getFactoryPartnerId(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_getFactoryPartnerId...");
    CHAR *pValue = NULL;

    UT_LOG("Invoking platform_hal_getFactoryPartnerId with pValue = NULL.");
    INT status = platform_hal_getFactoryPartnerId(pValue);

    UT_LOG("platform_hal_getFactoryPartnerId returns: %d", status);
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
* **Test Case ID:** 170 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platfom_hal_initLed() with config_file_name = valid buffer | config_file_name = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_initLed( void )
{
    UT_LOG("Entering test_l1_platform_hal_positive1_initLed...");
    INT result = 0;
    CHAR config_file_name[512]= {"\0"};

    UT_LOG("Invoking the API platform_hal_initLed with config_file_name = valid buffer.");
    result = platform_hal_initLed(config_file_name);

    UT_LOG("platform_hal_initLed API returns : %d", result);
    UT_LOG("Config File name : %s.", config_file_name );
    UT_ASSERT_EQUAL( result, RETURN_OK );
    UT_ASSERT_PTR_NOT_NULL(config_file_name);

    UT_LOG("Exiting test_l1_platform_hal_positive1_initLed");
}

/**
* @brief This function checks if platfom_hal_initLed() works as expected
*
* Calls the header function platfom_hal_initLed() with NULL pointer
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 171 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platfom_hal_initLed() with config_file_name = NULL| config_file_name = NULL| RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_initLed( void )
{
    UT_LOG("Entering test_l1_platform_hal_negative1_initLed...");
    INT result = 0;
    CHAR *config_file_name = NULL;
    UT_LOG("Invoking the API platform_hal_initLed with config_file_name = NULL.");
    result = platform_hal_initLed(config_file_name);

    UT_LOG("platform_hal_initLed API returns : %d", result);
    UT_ASSERT_EQUAL( result, RETURN_ERR );

    UT_LOG("Exiting test_l1_platform_hal_negative1_initLed...");
}
#endif

/**
* @brief This test function is used to verify the functionality of the platform_hal_getFanStatus() API.
*
* The objective of this test is to check if the API returns the correct fan status when called with valid famIndex from config file.
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
* | Variation / Step | Description| Test Data | Expected Result| Notes|
* | :----:| ---------| ----------|-----------| -----|
* | 01| Invoking the API platform_hal_getFanStatus with fanIndex from config file| fanIndex from config file| Returns 0 or 1 | Should be successful |
*/
void test_l1_platform_hal_positive1_getFanStatus(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getFanStatus...");
    BOOLEAN status = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking the API platform_hal_getFanStatus  with fanIndex = %d.", FanIndex[i]);
        status = platform_hal_getFanStatus(FanIndex[i]);

        UT_LOG("Status of the fan is %d",status);
        if(status == 0)
        {
            UT_LOG("Status of the fan is %d and it is disabled.", status);
            UT_PASS("Get Fan Status Validation success");
        }
        else if(status == 1 )
        {
            UT_LOG("Status of the fan is %d and it is enabled", status);
            UT_PASS("Get Fan Status Validation success");
        }
        else
        {
            UT_LOG("Status of the fan is %d", status);
            UT_FAIL("Get Fan Status Validation Failed");
        }
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFanStatus...");
}

/**
* @brief Test case to validate the platform_hal_getFanSpeed function for positive scenario using a specific fan index.
*
* This test case is used to validate the platform_hal_getFanSpeed function by invoking it with fan index from config file and checking the returned fan speed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 173 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_getFanSpeed with fanIndex from config file | fanIndex from config file | fanSpeed >= 0 |  Should be successful|
*/
void test_l1_platform_hal_positive1_getFanSpeed(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_getFanSpeed...");
    UINT fanSpeed = 0;
    int i = 0;

    for( i = 0;i < num_FanIndex; i++)
    {
        //FanIndex should be configured in platform_config file
        UT_LOG("Invoking platform_hal_getFanSpeed with fanIndex = %d.", FanIndex[i]);
        fanSpeed = platform_hal_getFanSpeed(FanIndex[i]);

        UT_LOG("Received fanSpeed = %d", fanSpeed);
        if (fanSpeed >= 0)
        {
            UT_LOG("Fan Speed is %d, which is a valid value.", fanSpeed);
            UT_PASS("Get Fan Speed validation success");
        }
        else
        {
            UT_LOG("Fan Speed is %d, which is an invalid value.", fanSpeed);
            UT_FAIL("Get Fan Speed validation failed");
        }
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_getFanSpeed...");
}

/**
* @brief Test case to verify the functionality of platform_hal_GetSSHEnable function
*
* This test case validates the functionality of the platform_hal_GetSSHEnable function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 174 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data| Expected Result | Notes|
* | :--------: | -----------| ---------| ----------| --------- |
* |01| Invoking platform_hal_GetSSHEnable with pFlag = valid buffer | pFlag = valid buffer| RETURN_OK |Should be successful|
*/
void test_l1_platform_hal_positive1_GetSSHEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetSSHEnable...");
    BOOLEAN pFlag = FALSE;

    UT_LOG("Invoking platform_hal_GetSSHEnable with pFlag = valid buffer");
    INT status = platform_hal_GetSSHEnable(&pFlag);

    UT_LOG("platform_hal_GetSSHEnable returns : %d", status);
    UT_LOG("pFlag: %d", pFlag);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    if(pFlag == TRUE || pFlag == FALSE )
    {
        UT_LOG("SSH Enable is %d", pFlag);
        UT_PASS("Get SSH Enable validation success");
    }
    else
    {
        UT_LOG("SSH Enable is %d", pFlag);
        UT_FAIL(" Get SSH Enable Validation failure");
    }

    UT_LOG("Exiting test_l1_platform_hal_positive1_GetSSHEnable...");
}

/**
* @brief Test case to verify the platform_hal_GetSSHEnable function
*
* This test case is used to verify the behavior of the platform_hal_GetSSHEnable function with NULL input.
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
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Test function platform_hal_GetSSHEnable with pFlag = NULL| pFlag = NULL | RETURN_ERR| Should return error |
*/
void test_l1_platform_hal_negative1_GetSSHEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetSSHEnable...");
    BOOLEAN *pFlag = NULL;

    UT_LOG("Invoking platform_hal_GetSSHEnable with pFlag = NULL");
    INT status = platform_hal_GetSSHEnable(pFlag);

    UT_LOG("platform_hal_GetSSHEnable returns : %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to TRUE.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to TRUE and return a success status.
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
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_SetSSHEnable with pFlag = TRUE | pFlag = TRUE | RETURN_OK | Should be successful|
*/
void test_l1_platform_hal_positive1_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetSSHEnable...");
    BOOLEAN pFlag = TRUE;

    UT_LOG("Invoking platform_hal_SetSSHEnable with pFlag = %d.", pFlag);
    INT returnValue = platform_hal_SetSSHEnable(pFlag);

    UT_LOG("platform_hal_SetSSHEnable returns : %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_SetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to FALSE.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to FALSE and return a success status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 177 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 |Invoking platform_hal_SetSSHEnable with  pFlag = FALSE| pFlag = FALSE | RETURN_OK | Should be successful|
*/
void test_l1_platform_hal_positive2_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetSSHEnable...");
    BOOLEAN pFlag = TRUE;

    UT_LOG("Invoking platform_hal_SetSSHEnable with  pFlag = %d.", pFlag);
    INT returnValue = platform_hal_SetSSHEnable(pFlag);

    UT_LOG("platform_hal_SetSSHEnable returns: %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_SetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to 2.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to 2 and return a failure status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 178 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_SetSSHEnable with invalid pFlag = 2 | pFlag = 2 | RETURN_ERR | Should return error  |
*/
void test_l1_platform_hal_negative1_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetSSHEnable...");
    BOOLEAN pFlag = 2;

    UT_LOG("Invoking platform_hal_SetSSHEnable with invalid pFlag = %d.", pFlag);
    INT returnValue = platform_hal_SetSSHEnable(pFlag);

    UT_LOG("platform_hal_SetSSHEnable returns : %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetSSHEnable...");
}

/**
* @brief This test case is used to verify the functionality of the platform_hal_SetSSHEnable() API by setting the SSH enable flag to 'a'.
*
* The objective of this test is to ensure that the platform_hal_SetSSHEnable() API is able to set the SSH enable flag to 'a' and return a failure status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 179 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_SetSSHEnable with invalid flag = 'a' | pFlag = 'a' | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative2_SetSSHEnable( void )
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetSSHEnable...");
    BOOLEAN pFlag = 'a';

    UT_LOG("Invoking platform_hal_SetSSHEnable with invalid flag = 'a'.");
    INT returnValue = platform_hal_SetSSHEnable(pFlag);

    UT_LOG("platform_hal_SetSSHEnable returns : %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_SetSSHEnable...");
}

/**
* @brief This test is used to verify the reset of DSCP counts for the DOCSIS interface type.
*
* The objective of this test is to ensure that the platform_hal_resetDscpCounts function successfully resets the DSCP counts for the DOCSIS interface type.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 180 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_resetDscpCounts with interfaceType = DOCSIS | interfaceType = DOCSIS | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_resetDscpCounts(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_resetDscpCounts...");
    WAN_INTERFACE interfaceType = DOCSIS;

    UT_LOG("Invoking platform_hal_resetDscpCounts with interfaceType = %d.", interfaceType);
    INT result = platform_hal_resetDscpCounts(interfaceType);

    UT_LOG("platform_hal_resetDscpCounts returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_resetDscpCounts...");
}

/**
* @brief Test the function platform_hal_resetDscpCounts for positive cases.
*
* This test case is used to verify the functionality of the platform_hal_resetDscpCounts function when the interface type is EWAN.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_resetDscpCounts with interfaceType = EWAN | interfaceType = EWAN | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_resetDscpCounts(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_resetDscpCounts...");
    WAN_INTERFACE interfaceType = EWAN;

    UT_LOG("Invoking platform_hal_resetDscpCounts with interfaceType = %d.", interfaceType);
    INT result = platform_hal_resetDscpCounts(interfaceType);

    UT_LOG("platform_hal_resetDscpCounts returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Existing test_l1_platform_hal_positive2_resetDscpCounts...");
}

/**
* @brief Test case to verify the behavior of the function platform_hal_resetDscpCounts
*
* This test case verifies the behavior of the platform_hal_resetDscpCounts function when an invalid interface type is provided as input.
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
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking platform_hal_resetDscpCounts with an invalid interfaceType = 5| interfaceType = 5 | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_resetDscpCounts(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_resetDscpCounts...");
    WAN_INTERFACE interfaceType = 5;

    UT_LOG("Invoking platform_hal_resetDscpCounts with an invalid interfaceType = %d", interfaceType);
    INT result = platform_hal_resetDscpCounts(interfaceType);

    UT_LOG("platform_hal_resetDscpCounts returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_resetDscpCounts...");
}

/**
* @brief This function checks if platform_hal_PandMDBInit() works as expected
*
* Calls the header function platform_hal_PandMDBInit() with no params
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 183 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platform_hal_PandMDBInit| None | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_PandMDBInit( void )
{
	UT_LOG("Entering test_l1_platform_hal_positive1_PandMDBInit...");
	INT result = 0;

	UT_LOG("Invoking the API platform_hal_PandMDBInit.");
	result = platform_hal_PandMDBInit();

	UT_LOG("platform_hal_PandMDBInit API returns : %d", result);
	UT_ASSERT_EQUAL( result, RETURN_OK );

	UT_LOG("Exiting test_l1_platform_hal_positive1_PandMDBInit...");
}

/**
* @brief Test function to verify the behavior of platform_hal_GetTelnetEnable() function.
*
* This test case is used to verify the functionality and correctness of the platform_hal_GetTelnetEnable() function.
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_GetTelnetEnable with pFlag = valid buffer | pFlag = valid buffer| RETURN_OK| Should be successful |
*/
void test_l1_platform_hal_positive1_GetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetTelnetEnable...");
    INT result = 0;
    BOOLEAN pFlag = FALSE;

    UT_LOG("Invoking platform_hal_GetTelnetEnable with pFlag = valid buffer.");
    result = platform_hal_GetTelnetEnable(&pFlag);

    UT_LOG("platform_hal_GetTelnetEnable returns :  %d and flag value: %d", result, pFlag);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    if(pFlag == TRUE || pFlag == FALSE )
    {
        UT_LOG("Telnet Enable is %d", pFlag);
        UT_PASS("Get Telnet Enable validation success");
    }
    else
    {
        UT_LOG("Telnet Enable is %d", pFlag);
        UT_FAIL(" Get Telnet Enable Validation failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetTelnetEnable...");
}

/**
* @brief Test function to verify the behavior of platform_hal_GetTelnetEnable() function.
*
* This test case is used to verify the functionality and correctness of the platform_hal_GetTelnetEnable() function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 185 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke platform_hal_GetTelnetEnable with pFlag = NULL  | pFlag = NULL |  RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_GetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetTelnetEnable...");
    INT result = 0;
    BOOLEAN *pFlag = NULL;

    UT_LOG("Invoking platform_hal_GetTelnetEnable with pFlag = NULL");
    result = platform_hal_GetTelnetEnable(pFlag);

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
* **Test Case ID:** 186 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| Invoke platform_hal_DocsisParamsDBInit| None | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_DocsisParamsDBInit( void )
{
    UT_LOG("Entering test_l1_platform_hal_positive1_DocsisParamsDBInit...");
    INT result = 0;

    UT_LOG("Invoking the API platform_hal_DocsisParamsDBInit");
    result = platform_hal_DocsisParamsDBInit();

    UT_LOG("platform_hal_DocsisParamsDBInit API returns : %d", result);
    UT_ASSERT_EQUAL( result, RETURN_OK );
    UT_LOG("Exiting test_l1_platform_hal_positive1_DocsisParamsDBInit...");
}

/**
* @brief This is a unit test to verify the functionality of the platform_hal_SetTelnetEnable API when the flag is set to TRUE.
*
* This test case checks the behavior of the platform_hal_SetTelnetEnable API when the flag is set to TRUE. The objective is to ensure that the API sets the Telnet enable flag correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 187 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with Flag = TRUE | Flag = TRUE | RETURN_OK | Should be Successful |
*/
void test_l1_platform_hal_positive1_SetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_SetTelnetEnable...");
    BOOLEAN Flag = TRUE;

    UT_LOG("Invoking platform_hal_SetTelnetEnable with Flag = %d.", Flag);
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
* **Test Case ID:** 188 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with Flag = FALSE | Flag = FALSE | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_SetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_SetTelnetEnable...");
    BOOLEAN Flag = FALSE;

    UT_LOG("Invoking platform_hal_SetTelnetEnable with Flag = %d.", Flag);
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
* **Test Case ID:** 189 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with invalid Flag = 2 | Flag = 2 | RETURN_ERR | Should Fail |
*/
void test_l1_platform_hal_negative1_SetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_SetTelnetEnable...");
    BOOLEAN Flag = 2;

    UT_LOG("Invoking platform_hal_SetTelnetEnable with invalid Flag = %d.", Flag);
    INT result = platform_hal_SetTelnetEnable(Flag);

    UT_LOG("platform_hal_SetTelnetEnable API returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_SetTelnetEnable...");
}

/**
* @brief This is a unit test to verify the functionality of the platform_hal_SetTelnetEnable API when the flag is set to 'a'.
*
* This test case checks the behavior of the platform_hal_SetTelnetEnable API when the flag is set to 'a'.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 190 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_SetTelnetEnable with invalid Flag = 'a' | Flag = 'a' | RETURN_ERR | Should Fail |
*/
void test_l1_platform_hal_negative2_SetTelnetEnable(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_SetTelnetEnable...");
    BOOLEAN Flag = 'a';

    UT_LOG("Invoking platform_hal_SetTelnetEnable with invalid Flag = 'a'");
    INT result = platform_hal_SetTelnetEnable(Flag);

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
* | 01 | Invoke platform_hal_StopMACsec with valid ethPort = 0| ethPort = 0 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_StopMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_StopMACsec...");
    INT ethPort = 0;

    UT_LOG("Invoking platform_hal_StopMACsec with valid ethPort = %d", ethPort);
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
* **Test Case ID:** 192 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_StopMACsec valid ethPort = MaxEthPort-1   | ethPort = MaxEthPort - 1 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive2_StopMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_StopMACsec...");
    //MaxEthPort should be configured in platform_config file
    INT ethPort = MaxEthPort - 1;

    UT_LOG("Invoking platform_hal_StopMACsec with valid ethPort = %d", ethPort);
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
* **Test Case ID:** 193 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_StopMACsec valid ethPort = 2 | ethPort = 2 | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive3_StopMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive3_StopMACsec...");
    //MaxEthPort should be configured in platform_config file
    INT ethPort = rand() % (MaxEthPort-1);

    UT_LOG("Invoking platform_hal_StopMACsec with valid ethPort = %d", ethPort);
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
* **Test Case ID:** 194 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_StopMACsec invalid ethPort = -1  | ethPort = -1 | RETURN_ERR | Should return error |
*/
void test_l1_platform_hal_negative1_StopMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_StopMACsec...");
    INT ethPort = -1;

    UT_LOG("Invoking platform_hal_StopMACsec with invalid ethPort = %d", ethPort);
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
* **Test Case ID:** 195 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_StopMACsec invalid ethPort = MaxEthPort| ethPort = MaxEthPort | RETURN_ERR | Should return error|
*/
void test_l1_platform_hal_negative2_StopMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_StopMACsec...");
    //MaxEthPort should be configured in platform_config file
    INT ethPort = MaxEthPort;

    UT_LOG("Invoking platform_hal_StopMACsec with invalid ethPort = %d", ethPort);
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
* **Test Case ID:** 196 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke platform_hal_StopMACsec invalid ethPort = MaxEthPort + 1| ethPort = MaxEthPort + 1 | RETURN_ERR | Should return error|
*/
void test_l1_platform_hal_negative3_StopMACsec(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_StopMACsec...");
    //MaxEthPort should be configured in platform_config file
    INT ethPort = MaxEthPort + 1;

    UT_LOG("Invoking platform_hal_StopMACsec with invalid ethPort = %d", ethPort);
    INT result = platform_hal_StopMACsec(ethPort);

    UT_LOG("platform_hal_StopMACsec API returns : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_StopMACsec...");
}

/**
* @brief Test case to check the functionality of the function GetInterfaceStats when passed valid interface names.
*
* This test case checks if the function GetInterfaceStats properly retrieves the interface statistics when passed valid interface names from config file. @n
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetInterfaceStats with valid interface names from config file | ifname from config file | RETURN_OK | Should be successful |
*/
void test_l1_platform_hal_positive1_GetInterfaceStats(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_GetInterfaceStats...");
    int i = 0;
    INT retStatus = 0;
    PINTF_STATS pIntfStats = (PINTF_STATS)malloc(sizeof(INTF_STATS));
    UT_LOG("Number of InterfaceNames values : %d ", num_InterfaceNames);
    if(pIntfStats != NULL)
    {
        for (i = 0; i < num_InterfaceNames; i++ )
        {
            //InterfaceNames should be configured in platform_config file
            UT_LOG("Invoking platform_hal_GetInterfaceStats with valid interface = %s", InterfaceNames[i]);
            retStatus = platform_hal_GetInterfaceStats(InterfaceNames[i], pIntfStats);
            UT_LOG("platform_hal_GetInterfaceStats returns: %d", retStatus);
            UT_ASSERT_EQUAL(retStatus, RETURN_OK);

            if ((pIntfStats->rx_packet >= 0) && (pIntfStats->rx_packet <= (pow(2,64) - 1)))
            {
                UT_LOG("Packets received  is: %lu which is an valid value",pIntfStats->rx_packet);
                UT_PASS("Get Interface Stats validation success");
            }
            else
            {
                UT_LOG("Packets received  is: %lu which is an invalid value",pIntfStats->rx_packet);
                UT_FAIL("Get Interface Stats validation failed");
            }
            if ((pIntfStats->tx_packet >= 0) && (pIntfStats->tx_packet <= (pow(2,64) - 1)))
            {
                UT_LOG("Packets sent  is: %lu which is an valid value",pIntfStats->tx_packet);
                UT_PASS("Get Interface Stats validation success");
            }
            else
            {
                UT_LOG("Packets sent  is: %lu which is an invalid value",pIntfStats->tx_packet);
                UT_FAIL("Get Interface Stats validation failed");
            }
            if ((pIntfStats->rx_bytes >= 0) && (pIntfStats->rx_bytes <= (pow(2,64) - 1)))
            {
                UT_LOG("Bytes received  is: %lu which is an valid value",pIntfStats->rx_bytes);
                UT_PASS("Get Interface Stats validation success");
            }
            else
            {
                UT_LOG("Bytes received  is: %lu which is an invalid value",pIntfStats->rx_bytes);
                UT_FAIL("Get Interface Stats validation failed");
            }
            if ((pIntfStats->tx_bytes >= 0) && (pIntfStats->tx_bytes <= (pow(2,64) - 1)))
            {
                UT_LOG("Bytes sent  is: %lu which is an valid value",pIntfStats->tx_bytes);
                UT_PASS("Get Interface Stats validation success");
            }
            else
            {
                UT_LOG("Bytes sent  is: %lu which is an invalid value",pIntfStats->tx_bytes);
                UT_FAIL("Get Interface Stats validation failed");
            }
        }
        free(pIntfStats);
        pIntfStats = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_platform_hal_positive1_GetInterfaceStats...");
}

/**
* @brief Test case to verify the behavior when the interface name is NULL.
*
* This test case verifies the behavior of the GetInterfaceStats function when the interface name is NULL. The objective of this test is to ensure that the function handles the NULL interface name parameter correctly. @n
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
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoking platform_hal_GetInterfaceStats with ifname as NULL | ifname = NULL | RETURN_ERR | Should fail |
*/
void test_l1_platform_hal_negative1_GetInterfaceStats(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_GetInterfaceStats...");
    char* ifname = NULL;
    INT retStatus = 0;

    PINTF_STATS pIntfStats = (PINTF_STATS)malloc(sizeof(INTF_STATS));
    if(pIntfStats != NULL)
    {
        UT_LOG("Invoking platform_hal_GetInterfaceStats with ifname as NULL ");
        retStatus = platform_hal_GetInterfaceStats(ifname, pIntfStats);
        UT_LOG("platform_hal_GetInterfaceStats returns : %d",retStatus);
        UT_ASSERT_EQUAL(retStatus, RETURN_ERR);

        free(pIntfStats);
        pIntfStats = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_negative1_GetInterfaceStats...");
}

/**
* @brief Test case to verify the behavior of the GetInterfaceStats function when the interface name is empty.
*
* This test case is intended to verify the behavior of the GetInterfaceStats function when the interface name is an empty string. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 199 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking platform_hal_GetInterfaceStats with ifname as an empty string | ifname = "" | RETURN_ERR | Should fail |
*/
void test_l1_platform_hal_negative2_GetInterfaceStats(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_GetInterfaceStats...");
    char* ifname = "";
    INT retStatus = 0;

    PINTF_STATS pIntfStats = (PINTF_STATS)malloc(sizeof(INTF_STATS));
    if(pIntfStats != NULL)
    {
        UT_LOG("Invoking platform_hal_GetInterfaceStats with ifname as an empty string ");
        retStatus = platform_hal_GetInterfaceStats(ifname, pIntfStats);
        UT_LOG("platform_hal_GetInterfaceStats returns : %d",retStatus);
        UT_ASSERT_EQUAL(retStatus, RETURN_ERR);

        free(pIntfStats);
        pIntfStats = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_negative2_GetInterfaceStats...");
}

/**
* @brief This test case verifies the behavior of the *GetInterfaceStats* function when provided with an invalid interface name.
*
* The objective of this test is to ensure that the function returns the correct error status when an invalid interface name is passed as an argument. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 200 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetInterfaceStats with ifname as non-existing or invalid interface name | ifname = "eth99" | RETURN_ERR | Should fail |
*/
void test_l1_platform_hal_negative3_GetInterfaceStats(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_GetInterfaceStats...");
    char* ifname = "eth99";
    INT retStatus = 0;

    PINTF_STATS pIntfStats = (PINTF_STATS)malloc(sizeof(INTF_STATS));
    if(pIntfStats != NULL)
    {
        UT_LOG("Invoking platform_hal_GetInterfaceStats with ifname 'eth99' as non-existing or invalid interface name ");
        retStatus = platform_hal_GetInterfaceStats(ifname, pIntfStats);
        UT_LOG("platform_hal_GetInterfaceStats returns : %d",retStatus);
        UT_ASSERT_EQUAL(retStatus, RETURN_ERR);

        free(pIntfStats);
        pIntfStats = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_negative3_GetInterfaceStats...");
}

/**
* @brief This test case checks the behavior of the GetInterfaceStats function when pIntfStats pointer is NULL.
*
* This test is to verify that the GetInterfaceStats function returns RETURN_ERR when the pIntfStats pointer is NULL. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 201 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_GetInterfaceStats with pIntfStats as NULL  and valid interface from config file| pIntfStats = NULL, valid ifname from config file | RETURN_ERR | Should fail |
*/
void test_l1_platform_hal_negative4_GetInterfaceStats(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative4_GetInterfaceStats...");
    PINTF_STATS pIntfStats = NULL;
    INT retStatus = 0;
    int i = 0;

    UT_LOG("Number of InterfaceNames values : %d ", num_InterfaceNames);
    for (i = 0; i < num_InterfaceNames; i++ )
    {
        //InterfaceNames should be configured in platform_config file
        UT_LOG("Invoking platform_hal_GetInterfaceStats with pIntfStats as NULL and valid interface = %s",InterfaceNames[i]);
        retStatus = platform_hal_GetInterfaceStats(InterfaceNames[i], pIntfStats);
        UT_LOG("platform_hal_GetInterfaceStats returns : %d",retStatus);
        UT_ASSERT_EQUAL(retStatus, RETURN_ERR);
    }

    UT_LOG("Exiting test_l1_platform_hal_negative4_GetInterfaceStats...");
}

/**
* @brief This test case checks the behavior of the GetInterfaceStats function when provided with an interface name that contains special characters or spaces.
*
* The objective of this test is to verify that the function handles interface names with special characters correctly and returns the expected error code. @n
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
* | Variation / Step | Description | Test Data | Expected Result | Notes  |
* | :---------: | --------- | ----------- | --------- | ------- |
* | 01 | Invoking platform_hal_GetInterfaceStats with an interface name that contains special character | ifname = "eth0$" | RETURN_ERR | Should fail |
*/
void test_l1_platform_hal_negative5_GetInterfaceStats(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative5_GetInterfaceStats...");
    char* ifname = "eth0$";
    INT retStatus = 0;
    PINTF_STATS pIntfStats = (PINTF_STATS)malloc(sizeof(INTF_STATS));
    if(pIntfStats != NULL)
    {
        UT_LOG(" Invoking platform_hal_GetInterfaceStats with an interface name 'eth0$' that contains special character");
        retStatus = platform_hal_GetInterfaceStats(ifname, pIntfStats);
        UT_LOG("platform_hal_GetInterfaceStats returns : %d",retStatus);
        UT_ASSERT_EQUAL(retStatus, RETURN_ERR);

        free(pIntfStats);
        pIntfStats = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l1_platform_hal_negative5_GetInterfaceStats...");
}

/**
 * @brief This test case verifies the functionality of the platform_hal_GetPppUserName API
 * with valid input parameters.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 203 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppUserName with pUserName = valid buffer, maxSize = 128 | pUserName = valid buffer, maxSize = 128 | RETURN_OK | Should Pass |
 */
void test_l1_platform_hal_positive1_platform_hal_GetPppUserName(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_platform_hal_GetPppUserName...");

    CHAR pUserName[128] = {"\0"};
    ULONG maxSize = 128;

    UT_LOG("Invoking platform_hal_GetPppUserName() with pUserName = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppUserName(pUserName, maxSize);

    UT_LOG("PPP Username: %s", pUserName);
    UT_LOG("platform_hal_GetPppUserName API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_platform_hal_GetPppUserName...");
}

/**
 * @brief This test case verifies the behavior of platform_hal_GetPppUserName API
 * with a minimum buffer size that can store the username.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 204 @n
 * **Priority:** Medium @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppUserName with pUserName = valid buffer, maxSize = 6 | pUserName = valid buffer, maxSize = 6 | RETURN_OK | Should Pass |
 */
void test_l1_platform_hal_positive2_platform_hal_GetPppUserName(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_platform_hal_GetPppUserName...");

    CHAR pUserName[6] = {"\0"};  // Assuming username length is 5 + null terminator
    ULONG maxSize = sizeof(pUserName);

    UT_LOG("Invoking platform_hal_GetPppUserName() with pUserName = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppUserName(pUserName, maxSize);

    UT_LOG("PPP Username: %s", pUserName);
    UT_LOG("platform_hal_GetPppUserName API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_platform_hal_GetPppUserName...");
}

/**
 * @brief This test case verifies the behavior of platform_hal_GetPppUserName API
 * with insufficient buffer size.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 205 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppUserName with pUserName = valid buffer, maxSize = 4 | pUserName = valid buffer, maxSize = 4 | RETURN_ERR | Should Fail |
 */
void test_l1_platform_hal_negative1_platform_hal_GetPppUserName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_platform_hal_GetPppUserName...");

    CHAR pUserName[4] = {"\0"};  // Assuming username length > 4
    ULONG maxSize = sizeof(pUserName);

    UT_LOG("Invoking platform_hal_GetPppUserName() with pUserName = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppUserName(pUserName, maxSize);

    UT_LOG("platform_hal_GetPppUserName API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_platform_hal_GetPppUserName...");
}

/**
 * @brief This test case verifies the behavior of platform_hal_GetPppUserName API
 * when the buffer pointer is NULL.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 206 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppUserName with pUserName = NULL | pUserName = NULL, maxSize = 128 | RETURN_ERR | Should Fail |
 */
void test_l1_platform_hal_negative2_platform_hal_GetPppUserName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_platform_hal_GetPppUserName...");

    ULONG maxSize = 128;

    UT_LOG("Invoking platform_hal_GetPppUserName() with pUserName = NULL, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppUserName(NULL, maxSize);

    UT_LOG("platform_hal_GetPppUserName API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_platform_hal_GetPppUserName...");
}

/**
 * @brief This test case verifies the behavior of platform_hal_GetPppUserName API
 * when maxSize is zero.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 207 @n
 * **Priority:** Medium @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppUserName with maxSize = 0 | pUserName = valid buffer, maxSize = 0 | RETURN_ERR | Should Fail |
 */
void test_l1_platform_hal_negative3_platform_hal_GetPppUserName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_platform_hal_GetPppUserName...");

    CHAR pUserName[128] = {"\0"};
    ULONG maxSize = 0;

    UT_LOG("Invoking platform_hal_GetPppUserName() with pUserName = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppUserName(pUserName, maxSize);

    UT_LOG("platform_hal_GetPppUserName API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_platform_hal_GetPppUserName...");
}

/**
 * @brief This test case verifies the behavior of platform_hal_GetPppUserName API
 * with maxSize set to an edge value (ULONG_MAX).
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 208 @n
 * **Priority:** Low @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppUserName with maxSize = ULONG_MAX | pUserName = valid buffer, maxSize = ULONG_MAX | RETURN_OK or RETURN_ERR | Should Handle Edge Case |
 */
void test_l1_platform_hal_negative4_platform_hal_GetPppUserName(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative4_platform_hal_GetPppUserName...");

    CHAR pUserName[128] = {"\0"};
    ULONG maxSize = ULONG_MAX;

    UT_LOG("Invoking platform_hal_GetPppUserName() with pUserName = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppUserName(pUserName, maxSize);

    UT_LOG("platform_hal_GetPppUserName API returns: %d", status);
    UT_ASSERT((status == RETURN_OK) || (status == RETURN_ERR));

    UT_LOG("Exiting test_l1_platform_hal_negative4_platform_hal_GetPppUserName...");
}

/**
 * @brief Test case to verify the platform_hal_GetPppPassword() function in L1 platform HAL.
 *
 * This test case is used to verify the functionality of the platform_hal_GetPppPassword() function in L1 platform HAL. The objective is to ensure that the function returns RETURN_OK when valid inputs are provided.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 209 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppPassword with pPassword = valid buffer, maxSize = 128 | pPassword = valid buffer, maxSize = 128 | RETURN_OK | Should Pass |
 */
void test_l1_platform_hal_positive1_platform_hal_GetPppPassword(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_platform_hal_GetPppPassword...");

    CHAR pPassword[128] = {"\0"};
    ULONG maxSize = 128;

    UT_LOG("Invoking platform_hal_GetPppPassword() with pPassword = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppPassword(pPassword, maxSize);

    UT_LOG("PPP Password: %s", pPassword);
    UT_LOG("platform_hal_GetPppPassword API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive1_platform_hal_GetPppPassword...");
}

/**
 * @brief Test case to verify the platform_hal_GetPppPassword() function for minimum buffer size.
 *
 * This test case is used to verify the functionality of the platform_hal_GetPppPassword() function with the smallest possible valid buffer size that can store the password.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 210 @n
 * **Priority:** Medium @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppPassword with minimum valid buffer size | pPassword = valid buffer, maxSize = 6 | RETURN_OK | Should Pass |
 */
void test_l1_platform_hal_positive2_platform_hal_GetPppPassword(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive2_platform_hal_GetPppPassword...");

    CHAR pPassword[6] = {"\0"};  // Assuming password length is 5 + null terminator
    ULONG maxSize = sizeof(pPassword);

    UT_LOG("Invoking platform_hal_GetPppPassword() with pPassword = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppPassword(pPassword, maxSize);

    UT_LOG("PPP Password: %s", pPassword);
    UT_LOG("platform_hal_GetPppPassword API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_platform_hal_positive2_platform_hal_GetPppPassword...");
}

/**
 * @brief Test case to verify the platform_hal_GetPppPassword() function for insufficient buffer size.
 *
 * This test case is used to verify the behavior of the platform_hal_GetPppPassword() function when the buffer size is insufficient to store the password.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 211 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppPassword with insufficient buffer size | pPassword = valid buffer, maxSize = 4 | RETURN_ERR | Should Fail |
 */
void test_l1_platform_hal_negative1_platform_hal_GetPppPassword(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_platform_hal_GetPppPassword...");

    CHAR pPassword[4] = {"\0"};  // Assuming password length > 4
    ULONG maxSize = sizeof(pPassword);

    UT_LOG("Invoking platform_hal_GetPppPassword() with pPassword = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppPassword(pPassword, maxSize);

    UT_LOG("platform_hal_GetPppPassword API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative1_platform_hal_GetPppPassword...");
}

/**
 * @brief Test case to verify the platform_hal_GetPppPassword() function when a null pointer is passed.
 *
 * This test case is used to verify the behavior of the platform_hal_GetPppPassword() function when the buffer pointer is NULL.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 212 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppPassword with pPassword = NULL | pPassword = NULL, maxSize = 128 | RETURN_ERR | Should Fail |
 */
void test_l1_platform_hal_negative2_platform_hal_GetPppPassword(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_platform_hal_GetPppPassword...");

    ULONG maxSize = 128;

    UT_LOG("Invoking platform_hal_GetPppPassword() with pPassword = NULL, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppPassword(NULL, maxSize);

    UT_LOG("platform_hal_GetPppPassword API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative2_platform_hal_GetPppPassword...");
}

/**
 * @brief Test case to verify the platform_hal_GetPppPassword() function with maxSize set to zero.
 *
 * This test case is used to verify the behavior of the platform_hal_GetPppPassword() function when maxSize is zero.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 213 @n
 * **Priority:** Medium @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking platform_hal_GetPppPassword with maxSize = 0 | pPassword = valid buffer, maxSize = 0 | RETURN_ERR | Should Fail |
 */
void test_l1_platform_hal_negative3_platform_hal_GetPppPassword(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_platform_hal_GetPppPassword...");

    CHAR pPassword[128] = {"\0"};
    ULONG maxSize = 0;

    UT_LOG("Invoking platform_hal_GetPppPassword() with pPassword = valid buffer, maxSize = %lu.", maxSize);
    INT status = platform_hal_GetPppPassword(pPassword, maxSize);

    UT_LOG("platform_hal_GetPppPassword API returns: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_platform_hal_negative3_platform_hal_GetPppPassword...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function with valid IPv4 parameters.
*
* This test is to verify that the platform_hal_qos_apply function returns 0 for valid IPv4 input parameters. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 214 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply with valid IPv4 parameters | Valid IPv4 addresses, ports, and DSCP value | 0 | Should pass |
*/
void test_l1_platform_hal_positive1_platform_hal_qos_apply(void)
{
    UT_LOG("Entering test_l1_platform_hal_positive1_platform_hal_qos_apply...");
    hal_network_params_t params = {0};
    INT retStatus = 0;

    params.ip_version = IP_VERSION_IPV4;
    params.src_ip.ipv4 = 0x0A000001; // 10.0.0.1
    params.dest_ip.ipv4 = 0xC0A80001; // 192.168.0.1
    params.src_port = 1234;
    params.dest_port = 80;
    params.protocol = PROTOCOL_TCP;
    params.dscp_value = 10;

    UT_LOG("Invoking platform_hal_qos_apply with valid IPv4 parameters.");
    retStatus = platform_hal_qos_apply(&params);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_EQUAL(retStatus, 0);

    UT_LOG("Exiting test_l1_platform_hal_positive1_platform_hal_qos_apply...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function when the hal_network_params_t pointer is NULL.
*
* This test is to verify that the platform_hal_qos_apply function returns a negative value when the hal_network_params_t pointer is NULL. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 215 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply with NULL parameters | hal_network_params_t = NULL | Negative value | Should fail |
*/
void test_l1_platform_hal_negative1_platform_hal_qos_apply(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative1_platform_hal_qos_apply...");
    INT retStatus = 0;

    UT_LOG("Invoking platform_hal_qos_apply with NULL parameters.");
    retStatus = platform_hal_qos_apply(NULL);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_TRUE(retStatus < 0);

    UT_LOG("Exiting test_l1_platform_hal_negative1_platform_hal_qos_apply...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function with invalid DSCP values.
*
* This test is to verify that the platform_hal_qos_apply function returns a negative value when DSCP value is outside the valid range. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 216 @n
* **Priority:** Medium @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply with invalid DSCP value | DSCP = 64 (out of range) | Negative value | Should fail |
*/
void test_l1_platform_hal_negative2_platform_hal_qos_apply(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative2_platform_hal_qos_apply...");
    hal_network_params_t params = {0};
    INT retStatus = 0;

    params.dscp_value = 64; // Invalid DSCP value (valid range: 0-63)
    UT_LOG("Invoking platform_hal_qos_apply with DSCP value: %d", params.dscp_value);
    retStatus = platform_hal_qos_apply(&params);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_TRUE(retStatus < 0);

    UT_LOG("Exiting test_l1_platform_hal_negative2_platform_hal_qos_apply...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function with mismatched IP version.
*
* This test is to verify that the platform_hal_qos_apply function returns a negative value when the IP version and IP address do not match. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 217 @n
* **Priority:** Medium @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply with mismatched IP version and address | IPv4 version with IPv6 address | Negative value | Should fail |
*/
void test_l1_platform_hal_negative3_platform_hal_qos_apply(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative3_platform_hal_qos_apply...");
    hal_network_params_t params = {0};
    INT retStatus = 0;

    params.ip_version = IP_VERSION_IPV4;
    memcpy(params.src_ip.ipv6, (UINT8_t[]){0x20, 0x01, 0x0D, 0xB8, 0x85, 0xA3, 0x00, 0x00, 0x00, 0x00, 0x8A, 0x2E, 0x03, 0x70, 0x73, 0x34}, 16);

    UT_LOG("Invoking platform_hal_qos_apply with mismatched IP version.");
    retStatus = platform_hal_qos_apply(&params);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_TRUE(retStatus < 0);

    UT_LOG("Exiting test_l1_platform_hal_negative3_platform_hal_qos_apply...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function with invalid IP version.
*
* This test is to verify that the platform_hal_qos_apply function returns a negative value when an invalid IP version is provided. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 218 @n
* **Priority:** Medium @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply with an invalid IP version | IP version = 3 (invalid) | Negative value | Should fail |
*/
void test_l1_platform_hal_negative4_platform_hal_qos_apply(void)
{
    UT_LOG("test_l1_platform_hal_negative4_platform_hal_qos_apply...");
    hal_network_params_t params = {0};
    INT retStatus = 0;

    params.ip_version = 3; // Invalid IP version
    UT_LOG("Invoking platform_hal_qos_apply with invalid IP version.");
    retStatus = platform_hal_qos_apply(&params);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_TRUE(retStatus < 0);

    UT_LOG("Exiting test_l1_platform_hal_negative4_platform_hal_qos_apply...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function with missing source port.
*
* This test is to verify that the platform_hal_qos_apply function returns a negative value when the source port is not set. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 219 @n
* **Priority:** Medium @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply without a source port | src_port = 0 | Negative value | Should fail |
*/
void test_l1_platform_hal_negative5_platform_hal_qos_apply(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative5_platform_hal_qos_apply...");
    hal_network_params_t params = {0};
    INT retStatus = 0;

    params.ip_version = IP_VERSION_IPV4;
    params.src_ip.ipv4 = 0xC0A80001; // 192.168.0.1
    params.dest_ip.ipv4 = 0xC0A80002; // 192.168.0.2
    params.src_port = 0; // Missing source port
    params.dest_port = 8080;
    params.protocol = PROTOCOL_TCP;
    params.dscp_value = 20;

    UT_LOG("Invoking platform_hal_qos_apply without source port.");
    retStatus = platform_hal_qos_apply(&params);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_TRUE(retStatus < 0);

    UT_LOG("Exiting test_l1_platform_hal_negative5_platform_hal_qos_apply...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function with unsupported protocol.
*
* This test is to verify that the platform_hal_qos_apply function returns a negative value when an unsupported protocol is provided. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 220 @n
* **Priority:** Medium @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply with unsupported protocol | protocol = 999 (invalid) | Negative value | Should fail |
*/
void test_l1_platform_hal_negative6_platform_hal_qos_apply(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative6_platform_hal_qos_apply...");
    hal_network_params_t params = {0};
    INT retStatus = 0;

    params.ip_version = IP_VERSION_IPV4;
    params.src_ip.ipv4 = 0xC0A80001; // 192.168.0.1
    params.dest_ip.ipv4 = 0xC0A80002; // 192.168.0.2
    params.src_port = 1234;
    params.dest_port = 80;
    params.protocol = 999; // Unsupported protocol
    params.dscp_value = 30;

    UT_LOG("Invoking platform_hal_qos_apply with unsupported protocol.");
    retStatus = platform_hal_qos_apply(&params);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_TRUE(retStatus < 0);

    UT_LOG("Exiting test_l1_platform_hal_negative6_platform_hal_qos_apply...");
}

/**
* @brief This test case checks the behavior of the platform_hal_qos_apply function when source and destination IPs are the same.
*
* This test is to verify that the platform_hal_qos_apply function returns a negative value when the source and destination IPs are the same. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 221 @n
* **Priority:** Low @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking platform_hal_qos_apply with identical source and destination IPs | src_ip = dest_ip | Negative value | Should fail |
*/
void test_l1_platform_hal_negative7_platform_hal_qos_apply(void)
{
    UT_LOG("Entering test_l1_platform_hal_negative7_platform_hal_qos_apply...");
    hal_network_params_t params = {0};
    INT retStatus = 0;

    params.ip_version = IP_VERSION_IPV4;
    params.src_ip.ipv4 = 0xC0A80001; // 192.168.0.1
    params.dest_ip.ipv4 = 0xC0A80001; // Same as source IP
    params.src_port = 1234;
    params.dest_port = 80;
    params.protocol = PROTOCOL_UDP;
    params.dscp_value = 15;

    UT_LOG("Invoking platform_hal_qos_apply with identical source and destination IPs.");
    retStatus = platform_hal_qos_apply(&params);
    UT_LOG("platform_hal_qos_apply returns: %d", retStatus);
    UT_ASSERT_TRUE(retStatus < 0);

    UT_LOG("Exiting test_l1_platform_hal_negative7_platform_hal_qos_apply...");
}

static UT_test_suite_t * pSuite = NULL;

/**
* @brief Register the main tests for this module
*
* @return int - 0 on success, otherwise failure
*/
int test_platform_hal_l1_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 platform_hal]", init_platform_hal_init, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetFirmwareName", test_l1_platform_hal_positive1_GetFirmwareName);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetFirmwareName", test_l1_platform_hal_negative1_GetFirmwareName);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetSoftwareVersion", test_l1_platform_hal_positive1_GetSoftwareVersion);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetSoftwareVersion", test_l1_platform_hal_negative1_GetSoftwareVersion);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetSerialNumber", test_l1_platform_hal_positive1_GetSerialNumber);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetSerialNumber", test_l1_platform_hal_negative1_GetSerialNumber);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetSNMPEnable", test_l1_platform_hal_positive1_GetSNMPEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetSNMPEnable", test_l1_platform_hal_negative1_GetSNMPEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetHardware_MemUsed", test_l1_platform_hal_positive1_GetHardware_MemUsed);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetHardware_MemUsed", test_l1_platform_hal_negative1_GetHardware_MemUsed);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetHardwareVersion", test_l1_platform_hal_positive1_GetHardwareVersion);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetHardwareVersion", test_l1_platform_hal_negative1_GetHardwareVersion);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetModelName", test_l1_platform_hal_positive1_GetModelName);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetModelName", test_l1_platform_hal_negative1_GetModelName);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetRouterRegion", test_l1_platform_hal_positive1_GetRouterRegion);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetRouterRegion", test_l1_platform_hal_negative1_GetRouterRegion);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetBootloaderVersion", test_l1_platform_hal_positive1_GetBootloaderVersion);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetBootloaderVersion", test_l1_platform_hal_negative1_GetBootloaderVersion);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetHardware", test_l1_platform_hal_positive1_GetHardware);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetHardware", test_l1_platform_hal_negative1_GetHardware);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetSNMPEnable", test_l1_platform_hal_positive1_SetSNMPEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetSNMPEnable", test_l1_platform_hal_positive2_SetSNMPEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive3_SetSNMPEnable", test_l1_platform_hal_positive3_SetSNMPEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetSNMPEnable", test_l1_platform_hal_negative1_SetSNMPEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetSNMPEnable", test_l1_platform_hal_negative2_SetSNMPEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetWebUITimeout", test_l1_platform_hal_positive1_SetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetWebUITimeout", test_l1_platform_hal_positive2_SetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive3_SetWebUITimeout", test_l1_platform_hal_positive3_SetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive4_SetWebUITimeout", test_l1_platform_hal_positive4_SetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetWebUITimeout", test_l1_platform_hal_negative1_SetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetWebUITimeout", test_l1_platform_hal_negative2_SetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetWebUITimeout", test_l1_platform_hal_positive1_GetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetWebUITimeout", test_l1_platform_hal_negative1_GetWebUITimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetBaseMacAddress", test_l1_platform_hal_positive1_GetBaseMacAddress);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetBaseMacAddress", test_l1_platform_hal_negative1_GetBaseMacAddress);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetHardware_MemFree", test_l1_platform_hal_positive1_GetHardware_MemFree);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetHardware_MemFree", test_l1_platform_hal_negative1_GetHardware_MemFree);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetUsedMemorySize", test_l1_platform_hal_positive1_GetUsedMemorySize);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetUsedMemorySize", test_l1_platform_hal_negative1_GetUsedMemorySize);
    UT_add_test( pSuite, "l1_platform_hal_positive1_ClearResetCount", test_l1_platform_hal_positive1_ClearResetCount);
    UT_add_test( pSuite, "l1_platform_hal_positive2_ClearResetCount", test_l1_platform_hal_positive2_ClearResetCount);
    UT_add_test( pSuite, "l1_platform_hal_negative1_ClearResetCount", test_l1_platform_hal_negative1_ClearResetCount);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetDeviceCodeImageValid", test_l1_platform_hal_positive1_SetDeviceCodeImageValid);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetDeviceCodeImageValid", test_l1_platform_hal_positive2_SetDeviceCodeImageValid);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetDeviceCodeImageValid", test_l1_platform_hal_negative1_SetDeviceCodeImageValid);
    UT_add_test( pSuite, "l1_platform_hal_positive1_setFactoryCmVariant", test_l1_platform_hal_positive1_setFactoryCmVariant);
    UT_add_test( pSuite, "l1_platform_hal_negative1_setFactoryCmVariant", test_l1_platform_hal_negative1_setFactoryCmVariant);
    UT_add_test( pSuite, "l1_platform_hal_negative2_setFactoryCmVariant", test_l1_platform_hal_negative2_setFactoryCmVariant);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getLed", test_l1_platform_hal_positive1_getLed);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getLed", test_l1_platform_hal_negative1_getLed);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getRotorLock", test_l1_platform_hal_positive1_getRotorLock);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getRotorLock", test_l1_platform_hal_negative1_getRotorLock);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetTotalMemorySize", test_l1_platform_hal_positive1_GetTotalMemorySize);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetTotalMemorySize", test_l1_platform_hal_negative1_GetTotalMemorySize);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetFactoryResetCount", test_l1_platform_hal_positive1_GetFactoryResetCount);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetFactoryResetCount", test_l1_platform_hal_negative1_GetFactoryResetCount);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetDeviceCodeImageTimeout", test_l1_platform_hal_positive1_SetDeviceCodeImageTimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetDeviceCodeImageTimeout", test_l1_platform_hal_positive2_SetDeviceCodeImageTimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive3_SetDeviceCodeImageTimeout", test_l1_platform_hal_positive3_SetDeviceCodeImageTimeout);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetDeviceCodeImageTimeout", test_l1_platform_hal_negative1_SetDeviceCodeImageTimeout);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetDeviceCodeImageTimeout", test_l1_platform_hal_negative2_SetDeviceCodeImageTimeout);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getFactoryCmVariant", test_l1_platform_hal_positive1_getFactoryCmVariant);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getFactoryCmVariant", test_l1_platform_hal_negative1_getFactoryCmVariant);
    UT_add_test( pSuite, "l1_platform_hal_positive1_setLed", test_l1_platform_hal_positive1_setLed);
    UT_add_test( pSuite, "l1_platform_hal_negative1_setLed", test_l1_platform_hal_negative1_setLed);
    UT_add_test( pSuite, "l1_platform_hal_negative2_setLed", test_l1_platform_hal_negative2_setLed);
    UT_add_test( pSuite, "l1_platform_hal_negative3_setLed", test_l1_platform_hal_negative3_setLed);
    UT_add_test( pSuite, "l1_platform_hal_negative4_setLed", test_l1_platform_hal_negative4_setLed);
    UT_add_test( pSuite, "l1_platform_hal_negative5_setLed", test_l1_platform_hal_negative5_setLed);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getRPM", test_l1_platform_hal_positive1_getRPM);
#ifdef FEATURE_RDKB_THERMAL_MANAGER
    UT_add_test( pSuite, "l1_platform_hal_positive1_initThermal", test_l1_platform_hal_positive1_initThermal);
    UT_add_test( pSuite, "l1_platform_hal_negative1_initThermal", test_l1_platform_hal_negative1_initThermal);
    UT_add_test( pSuite, "l1_platform_hal_positive1_LoadThermalConfig", test_l1_platform_hal_positive1_LoadThermalConfig);
    UT_add_test( pSuite, "l1_platform_hal_negative1_LoadThermalConfig", test_l1_platform_hal_negative1_LoadThermalConfig);
    UT_add_test( pSuite, "l1_platform_hal_positive1_setFanSpeed", test_l1_platform_hal_positive1_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_positive2_setFanSpeed", test_l1_platform_hal_positive2_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_positive3_setFanSpeed", test_l1_platform_hal_positive3_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_positive4_setFanSpeed", test_l1_platform_hal_positive4_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_positive5_setFanSpeed", test_l1_platform_hal_positive5_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_negative1_setFanSpeed", test_l1_platform_hal_negative1_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_negative2_setFanSpeed", test_l1_platform_hal_negative2_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_negative3_setFanSpeed", test_l1_platform_hal_negative3_setFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getFanTemperature", test_l1_platform_hal_positive1_getFanTemperature);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getFanTemperature", test_l1_platform_hal_negative1_getFanTemperature);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getInputCurrent", test_l1_platform_hal_positive1_getInputCurrent);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getInputCurrent", test_l1_platform_hal_negative1_getInputCurrent);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getInputPower", test_l1_platform_hal_positive1_getInputPower);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getInputPower", test_l1_platform_hal_negative1_getInputPower);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getRadioTemperature", test_l1_platform_hal_positive1_getRadioTemperature);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getRadioTemperature", test_l1_platform_hal_negative1_getRadioTemperature);
    UT_add_test( pSuite, "l1_platform_hal_negative2_getRadioTemperature", test_l1_platform_hal_negative2_getRadioTemperature);
    UT_add_test( pSuite, "l1_platform_hal_positive2_getRadioTemperature", test_l1_platform_hal_positive2_getRadioTemperature);
    UT_add_test( pSuite, "l1_platform_hal_positive3_getRadioTemperature", test_l1_platform_hal_positive3_getRadioTemperature);
    UT_add_test( pSuite, "l1_platform_hal_positive1_platform_hal_getEcoModeStatus", test_l1_platform_hal_positive1_platform_hal_getEcoModeStatus);
    UT_add_test( pSuite, "l1_platform_hal_positive2_platform_hal_getEcoModeStatus", test_l1_platform_hal_positive2_platform_hal_getEcoModeStatus);
    UT_add_test( pSuite, "l1_platform_hal_positive3_platform_hal_getEcoModeStatus", test_l1_platform_hal_positive3_platform_hal_getEcoModeStatus);
    UT_add_test( pSuite, "l1_platform_hal_negative1_platform_hal_getEcoModeStatus", test_l1_platform_hal_negative1_platform_hal_getEcoModeStatus);
    UT_add_test( pSuite, "l1_platform_hal_negative2_platform_hal_getEcoModeStatus", test_l1_platform_hal_negative2_platform_hal_getEcoModeStatus);
    UT_add_test( pSuite, "l1_platform_hal_negative3_platform_hal_getEcoModeStatus", test_l1_platform_hal_negative3_platform_hal_getEcoModeStatus);
    UT_add_test( pSuite, "l1_platform_hal_negative4_platform_hal_getEcoModeStatus", test_l1_platform_hal_negative4_platform_hal_getEcoModeStatus);
#endif
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetMACsecEnable", test_l1_platform_hal_positive1_SetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetMACsecEnable", test_l1_platform_hal_positive2_SetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetMACsecEnable", test_l1_platform_hal_negative1_SetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive3_SetMACsecEnable", test_l1_platform_hal_positive3_SetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetMACsecEnable", test_l1_platform_hal_negative2_SetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetMemoryPaths", test_l1_platform_hal_positive1_GetMemoryPaths);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetMemoryPaths", test_l1_platform_hal_negative1_GetMemoryPaths);
    UT_add_test( pSuite, "l1_platform_hal_negative2_GetMemoryPaths", test_l1_platform_hal_negative2_GetMemoryPaths);
    UT_add_test( pSuite, "l1_platform_hal_negative3_GetMemoryPaths", test_l1_platform_hal_negative3_GetMemoryPaths);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetMACsecEnable", test_l1_platform_hal_positive1_GetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetMACsecEnable", test_l1_platform_hal_negative1_GetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative2_GetMACsecEnable", test_l1_platform_hal_negative2_GetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive2_GetMACsecEnable", test_l1_platform_hal_positive2_GetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive3_GetMACsecEnable", test_l1_platform_hal_positive3_GetMACsecEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_StartMACsec", test_l1_platform_hal_positive1_StartMACsec);
    UT_add_test( pSuite, "l1_platform_hal_negative1_StartMACsec", test_l1_platform_hal_negative1_StartMACsec);
    UT_add_test( pSuite, "l1_platform_hal_positive2_StartMACsec", test_l1_platform_hal_positive2_StartMACsec);
    UT_add_test( pSuite, "l1_platform_hal_positive3_StartMACsec", test_l1_platform_hal_positive3_StartMACsec);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetDhcpv6_Options", test_l1_platform_hal_positive1_GetDhcpv6_Options);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetDhcpv6_Options", test_l1_platform_hal_negative1_GetDhcpv6_Options);
    UT_add_test( pSuite, "l1_platform_hal_negative2_GetDhcpv6_Options", test_l1_platform_hal_negative2_GetDhcpv6_Options);
    UT_add_test( pSuite, "l1_platform_hal_negative3_GetDhcpv6_Options", test_l1_platform_hal_negative3_GetDhcpv6_Options);
    UT_add_test( pSuite, "l1_platform_hal_positive1_setDscp", test_l1_platform_hal_positive1_setDscp);
    UT_add_test( pSuite, "l1_platform_hal_positive2_setDscp", test_l1_platform_hal_positive2_setDscp);
    UT_add_test( pSuite, "l1_platform_hal_positive3_setDscp", test_l1_platform_hal_positive3_setDscp);
    UT_add_test( pSuite, "l1_platform_hal_positive4_setDscp", test_l1_platform_hal_positive4_setDscp);
    UT_add_test( pSuite, "l1_platform_hal_negative1_setDscp", test_l1_platform_hal_negative1_setDscp);
    UT_add_test( pSuite, "l1_platform_hal_negative2_setDscp", test_l1_platform_hal_negative2_setDscp);
    UT_add_test( pSuite, "l1_platform_hal_negative3_setDscp", test_l1_platform_hal_negative3_setDscp);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetLowPowerModeState", test_l1_platform_hal_positive1_SetLowPowerModeState);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetLowPowerModeState", test_l1_platform_hal_negative1_SetLowPowerModeState);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetLowPowerModeState", test_l1_platform_hal_negative2_SetLowPowerModeState);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetFirmwareBankInfo", test_l1_platform_hal_positive1_GetFirmwareBankInfo);
    UT_add_test( pSuite, "l1_platform_hal_positive2_GetFirmwareBankInfo", test_l1_platform_hal_positive2_GetFirmwareBankInfo);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetFirmwareBankInfo", test_l1_platform_hal_negative1_GetFirmwareBankInfo);
    UT_add_test( pSuite, "l1_platform_hal_negative2_GetFirmwareBankInfo", test_l1_platform_hal_negative2_GetFirmwareBankInfo);
    UT_add_test( pSuite, "l1_platform_hal_negative3_GetFirmwareBankInfo", test_l1_platform_hal_negative3_GetFirmwareBankInfo);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getCMTSMac", test_l1_platform_hal_positive1_getCMTSMac);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getCMTSMac", test_l1_platform_hal_negative1_getCMTSMac);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetDhcpv4_Options", test_l1_platform_hal_positive1_GetDhcpv4_Options);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetDhcpv4_Options", test_l1_platform_hal_negative1_GetDhcpv4_Options);
    UT_add_test( pSuite, "l1_platform_hal_negative2_GetDhcpv4_Options", test_l1_platform_hal_negative2_GetDhcpv4_Options);
    UT_add_test( pSuite, "l1_platform_hal_negative3_GetDhcpv4_Options", test_l1_platform_hal_negative3_GetDhcpv4_Options);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getDscpClientList", test_l1_platform_hal_positive1_getDscpClientList);
    UT_add_test( pSuite, "l1_platform_hal_positive2_getDscpClientList", test_l1_platform_hal_positive2_getDscpClientList);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getDscpClientList", test_l1_platform_hal_negative1_getDscpClientList);
    UT_add_test( pSuite, "l1_platform_hal_negative2_getDscpClientList", test_l1_platform_hal_negative2_getDscpClientList);
    UT_add_test( pSuite, "l1_platform_hal_negative3_getDscpClientList", test_l1_platform_hal_negative3_getDscpClientList);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetDeviceConfigStatus", test_l1_platform_hal_positive1_GetDeviceConfigStatus);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetDeviceConfigStatus", test_l1_platform_hal_negative1_GetDeviceConfigStatus);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetSNMPOnboardRebootEnable", test_l1_platform_hal_positive1_SetSNMPOnboardRebootEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetSNMPOnboardRebootEnable", test_l1_platform_hal_positive2_SetSNMPOnboardRebootEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetSNMPOnboardRebootEnable", test_l1_platform_hal_negative1_SetSNMPOnboardRebootEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetSNMPOnboardRebootEnable", test_l1_platform_hal_negative2_SetSNMPOnboardRebootEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetMACsecOperationalStatus", test_l1_platform_hal_positive1_GetMACsecOperationalStatus);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetMACsecOperationalStatus", test_l1_platform_hal_negative1_GetMACsecOperationalStatus);
    UT_add_test( pSuite, "l1_platform_hal_positive1_setFanMaxOverride", test_l1_platform_hal_positive1_setFanMaxOverride);
    UT_add_test( pSuite, "l1_platform_hal_positive2_setFanMaxOverride", test_l1_platform_hal_positive2_setFanMaxOverride);
    UT_add_test( pSuite, "l1_platform_hal_negative1_setFanMaxOverride", test_l1_platform_hal_negative1_setFanMaxOverride);
    UT_add_test( pSuite, "l1_platform_hal_negative2_setFanMaxOverride", test_l1_platform_hal_negative2_setFanMaxOverride);
    UT_add_test( pSuite, "l1_platform_hal_negative3_setFanMaxOverride", test_l1_platform_hal_negative3_setFanMaxOverride);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetCPUSpeed", test_l1_platform_hal_positive1_GetCPUSpeed);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetCPUSpeed", test_l1_platform_hal_negative1_GetCPUSpeed);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetFreeMemorySize", test_l1_platform_hal_positive1_GetFreeMemorySize);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetFreeMemorySize", test_l1_platform_hal_negative1_GetFreeMemorySize);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getTimeOffSet", test_l1_platform_hal_positive1_getTimeOffSet);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getTimeOffSet", test_l1_platform_hal_negative1_getTimeOffSet);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getFactoryPartnerId", test_l1_platform_hal_positive1_getFactoryPartnerId);
    UT_add_test( pSuite, "l1_platform_hal_negative1_getFactoryPartnerId", test_l1_platform_hal_negative1_getFactoryPartnerId);
#ifdef FEATURE_RDKB_LED_MANAGER
    UT_add_test( pSuite, "l1_platform_hal_positive1_initLed", test_l1_platform_hal_positive1_initLed);
    UT_add_test( pSuite, "l1_platform_hal_negative1_initLed", test_l1_platform_hal_negative1_initLed);
#endif
    UT_add_test( pSuite, "l1_platform_hal_positive1_getFanStatus", test_l1_platform_hal_positive1_getFanStatus);
    UT_add_test( pSuite, "l1_platform_hal_positive1_getFanSpeed", test_l1_platform_hal_positive1_getFanSpeed);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetSSHEnable", test_l1_platform_hal_positive1_GetSSHEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetSSHEnable", test_l1_platform_hal_negative1_GetSSHEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetSSHEnable", test_l1_platform_hal_positive1_SetSSHEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetSSHEnable", test_l1_platform_hal_positive2_SetSSHEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetSSHEnable", test_l1_platform_hal_negative1_SetSSHEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetSSHEnable", test_l1_platform_hal_negative2_SetSSHEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_resetDscpCounts", test_l1_platform_hal_positive1_resetDscpCounts);
    UT_add_test( pSuite, "l1_platform_hal_positive2_resetDscpCounts", test_l1_platform_hal_positive2_resetDscpCounts);
    UT_add_test( pSuite, "l1_platform_hal_negative1_resetDscpCounts", test_l1_platform_hal_negative1_resetDscpCounts);
    UT_add_test( pSuite, "l1_platform_hal_positive1_PandMDBInit", test_l1_platform_hal_positive1_PandMDBInit);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetTelnetEnable", test_l1_platform_hal_positive1_GetTelnetEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetTelnetEnable", test_l1_platform_hal_negative1_GetTelnetEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_DocsisParamsDBInit", test_l1_platform_hal_positive1_DocsisParamsDBInit);
    UT_add_test( pSuite, "l1_platform_hal_positive1_SetTelnetEnable", test_l1_platform_hal_positive1_SetTelnetEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive2_SetTelnetEnable", test_l1_platform_hal_positive2_SetTelnetEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative1_SetTelnetEnable", test_l1_platform_hal_negative1_SetTelnetEnable);
    UT_add_test( pSuite, "l1_platform_hal_negative2_SetTelnetEnable", test_l1_platform_hal_negative2_SetTelnetEnable);
    UT_add_test( pSuite, "l1_platform_hal_positive1_StopMACsec", test_l1_platform_hal_positive1_StopMACsec);
    UT_add_test( pSuite, "l1_platform_hal_positive2_StopMACsec", test_l1_platform_hal_positive2_StopMACsec);
    UT_add_test( pSuite, "l1_platform_hal_positive3_StopMACsec", test_l1_platform_hal_positive3_StopMACsec);
    UT_add_test( pSuite, "l1_platform_hal_negative1_StopMACsec", test_l1_platform_hal_negative1_StopMACsec);
    UT_add_test( pSuite, "l1_platform_hal_negative2_StopMACsec", test_l1_platform_hal_negative2_StopMACsec);
    UT_add_test( pSuite, "l1_platform_hal_negative3_StopMACsec", test_l1_platform_hal_negative3_StopMACsec);
    UT_add_test( pSuite, "l1_platform_hal_positive1_GetInterfaceStats", test_l1_platform_hal_positive1_GetInterfaceStats);
    UT_add_test( pSuite, "l1_platform_hal_negative1_GetInterfaceStats", test_l1_platform_hal_negative1_GetInterfaceStats);
    UT_add_test( pSuite, "l1_platform_hal_negative2_GetInterfaceStats", test_l1_platform_hal_negative2_GetInterfaceStats);
    UT_add_test( pSuite, "l1_platform_hal_negative3_GetInterfaceStats", test_l1_platform_hal_negative3_GetInterfaceStats);
    UT_add_test( pSuite, "l1_platform_hal_negative4_GetInterfaceStats", test_l1_platform_hal_negative4_GetInterfaceStats);
    UT_add_test( pSuite, "l1_platform_hal_negative5_GetInterfaceStats", test_l1_platform_hal_negative5_GetInterfaceStats);
    UT_add_test( pSuite, "l1_platform_hal_positive1_platform_hal_GetPppUserName", test_l1_platform_hal_positive1_platform_hal_GetPppUserName);
    UT_add_test( pSuite, "l1_platform_hal_positive2_platform_hal_GetPppUserName", test_l1_platform_hal_positive2_platform_hal_GetPppUserName);
    UT_add_test( pSuite, "l1_platform_hal_negative1_platform_hal_GetPppUserName", test_l1_platform_hal_negative1_platform_hal_GetPppUserName);
    UT_add_test( pSuite, "l1_platform_hal_negative2_platform_hal_GetPppUserName", test_l1_platform_hal_negative2_platform_hal_GetPppUserName);
    UT_add_test( pSuite, "l1_platform_hal_negative3_platform_hal_GetPppUserName", test_l1_platform_hal_negative3_platform_hal_GetPppUserName);
    UT_add_test( pSuite, "l1_platform_hal_negative4_platform_hal_GetPppUserName", test_l1_platform_hal_negative4_platform_hal_GetPppUserName);
    UT_add_test( pSuite, "l1_platform_hal_positive1_platform_hal_GetPppPassword", test_l1_platform_hal_positive1_platform_hal_GetPppPassword);
    UT_add_test( pSuite, "l1_platform_hal_positive2_platform_hal_GetPppPassword", test_l1_platform_hal_positive2_platform_hal_GetPppPassword);
    UT_add_test( pSuite, "l1_platform_hal_negative1_platform_hal_GetPppPassword", test_l1_platform_hal_negative1_platform_hal_GetPppPassword);
    UT_add_test( pSuite, "l1_platform_hal_negative2_platform_hal_GetPppPassword", test_l1_platform_hal_negative2_platform_hal_GetPppPassword);
    UT_add_test( pSuite, "l1_platform_hal_negative3_platform_hal_GetPppPassword", test_l1_platform_hal_negative3_platform_hal_GetPppPassword);
    UT_add_test( pSuite, "l1_platform_hal_positive1_platform_hal_qos_apply", test_l1_platform_hal_positive1_platform_hal_qos_apply);
    UT_add_test( pSuite, "l1_platform_hal_negative1_platform_hal_qos_apply", test_l1_platform_hal_negative1_platform_hal_qos_apply);
    UT_add_test( pSuite, "l1_platform_hal_negative2_platform_hal_qos_apply", test_l1_platform_hal_negative2_platform_hal_qos_apply);
    UT_add_test( pSuite, "l1_platform_hal_negative3_platform_hal_qos_apply", test_l1_platform_hal_negative3_platform_hal_qos_apply);
    UT_add_test( pSuite, "l1_platform_hal_negative4_platform_hal_qos_apply", test_l1_platform_hal_negative4_platform_hal_qos_apply);
    UT_add_test( pSuite, "l1_platform_hal_negative5_platform_hal_qos_apply", test_l1_platform_hal_negative5_platform_hal_qos_apply);
    UT_add_test( pSuite, "l1_platform_hal_negative6_platform_hal_qos_apply", test_l1_platform_hal_negative6_platform_hal_qos_apply);
    UT_add_test( pSuite, "l1_platform_hal_negative7_platform_hal_qos_apply", test_l1_platform_hal_negative7_platform_hal_qos_apply);

    return 0;
}
