#include <iostream>

//struttura dati nodo coda
template <typename T>
struct Node {
    T data;
    Node* next;
};

//classe coda multipla
template <typename T>
class CodaMultipla {
    private:
        int numCode;
        Node<T>** code;
        int* dim;

    public:
        CodaMultipla(int numCode) : numCode(numCode), code(new Node<T>*[numCode]), dim(new int[numCode]) {
            for (int i = 0; i < numCode; i++) {
                code[i] = nullptr;
                dim[i] = 0;
            }
        }

        //inserisce un elemento nella coda specificata
        void push(int indiceCoda, const T& elemento) {
            //controllo l'indice della coda
            if (indiceCoda < 0 || indiceCoda >= numCode) {
                std::cerr << "Indice di coda non valido" << std::endl;
                return;
            }

            //creo un nodo temporaneo
            Node<T>* newNode = new Node<T>{elemento, nullptr};

            //se la coda non esiste ne creo una nuova (tramite la temporanea), altrimenti aggiungo l'elemento
            if (!code[indiceCoda]) {
                code[indiceCoda] = newNode;
            } else {
                Node<T>* current = code[indiceCoda];
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }

            //aggiorno la dimensione della coda
            dim[indiceCoda]++;
        }

        //estrae un elemento dalla coda specificata
        T pop(int indiceCoda) {
            //controllo l'indice della coda
            if (indiceCoda < 0 || indiceCoda >= numCode || dim[indiceCoda] == 0) {
                std::cerr << "Indice di coda non valido o coda vuota" << std::endl;
                return T();
            }

            //prelevo l'elemento in testa alla coda e lo elimino
            Node<T>* testa = code[indiceCoda];
            T elemento = testa->data;
            code[indiceCoda] = testa->next;
            delete testa;

            //aggiorno la dimensione della coda
            dim[indiceCoda]--;

            return elemento;
        }

        //restituisce il numero di elementi nella coda specificata
        int size(int indiceCoda) const {
            if (indiceCoda < 0 || indiceCoda >= numCode) {
                std::cerr << "Indice di coda non valido" << std::endl;
                return 0;
            }

            return dim[indiceCoda];
        }

        //stampa la coda specificata
        void stampaCoda(int indiceCoda){
            //controllo l'indice della coda
            if (indiceCoda < 0 || indiceCoda >= numCode) {
                std::cerr << "Indice di coda non valido" << std::endl;
                return;
            }

            //prendo la coda da stampare e la itero
            Node<T>* current = code[indiceCoda];
            while (current->next) {
                std::cout << current->data << ' ';
                current = current->next;
            }
            std::cout << current->data << std::endl;

            return;
        }
};

int main() {
    //definisco la coda multipla
    CodaMultipla<int> codaMultipla(3);

    //inserisco gli elementi nelle code
    codaMultipla.push(0, 1);
    codaMultipla.push(1, 2);
    codaMultipla.push(2, 3);

    codaMultipla.push(0, 2);
    codaMultipla.push(0, 3);
    codaMultipla.push(1, 3);

    //stampa debug
    std::cout << "Coda 0 size: " << codaMultipla.size(0) << std::endl;
    std::cout << "Coda 1 size: " << codaMultipla.size(1) << std::endl;
    std::cout << "Coda 2 size: " << codaMultipla.size(2) << std::endl;

    //debug stampaCoda
    std::cout << "stampo coda 0: ";
    codaMultipla.stampaCoda(0);

    //estraggo elementi dalle code
    int elemento1 = codaMultipla.pop(0);
    int elemento2 = codaMultipla.pop(1);
    int elemento3 = codaMultipla.pop(2);

    //stampa debug
    std::cout << "Pop dalla coda 0: " << elemento1 << std::endl;
    std::cout << "Pop dalla coda 1: " << elemento2 << std::endl;
    std::cout << "Pop dalla coda 2: " << elemento3 << std::endl;

    return 0;
}
