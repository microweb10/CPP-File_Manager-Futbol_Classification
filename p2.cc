// *********************************************************************
// DNI 1: 48460003-S Francisco Bernabeu Tovar
// DNI 2: 45567904-M Julian Nicolas Herrero
// *********************************************************************

//Programa Principal

#include "lib2.h"
using namespace std;
int main(){
int opcion,i;
string fichero;
Tpartido partidos[kNUMPARTIDOS];
Tequipo lista=NULL;
do {
	cout<<endl;
	cout<<"MENU PRINCIPAL DE LA PRACTICA 2"<<endl;
	cout<<"==============================="<<endl;
	cout<<"\t1. VISUALIZAR JORNADA"<<endl;
	cout<<"\t2. INTRODUCIR NUEVA JORNADA"<<endl;
	cout<<"\t3. ACTUALIZAR LISTA EQUIPOS DESDE JORNADA"<<endl;
	cout<<"\t4. BORRAR LISTA EQUIPOS"<<endl;
	cout<<"\t5. ALMACENAR LISTA EQUIPOS EN FICHERO"<<endl;
	cout<<"\t6. RECUPERAR LISTA EQUIPOS DESDE FICHERO"<<endl;
	cout<<"\t7. VISUALIZAR LISTA EQUIPOS"<<endl;
	cout<<"\t0. SALIR DEL PROGRAMA"<<endl;
	cout<<"==============================="<<endl;
	cout<<"PULSE UNA OPCION:";
	cin>>opcion;
	cin.get();
	if((opcion<0)||(opcion>7))
		cout<<kM1<<endl;
	switch(opcion){
	case 1: cout<<"NOMBRE FICHERO DE LA JORNADA:";
		getline(cin,fichero);
		if (VisualizarJornada(fichero)==-1)
			cout<<kM2<<endl;
	break;
	case 2: cout<<"NOMBRE FICHERO DE LA JORNADA:";
		getline(cin,fichero);
		if (IntroducirNuevaJornada(fichero,partidos)==-1)
			cout<<kM3<<endl;
	break;
	case 3: if(partidos[1].equipo1=="")
			cout<<kM9<<endl;
		else {
			if (lista==NULL){
				if (CrearListaDeJornada(partidos,lista)==-1)
					cout<<kM4<<endl;
			}
			else {
				if (ActualizarListaDeJornada(partidos,lista)==-1)
					cout<<kM5<<endl;
			}
		}
	break;
	case 4: cout<<kM6<<BorrarLista(lista)<<endl;
	break;
	case 5: cout<<"NOMBRE FICHERO A CREAR:";
		getline(cin,fichero);
		if (CrearFicheroClasificacion(fichero,lista)==-1)
			cout<<kM7<<endl;
	break;
	case 6: cout<<"NOMBRE FICHERO PARA RECUPERAR:";
		getline(cin,fichero);
		if (CrearListaDeFichero(fichero,lista)==-1)
			cout<<kM8<<endl;
	break;
	case 7: VisualizarListaEquipos(lista);
	break;
	}
}
while (opcion !=0);
return (opcion);
}
