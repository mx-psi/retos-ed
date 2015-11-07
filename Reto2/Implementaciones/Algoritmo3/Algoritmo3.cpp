#include <ctime>
#include "pila.h"
#include "vector.h"
#include <algorithm>
using namespace std;

bool Algo3(int obj, Vector& nums, Pila& p, int& m_a){

  // Caso base: 2 elementos
  if(nums.size() == 2){
    for (int op = 0; op < 4; op++) {
      int res = Opera(nums[0], nums[1], op);
      if(res == 0)
        continue;

      if(abs(res-obj) < abs(m_a-obj)){
        m_a = res;
        if(obj == m_a){
          p.push({nums[0], nums[1], op});
          return true;
        }
      }
    }
   return false;
  }

  // Caso recursivo: más de 2
  for (int op = 0; op < 4; op++) {
    for (int i = nums.inicial(op); i < nums.size(); i+=nums.avanza(i)){
      int nums_i = nums[i];
      for (int j = i+1; j < nums.size(); j+=nums.avanza(j)){
        int nums_j = nums[j];
        int res = Opera(nums_i, nums_j, op);
        if(res == 0 || res == nums_i || res == nums_j) continue;

        p.push({nums_i, nums_j, op});
        nums.borra(j);
        nums.borra(i);
        int pos = nums.inserta(res);

        if(abs(res-obj) < abs(m_a-obj)){
          m_a = res;
          if(obj == m_a)
            return true;
        }
        if(Algo3(obj,nums,p,m_a))
          return true;

        p.pop();
        nums.borra(pos);
        nums.inserta(nums_j);
        nums.inserta(nums_i);
      }
    }
  }
  return false;
}

void Cifras(int obj, int iniciales[6]) {
  Pila p;
  int m_a = 0;
  sort(iniciales, iniciales+6);
  Vector nums(iniciales);
  bool usados[6];

  clock_t tini = clock();
  Algo3(obj,nums,p,m_a);

  if(obj != m_a){
    nums.reinicia(iniciales);
    p.clear();
    obj = m_a;
    m_a = 0;
    Algo3(obj,nums,p,m_a);
  }
  clock_t tfin = clock();

  cout << "Obtenida: " << m_a << endl;
  p.Imprime(iniciales, usados);
  cout << "Tiempo: " << (tfin-tini)/(double)CLOCKS_PER_SEC << " segundos" << endl;
}
