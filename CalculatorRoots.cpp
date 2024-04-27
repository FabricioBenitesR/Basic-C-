#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, b, c, discriminante, raiz1, raiz2;

    cout << "Ingrese la ecuacion de segundo grado:" << endl;
   
    cout << "Ax^2: "; cin >> a;
    cout << "Bx: "; cin >> b;
    cout << "C: "; cin >> c;

    discriminante = b*b - 4*a*c;

    raiz1 = ((-1)*(b) + sqrt(discriminante))/((2)*(a));
    raiz2 = ((-1)*(b) - sqrt(discriminante))/((2)*(a));

    cout << "Las raices son: " << raiz1 << " ; " << raiz2;  
}
