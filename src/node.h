#ifndef NODE_H
#define NODE_H

template <typename T> class Node {
    private:
        T data;
        Node* next;

    public:
        Node(){ this->next = nullptr; };
        void setData(T element) { this->data = element; };
        void setNext(Node<T>* element) { this->next = element; };

        T getData(void){ return data; }
        Node* getNext(void){ return next; }
};

#endif