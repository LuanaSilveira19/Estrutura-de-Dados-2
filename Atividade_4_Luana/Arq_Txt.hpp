#ifndef _HPP_ARVORE
#define _HPP_ARVORE

#include <iomanip>
typedef struct arv
{
    int info;
    arv *sae;
    arv *sad;
} arvore;
int testa_vazia(arvore *t)
{
    if(t == NULL)
        return 1;
    if(t->info == NULL)
        return 1;
    return 0;
}

void inserir(arvore **t, int num)
{
    if(*t == NULL)
    {
        *t = new arvore;
        (*t)->sae = NULL;
        (*t)->sad = NULL;
        (*t)->info = num;
    }

    else
    {
        if(num < (*t)->info)
            inserir(&(*t)->sae, num);
        else
            inserir(&(*t)->sad, num);

    }
}

void mostra_PreOrd(arvore *t)
{

    cout << "<";
    if(!testa_vazia(t))
    {
        cout << t->info;
        mostra_PreOrd(t->sae);
        mostra_PreOrd(t->sad);
    }
    cout << ">";


}
void mostra_OrdS(arvore *t)
{
    cout << "<";
    if(!testa_vazia(t))
    {
        mostra_OrdS(t->sae);
        cout << t->info;
        mostra_OrdS(t->sad);
    }
    cout << ">";
}
void mostra_PosOrd(arvore *t)
{
    cout << "<";
    if(!testa_vazia(t))
    {
        mostra_PosOrd(t->sae);
        mostra_PosOrd(t->sad);
        cout << t->info;
    }
    cout << ">";
}

arvore* remover(arvore **t, int num)
{

    if(num < (*t)->info)
        remover(&(*t)->sae, num);
    else if(num > (*t)->info)
        remover(&(*t)->sad, num);
    else
    {
        arvore *aux = *t;
//se for uma folha
        if(((*t)->sae == NULL) && ((*t)->sad == NULL))
        {
            delete(aux);
            (*t) = NULL;
        }
        else if((*t)->sae == NULL)
        {
//só tem filho a direita
            (*t) = (*t)->sad;
            aux->sad = NULL;
            delete(aux);
            aux = NULL;
        }
        else if((*t)->sad == NULL)
        {
//só tem filho a esquerda
            (*t) = (*t)->sae;
            aux->sae = NULL;
            delete(aux);
            aux = NULL;
        }
        else
        {
            //se possui 2 filhos
            aux = (*t)->sae;
            while(aux->sad != NULL)
            {
                aux = aux->sad;
            }
            (*t)->info = aux->info;
            aux->info = num;
            (*t)->sae = remover(&(*t)->sae, num);
        }
    }
    return *t;
}


bool busca_valor(arvore *t, int num)
{

    if(!testa_vazia(t))
    {

        if(t->info==num)
            return true;
        if(t->info>num)
            return busca_valor(t->sae, num);
        else
            return busca_valor(t->sad, num);
    }
}

int altura (arvore *t)
{
    if (t == NULL)
        return 0; // altura da árvore vazia
    else
    {
        int he = altura (t->sae);
        int hd = altura (t->sad);
        if (he < hd) return hd + 1;
        else return he + 1;
    }
}

int nivel_no(arvore *t, int num, int nivel)
{
    if(!testa_vazia(t))
    {
        //ver a questão quando existe número repetido
        if(t->info==num)
            return nivel;
        if(t->info>num)
            return nivel_no(t->sae, num, nivel+1);
        else
            return nivel_no(t->sad, num, nivel +1);
    }
}

arvore* limpar_tudo(arvore *t)
{
    while(!testa_vazia(t))
    {
        if(t->sae==NULL && t->sad==NULL)
        {
            delete(t);
            return NULL;
        }
        else if(t->sae!=NULL)
            t->sae=limpar_tudo(t->sae);
        else
            t->sad=limpar_tudo(t->sad);
    }
    return t;

}

int total_folhas(arvore *t)
{
    if(t==NULL)
        return 0;
    else if(t->sae==NULL && t->sad==NULL)
        return 1;
    else
        return total_folhas(t->sae)+total_folhas(t->sad);

}
void elementos_maior_nivel(arvore *t, int nivel, int cont)
{
    if(t)
    {
        if(nivel==cont)
            cout<<t->info<<", ";
        elementos_maior_nivel(t->sae,nivel,cont+1);
        elementos_maior_nivel(t->sad,nivel,cont+1);
    }
}

int qtd_ultimoNivel(arvore *t, int nivel, int cont)
{
    if(t)
    {
        if(nivel==cont)
            return 1;
        return qtd_ultimoNivel(t->sae,nivel,cont+1) +  qtd_ultimoNivel(t->sad,nivel,cont+1);
    }
}

void exibe_parag(arvore* t, int nivel)
{
    if(!testa_vazia(t))
    {

        for(int i=0; i<nivel; i++)
            cout<<".";
        cout<<t->info<<endl;
        exibe_parag(t->sae, nivel+1);//se pedir em outra ordem é só mudar
        exibe_parag(t->sad, nivel+1);
    }
}

int total_nos(arvore *t)
{
    if(t==NULL)
        return 0;
    else
        return 1+total_nos(t->sae)+total_nos(t->sad);
}
void matriz_arvore(arvore *t, int mat[][4], int indice=0)
{
    if(!testa_vazia(t))
    {
        int i=indice;
        mat[i][0]=i;
        mat[i][2]=t->info;
        if(t->sae){
            matriz_arvore(t->sae,mat,i+1);
             mat[i][1]=i+1;
        }
        else
            mat[i][1]=-1;

         if(t->sad){
            matriz_arvore(t->sad,mat,i+total_nos(t->sae)+1);
             mat[i][3]=i+1;
        }
        else
            mat[i][3]=-1;

    }
}

void mostraM(arvore *t)
{
    if(!testa_vazia(t))
    {
        int mat[total_nos(t)][4];
        matriz_arvore(t,mat);

        for(int i=0; i<total_nos(t); i++)
        {
            for(int j=0; j<4; j++){
                if(mat[i][j]==-1)
                     cout<<mat[i][j]<<" |\t";
                else
                cout<<mat[i][j]<<"  |\t";
            }

            cout<<endl;

        }
    }
}


#endif
