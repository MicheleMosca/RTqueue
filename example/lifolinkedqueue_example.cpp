extern "C"	{
	#include <ptask.h>
}
#include <iostream>
#include <RTqueue.h>

LIFOLinkedQueue<int> *queue;

ptask writer(){
    int id = ptask_get_index();

    printf("[ptask %d] Writer Started!\n", id);

    for (int i=0; i < 10; i++)
    {
        queue->push(i);
        printf("[ptask %d] Writed %d\n", id, i);
    }

    printf("[ptask %d] Writer Finish!\n", id);
}

ptask reader(){
    int id = ptask_get_index();

    printf("[ptask %d] Reader Started!\n", id);

    while (1)
    {
        printf("[ptask %d] %d \n", id, queue->pop());
    }
}

int main()
{
    ptask_init(SCHED_FIFO, GLOBAL, NO_PROTOCOL);

    queue = new LIFOLinkedQueue<int>();

    tpars params_scrittori = TASK_SPEC_DFL;
    params_scrittori.period = tspec_from(20, MILLI);
    params_scrittori.rdline = tspec_from(20, MILLI);
    params_scrittori.priority = 1;
    params_scrittori.measure_flag = 1;
    params_scrittori.act_flag = NOW;

    if(ptask_create_param(writer, &params_scrittori) == -1){
        std::cerr << "errore ptask_create_'param()" << std::endl;
        return -1;
    }

    tpars params_lettori = TASK_SPEC_DFL;
    params_lettori.period = tspec_from(20, MILLI);
    params_lettori.rdline = tspec_from(20, MILLI);
    params_lettori.priority = 1;
    params_lettori.measure_flag = 1;
    params_lettori.act_flag = NOW;

    if(ptask_create_param(reader, &params_lettori) == -1){
        std::cerr << "errore ptask_create_'param()" << std::endl;
        return -1;
    }

    for (;;);

    return 0;
}