#include <unistd.h>
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>

using namespace std;
#include "TXT_FB.hpp"

int main()
{

    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0, num;
    arvore *A=NULL;
    stringstream strBuffer;
    string op, linha;
    ifstream arq ("entrada.txt");
    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "................Árvore.............." << endl;
        cout << "-- 1 Inseir                   ......" << endl;
        cout << "-- 2 Mostrar                  ......" << endl;
        cout << "-- 3 Remover elemento         ......" << endl;
        cout << "-- 4 Quantidade de nós FB     ......" << endl;
        cout << "-- 5 Descendentes             ......" << endl;
        cout << "-- 6 Ler arquivo texto        ......" << endl;
        cout << "-- 7 Grau de um nó            ......" << endl;
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
            inserir(&A,10);
            inserir(&A,20);
            inserir(&A,30);
            inserir(&A,40);
            inserir(&A,50);
            inserir(&A,60);
            inserir(&A,70);
            inserir(&A,80);
            inserir(&A,90);


            cout<<"Valor inserido com sucesso!"<<endl;
            system("pause");
            break;
        case 2:
            system("cls");
            cout<<"Árvore na pré-ordem: ";
            mostra_PreOrd(A);
            cout<<endl;
            cout<<"Árvore horizontal: ";
            imprimir(A,0);
            cout<<endl;
            system("pause");
            break;
        case 3:
            system("cls");
            cout<<"Informe um número para ser removido:";
            cin>>num;
            if(busca_valor(A,num))
            {
                A=remover(A,num);
                cout<<"Elemento removido!"<<endl;

            }
            else
                cout<<"Esse número não está na árvore!"<<endl;


            system("pause");
            break;
        case 4:
            system("cls");

            cout<<"Quantidade de nós com FB = -1: "<<calcula_fb_Menos1(A)<<" nós"<<endl;
            cout<<"Quantidade de nós com FB = 0: "<<calcula_fb_zero(A)<<" nós"<<endl;
            cout<<"Quantidade de nós com FB = +1: "<<calcula_fb_Mais1(A)<<" nós"<<endl;

            system("pause");
            break;

        case 5:
            system("cls");
            cout<<"Informe um número para descobrir seus descendentes: ";
            cin>>num;
            if(busca_valor(A,num))
            {
                imprimir(retorna_busca(A,num),0);
                cout<<endl;

                cout<<"Ancestrais do nó:"<<endl;
                ancestrais(A,num);
                cout<<endl;
                cout<<"Descendentes do nó:"<<endl;
                descendentes(retorna_busca(A,num),num);
                cout<<endl;

            }
            else
                cout<<"O valor não existe na árvore!"<<endl;

            system("pause");
            break;
        case 6:
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
                cout<<op<<endl;
                if(op == "Incluir")
                {
                    strBuffer >> num;
                    inserir(&A,num);
                }
                else if(op == "Remover")
                {
                    strBuffer >> num;
                    if(busca_valor(A,num))
                        A=remover(A,num);
                    else
                        cout<<"O valor NÃO está na árvore!"<<endl;
                }
                else if(op == "Mostrar")
                {
                    strBuffer >> num;
                    if(num==1)
                    {
                        cout<<"Pré-ordem: ";
                        mostra_PreOrd(A);
                        cout<<endl;
                        imprimir(A,0);
                        cout<<endl;
                    }
                    else if(num==2)
                    {
                        cout<<"Ordem simétrica: ";
                        mostra_OrdS(A);
                        cout<<endl;
                    }

                }

            }

            usleep(10000);
            system("pause");
            break;
        case 7:
            system("cls");

            cout<<"Grau dos nós da arvore"<<endl;
            grau(A);
            system("pause");
            break;
        }

    }
    while (menu != 0);

}


