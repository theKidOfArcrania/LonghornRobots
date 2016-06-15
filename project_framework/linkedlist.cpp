#define NULL 0 //is this right?
//sparse matrix with doubly linked lists
//scratch that^
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
    Node()
    {
      data = NULL;
      next = NULL;
      prev = NULL;
    }
    Node(T dat, Node *nxt, Node *prv) //do I need <T>?
    {
      data = dat;
      next = nxt;
      prev = prv;
    }
    T getdata(){
      return data;
    }
    void setdata(T dat){
      data = dat;
    }
    Node* getnext(){
      //did I handle null pointer exeptions?
      return next;
    }
    void setnext(Node *nxt){
      next = nxt;
    }
    Node* getprev(){
      return prev;
    }
    void setprev(Node *prv){
      prev = prv;
    }    
}; //does node need to be in stack?
template <class T>
class Stack{
  private:
    Node<T> top;
    Node<T> temp;
  public:
    Stack(){
      top = NULL;
      temp = NULL;
    }
    void push(Node<T> tp)
    {
        if(top == NULL){
        top = tp;
        top.setnext(temp);
        top.setprev(NULL);
        }
        else{  //if(temp == NULL){
          tp.setnext(top);
          tp.setprev(NULL);
          top.setprev(tp);
          temp = top;
          top = tp;
        }
        //check
    }
    T pop()
    {
      if(top == NULL){
        return NULL;
      }
      
      temp.setprev(NULL);
      top.setnext(NULL);
      Node<T> tmp2 = top;
      top = temp;
      temp = temp.getnext();
      return tmp2;
    }
    T peektop()
    {
      return top;
    }
};

