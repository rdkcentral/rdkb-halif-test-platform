# Unit Testing Suite for platform HAL

The following documents should be referenced to provide specific information on the tests required for this module.

[Documentation can be found under "docs/pages" in this repository](docs/pages)

## Table of Contents

- [Version History](#version-history)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)
- [Makefile configurations](#makefile-configurations)
- [Populate Configurations](#populate-configurations)

## Version History

| Date     | Comment         | Version |
| -------- | --------------- | ------- |
| 01/23/24 | Initial Release | 1.0.0   |

## Acronyms, Terms and Abbreviations

- `L1` - Unit Tests
- `HAL`- Hardware Abstraction Layer

## Description

This repository contains the Unit Test Suites (L1) for Platform `HAL`.

## Reference Documents

| SNo | Document Name                | Document Description                                                                               | Document Link                                                                                                                    |
| --- | ---------------------------- | -------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| 1   | `HAL` Specification Document | This document provides specific information on the APIs for which tests are written in this module | [PlatformhalSpec.md](../../../../../rdkcentral/rdkb-halif-platform/blob/main/docs/pages/PlatformhalSpec.md "PlatformhalSpec.md") |
| 2   | `L1` Tests                   | `L1` Test Case File for this module                                                                | [test_l1_platform_hal.c](src/test_l1_platform_hal.c "test_l1_platform_hal.c")                                                    |

## Enable RDKB Features

FEATURE_RDKB_LED_MANAGER and FEATURE_RDKB_THERMAL_MANAGER features are disabled by default in platform hal test suite.

If the platform supports these features, enable thermal manager and led manager apis and its tests, using below CFLAGS in rdkb-halif-test-platform/Makefile :

```
CFLAGS += -DFEATURE_RDKB_THERMAL_MANAGER -DFEATURE_RDKB_LED_MANAGER
```

## Populate Configuration File

The users of platform hal 3PE test suite can populate appropriate platform specific values for the below parameters in the configuration file "platform_config" before executing the test binary.

1.  Fill the param MaxEthPort with Number of Ethernet ports. "MaxEthPort" : x , where x is the number of ethernet ports

2.  For PartnerID, fill with Partner ID of the device. Refer the example given below :

    "PartnerID": "comcast"

3.  For FactoryCmVariant , fill with supported CM Variant values as a list of strings. Refer the example given below :

    "FactoryCmVariant" : ["pc20", "pc20genband", "pc15sip", "pc15mgcp"]

4.  For Supported_CPUS :

        a. If only HOST_CPU is supported, fill this param with "Supported_CPUS" : [0]

        b.If only HOST_PEER is supported, fill this param with "Supported_CPUS" : [1]

        c. Both HOST_CPU and PEER_CPU are supported then "Supported_CPUS" : [0,1]

    - where 0 refers to HOST_CPU and 1 refers to PEER_CPU of enum RDK_CPUS.

5.  For Supported_PSM_STATE :

        a. If only PSM_AC is supported , fill this param  with "Supported_PSM_STATE" : [1]

        b. If only PSM_BATT is supported , fill this param  with "Supported_PSM_STATE" : [2]

        c. If only PSM_HOT is supported , fill this param  with "Supported_PSM_STATE" : [3]

        d. If only PSM_COOLED is supported , fill this param  with "Supported_PSM_STATE" : [4]

    - Platform can support multiple Power Saving Mode States. Specify as a comma separated list. Refer the example given below :

      "Supported_PSM_STATE" : [1,2]

6.  For FanIndex:

        a. If platform supports only 1 fan , fill this parm with "FanIndex" : [0]

        b. If platform supports 2 fans , fill this param with "FanIndex" : [0,1]

    - The range of FanIndex is from 0 to 1.

7.  For InterfaceNames, fill with supported interfaces on each platform as a list of available network interfaces. Refer the example given below :

    "InterfaceNames": ["br106", "eth0", "erouter0", "eth3", "gretap0"]
