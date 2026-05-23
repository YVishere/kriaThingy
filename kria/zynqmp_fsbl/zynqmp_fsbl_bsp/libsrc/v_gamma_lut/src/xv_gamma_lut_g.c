#include "xv_gamma_lut.h"

XV_gamma_lut_Config XV_gamma_lut_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,v-gamma-lut-1.1", /* compatible */
		0xa0040000, /* reg */
		0x1, /* xlnx,samples-per-clock */
		0x800, /* xlnx,max-cols */
		0x400, /* xlnx,max-rows */
		0x8 /* xlnx,max-data-width */
	},
	 {
		 NULL
	}
};