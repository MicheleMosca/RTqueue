#include <stdlib.h>
#include <unistd.h>
#include <ptask.h>

ptask prova()
{
	int i;
	i = ptask_get_index();
	printf("Sono partito!\n");
	while (1)
	{
		ptask_wait_for_period();
		printf("periodo\n");
	}
}

int main()
{
	ptask_create_prio(&prova, 10, 1, NOW);
	printf("Ho fatto partire il cazzillo!\n");
	sleep(1000);
	return 0;
}
