#include "neos.h"
#include "hld.h"

int main ()
{
	palInit();
	palSetPadMode(IOPORTA, PAL_PORT_BIT(1), PAL_MODE_INPUT_ANALOG);
	uint16_t xx = palReadPad(IOPORTA, PAL_PORT_BIT(1));
	palWritePad(IOPORTA, PAL_PORT_BIT(1), PAL_HIGH);


	coreStartSchedule();
	return xx;
}