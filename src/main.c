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

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include "platform_hal.h"

extern int MaxEthPort;
extern char PartnerID[512] ;
extern char** factoryCmVariant;
extern int num_FactoryCmVariant;
extern RDK_CPUS *supportedCpus;
extern int num_SupportedCPUs;
extern PSM_STATE *Supported_PSM_STATE;
extern int num_Supported_PSM_STATE;
extern int *FanIndex;
extern int num_FanIndex;

extern int register_hal_l1_tests( void );
extern int register_hal_l2_tests( void );
extern int get_MaxEthPort(void);
extern int get_PartnerID(void);
extern int get_FactoryCmVariant(void);
extern int get_SupportedCPUs(void);
extern int get_LowPowerModeStates(void);
extern int get_FanIndex(void);
extern void freeFactoryCmVariant(void);

int init_platform_hal_init(void)
{
    int ret = 0;
    ret = platform_hal_PandMDBInit();
    if (ret == 0)
    {
        UT_LOG("platform_hal_PandMDBInit returned success");
    }
    else
    {
        UT_LOG("platform_hal_PandMDBInit returned failure");
        UT_FAIL("platform_hal_PandMDBInit initialization failed");
    }

    ret = platform_hal_DocsisParamsDBInit();
    if (ret == 0)
    {
        UT_LOG("platform_hal_DocsisParamsDBInit returned success");
    }
    else
    {
        UT_LOG("platform_hal_DocsisParamsDBInit returned failure");
        UT_FAIL("platform_hal_DocsisParamsDBInit initialization failed");
    }
#ifdef FEATURE_RDKB_THERMAL_MANAGER
    THERMAL_PLATFORM_CONFIG *thermalConfig = (THERMAL_PLATFORM_CONFIG*)malloc(sizeof(THERMAL_PLATFORM_CONFIG));
    if(thermalConfig != NULL)
    {
        ret = platform_hal_initThermal(thermalConfig);
        if (ret == 0)
        {
            UT_LOG("platform_hal_initThermal returned success");
        }
        else
        {
            UT_LOG("platform_hal_initThermal returned failure");
            UT_FAIL("platform_hal_initThermal initialization failed");
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
#endif
    return 0;
}

int main(int argc, char** argv)
{
    int registerReturn = 0;
    int i = 0;
    if (get_MaxEthPort() == 0)
    {
        UT_LOG("Got the MaxEthPort value : %d", MaxEthPort);
    }
    else
    {
        printf("Failed to get MaxEthPort value\n");
    }

    if (get_PartnerID() == 0)
    {
        UT_LOG("Got the PartnerID value : %s", PartnerID);
    }
    else
    {
        printf("Failed to get PartnerID value\n");
    }
    if (get_FactoryCmVariant() == 0)
    {
        UT_LOG("Got the FactoryCmVariant values :\n");
        for (i = 0;i < num_FactoryCmVariant; i++)
        {
            UT_LOG("%s \n", factoryCmVariant[i]);
        }
    }
    else
    {
        printf("Failed to get FactoryCmVariant value\n");
    }
    if (get_SupportedCPUs() == 0)
    {
        UT_LOG("Got the SupportedCPUs values :\n");
        for (i = 0;i < num_SupportedCPUs; i++)
        {
            UT_LOG("%d \n", supportedCpus[i]);
        }
    }
    else
    {
        printf("Failed to get SupportedCPUs value\n");
    }
    if (get_LowPowerModeStates() == 0)
    {
        UT_LOG("Got the LowPowerModeStates values : ");
        for (i = 0;i < num_Supported_PSM_STATE; i++)
        {
            UT_LOG("%d \n", Supported_PSM_STATE[i]);
        }
    }
    else
    {
        printf("Failed to get LowPowerModeStates value\n");
    }

    if (get_FanIndex() == 0)
    {
        UT_LOG("Got the FanIndex values : ");
        for (i = 0;i < num_FanIndex; i++)
        {
            UT_LOG("%d \n", FanIndex[i]);
        }
    }
    else
    {
        printf("Failed to get FanIndex value\n");
    }

    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );
    /* Check if tests are registered successfully */
    registerReturn = register_hal_l1_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_l1_tests() returned success");
    }
    else
    {
        printf("register_hal_l1_tests() returned failure");
        return 1;
    }
    registerReturn = register_hal_l2_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_l2_tests() returned success");
    }
    else
    {
        printf("register_hal_l2_tests() returned failure");
        return 1;
    }
    UT_run_tests();

    freeFactoryCmVariant();
    free(supportedCpus);
    free(Supported_PSM_STATE);
    free(FanIndex);

    return 0;
}