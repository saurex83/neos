#include "events.h"
int main ();

void test(void)
{

}

SUBSCRIBERS_CHAIN_BEGIN(Oleg)
	SUBSCRIBER(test),
	SUBSCRIBER(test),
	SUBSCRIBER(test)
SUBSCRIBERS_CHAIN_END



int main ()
{
	return 0;
}