// *********************************************************************
// DNI 1: 48460003-S Francisco Bernabeu Tovar
// DNI 2: 45567904-M Julian Nicolas Herrero
// *********************************************************************

//funciones lib2.cc

#include "lib2.h"
using namespace std;


//funcion VisualizarJornada
int VisualizarJornada (string fichero){
	int aux=0;
	fstream jornada;
	char letra;
	jornada.open(fichero.c_str(),ios::in);
	if (!jornada)
		aux=-1;
	else {
		letra=jornada.get();
		while (!jornada.eof()){
			cout.put (letra);
			letra=jornada.get();
		}
		cout<<endl;
	}
	jornada.close();
return (aux);
}


//funcion IntroducirNuevaJornada
int IntroducirNuevaJornada (string fichero,Tpartido partidos[]){
	int aux=0,i=0;
	fstream jornada;
	jornada.open(fichero.c_str(),ios::in);
	if (!jornada)
		aux=-1;
	else {
		while ((i<kNUMPARTIDOS)&&(!jornada.eof())){
			jornada>>partidos[i].equipo1;
			jornada>>partidos[i].golesEquipo1;
			jornada.get(); //PARA LEER EL GUION
			jornada>>partidos[i].equipo2;
			jornada>>partidos[i].golesEquipo2;
			i++;
		}
	}
	jornada.close();
return (aux);
}


//funcion CrearListaDeJornada
int CrearListaDeJornada (Tpartido jornada[], Tequipo &inicio) {
	int aux=0,i=0;
	Tequipo nodo1,nodo2;
	nodo1 = new Tnodo;
	if (!nodo1)
		aux=-1;
	else {
		inicio=nodo1;
		for (i;i<kNUMPARTIDOS;i++) {
			nodo2 = new Tnodo;
			if (!nodo2) {
				aux=-1;
				i=kNUMPARTIDOS;
			}
			else {
				nodo1->numPartidos=1;
				nodo1->nombre=jornada[i].equipo1;
				nodo1->golesFavor=jornada[i].golesEquipo1;
				nodo1->golesContra=jornada[i].golesEquipo2;
				//verificacion del equipo ganador para asignar puntos
				if (jornada[i].golesEquipo1==jornada[i].golesEquipo2) {
					nodo1->puntos=1;
					nodo2->puntos=1;
				}
				else {
					if (jornada[i].golesEquipo1>jornada[i].golesEquipo2) {
						nodo1->puntos=3;
						nodo2->puntos=0;
					}
					else {
						nodo1->puntos=0;
						nodo2->puntos=3;
					}
				}
				nodo1->sig=nodo2;
				nodo2->numPartidos=1;
				nodo2->nombre=jornada[i].equipo2;
				nodo2->golesFavor=jornada[i].golesEquipo2;
				nodo2->golesContra=jornada[i].golesEquipo1;
				nodo1 = new Tnodo;
				if (!nodo1) {
					aux=-1;
					i=kNUMPARTIDOS;
				}
				else {
					if (i==kNUMPARTIDOS-1)
						nodo2->sig=NULL;
					else
						nodo2->sig=nodo1;
				}
			}
		}
	}
return (aux);
}


//funcion ActualizarListaDeJornada
int ActualizarListaDeJornada (Tpartido jornada[], Tequipo &inicio) {
	int aux=0,i;
	Tequipo nodo1;
	nodo1=inicio;
	while (nodo1!=NULL) {
		i=0;
		while ((i<kNUMPARTIDOS)&&(nodo1->nombre!=jornada[i].equipo1)&& 							(nodo1->nombre!=jornada[i].equipo2))
			i++;
		if (i==kNUMPARTIDOS) {
			aux=-1;
			nodo1=NULL;
		}
		else {
			nodo1->numPartidos+=1;
			if (nodo1->nombre==jornada[i].equipo1) {
				nodo1->golesFavor+=jornada[i].golesEquipo1;
				nodo1->golesContra+=jornada[i].golesEquipo2;
				if (jornada[i].golesEquipo1==jornada[i].golesEquipo2)
					nodo1->puntos+=1;
				else
					if (jornada[i].golesEquipo1>jornada[i].golesEquipo2)
						nodo1->puntos+=3;
			}
			else {
				nodo1->golesFavor+=jornada[i].golesEquipo2;
				nodo1->golesContra+=jornada[i].golesEquipo1;
				if (jornada[i].golesEquipo1==jornada[i].golesEquipo2)
					nodo1->puntos+=1;
				else
					if (jornada[i].golesEquipo2>jornada[i].golesEquipo1)
						nodo1->puntos+=3;
			}
			nodo1=nodo1->sig;
		}
	}
return (aux);
}


//funcionBorrarLista
int BorrarLista (Tequipo &inicio) {
	int aux=0;
	Tequipo nodo1,nodo2;
	nodo1=inicio;
	while (nodo1!=NULL) {
		nodo2=nodo1->sig;
		delete nodo1;
		nodo1=nodo2;
		aux++;
	}
	inicio=nodo1;
return (aux);
}


//funcion CrearFicheroClasificacion
int CrearFicheroClasificacion (string salida, Tequipo inicio) {
	int aux=0;
	Tequipo nodo;
	Tregistro registro;
	fstream fichero;
	fichero.open (salida.c_str(),ios::out);
	if (!fichero)
		aux=-1;
	else {
		nodo=inicio;
		while (nodo!=NULL) {
			registro.puntos=nodo->puntos;
			registro.numPartidos=nodo->numPartidos;
			strcpy (registro.nombre,nodo->nombre.c_str());
			registro.golesFavor=nodo->golesFavor;
			registro.golesContra=nodo->golesContra;
			fichero.write(((const char*)(&registro)), sizeof(Tregistro));
			nodo=nodo->sig;
		}
		fichero.close();
	}
return (aux);
}


//funcion CrearListaDeFichero
int CrearListaDeFichero (string ficheroEntrada,Tequipo &inicio) {
	int aux=0;
	fstream fichero;
	Tequipo nodo1, nodo2;
	Tregistro registro;
	fichero.open (ficheroEntrada.c_str(),ios::in);
	if (!fichero)
		aux=-1;
	else {
		if (inicio!=NULL)
			cout<<kM6<<BorrarLista(inicio);
		else {
			nodo1 = new Tnodo;
			if (!nodo1)
				aux=-1;
			else {
				inicio=nodo1;
				fichero.read (((char*)(&registro)), sizeof(Tregistro));
				while (!fichero.eof()) {
					nodo1->puntos=registro.puntos;
					nodo1->numPartidos=registro.numPartidos;
					nodo1->nombre=registro.nombre;
					nodo1->golesFavor=registro.golesFavor;
					nodo1->golesContra=registro.golesContra;
					fichero.read (((char*)(&registro)), sizeof(Tregistro));
					if (fichero.eof())
						nodo1->sig=NULL;
					else {
						nodo2 = new Tnodo;
						if (!nodo2)
							aux=-1;
						else {
							nodo1->sig=nodo2;
							nodo1=nodo2;
						}
					}
				}
				fichero.close();
			}
		}
	}
return (aux);
}


//funcionVisualizarListaEquipos
void VisualizarListaEquipos (Tequipo inicio) {
	int posicion=1;
	Tequipo nodo1;
	nodo1=inicio;
	cout<<"CLASIFICACION DE LOS EQUIPOS"<<endl;
	cout<<"============================"<<endl;
	cout<<"Pos*Nombre     *Puntos*Partidos*GolesFavor*GolesContra*"<<endl;
	cout<<"================================================================="<<endl;
	while (nodo1!=NULL) {
		cout<<posicion<<"   "<<nodo1->nombre<<"\t   "<<nodo1->puntos<<"\t   "<<nodo1->numPartidos			<<"\t    "<<nodo1->golesFavor<<"\t       "<<nodo1->golesContra<<endl;
		nodo1=nodo1->sig;
		posicion++;
	}
return;
}


//funcion ConvertirStringAEntero
int ConvertirStringAEntero (string goles) {
	int aux;
	if (goles=="0") aux=0;
	if (goles=="1") aux=1;
	if (goles=="2") aux=2;
	if (goles=="3") aux=3;
	if (goles=="4") aux=4;
	if (goles=="5") aux=5;
	if (goles=="6") aux=6;
	if (goles=="7") aux=7;
	if (goles=="8") aux=8;
	if (goles=="9") aux=9;
return(aux);
}














