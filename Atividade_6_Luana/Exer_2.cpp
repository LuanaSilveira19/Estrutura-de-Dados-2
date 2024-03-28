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

void aprovados( arvore *t){
      if(!testa_vazia(t))
    {
        if(t->info.media>=6 && t->info.frequencia>=75){
              cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", Méd: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]"<<endl;
        }
        aprovados(t->sae);
        aprovados(t->sad);
    }
}

void reprovados( arvore *t){
      if(!testa_vazia(t))
    {
        if(t->info.media<6 || t->info.frequencia<75){
              cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", Méd: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]"<<endl;
        }
        reprovados(t->sae);
        reprovados(t->sad);
    }
}
int main()
{

    setlocale(LC_ALL, "Portuguese");
    int menu = -1, cont=0, num;
    Alunos AL;
    arvore *A=NULL;

    do
    {
        system("cls");
        cout << "...................................." << endl;
        cout << "................Árvore.............." << endl;
        cout << "-- 1 Inseir alunos            ......" << endl;
        cout << "-- 2 Mostrar alunos           ......" << endl;
        cout << "-- 3 Mostrar aprovados e reprovados." << endl;
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
            AL.frequencia=99.2;
            AL.matricula=2;
            AL.media=6;
            AL.nome="Giovana";
            inserir(&A,AL);

            AL.frequencia=90.2;
            AL.matricula=26;
            AL.media=8;
            AL.nome="Luana";
            inserir(&A,AL);

            AL.frequencia=78.2;
            AL.matricula=14;
            AL.media=2;
            AL.nome="Lucas";
            inserir(&A,AL);

            AL.frequencia=78.2;
            AL.matricula=39;
            AL.media=6;
            AL.nome="Carlos";
            inserir(&A,AL);

            AL.frequencia=60.2;
            AL.matricula=22;
            AL.media=7;
            AL.nome="Laura";
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


        }
        }while (menu != 0);

    }
