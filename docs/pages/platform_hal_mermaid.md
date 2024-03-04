Please find the mermaid flow of platform hal L2 Test cases:

### Test Function Name : test_l2_platform_hal_getset_TelnetEnable

```mermaid
flowchart TD
    A[Start Test Case 1] --> B(Call platform_hal_GetTelnetEnable)
    B --> C{Is Telnet <br> Enabled?}
    C -->|No| E["Enable Telnet<br>platform_hal_SetTelnetEnable(TRUE)"]
    C -->|Yes| D["Disable Telnet<br>platform_hal_SetTelnetEnable(FALSE)"]
    D --> F[Validate<br>Call platform_hal_GetTelnetEnable]
    E --> G[Validate<br>Call platform_hal_GetTelnetEnable]
    F -->|Telnet Disabled| I[End Test Case<br>Success]
    G -->|Telnet still Disabled| J[Test Case Fail<br>Telnet Not Enabled]
    F -->|Telnet still Enabled| H[Test Case Fail<br>Telnet Not Disabled]
    G -->|Telnet Enabled| I[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_SSHEnable

```mermaid
flowchart TD
    A[Start Test Case 2] --> B(Call platform_hal_GetSSHEnable)
    B --> C{Is SSH <br> Enabled?}
    C -->|No| E["Enable SSH<br>platform_hal_SetSSHEnable(TRUE)"]
    C -->|Yes| D["Disable SSH<br>platform_hal_SetSSHEnable(FALSE)"]
    D --> F[Validate<br>Call platform_hal_GetSSHEnable]
    E --> G[Validate<br>Call platform_hal_GetSSHEnable]
    F -->|SSH Disabled| I[End Test Case<br>Success]
    F -->|SSH still Enabled| H[Test Case Fail<br>SSH Not Disabled]
    G -->|SSH still Disabled| J[Test Case Fail<br>SSH Not Enabled]
    G -->|SSH Enabled| I[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_SNMPEnable

```mermaid
flowchart TD
    A[Start Test Case 3] --> B[Call platform_hal_GetSNMPEnable]
    B --> C{Current SNMP <br> Status}
    C -->|Disabled| E["Toggle to Enabled<br>platform_hal_SetSNMPEnable(Enabled)"]
    C -->|Enabled| D["Toggle to Disabled<br>platform_hal_SetSNMPEnable(Disabled)"]
    D --> F[Validate<br>Call platform_hal_GetSNMPEnable]
    E --> G[Validate<br>Call platform_hal_GetSNMPEnable]
    F -->|SNMP Disabled| I[End Test Case<br>Success]
    F -->|SNMP still Enabled| H[Test Case Fail<br>SNMP Not Disabled]
    G -->|SNMP still Disabled| J[Test Case Fail<br>SNMP Not Enabled]
    G -->|SNMP Enabled| I[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_WebUITimeout

```mermaid
flowchart TD
    A[Start Test Case 4] --> B[Call platform_hal_GetWebUITimeout]
    B -->|Failure| X[Test Case Fail<br>Unable to Get Current Timeout]
    B -->|Success| C["Change Timeout<br>platform_hal_SetWebUITimeout(new value)"]
    C -->|Failure| Y[Test Case Fail<br>Unable to Set New Timeout]
    C -->|Success| D[Validate<br>Call platform_hal_GetWebUITimeout]
    D --> E{Is New<br>Timeout<br>Set?}
    E -->|No| G[Test Case Fail<br>New Timeout Not Set]
    E -->|Yes| F[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_Memused_lesserthanor_equalto_flashMemory

```mermaid
flowchart TD
    A[Start Test Case 5] --> B[Invoke platform_hal_GetHardware]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetHardware Failed]
    B -->|Success| C[Invoke platform_hal_GetHardware_MemUsed]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetHardware_MemUsed Failed]
    C -->|Success| D{Verify <br>Used Memory <br> \<= <br> Total Flash <br> Size}
    D -->|No| F[Test Case Fail<br>Used Memory Exceeds Total Flash Size]
    D -->|Yes| E[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_MemFree_lesserthanor_equalto_flashMemory

```mermaid
flowchart TD
    A[Start Test Case 6] --> B[Invoke platform_hal_GetHardware]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetHardware Failed]
    B -->|Success| C[Invoke platform_hal_GetHardware_MemFree]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetHardware_MemFree Failed]
    C -->|Success| D{"Verify <br> Free Memory <br> <= <br>Total Flash <br> Memory"}
    D -->|No| F[Test Case Fail<br>Free Memory Exceeds Total Flash Memory]
    D -->|Yes| E[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_checksumof_memusedandfree_equals_totalflash

```mermaid
flowchart TD
    A[Start Test Case 7] --> B[Invoke platform_hal_GetHardware]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetHardware Failed]
    B -->|Success| C[Invoke platform_hal_GetHardware_MemUsed]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetHardware_MemUsed Failed]
    C -->|Success| D[Invoke platform_hal_GetHardware_MemFree]
    D -->|Failure| Z[Test Case Fail<br>platform_hal_GetHardware_MemFree Failed]
    D -->|Success| E{Verify <br> Used + Free Memory <br>= Total Flash}
    E -->|No| G[Test Case Fail<br>Memory Mismatch]
    E -->|Yes| F[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_checkusedmemory_lesserthanor_equals_totalDRAM

```mermaid
flowchart TD
    A[Start Test Case 8] --> B[Invoke platform_hal_GetTotalMemorySize]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetTotalMemorySize Failed]
    B -->|Success| C[Invoke platform_hal_GetUsedMemorySize]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetUsedMemorySize Failed]
    C -->|Success| D{"Verify <br> Used Memory <br> <= <br> Total DRAM"}
    D -->|No| F[Test Case Fail<br>Used Memory Exceeds Total DRAM]
    D -->|Yes| E[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_checkfreememory_lesserthanor_equals_totalDRAM

```mermaid
flowchart TD
    A[Start Test Case 9] --> B[Invoke platform_hal_GetTotalMemorySize]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetTotalMemorySize Failed]
    B -->|Success| C[Invoke platform_hal_GetFreeMemorySize]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetFreeMemorySize Failed]
    C -->|Success| D{"Verify <br> Free Memory <br> <= <br> Total DRAM"}
    D -->|No| F[Test Case Fail<br>Free Memory Exceeds Total DRAM]
    D -->|Yes| E[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_checksumof_usedandfree_memory_equals_totalDRAM

```mermaid
flowchart TD
    A[Start Test Case 10] --> B[Invoke platform_hal_GetTotalMemorySize]
    B -->|Failure| X[Test Case Fail<br>platform_hal_GetTotalMemorySize Failed]
    B -->|Success| C[Invoke platform_hal_GetUsedMemorySize]
    C -->|Failure| Y[Test Case Fail<br>platform_hal_GetUsedMemorySize Failed]
    C -->|Success| D[Invoke platform_hal_GetFreeMemorySize]
    D -->|Failure| Z[Test Case Fail<br>platform_hal_GetFreeMemorySize Failed]
    D -->|Success| E{Verify <br> Used + Free Memory <br> = <br> Total DRAM}
    E -->|No| G[Test Case Fail<br>Memory Mismatch]
    E -->|Yes| F[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_verify_factoryresetcount_afterclearing

```mermaid
flowchart TD
    A[Start Test Case 11] --> B[Fetch Reset Count<br>platform_hal_GetFactoryResetCount]
    B -->|Failure| X[Test Case Fail<br>Fetch Reset Count Failed]
    B -->|Success| C[Clear Reset Count<br>platform_hal_ClearResetCount]
    C -->|Failure| Y[Test Case Fail<br>Clear Reset Count Failed]
    C -->|Success| D[Validate Reset Count<br>platform_hal_GetFactoryResetCount]
    D --> E{Is Reset Count <br> Cleared?}
    E -->|No| G[Test Case Fail<br>Reset Count Not Cleared]
    E -->|Yes| F[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_FactoryCmVariant

```mermaid
flowchart TD
    A[Start Test Case 12] --> B[Retrieve CM Variant<br>platform_hal_getFactoryCmVariant]
    B -->|Failure| X[Test Case Fail<br>Retrieve CM Variant Failed]
    B -->|Success| C[Modify CM Variant<br>platform_hal_setFactoryCmVariant]
    C -->|Failure| Y[Test Case Fail<br>Modify CM Variant Failed]
    C -->|Success| D[Validate CM Variant<br>platform_hal_getFactoryCmVariant]
    D --> E{is Retrieved Value = <br>Set Value ?}
    E -->|No| G[Test Case Fail<br>Validation Failed]
    E -->|Yes| F[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_Led

```mermaid
flowchart TD
    A[Start Test Case 13] --> B[Retrieve LED Status<br>platform_hal_getLed]
    B -->|Failure| X[Test Case Fail<br>Retrieve LED Status Failed]
    B -->|Success| C[Set LED Status<br>platform_hal_setLed]
    C -->|Failure| Y[Test Case Fail<br>Set LED Status Failed]
    C -->|Success| D[Retrieve LED Status Again<br>platform_hal_getLed]
    D -->|Failure| Z[Test Case Fail<br>Retrieve LED Status Again Failed]
    D -->|Success| E{is Retrieved <br> LED Status = <br> Set Status ?}
    E -->|No| G[Test Case Fail<br>LED Status Mismatch]
    E -->|Yes| F[End Test Case<br>Success]
```

### Test Function Name : test_l2_platform_hal_getset_MACsecEnable

```mermaid
flowchart TD
    A[Start Test Case 14] --> B{For Each Eth Port <br> 0 to MaxEthPort-1}
    B --> C[Get MACsec Status<br>platform_hal_GetMACsecEnable]
    C -->|Failure| X[Test Case Fail<br>Get MACsec Status Failed]
    C -->|Success| D[Toggle MACsec Status<br>platform_hal_SetMACsecEnable]
    D -->|Failure| Y[Test Case Fail<br>Toggle MACsec Status Failed]
    D -->|Success| E[Validate MACsec Status<br>platform_hal_GetMACsecEnable]
    E -->|Failure| Z[Test Case Fail<br>Validate MACsec Status Failed]
    E --> F{is Retrieved <br> Status = <br> Toggled Status?}
    F -->|No| H[Test Case Fail<br>MACsec Status Mismatch]
    F -->|Yes| G[Continue to Next Port<br>Or End Test Case if Last Port]
    G --Ethport 1 to n-1 -->B
```
