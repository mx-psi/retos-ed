#include "pila.h"
#include "vector.h"
#include <ctime>
#include <algorithm>
using namespace std;

// Distancia
inline int d(int a, int b){return abs(a-b);}

bool Cifras(int obj, Vector& nums, Pila& p, int& m_a){
  for (int op = 0; op < 4; op++) {
    for (int j = nums.no_usa_uno(op); j < nums.size(); j+=nums.dup(j)){
      int nums_j = nums[j];
      for (int k = j+1; k < nums.size(); k+=nums.dup(k)){
        int nums_k = nums[k];
        int res = Opera(nums_j, nums_k, op);
        if(res == 0) continue;

        p.push({nums_j, nums_k, op});
        nums.borra(k);
        nums.borra(j);
        int pos = nums.inserta(res);

        if(d(res,obj) < d(m_a,obj)){
          m_a = res;
          if(d(obj,m_a) == 0) return true;
        }
        if(Cifras(obj,nums,p,m_a))
          return true;

        p.pop();
        nums.borra(pos);
        nums.inserta(nums_k);
        nums.inserta(nums_j);
      }
    }
  }
  return false;
}

int main(){
  int posibles[14] = {1,2,3,4,5,6,7,8,9,10,25,50,75,100};

  srand(time(0));
  int obj = (rand()%900) + 100;
  int list[6];

  for (int i = 0; i < 6; i++)
    list[i] = posibles[rand()%14];
  sort(list, list+6);

  Pila p;
  Vector nums(list);
  int m_a = list[5];

  // Objetivo
  cout << nums << "⟶ " << obj << endl;

  clock_t tini = clock();
  Cifras(obj,nums,p,m_a);
  clock_t tfin = clock();

  // Solución
  cout << "Obtenida: " << m_a << endl;
  cout << p;

  // Tiempo
  cout << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
}
