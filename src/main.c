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
#include "cJSON.h"

extern int register_hal_l1_tests( void );

int MaxEthPort = 0;

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

int main(int argc, char** argv)
{
    int registerReturn = 0;
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

    UT_run_tests();
    
    return 0;
}

