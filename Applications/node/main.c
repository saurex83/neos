#include "neos.h"
#include "hld.h"



int main ()
{

	uint8_t buf[10] = {0xaa};


	halInit();

	palSetPadMode(
		IOPORTH,
		PAL_PORT_BIT(0) | PAL_PORT_BIT(1),
	 	PAL_MODE_OUTPUT_PUSHPULL
	 	);

	palSetPadMode(
		IOPORTA,
		PAL_PORT_BIT(3),
	 	PAL_MODE_OUTPUT_PUSHPULL
	 	);	


	bool st;
	while (true)
		{
			palWritePad(IOPORTH, (0), st);
			palWritePad(IOPORTH, (1), ~st);

			palWritePad(IOPORTA, (3), st);

			st = ~ st;

			spi1Write(buf, sizeof(buf));
		}

	coreStartSchedule();
	return 1;
}