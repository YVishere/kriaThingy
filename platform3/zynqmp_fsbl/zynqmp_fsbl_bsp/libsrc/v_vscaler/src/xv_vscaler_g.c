#include "xv_vscaler.h"

XV_vscaler_Config XV_vscaler_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,v-vscaler-1.1", /* compatible */
		0x20000, /* reg */
		0x1, /* xlnx,samples-per-clock */
		0x3, /* xlnx,num-video-components */
		0x780, /* xlnx,max-cols */
		0x438, /* xlnx,max-rows */
		0x8, /* xlnx,max-data-width */
		0x6, /* xlnx,phase-shift */
		0x2, /* xlnx,scale-mode */
		0x6, /* xlnx,taps */
		0x1 /* xlnx,enable-420 */
	},
	{
		"xlnx,v-vscaler-1.1", /* compatible */
		0x20000, /* reg */
		0x1, /* xlnx,samples-per-clock */
		0x3, /* xlnx,num-video-components */
		0x780, /* xlnx,max-cols */
		0x438, /* xlnx,max-rows */
		0x8, /* xlnx,max-data-width */
		0x6, /* xlnx,phase-shift */
		0x2, /* xlnx,scale-mode */
		0x6, /* xlnx,taps */
		0x1 /* xlnx,enable-420 */
	},
	 {
		 NULL
	}
};