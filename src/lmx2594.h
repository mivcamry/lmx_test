#ifndef __LMX_2594_H__
#define __LMX_2594_H__

#include <stdint.h>
#include <stdint.h>
#include "lmx2594_reg.h"

int lmx2594_init(int fd);
int lmx2594_reset(int fd);

int lmx2594_configure(int fd);

int lmx2594_register_write(int fd, uint8_t address, uint16_t data);
int lmx2594_register_read(int fd, const uint8_t address, uint16_t* data);

int lmx2594_register_write_tbl(int fd, struct lmx2594_reg_data* tbl, uint32_t count);

#endif // __LMK_0482X_H__

