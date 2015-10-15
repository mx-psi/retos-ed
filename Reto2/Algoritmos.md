##Algoritmos para hallar las cifras de Cifras y Letras

####Algoritmo 1:
* __Entrada__: número a buscar, números disponibles.
* __Procedimiento__:
  * Si el número de números disponibles es 2, se comprueba si hay una operación entre ellos cuyo resultado sea la solución: si es posible, se devuelve la operación realizada.
  * En caso contrario, para cada número disponible `i` y cada operación posible `op` (incluyendo la operación descartar el número actual, que puede entenderse como aquella que cumple `a op b = b`), se calcula `x` tal que `i` `op` `x` es igual al número a buscar y (si `x` es un número temporal válido y distinto del número a buscar) se llama a este mismo algoritmo con `x` como número a buscar y todos los números disponibles excepto `i` como números disponibles. En caso de que tal llamada devuelva una solución, se devolverá tal solución junto con la operación que se ha hecho en este paso.
* __Salida__: una serie de operaciones que llevan al número buscado o un indicador de que no se ha encontrado solución.
* __Implementaciones__:
  * __C++__: [try1.cpp]  (Reto2/try1.cpp). Incluye generador de valores de entrada aleatorios.
  * __JavaScript__: [try1.js]  (Reto2/try1.js). Incluye generador de valores de entrada aleatorios y lector de valores de entrada.
* __Problemas__:
  * __Es poco menos que de fuerza bruta__: prueba todas las posibles combinaciones que llevan exactamente al número hasta que encuentra alguna. Evidentemente no prueba caminos estúpidos o inválidos como divisiones no exactas, números temporales nulos o negativos o divisiones o productos por 1, pero la cantidad de caminos posibles sigue siendo muy elevada.
  * __No puede aproximar la solución__: si no encuentra solución exacta, no busca soluciones cercanas. Podría imponerse que, si no se encuentra solución, pruebe con los números anterior y siguiente, pero es una chapuza.
  * __No es exhaustivo__ (pese a que la intención es esa misma): en el pdf se afirma que con los números disponibles `C = {2,6,7,9,50,75}` puede obtenerse todo número de tres cifras. Si eso es cierto, el algoritmo no es exhaustivo, dado que no puede encontrar solución para `767, C` ni `821, C` (aunque para el resto de números de 100 a 999 sí). Esto se debe a que el algoritmo no considera soluciones en las que se haga una operación con dos números temporales, sino que obliga a que todas las operaciones incluyan un número proporcionado al principio (en el pdf no quedaba claro si esto era posible o no). Una solución (que este algoritmo no encuentra y a mí me ha costado bastante encontrar) para `767, {2,6,7,9,50,75}` es: `7 * 6 = 42;
9 * 75 = 675;
675 + 42 = 717;
717 + 50 = 767`
