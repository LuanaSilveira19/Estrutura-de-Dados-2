#include <iostream>
using namespace std;

#include "AVL.hpp"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0, num;
    arvore *A=NULL;

    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "...............Árvore AVL..........." << endl;
        cout << "-- 1 Inseir                   ......" << endl;
        cout << "-- 2 Mostrar                  ......" << endl;
        cout << "-- 3 Remover elemento         ......" << endl;
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
            int num;
            /*cout<<"Insira um valor: ";
            cin>>num;
            inserir(&A,num);
            cout<<"Valor inserido com sucesso!"<<endl;*/
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
            //mostraArvore(A,0);
           // mostra_PreOrd(A);
           cout<<"Teste: "<<endl;
           exibe_parag(A,0);
            cout<<endl;
            cout<<"Forma de árvore"<<endl;//não esta balanceando
            imprimir(A,0);
            cout<<endl;
            system("pause");
            break;
        case 3:
            system("cls");
            //int num;

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


        }

    }
    while (menu != 0);

}

