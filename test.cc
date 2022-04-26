#include <iostream>

int main() {

int opc{0},n{0},i{0};
double A[30],x, suma{0}, resta {0}; 

while(true){

	do {

      std::cout << "Introduzca opcion. <1>Suma <2>Resta <0>Salir: ";
      std::cin >> opc;

    } while (opc>2 || opc<0);

 	if (opc == 1){

		std::cout << "Introduzca el valor de n: ";
	    std::cin >> n;
	    A[i] = n;
	    i++;

	    std::cout << "Introduzca el valor de x: ";
    	std::cin >> x;
	    A[i] = x;
	    i++;

 		suma = n + x;
 		std::cout << "Suma = " << suma << std::endl;
 		A[i] = suma;
	    i++;

	}else if (opc == 2){

		std::cout << "Introduzca el valor de n: ";
	    std::cin >> n;
	    A[i] = n;
	    i++;	    
	    
	    std::cout << "Introduzca el valor de x: ";
    	std::cin >> x;
	    A[i] = x;
	    i++; 	

		resta = n - x;
 		std::cout << "Resta = " << resta << std::endl;
 		A[i] = resta;
 		i++;

	}

    if(opc == 0){
      std::cout << "Tabla de resultado: " << std::endl;

      for (int j = 0; j < i;){
      	for (int k = 0; k < 3; ++k, ++j)
      		std::cout << A[j] << " ";
      	std::cout << std::endl;
      }	
	  return 0;
    }
  }
}