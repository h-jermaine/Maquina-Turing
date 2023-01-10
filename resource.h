#ifndef RESOURCE_H_
#define RESOURCE_H_
#include <iostream>
#include <map>
#include <string.h>
#define BOTON1 1001
#define BOTON2 1002
#define BOTON3 1003
#define CAJAENTRADA 1004
#define CAJAEDIT1 1051
#define CAJAEDIT2 1052
#define CAJAEDIT3 1053

HWND boton1;
HWND boton2;
HWND boton3;

HWND cajaEntrada;
HWND botonLeer;

HWND columnaMt;
HWND filaMt;
HWND estadoMt;

HWND cajaEditable1;
HWND cajaEditable2;
HWND cajaEditable3;

WORD Entrada;

int numeroEstado(std::string numEs);

class Columna{
    public:
    std::map<std::string, std::string> C;   //Inicializacion del map<string, string> C

    // Metodo insertar
    void Insertar(std::string Pos, std::string S){
        C[Pos]=S;
    }

    std::string Obtener(std::string Pos){
        //return C[Pos];
        std::map<std::string, std::string>::iterator it = C.find(Pos);
        if(it!=C.end())
            return (*it).second;
        else
            return "";
    }

    void Mostrar(HDC hdc, int i, int j){
        std::map<std::string, std::string>::iterator it;
        for(it = C.begin(); it != C.end(); it++){
            char arr[Obtener(it->first).length() + 1];
            strcpy(arr, Obtener(it->first).c_str());
            TextOut(hdc, i, j + (numeroEstado(it->first) * 30), arr, Obtener(it->first).length());
            //std::cout << "(" <<(*it).first<<")["<<(*it).second<<"] ";
        }
        //std::cout << std::endl;
    }
};

class Matriz{
    public:
    std::map<std::string, Columna> M;

    void Insertar(std::string Col, std::string Fil, std::string S){
        std::map<std::string, Columna>::iterator it=M.find(Col);
        if(it!=M.end())
            ((*it).second).Insertar(Fil,S);
        else{
            Columna ColObj;
            ColObj.Insertar(Fil,S);
            M[Col] = ColObj;
        }
    }

    void Mostrar(HDC hdc){
        std::map<std::string, Columna>::iterator it;
        int i = 100;
        char estadosArr [1024] = {"q0q1q2q3q4q5q6q7q8q9"};
        char estarr[2];
        for(int k = 180, j = 0; j < 19; k += 30, j += 2){

            estarr[0] = estadosArr[j];
            estarr[1] = estadosArr[j+1];
            TextOut(hdc, 20, k, estarr, 2);
        }
        for(it = M.begin(); it != M.end(); it++, i += 100){
            char arr[it->first.length() + 1];
            strcpy(arr, it->first.c_str());
            TextOut(hdc, i, 150, arr, it->first.length());
            ((*it).second).Mostrar(hdc, i, 180);
        }
        std::cout<<std::endl;
    }

    std::string Obtener(std::string Fil, std::string Col){
        std::map<std::string, Columna>::iterator it = M.find(Fil);
        if(it!=M.end())
            return ((*it).second).Obtener(Col);
        else
            return "";
    }

    void Eliminar(std::string Col, std::string Fil){
        std::map <std::string,Columna>::iterator itr = M.find(Col);
            if(itr != M.end()){
                (*itr).second.C.erase(Fil);
            }
    }

    int Verificar(char cptextoCajaMT[], std::string &estadoVr, std::string &senteciaVr, int &indiceVr){
        char cpTempTextoCajaMT [1] = "";
        cpTempTextoCajaMT[0] = cptextoCajaMT[indiceVr];
        std::string columnaVr = cpTempTextoCajaMT;
        std::string estadoTemp = "";
        std::string simbolo = "";
        std::string idicador = "";
        std::map <std::string,Columna>::iterator itr = M.find(columnaVr);
        if(itr != M.end()){
            std::map <std::string, std::string> contenidoVr = (*itr).second.C;
            std::string contenidoFirst = contenidoVr[estadoVr];
            senteciaVr = contenidoFirst;
            if(senteciaVr != ""){

                int contador = 0;
                for(int i = 0; i < contenidoFirst.length(); i++){
                    if((contenidoFirst[i] != ',') && (contador == 0))
                        estadoTemp += contenidoFirst[i];
                    if((contenidoFirst[i] != ',') && (contador == 1))
                        simbolo += contenidoFirst[i];
                    if((contenidoFirst[i] != ',') && (contador == 2))
                        idicador += contenidoFirst[i];
                    if(contenidoFirst[i] == ',')
                        contador++;
                }
                estadoVr = estadoTemp;
                cpTempTextoCajaMT[0] = simbolo[0];
                cptextoCajaMT[indiceVr] = cpTempTextoCajaMT[0];

                if(idicador == "D")
                    return indiceVr += 1;
                if(idicador == "I")
                    return indiceVr -= 1;
                if(idicador == "S"){
                    estadoVr = "q0";
                    return 0;
                }
            }
            else{
                estadoVr = "q0";
                return 0;
            }
        }
        estadoVr = "q0";
            return 0;
    }
};

int numeroEstado(std::string numEs){
    std::string temporal;
    for(int i = 1; i < numEs.length(); i++){
        temporal += numEs[i];
    }
    return stoi(temporal);
}

#endif // RESOURCE_H_

