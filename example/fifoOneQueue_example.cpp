extern "C"	{
	#include <ptask.h>
}

#include <iostream>
#include <RTqueue.h>
#include <iostream>

int numQueue = 3;
int dimQueue = 10;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FIFOLinkedQueue<int>* queue = new FIFOLinkedQueue<int>();

ptask scrittori(){
    int argomento = *((int*)ptask_get_argument());
    if (argomento < 0 || argomento >= numQueue) {
        std::cerr << "Indice task non valido" << std::endl;
        //return;
    }
    std::cout << "Scrittore " << argomento << " partito!" << std::endl;

    while(true){

        /*     SEZIONE CRITICA     */
            
        pthread_mutex_lock(&mutex);

        //aspetto che ci sia spazio nella coda
        while (queue->size() >= dimQueue) {
            pthread_cond_wait(&condition, &mutex);
        }

        //inserisco un elemento nella coda
        //nota: se la coda è piena, estraggo l'elemento più vecchio e inserisco quello nuovo
        if(queue->size() == dimQueue)
            queue->pop();
        queue->push(argomento);

        //stampa di debug
        std::cout << "Scrittore " << argomento << " ha scritto: " << queue->back() << std::endl;

        //stampo la coda
        std::cout << "Scrittore " << argomento << " stampa coda: " << std::endl; 
        std::cout << "dimCoda: " << queue->size() << std::endl;
        queue->printQueue();

        //segnalo che ho inserito un elemento nella coda
        pthread_cond_signal(&condition);
            
        pthread_mutex_unlock(&mutex);

        /*     FINE SEZIONE CRITICA     */

        }
}

ptask lettori(){
    int argomento = *((int*)ptask_get_argument());
    if (argomento < 0 || argomento >= numQueue) {
        std::cerr << "Indice task non valido" << std::endl;
        //return;
    }
    std::cout << "Lettore " << argomento << " partito!" << std::endl;

    while(true){

        /*     SEZIONE CRITICA     */
            
        pthread_mutex_lock(&mutex);

        //aspetto che ci siano elementi nella coda
        while (queue->empty()) {
            pthread_cond_wait(&condition, &mutex);
        }

        //leggo un elemento nella coda
        int elemento = queue->pop();

        //stampa di debug
        std::cout << "Lettore " << argomento << " ha letto: " << elemento << std::endl;

        //stampo la coda
        std::cout << "Lettore " << argomento << " stampa coda: " << std::endl; 
        queue->printQueue();
        
        //segnalo che ho letto un elemento
        pthread_cond_signal(&condition);
            
        pthread_mutex_unlock(&mutex);

        /*     FINE SEZIONE CRITICA     */

    }
}

int main()
{
    ptask_init(SCHED_FIFO, GLOBAL, NO_PROTOCOL);
    
    tpars params_scrittori = TASK_SPEC_DFL;

    for(int i = 0; i < numQueue; i++){
        std::cout << "for scrittori" << std::endl;

        params_scrittori.period = tspec_from(20, MILLI);
        params_scrittori.rdline = tspec_from(20, MILLI);
        params_scrittori.priority = 1;
        params_scrittori.measure_flag = 1;
        params_scrittori.act_flag = NOW;
        params_scrittori.arg = &i;

        if(ptask_create_param(scrittori, &params_scrittori) == -1){
            std::cerr << "errore ptask_create_'param()" << std::endl;
            return -1;
        }
        sleep(1);
    }

    tpars params_lettori = TASK_SPEC_DFL;
    for(int i = 0; i < numQueue; i++){
        params_lettori.period = tspec_from(20, MILLI);
        params_lettori.rdline = tspec_from(20, MILLI);
        params_lettori.priority = 1;
        params_lettori.measure_flag = 1;
        params_lettori.act_flag = NOW;
        params_lettori.arg = &i;

        if(ptask_create_param(lettori, &params_lettori) == -1){
            std::cerr << "errore ptask_create_'param()" << std::endl;
            return -1;
        }
        sleep(1);
    }

    for(int i = 0; i < numQueue * 2; i++){
        ptask_get_threadid(i);
    }

    return 0;

}