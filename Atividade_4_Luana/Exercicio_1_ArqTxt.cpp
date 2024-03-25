#include <unistd.h>
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>

using namespace std;
#include "Arq_Txt.hpp"

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
        cout << "-- 4 Busca Valor              ......" << endl;
        cout << "-- 5 Altura                   ......" << endl;
        cout << "-- 6 Encontrar nível          ......" << endl;
        cout << "-- 7 Limpar tudo              ......" << endl;
        cout << "-- 8 Total de folhas          ......" << endl;
        cout << "-- 9 Maior nível              ......" << endl;
        cout << "-- 10 Verificar se é completa ......" << endl;
        cout << "-- 11 Exibir em paragrafação  ......" << endl;
        cout << "-- 12 Matriz da árvore        ......" << endl;
        cout << "-- 13 Ler arquivo texto       ......" << endl;
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
            //validar se tiver vazia
            //int valor;
            //cout<<"Insira um valor:";
            //cin>>valor;
            //inserir(&A,valor);
            cont++;
             /*inserir(&A,6);
             inserir(&A,8);
             inserir(&A,4);
             inserir(&A,5);
             inserir(&A,2);
             inserir(&A,3);
             inserir(&A,1);
             inserir(&A,9);
            // inserir(&A,10);
             //inserir(&A,12);
             inserir(&A,7);
             inserir(&A,6);*/

             inserir(&A,9);
             inserir(&A,4);
             inserir(&A,12);
             inserir(&A,3);
             inserir(&A,6);
             inserir(&A,14);
             inserir(&A,5);
             inserir(&A,7);


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
            if(cont>0)
            {

                cout<<"Informe um número para ser removido:";
                cin>>num;
                if(busca_valor(A,num))
                {
                    remover(&A,num);
                    cout<<"Elemento removido!"<<endl;
                }
                else
                    cout<<"Esse número não está na árvore!"<<endl;
            }
            else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;

            system("pause");
            break;
        case 4:
            system("cls");
            if(cont>0)
            {
                cout<<"Informe um número para buscar:";
                cin>>num;

                if(busca_valor(A,num))
                    cout<<"O valor está na árvore!"<<endl;
                else
                    cout<<"O valor NÃO está na árvore!"<<endl;
            }
            else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;

            system("pause");
            break;
        case 5:
            system("cls");
            if(cont>0)
            {
                cout<<"A altura da árvore é: "<<altura(A)<<endl;
                cout<<"A altura da sub_árvore esquerda é: "<<altura(A->sae)<<endl;
                cout<<"A altura da sub_árvore direita é: "<<altura(A->sad)<<endl;
            }
            else
                cout<<"Árvore vazia! Insira os elementos primeiro"<<endl;
            system("pause");
            break;
        case 6:
            system("cls");
            if(cont>0)
            {
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
        case 8:
            system("cls");

                cout<<"O total de folhas na árvore é: "<<total_folhas(A)<<endl;
            system("pause");
            break;
        case 9:
            system("cls");
            cout<<"O maior nível da árvore é: "<<(altura(A)-1)<<endl;
            cout<<"Os elementos desse nível são: ";
            elementos_maior_nivel(A,(altura(A)-1),0);
            cout<<endl;
            system("pause");
            break;
        case 10:
            system("cls");

            if( total_folhas(A) == qtd_ultimoNivel(A,(altura(A)-1),0))
                cout<<"A árvore É completa!"<<endl;
                else
                cout<<"A árvore NÃO É completa!"<<endl;


            system("pause");
            break;
        case 11:
            system("cls");
                cout<<"Paragrafação: "<<endl;
                exibe_parag(A,0);
            system("pause");
            break;
        case 13:
            system("cls");

            if (!arq.is_open())
            {
                cout << "Erro: não foi possível abrir o arquivo texto.\n";
                return 0;
            }

            while(!arq.eof())
            {
                linha = ""; //IMPORTANTE, sempre inicializar a string
                getline(arq, linha);
                strBuffer = stringstream(linha);
                strBuffer >> op;
                cout<<op<<endl;
                if(op == "inserir")//VER O PQ TA DUPLICANDO
                {
                    strBuffer >> num;
                    inserir(&A,num);
                }
                else if(op == "remover")
                {
                    strBuffer >> num;
                    if(busca_valor(A,num))
                        remover(&A,num);
                    else
                        cout<<"O valor NÃO está na árvore!"<<endl;
                }

            }

            usleep(10000);
            system("pause");
            break;
        case 12://inverti os case pq dava erro de jump
            system("cls");
                string mat1[1][4]={"IND|\t", "ESQ|\t", "VAL|\t","DIR|"};
                for(int i=0; i<1;i++){
                    for(int j=i; j<4;j++)
                        cout<<mat1[i][j];
                }
                cout<<endl;
                mostraM(A);
            system("pause");
            break;

        }

    }while (menu != 0);

}






