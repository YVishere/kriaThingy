#include "xisppipeline_accel.h"

XIsppipeline_accel_Config XIsppipeline_accel_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,ISPPipeline-accel-1.0", /* compatible */
		0xb0000000 /* reg */
	},
	 {
		 NULL
	}
};