extern "C"	{
	#include <ptask.h>
}
#include <iostream>
#include <RTqueue.h>
#include <chrono>
using namespace std::chrono;

#define N 100

typedef struct struct_data{
    int thread_id;
    int data;
}data;

StaticQueue<data> *queue;

ptask writer(){
    int id = ptask_get_index();

    data my_data;

    my_data.thread_id = id;

    for (int i=0; i < N; i++)
    {
        my_data.data = i;

        auto start = high_resolution_clock::now();

        queue->push(my_data);

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(stop - start);

        printf("writer%d %d %ld\n", id, i, duration.count());
        sleep(0.5); // wait before push another data
    }
}

ptask reader(){
    int id = ptask_get_index();

    data my_data;

    while (1)
    {
        auto start = high_resolution_clock::now();

        my_data = queue->pop();

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(stop - start);

        printf("reader%d %d %ld %d\n", id, my_data.data, duration.count(), my_data.thread_id);
    }
}

int main()
{
    ptask_init(SCHED_FIFO, GLOBAL, NO_PROTOCOL);

    queue = new LIFOStaticQueue<data>(100);

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