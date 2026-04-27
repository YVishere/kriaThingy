#include "xdphy.h"

XDphy_Config XDphy_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,mipi-dphy-4.3", /* compatible */
		0x1000, /* reg */
		0x0, /* xlnx,dphy-mode */
		0x1, /* xlnx,en-reg-if */
		0x2, /* xlnx,dphy-lanes */
		0x32, /* xlnx,esc-clk-period */
		0x6400, /* xlnx,esc-timeout */
		0x390, /* xlnx,hs-line-rate */
		0x10005, /* xlnx,hs-timeout */
		0x32, /* xlnx,lpx-period */
		0x5, /* xlnx,stable-clk-period */
		0x85d9a0, /* xlnx,txpll-clkin-period */
		0xf4240, /* xlnx,wakeup */
		0x0, /* xlnx,en-timeout-regs */
		0x91 /* xlnx,hs-settle-ns */
	},
	 {
		 NULL
	}
};