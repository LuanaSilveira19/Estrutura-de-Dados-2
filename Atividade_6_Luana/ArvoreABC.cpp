#include <unistd.h>
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "ABC.hpp"
void simetrica(arvore *t, char vet[], int indice=0)
{
    int i=indice;
    if(!testa_vazia(t))
    {
        simetrica(t->sae,vet,i+1);
        vet[i]=t->info;
        simetrica(t->sad,vet,i+total_nos(t->sae)+1);
    }
}
void ordena(char vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = i; j < tamanho; j++)
        {
            if (vetor[i] > vetor[j])
            {
                char temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}

int main()
{

    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0, num;
    arvore *A=NULL, *C=NULL;

    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "................Árvore.............." << endl;
        cout << "-- 1 Inseir                   ......" << endl;
        cout << "-- 2 Mostrar                  ......" << endl;
        cout << "-- 3 Remover elemento         ......" << endl;
        cout << "-- 4 Mostra caminho           ......" << endl;
        cout << "-- 5 Cópia                    ......" << endl;
        cout << "-- 6 Remove predecessor       ......" << endl;
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
            inserir(&A,'F');
            inserir(&A,'B');
            inserir(&A,'G');
            inserir(&A,'A');
            inserir(&A,'D');
            inserir(&A,'I');
            inserir(&A,'C');
            inserir(&A,'E');
            inserir(&A,'H');

            cout<<"Valor inserido com sucesso!"<<endl;
            system("pause");
            break;
        case 2:
            system("cls");
            cout<<"Mostrar pré-ordem:"<<endl;
            mostra_PreOrd(A);
            cout<<endl;
            cout<<"Mostrar ordem:"<<endl;
            mostra_OrdS(A);
            cout<<endl;
            cout<<"Mostrar pos-ordem:"<<endl;
            mostra_PosOrd(A);
            cout<<endl;
            cout<<"Mostrar horizontal:"<<endl;
            imprimir(A,1);
            cout<<endl;
            system("pause");
            break;
        case 3:
            system("cls");
            char num;
            cout<<"Informe um elemento para remover!";
            cin>>num;
            A=remover(A,num);
            system("pause");
            break;
        case 4:
            system("cls");
            cout<<"Informe um elemento para mostrar o caminho até ele!";
            cin>>num;
            mostra_caminho(A,num);
            cout<<endl;
            system("pause");
            break;
        case 5:
            system("cls");
            cout<<"Cópia criada!";
            C=copia(A,C);
            imprimir(C,1);
            cout<<endl;
            cout<<endl;
            cout<<"Original!";
            imprimir(A,1);
            cout<<endl;
            cout<<"Remova um elemento da arvore!";
            cin>>num;
            A=remover(A,num);
            cout<<"Cópia !"<<endl;
            imprimir(C,1);
            cout<<endl;
            cout<<"ORIGINAL POS REMOÇÃO !"<<endl;
            imprimir(A,1);
            cout<<endl;
            system("pause");
            break;
        case 6:
            system("cls");
            cout<<"Informe um número para descobrir o predecessor e remover: ";
            cin>>num;
            if(busca_valor(A,num))
            {
                imprimir(A,1);
                cout<<endl;

                char vet[total_nos(A)];
                simetrica(A,vet,0);
                cout<<"Predecessor do número: "<<endl;
                ordena(vet,total_nos(A));

                for(int i=0; i<total_nos(A); i++)
                {
                    if(vet[0]==num)
                        cout<<"O numero não tem predecessor!"<<endl;
                    else if(vet[i+1]==num)
                    {
                        num=vet[i];
                        cout<<vet[i]<<endl;
                    }
                }
                cout<<endl;
                A=remover(A,num);
                cout<<"Arvore depois de remover o predecessor do número:"<<endl;
                imprimir(A,1);
                cout<<endl;
            }
            else
                cout<<"O valor não existe na árvore!"<<endl;
            system("pause");
            break;
        }

    }
    while (menu != 0);

}


