#include <stdio.h>
#include "app.h"
#include "hal.h"
#include "lmx2594.h"
#include "app_error.h"

int fd = -1;

int APP_init(void)
{
	int appError = APP_ERR_OK;
	/*Initialise SPI Driver on Platform*/
	printf("APP:INIT: SPI \r\n");

	spi_init();
	appError = spi_open(1,2, &fd);
	if(appError != APP_ERR_OK) {
		printf("APP_init: spi_open() failed! Error: %d \n", appError);
		return appError;
	}

	appError = lmx2594_configure(fd);
	if(appError != APP_ERR_OK) {
		printf("APP_init: spi_configure() failed! Error: %d \n", appError);
		return appError;
	}
	else
		printf("spi_configure() successful! \n");


	return appError;
}

int APP_shutdown(void)
{
	int appError = APP_ERR_OK;

	printf("APP:SHTDWN: SPI \r\n");
	spi_close(fd);
	fd = -1;

	return appError;
}
