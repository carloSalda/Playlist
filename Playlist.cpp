//Carlos Eugenio Saldaña Tijerina 


#include <iostream>
#include <string>
#include <stdio.h>
#include <array>
#include<ctime>
#include <cstdlib>
using namespace std;


class Tiempo{    // clase tiempo
    protected:        //protected en vez de private para poder usar herencias 
        int minutos;
        int segundos;
    public:
        Tiempo();
        Tiempo(int, int);
        int getMinutos();
        int getSegundos();
        void setMinutos(int);
        void setSegundos(int);
};

Tiempo::Tiempo(){         //Constructor default tiempo
    minutos=0;
    segundos=0;
}

Tiempo::Tiempo(int tiempoMinutos, int tiempoSegundos){   //Constructor con parametros dados por el user
    minutos= tiempoMinutos;
    if (tiempoSegundos>=60){      //   if para checar que segundos sean menor a 60
        minutos= minutos+tiempoSegundos/60;
        segundos= tiempoSegundos%60;
    }
    else {
        segundos=tiempoSegundos;
    }
}

int Tiempo::getMinutos(){
    return minutos;
}

int Tiempo::getSegundos(){
    return segundos;
}

void Tiempo:: setMinutos(int tiempoMinutos){
    minutos=tiempoMinutos;
}

void Tiempo:: setSegundos(int tiempoSegundos){
    if (tiempoSegundos>=60){      //   if para checar que segundos sean menor a 60
        minutos= minutos+tiempoSegundos/60;
        segundos= tiempoSegundos%60;
    }
    else {
        segundos=tiempoSegundos;     //si no es mas de 60 simplemente se suma a el valor numeros
    }
}


class Cancion : public Tiempo{     // clase cancion con herencia de tiempo
    private:
        bool cancionExiste;      //booleano para determinar si cancion se toma en cuenta
        string nombreCancion;
        string nombreArtista;
        string nombreAlbum;
    public:
        Cancion();
        Cancion(string, string, string, int, int);
        string getNombreCancion();
        Tiempo getDuracionCancion();
        string getNombreArtista();
        string getNombreAlbum();
        bool getCancionExiste();
        void setNombreCancion(string);
        void setDuracionCancion(Tiempo);
        void setNombreArtista(string);
        void setNombreAlbum(string);
};

Cancion::Cancion(){      //constructor default cancion
    nombreCancion="Eso tilin";  
    nombreArtista="Carlos Lagaña";
    nombreAlbum="Inodoro Azul";
    cancionExiste=false;
}

Cancion::Cancion(string nombreMusica, string nombreCantante, string nombreRecord, int tiempoMinutos, int tiempoSegundos) :Tiempo( tiempoMinutos, tiempoSegundos) {       //constructor con herencia de tiempo
    nombreCancion= nombreMusica;
    nombreArtista=nombreCantante;
    nombreAlbum=nombreRecord;
    cancionExiste=true;             //comprobar si la cancion fue escrita por el usuario y no por el default
}


string Cancion::getNombreCancion(){
    return nombreCancion;
}

bool Cancion::getCancionExiste(){
    return cancionExiste;
}


string Cancion::getNombreArtista(){
    return nombreArtista;
}
string Cancion::getNombreAlbum(){
    return nombreAlbum;
}


void Cancion::setNombreCancion(string nombreMusica){
    nombreCancion=nombreMusica;
}

void Cancion::setNombreArtista(string nombreCantante){
    nombreArtista=nombreCantante;
}

void Cancion::setNombreAlbum(string nombreRecord){
    nombreAlbum=nombreRecord;
}

class Playlist : public Tiempo {
    private: 
        string nombrePlaylist;
        Tiempo duracionPlaylist;
        Cancion lista[50];                   //Array de canciones con limite de 50
    public:
        Playlist();
        Playlist(string);
        string getNombrePlaylist();
        int getNumeroCanciones();
        Tiempo getDuracionPlaylist();
        Cancion getCancionPlaylist(int);
        void setCancionPlaylist(Cancion, int);
        void setNombrePlaylist(string);
        void setNumeroCanciones(int);
        void setDuracionPlaylist(Tiempo);
        void actualizarTiempo();                //agregar el tiempo de cada cancion nueva 
        int getMinutos();
        int getSegundos();

};

Playlist::Playlist(){                           //Constructor default nombre playlist
    nombrePlaylist="Somalis en McAllen";
}

Playlist::Playlist(string nombreLista){        //Constructor con parametros de nombre
    nombrePlaylist= nombreLista;
}

string Playlist::getNombrePlaylist(){
    return nombrePlaylist;
}

int Playlist::getNumeroCanciones(){                    //si la cancion es escrita por el usuario se le suma a el contador de canciones en la playlist
  int canciones=0;  
  for (int contador=0; contador<50; contador++){
    if(getCancionPlaylist(contador).getCancionExiste()){
      canciones=canciones+1;
    } 
   };
  return canciones;
}

Tiempo Playlist::getDuracionPlaylist(){
  actualizarTiempo();            //Actualizar el tiempo cuando se le agrega una duracion de cancion nueva
  return duracionPlaylist;
}

void Playlist::setNombrePlaylist(string nombreLista){
    nombrePlaylist=nombreLista;
}

void Playlist::setDuracionPlaylist(Tiempo duracionLista){
    duracionPlaylist=duracionLista;
}

Cancion Playlist::getCancionPlaylist(int posicion){    //getter para sacar cancion especifica
    return lista[posicion];
}

void Playlist::setCancionPlaylist(Cancion cancionset, int posicion){
  lista[posicion]=cancionset;
}

void Playlist::actualizarTiempo(){   //funcion para actualizar el tiempo
  int segundostemp=0;
  for(int iteracion=0;iteracion<50;iteracion++){   //for que checa cada cancion
    if(getCancionPlaylist(iteracion).getCancionExiste()) //solo toma en cuenta canciones con booleano true
      segundostemp = segundostemp + getCancionPlaylist(iteracion).getSegundos(); //getter de segundos de cancion
      minutos = minutos + getCancionPlaylist(iteracion).getMinutos();
  } //getter de minutos de cancion
  if (segundostemp>=60){      //   if para checar que segundos sean menor a 60
    minutos= minutos+(segundostemp/60);
    segundos= segundostemp%60; //segundos igual al remainder de division
    }else{
    segundos=segundostemp; //si los segundos son menores a 60 no se hace nada
    }
}

int Playlist::getMinutos(){
  actualizarTiempo();   //actualizacion de tiempo antes de retorno de valor
  return minutos;
}

int Playlist::getSegundos(){
  actualizarTiempo();    //actualizacion de tiempo antes de retorno de valor
  return segundos;
}



int main(){
  Cancion cancion;  //inicializacion de variables
  Playlist playlistinfo;
  int contador=0;
  string nombreIn;

  getline(cin, nombreIn); //input para nombre de playlist, uso de getline para strings con espacio

  playlistinfo.setNombrePlaylist(nombreIn); //set de nombre de playlist
 
  for (int contador=0; contador<50; contador++){  //for loop hasta maximo de canciones
    string nombreCancionIn,nombreArtistaIn, nombreAlbumIn, tiempoIn, segundosIn, minutosIn;  //declaracion de variables temporales
    
    getline(cin, nombreCancionIn);
    if (nombreCancionIn==""){ //check para break
      break;
      }
    getline(cin, minutosIn);
    getline(cin, segundosIn);
    getline(cin, nombreArtistaIn);
    getline(cin, nombreAlbumIn);
    Cancion prueba(nombreCancionIn,nombreArtistaIn,nombreAlbumIn,stoi(minutosIn),stoi(segundosIn));//creacion de cancion temporal, uso de stoi para paso de strings a integers
    playlistinfo.setCancionPlaylist(prueba, contador ); //adicion de cancion a playlist
  }
  cout << "-Playlist creada-\n"; 

  cout << "Playlist: " << playlistinfo.getNombrePlaylist() << "\n";
  cout << "Cantidad de canciones: " << playlistinfo.getNumeroCanciones()<< "\n";
  cout << "Duración total: " << playlistinfo.getMinutos() << ":" << playlistinfo.getSegundos()<< "\n" ;

  for (int contador=0; contador<50; contador++){  //for loop hasta maximo de canciones
    if(playlistinfo.getCancionPlaylist(contador).getCancionExiste()){  //check para que solo se impriman canciones validas
      cout << contador+1 <<". "<<playlistinfo.getCancionPlaylist(contador).getNombreCancion()<<"\n";
      cout << "   "<<playlistinfo.getCancionPlaylist(contador).getNombreArtista()<<"\n";
      cout << "   "<<playlistinfo.getCancionPlaylist(contador).getNombreAlbum()<<"\n";
      cout << "   "<<playlistinfo.getCancionPlaylist(contador).getMinutos() << ":" << playlistinfo.getCancionPlaylist(contador).getSegundos()<< "\n" ;
      
    }
  }
  cout << "\n"
  cout << "-playlist cambio-\n"<<"modo de ejecucion: aleatorio\n\n"<<"-Cancion consulta-\n";
  cout << "Numero de cancion: 4\n"; 
  cout << "Titulo: "<<playlistinfo.getCancionPlaylist(3).getNombreCancion()<<"\n";
  cout << "Artista: "<<playlistinfo.getCancionPlaylist(3).getNombreArtista()<<"\n";
  cout << "Album: "<<playlistinfo.getCancionPlaylist(3).getNombreAlbum()<<"\n";
  cout << "Duracion: "<<playlistinfo.getCancionPlaylist(3).getMinutos() << ":" << playlistinfo.getCancionPlaylist(3).getSegundos()<< "\n\n" ;
  
  srand(time(0)); //declaracion de random con tiempo


  for (int contador=0; contador<playlistinfo.getNumeroCanciones(); contador++){ //contador que pasa por cada cancion
    int index = rand() % playlistinfo.getNumeroCanciones(); //numero random

    Cancion temp = playlistinfo.getCancionPlaylist(contador); //guarda cancion en variable temporal
    playlistinfo.setCancionPlaylist(playlistinfo.getCancionPlaylist(index),contador); //reemplazo de cancion con index random
    playlistinfo.setCancionPlaylist(temp, index); //remplazo de cancion en index random
    
  }
  cout << "-Lista de reproducción-\n";
  for (int contador=0; contador<playlistinfo.getNumeroCanciones(); contador++){ //impresion de canciones en orden aleatoria
  cout << contador+1 <<". "<< playlistinfo.getCancionPlaylist(contador).getNombreCancion() << endl<<endl;
    }
  
  return 0;
}

//Orden de inputs:
//NombrePlaylist - Nombre Cancion - Duracion minutos- Duracion segundos- Nombre Artista - Nombre Album
// Si se quiere ingresar otra cancion simplemente repetir desde el paso nombre cancion 
//Si se quiere cerrar la playlist no escribir nada y darle enter