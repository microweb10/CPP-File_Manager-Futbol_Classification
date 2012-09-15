// *********************************************************************
// DNI 1: 48460003-S Francisco Bernabeu Tovar
// DNI 2: 45567904-M Julian Nicolas Herrero
// *********************************************************************

//libreria lib2.h

#include <fstream>
#include <string>
#include <iostream>
using namespace std;


//ESTRUCTURAS

struct Tpartido {
	string equipo1;
	string equipo2;
	unsigned short int golesEquipo1;
	unsigned short int golesEquipo2;
};


struct Tnodo {
	unsigned short int puntos;
	unsigned short int numPartidos;
	string nombre;
	unsigned short int golesFavor;
	unsigned short int golesContra;
	Tnodo *sig;
};
typedef Tnodo *Tequipo;


struct Tregistro {
	unsigned short int puntos;
	unsigned short int numPartidos;
	char nombre[30];
	unsigned short int golesFavor;
	unsigned short int golesContra;
};


// DECLARACION DE CONSTANTES

const int kNUMPARTIDOS=10;
const string kM1="M1:OPCION INCORRECTA.";
const string kM2="M2:ERROR EN EL FICHERO.";
const string kM3="M3:ERROR FICHERO.JORNADA INCORRECTA.";
const string kM4="M4:ERROR CREACION LISTA.";
const string kM5="M5:ERROR AL ACTUALIZAR LA JORNADA.";
const string kM6="M6:LISTA VACIA.NODOS BORRADOS:";
const string kM7="M7:ERROR EN LA CREACION DEL FICHERO.";
const string kM8="M8:ERROR EN LA CRECION DE LA NUEVA LISTA.";
const string kM9="M9:ERROR NO HAY PARTIDOS.";


// PROTOTIPOS DE FUNCIONES

int VisualizarJornada (string);
int IntroducirNuevaJornada (string, Tpartido[]);
int CrearListaDeJornada (Tpartido[], Tequipo &);
int ActualizarListaDeJornada (Tpartido[], Tequipo &);
int BorrarLista (Tequipo &);
int CrearFicheroClasificacion (string, Tequipo);
int CrearListaDeFichero (string, Tequipo &);
void VisualizarListaEquipos (Tequipo);
int ConvertirStringAEntero (string);







