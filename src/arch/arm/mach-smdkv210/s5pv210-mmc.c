/*
 * s5pv210-mmc.c
 *
 * Copyright (c) 2007-2011  jianjun jiang <jerryjianjun@gmail.com>
 * official site: http://xboot.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#include <configs.h>
#include <default.h>
#include <macros.h>
#include <types.h>
#include <div64.h>
#include <io.h>
#include <xboot/log.h>
#include <xboot/clk.h>
#include <xboot/printk.h>
#include <xboot/machine.h>
#include <xboot/initcall.h>
#include <time/delay.h>
#include <mmc/mmc.h>
#include <mmc/mmc_host.h>
#include <s5pv210/reg-gpio.h>
#include <s5pv210/reg-mmc.h>

static x_bool setup_hsmmc_clock(x_s32 ch)
{
	return FALSE;
}

static x_bool setup_hsmmc_cfg_gpio(x_s32 ch)
{
	switch(ch)
	{
	case 0:
		/* gpg0[0:6] = clk, cmd, cd, data[0:3] */
		writel(S5PV210_GPG0CON, 0x02222222);
		writel(S5PV210_GPG0PUD, 0x00002aaa);
		writel(S5PV210_GPG0DRV, 0x00003fff);
		return TRUE;

	case 1:
		/* gpg1[0:6] = clk, cmd, cd, data[0:3] */
		writel(S5PV210_GPG1CON, 0x02222222);
		writel(S5PV210_GPG1PUD, 0x00002aaa);
		writel(S5PV210_GPG1DRV, 0x00003fff);
		return TRUE;

	case 2:
		/* gpg2[0:6] = clk, cmd, cd, data[0:3] */
		writel(S5PV210_GPG2CON, 0x02222222);
		writel(S5PV210_GPG2PUD, 0x00002aaa);
		writel(S5PV210_GPG2DRV, 0x00003fff);
		return TRUE;

	case 3:
		/* gpg3[0:6] = clk, cmd, cd, data[0:3] */
		writel(S5PV210_GPG3CON, 0x02222222);
		writel(S5PV210_GPG3PUD, 0x00002aaa);
		writel(S5PV210_GPG3DRV, 0x00003fff);
		return TRUE;

	default:
		break;
	}

	return FALSE;
}

static void s5pv210_mmc_init(void)
{

}

static void s5pv210_mmc_exit(void)
{

}

x_bool s5pv210_mmc_probe(struct mmc_card_info * info)
{
	return FALSE;
}

x_bool s5pv210_mmc_read_sector(struct mmc_card * card, x_u32 sector, x_u8 * data)
{
	return FALSE;
}

x_bool s5pv210_mmc_write_sector(struct mmc_card * card, x_u32 sector, x_u8 * data)
{
	return FALSE;
}

static struct mmc_host s5pv210_mmc_host_controller = {
	.name			= "s5pv210-mmc",
	.init			= s5pv210_mmc_init,
	.exit			= s5pv210_mmc_exit,
	.probe			= s5pv210_mmc_probe,
	.read_sector	= s5pv210_mmc_read_sector,
	.write_sector	= s5pv210_mmc_write_sector,
};

static __init void s5pv210_mmc_host_controller_init(void)
{
	if(!register_mmc_host(&s5pv210_mmc_host_controller))
		LOG_E("failed to register mmc host controller '%s'", s5pv210_mmc_host_controller.name);
}

static __exit void s5pv210_mmc_host_controller_exit(void)
{
	if(!unregister_mmc_host(&s5pv210_mmc_host_controller))
		LOG_E("failed to unregister mmc host controller '%s'", s5pv210_mmc_host_controller.name);
}

module_init(s5pv210_mmc_host_controller_init, LEVEL_MACH_RES);
module_exit(s5pv210_mmc_host_controller_exit, LEVEL_MACH_RES);
