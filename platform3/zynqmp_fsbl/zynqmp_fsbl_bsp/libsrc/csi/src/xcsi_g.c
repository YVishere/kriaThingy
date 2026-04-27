#include "xcsi.h"

XCsi_Config XCsi_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,mipi-csi2-rx-ctrl-1.0", /* compatible */
		0x0, /* reg */
		0x4, /* xlnx,csi-lanes */
		0x0, /* xlnx,csi-offload-non-image */
		0x0, /* xlnx,csi-en-vc-support */
		0x0, /* xlnx,csi-fixed-vc */
		0x0 /* xlnx,csi-optt3-fixed-lanes */
	},
	{
		"xlnx,mipi-csi2-rx-ctrl-1.0", /* compatible */
		0x0, /* reg */
		0x2, /* xlnx,csi-lanes */
		0x0, /* xlnx,csi-offload-non-image */
		0x1, /* xlnx,csi-en-vc-support */
		0x0, /* xlnx,csi-fixed-vc */
		0x0 /* xlnx,csi-optt3-fixed-lanes */
	},
	 {
		 NULL
	}
};