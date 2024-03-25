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
        cout << "................�rvore.............." << endl;
        cout << "-- 1 Inseir                   ......" << endl;
        cout << "-- 2 Mostrar                  ......" << endl;
        cout << "-- 3 Remover elemento         ......" << endl;
        cout << "-- 4 Busca Valor              ......" << endl;
        cout << "-- 5 Altura                   ......" << endl;
        cout << "-- 6 Encontrar n�vel          ......" << endl;
        cout << "-- 7 Limpar tudo              ......" << endl;
        cout << "-- 8 Total de folhas          ......" << endl;
        cout << "-- 9 Maior n�vel              ......" << endl;
        cout << "-- 10 Verificar se � completa ......" << endl;
        cout << "-- 11 Exibir em paragrafa��o  ......" << endl;
        cout << "-- 12 Matriz da �rvore        ......" << endl;
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
                cout<<"�rvore na pr�-ordem: ";
                mostra_PreOrd(A);
                cout<<endl;
                cout<<"�rvore na ordem sim�trica: ";
                mostra_OrdS(A);
                cout<<endl;
                cout<<"�rvore na pos-ordem: ";
                mostra_PosOrd(A);
                cout<<endl;
            }
            else
                cout<<"�rvore vazia! Insira os elementos primeiro"<<endl;
            system("pause");
            break;
        case 3:
            system("cls");
            if(cont>0)
            {

                cout<<"Informe um n�mero para ser removido:";
                cin>>num;
                if(busca_valor(A,num))
                {
                    remover(&A,num);
                    cout<<"Elemento removido!"<<endl;
                }
                else
                    cout<<"Esse n�mero n�o est� na �rvore!"<<endl;
            }
            else
                cout<<"�rvore vazia! Insira os elementos primeiro"<<endl;

            system("pause");
            break;
        case 4:
            system("cls");
            if(cont>0)
            {
                cout<<"Informe um n�mero para buscar:";
                cin>>num;

                if(busca_valor(A,num))
                    cout<<"O valor est� na �rvore!"<<endl;
                else
                    cout<<"O valor N�O est� na �rvore!"<<endl;
            }
            else
                cout<<"�rvore vazia! Insira os elementos primeiro"<<endl;

            system("pause");
            break;
        case 5:
            system("cls");
            if(cont>0)
            {
                cout<<"A altura da �rvore �: "<<altura(A)<<endl;
                cout<<"A altura da sub_�rvore esquerda �: "<<altura(A->sae)<<endl;
                cout<<"A altura da sub_�rvore direita �: "<<altura(A->sad)<<endl;
            }
            else
                cout<<"�rvore vazia! Insira os elementos primeiro"<<endl;
            system("pause");
            break;
        case 6:
            system("cls");
            if(cont>0)
            {
                cout<<"Informe um valor para encontrar o n�vel!";
                cin>>num;
                if(busca_valor(A,num))
                    cout<<"Esse n�mero est� no n�vel: "<<nivel_no(A,num,0)<<endl;
                else
                    cout<<"Esse valor n�o existe na �rvore!"<<endl;
            }
            else
                cout<<"�rvore vazia! Insira os elementos primeiro"<<endl;
            system("pause");
            break;
        case 7:
            system("cls");
            A=limpar_tudo(A);
            //cont=0;
            cout<<"�rvore limpa!"<<endl;
            system("pause");
            break;
        case 8:
            system("cls");

                cout<<"O total de folhas na �rvore �: "<<total_folhas(A)<<endl;
            system("pause");
            break;
        case 9:
            system("cls");
            cout<<"O maior n�vel da �rvore �: "<<(altura(A)-1)<<endl;
            cout<<"Os elementos desse n�vel s�o: ";
            elementos_maior_nivel(A,(altura(A)-1),0);
            cout<<endl;
            system("pause");
            break;
        case 10:
            system("cls");

            if( total_folhas(A) == qtd_ultimoNivel(A,(altura(A)-1),0))
                cout<<"A �rvore � completa!"<<endl;
                else
                cout<<"A �rvore N�O � completa!"<<endl;


            system("pause");
            break;
        case 11:
            system("cls");
                cout<<"Paragrafa��o: "<<endl;
                exibe_parag(A,0);
            system("pause");
            break;
        case 13:
            system("cls");

            if (!arq.is_open())
            {
                cout << "Erro: n�o foi poss�vel abrir o arquivo texto.\n";
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
                        cout<<"O valor N�O est� na �rvore!"<<endl;
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






