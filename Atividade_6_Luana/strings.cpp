#include <unistd.h>
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>

using namespace std;

#include "stringAVL.hpp"

int main()
{

    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0;

    arvore *A=NULL;
    string nome;
    stringstream strBuffer;
    string op, linha;
    ifstream arq ("palavras.txt");

    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "................Árvore.............." << endl;
        cout << "-- 1 Inseir             ......" << endl;
        cout << "-- 2 Mostrar            ......" << endl;
        cout << "-- 4 txt                 ......" << endl;
        cout << "-- 0 Sair                     ......" << endl;
        cout << "...................................." << endl;
        cout << "Sua escolha: ";
        cin >> menu;
        fflush(stdin);
        switch(menu)
        {
        case 0:
            system("cls");
            cout << "Programa finalizado!";
            system("pause");
            break;
        case 1:
            system("cls");

            system("pause");
            break;

        case 2:
            system("cls");

            system("pause");
            break;
        case 3:
            system("cls");


            system("pause");
            break;
        case 4:
            system("cls");
            if (!arq.is_open())
            {
                cout << "Erro: não foi possível abrir o arquivo texto.\n";
                return 0;
            }

            while(!arq.eof())
            {
                linha = "";
                getline(arq, linha);
                strBuffer = stringstream(linha);
                strBuffer >> op;
                // cout<<op<<endl;
                if(op == "inserir")
                {
                    strBuffer >> nome;
                    inserir(&A,nome);
                    cout<<"ok "<<endl;
                }
                else if(op == "mostrar")
                {
                    cout<<"Palavras: "<<endl;
                    imprimir(A,1);
                    cout<<endl;
                }


            }

            usleep(10000);

            system("pause");
            break;


        }
    }
    while (menu != 0);

}

