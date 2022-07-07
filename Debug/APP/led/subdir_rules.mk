################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
APP/led/%.obj: ../APP/led/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/APP/iic" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/APP/OLED" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/APP/adc" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/APP/pi" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/APP/epwm" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/APP/led" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/APP/key" --include_path="D:/CCS/dsp28335/workspace/DCDC_xiaosai/DSP2833x_Libraries/include" --include_path="D:/CCS/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="APP/led/$(basename $(<F)).d_raw" --obj_directory="APP/led" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


