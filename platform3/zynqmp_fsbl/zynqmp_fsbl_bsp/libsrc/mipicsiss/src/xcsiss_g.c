#include "xcsiss.h"

XCsiSs_Config XCsiSs_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,mipi-csi2-rx-subsystem-6.0", /* compatible */
		0x80000000, /* reg */
		0x80000fff, /* xlnx,highaddr */
		0x0, /* xlnx,cmn-inc-iic */
		0x4, /* xlnx,cmn-num-lanes */
		0x1, /* xlnx,cmn-num-pixels */
		0x18, /* xlnx,cmn-pxl-format */
		0x0, /* xlnx,cmn-vc */
		0x1000, /* xlnx,csi-buf-depth */
		0x0, /* xlnx,csi-emb-non-img */
		0x0, /* xlnx,dpy-en-reg-if */
		0x380, /* xlnx,dpy-line-rate */
		0x1, /* xlnx,csi-en-crc */
		0x0, /* xlnx,csi-en-activelanes */
		0x0, /* xlnx,en-csi-v2 */
		0x4, /* xlnx,dphy-lanes */
		0x0, /* axii2c-present */
		0x0, /* axii2c-connected */
		0x1, /* csirx-present */
		0x0, /* csirx-connected */
		0x0, /* mipi-dphy-present */
		0x0, /* mipi-dphy-connected */
		0x0, /* rxphy-present */
		0x0, /* rxphy-connected */
		0x4068, /* interrupts */
		0xf9010000 /* interrupt-parent */
	},
	{
		"xlnx,mipi-csi2-rx-subsystem-6.0", /* compatible */
		0x80002000, /* reg */
		0x80003fff, /* xlnx,highaddr */
		0x0, /* xlnx,cmn-inc-iic */
		0x2, /* xlnx,cmn-num-lanes */
		0x1, /* xlnx,cmn-num-pixels */
		0x2b, /* xlnx,cmn-pxl-format */
		0x4, /* xlnx,cmn-vc */
		0x200, /* xlnx,csi-buf-depth */
		0x0, /* xlnx,csi-emb-non-img */
		0x1, /* xlnx,dpy-en-reg-if */
		0x390, /* xlnx,dpy-line-rate */
		0x0, /* xlnx,csi-en-crc */
		0x0, /* xlnx,csi-en-activelanes */
		0x0, /* xlnx,en-csi-v2 */
		0x2, /* xlnx,dphy-lanes */
		0x0, /* axii2c-present */
		0x0, /* axii2c-connected */
		0x1, /* csirx-present */
		0x0, /* csirx-connected */
		0x0, /* mipi-dphy-present */
		0x0, /* mipi-dphy-connected */
		0x0, /* rxphy-present */
		0x0, /* rxphy-connected */
		0x406c, /* interrupts */
		0xf9010000 /* interrupt-parent */
	},
	 {
		 NULL
	}
};