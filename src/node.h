#ifndef Node_H
#define Node_H

//! Struture definition of a Node

template <typename T> class Node {
    private:
        //! Element of the node
        T data;

        //! Pointer to the next node
        Node* next;

    public:
        //! Constructor of the Node
        Node(){ this->next = nullptr; };

        //! Set the element of the Node
        void setData(T element) { this->data = element; };

        //! Set the pointer to the next Node
        void setNext(Node<T>* element) { this->next = element; };

        //! Return the element of the Node
        T getData(void){ return data; }

        //! Return the pointer od the next Node
        Node* getNext(void){ return next; }
};

#endif