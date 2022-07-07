################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/CCS/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./APP/OLED/oled.obj" \
"./APP/adc/adc.obj" \
"./APP/epwm/epwm_0.obj" \
"./APP/iic/iic.obj" \
"./APP/key/key.obj" \
"./APP/led/led.obj" \
"./APP/pi/pi.obj" \
"./DSP2833x_Libraries/source/DSP2833x_ADC_cal.obj" \
"./DSP2833x_Libraries/source/DSP2833x_Adc.obj" \
"./DSP2833x_Libraries/source/DSP2833x_CodeStartBranch.obj" \
"./DSP2833x_Libraries/source/DSP2833x_DefaultIsr.obj" \
"./DSP2833x_Libraries/source/DSP2833x_EPwm.obj" \
"./DSP2833x_Libraries/source/DSP2833x_GlobalVariableDefs.obj" \
"./DSP2833x_Libraries/source/DSP2833x_Gpio.obj" \
"./DSP2833x_Libraries/source/DSP2833x_MemCopy.obj" \
"./DSP2833x_Libraries/source/DSP2833x_PieCtrl.obj" \
"./DSP2833x_Libraries/source/DSP2833x_PieVect.obj" \
"./DSP2833x_Libraries/source/DSP2833x_SysCtrl.obj" \
"./DSP2833x_Libraries/source/DSP2833x_usDelay.obj" \
"../cmd/DSP2833x_Headers_nonBIOS.cmd" \
"../cmd/F28335.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include APP/OLED/subdir_vars.mk
-include APP/adc/subdir_vars.mk
-include APP/epwm/subdir_vars.mk
-include APP/iic/subdir_vars.mk
-include APP/key/subdir_vars.mk
-include APP/led/subdir_vars.mk
-include APP/pi/subdir_vars.mk
-include DSP2833x_Libraries/source/subdir_vars.mk
-include cmd/subdir_vars.mk
-include subdir_rules.mk
-include APP/OLED/subdir_rules.mk
-include APP/adc/subdir_rules.mk
-include APP/epwm/subdir_rules.mk
-include APP/iic/subdir_rules.mk
-include APP/key/subdir_rules.mk
-include APP/led/subdir_rules.mk
-include APP/pi/subdir_rules.mk
-include DSP2833x_Libraries/source/subdir_rules.mk
-include cmd/subdir_rules.mk
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
DCDC_xiaosai.out \

EXE_OUTPUTS__QUOTED += \
"DCDC_xiaosai.out" \

BIN_OUTPUTS += \
DCDC_xiaosai.hex \

BIN_OUTPUTS__QUOTED += \
"DCDC_xiaosai.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "DCDC_xiaosai.out"

# Tool invocations
DCDC_xiaosai.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/CCS/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"DCDC_xiaosai.map" --stack_size=0x300 --warn_sections -i"D:/CCS/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/lib" -i"D:/CCS/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="DCDC_xiaosai_linkInfo.xml" --rom_model -o "DCDC_xiaosai.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

DCDC_xiaosai.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"D:/CCS/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/hex2000" --diag_wrap=off -o "DCDC_xiaosai.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "APP\OLED\oled.obj" "APP\adc\adc.obj" "APP\epwm\epwm_0.obj" "APP\iic\iic.obj" "APP\key\key.obj" "APP\led\led.obj" "APP\pi\pi.obj" "DSP2833x_Libraries\source\DSP2833x_ADC_cal.obj" "DSP2833x_Libraries\source\DSP2833x_Adc.obj" "DSP2833x_Libraries\source\DSP2833x_CodeStartBranch.obj" "DSP2833x_Libraries\source\DSP2833x_DefaultIsr.obj" "DSP2833x_Libraries\source\DSP2833x_EPwm.obj" "DSP2833x_Libraries\source\DSP2833x_GlobalVariableDefs.obj" "DSP2833x_Libraries\source\DSP2833x_Gpio.obj" "DSP2833x_Libraries\source\DSP2833x_MemCopy.obj" "DSP2833x_Libraries\source\DSP2833x_PieCtrl.obj" "DSP2833x_Libraries\source\DSP2833x_PieVect.obj" "DSP2833x_Libraries\source\DSP2833x_SysCtrl.obj" "DSP2833x_Libraries\source\DSP2833x_usDelay.obj" 
	-$(RM) "main.d" "APP\OLED\oled.d" "APP\adc\adc.d" "APP\epwm\epwm_0.d" "APP\iic\iic.d" "APP\key\key.d" "APP\led\led.d" "APP\pi\pi.d" "DSP2833x_Libraries\source\DSP2833x_Adc.d" "DSP2833x_Libraries\source\DSP2833x_DefaultIsr.d" "DSP2833x_Libraries\source\DSP2833x_EPwm.d" "DSP2833x_Libraries\source\DSP2833x_GlobalVariableDefs.d" "DSP2833x_Libraries\source\DSP2833x_Gpio.d" "DSP2833x_Libraries\source\DSP2833x_MemCopy.d" "DSP2833x_Libraries\source\DSP2833x_PieCtrl.d" "DSP2833x_Libraries\source\DSP2833x_PieVect.d" "DSP2833x_Libraries\source\DSP2833x_SysCtrl.d" 
	-$(RM) "DSP2833x_Libraries\source\DSP2833x_ADC_cal.d" "DSP2833x_Libraries\source\DSP2833x_CodeStartBranch.d" "DSP2833x_Libraries\source\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

