#include <iostream>
using namespace std;

#include "MenuOrdens.hpp"
/*1.1 Encontrar a altura da sub-árvore esquerda e direita
1.2 Encontrar a altura da árvore
1.3 Limpar todos os nós da árvore, liberando as respectivas memórias.
1.4 Dado um determinado valor, se o mesmo estiver contido na árvore encontrar o nível que
ele se encontra.*/
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0, num;
    arvore *A=NULL;

    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "................Árvore.............." << endl;
        cout << "-- 1 Inseir                   ......" << endl;
        cout << "-- 2 Mostrar                  ......" << endl;
        cout << "-- 3 Remover elemento         ......" << endl;
        cout << "-- 4 Busca Valor              ......" << endl;
        cout << "-- 5 Altura                   ......" << endl;
        cout << "-- 6 Encontrar nível          ......" << endl;
        cout << "-- 7 Limpar tudo              ......" << endl;
        cout << "-- 0 Sair                   ......" << endl;
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
            //validar se tiver vazia
            //int valor;
            //cout<<"Insira um valor:";
            //cin>>valor;
            //inserir(&A,valor);
            cont++;
            //com essa sequência a altura funciona certo
           /*inserir(&A,6);
            inserir(&A,8);
            inserir(&A,4);
            inserir(&A,5);
            inserir(&A,2);
            inserir(&A,3);
            inserir(&A,1);
            inserir(&A,9);
            inserir(&A,7);
            inserir(&A,6);*/

            //com essa sequência a altura não funciona
            inserir(&A,40);
            inserir(&A,20);
            inserir(&A,32);
            inserir(&A,54);
            inserir(&A,70);
            inserir(&A,62);
            inserir(&A,61);
            inserir(&A,65);

            cout<<"Valor inserido com sucesso!"<<endl;
            system("pause");
            break;
        case 2:
            system("cls");
            if(cont>0)
            {
                cout<<"Árvore na pré-ordem: ";
                mostra_PreOrd(A);
                cout<<endl;
                cout<<"Árvore na ordem simétrica: ";
                mostra_OrdS(A);
                cout<<endl;
                cout<<"Árvore na pos-ordem: ";
                mostra_PosOrd(A);
                cout<<endl;
            }
            else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;
            system("pause");
            break;
        case 3:
            system("cls");
            if(cont>0){

            cout<<"Informe um número para ser removido:";
            cin>>num;
            if(busca_valor(A,num)){
                        remover(&A,num);
                    //A=remover(A,num);
                    cout<<"Elemento removido!"<<endl;
            }
            else
                cout<<"Esse número não está na árvore!"<<endl;
            }
             else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;

            //cout<<"Elemento: "<<remover(&A,num)<<endl;

            system("pause");
            break;
        case 4:
            system("cls");
            if(cont>0){
            cout<<"Informe um número para buscar:";
            cin>>num;

            if(busca_valor(A,num))
                cout<<"O valor está na árvore!"<<endl;
            else
                cout<<"O valor NÃO está na árvore!"<<endl;
            } else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;

            system("pause");
            break;
        case 5:
            system("cls");
            if(cont>0){//Não funciona com outros valores
            cout<<"A altura da árvore é: "<<altura_arvore(A)-1<<endl;
            cout<<"A altura da sub_árvore esquerda é: "<<altura_arvore(A->sae)<<endl;
            cout<<"A altura da sub_árvore direita é: "<<altura_arvore(A->sad)<<endl;
            }
             else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;
            system("pause");
            break;
        case 6:
            system("cls");
            if(cont>0){
                 cout<<"Informe um valor para encontrar o nível!";
            cin>>num;
            if(busca_valor(A,num))
                cout<<"Esse número está no nível: "<<nivel_no(A,num,0)<<endl;
            else
                cout<<"Esse valor não existe na árvore!"<<endl;
            }
            else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;
            system("pause");
            break;
        case 7:
            system("cls");
            A=limpar_tudo(A);
            //cont=0;
            cout<<"Árvore limpa!"<<endl;
            system("pause");
            break;



        }

    }
    while (menu != 0);

}
