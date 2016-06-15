// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
class Node{
  //template<typename T>  T data = T(0);
  private:
    T data;
    //node<T> *next = NULL;
    //node<T> *prev = NULL;
    Node *next;
    Node *prev;
  public:
    Node();
    Node(T dat, Node *nxt, Node *prv);
    T getdata();
    void setdata(T dat);
    Node* getnext();
    void setnext(Node *nxt);
    Node* getprev();
    void setprev(Node *prv);
};

template <class T>
class Stack{
  private:
    Node<T> top;
    Node<T> temp;
  public:
    Stack();
    void push(Node<T> tp);
    T pop();
    T peektop();
};

// This is the end of the header guard
#endif
