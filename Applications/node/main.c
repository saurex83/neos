#include "neos.h"
#include "hld.h"



int main ()
{

	uint8_t buf[10] = {0xaa};


	halInit();

	palSetPadMode(
		IOPORTH,
		0,
	 	PAL_MODE_OUTPUT_PUSHPULL
	 );

	palSetPadMode(
		IOPORTH,
		1,
	 	PAL_MODE_OUTPUT_PUSHPULL
	 );

	palSetPadMode(
		IOPORTA,
		3,
	 	PAL_MODE_OUTPUT_PUSHPULL
	 );	


	bool st = true;
	while (true)
		{
			palWritePad(IOPORTH, (0), st);
			palWritePad(IOPORTH, (1), ~st);

			palWritePad(IOPORTA, (3), st);
			//palWritePort(IOPORTA, 0xffff);
			//palWritePort(IOPORTA, 0x0);
			st = !st;

			spi1Send_sync(buf, sizeof(buf));
		}

	coreStartSchedule();
	return 1;
}