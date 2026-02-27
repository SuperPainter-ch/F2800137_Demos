################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./Peripheral/Adc.obj" \
"./Peripheral/Epwm.obj" \
"./Peripheral/Gpio.obj" \
"./Peripheral/Sci.obj" \
"./Peripheral/Timer.obj" \
"./User/Timer0_ISR.obj" \
"./User/Timer1_ISR.obj" \
"./User/Timer2_ISR.obj" \
"./common/source/f280013x_adc.obj" \
"./common/source/f280013x_codestartbranch.obj" \
"./common/source/f280013x_cputimers.obj" \
"./common/source/f280013x_dbgier.obj" \
"./common/source/f280013x_defaultisr.obj" \
"./common/source/f280013x_epwm.obj" \
"./common/source/f280013x_gpio.obj" \
"./common/source/f280013x_piectrl.obj" \
"./common/source/f280013x_pievect.obj" \
"./common/source/f280013x_spi.obj" \
"./common/source/f280013x_sysctrl.obj" \
"./common/source/f280013x_tempsensorconv.obj" \
"./common/source/f280013x_usdelay.obj" \
"./headers/source/f280013x_globalvariabledefs.obj" \
"../common/cmd/280013x_generic_flash_lnk.cmd" \
"../headers/cmd/f280013x_headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Peripheral/subdir_vars.mk
-include User/subdir_vars.mk
-include common/cmd/subdir_vars.mk
-include common/source/subdir_vars.mk
-include headers/cmd/subdir_vars.mk
-include headers/source/subdir_vars.mk
-include subdir_rules.mk
-include Peripheral/subdir_rules.mk
-include User/subdir_rules.mk
-include common/cmd/subdir_rules.mk
-include common/source/subdir_rules.mk
-include headers/cmd/subdir_rules.mk
-include headers/source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
F280013x_Demo09_AdcSoftTrig.out 

EXE_OUTPUTS__QUOTED += \
"F280013x_Demo09_AdcSoftTrig.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "F280013x_Demo09_AdcSoftTrig.out"

# Tool invocations
F280013x_Demo09_AdcSoftTrig.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"F280013x_Demo09_AdcSoftTrig.map" --heap_size=0x400 --stack_size=0x200 --warn_sections -i"D:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib" -i"D:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="F280013x_Demo09_AdcSoftTrig_linkInfo.xml" --rom_model -o "F280013x_Demo09_AdcSoftTrig.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "Peripheral\Adc.obj" "Peripheral\Epwm.obj" "Peripheral\Gpio.obj" "Peripheral\Sci.obj" "Peripheral\Timer.obj" "User\Timer0_ISR.obj" "User\Timer1_ISR.obj" "User\Timer2_ISR.obj" "common\source\f280013x_adc.obj" "common\source\f280013x_codestartbranch.obj" "common\source\f280013x_cputimers.obj" "common\source\f280013x_dbgier.obj" "common\source\f280013x_defaultisr.obj" "common\source\f280013x_epwm.obj" "common\source\f280013x_gpio.obj" "common\source\f280013x_piectrl.obj" "common\source\f280013x_pievect.obj" "common\source\f280013x_spi.obj" "common\source\f280013x_sysctrl.obj" "common\source\f280013x_tempsensorconv.obj" "common\source\f280013x_usdelay.obj" "headers\source\f280013x_globalvariabledefs.obj" 
	-$(RM) "main.d" "Peripheral\Adc.d" "Peripheral\Epwm.d" "Peripheral\Gpio.d" "Peripheral\Sci.d" "Peripheral\Timer.d" "User\Timer0_ISR.d" "User\Timer1_ISR.d" "User\Timer2_ISR.d" "common\source\f280013x_adc.d" "common\source\f280013x_cputimers.d" "common\source\f280013x_defaultisr.d" "common\source\f280013x_epwm.d" "common\source\f280013x_gpio.d" "common\source\f280013x_piectrl.d" "common\source\f280013x_pievect.d" "common\source\f280013x_spi.d" "common\source\f280013x_sysctrl.d" "common\source\f280013x_tempsensorconv.d" "headers\source\f280013x_globalvariabledefs.d" 
	-$(RM) "common\source\f280013x_codestartbranch.d" "common\source\f280013x_dbgier.d" "common\source\f280013x_usdelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

