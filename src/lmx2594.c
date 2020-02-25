#include "lmx2594.h"
#include <stdio.h>
#include <unistd.h>
#include "lmx2594_reg.h"


struct lmx2594_reg_data LMX_INIT_TBL[] = {
	{LMX2594_REG0,  0x0000},
	{LMX2594_REG1,  0x0808},
	{LMX2594_REG2,  0x0500},
	{LMX2594_REG3,  0x0642},
	{LMX2594_REG4,  0x0A43},
	{LMX2594_REG5,  0x00C8},
	{LMX2594_REG6,  0xC802},
	{LMX2594_REG7,  0x40B2},
	{LMX2594_REG8,  0x2000},
	{LMX2594_REG9,  0x1604},
	{LMX2594_REG10, 0x10D8},
	{LMX2594_REG11, 0x0018},
	{LMX2594_REG12, 0x5001},
	{LMX2594_REG13, 0x4000},
	{LMX2594_REG14, 0x1E70},
	{LMX2594_REG15, 0x064F},
	{LMX2594_REG16, 0x0080},
	{LMX2594_REG17, 0x012C},
	{LMX2594_REG18, 0x0064},
	{LMX2594_REG19, 0x27B7},
	{LMX2594_REG20, 0xE048},
	{LMX2594_REG21, 0x0401},
	{LMX2594_REG22, 0x0001},
	{LMX2594_REG23, 0x007C},
	{LMX2594_REG24, 0x071A},
	{LMX2594_REG25, 0x0624},
	{LMX2594_REG26, 0x0DB0},
	{LMX2594_REG27, 0x0002},
	{LMX2594_REG28, 0x0488},
	{LMX2594_REG29, 0x318C},
	{LMX2594_REG30, 0x318C},
	{LMX2594_REG31, 0x43EC},
	{LMX2594_REG32, 0x0393},
	{LMX2594_REG33, 0x1E21},
	{LMX2594_REG34, 0x0000},
	{LMX2594_REG35, 0x0004},
	{LMX2594_REG36, 0x0046},
	{LMX2594_REG37, 0x0404},
	{LMX2594_REG38, 0x0000},
	{LMX2594_REG39, 0x03E8},
	{LMX2594_REG40, 0x0000},
	{LMX2594_REG41, 0x0000},
	{LMX2594_REG42, 0x0000},
	{LMX2594_REG43, 0x0000},
	{LMX2594_REG44, 0x1FA3},
	{LMX2594_REG45, 0xC0DF},
	{LMX2594_REG46, 0x07FC},
	{LMX2594_REG47, 0x0300},
	{LMX2594_REG48, 0x0300},
	{LMX2594_REG49, 0x4180},
	{LMX2594_REG50, 0x0000},
	{LMX2594_REG51, 0x0080},
	{LMX2594_REG52, 0x0820},
	{LMX2594_REG53, 0x0000},
	{LMX2594_REG54, 0x0000},
	{LMX2594_REG55, 0x0000},
	{LMX2594_REG56, 0x0000},
	{LMX2594_REG57, 0x0020},
	{LMX2594_REG58, 0x8001},
	{LMX2594_REG59, 0x0001},
	{LMX2594_REG60, 0x0000},
	{LMX2594_REG61, 0x00A8},
	{LMX2594_REG62, 0x0322},
	{LMX2594_REG63, 0x0000},
	{LMX2594_REG64, 0x1388},
	{LMX2594_REG65, 0x0000},
	{LMX2594_REG66, 0x01F4},
	{LMX2594_REG67, 0x0000},
	{LMX2594_REG68, 0x03E8},
	{LMX2594_REG69, 0x0000},
	{LMX2594_REG70, 0xC350},
	{LMX2594_REG71, 0x0081},
	{LMX2594_REG72, 0x0001},
	{LMX2594_REG73, 0x003F},
	{LMX2594_REG74, 0x0000},
	{LMX2594_REG75, 0x0800},
	{LMX2594_REG76, 0x000C},
	{LMX2594_REG77, 0x0000},
	{LMX2594_REG78, 0x0003},
	{LMX2594_REG79, 0x0026},
	{LMX2594_REG80, 0x6666},
	{LMX2594_REG81, 0x0000},
	{LMX2594_REG82, 0x1E00},
	{LMX2594_REG83, 0x0000},
	{LMX2594_REG84, 0x0001},
	{LMX2594_REG85, 0xD300},
	{LMX2594_REG86, 0x0000},
	{LMX2594_REG87, 0x0000},
	{LMX2594_REG88, 0x0000},
	{LMX2594_REG89, 0x0000},
	{LMX2594_REG90, 0x0000},
	{LMX2594_REG91, 0x0000},
	{LMX2594_REG92, 0x0000},
	{LMX2594_REG93, 0x0000},
	{LMX2594_REG94, 0x0000},
	{LMX2594_REG95, 0x0000},
	{LMX2594_REG96, 0x0000},
	{LMX2594_REG97, 0x0888},
	{LMX2594_REG98, 0x0200},
	{LMX2594_REG99, 0x0000},
	{LMX2594_REG100, 0x0000},
	{LMX2594_REG101, 0x0011},
	{LMX2594_REG102, 0x3F80},
	{LMX2594_REG103, 0x0000},
	{LMX2594_REG104, 0x0000},
	{LMX2594_REG105, 0x0021},
	{LMX2594_REG106, 0x0000},
	{LMX2594_REG107, 0x0000},
	{LMX2594_REG108, 0x0000},
	{LMX2594_REG109, 0x0000},
	{LMX2594_REG110, 0x0000},
	{LMX2594_REG111, 0x0000},
	{LMX2594_REG112, 0x0000},
};


int lmx2594_configure(int fd)
{
	int ret = 0;

	uint16_t data = 0;

	//------------    Reset Chip  on    ---------------
	ret = lmx2594_register_write(fd, LMX2594_REG0, 0x00251A /*0x02*/);
	if(ret != 0)
		printf("--- Error spi_write_master(LMX2594_REG0, 0x02) ---\n");
	else
		printf("--- Chip reset on success ---\n");

	//------------  Reset Chip  off  ----------------
	ret = lmx2594_register_write(fd, LMX2594_REG0, 0x002518 /*0x00*/);
	if(ret != 0)
		printf("--- Error spi_write_master(LMX2594_REG0, 0x02) ---\n");
	else
		printf("--- Chip reset off success ---\n");


	printf("******************************************************\n");


	sleep(1);

	ret = lmx2594_register_write(fd, LMX2594_REG1, 0x0808);
	if(ret != 0)
		printf("--- Error spi_write_master(LMX2594_REG0, 0x0808) ---\n");
	else
		printf("--- spi_write_master(LMX2594_REG0, 0x0808) ---\n");


	while(1) {

	data = 0;
	ret = lmx2594_register_read(fd, LMX2594_REG0, &data);
	if(ret != 0)
		printf("--- Error lmk0482x_register_read(LMK0482x_REG_CFG_A, &data) ---\n");
	else
		printf("--- read register LMX2594_REG0 [0]:%x, ---\n", data);


	data = 0;
	ret = lmx2594_register_read(fd, LMX2594_REG1, &data);
	if(ret != 0)
		printf("--- Error lmk0482x_register_read(LMX2594_REG1, &data) ---\n");
	else
		printf("--- read register LMX2594_REG1 [0]:%x, ---\n", data);

	sleep(1);

	}
	//-----------------------------------------------------------------------

	return ret;

}

