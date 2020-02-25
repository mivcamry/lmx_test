#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <linux/spi/spidev.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "hal.h"

#include "lmx2594_reg.h"


#define MAX_PATH_LEN  40
//#define SPI_DEVICE_PATH_BASE "/dev/spidev"
//#define SPI_DEVICE "/dev/spidev2.1"


	
static int active = 0;

static uint32_t mode = 0;
static int lsb_first = 0;


static uint8_t bpw = 8;
static uint32_t speed = 1000000;

static int fd = -1;
void spi_init()
{
	active = 0;
	mode = 0;
	bpw = 8;
	speed = 1000000;
	fd = -1;
	lsb_first = 0;
}

int spi_open(int bus, int channel, int* fd)
{
	char spi_path[MAX_PATH_LEN];
	int r;

	if (active != 0)
	{
		close(*fd);
	}

	snprintf(spi_path, MAX_PATH_LEN, "/dev/spidev%d.%d", bus, channel);

	if ((*fd = open(spi_path, O_RDWR, 0)) < 0)
	{
		printf("open(%s) failed\n", spi_path);
		return *fd;
	}
	else
		printf("=== SPI device %s opened succesfull ===\n", spi_path);


	/*  spi mode  */
	if((r = ioctl(*fd, SPI_IOC_WR_MODE32, &mode)) < 0) {
		printf("ioctl(fd, SPI_IOC_WR_MODE32, &mode) failed\n");
		return r;
	}
	else
		printf("--- Set SPI_IOC_WR_MODE32 success ---\n");

	if((r = ioctl(*fd, SPI_IOC_RD_MODE32, &mode)) < 0) {
		printf("ioctl(fd, SPI_IOC_RD_MODE32, &mode) failed\n");
		return r;
	}
	else
		printf("--- Set SPI_IOC_RD_MODE32 success ---\n");

	/* bits per word */
	if((r = ioctl(*fd, SPI_IOC_WR_BITS_PER_WORD, &bpw)) < 0) {
		printf("ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bpw) failed\n");
		return r;
	}
	else
		printf("--- Set SPI_IOC_WR_BITS_PER_WORD success ---\n");
	if((r = ioctl(*fd, SPI_IOC_RD_BITS_PER_WORD, &bpw)) < 0) {
		printf("ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bpw) failed\n");
		return r;
	}
	else
		printf("--- Set SPI_IOC_RD_BITS_PER_WORD success ---\n");

	/* max speed hz */
	if((r = ioctl(*fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)) < 0) {
		printf("ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) failed\n");
		return r;
	}
	else
		printf("--- Set SPI_IOC_WR_MAX_SPEED_HZ success ---\n");

	if((r = ioctl(*fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)) < 0) {
		printf("ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) failed\n");
		return r;
	}
	else
		printf("--- Set SPI_IOC_RD_MAX_SPEED_HZ success ---\n");

	active = 1;
	
	return 0;
}

int spi_close(int fd)
{
	int tmpfd = fd;
	if (!active)
	{
		return -ENODEV;
	}
	
	mode = 0;
	bpw = 0;
	speed = 0;
	active = 0;
	fd = -1;
	return close(tmpfd);
}

int spi_set_mode(int fd, uint8_t m)
{
	m &= SPI_CPHA | SPI_CPOL;
	m = (mode & ~(SPI_CPHA | SPI_CPOL)) | m;

	int r = ioctl(fd, SPI_IOC_WR_MODE, &m);
	if (r < 0)
	{
		return r;
	}

	r = ioctl(fd, SPI_IOC_RD_MODE, &m);
	if (r < 0)
	{
		return r;
	}

	mode = m;

	return 0;
}

int spi_set_clk_polarity(int fd, uint8_t pol)
{
	uint8_t mode = 0;
	pol &= SPI_CPOL;
	mode = (mode & ~(SPI_CPOL)) | pol;

	return spi_set_mode(fd, mode);
}

int spi_set_clk_phase(int fd, uint8_t phase)
{
	uint8_t mode = 0;
	phase &= SPI_CPHA;
	mode = (mode & ~(SPI_CPHA)) | phase;

	return spi_set_mode(fd, mode);
}

int spi_set_lsb_first(int fd, int lsb_first)
{
	int r;
	if (!active)
	{
		return -ENODEV;
	}
	if ((r = ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsb_first)) < 0)
	{
		return r;
	}
	lsb_first = lsb_first;
	return 0;
}

int spi_set_bits_per_word(int fd, int bits)
{
	int r;
	if (!active)
	{
		return -ENODEV;
	}

	if ((r = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)) < 0)
	{
		return r;
	}

	bpw = bits;
	return 0;
}

/* CPHA - clock phase 
   CPOL - clock polarity
*/
int spi_set_speed(int fd, uint32_t speed)
{
	int r;
	uint32_t tmp;

	if (!active)
	{
		return -ENODEV;
	}

	r = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (r < 0)
	{
		printf("ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed): %s", strerror(r));
		return r;
	}

	r = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &tmp);
	if (r < 0)
	{
		printf("ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed): %s", strerror(r));
		return r;
	}
	speed = tmp;
	return 0;
}

int spi_xfer1(int fd, uint8_t* wbuf, uint8_t* rbuf, int len)
{
	struct spi_ioc_transfer txinfo;
	memset(&txinfo, 0, sizeof(struct spi_ioc_transfer));

	txinfo.tx_buf = (__u64) wbuf;
	txinfo.rx_buf = (__u64) rbuf;
	txinfo.len = len;
	txinfo.delay_usecs = 0;
	txinfo.speed_hz = speed;
	txinfo.bits_per_word = bpw;
	//@camry txinfo.cs_change = 1; --- Убрать !!! ---

	int r = ioctl(fd, SPI_IOC_MESSAGE(1), &txinfo);
	if (r < 0)
	{
		printf("ioctl(fd, SPI_IOC_MESSAGE(1), &txinfo): %s (len=%d)\n", strerror(r), len);
		return r;
	}

	//0 - OK
	return 0;
}


int spi_xfer(int fd, uint8_t *wbuf, uint8_t *rbuf, int len)
{
	int ret = 0;
	if (len != 3)
	{
		//2 bytes for adderss and 1 byte data
		return -1;
	}

	ret = spi_xfer1(fd, wbuf, rbuf, len);

	return ret;
}


#define AD916X_NUM_REGS_ 0x7FFF
uint32_t ad916x_registers[AD916X_NUM_REGS_] = {0};


int delay_us(unsigned int time_us)
{
    uint32_t retval = 0;
    struct timespec t0;
    struct timespec t1;
    struct timespec *tmp;
    struct timespec *waitTime = &t0;
    struct timespec *remainTime = &t1;

    waitTime->tv_sec  = time_us/1000000;
    waitTime->tv_nsec = (time_us % 1000000) * (1000);

    do {
        retval = nanosleep(waitTime, remainTime);
        tmp = waitTime;
        waitTime = remainTime;
        remainTime = tmp;
    }
    while((retval == -1) && (errno == EINTR));

    if(retval)
    {
        return errno;
    }
    else
    {
        return 0;
    }

}
