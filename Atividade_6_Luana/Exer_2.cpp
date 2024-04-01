#include <unistd.h>
#include<iostream>
#include<string>
#include <sstream>
#include <fstream>

using namespace std;
struct Alunos
{
    int matricula;
    string nome;
    float media;
    float frequencia;

};
#include "Struct_AVL.hpp"

void aprovados( arvore *t)
{
    if(!testa_vazia(t))
    {
        if(t->info.media>=6 && t->info.frequencia>=75)
        {
            cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", Méd: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]"<<endl;
        }
        aprovados(t->sae);
        aprovados(t->sad);
    }
}

void reprovados( arvore *t)
{
    if(!testa_vazia(t))
    {
        if(t->info.media<6 || t->info.frequencia<75)
        {
            cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", Méd: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]"<<endl;
        }
        reprovados(t->sae);
        reprovados(t->sad);
    }
}

void escreve_aprovados( arvore *t, std::ofstream& escreve)
{
    if(!testa_vazia(t))
    {
        if(t->info.media>=6 && t->info.frequencia>=75)
        {
            escreve << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", Méd: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]"<<endl;
        }
         escreve_aprovados(t->sae,escreve);
         escreve_aprovados(t->sad,escreve);
    }
}

void escreve_reprovados( arvore *t, std::ofstream& escreve)
{
    if(!testa_vazia(t))
    {
        if(t->info.media<6 || t->info.frequencia<75)
        {
            escreve << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", Méd: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]"<<endl;
        }
        escreve_reprovados(t->sae,escreve);
        escreve_reprovados(t->sad,escreve);
    }
}

int main()
{

    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0;
    float num;
    Alunos AL;
    arvore *A=NULL;
    string nome;
    stringstream strBuffer;
    string op, linha;
    ifstream arq ("entradaesaida.txt");

    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "................Árvore.............." << endl;
        cout << "-- 1 Inseir alunos            ......" << endl;
        cout << "-- 2 Mostrar alunos           ......" << endl;
        cout << "-- 3 Mostrar aprovados e reprovados." << endl;
        cout << "-- 4 Ler arquivo TXT          ......" << endl;
        cout << "-- 5 Escrever arquivo TXT     ......" << endl;
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
            AL.frequencia=98.2;
            AL.matricula=24;
            AL.media=6;
            AL.nome="Gustavo";
            inserir(&A,AL);

            AL.frequencia=80.2;
            AL.matricula=27;
            AL.media=8;
            AL.nome="Gabriel";
            inserir(&A,AL);


            /*cout<<"Insira o nome do aluno: ";
            cin>>AL.nome;
             cout<<"Insira a matricula do aluno: ";
            cin>>AL.matricula;
             cout<<"Insira a frequencia do aluno: ";
            cin>>AL.frequencia;
             cout<<"Insira a media do aluno: ";
            cin>>AL.media;
            inserir(&A,AL);*/


            cout<<"Valor inserido com sucesso!"<<endl;
            system("pause");
            break;

        case 2:
            system("cls");
            cout<<"Alunos: "<<endl;
            mostra_PreOrd(A);
            cout<<endl;
            imprimir(A,0);
            cout<<endl;
            system("pause");
            break;
        case 3:
            system("cls");
            cout<<"Alunos aprovados: "<<endl;
            aprovados(A);
            cout<<endl;
            cout<<"Alunos reprovados: "<<endl;
            reprovados(A);
            cout<<endl;

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
                    strBuffer >> num;
                    AL.frequencia=num;

                    strBuffer >> num;
                    AL.matricula=num;

                    strBuffer >> num;
                    AL.media=num;

                    strBuffer >> nome;
                    AL.nome=nome;

                    inserir(&A,AL);
                }
                else if(op == "alunos")
                {
                    cout<<"Alunos: "<<endl;
                    imprimir(A,1);
                    cout<<endl;
                }
                else if(op == "aprovados")
                {
                    cout<<"---------------------------------------"<<endl;
                    cout<<"Alunos aprovados: "<<endl;
                    aprovados(A);
                    cout<<endl;

                }
                else if(op == "reprovados")
                {
                    cout<<"---------------------------------------"<<endl;
                    cout<<"Alunos reprovados: "<<endl;
                    reprovados(A);
                    cout<<endl;

                }

            }

            usleep(10000);

            system("pause");
            break;
        case 5:
            system("cls");
            ofstream escreve;
            escreve.open("escreveStruct.txt", ios::out);

            if(escreve.is_open())
            {
                escreve<<"---------------------------------------"<<endl;
                escreve<<"Alunos aprovados: "<<endl;
                escreve_aprovados(A,escreve);

                escreve<<"---------------------------------------"<<endl;
                escreve<<"Alunos reprovados: "<<endl;
                escreve_reprovados(A,escreve);
                cout<<"Ok"<<endl;
            }
            escreve.close();
            system("pause");
            break;


        }
    }
    while (menu != 0);

}
