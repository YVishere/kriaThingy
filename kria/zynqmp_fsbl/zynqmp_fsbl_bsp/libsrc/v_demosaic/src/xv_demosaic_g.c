#include "xv_demosaic.h"

XV_demosaic_Config XV_demosaic_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,v-demosaic-1.1", /* compatible */
		0xa0030000, /* reg */
		0x1, /* xlnx,samples-per-clock */
		0x800, /* xlnx,max-cols */
		0x400, /* xlnx,max-rows */
		0x8, /* xlnx,max-data-width */
		0x0, /* xlnx,algorithm */
		0x2000, /* interrupts */
		0xa0010001 /* interrupt-parent */
	},
	 {
		 NULL
	}
};