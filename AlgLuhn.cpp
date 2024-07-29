#include <iostream>

using namespace std;

void orderCard (int tarjetinha [], int j = 0){
	
	if (j < 16){
		
		cout << "Ingrese el digito numero " << j+1 << " de la tarjeta: "; 
		cin >> tarjetinha[j];
		
		if (tarjetinha[j] < 10 && tarjetinha[j] >= 0){
			orderCard (tarjetinha, j + 1);
		} else {
			cout << "DIGITO ERRONEO, VUELVA A INGRESAR" << endl; 
			orderCard (tarjetinha, j);
		}
	}			
}

int cardChecker (int tarjetinha []){
	
	int sum = 0;
			
	for(int i = 0; i < 16; ++i){
		if (i % 2 == 0){
			if(2 * tarjetinha [i] > 9){
				tarjetinha [i] = tarjetinha [i] - 9;
				sum = sum + tarjetinha [i];
			} else {
				tarjetinha [i] = 2 * tarjetinha[i];
				sum = sum + tarjetinha[i];
			}	
		} else {
			sum = sum + tarjetinha [i];
		}
	}
	
	return sum;
}

int main(){
	
	int tarjeta[16], suma = 0, i = 0;
	
	orderCard (tarjeta, i);
	
	suma = cardChecker(tarjeta);
	
	if (suma % 10 == 0){
		cout << "TARJETA VALIDA";
	} else {
		cout << "TARJETA INVALIDA";
	}	
}
