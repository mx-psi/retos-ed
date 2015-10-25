#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

// Operaciones a realizar
int suma(int a, int b){return a+b;}
int resta1(int a, int b){return a-b;}
int resta2(int a, int b){return resta1(b,a);}
int mult(int a, int b){return a*b;}
int div1(int a, int b){return (a%b)?-1:a/b;}
int div2(int a, int b){return div1(b,a);}


const int N = 6;
// Operaciones posibles
int (*op[N]) (int, int) = {suma, resta1, resta2, mult, div1, div2};
// Inversas de las operaciones
int (*inv[N]) (int, int) = {resta1, suma, suma, div1, mult, mult};
// Representaciones de las operaciones
string repr[N] = {"+", "-", "-", "*", "/", "/"};
// Orden de los argumentos de las operaciones
bool cambiados[N] = {false, false, true, false, false, true};

/**
  @brief: Representa "a · b = obj", donde · es la operación i-ésima
*/
string representa(int a, int b, int i, int obj)
{
  if(cambiados[i])
  {
    int temp = a;
    a = b;
    b = temp;
  }
  return to_string(a) + repr[i] + to_string(b) + "\t= " + to_string(obj);
}


/**
  @brief: Calcula la descomposición de un número
*/
string cifras(int obj, int* a, int n){

  if (n == 2){
    for(int i = 0; i < N; i++)
      if ((*op[i])(a[0],a[1]) == obj)
        return representa(a[0], a[1], i, obj);
    return "No";
  }

  for (int i = 0; i < n; i++)
  {
    // Crea un nuevo vector con los restantes
    int* resto = new int[n-1];
    for (int k = 0; k < i; k++)
      resto[k] = a[k];
    for (int k = i; k < n-1; k++)
      resto[k] = a[k+1];

    for(int j = 0; j < N; j++)
    {
      int nuevo_obj = (*inv[j])(obj,a[i]);
      if (nuevo_obj > 0 && nuevo_obj != obj) {
        string solt = cifras(nuevo_obj, resto, n-1);
        if (solt != "No")
          return solt + "\n" + representa(nuevo_obj, a[i], j, obj);
      }
    }
    string solt = cifras(obj, resto, n-1);
    if (solt != "No")
      return solt;

    delete[] resto;
  }
  return "No";
}


int main(){
  int posibles[14] = {1,2,3,4,5,6,7,8,9,10,25,50,75,100};

  srand(time(0));
  int obj = (rand()%900) + 100;
  int list[6];

  for (int i = 0; i < 6; i++)
    list[i] = posibles[rand()%14];

  cout << "[";
  for(int i = 0; i < 6; i++)
    cout << (i?",":"") << list[i];
  cout << "]\n";

  cout << obj << ":\n" << cifras(obj,list, 6);
}
