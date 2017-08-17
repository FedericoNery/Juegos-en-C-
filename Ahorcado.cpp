#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;
const size_t TAM_JUGADORES = 2;
typedef string arregloDeString[TAM_JUGADORES];

void ingresarNombresDeJugadores(arregloDeString);
void ingresarPalabras(arregloDeString,arregloDeString);
char ingreseLetra();
void jugarAlAhorcado(arregloDeString,arregloDeString);
bool buscarLetraEnPalabra(arregloDeString, unsigned int, char);
void mostrarHorca(size_t);

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
    AjustarVentana(100,40);
    cambiarColorDeFondoYLetras("color 9A");
    mensajeDeBienvenida();
    Sleep(3000);
    limpiarConsola();
    arregloDeString nombresDeJugadores;
    arregloDeString palabrasDeLosJugadores;
    ingresarNombresDeJugadores(nombresDeJugadores);
    limpiarConsola();
    ingresarPalabras(nombresDeJugadores,palabrasDeLosJugadores);//palabra 0 para el jugador 1 y la palabra 1 para el jugador 0
    limpiarConsola();
    jugarAlAhorcado(nombresDeJugadores,palabrasDeLosJugadores);
}

void mostrarHorca(size_t contOportunidades)
{
    switch(contOportunidades)
    {
    case 0:
    {
        cout<<"         #########################        "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                     *****          "<<endl;
        cout<<"         #                    *     *      "<<endl;
        cout<<"         #                    *     *     "<<endl;
        cout<<"         #                     *****      "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                     * * *        "<<endl;
        cout<<"         #                  ***  *  ***      "<<endl;
        cout<<"         #                  *    *    *      "<<endl;
        cout<<"         #                  *    *    *      "<<endl;
        cout<<"         #                      * *        "<<endl;
        cout<<"         #                     *   *     "<<endl;
        cout<<"         #                    *     *    "<<endl;
        cout<<"         #                 ***       *** "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"################### "<<endl;
        cout<<"                                           "<<endl;
        cout<<"  *****      *      **    ** *****     ***  *         * ****** ****           "<<endl;
        cout<<" *          * *     *  * * * *        *   *  *       *  *      *   *    "<<endl;
        cout<<" *         *   *    *   *  * *        *   *   *     *   *      *   *    "<<endl;
        cout<<" * ****   *     *   *      * *****    *   *    *   *    *****  ****           "<<endl;
        cout<<" *    *  * ***** *  *      * *        *   *     * *     *      *   *    "<<endl;
        cout<<"  ****  *         * *      * *****     ***       *      ****** *    *        "<<endl;

    }break;
    case 1:
    {
        cout<<"         #########################        "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                     *****          "<<endl;
        cout<<"         #                    *     *      "<<endl;
        cout<<"         #                    *     *     "<<endl;
        cout<<"         #                     *****      "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                     * * *        "<<endl;
        cout<<"         #                  ***  *  ***      "<<endl;
        cout<<"         #                  *    *    *      "<<endl;
        cout<<"         #                  *    *    *      "<<endl;
        cout<<"         #                        *        "<<endl;
        cout<<"         #                         *     "<<endl;
        cout<<"         #                          *    "<<endl;
        cout<<"         #                           *** "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"################### "<<endl;
    }break;
    case 2:
    {
        cout<<"         #########################        "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                     *****          "<<endl;
        cout<<"         #                    *     *      "<<endl;
        cout<<"         #                    *     *     "<<endl;
        cout<<"         #                     *****      "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                     * * *        "<<endl;
        cout<<"         #                  ***  *  ***      "<<endl;
        cout<<"         #                  *    *    *      "<<endl;
        cout<<"         #                  *    *    *      "<<endl;
        cout<<"         #                               "<<endl;
        cout<<"         #                        "<<endl;
        cout<<"         #                        "<<endl;
        cout<<"         #                  "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"################### "<<endl;
    }break;
    case 3:
    {
        cout<<"         #########################        "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                     *****          "<<endl;
        cout<<"         #                    *     *      "<<endl;
        cout<<"         #                    *     *     "<<endl;
        cout<<"         #                     *****      "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                     *   *        "<<endl;
        cout<<"         #                  ***     ***      "<<endl;
        cout<<"         #                  *         *      "<<endl;
        cout<<"         #                  *         *      "<<endl;
        cout<<"         #                              "<<endl;
        cout<<"         #                     "<<endl;
        cout<<"         #                    "<<endl;
        cout<<"         #                  "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"################### "<<endl;
    }break;
    case 4:
    {
        cout<<"         #########################        "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                     *****          "<<endl;
        cout<<"         #                    *     *      "<<endl;
        cout<<"         #                    *     *     "<<endl;
        cout<<"         #                     *****      "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                         *        "<<endl;
        cout<<"         #                          ***      "<<endl;
        cout<<"         #                            *      "<<endl;
        cout<<"         #                            *      "<<endl;
        cout<<"         #                             "<<endl;
        cout<<"         #                       "<<endl;
        cout<<"         #                    "<<endl;
        cout<<"         #                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"################### "<<endl;
    }break;
    case 5:
    {
        cout<<"         #########################        "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                     *****          "<<endl;
        cout<<"         #                    *     *      "<<endl;
        cout<<"         #                    *     *     "<<endl;
        cout<<"         #                     *****      "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                       *          "<<endl;
        cout<<"         #                            "<<endl;
        cout<<"         #                    "<<endl;
        cout<<"         #                    "<<endl;
        cout<<"         #                    "<<endl;
        cout<<"         #                           "<<endl;
        cout<<"         #                        "<<endl;
        cout<<"         #                       "<<endl;
        cout<<"         #                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"################### "<<endl;
    }break;
    case 6:
    {
        cout<<"         #########################        "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                     *****          "<<endl;
        cout<<"         #                    *     *      "<<endl;
        cout<<"         #                    *     *     "<<endl;
        cout<<"         #                     *****      "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                          "<<endl;
        cout<<"         #                       "<<endl;
        cout<<"         #                       "<<endl;
        cout<<"         #                    "<<endl;
        cout<<"         #                             "<<endl;
        cout<<"         #                          "<<endl;
        cout<<"         #                      "<<endl;
        cout<<"         #                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"################### "<<endl;
    }break;
    case 7:
    {
        cout<<"         #########################         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                       #         "<<endl;
        cout<<"         #                              "<<endl;
        cout<<"         #                       "<<endl;
        cout<<"         #                        "<<endl;
        cout<<"         #                          "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"         #                                 "<<endl;
        cout<<"###################"<<endl;
    }break;
    }
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

void ingresarPalabras(arregloDeString nombresDeJugadores, arregloDeString palabrasDeLosJugadores)
{
    string entrada;
    size_t contador = 0;
    bool ingresoEsValido = false;

    while(contador<2)
    {
        while(!ingresoEsValido)
        {
            cout<<"Jugador: "<<nombresDeJugadores[contador]<<" "<<"Ingrese una palabra: ";
            getline(cin,entrada);
            cout<<endl;
            limpiarConsola();
            if(!entrada.empty())
            {
                ingresoEsValido = true;
            }
        }
        palabrasDeLosJugadores[contador] = entrada;
        ingresoEsValido = false;
        contador++;
    }
}

void jugarAlAhorcado(arregloDeString nombresDeJugadores, arregloDeString palabrasDeLosJugadores)
{
    bool jugadorADescubrioPalabra = false, jugadorBDescubrioPalabra = false;
    bool existeLetraEnPalabra = false;
    bool ganoJugadorA = false,ganoJugadorB = false;
    size_t contTurno = 0, contOportunidadesA = 7, contOportunidadesB = 7;
    char letra;
    string mostrarPalabraA ="";
    string mostrarPalabraB ="";
    for(int j=0;j<palabrasDeLosJugadores[1].length();j++)
    {
        mostrarPalabraA = mostrarPalabraA + '-';
    }
    for(int j=0;j<palabrasDeLosJugadores[0].length();j++)
    {
        mostrarPalabraB = mostrarPalabraB + '-';
    }

    while(!jugadorADescubrioPalabra && !jugadorBDescubrioPalabra && contOportunidadesA>0 && contOportunidadesB>0)
    {

        if(contTurno==0)
        {
            cout<<"JUEGA "<<nombresDeJugadores[contTurno]<<endl;
            mostrarHorca(contOportunidadesA);
            cout<<"Palabra 1:"<<mostrarPalabraA<<endl;
            letra = ingreseLetra();
            existeLetraEnPalabra = buscarLetraEnPalabra(palabrasDeLosJugadores,contTurno,letra);
            if(existeLetraEnPalabra)
            {
                for(int i=0;i<palabrasDeLosJugadores[1].length();i++)
                {
                    if(letra == palabrasDeLosJugadores[1].at(i))
                    {
                        mostrarPalabraA.at(i) = palabrasDeLosJugadores[1].at(i);
                    }
                }
            }
            else
            {
                contOportunidadesA--;
                //mostrarHorca(contOportunidadesA);
            }
            cout<<"Al jugador: "<<nombresDeJugadores[contTurno]<<" le quedan "<<contOportunidadesA<<" oportunidades "<<endl;
            cout<<"La palabra queda: "<<mostrarPalabraA<<endl;
            cout<<endl;
            jugadorADescubrioPalabra = (palabrasDeLosJugadores[1]==mostrarPalabraA);
            Sleep(3000);
            limpiarConsola();
        }
        if(contTurno==1)
        {
            cout<<"JUEGA "<<nombresDeJugadores[contTurno]<<endl;
            mostrarHorca(contOportunidadesB);
            cout<<"Palabra 2:"<<mostrarPalabraB<<endl;
            letra = ingreseLetra();
            existeLetraEnPalabra = buscarLetraEnPalabra(palabrasDeLosJugadores,contTurno,letra);
            if(existeLetraEnPalabra)
            {
                for(int i=0;i<palabrasDeLosJugadores[0].length();i++)
                {
                    if(letra == palabrasDeLosJugadores[0].at(i))
                    {
                        mostrarPalabraB.at(i) = palabrasDeLosJugadores[0].at(i);
                    }
                }
            }
            else
            {
                contOportunidadesB--;
                //mostrarHorca(contOportunidadesB);
            }
            cout<<"Al jugador: "<<nombresDeJugadores[contTurno]<<" le quedan "<<contOportunidadesB<<" oportunidades "<<endl;
            cout<<"La palabra queda: "<<mostrarPalabraB<<endl;
            cout<<endl;
            jugadorBDescubrioPalabra = (palabrasDeLosJugadores[0]==mostrarPalabraB);
            Sleep(3000);
            limpiarConsola();
        }
        contTurno++;
        if(contTurno==2)
        {
            contTurno = 0;
        }
    }
    if(jugadorADescubrioPalabra || contOportunidadesB==0)
    {
        cout<<"GANASTE "<<nombresDeJugadores[0]<<endl;
    }
    if(jugadorBDescubrioPalabra || contOportunidadesA==0)
    {
        cout<<"GANASTE "<<nombresDeJugadores[1]<<endl;
    }
}

char ingreseLetra()
{
    bool ingresoEsValido = false;
    string entrada;
    while(!ingresoEsValido)
    {
        cout<<"Ingrese letra: ";
        getline(cin,entrada);
        if(!entrada.empty() && entrada.length()==1)
        {
            ingresoEsValido = true;
        }
        else
        {
            cout<<"ERROR!!"<<endl;
        }
    }
    return entrada.at(0);
}

bool buscarLetraEnPalabra(arregloDeString palabraDeLosJugadores, unsigned int contTurno, char letra)
{
    if(contTurno==0)
    {
        contTurno = 1;
    }
    else
    {
        contTurno = 0;
    }
    for(size_t i=0;i<palabraDeLosJugadores[contTurno].length();i++)
    {
        if(letra == palabraDeLosJugadores[contTurno].at(i) )
        {
            return true;
        }
    }
    return false;
}

bool ganoElAhorcado(string palabra)
{
    for(size_t i=0;i<palabra.length();i++)
    return true;
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
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" \t  BBBBB  I EEEEE NN    N V       V EEEEE NN    N I DDDD   OOOO          A     L      "<<endl;
    cout<<" \t  B    B I E     N N   N  V     V  E     N N   N I D   D O    O        A A    L      "<<endl;
    cout<<" \t  BBBBB  I EEEEE N  N  N   V   V   EEEEE N  N  N I D   D O    O       A   A   L      "<<endl;
    cout<<" \t  B    B I E     N   N N    V V    E     N   N N I D   D O    O      AAAAAAA  L      "<<endl;
    cout<<" \t  BBBBB  I EEEEE N    NN     V     EEEEE N    NN I DDDD   OOOO      A       A LLLLL  "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" \t \t     A     H    H  OOOO  RRRRR   CCCC     A     DDDD   OOOO     "<<endl;
    cout<<" \t \t    A A    H    H O    O R    R C        A A    D   D O    O    "<<endl;
    cout<<" \t \t   A   A   HHHHHH O    O RRRRR  C       A   A   D   D O    O    "<<endl;
    cout<<" \t \t  AAAAAAA  H    H O    O R  R   C      AAAAAAA  D   D O    O    "<<endl;
    cout<<" \t \t A       A H    H  OOOO  R   R   CCCC A       A DDDD   OOOO     "<<endl;
    cout<<endl;
    cout<<endl;
}

