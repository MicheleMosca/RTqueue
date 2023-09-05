#define _GNU_SOURCE
#include <ptask.h>
#include <iostream>

int numQueue = 5;
int dimQueue = 10;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//classe nodo
template <class T>
class Node{
    private:
        T data;
        Node* next;

    public:
        void setData(T element){
            data = element;
        }

        void setNext(Node<T>* element){
            next = element;
        }

        T getData(void){
            return data;
        }

        Node* getNext(void){
            return next;
        }
};

//classe coda
template <class T>
class Queue{  
    private:
        Node<T>* first;
        Node<T>* last;
        int count;
    
    public:
        Queue(void){
            first = NULL;
            last = NULL;
            count = 0;
        }

        void push(T element)
        {
            Node<T>* tmp = new Node<T>();
            tmp->setData(element);
            tmp->setNext(NULL);

            if (isEmpty()) {
                first = last = tmp;
            }
            else {
                last->setNext(tmp);
                last = tmp;
            }
            count++;
        }

        T pop(void){
            if ( isEmpty() )
                std::cout << "Queue is empty" << std::endl;
            
            T ret = first->getData();
            Node<T>* tmp = first;
            first = first->getNext();
            count--;
            delete tmp;
            return ret;
        }

        void printQueue(int indiceCoda){
            if(isEmpty()){
                std::cout << "Queue is empty" << std::endl;
                return;
            }
            
            Node<T> *tmp = first;
            while(first->getNext()){
                std::cout << tmp->getData() << ' '; 
                first = first->getNext();
            }
            std::cout << tmp->getData() << std::endl;
        }

        T First(void){
            if (isEmpty())
                std::cout << "Queue is empty" << std::endl;
            return first->getData();
        }

        T Last(void){
            if (isEmpty())
                std::cout << "Queue is empty" << std::endl;
            return last->getData();
        }

        int Size(void){
            return count;
        }

        bool isEmpty(void){
            return count == 0 ? true : false;
        }
};

Queue<int> queue[5];

ptask scrittori(){
    int argomento = *((int*)ptask_get_argument());
    if (argomento < 0 || argomento >= numQueue) {
        std::cerr << "Indice task non valido" << std::endl;
        return;
    }
    std::cout << "Scrittore " << argomento << " partito!" << std::endl;

    /*     SEZIONE CRITICA     */
        
    pthread_mutex_lock(&mutex);

    //aspetto che ci sia spazio nella coda
    while (queue[argomento].Size() >= dimQueue) {
        pthread_cond_wait(&condition, &mutex);
    }

    //inserisco un elemento nella coda
    queue[argomento].push(argomento);

    //stampa di debug
    std::cout << "Scrittore " << argomento << " ha scritto: " << queue[argomento].Last() << std::endl;

    //stampo la coda
    std::cout << "Scrittore " << argomento << " stampa coda: " << std::endl; 
    queue[argomento].printQueue(argomento);

    //segnalo che ho inserito un elemento nella coda
    pthread_cond_signal(&condition);
        
    pthread_mutex_unlock(&mutex);

    /*     FINE SEZIONE CRITICA     */
}

ptask lettori(){
    int argomento = *((int*)ptask_get_argument());
    if (argomento < 0 || argomento >= numQueue) {
        std::cerr << "Indice task non valido" << std::endl;
        return;
    }
    std::cout << "Lettore " << argomento << " partito!" << std::endl;

    /*     SEZIONE CRITICA     */
        
    pthread_mutex_lock(&mutex);

    //aspetto che ci siano elementi nella coda
    while (queue[argomento].isEmpty()) {
        pthread_cond_wait(&condition, &mutex);
    }

    //stampo la coda
    std::cout << "Lettore " << argomento << " stampa coda: " << std::endl; 
    queue[argomento].printQueue(argomento);

    //leggo un elemento nella coda
    int elemento = queue[argomento].pop();

    //stampa di debug
    std::cout << "Lettore " << argomento << " ha letto: " << elemento << std::endl;
    
    //segnalo che ho letto un elemento
    pthread_cond_signal(&condition);
        
    pthread_mutex_unlock(&mutex);

    /*     FINE SEZIONE CRITICA     */
}

int main(){
    ptask_init(SCHED_FIFO, GLOBAL, NO_PROTOCOL);
    
    tpars params_scrittori = TASK_SPEC_DFL;
    for(int i = 0; i < numQueue; i++){
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
    }

    for(int i = 0; i < numQueue * 2; i++){
        ptask_get_threadid(i);
    }

    return 0;
}
