namespace ft
{
  template <typename T>
  void baseSwap(T &a, T &b){

    T temp = a;
    a = b;
    b = temp;
  };
}; // NAMESPACE