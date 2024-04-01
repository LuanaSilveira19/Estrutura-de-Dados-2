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
        cout << "................Árvore.............." << endl;
        cout << "-- 1 Inseir                   ......" << endl;
        cout << "-- 2 Mostrar                  ......" << endl;
        cout << "-- 3 Remover elemento         ......" << endl;
        cout << "-- 4 Quantidade de nós FB     ......" << endl;
        cout << "-- 5 Ancestrais e Descendentes ....." << endl;
        cout << "-- 6 Ler arquivo texto        ......" << endl;
        cout << "-- 7 Grau de um nó            ......" << endl;
        cout << "-- 8 Paragrafação             ......" << endl;
        cout << "-- 9 Elementos contidos no nivel ..." << endl;
        cout << "-- 10 Árvore genealógica          .." << endl;
        cout << "-- 11 Total                       .." << endl;
        cout << "-- 12 Verifica se é mórfica       .." << endl;
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
            cout<<"Árvore na pré-ordem: ";
            mostra_PreOrd(A);
            cout<<endl;
            cout<<"Árvore horizontal: ";
            imprimir(A,1);
            cout<<endl;
            cout<<"Árvore horizontal: ";
            imprimir(A2,1);
            cout<<endl;
            //se for usar essa função fazer uma arvore aux como copia pra poder modificar
            /*cout<<endl;
            cout<<"Árvore ordem invertida: ";
            troca_arvore(A);
            cout<<endl;*/

            system("pause");
            break;
        case 3:
            system("cls");
            cout<<"Informe um número para ser removido:";
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
                cout<<"Esse número não está na árvore!"<<endl;


            system("pause");
            break;
        case 4:
            system("cls");

            cout<<"Quantidade de nós com FB = -1: "<<calcula_fb_Menos1(A)<<" nós"<<endl;
            cout<<"Quantidade de nós com FB = 0: "<<calcula_fb_zero(A)<<" nós"<<endl;
            cout<<"Quantidade de nós com FB = +1: "<<calcula_fb_Mais1(A)<<" nós"<<endl;
            cout<<"Árvore horizontal: ";
            imprimir(A,1);
            cout<<endl;

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

                int vet[total_nos(A)];
                simetrica(A,vet,0);//mesmo mudando a ordem ele pega a mesma sequencia sempre
                cout<<"Predecessor do número: "<<endl;
                ordena(vet,total_nos(A));

                for(int i=0; i<total_nos(A);i++)
                {
                    if(vet[0]==num)
                        cout<<"O numero não tem predecessor!"<<endl;
                    else if(vet[i+1]==num)
                        cout<<vet[i]<<endl;
                }
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
        case 8:
            system("cls");

            cout<<"Paragrafação: "<<endl;
            exibe_parag(A,0);
            system("pause");
            break;
        case 9:
            system("cls");

            cout<<"Informe um nível para procurar os elementos: ";
            cin>>num;
            if(num>-1 && num<=(altura(A)-1))
            {
                cout<<"Elementos contidos no nível "<<num<<" da árvore: ";
                elementos_do_nivel(A,num,0);
                cout<<endl;

            }
            else
                cout<<"Esse nível não existe na árvore!"<<endl;

            system("pause");
            break;
        case 10:
            system("cls");
            cout<<"Arvore genealógica: "<<endl;
            cout<<"Informe um número para saber o parentesco: ";
            cin>>num;
                arvore_genealogica(A,num);
                cout<<endl;
                imprimir(A,1);
                  cout<<endl;

            system("pause");
            break;
         case 11:
            system("cls");
            cout<<"Total de nós: "<<total_nos(A)<<endl;
            cout<<"Total de nós folhas: "<<total_folhas(A)<<endl;
            cout<<"Total de nós com 1 filho: "<< total_nos1f(A)<<endl;
            cout<<"Total de nós com 2 filhos: "<<total_nos2f(A)<<endl;
            system("pause");
            break;
         case 12:
            system("cls");
            if(verifica_morfica(A,A2)==true)
                cout<<"As árvores SÃO MÓRFICAS!"<<endl;
            else
                  cout<<"As árvores NÃO SÃO MÓRFICAS!"<<endl;
            system("pause");
            break;
        }

    }
    while (menu != 0);

}


