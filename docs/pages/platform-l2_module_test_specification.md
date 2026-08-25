### Test 1

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetTelnetEnable_SetTelnetEnable|
|Description|Test the functionality of getting and setting the Telnet enable status using platform_hal_GetTelnetEnable and platform_hal_SetTelnetEnable APIs. This will ensure that the Telnet enable status can be properly fetched and updated.|
|Test Group|Module (L2): 02|
|Test Case ID|001|
|Priority|High|

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** If the user chooses to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get the current Telnet status by invoking platform_hal_GetTelnetEnable. | currentStatus=buffer | RETURN_OK | Should be successful |
| 02 | If Telnet is currently enabled, disable it by invoking platform_hal_SetTelnetEnable. | Enable=FALSE | RETURN_OK | Should be successful |
| 03 | After disabling Telnet, validate the status is actually disabled by invoking platform_hal_GetTelnetEnable again. | currentStatus=buffer | RETURN_OK and currentStatus=FALSE | Should be successful |

### Test 2

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetSSHEnable_SetSSHEnable|
|Description|This test examines the functionality of the SSH enablement setting and obtaining operations using the platform_hal_GetSSHEnable and platform_hal_SetSSHEnable functions.|
|Test Group|Module : 02|
|Test Case ID|002|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get the current SSH status using platform_hal_GetSSHEnable | SSHStatus = &SSHStatus | RETURN_OK | Should be successful |
| 02 | If SSH is enabled, disable SSH using platform_hal_SetSSHEnable function | SSHStatus = false | RETURN_OK | Should be successful |
| 03 | Recheck SSH status using platform_hal_GetSSHEnable to validate it is disabled | SSHStatus = &SSHStatus | RETURN_OK, SSHStatus: false | Should be successful |

### Test 3

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetSNMPEnable_SetSNMPEnable_GetSNMPEnable|
|Description|This test evaluates the functionality of getting and setting the SNMP enable status using the GetSNMPEnable and SetSNMPEnable functions.|
|Test Group|Module : 02|
|Test Case ID|003|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get the current SNMP status by invoking l2_platform_hal_GetSNMPEnable() | oldValue = valid buffer | RETURN_OK | Should be successful |
| 02 | If SNMP is enabled, disable it using the l2_platform_hal_SetSNMPEnable() function | oldValue = FALSE | RETURN_OK | Should be successful |
| 03 | Validate that the SNMP status is disabled by invoking l2_platform_hal_GetSNMPEnable() | oldValue = valid buffer | RETURN_OK | Should be successful |
| 04 | If SNMP is disabled, enable it using the l2_platform_hal_SetSNMPEnable() function | oldValue = TRUE | RETURN_OK | Should be successful |
| 05 | Validate that the SNMP status is enabled by invoking l2_platform_hal_GetSNMPEnable() | oldValue = valid buffer | RETURN_OK | Should be successful |

### Test 4

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetWebUITimeout_SetWebUITimeout_GetWebUITimeout|
|Description|This test checks for the functionality of getting and setting Web UI timeout.|
|Test Group|Module : 02|
|Test Case ID|004|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If the user chooses to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get current Web UI timeout using platform_hal_GetWebUITimeout | timeoutValue = reference to valid ULONG variable | RETURN_OK | Should be successful |
| 02 | Check the value of timeout. If it's equal to 300, update it to 500 | timeoutValue = 300 | N/A | N/A |
|03| Set the updated WebUI timeout value using platform_hal_SetWebUITimeout, if any.| newTimeoutValue = 500| Not checked in the code provided. | Not checked in the code provided. |
|04| Get the updated Web UI timeout value to validate the modification.| timeoutValue = reference to valid ULONG variable | Not checked in the code provided. | Not checked in the code provided. |


### Test 5

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetHardware_GetHardware_MemUsed|
|Description|This test verifies the value returned by the GetHardware_MemUsed function of the l2_platform_hal system. The test function checks if the memory utilization information of the hardware platform is retrieved successfully or not.|
|Test Group|Module : 02|
|Test Case ID|005|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Output logging info Entering test_l2_platform_hal_GetHardware_GetHardware_MemUsed... | UT_LOG function call | Success of UT_LOG function | Should be successful |
| 02 | Define a return value returnValue and initialize it with 0 | intValue = 0 | Confirmation of variable initialization | Should be successful |
| 03 | Define a buffer for total flash memory totalFlash and initialize it with an empty string | CHAR totalFlash[BUFFER_SIZE] = {'\0'} | Confirmation of buffer initialization | Should be successful |

### Test 6

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetHardware_GetHardware_MemFree|
|Description|This test verifies the functionality of getting hardware and memory free status in the Layer 2 platform HAL operations. It checks if the return statuses for hardware and memory are correct when the respective operations are performed.|
|Test Group|Module : 02|
|Test Case ID|006|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initiate logging for the test | log = Entering test_l2_platform_hal_GetHardware_GetHardware_MemFree... | None | Should be successful |
| 02 | Initialize the statuses for hardware and memoryfree to zero | hw_status = 0, mem_free_status = 0 | None | Should be successful |
| 03 | Initialize the flash memory to null character | flash_memory = "\0" | None | Should be successful |


### Test 7

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetHardware_GetHardware_MemUsed_GetHardware_MemFree|
|Description|Test the functionality of getting the used and free memory in hardware using `GetHardware_MemUsed` and `GetHardware_MemFree` functions|
|Test Group|Module : 02|
|Test Case ID|007|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
|01| Set totalFlash as an empty buffer. | totalFlash = empty buffer | N/A | N/A |
|02| Call the function GetHardware to get the total hardware memory. | totalFlash = buffer with memory size | Expected to fetch the memory size | Should be successful |
|03| Call the function GetHardware_MemUsed to get the used memory. | totalFlash = buffer with memory size | Returns the size of used memory | Should be successful |
|04| Call the function GetHardware_MemFree to get the free memory. | totalFlash = buffer with memory size | Returns the size of free memory | Should be successful |

### Test 8

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize|
|Description|Test the functionality of getting total memory size and used memory size using platform_hal_GetTotalMemorySize and platform_hal_GetUsedMemorySize. Verify if the used memory size is less than or equal to total memory size.|
|Test Group|Module : 02|
|Test Case ID|008|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get total memory size using platform_hal_GetTotalMemorySize | totalMemorySize = valid ULONG pointer | RETURN_OK | Should be successful |
| 02 | If success, get used memory size using platform_hal_GetUsedMemorySize | usedMemorySize = valid ULONG pointer | RETURN_OK | Should be successful |
| 03 | Verify if the used memory size is less than or equal to total memory size | usedMemorySize, totalMemorySize | Used Memory is smaller than Total Memory | Should be successful |

### Test 9

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetTotalMemorySize_GetFreeMemorySize|
|Description|The objective of this test is to ensure that the platform_hal_GetTotalMemorySize() and the platform_hal_GetFreeMemorySize() function calls return an acceptable status and that free memory is less than or equal to the total memory.|
|Test Group|Module : 02|
|Test Case ID|009|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Invoke the function platform_hal_GetTotalMemorySize() with a valid output parameter. | totalMemory = valid memory buffer | RETURN_OK | Should be successful |
| 02 | Invoke the function platform_hal_GetFreeMemorySize() with a valid output parameter. | freeMemory = valid memory buffer | RETURN_OK | Should be successful |
| 03 | Validation step- Check if free memory is smaller or equal to total memory. | freeMemory, totalMemory | freeMemory <= totalMemory | Should be successful |

### Test 10

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetTotalMemorySize_GetUsedMemorySize_GetFreeMemorySize|
|Description|This test aims to evaluate the functionality of retrieving the total memory size, used memory size, and free memory size using the platform_hal_GetTotalMemorySize, platform_hal_GetUsedMemorySize, and platform_hal_GetFreeMemorySize functions respectively, and to confirm memory consistency.|
|Test Group|Module : 02|
|Test Case ID|010|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Retrieving the total memory size using platform_hal_GetTotalMemorySize function | Output parameter = &totalMemorySize | RETURN_OK | Should be successful |
| 02 | Retrieving the used memory size using platform_hal_GetUsedMemorySize function | Output parameter = &usedMemorySize | RETURN_OK | Should be successful |
| 03 | Retrieving the free memory size using platform_hal_GetFreeMemorySize function | Output parameter = &freeMemorySize | RETURN_OK | Should be successful |
| 04 | Cross-verifying that the total memory size equals the sum of used memory size and free memory size | totalMemorySize = usedMemorySize + freeMemorySize | True | Should be successful |

### Test 11

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_GetFactoryResetCount_ClearResetCount_GetFactoryResetCount|
|Description|This test aims to verify the functionality of getting the factory reset count, clearing it, and getting the reset count again to validate correctness.|
|Test Group|Module : 02|
|Test Case ID|011|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get the factory reset count using platform_hal_GetFactoryResetCount | Address of pulSizeBefore variable  | RETURN_OK | Should be successful |
| 02 | Clear the factory reset count using platform_hal_ClearResetCount | bFlag = TRUE | RETURN_OK | Should be successful |
| 03 | Get the factory reset count again using platform_hal_GetFactoryResetCount after clearing  | Address of `pulSizeAfter` variable  | RETURN_OK | Should be successful |
| 04 | Check if factory reset count is zero after clearing | N/A | Zero | Should be successful |

### Test 12

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_getFactoryCmVariant_setFactoryCmVariant_getFactoryCmVariant|
|Description|This test evaluates the validity of the getFactoryCmVariant and setFactoryCmVariant APIs by first capturing the initial factory CM variant, setting a new variant, and then getting the variant to ensure the new set value matches.|
|Test Group|Module : 02|
|Test Case ID|012|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get the initial factory CM variant using getFactoryCmVariant API, saving the value to preSetValue | preSetValue = valid buffer | RETURN_OK | Should be successful |
| 02 | Set a new factory CM variant using setFactoryCmVariant API | New factory CM variant = TRUE | RETURN_OK | Should be successful |
| 03 | Get the factory CM variant after setting new value, save this to setValue | setValue = valid buffer | RETURN_OK | Should be successful |
| 04 | Compare the preSetValue and setValue to validate if the new set value is taken effect. | preSetValue, setValue = valid buffers | Both should not be equal | Should be successful |

### Test 13

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_setLed_getLed|
|Description|Test the functionality of setting and getting the LED status using platform_hal_setLed and platform_hal_getLed|
|Test Group|Module : 02|
|Test Case ID|013|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Set LED status using platform_hal_setLed | LedColor = LED_BLUE, State = 1, Interval = 5 | RETURN_OK | Should be successful |
| 02 | Get current LED status using platform_hal_getLed on allocated memory | getLEDStatus = valid malloc | RETURN_OK | Should be successful |
| 03 | Validate the returned LED status matches with the set status | getLEDStatus set earlier | RETURN_OK, LedColor = LED_BLUE, State = 1, Interval = 5 | Should be successful |

### Test 14

|Title|Details|
|--|--|
|Function Name|test_l2_platform_hal_MACsecEnableFunctions|
|Description|Test the functionality of getting and setting the MACsec enable status using platform_hal_GetMACsecEnable and platform_hal_SetMACsecEnable.|
|Test Group|Module: 02|
|Test Case ID|014|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes |
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Get the current MACsec status from the platform_hal_GetMACsecEnable function for ethernet port ethPort | ethPort = 0 to MaxEthPort, Flag = valid buffer | RETURN_OK | Should be successful |
| 02 | Toggle the Flag and set the new MACsec status using the platform_hal_SetMACsecEnable function | ethPort = 0 to MaxEthPort, Flag = !Flag | RETURN_OK | Should be successful |
| 03 | Validate the new MACsec status using platform_hal_GetMACsecEnable function | ethPort = 0 to MaxEthPort, NewFlag = valid buffer | RETURN_OK | Should be successful |
|04 | If the newly retrieved Flag(NewFlag) is same as the set Flag, then the MACsec status is set correctly | ethPort = 0 to MaxEthPort, Flag = !Flag, NewFlag = Flag | RETURN_OK | Should be successful |