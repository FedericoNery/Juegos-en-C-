#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <strings.h>
#include <sstream>
#include <windows.h>

using namespace std;

const size_t TAM_CAMPO = 50;
typedef char arregloDeChar[TAM_CAMPO][TAM_CAMPO];

const size_t TAM_MAX_MINAS = 25;
typedef string arregloDeString[TAM_MAX_MINAS];

//FUNCIONES DE INICIALIZACION
void inicializarCampo(arregloDeChar,int);
void inicializarCoordenadasConMinas(arregloDeString,int);
void colocarMinasEnElCampo(arregloDeChar,int,int,arregloDeString);

//FUNCIONES DE INGRESO
int ingresarNumero();
string ingresarCoordenadas(int);
int ingresarNumFilaColumna();

//FUNCIONES DE IMPRESION
void mostrarMinasAlrededorDeLaCoordenada(string,arregloDeChar,int);
void mostrarElCampo(arregloDeChar);
void imprimirEncabezado(int);
void imprimirCampo(arregloDeChar,int);
void mostrarElCampo(arregloDeChar, int);

//FUNCIONES LOGICAS
bool coordenadaIngresadaEsUnaBomba(arregloDeChar,string,arregloDeString);
bool verificarSiQuedaronSoloLasBombas(arregloDeChar,int,int);
bool noSeRepiteCoordenadaDeMina(arregloDeString,string,int);
bool sonIgualesLosStrings(string,string);
bool coordenadaEstaDentroDelCampo(int,int,int);

//FUNCIONES AUXILIARES(CONVERSION,EXTRACCION)
char valorFinalDeCasilla(int);
string convertirCoordAString(int, int);
int extraerFila(string);
int extraerColumna(string);

//FUNCION PARA MODIFICAR
void establecerNumerosAlrededorDeLasMinas(arregloDeChar,int,arregloDeString);
void copiarCampos(arregloDeChar,arregloDeChar,int);

//FUNCION DE JUEGO
void jugarAlBuscaminas(arregloDeChar,int,arregloDeString,arregloDeChar,int);

//FUNCIONES PARA MODIFICAR LA CONSOLA
void mensajeDeBienvenida();
void AjustarVentana(int, int);
void cambiarColorDeFondoYLetras(string);
void limpiarConsola();
void colocarNombreALaVentana(string);
void expandirCeros(int,int, arregloDeChar, arregloDeChar);


int main()
{
    arregloDeChar campo,campoParaImpresion;
    arregloDeString listaCoordDeMinas;
    int cantidadDeMinas = 0,tamanioCampo = 0;

    //Inicializacion
    colocarNombreALaVentana("BUSCAMINAS");
    AjustarVentana(150,40);
    cambiarColorDeFondoYLetras("color 6A");
    mensajeDeBienvenida();

    Sleep(2000);
    limpiarConsola();
    //PARAMETROS INICIALES
    cout<<"Ingrese la cantidad de minas: ";
    cantidadDeMinas = ingresarNumero();
    cout<<"Ingrese el tamanio del campo: ";
    tamanioCampo = ingresarNumero();
    inicializarCampo(campo,tamanioCampo);
    inicializarCoordenadasConMinas(listaCoordDeMinas,tamanioCampo);
    colocarMinasEnElCampo(campo,cantidadDeMinas,tamanioCampo,listaCoordDeMinas);

    imprimirCampo(campo,tamanioCampo);
    copiarCampos(campo,campoParaImpresion,tamanioCampo);

    cout<<endl;
    for(int a=0;a<cantidadDeMinas;a++)
    {
        cout<<listaCoordDeMinas[a]<<endl;
    }
    //campoParaImpresion = campo;
    //mostrarElCampo(campoParaImpresion,tamanioCampo);

    establecerNumerosAlrededorDeLasMinas(campoParaImpresion,tamanioCampo,listaCoordDeMinas);
    inicializarCampo(campo,tamanioCampo);
    //ocultarMinas(campo,tamanioCampo);
    //mostrarElCampo(campo,tamanioCampo);
    limpiarConsola();
    //JUGAR
    jugarAlBuscaminas(campo,tamanioCampo,listaCoordDeMinas,campoParaImpresion,cantidadDeMinas);
}

void copiarCampos(arregloDeChar campo,arregloDeChar campoParaImpresion,int tamanioCampo)
{
    for(int i=0;i<tamanioCampo;i++)
    {
        for(int j=0;j<tamanioCampo;j++)
        {
            campoParaImpresion[i][j] = campo[i][j];
        }
    }
}

string convertirCoordAString(int fila, int columna)
{
    string coordenada,filaConvertida,columnaConvertida;//string which will contain the result
    stringstream convert; // stringstream used for the conversio
    convert << fila;//add the value of Number to the characters in the stream
    filaConvertida = convert.str();//set Result to the content of the stream
    convert.str("");

    convert<<columna;
    columnaConvertida = convert.str();
    convert.str("");

    coordenada = filaConvertida + '-' + columnaConvertida;

    return coordenada;
}

char valorFinalDeCasilla(int valorCasilla)
{
    char caracter;
    if(valorCasilla>=1)
    {
        caracter = valorCasilla+48;
    }
    if(valorCasilla==0)
    {
        caracter = 176;
    }
    return caracter;
}

void establecerNumerosAlrededorDeLasMinas(arregloDeChar campoParaImpresion,int tamanioCampo,arregloDeString listaDeBombas)
{
    int valorCasilla = 0;
    char caracter;
    char caracterBomba=169;
    string coordenadaGenerada="";
    int numeroFilaAlrededor,numeroColumnaAlrededor,numeroFila,numeroColumna;
    for(int j=0;j<tamanioCampo;j++)
    {
        for(int k=0;k<tamanioCampo;k++)
        {
            numeroFila = j;
            numeroColumna = k;
            caracter=campoParaImpresion[j][k];
            if(caracter!=caracterBomba)
            {
                for(size_t i=1;i<9;i++)
                {

                    switch (i) {
                    /*
                        1 2 3
                        4 C 5
                        6 7 8
                    */
                    case 1:
                        numeroFilaAlrededor = numeroFila - 1;
                        numeroColumnaAlrededor = numeroColumna -1;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                        //cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;//
                    case 2:
                        numeroFilaAlrededor = numeroFila - 1;
                        numeroColumnaAlrededor = numeroColumna;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                        //cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;
                        /*
                            1 2 3
                            4 C 5
                            6 7 8
                        */
                    case 3:
                        numeroFilaAlrededor = numeroFila - 1;
                        numeroColumnaAlrededor = numeroColumna +1;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                        //cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;
                    case 4:
                        numeroFilaAlrededor = numeroFila;
                        numeroColumnaAlrededor = numeroColumna -1;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                        //cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;
                        /*
                            1 2 3
                            4 C 5
                            6 7 8
                        */
                    case 5:
                        numeroFilaAlrededor = numeroFila;
                        numeroColumnaAlrededor = numeroColumna +1;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                       //cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;
                    case 6:
                        numeroFilaAlrededor = numeroFila + 1;
                        numeroColumnaAlrededor = numeroColumna -1;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                       // cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;
                        /*
                            1 2 3
                            4 C 5
                            6 7 8
                        */
                    case 7:
                        numeroFilaAlrededor = numeroFila + 1;
                        numeroColumnaAlrededor = numeroColumna;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                       // cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;
                    case 8:
                        numeroFilaAlrededor = numeroFila + 1;
                        numeroColumnaAlrededor = numeroColumna +1;
                        coordenadaGenerada = convertirCoordAString(numeroFilaAlrededor,numeroColumnaAlrededor);
                       // cout<<i<<':'<<coordenadaGenerada<<endl;
                        if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor)
                                && coordenadaIngresadaEsUnaBomba(campoParaImpresion,coordenadaGenerada,listaDeBombas))
                        {
                           valorCasilla++;
                        }
                        break;
                    default:
                        break;
                    }
                }
                caracter = valorFinalDeCasilla(valorCasilla);
                campoParaImpresion[j][k] = caracter;
                valorCasilla=0;
            }
                //mostrarElCampo(campoParaImpresion,tamanioCampo);
        }
    }

}

void inicializarCoordenadasConMinas(arregloDeString coordenadasConMinas,int tamanioCampo)
{
    for(int i=0;i<tamanioCampo;i++)
    {
        coordenadasConMinas[i]="";
    }
}

void imprimirCampo(arregloDeChar campo,int tamanioDeCampo)
{
    char caracterSinBomba=254,caracterDeBomba=169;
    imprimirEncabezado(tamanioDeCampo);
    for (int i=0;i<tamanioDeCampo;i++)
    {
        for(int j=0;j<tamanioDeCampo;j++)
        {
            if(j==0)
            {
                if(tamanioDeCampo>10 && i<10)
                {
                    cout<<' '<<i<<' ';
                }
                if(tamanioDeCampo>10 && i>=10)
                {
                    cout<<i<<' ';
                }
                if(tamanioDeCampo<=10)
                {
                    cout<<' '<<i<<' ';
                }
            }
            if(campo[i][j]==caracterDeBomba)
            {
                //caracter=169;
                if(j<10)
                {
                    cout<<caracterDeBomba<<' ';
                }
                if(j>=10)
                {
                    cout<<' '<<caracterDeBomba<<' ';
                }
            }
            else
            {
                if(campo[i][j]==caracterSinBomba)
                {
                  //  caracter=254;
                    cout<<caracterSinBomba<<' ';
                }
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

void imprimirEncabezado(int tamanioCampo)
{
    cout<<"   ";
    for(int i=0;i<tamanioCampo;i++)
    {
        if(i<10)
        {
            cout<<' '<<i<<' ';
        }
        if(i>=10)
        {
            cout<<i<<' ';
        }

    }
    cout<<endl;
}

int ingresarNumero()
{
    string entrada;
    int numero = 0;
    while(numero<=0)
    {
        getline(cin,entrada);
        if(entrada.length()==1)
        {
            numero = entrada.at(0)-48;
        }
        else
        {
            numero = atoi(entrada.c_str());
        }

        if(numero<=0)
        {
            cout<<"ERROR!!!"<<endl;
        }
    }
    return numero;
}

int ingresarNumFilaColumna()
{
    string entrada;
    bool ingresoEsValido = false;
    int numero = 0;
    while(!ingresoEsValido)
    {
        getline(cin,entrada);
        if(entrada.length()==1)
        {
            numero = entrada.at(0)-48;
            if(entrada.at(0)!='0' && numero==0)
            {
                cout<<"ERROR!!! Reingrese el valor"<<endl;
            }
            else
            {
                ingresoEsValido = true;
            }
        }
        else
        {
            numero = atoi(entrada.c_str());
            if(entrada!="0" && numero==0)
            {
                cout<<"ERROR!!! Reingrese el valor"<<endl;
            }
            else
            {
                ingresoEsValido = true;
            }
        }
    }
    return numero;
}

void colocarMinasEnElCampo(arregloDeChar campo,int cantidadDeMinas,int tamanioCampo,arregloDeString coordenadasConMinas)
{
    string filaConMina,columnaConMina;
    int contador = 0;
    int aleatorioFila = 0;
    int aleatorioColumna = 0;
    char caracterBomba=169;
    string coordenadaConMina="";//string which will contain the result
    stringstream convert; // stringstream used for the conversion

    /* initialize random seed: */
      srand (time(NULL));

    while(contador<cantidadDeMinas)
    {
        aleatorioFila = rand() % tamanioCampo;
        convert << aleatorioFila;//add the value of Number to the characters in the stream
        filaConMina = convert.str();//set Result to the content of the stream

        convert.str("");
        //coordenadaConMina = coordenadaConMina + filaConMina + '-';

        aleatorioColumna = rand() % tamanioCampo;
        convert << aleatorioColumna;//add the value of Number to the characters in the stream
        columnaConMina = convert.str();//set Result to the content of the stream

        convert.str("");

        coordenadaConMina = filaConMina +'-'+ columnaConMina;
        if(noSeRepiteCoordenadaDeMina(coordenadasConMinas,coordenadaConMina,tamanioCampo))
        {
            coordenadasConMinas[contador] = coordenadaConMina;
            campo[aleatorioFila][aleatorioColumna] = caracterBomba;
            coordenadaConMina="";
            contador++;
        }
        convert.str("");
        coordenadaConMina="";
    }
}

bool noSeRepiteCoordenadaDeMina(arregloDeString coordenadasConMinas, string coordenadaConMina,int tamanioDeCampo)
{
    string comparacion;
    for(int i=0;i<tamanioDeCampo;i++)
    {
        for(int j=0;j<tamanioDeCampo;j++)
        {
            comparacion = coordenadasConMinas[i][j];
            if(sonIgualesLosStrings(comparacion,coordenadaConMina))
            {
                return false;
            }
        }
    }
    return true;
}

bool sonIgualesLosStrings(string coordenadaConMina,string coordenadaIngresada)
{
    if((coordenadaConMina.length())!=(coordenadaIngresada.length()))
    {
        return false;
    }
    else
    {
        for(int i=0;i<coordenadaConMina.length();i++)
        {
            if(coordenadaConMina.at(i)!=coordenadaIngresada.at(i))
            {
                return false;
            }
        }
    }
    return true;
}

void mostrarMinasAlrededorDeLaCoordenada(string coordenada, arregloDeChar campo,int tamanioCampo)
{
    int numeroFila = (coordenada.at(0)+48);
    int numeroColumna = (coordenada.at(0)+48);
    int numeroFilaAlrededor = 0;
    int numeroColumnaAlrededor = 0;
    for(size_t i=1;i<9;i++)
    {
        switch (i) {
        /*
            1 2 3
            4 C 5
            6 7 8
        */
        case 1:
            numeroFilaAlrededor = numeroFila - 1;
            numeroColumnaAlrededor = numeroColumna -1;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;//
        case 2:
            numeroFilaAlrededor = numeroFila - 1;
            numeroColumnaAlrededor = numeroColumna;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;
            /*
                1 2 3
                4 C 5
                6 7 8
            */
        case 3:
            numeroFilaAlrededor = numeroFila - 1;
            numeroColumnaAlrededor = numeroColumna +1;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;
        case 4:
            numeroFilaAlrededor = numeroFila;
            numeroColumnaAlrededor = numeroColumna -1;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;
            /*
                1 2 3
                4 C 5
                6 7 8
            */
        case 5:
            numeroFilaAlrededor = numeroFila;
            numeroColumnaAlrededor = numeroColumna +1;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;
        case 6:
            numeroFilaAlrededor = numeroFila + 1;
            numeroColumnaAlrededor = numeroColumna -1;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;
            /*
                1 2 3
                4 C 5
                6 7 8
            */
        case 7:
            numeroFilaAlrededor = numeroFila + 1;
            numeroColumnaAlrededor = numeroColumna;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;
        case 8:
            numeroFilaAlrededor = numeroFila + 1;
            numeroColumnaAlrededor = numeroColumna +1;
            if(coordenadaEstaDentroDelCampo(tamanioCampo,numeroFilaAlrededor,numeroColumnaAlrededor))
            {

            }
            break;
        default:
            break;
        }
    }
}

void inicializarCampo(arregloDeChar campo,int tamanioCampo)
{
    char caracterSinBomba = 254;
    for(int i=0;i<tamanioCampo;i++)
    {
        for(int j=0;j<tamanioCampo;j++)
        {
            campo[i][j] = caracterSinBomba;
        }
    }
}

void jugarAlBuscaminas(arregloDeChar campo,int tamanioCampo,arregloDeString listaDeBombas,arregloDeChar campoParaImpresion,int cantidadDeMinas)
{
    bool explotoBomba = false,quedaronSoloLasBombas = false;
    char caracterSinBombaA= 254;
    char caracterSinBombaB= 176;
    //arregloDeChar campoParaImpresion;
    //campoParaImpresion = campo;
    string coordenadaIngresada="";
    int filaIngresada=0;
    int columnaIngresada=0;
    mostrarElCampo(campo,tamanioCampo);
    while(!explotoBomba && !quedaronSoloLasBombas)
    {
        coordenadaIngresada = ingresarCoordenadas(tamanioCampo);
        filaIngresada = extraerFila(coordenadaIngresada);
        columnaIngresada = extraerColumna(coordenadaIngresada);
        explotoBomba = coordenadaIngresadaEsUnaBomba(campo,coordenadaIngresada,listaDeBombas);
        quedaronSoloLasBombas = verificarSiQuedaronSoloLasBombas(campo,cantidadDeMinas,tamanioCampo);
        campo[filaIngresada][columnaIngresada]=campoParaImpresion[filaIngresada][columnaIngresada];

        Sleep(1000);
        limpiarConsola();
        mostrarElCampo(campo,tamanioCampo);
        coordenadaIngresada="";
    }
    if(explotoBomba)
    {
        cout<<endl;
        cout<<"PERDISTE MANCOOOOO"<<endl;
    }
    if(quedaronSoloLasBombas && !explotoBomba)
    {
        cout<<endl;
        cout<<"LA ROMPISTE TODA. SOS UN DISTINTO"<<endl;
    }
}

void mostrarElCampo(arregloDeChar campo, int tamanioDeCampo)
{
    imprimirEncabezado(tamanioDeCampo);
    for (int i=0;i<tamanioDeCampo;i++)
    {
        for(int j=0;j<tamanioDeCampo;j++)
        {
            if(j==0)
            {
                if(tamanioDeCampo>10 && i<10)
                {
                    cout<<' '<<i<<' ';
                }
                if(tamanioDeCampo>10 && i>=10)
                {
                    cout<<i<<' ';
                }
                if(tamanioDeCampo<=10)
                {
                    cout<<' '<<i<<' ';
                }
            }

            if(j<10)
            {
                cout<<' '<<campo[i][j]<<' ';
            }
            if(j>=10)
            {
                cout<<' '<<campo[i][j]<<' ';
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

string ingresarCoordenadas(int tamanioCampo)
{
    int posFilaIngresada=0,posColumIngresada=0;
    bool ingresoEsValido = false;
    string coordenadaIngresada="",stringFila="",stringColumna="";
    stringstream convert; // stringstream used for the conversion

    while(!ingresoEsValido)
    {
       cout<<"Ingrese posicion de Fila: ";
       posFilaIngresada = ingresarNumFilaColumna();
       cout<<"Ingrese posicion de Columna: ";
       posColumIngresada = ingresarNumFilaColumna();
       if(posFilaIngresada<tamanioCampo && posColumIngresada<tamanioCampo)
       {

           convert << posFilaIngresada;//add the value of Number to the characters in the stream
           stringFila = convert.str();//set Result to the content of the stream
           convert.str("");

           convert << posColumIngresada;
           stringColumna = convert.str();
           convert.str("");

           coordenadaIngresada = stringFila + '-' + stringColumna;
           ingresoEsValido=true;
       }
       else
       {
           cout<<"ERROR!!!";
       }
    }
    return coordenadaIngresada;
}

bool coordenadaIngresadaEsUnaBomba(arregloDeChar campo,string coordenadaIngresada,arregloDeString listaDeBombas)
{

    for(size_t i=0;i<TAM_MAX_MINAS;i++)
    {
        if(sonIgualesLosStrings(coordenadaIngresada,listaDeBombas[i]))
        {
            return true;
        }
    }
    return false;

}

bool coordenadaEstaDentroDelCampo(int tamanioCampo,int numeroFila,int numeroColumna)
{
    bool condicion = false;
    condicion = (numeroFila<tamanioCampo && numeroFila>=0 && numeroColumna>=0 && numeroColumna<tamanioCampo);
    return condicion;
}

bool verificarSiQuedaronSoloLasBombas(arregloDeChar campo,int cantidadDeMinas,int tamanioCampo)
{
    char caracterSinBomba = 254,caracter;
    int contadorDeBombas=0;
    for(int i=0;i<tamanioCampo;i++)
    {
        for(int j=0;j<tamanioCampo;j++)
        {
            caracter = campo[i][j];
            if(caracter == caracterSinBomba)
            {
                contadorDeBombas++;
            }

        }
    }
    if(contadorDeBombas==cantidadDeMinas)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int extraerFila(string coordenadaIngresada)
{
    string filaIngresada;
    int cont=0;
    int filaNumero;//number which will contain the result
    while(coordenadaIngresada.at(cont)!='-')
    {
        filaIngresada = filaIngresada+coordenadaIngresada.at(cont);
        cont++;
    }
    stringstream convert(filaIngresada); // stringstream used for the conversion initialized with the contents of Text
    convert>>filaNumero;
    return filaNumero;
}

int extraerColumna(string coordenadaIngresada)
{
    string columnaIngresada;
    int cont=0;
    int columnaNumero;//number which will contain the result
    while(coordenadaIngresada.at(cont)!='-')
    {
        cont++;
    }
    cont++;
    while(cont<coordenadaIngresada.length())
    {
       columnaIngresada = columnaIngresada+coordenadaIngresada.at(cont);
       cont++;
    }
    stringstream convert(columnaIngresada); // stringstream used for the conversion initialized with the contents of Text
    convert>>columnaNumero;
    return columnaNumero;
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
    cout<<" \t \t B B B  I EEEEE NN    N V       V EEEEE NN    N I DDDD   OOOO          A     L              "<<endl;
    cout<<" \t \t B    B I E     N N   N  V     V  E     N N   N I D   D O    O        A A    L              "<<endl;
    cout<<" \t \t B B B  I EEEEE N  N  N   V   V   EEEEE N  N  N I D   D O    O       A   A   L              "<<endl;
    cout<<" \t \t B    B I E     N   N N    V V    E     N   N N I D   D O    O      AAAAAAA  L              "<<endl;
    cout<<" \t \t B B B  I EEEEE N    NN     V     EEEEE N    NN I DDDD   OOOO      A       A LLLLL          "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;

    cout<<" \t \t @@@@@  @    @  @@@@   @@@@     @     @@   @@ @ @@    @     @     @@@@    "<<endl;
    cout<<" \t \t @    @ @    @ @      @        @ @    @ @ @ @ @ @ @   @    @ @   @        "<<endl;
    cout<<" \t \t @@@@@  @    @  @@@@  @       @   @   @  @  @ @ @  @  @   @   @   @@@@    "<<endl;
    cout<<" \t \t @    @ @    @      @ @      @@@@@@@  @     @ @ @   @ @  @@@@@@@      @   "<<endl;
    cout<<" \t \t @@@@@   @@@@   @@@@   @@@@ @       @ @     @ @ @    @@ @       @ @@@@    "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                               *********                                       "<<endl;
    cout<<"                           *****************                                       "<<endl;
    Sleep(50);
    cout<<"                        ***********************                                 "<<endl;
    Sleep(50);
    cout<<"                    ********************************                        "<<endl;
    Sleep(50);
    cout<<"                ***************************************                  "<<endl;
    Sleep(50);
    cout<<"            *********************************************               "<<endl;
    Sleep(50);
    cout<<"          ***************************************************            "<<endl;
    Sleep(50);
    cout<<"        *******************************************************           "<<endl;
    Sleep(50);
    cout<<"       **********************************************************          "<<endl;
    Sleep(50);
    cout<<"      ************************************************************          "<<endl;
    Sleep(50);
    cout<<"      ************************************************************          "<<endl;
    Sleep(50);
    cout<<"        *********************************************************          "<<endl;
    Sleep(50);
    cout<<"           ****************************************************           "<<endl;
    Sleep(50);
    cout<<"             ************************************************            "<<endl;
    Sleep(50);
    cout<<"                ******************************************               "<<endl;
    Sleep(50);
    cout<<"                   ************************************                  "<<endl;
    Sleep(50);
    cout<<"                      *****************************      *                  "<<endl;
    Sleep(50);
    cout<<"                        ************************          **                  "<<endl;
    cout<<"                           *****************              ***                    "<<endl;
    Sleep(50);
    cout<<"                               *********                  ****                 "<<endl;
    Sleep(50);
    cout<<"                                                           ******     "<<endl;
    Sleep(50);
    cout<<endl;
    cout<<endl;
}

void expandirCeros(int fila,int columna, arregloDeChar campo, arregloDeChar campoParaImpresion)
{
    char caracterSinBombaA= 254;
    char caracterSinBombaB= 176;
    int filaAnalizada=fila;
    int columnaAnalizada=columna;
    int contador=0;
}


