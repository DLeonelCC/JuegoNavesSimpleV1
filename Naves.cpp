#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>

///Definiendo las teclas con sus respectivos numeros asigandos por tecla predeterminados
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

///windows.h nos permite dar una posicion a nuestro cursor o salida
///conio.h nos permite dectectar si se presionaron teclas en la consola
///stdlib.h nos permite dar numeros aleatorios con randon
///list nos permite crear una lista predeterminada para ahorrar lineas de codigo

using namespace std;


void gotoxy(int x, int y){///determinar posicion

    HANDLE hcon;///creando un HANDLE(identificador de nuestra pantalla de consola) y guardandolo en hcon
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);///recuperando el identificador de la consola y tener el control de la pantalla de la consola

    COORD Pos;///definiedo las nuevas coordenadas de nuestra salida de datos
    Pos.X = x;
    Pos.Y = y;

    SetConsoleCursorPosition(hcon, Pos);///funcion para dar nueva pocision al cursor

}

void OcultarCursor(){

    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO apari; /// controlar la apariencia del cursor usando un objeto por nombre apari en esta ocacion
    apari.dwSize = 50;  ///atributos del objeto // tamaño del cursor
    apari.bVisible = FALSE; /// visivilidad del cursor

    SetConsoleCursorInfo(hcon,&apari);///& = por referencia para que pueda accecer a sus datos y modificar en el caso de la visibilidad

}

void Pintar_Limites(){
    for(int i=2; i<117; i++){
            gotoxy(i,3);  cout<<char(205);
            gotoxy(i,28); cout<<char(205);
    }

    for(int j=4; j<28; j++){
        gotoxy(2,j);  cout<<char(186);
        gotoxy(117,j); cout<<char(186);
    }

    gotoxy(2,3);    cout<<char(201);
    gotoxy(117,3);  cout<<char(187);
    gotoxy(2,28);   cout<<char(200);
    gotoxy(117,28); cout<<char(188);

}

class Nave{
private:
    int x;
    int y;
    int corazones;
    int vidas;
public:
    Nave(int _x,int _y,int _corazones, int _vidas){
        x = _x;
        y = _y;
        corazones = _corazones;
        vidas = _vidas;
    }

    int RetX(){
        return x;
    }
    int RetY(){
        return y;
    }
    int RetVidas(){
        return vidas;
    }

    void Pintar(){
        gotoxy(x,y);  cout<<"  "<<char(254);
        gotoxy(x,y+1);cout<<" "<<char(40)<<char(207)<<char(41);
        gotoxy(x,y+2);cout<<char(201)<<char(223)<<" "<<char(223)<<char(187);

    }

    void Borrar(){
        gotoxy(x,y);  cout<<"      ";
        gotoxy(x,y+1);cout<<"      ";
        gotoxy(x,y+2);cout<<"      ";

    }

    void Mover(){

         if(kbhit()){///funcion que detecta si se ah presionado una tecla
                char tecla = getch();///getch = guardando la tecla que se presione en la variable tecla
                Borrar();
                if(tecla == IZQUIERDA && x>3){
                    x--;
                    x--;
                }
                if(tecla == DERECHA && x+6<117){
                    x++;
                    x++;
                }
                if(tecla == ARRIBA && y>4){
                    y--;
                }
                if(tecla == ABAJO && y+3<28){
                    y++;
                }
                if(tecla == 'o'){
                    corazones--;
                }
                Pintar();
                PintarCorazones();
         }
    }

    void PintarCorazones(){
        gotoxy(90,2);   cout<<"Vidas: "<<vidas;
        gotoxy(105,2);  cout<<"Salud:";
        gotoxy(111,2);  cout<<"     ";

        for(int i=0; i<corazones; i++){
            gotoxy(111+i,2);cout<<char(219);
        }
    }

    void MenosCorazones(){
        corazones--;
    }

    void Morir(){
        if(corazones == 0){

            Borrar();
            gotoxy(x,y);   cout<<"  **  ";
            gotoxy(x,y+1); cout<<" **** ";
            gotoxy(x,y+2); cout<<"  **  ";
            Sleep(200);

            Borrar();
            gotoxy(x,y);   cout<<"* ** *";
            gotoxy(x,y+1); cout<<" **** ";
            gotoxy(x,y+2); cout<<"* ** *";
            Sleep(200);

            Borrar();
            vidas--;
            corazones = 3;
            PintarCorazones();
            Pintar();
        }
    }
};

class Asteroide{
private:
    int x;
    int y;
public:
    Asteroide(int _x, int _y){
        x = _x;
        y = _y;
    }
    int RetXAst(){
        return x;
    }
    int RetYAst(){
        return y;
    }

    void PintarAst(){
        gotoxy(x,y); cout<<char(178);
    }

    void MoverAst(){
        gotoxy(x,y); cout<<" ";
        y++;
        if(y > 27){
                x = rand()%100 + 4;
                y = 4;
        }
        PintarAst();
    }

    void Choque(class Nave &N){
        if( x >= N.RetX() && x < N.RetX() + 6 && y >= N.RetY() && y <= N.RetY() + 2){
                N.MenosCorazones();
                N.Borrar();
                N.Pintar();
                N.PintarCorazones();
                x = rand()%100 + 4;
                y = 4;
                PintarAst();

        }
    }
};

class Bala{
private:
    int x;
    int y;
public:
    Bala(int _x, int _y){
        x = _x;
        y = _y;
    }

    int RetXBa(){
        return x;
    }
    int RetYBa(){
        return y;
    }

    void Mover(){
            gotoxy(x,y);cout<<" ";
            y--;
            gotoxy(x,y); cout<<char(94);
    }

    bool Fuera(){
        if(y == 4){
            return true;
        }else{
            return false;
        }

    }
};


int main(){

    OcultarCursor();
    Pintar_Limites();


    Nave n(57,25,5,3);
    n.Pintar();
    n.PintarCorazones();

    list<Asteroide*> a;
    list<Asteroide*>::iterator itA;
    for(int i=0; i<5; i++){
        a.push_back(new Asteroide(rand()%114 + 3, rand()%5 + 4));
    }


    list<Bala*> b;  ///creando  una lista para guardar punteros clase objetos
    list<Bala*>::iterator it;/// recorrer toda la lista a travez de it y hacer lo que queramos con los elementos de la lista


    bool game_over = false;
    int puntos = 0;

    while(!game_over){

            gotoxy(4,2);cout<<"Puntos: "<<puntos;

            if(kbhit()){
                char tecla = getch();
                if(tecla == 'h'){
                    b.push_back(new Bala(n.RetX() + 2,n.RetY() - 1)); ///creando un objeto bala en la lista
                }
            }

            for(it = b.begin(); it != b.end(); it++){///recorriendo la lista desde el principio con(.begin) hasta el final con (.end)
                    (*it)->Mover();
                    if((*it)->Fuera()){
                        gotoxy((*it)->RetXBa(),(*it)->RetYBa()); cout<<" ";
                        delete(*it);
                        it = b.erase(it);///pansandonos al siguiente elemento para no perder la hilacion
                    }
            }

            for(itA = a.begin(); itA != a.end(); itA++){
                    (*itA)->MoverAst();
                    (*itA)->Choque(n);

            }

            for(itA = a.begin(); itA != a.end(); itA++){
                    for(it = b.begin(); it != b.end(); it++){
                            if( (*itA)->RetXAst() == (*it)->RetXBa() && ( (*itA)->RetYAst() + 1 == (*it)->RetYBa() ) || (*itA)->RetYAst() == (*it)->RetYBa() && (*itA)->RetXAst() == (*it)->RetXBa()){

                                gotoxy( (*it)->RetXBa() , (*it)->RetYBa() ); cout<<" ";
                                delete(*it);
                                it = b.erase(it);

                                a.push_back(new Asteroide(rand()%110 + 3,4));
                                gotoxy( (*itA)->RetXAst() , (*itA)->RetYAst() ); cout<<" ";
                                delete(*itA);
                                itA = a.erase(itA);

                                puntos = puntos + 5;
                            }
                    }
            }
            if(n.RetVidas() == 0){
                game_over = true;
            }

            n.Mover();
            n.Morir();
            Sleep(30);
    }
    gotoxy(54,16);  cout<<"Fin DEL JUEGO...";

gotoxy(4,28);return 0;
}
