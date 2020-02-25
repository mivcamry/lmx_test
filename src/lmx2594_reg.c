#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "lmx2594_reg.h"
#include "api_errors.h"
#include "hal.h"


#define IN_OUT_BUFF_SZ 3

int lmx2594_register_write(int fd, const uint8_t address, const uint16_t data)
{
	uint8_t rd[] = {0,0,0};
	uint8_t wr[3];

	wr[2] = data & 0xFF;
	wr[1] = (data >> 8) & 0xFF;
	wr[0] = address & 0x7F;

	printf("--- write data to register %x  << [0]:%x, [1]:%x, [2]:%x >> ---\n", address, wr[0], wr[1], wr[2]);

	return spi_xfer(fd, wr, rd, IN_OUT_BUFF_SZ);
}

int lmx2594_register_read(int fd, const uint8_t address, uint16_t* data)
{
	int ret = API_ERROR_INVALID_PARAM;
	uint8_t rd[] = {0,0,0};
	uint8_t wr[3];

	wr[2] = 0xFF;
	wr[1] = 0xFF;
	wr[0] = address;
	wr[0] |= 0x80;

	ret = spi_xfer(fd, wr, rd, IN_OUT_BUFF_SZ);

	if(ret == API_ERROR_OK)
		*data = (rd[1] << 8) | rd[2];

	printf("--- write data to register %x  << [0]:%x, [1]:%x, [2]:%x >> ---\n", address, wr[0], wr[1], wr[2]);
	printf("--- read data from register %x  << [0]:%x, [1]:%x, [2]:%x >> ---\n", address, rd[0], rd[1], rd[2]);

	return ret;
}

int lmx2594_register_write_tbl(int fd, struct lmx2594_reg_data* tbl, uint32_t count)
{
	uint16_t i =0;

	for (i = 0; i<count; i++) {
		lmx2594_register_write(fd, tbl[i].reg, tbl[i].val);
	}

	return API_ERROR_OK;
}
