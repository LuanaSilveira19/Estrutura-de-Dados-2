#include <unistd.h>
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "TXT_FB.hpp"
void simetrica(arvore *t, int vet[], int indice=0)
{
    int i=indice;
    if(!testa_vazia(t))
    {
        simetrica(t->sae,vet,i+1);
        vet[i]=t->info;
        simetrica(t->sad,vet,i+total_nos(t->sae)+1);
    }
}
void ordena(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = i; j < tamanho; j++)
        {
            if (vetor[i] > vetor[j])
            {
                int temp = vetor[i];
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
    arvore *A=NULL, *aux=NULL, *A2=NULL;

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
        cout << "-- 4 Quantidade de n�s FB     ......" << endl;
        cout << "-- 5 Ancestrais e Descendentes ....." << endl;
        cout << "-- 6 Ler arquivo texto        ......" << endl;
        cout << "-- 7 Grau de um n�            ......" << endl;
        cout << "-- 8 Paragrafa��o             ......" << endl;
        cout << "-- 9 Elementos contidos no nivel ..." << endl;
        cout << "-- 10 �rvore geneal�gica          .." << endl;
        cout << "-- 11 Total                       .." << endl;
        cout << "-- 12 Verifica se � m�rfica       .." << endl;
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
            inserir(&A,1);
            inserir(&A,2);
            inserir(&A,3);
            inserir(&A,4);
            inserir(&A,5);
            inserir(&A,6);
            inserir(&A,7);

            inserir(&A2,10);
            inserir(&A2,20);
            inserir(&A2,30);
            inserir(&A2,40);
            inserir(&A2,50);
            inserir(&A2,60);
            inserir(&A2,70);


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
            cout<<"�rvore horizontal: ";
            imprimir(A2,1);
            cout<<endl;
            //se for usar essa fun��o fazer uma arvore aux como copia pra poder modificar
            /*cout<<endl;
            cout<<"�rvore ordem invertida: ";
            troca_arvore(A);
            cout<<endl;*/

            system("pause");
            break;
        case 3:
            system("cls");
            cout<<"Informe um n�mero para ser removido:";
            cin>>num;
            if(busca_valor(A,num))
            {
                A=remover(A,num);
                inserir(&aux,num);
                cout<<"Elemento removido!"<<endl;
                cout<<"Arvore aux com os elementos removidos!"<<endl;
                imprimir(aux,1);
                cout<<endl;

            }
            else
                cout<<"Esse n�mero n�o est� na �rvore!"<<endl;


            system("pause");
            break;
        case 4:
            system("cls");

            cout<<"Quantidade de n�s com FB = -1: "<<calcula_fb_Menos1(A)<<" n�s"<<endl;
            cout<<"Quantidade de n�s com FB = 0: "<<calcula_fb_zero(A)<<" n�s"<<endl;
            cout<<"Quantidade de n�s com FB = +1: "<<calcula_fb_Mais1(A)<<" n�s"<<endl;
            cout<<"�rvore horizontal: ";
            imprimir(A,1);
            cout<<endl;

            system("pause");
            break;

        case 5:
            system("cls");
            cout<<"Informe um n�mero para descobrir seus descendentes: ";
            cin>>num;
            if(busca_valor(A,num))
            {
                imprimir(retorna_busca(A,num),0);
                cout<<endl;

                cout<<"Ancestrais do n�:"<<endl;
                ancestrais(A,num);
                cout<<endl;
                cout<<"Descendentes do n�:"<<endl;
                descendentes(retorna_busca(A,num),num);
                cout<<endl;

                int vet[total_nos(A)];
                simetrica(A,vet,0);//mesmo mudando a ordem ele pega a mesma sequencia sempre
                cout<<"Predecessor do n�mero: "<<endl;
                ordena(vet,total_nos(A));

                for(int i=0; i<total_nos(A);i++)
                {
                    if(vet[0]==num)
                        cout<<"O numero n�o tem predecessor!"<<endl;
                    else if(vet[i+1]==num)
                        cout<<vet[i]<<endl;
                }
                cout<<endl;

            }
            else
                cout<<"O valor n�o existe na �rvore!"<<endl;

            system("pause");
            break;
        case 6:
            system("cls");

            if (!arq.is_open())
            {
                cout << "Erro: n�o foi poss�vel abrir o arquivo texto.\n";
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
                        cout<<"O valor N�O est� na �rvore!"<<endl;
                }
                else if(op == "Mostrar")
                {
                    strBuffer >> num;
                    if(num==1)
                    {
                        cout<<"Pr�-ordem: ";
                        mostra_PreOrd(A);
                        cout<<endl;
                        imprimir(A,0);
                        cout<<endl;
                    }
                    else if(num==2)
                    {
                        cout<<"Ordem sim�trica: ";
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

            cout<<"Grau dos n�s da arvore"<<endl;
            grau(A);
            system("pause");
            break;
        case 8:
            system("cls");

            cout<<"Paragrafa��o: "<<endl;
            exibe_parag(A,0);
            system("pause");
            break;
        case 9:
            system("cls");

            cout<<"Informe um n�vel para procurar os elementos: ";
            cin>>num;
            if(num>-1 && num<=(altura(A)-1))
            {
                cout<<"Elementos contidos no n�vel "<<num<<" da �rvore: ";
                elementos_do_nivel(A,num,0);
                cout<<endl;

            }
            else
                cout<<"Esse n�vel n�o existe na �rvore!"<<endl;

            system("pause");
            break;
        case 10:
            system("cls");
            cout<<"Arvore geneal�gica: "<<endl;
            cout<<"Informe um n�mero para saber o parentesco: ";
            cin>>num;
                arvore_genealogica(A,num);
                cout<<endl;
                imprimir(A,1);
                  cout<<endl;

            system("pause");
            break;
         case 11:
            system("cls");
            cout<<"Total de n�s: "<<total_nos(A)<<endl;
            cout<<"Total de n�s folhas: "<<total_folhas(A)<<endl;
            cout<<"Total de n�s com 1 filho: "<< total_nos1f(A)<<endl;
            cout<<"Total de n�s com 2 filhos: "<<total_nos2f(A)<<endl;
            system("pause");
            break;
         case 12:
            system("cls");
            if(verifica_morfica(A,A2)==true)
                cout<<"As �rvores S�O M�RFICAS!"<<endl;
            else
                  cout<<"As �rvores N�O S�O M�RFICAS!"<<endl;
            system("pause");
            break;
        }

    }
    while (menu != 0);

}


