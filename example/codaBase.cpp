#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <ptask.h>
#include <pthread.h>
#include <queue>
#include <iostream>

const int NUM_CODE = 3;
const int DIM_CODA = 10;

// Struttura coda generica
template <typename T>
struct CodaGenerica {
    std::queue<T> data;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
};

CodaGenerica<int> queues[NUM_CODE];

// produttori
template <typename T>
ptask produttore() {
    int index = ptask_get_index();
//    CodaGenerica<T>* coda = static_cast<CodaGenerica<T>*>(index);
    
    //itero la coda
    for (int i = 0; i < DIM_CODA; ++i) {
        
        /*     SEZIONE CRITICA     */
        
        pthread_mutex_lock(&queues[index].mutex);
        
        //aspetto che ci sia spazio nella coda
        while (queues[index].data.size() >= DIM_CODA) {
            pthread_cond_wait(&queues[index].condition, &queues[index].mutex);
        }

        //inserisco un elemento nella coda
        queues[index].data.push(i);

        //stampa di debug
//        std::cout << "Produttore %d ha scritto %d: " << index << i << std::endl;
        fprintf(stdout, "Produttore %d ha scritto %d\n", index, i);

        //segnalo che ho inserito un elemento
        pthread_cond_signal(&queues[index].condition);
        
        pthread_mutex_unlock(&queues[index].mutex);

        /*     FINE SEZIONE CRITICA     */
    }
}

// consumatori
template <typename T>
ptask consumatore() {
    int index = ptask_get_index();
//    CodaGenerica<T>* coda = static_cast<CodaGenerica<T>*>(index);
    
    //itero la coda
    for (int i = 0; i < DIM_CODA; ++i) {
        
        /*     SEZIONE CRITICA     */

        pthread_mutex_lock(&queues[index].mutex);
        
        //aspetto che ci siano elementi in coda
        while (queues[index].data.empty()) {
            pthread_cond_wait(&queues[index].condition, &queues[index].mutex);
        }

        //leggo
        int elemento = queues[index].data.front();
        queues[index].data.pop();

        //stampa di debug
        //std::cout << "Consumatore %d ha letto %d: " << index << elemento << std::endl;
        fprintf(stdout, "Consumatore %d ha letto %d\n", index, elemento);

        //segnalo che ho letto
        pthread_cond_signal(&queues[index].condition);
        
        pthread_mutex_unlock(&queues[index].mutex);

        /*     FINE SEZIONE CRITICA     */
    }
}

int main(){
    ptask_init(SCHED_FIFO, GLOBAL, PRIO_INHERITANCE);

	int last_proc = 0;
	int max_proc = ptask_getnumcores();

    //produttori
    for (int i = 0; i < NUM_CODE * 2; i+=2){
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

		if(i % 2 == 0){
			if (ptask_create_param(produttore<int>, &params) == -1){
				perror("Error: Can't create produttori task!\n");
				exit(-1);
            }	
        }
	}

    //consumatori
	for (int i = 1; i < NUM_CODE * 2; i++){
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

		if(i % 2 == 0){
			if (ptask_create_param(produttore<int>, &params) == -1){
				perror("Error: Can't create produttori task!\n");
				exit(-1);
            }	
        }
        else{
            if (ptask_create_param(consumatore<int>, &params) == -1){
				perror("Error: Can't create consumatori task!\n");
				exit(-1);
			}
		}	
	}

	sleep(100);

    return 0;
}