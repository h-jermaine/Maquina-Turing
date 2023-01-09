#ifndef RESOURCE_H_
#define RESOURCE_H_

#define DENO 2342;

#include <iostream>
#define BT1 101
#define BT2 102
#define BT3 103

#define CAJALEER 202

#define BEDIT1 151
#define BEDIT2 152
#define BEDIT3 153

HWND deno;

HWND boton1;
HWND boton2;
HWND boton3;

HWND cajaLeer;
HWND botonLeer;

HWND columnaMt;
HWND filaMt;
HWND estadoMt;

HWND hEdtNum1;
HWND hEdtNum2;
HWND hEdtNum3;

WORD Comando;

#include <map>
#include <string.h>

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
            M[Col]=ColObj;
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

    void Verificar(HDC hdc, char textoC[]){
        std::string tmp;
        std::string estado1 = "q0";
        std::string estado2;
        std::string simbolo;
        std::string columna;
        std::string leerCinta;
        std::string tmpLeerCin;
        std::string tempCaja = textoC;
        int i = 1;
        while(tempCaja[i] != 'B'){
            tmp = tempCaja[i];
            std::map <std::string,Columna>::iterator itr = M.find(tmp);
            if(itr != M.end()){
                std::map <std::string, std::string> tmpnose = (*itr).second.C;
                leerCinta = tmpnose[estado1];
                if(leerCinta != ""){

                int cont = 0;
                for(int j = 0; j < leerCinta.length(); j++){
                    if((leerCinta[j] != ',') && (cont == 0))
                        estado2 += leerCinta[j];

                    if((leerCinta[j] != ',') && (cont == 1))
                        simbolo += leerCinta[j];

                    if((leerCinta[j] != ',') && (cont == 2))
                        columna += leerCinta[j];

                    if(leerCinta[j] == ',')
                        cont++;
                }
                //cout << estado2 << " " << simbolo << " " << columna << endl;
                estado1 = estado2;
                tempCaja[i] = simbolo[0];
                if(columna == "D")
                    i++;
                if(columna == "I")
                    i--;
                if(columna == "S")
                    break;
                estado2 = simbolo = columna = "";
                }
                else
                    break;
            }
            else
                break;
        }
            //std::cout << tempCaja << std::endl;
            for(int i = 0; i < tempCaja.length(); i++){
                textoC[i] = tempCaja[i];
            }
            std::string cpTextoC = textoC;
            char arr[1];
            for(int i = 0; i < cpTextoC.length(); i++){
                arr[0] = textoC[i];
                TextOut(hdc, 100 + (i * 20), 60, arr, 1);
            }
    }

    int Verificar2(char cptextoCajaWM[], std::string &estadoVr, std::string &senteciaVr, int &indiceVr){
        char cpTempTextoCajaWM [1] = "";
        cpTempTextoCajaWM[0] = cptextoCajaWM[indiceVr];
        std::string columnaVr = cpTempTextoCajaWM;
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
                cpTempTextoCajaWM[0] = simbolo[0];
                cptextoCajaWM[indiceVr] = cpTempTextoCajaWM[0];

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
