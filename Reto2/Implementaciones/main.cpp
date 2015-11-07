#include <ctime>
#include <cstdlib>

void Cifras(int solucion,int disponibles[]);

int main(int argc, char* argv[]) {
   int disponibles[6];
   int solucion;
   if (argc == 8) {
      solucion = atoi(argv[7]);
      for (int i = 0; i < 6; i++)
         disponibles[i] = atoi(argv[i+1]);
   }
	else {
      int posibles[14] = {1,2,3,4,5,6,7,8,9,10,25,50,75,100};

      srand(time(0));
      solucion = (rand()%900) + 100;

      for (int i = 0; i < 6; i++)
         disponibles[i] = posibles[rand()%14];
   }

   Cifras(solucion, disponibles);
}
