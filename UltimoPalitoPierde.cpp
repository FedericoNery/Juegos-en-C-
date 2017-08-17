#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <windows.h>

using namespace std;
const size_t TAM_MAX = 4;
typedef string arregloDeString[TAM_MAX];

int ingresarPalitos();
unsigned int ingresarCantidadDeJugadores();
void ingresarNombresDeJugadores(unsigned int, arregloDeString);
void jugarAlUPP(unsigned int,int,arregloDeString);
unsigned int ingresarPalosASacar();

//FUNCIONES PARA MODIFICAR LA CONSOLA
void mensajeDeBienvenida();
void AjustarVentana(int, int);
void cambiarColorDeFondoYLetras(string);
void limpiarConsola();
void colocarNombreALaVentana(string);

int main()
{
    //Inicializacion
    colocarNombreALaVentana("AHORCADO");
    AjustarVentana(150,40);
    cambiarColorDeFondoYLetras("color 8C");
    mensajeDeBienvenida();
    Sleep(3000);
    limpiarConsola();

   arregloDeString nombresDeJugadores;
   int cantidadDePalitos = 0;
   unsigned int cantidadDeJugadores = 0;
   cantidadDePalitos = ingresarPalitos();
   limpiarConsola();
   cantidadDeJugadores = ingresarCantidadDeJugadores();
   limpiarConsola();
   ingresarNombresDeJugadores(cantidadDeJugadores,nombresDeJugadores);
   limpiarConsola();
   jugarAlUPP(cantidadDeJugadores,cantidadDePalitos,nombresDeJugadores);


}

int ingresarPalitos()
{
    string entrada;
    int cantPalitos = 0;
    while(cantPalitos<=0)
    {
        cout<<"Ingresar cantidad de palitos:";
        getline(cin,entrada);
        cantPalitos = atoi(entrada.c_str());
        if(cantPalitos<=0)
        {
            cout<<"ERROR!!!"<<endl;
        }
    }
    return cantPalitos;
}

unsigned int ingresarCantidadDeJugadores()
{
    string entrada;
    unsigned int cantJugadores = 0;
    while(cantJugadores<=1 || cantJugadores>4)
    {
        cout<<"Ingresar cantidad de jugadores:";
        getline(cin,entrada);
        cantJugadores = atoi(entrada.c_str());
        if(cantJugadores<=1 || cantJugadores>4)
        {
            cout<<"ERROR!!!"<<endl;
        }
    }
    return cantJugadores;
}

void ingresarNombresDeJugadores(unsigned int cantDeJugadores,arregloDeString nombresDeJugadores)
{
    string entrada;
    bool ingresoEsValido = false;
    unsigned int contador = 0;
    while(contador<cantDeJugadores)
    {
        while(!ingresoEsValido)
        {
            cout<<"Ingrese el nombre del jugador "<<(contador+1)<<":";
            getline(cin,entrada);
            if(!entrada.empty())
            {
                ingresoEsValido = true;
            }
        }
        nombresDeJugadores[contador] = entrada;
        ingresoEsValido = false;
        contador++;
    }
}

void jugarAlUPP(unsigned int cantJugadores,int cantPalitos,arregloDeString nombresDeJugadores)
{
    bool noHayMasPalitos = false,turnoCorrecto = false;
    unsigned int contadorDeTurno = 0;
    int palosASacar = 0;
    while(!noHayMasPalitos)
    {
        while(contadorDeTurno<cantJugadores && !noHayMasPalitos)
        {
            cout<<"JUEGA EL JUGADOR:"<<nombresDeJugadores[contadorDeTurno]<<endl;
            while((cantPalitos-palosASacar)>=0 && cantPalitos>0 && !turnoCorrecto)
            {
                palosASacar = ingresarPalosASacar();
                if((cantPalitos-palosASacar)<0 && cantPalitos>0)
                {
                    cout<<"ERROR debe retirar menos palos!!"<<endl;
                    palosASacar = 0;
                }
                else
                {
                    cantPalitos = cantPalitos-palosASacar;
                    turnoCorrecto = true;
                }
            }
            if(cantPalitos==0)
            {
                noHayMasPalitos = true;
                cout<<"El jugador:"<<nombresDeJugadores[contadorDeTurno]<<" PERDIO!! "<<endl;
            }
            contadorDeTurno++;
            palosASacar = 0;
            turnoCorrecto = false;
            Sleep(3000);
            limpiarConsola();
        }
        contadorDeTurno = 0;
    }
}

unsigned int ingresarPalosASacar()
{
    string entrada;
    bool ingresoEsValido = false;
    unsigned int cantPalosASacar = 0;
    while(!ingresoEsValido)
    {
        cout<<"Ingrese la cantidad de palos a sacar: ";
        getline(cin,entrada);

        if(entrada.length()==1)
        {
            cantPalosASacar = atoi(entrada.c_str());
            if(cantPalosASacar>=1 && cantPalosASacar<=3 )
            {
                ingresoEsValido = true;
            }
        }
    }
    return cantPalosASacar;
}

void AjustarVentana(int Ancho, int Alto) {
    _COORD Coordenada;
    Coordenada.X = Ancho;
    Coordenada.Y = Alto;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Right = Ancho - 1;
    Rect.Bottom = Alto - 1;

    // Obtener el handle de la consola
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    // Ajustar el buffer al nuevo tamaño
    SetConsoleScreenBufferSize(hConsola, Coordenada);
    // Cambiar tamaño de consola a lo especificado en el buffer
    SetConsoleWindowInfo(hConsola, TRUE, &Rect);
}

void cambiarColorDeFondoYLetras(string parametro)
{
    system(parametro.c_str());
}

void limpiarConsola()
{
    system("cls");
}

void colocarNombreALaVentana(string nombre)
{
    SetConsoleTitleA(nombre.c_str());
}

void mensajeDeBienvenida()
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" \t \t \t B B B  I EEEEE NN    N V       V EEEEE NN    N I DDDD   OOOO          A        "<<endl;
    cout<<" \t \t \t B    B I E     N N   N  V     V  E     N N   N I D   D O    O        A A       "<<endl;
    cout<<" \t \t \t B B B  I EEEEE N  N  N   V   V   EEEEE N  N  N I D   D O    O       A   A      "<<endl;
    cout<<" \t \t \t B    B I E     N   N N    V V    E     N   N N I D   D O    O      AAAAAAA     "<<endl;
    cout<<" \t \t \t B B B  I EEEEE N    NN     V     EEEEE N    NN I DDDD   OOOO      A       A    "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" \t  U    U L    TTTTT I MM   MM  OOOO     PPPP    A     L     I TTTTT  OOOO     PPPP  I EEEEE RRRR  DDDD  EEEEE      "<<endl;
    cout<<" \t  U    U L      T   I M M M M O    O    P   P  A A    L     I   T   O    O    P   P I E     R   R D   D E          "<<endl;
    cout<<" \t  U    U L      T   I M  M  M O    O    PPPP  A   A   L     I   T   O    O    PPPP  I EEEEE RRRR  D   D EEEEE      "<<endl;
    cout<<" \t  U    U L      T   I M     M O    O    P    AAAAAAA  L     I   T   O    O    P     I E     R  R  D   D E          "<<endl;
    cout<<" \t   UUUU  LLLLL  T   I M     M  OOOO     P   A       A LLLLL I   T    OOOO     P     I EEEEE R   R DDDD  EEEEE      "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
}

