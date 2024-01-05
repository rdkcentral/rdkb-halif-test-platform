Please find the mermaid flow of platform hal L2 Test cases:

### Test Function Name : test_l2_platform_hal_getset_TelnetEnable

```mermaid
flowchart TD
    A[Start Test Case 1] --> B(Call platform_hal_GetTelnetEnable)
    B --> C{Is Telnet <br> Enabled?}
    C -->|Yes| D["Disable Telnet<br>platform_hal_SetTelnetEnable(FALSE)"]
    C -->|No| E["Enable Telnet<br>platform_hal_SetTelnetEnable(TRUE)"]
    D --> F[Validate<br>Call platform_hal_GetTelnetEnable]
    E --> G[Validate<br>Call platform_hal_GetTelnetEnable]
    F -->|Telnet still Enabled| H[Test Case Fail<br>Telnet Not Disabled]
    F -->|Telnet Disabled| I[End Test Case<br>Success]
    G -->|Telnet still Disabled| J[Test Case Fail<br>Telnet Not Enabled]
    G -->|Telnet Enabled| I[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_SSHEnable

```mermaid
flowchart TD
    A[Start Test Case 2] --> B(Call platform_hal_GetSSHEnable)
    B --> C{Is SSH <br> Enabled?}
    C -->|Yes| D["Disable SSH<br>platform_hal_SetSSHEnable(FALSE)"]
    C -->|No| E["Enable SSH<br>platform_hal_SetSSHEnable(TRUE)"]
    D --> F[Validate<br>Call platform_hal_GetSSHEnable]
    E --> G[Validate<br>Call platform_hal_GetSSHEnable]
    F -->|SSH still Enabled| H[Test Case Fail<br>SSH Not Disabled]
    F -->|SSH Disabled| I[End Test Case<br>Success]
    G -->|SSH still Disabled| J[Test Case Fail<br>SSH Not Enabled]
    G -->|SSH Enabled| I[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_SNMPEnable

```mermaid
flowchart TD
    A[Start Test Case 3] --> B[Call platform_hal_GetSNMPEnable]
    B --> C{Current SNMP <br> Status}
    C -->|Enabled| D["Toggle to Disabled<br>platform_hal_SetSNMPEnable(Disabled)"]
    C -->|Disabled| E["Toggle to Enabled<br>platform_hal_SetSNMPEnable(Enabled)"]
    D --> F[Validate<br>Call platform_hal_GetSNMPEnable]
    E --> G[Validate<br>Call platform_hal_GetSNMPEnable]
    F -->|SNMP still Enabled| H[Test Case Fail<br>SNMP Not Disabled]
    F -->|SNMP Disabled| I[End Test Case<br>Success]
    G -->|SNMP still Disabled| J[Test Case Fail<br>SNMP Not Enabled]
    G -->|SNMP Enabled| I[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_WebUITimeout

```mermaid
flowchart TD
    A[Start Test Case 4] --> B[Call platform_hal_GetWebUITimeout]
    B -->|Success| C["Change Timeout<br>platform_hal_SetWebUITimeout(new value)"]
    B -->|Failure| X[Test Case Fail<br>Unable to Get Current Timeout]
    C -->|Success| D[Validate<br>Call platform_hal_GetWebUITimeout]
    C -->|Failure| Y[Test Case Fail<br>Unable to Set New Timeout]
    D --> E{Is New Timeout <br>Set?}
    E -->|Yes| F[End Test Case<br>Success]
    E -->|No| G[Test Case Fail<br>New Timeout Not Set]
```

### Test Function Name : test_l2_platform_hal_Memused_lesserthanor_equalto_flashMemory

```mermaid
flowchart TD
    A[Start Test Case 5] --> B[Invoke platform_hal_GetHardware]
    B -->|Success| C[Invoke platform_hal_GetHardware_MemUsed]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetHardware Failed]
    C -->|Success| D{Verify <br>Used Memory <= Total Flash Size}
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetHardware_MemUsed Failed]
    D -->|Yes| E[End Test Case<br>Success]
    D -->|No| F[Test Case Fail<br>Used Memory Exceeds Total Flash Size]
```

### Test Function Name : test_l2_platform_hal_MemFree_lesserthanor_equalto_flashMemory

```mermaid
flowchart TD
    A[Start Test Case 6] --> B[Invoke platform_hal_GetHardware]
    B -->|Success| C[Invoke platform_hal_GetHardware_MemFree]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetHardware Failed]
    C -->|Success| D{Verify <br> Free Memory <= Total Flash Memory}
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetHardware_MemFree Failed]
    D -->|Yes| E[End Test Case<br>Success]
    D -->|No| F[Test Case Fail<br>Free Memory Exceeds Total Flash Memory]
```

### Test Function Name : test_l2_platform_hal_checksumof_memusedandfree_equals_totalflash

```mermaid
flowchart TD
    A[Start Test Case 7] --> B[Invoke platform_hal_GetHardware]
    B -->|Success| C[Invoke platform_hal_GetHardware_MemUsed]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetHardware Failed]
    C -->|Success| D[Invoke platform_hal_GetHardware_MemFree]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetHardware_MemUsed Failed]
    D -->|Success| E{Verify Used + Free Memory = Total Flash}
    D -->|Failure| Z[Test Case Fail<br>platform_hal_GetHardware_MemFree Failed]
    E -->|Yes| F[End Test Case<br>Success]
    E -->|No| G[Test Case Fail<br>Memory Mismatch]
```

### Test Function Name : test_l2_platform_hal_checkusedmemory_lesserthanor_equals_totalDRAM

```mermaid
flowchart TD
    A[Start Test Case 8] --> B[Invoke platform_hal_GetTotalMemorySize]
    B -->|Success| C[Invoke platform_hal_GetUsedMemorySize]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetTotalMemorySize Failed]
    C -->|Success| D{Verify <br>Used Memory <= Total DRAM}
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetUsedMemorySize Failed]
    D -->|Yes| E[End Test Case<br>Success]
    D -->|No| F[Test Case Fail<br>Used Memory Exceeds Total DRAM]
```

### Test Function Name : test_l2_platform_hal_checkfreememory_lesserthanor_equals_totalDRAM

```mermaid
flowchart TD
    A[Start Test Case 9] --> B[Invoke platform_hal_GetTotalMemorySize]
    B -->|Success| C[Invoke platform_hal_GetFreeMemorySize]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetTotalMemorySize Failed]
    C -->|Success| D{Verify <br>Free Memory <= Total DRAM}
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetFreeMemorySize Failed]
    D -->|Yes| E[End Test Case<br>Success]
    D -->|No| F[Test Case Fail<br>Free Memory Exceeds Total DRAM]
```

### Test Function Name : test_l2_platform_hal_checksumof_usedandfree_memory_equals_totalDRAM

```mermaid
flowchart TD
    A[Start Test Case 10] --> B[Invoke platform_hal_GetTotalMemorySize]
    B -->|Success| C[Invoke platform_hal_GetUsedMemorySize]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetTotalMemorySize Failed]
    C -->|Success| D[Invoke platform_hal_GetFreeMemorySize]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetUsedMemorySize Failed]
    D -->|Success| E{Verify <br> Used + Free Memory = Total DRAM}
    D -->|Failure| Z[Test Case Fail<br>platform_hal_GetFreeMemorySize Failed]
    E -->|Yes| F[End Test Case<br>Success]
    E -->|No| G[Test Case Fail<br>Memory Mismatch]
```

### Test Function Name : test_l2_platform_hal_verify_factoryresetcount_afterclearing

```mermaid
flowchart TD
    A[Start Test Case 11] --> B[Fetch Reset Count<br>platform_hal_GetFactoryResetCount]
    B -->|Success| C[Clear Reset Count<br>platform_hal_ClearResetCount]
    B -->|Failure| X[Test Case Fail<br>Fetch Reset Count Failed]
    C -->|Success| D[Validate Reset Count<br>platform_hal_GetFactoryResetCount]
    C -->|Failure| Y[Test Case Fail<br>Clear Reset Count Failed]
    D --> E{Is Reset Count <br> Cleared?}
    E -->|Yes| F[End Test Case<br>Success]
    E -->|No| G[Test Case Fail<br>Reset Count Not Cleared]
```

### Test Function Name : test_l2_platform_hal_getset_FactoryCmVariant

```mermaid
flowchart TD
    A[Start Test Case 12] --> B[Retrieve CM Variant<br>platform_hal_getFactoryCmVariant]
    B -->|Success| C[Modify CM Variant<br>platform_hal_setFactoryCmVariant]
    B -->|Failure| X[Test Case Fail<br>Retrieve CM Variant Failed]
    C -->|Success| D[Validate CM Variant<br>platform_hal_getFactoryCmVariant]
    C -->|Failure| Y[Test Case Fail<br>Modify CM Variant Failed]
    D --> E{Does Retrieved Value <br> Match Set Value?}
    E -->|Yes| F[End Test Case<br>Success]
    E -->|No| G[Test Case Fail<br>Validation Failed]
```

### Test Function Name : test_l2_platform_hal_getset_Led

```mermaid
flowchart TD
    A[Start Test Case 13] --> B[Retrieve LED Status<br>platform_hal_getLed]
    B -->|Success| C[Set LED Status<br>platform_hal_setLed]
    B -->|Failure| X[Test Case Fail<br>Retrieve LED Status Failed]
    C -->|Success| D[Retrieve LED Status Again<br>platform_hal_getLed]
    C -->|Failure| Y[Test Case Fail<br>Set LED Status Failed]
    D -->|Success| E{Does Retrieved <br>LED Status Match <br>Set Status?}
    D -->|Failure| Z[Test Case Fail<br>Retrieve LED Status Again Failed]
    E -->|Yes| F[End Test Case<br>Success]
    E -->|No| G[Test Case Fail<br>LED Status Mismatch]
```

### Test Function Name : test_l2_platform_hal_getset_MACsecEnable

```mermaid
flowchart TD
    A[Start Test Case 14] --> B{For Each Eth Port <br> 0 to MaxEthPort-1}
    B --> C[Get MACsec Status<br>platform_hal_GetMACsecEnable]
    C -->|Success| D[Toggle MACsec Status<br>platform_hal_SetMACsecEnable]
    C -->|Failure| X[Test Case Fail<br>Get MACsec Status Failed]
    D -->|Success| E[Validate MACsec Status<br>platform_hal_GetMACsecEnable]
    D -->|Failure| Y[Test Case Fail<br>Toggle MACsec Status Failed]
    E --> F{Does Retrieved Status <br> Match Toggled Status?}
    E -->|Failure| Z[Test Case Fail<br>Validate MACsec Status Failed]
    F -->|Yes| G[Continue to Next Port<br>Or End Test Case if Last Port]
    G --Ethport 1 to n-1 -->B
    F -->|No| H[Test Case Fail<br>MACsec Status Mismatch]
```