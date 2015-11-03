#include "pila.h"
#include "vector.h"
#include <ctime>
using namespace std;

// Distancia
inline int d(int a, int b){return abs(a-b);}

bool Cifras(int obj, Vector& nums, Pila& p, int& m_a){

  // Caso base: 2 elementos
  if(nums.size() == 2){
    for (int op = 0; op < 4; op++) {
      int res = Opera(nums[0], nums[1], op);
      if(res == 0)
        continue;

      if(d(res,obj) < d(m_a,obj)){
        m_a = res;
        if(d(obj,m_a) == 0){
          p.push({nums[0], nums[1], op});
          return true;
        }
      }
    }
   return false;
  }

  // Caso recursivo: más de 2
  for (int op = 0; op < 4; op++) {
    for (int i = nums.no_usa_uno(op); i < nums.size(); i+=nums.dup(i)){
      int nums_i = nums[i];
      for (int j = i+1; j < nums.size(); j+=nums.dup(j)){
        int nums_j = nums[j];
        int res = Opera(nums_i, nums_j, op);
        if(res == 0 || res == nums_i || res == nums_j) continue;

        p.push({nums_i, nums_j, op});
        nums.borra(j); // Borramos primero j para conservar posiciones
        nums.borra(i);
        int pos = nums.inserta(res); //pos: Posición de res

        if(d(res,obj) < d(m_a,obj)){
          m_a = res;
          if(d(obj,m_a) == 0) return true;
        }
        if(Cifras(obj,nums,p,m_a))
          return true;

        p.pop();
        nums.borra(pos);
        nums.inserta(nums_j);
        nums.inserta(nums_i);
      }
    }
  }
}

int main(){
  int posibles[14] = {1,2,3,4,5,6,7,8,9,10,25,50,75,100};

  srand(time(0));
  int obj = (rand()%900) + 100;
  int list[6];

  for (int i = 0; i < 6; i++)
    list[i] = posibles[rand()%14];

  Pila p;
  int m_a = 0;

  Vector nums(list);

  // Objetivo
  cout << nums << "⟶ " << obj << endl;

  // Algoritmo
  clock_t tini = clock();
  Cifras(obj,nums,p,m_a);
  clock_t tfin = clock();

  // Impresión de la solución
  cout << "Obtenida: " << m_a << endl;
  bool usados[6];
  if(!p.empty())
    p.Imprime(list, usados, p.size()-1);

  cout << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
}
