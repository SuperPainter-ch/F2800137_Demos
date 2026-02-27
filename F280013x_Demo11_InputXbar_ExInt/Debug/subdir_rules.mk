################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --include_path="E:/F2800137_Demos/F280013x_Demo11_InputXbar_ExInt/common/include" --include_path="E:/F2800137_Demos/F280013x_Demo11_InputXbar_ExInt/User" --include_path="E:/F2800137_Demos/F280013x_Demo11_InputXbar_ExInt/Peripheral" --include_path="E:/F2800137_Demos/F280013x_Demo11_InputXbar_ExInt/headers/include" --include_path="E:/F2800137_Demos/F280013x_Demo11_InputXbar_ExInt" --include_path="D:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


