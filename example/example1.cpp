#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <ptask.h>

ptask prova()
{
	int id = ptask_get_index();
	printf("[%d] Task Start!\n", id);

	for (int i = 0; i < 3; i++)
	{
		printf("[%d] Start period %d\n", id, i);
		ptask_wait_for_period();
		printf("[%d] End period %d\n", id, i);
	}

	printf("[%d] Task End!\n", id);
}

int main()
{
	ptask_init(SCHED_FIFO, GLOBAL, PRIO_INHERITANCE);

	int last_proc = 0;
	int max_proc = ptask_getnumcores();

	for (int i = 0; i < 5; i++)
	{
		tpars params = TASK_SPEC_DFL;
		params.period = tspec_from(20, MILLI);
		params.rdline = tspec_from(20, MILLI);
		params.priority = 80 - i;
		params.measure_flag = 1;
		params.act_flag = NOW;
		/* a round robin assignment */
		params.processor = last_proc++;
		if (last_proc >= max_proc)
                last_proc = 0;

		if (ptask_create_param(prova, &params) == -1)
		{
			perror("Error: Can't create task!\n");
			exit(-1);
		}
	}

	sleep(10);
	return 0;
}