#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>

using namespace std;

const size_t TAM_JUGADORES = 2;
typedef string arregloDeString[TAM_JUGADORES];

const size_t TAM_TABLERO = 10;
typedef char tablero[TAM_TABLERO][TAM_TABLERO];

//FUNCIONES DE INICIALIZACION
void inicializarTablero(tablero);

//FUNCIONES DE INGRESO
void ingresarNombresDeJugadores(arregloDeString);
void ingresarTodosLosBarcos(tablero);
void ingresarBarco(tablero,int,size_t);
string ingresarCoordenada();


//FUNCIONES DE MODIFICACION
void guardarValores(tablero,string,string);
void modificarTablero(tablero,string);

//FUNCIONES DE JUEGO
void jugarAlaBatallaNaval(arregloDeString,tablero,tablero);

//FUNCIONES LOGICAS
bool hundioTodosLosBarcos(tablero);
bool golpeoAlBarco(tablero,string);
bool coordenadaEsNegativa(int);
bool coordenadaOrtogonalEsValida(string,string,int);
bool coordenadaIngresadaEsValida(string);

//FUNCIONES PARA MOSTRAR EN CONSOLA
void imprimirEncabezadoSuperior();
void mostrarIngresoDeTablero(tablero);
void mostrarTablero(tablero);
void imprimirPosiblesCoordenadasFinales(char,char,int);

//FUNCIONES PARA MODIFICAR LA CONSOLA
void mensajeDeBienvenida();
void AjustarVentana(int, int);
void cambiarColorDeFondoYLetras(string);
void limpiarConsola();
void colocarNombreALaVentana(string);

int main()
{
    //Inicializacion
    colocarNombreALaVentana("BATALLA NAVAL");
    AjustarVentana(150,50);
    cambiarColorDeFondoYLetras("color 1D");
    mensajeDeBienvenida();
    Sleep(3000);
    limpiarConsola();
    arregloDeString nombresDeJugadores;
    tablero mapaDelJugadorA;
    tablero mapaDelJugadorB;

    //Inicializo tableros
    inicializarTablero(mapaDelJugadorA);
    inicializarTablero(mapaDelJugadorB);

    //Ingreso nombres de jugadores
    ingresarNombresDeJugadores(nombresDeJugadores);
    limpiarConsola();
    //Ingreso Barcos
    cout<<"Jugador A: "<<nombresDeJugadores[0]<<endl;
    ingresarTodosLosBarcos(mapaDelJugadorA);
    limpiarConsola();
    cout<<"Jugador B: "<<nombresDeJugadores[1]<<endl;
    ingresarTodosLosBarcos(mapaDelJugadorB);
    limpiarConsola();
    //Jugar
    jugarAlaBatallaNaval(nombresDeJugadores,mapaDelJugadorA,mapaDelJugadorB);

}

void ingresarNombresDeJugadores(arregloDeString nombresDeJugadores)
{
    string entrada;
    bool ingresoEsValido = false;
    unsigned int contador = 0;
    while(contador<2)
    {
        while(!ingresoEsValido)
        {
            cout<<"Ingrese el nombre del jugador "<<(contador+1)<<": ";
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

void ingresarTodosLosBarcos(tablero mapaDelJugador)
{
    mostrarIngresoDeTablero(mapaDelJugador);
    ingresarBarco(mapaDelJugador,5,1);
    ingresarBarco(mapaDelJugador,4,1);
    ingresarBarco(mapaDelJugador,3,1);
    ingresarBarco(mapaDelJugador,2,1);

    /*
    ingresarBarco(mapaDelJugador,5,1);
    ingresarBarco(mapaDelJugador,4,2);
    ingresarBarco(mapaDelJugador,3,3);
    ingresarBarco(mapaDelJugador,2,4);
    */
}

void ingresarBarco(tablero mapaDelJugador,int tamanioBarco, size_t cantidadDeBarcos)
{
    bool ingresoGeneralEsValido = false, ingresoCoordFinalEsValida = false;
    size_t cantidadBarcosIngresados = 0;
    char filaInicial,columnaInicial;
    string entrada,coordenadaOrigen,coordenadaFinal;
    while(cantidadBarcosIngresados<cantidadDeBarcos)
    {
        cout<<"INGRESO DEL BARCO DE "<<tamanioBarco<<" POSICIONES"<<endl;
        while(!ingresoGeneralEsValido)
        {
            cout<<"Ingrese coordenadas numericas de origen: ";
            getline(cin,entrada);
            if(coordenadaIngresadaEsValida(entrada))
            {
                coordenadaOrigen = entrada;
                filaInicial = entrada.at(0);
                columnaInicial = entrada.at(1);
                while(!ingresoCoordFinalEsValida)
                {
                    imprimirPosiblesCoordenadasFinales(filaInicial,columnaInicial,tamanioBarco);
                    cout<<"Ingrese coordenadas numericas finales: ";
                    getline(cin,entrada);
                    coordenadaFinal = entrada;
                    if(coordenadaIngresadaEsValida(coordenadaFinal)&& coordenadaOrtogonalEsValida(coordenadaOrigen,coordenadaFinal,tamanioBarco))
                    {
                        ingresoCoordFinalEsValida = true;
                        ingresoGeneralEsValido = true;
                    }
                    else
                    {
                        cout<<"ERROR!!!"<<endl;
                    }
                }
            }
            else
            {
                cout<<"ERROR!!!"<<endl;
            }
        }
        guardarValores(mapaDelJugador,coordenadaOrigen,coordenadaFinal);
        cantidadBarcosIngresados++;
        Sleep(2000);
        limpiarConsola();
        mostrarIngresoDeTablero(mapaDelJugador);
    }

}

void inicializarTablero(tablero mapaDelJugador)
{
    for(size_t i=0;i<TAM_TABLERO;i++)
    {
        for(size_t j=0;j<TAM_TABLERO;j++)
        {
            mapaDelJugador[i][j] = 'O';
        }
    }
}

bool coordenadaIngresadaEsValida(string coordenadaIngresada)
{
    return (!coordenadaIngresada.empty() && coordenadaIngresada.length()==2
            && coordenadaIngresada.at(0)>=48 && coordenadaIngresada.at(0)<=57
            && coordenadaIngresada.at(1)>=48 && coordenadaIngresada.at(1)<=57);
}

void imprimirPosiblesCoordenadasFinales(char filaInicial,char columnaInicial,int tamanioBarco)
{
   int numFilaInicial = filaInicial-48;
   int numColumnaInicial = columnaInicial-48;
   int numFilaCursor=0;
   int numColumnaCursor=0;
   tamanioBarco--;
   for(size_t i=0;i<4;i++)
   {
       switch (i) {
       case 0:
       {
           numFilaCursor = numFilaInicial+tamanioBarco;//aumento columna, hacia la derecha
           if(!(coordenadaEsNegativa(numFilaCursor))&& numFilaCursor<TAM_TABLERO)
           {
               cout<<"Posible coordenada final: ("<<numFilaCursor<<";"<<numColumnaInicial<<")"<<endl;
           }
           numFilaCursor=0;
       }
           break;
       case 1:
       {
           numColumnaCursor = numColumnaInicial+tamanioBarco;//aumento fila, hacia abajo
           if(!(coordenadaEsNegativa(numColumnaCursor)) && numColumnaCursor<TAM_TABLERO)
           {
               cout<<"Posible coordenada final: ("<<numFilaInicial<<";"<<numColumnaCursor<<")"<<endl;
           }
           numColumnaCursor=0;
       }
           break;
       case 2:
       {
           numFilaCursor = numFilaInicial-tamanioBarco;//reduzco columna, hacia la izquierda
           if(!(coordenadaEsNegativa(numFilaCursor)) && numFilaCursor<TAM_TABLERO)
           {
               cout<<"Posible coordenada final: ("<<numFilaCursor<<';'<<numColumnaInicial<<')'<<endl;
           }
           numFilaCursor=0;
       }
           break;
       case 3:
       {
           numColumnaCursor = numColumnaInicial-tamanioBarco;//reduzco fila, hacia arriba
           if(!(coordenadaEsNegativa(numColumnaCursor))&& numColumnaCursor<TAM_TABLERO)
           {
               cout<<"Posible coordenada final: ("<<numFilaInicial<<";"<<numColumnaCursor<<")"<<endl;
           }
           numColumnaCursor=0;
       }
           break;
       default:
           break;
       }
   }
}

bool coordenadaEsNegativa(int coordenada)
{
    bool condicion = (coordenada<0);
    return condicion;
}

bool coordenadaOrtogonalEsValida(string coordenadaOrigen, string coordenadaFinal,int tamanioBarco )
{
    char filaInicial=coordenadaOrigen.at(0);
    char columnaInicial=coordenadaOrigen.at(1);
    char filaFinal=coordenadaFinal.at(0);
    char columnaFinal=coordenadaFinal.at(1);
    bool coordFinalHorizontalDer = false,coordFinalHorizontalIzq = false;
    bool coordFinalVerticalSup = false,coordFinalVerticalInf = false;
    int numFilaInicial = filaInicial-48;
    int numColumnaInicial = columnaInicial-48;
    int numFilaFinal = filaFinal-48;
    int numColumnaFinal = columnaFinal-48;
    tamanioBarco--;
    //Si las coordenadas son negativas o sobrepasan el tablero
    if((coordenadaEsNegativa(numFilaFinal)||coordenadaEsNegativa(numColumnaFinal)) && (numFilaFinal>TAM_TABLERO || numColumnaFinal>TAM_TABLERO))
    {
        return false;
    }
    //
    coordFinalHorizontalDer = (((numFilaInicial+tamanioBarco)==numFilaFinal) && (numColumnaInicial==numColumnaFinal));
    coordFinalHorizontalIzq = (((numFilaInicial-tamanioBarco)==numFilaFinal) && (numColumnaInicial==numColumnaFinal));
    coordFinalVerticalSup = (((numColumnaInicial+tamanioBarco)==numColumnaFinal) && (numFilaInicial==numFilaFinal));
    coordFinalVerticalInf = (((numColumnaInicial-tamanioBarco)==numColumnaFinal) && (numFilaInicial==numFilaFinal));
    if(coordFinalHorizontalDer || coordFinalHorizontalIzq || coordFinalVerticalInf ||coordFinalVerticalSup)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void guardarValores(tablero mapaDelJugador, string coordenadaOrigen, string coordenadaFinal)
{
    char filaInicial=coordenadaOrigen.at(0);
    char columnaInicial=coordenadaOrigen.at(1);
    char filaFinal=coordenadaFinal.at(0);
    char columnaFinal=coordenadaFinal.at(1);
    int numfilaInicial = filaInicial-48;
    int numColumnaInicial = columnaInicial-48;
    int numfilaFinal = filaFinal-48;
    int numColumnaFinal = columnaFinal-48;
    if(numfilaInicial==numfilaFinal)
    {
        if(numColumnaInicial<numColumnaFinal)//Que el contador sume
        {
            for(int i=numColumnaInicial;i<=numColumnaFinal;i++)
            {
                mapaDelJugador[numfilaInicial][i] = 'X';
            }
        }
        else
        {
            if(numColumnaInicial>numColumnaFinal)
            {
                for(int i=numColumnaInicial;i>=numColumnaFinal;i--)
                {
                    mapaDelJugador[numfilaInicial][i] = 'X';
                }
            }
        }
    }

    if(numColumnaInicial==numColumnaFinal)
    {
        if(numfilaInicial<numfilaFinal)//Que el contador sume
        {
            for(int i=numfilaInicial;i<=numfilaFinal;i++)
            {
                mapaDelJugador[i][numColumnaInicial] = 'X';
            }
        }
        else
        {
            if(numfilaInicial>numfilaFinal)
            {
                for(int i=numfilaInicial;i>=numfilaFinal;i--)
                {
                    mapaDelJugador[i][numColumnaInicial] = 'X';
                }
            }
        }
    }
}

void jugarAlaBatallaNaval(arregloDeString nombresDeJugadores,tablero mapaDelJugadorA,tablero mapaDelJugadorB)
{
    bool ganoJugadorA = false, ganoJugadorB = false;
    size_t contadorTurno=0;
    string coordenadaIngresada;
    cout<<endl;
    cout<<"EMPEZO EL JUEGO!!"<<endl;
    while(!ganoJugadorA && !ganoJugadorB)
    {
            if(contadorTurno==0 && !ganoJugadorB)
            {
                mostrarTablero(mapaDelJugadorB);
                cout<<"Turno de: "<<nombresDeJugadores[0]<<endl;
                coordenadaIngresada = ingresarCoordenada();
                if(coordenadaIngresadaEsValida(coordenadaIngresada))
                {
                    if(golpeoAlBarco(mapaDelJugadorB,coordenadaIngresada))
                    {
                        cout<<"ENHORABUENA"<<endl;
                        modificarTablero(mapaDelJugadorB,coordenadaIngresada);
                    }
                    else
                    {
                        cout<<"Hiciste agua mostro..."<<endl;
                    }
                }

                ganoJugadorB = hundioTodosLosBarcos(mapaDelJugadorB);
                mostrarTablero(mapaDelJugadorB);
                contadorTurno = 1;
                Sleep(3000);
                limpiarConsola();
            }
            if(contadorTurno==1 && !ganoJugadorA)
            {
                mostrarTablero(mapaDelJugadorA);
                cout<<"Turno de: "<<nombresDeJugadores[1]<<endl;
                coordenadaIngresada = ingresarCoordenada();
                if(coordenadaIngresadaEsValida(coordenadaIngresada))
                {
                    if(golpeoAlBarco(mapaDelJugadorA,coordenadaIngresada))
                    {
                        cout<<"ENHORABUENA"<<endl;
                        modificarTablero(mapaDelJugadorA,coordenadaIngresada);
                    }
                    else
                    {
                        cout<<"Hiciste agua mostro..."<<endl;
                    }
                }

                mostrarTablero(mapaDelJugadorA);
                ganoJugadorA = hundioTodosLosBarcos(mapaDelJugadorA);
                contadorTurno = 0;
                Sleep(3000);
                limpiarConsola();
            }


    }
    if(ganoJugadorA)
    {
        cout<<endl;
        cout<<"Jugador: "<<nombresDeJugadores[0]<<" GANASTE!!!"<<endl;
    }
    if(ganoJugadorB)
    {
        cout<<endl;
        cout<<"Jugador: "<<nombresDeJugadores[1]<<" GANASTE!!!"<<endl;
    }
}

string ingresarCoordenada()
{
    string coordenadaIngresada;
    bool ingresoEsValido = false;
    while(!ingresoEsValido)
    {
        cout<<"INGRESE COORDENADA: ";
        getline(cin,coordenadaIngresada);
        if(coordenadaIngresadaEsValida(coordenadaIngresada))
        {
            ingresoEsValido = true;
        }
        else
        {
            cout<<"ERROR!!!"<<endl;
        }
    }
    return coordenadaIngresada;
}

void mostrarTablero(tablero mapaDelJugador)
{
    cout<<endl;
    imprimirEncabezadoSuperior();
    for(size_t i=0;i<TAM_TABLERO;i++)
    {
        cout<<i<<'|'<<' ';
        for(size_t j=0;j<TAM_TABLERO;j++)
        {
            if(mapaDelJugador[i][j]=='O' || mapaDelJugador[i][j]=='X')
            {
               cout<<'O'<<' ';
            }
            else
            {
                cout<<'+'<<' ';
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

bool golpeoAlBarco(tablero mapaDelJugador,string coordenadaIngresada)
{
    int numeroFila = coordenadaIngresada.at(0)-48;
    int numeroColumna = coordenadaIngresada.at(1)-48;
    if(mapaDelJugador[numeroColumna][numeroFila] == 'X')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void modificarTablero(tablero mapaDelJugador,string coordenadaIngresada)
{
    int numeroFila = coordenadaIngresada.at(0)-48;
    int numeroColumna = coordenadaIngresada.at(1)-48;
    mapaDelJugador[numeroColumna][numeroFila] = '+';
}

bool hundioTodosLosBarcos(tablero mapaDelJugador)
{
    for(size_t i=0;i<TAM_TABLERO;i++)
    {
        for(size_t j=0;j<TAM_TABLERO;j++)
        {
            if(mapaDelJugador[i][j]=='X')
            {
                return false;
            }
        }
    }
    return true;
}

void imprimirEncabezadoSuperior()
{
    cout<<"TABLERO"<<endl;
    cout<<"   0 1 2 3 4 5 6 7 8 9"<<endl;
    cout<<"   _ _ _ _ _ _ _ _ _ _"<<endl;
}

void mostrarIngresoDeTablero(tablero mapaDelJugador)
{
    cout<<endl;
    imprimirEncabezadoSuperior();
    for (size_t i=0;i<TAM_TABLERO;i++)
    {
        cout<<i<<'|'<<' ';
        for(size_t j=0;j<TAM_TABLERO;j++)
        {
            if(mapaDelJugador[i][j]=='O')
            {
                cout<<'O'<<' ';
            }
            if(mapaDelJugador[i][j]=='X')
            {
                cout<<'X'<<' ';
            }
        }
        cout<<endl;
    }
    cout<<endl;
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
    cout<<" \t \t B B B  I EEEEE NN    N V       V EEEEE NN    N I DDDD   OOOO          A         L         A     "<<endl;
    cout<<" \t \t B    B I E     N N   N  V     V  E     N N   N I D   D O    O        A A        L        A A     "<<endl;
    cout<<" \t \t B B B  I EEEEE N  N  N   V   V   EEEEE N  N  N I D   D O    O       A   A       L       A   A     "<<endl;
    cout<<" \t \t B    B I E     N   N N    V V    E     N   N N I D   D O    O      AAAAAAA      L      AAAAAAA   "<<endl;
    cout<<" \t \t B B B  I EEEEE N    NN     V     EEEEE N    NN I DDDD   OOOO      A       A     LLLLL A       A  "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" \t \t BBBB      A    TTTTT    A     L     L         A        NN    N     A   V       V  A     L         "<<endl;
    cout<<" \t \t B   B    A A     T     A A    L     L        A A       N N   N    A A   V     V  A A    L         "<<endl;
    cout<<" \t \t BBBB    A   A    T    A   A   L     L       A   A      N  N  N   A   A   V   V  A   A   L         "<<endl;
    cout<<" \t \t B   B  AAAAAAA   T   AAAAAAA  L     L      AAAAAAA     N   N N  AAAAAAA   V V  AAAAAAA  L         "<<endl;
    cout<<" \t \t BBBB  A       A  T  A       A LLLLL LLLLL A       A    N    NN A       A   V  A       A LLLLL     "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
}
