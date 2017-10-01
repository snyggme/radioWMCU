################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CC1310_LAUNCHXL.obj: ../CC1310_LAUNCHXL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/other/Code Composer Studio/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="D:/other/Code Composer Studio/Workspace/rfPacketTx_CC1310_LAUNCHXL_tirtos_ccs" --include_path="C:/ti/tirex-content/simplelink_cc13x0_sdk_1_00_00_13/kernel/tirtos/packages/ti/sysbios/posix" --include_path="D:/other/Code Composer Studio/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=DEVICE_FAMILY=cc13x0 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CC1310_LAUNCHXL.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ccfg.obj: ../ccfg.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/other/Code Composer Studio/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="D:/other/Code Composer Studio/Workspace/rfPacketTx_CC1310_LAUNCHXL_tirtos_ccs" --include_path="C:/ti/tirex-content/simplelink_cc13x0_sdk_1_00_00_13/kernel/tirtos/packages/ti/sysbios/posix" --include_path="D:/other/Code Composer Studio/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=DEVICE_FAMILY=cc13x0 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ccfg.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rfPacketTx.obj: ../rfPacketTx.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/other/Code Composer Studio/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="D:/other/Code Composer Studio/Workspace/rfPacketTx_CC1310_LAUNCHXL_tirtos_ccs" --include_path="C:/ti/tirex-content/simplelink_cc13x0_sdk_1_00_00_13/kernel/tirtos/packages/ti/sysbios/posix" --include_path="D:/other/Code Composer Studio/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=DEVICE_FAMILY=cc13x0 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="rfPacketTx.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


