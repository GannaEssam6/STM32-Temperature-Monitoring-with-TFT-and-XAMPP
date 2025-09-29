/*
 * MRCC_Config.h
 *
 *  Created on: Aug 17, 2025
 *      Author: Ganaa
 */

#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_

/* Choose between:
 * 1-HSI_clock
 * 2-HSE_clock
 * 3-PLL
 */
#define SYSTEM_CLOCK HSI_CLOCK

/* Choose between:
 * 1-Mechanical_clock
 * 2-RC_clock
 */
#define HSE_OSC RC_CLK

#endif /* MRCC_CONFIG_H_ */
