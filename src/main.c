#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "hal.h"
#include "app.h"


#define MAX_CMD_BUFFER 2
char buffer[MAX_CMD_BUFFER];


int main()
{
	int quit_flag = 0;
	int char_count = 0;

	printf("APP: LMX Module Example Application \r\n");

	APP_init();

	printf("**** Command Menu******* \r\n");

	printf("q: Quit Application \r\n");
	printf("************************ \r\n");

	while (quit_flag == 0)
	{
		char_count  = scanf("%c", &buffer[0]);

		if (char_count > 0 )
		{
			switch(buffer[0])
			{
			case 'q':
				printf("q: Quiting and Shutting Down\r\n");
				quit_flag = 1;
				break;
			case '\n':
				break;

			}
		}
	}

	APP_shutdown();

	return 0;
}
