#include <unistd.h>
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "MediaePor100.hpp"

int main()
{

    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0, num, n;
    arvore *A=NULL;

    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "................�rvore.............." << endl;
        cout << "-- 1 Inseir                   ......" << endl;
        cout << "-- 2 Mostrar                  ......" << endl;
        cout << "-- 3 Remover elemento         ......" << endl;
        cout << "-- 4 Soma, media e porcentagem ....." << endl;
        cout << "-- 5 Impares e pares          ......" << endl;
        cout << "-- 6 N�veis a cima ou abaixo  ......" << endl;
        cout << "-- 7 Maiores crescentes       ......" << endl;
        cout << "-- 8 QTD maiores que x        ......" << endl;
        cout << "-- 9 Extritamente bin�ria?    ......" << endl;
        cout << "-- 10 Quase completa?         ......" << endl;
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
            inserir(&A,23);
            inserir(&A,30);
            inserir(&A,47);
            inserir(&A,51);
            inserir(&A,60);
            inserir(&A,75);
            inserir(&A,80);
            inserir(&A,99);

            cout<<"Valor inserido com sucesso!"<<endl;
            system("pause");
            break;
        case 2:
            system("cls");
            cout<<"�rvore na pr�-ordem: ";
            mostra_PreOrd(A);
            cout<<endl;
            cout<<"�rvore horizontal: ";
            imprimir(A,1);
            cout<<endl;
            cout<<"Maior elemento: "<<maior_elemento(A)<<endl;
            cout<<"Menor elemento: "<<menor_elemento(A)<<endl;

            system("pause");
            break;
        case 3:
            system("cls");
            cout<<"Informe um n�mero para ser removido:";
            cin>>num;
            if(busca_valor(A,num))
            {
                A=remover(A,num);
                cout<<"Elemento removido!"<<endl;
            }
            else
                cout<<"Esse n�mero n�o est� na �rvore!"<<endl;


            system("pause");
            break;
        case 4:
            system("cls");
            cout<<"Soma de todos os elementos da �rvore: "<<soma_elemento(A)<<endl;
            cout<<"Soma dos elementos menores que a raiz: "<<soma_elemento(A->sae)<<endl;
            cout<<"Soma dos elementos maiores que a raiz: "<<soma_elemento(A->sad)<<endl;
            cout<<"M�dia dos elementos: "<<soma_elemento(A)/total_nos(A)<<endl;
            cout<<"Porcentagem dos elementos da arvore: "<<total_nos(A)/100.0<<endl;

            system("pause");
            break;
        case 5:
            system("cls");
            cout<<"Numeros pares: ";
            mostra_pares(A);
            cout<<endl;
            cout<<"Numeros impares: ";
            mostra_impares(A);
            cout<<endl;
            cout<<"Total de n�meros pares: "<<total_par(A)<<endl;
            cout<<"Total de n�meros impares: "<<total_impar(A)<<endl;
            system("pause");
            break;
        case 6:
            system("cls");

            cout<<"Informe o n�mero base: ";
            cin>>num;
            cout<<"Informe quantos n�veis acima dele deve se buscar o elemento: ";
            cin>>n;
            if(nivel_no(A,num,0)-n<0 || nivel_no(A,num,0)-n>(altura(A)-1))
                cout<<"O n�vel informado n�o existe!"<<endl;
            else
            {
                cout<<"O elemento que est� a "<< n <<" n�veis a cima do "<<num <<" �: "<<elemento_nivelacima(A,(nivel_no(A,num,0)-n),num,0)<<endl;
                cout<<"Elementos contidos no mesmo n�vel: ";
                elementos_do_nivel(A,(nivel_no(A,num,0)-n),0);
                cout<<endl;
            }
            system("pause");
            break;
        case 7:
            system("cls");
            cout<<"Digite um n�mero!"<<endl;
            cin>>num;
            if(busca_valor(A,num))
            {
                cout<<"N�meros impares maiores que o valor, em ordem crescente!"<<endl;
                cout<<"V= "<<num<<" -> ";
                mostraMaioresCres(A,num);
                cout<<endl;
                cout<<"N�meros impares maiores que o valor, em ordem decrescente!"<<endl;
                cout<<"V= "<<num<<" -> ";
                mostraMaioresDecres(A,num);
                cout<<endl;

            }
            else
                cout<<"O n�mero informado n�o existe!"<<endl;
            system("pause");
            break;

        case 8:
            system("cls");
            cout<<"Digite um n�mero!"<<endl;
            cin>>num;
            if(busca_valor(A,num))
            {
                cout<<"Quantidade de elementos maiores que "<<num<<": "<<qtd_maiores(A,num)<<" n�s";
                cout<<endl;

            }
            else
                cout<<"O n�mero informado n�o existe!"<<endl;
            system("pause");
            break;
         case 9:
            system("cls");

            if(extritamente_Bin(A))
            cout<<"A �rvore � extritamente bin�ria!"<<endl;
            else
                cout<<"A �rvore n�o � extritamente bin�ria!"<<endl;//vai acontecer s� se n�o for AVL
            system("pause");
        break;
             case 10:
            system("cls");

            if(total_folhas(A)==(total_folhas_do_nivel(A,altura(A)-1,0)+total_folhas_do_nivel(A,altura(A)-2,0)))//ver a quest�o se ela pender pra um lado s�
            cout<<"A �rvore � quase completa ou completa!"<<endl;
            else
                cout<<"A �rvore n�o � quase completa!"<<endl;
            system("pause");
            break;

        }

    }
    while (menu != 0);

}


