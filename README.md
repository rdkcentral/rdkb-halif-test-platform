# Unit Testing Suite

The following documents should be references to provide specific information on the tests required for this module.

[Documentation can be found under "docs/pages" in this repository](docs/pages)

### Populate Configurations

The users of platform hal 3PE test suite can populate appropriate platform specific values for the below parameters in the configuration file "platform_config" before executing the test binary.

1. Fill the param MaxEthPort with Number of Ethernet ports. "MaxEthPort" : x , where x is the number of ethernet ports

2. For PartnerID, fill with Partner ID of the device. Refer the example given below

    "PartnerID": "comcast"

3. For FactoryCmVariant , fill with supported CM Variant values as a list of strings. Refer the example given below :

    "FactoryCmVariant" : ["pc20", "pc20genband", "pc15sip", "pc15mgcp"]

4. For Supported_CPUS :

        a. If only HOST_CPU is supported, fill this param with "Supported_CPUS" : [0]

        b.If only HOST_PEER is supported, fill this param with "Supported_CPUS" : [1]

        c. Both HOST_CPU and PEER_CPU are supported then "Supported_CPUS" : [0,1]

    * where 0 refers to HOST_CPU and 1 refers to PEER_CPU of enum RDK_CPUS.
    
5. For Supported_PSM_STATE :

        a. If only PSM_AC is supported , fill this param  with "Supported_PSM_STATE" : [1]

        b. If only PSM_BATT is supported , fill this param  with "Supported_PSM_STATE" : [2]

        c. If only PSM_HOT is supported , fill this param  with "Supported_PSM_STATE" : [3]

        d. If only PSM_COOLED is supported , fill this param  with "Supported_PSM_STATE" : [4]

    * Platform can support multiple Power Saving Mode States. Specify as a comma separated list. Refer the example given below    

        "Supported_PSM_STATE" : [1,2]
