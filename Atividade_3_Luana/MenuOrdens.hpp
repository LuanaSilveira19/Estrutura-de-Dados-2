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

int altura_arvore(arvore *t)//vi com o monitor, a função está certa mas tem momentos que ela não funciona (vou ver em aula)
{
    if(t==NULL)
        return 1;
    else
    {
        int alt_sae= 1+ altura_arvore(t->sae);
        int alt_sad= 1+ altura_arvore(t->sad);
        if(alt_sae<alt_sad)
            return alt_sae;
        else if(alt_sae<alt_sad)
            return alt_sad;

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
/*arvore* remover(arvore *t, int num)//segundo teste
{

    if(t->info==num)
    {
        //verifficar quantos filhos tem
        if(t->sae==NULL && t->sad==NULL) //folha
        {
            delete(t);
            cout<<"Elemento removido!"<<endl;
            return NULL;
        }
        else
        {
            if(t->sae!=NULL && t->sad!=NULL) //2 filhos
            {
                arvore *aux= t->sae;
                while(aux->sad!=NULL)
                    aux= aux->sad;
                t->info= aux->info;
                aux->info= num;
                t->sae= remover(t->sae,num);
                return t;

            }
            else  //1 filho
            {
                arvore *aux;
                if(t->sae!=NULL)
                    aux= t->sae;
                else
                    aux= t->sad;
                delete(t);
                return aux;
            }

        }
    }
    else
    {
        if(num<t->info)
            t->sae= remover(t->sae,num);
        else
            t->sad= remover(t->sad,num);
        return t;
    }
}*/
arvore* limpar_tudo(arvore *t)
{
    while(!testa_vazia(t))
    {
        if(t->sae==NULL && t->sad==NULL)
        {
            delete(t);
           // cout<<"Elemento removido!"<<endl;
            return NULL;
        }
        else if(t->sae!=NULL)
            t->sae=limpar_tudo(t->sae);
        else
            t->sad=limpar_tudo(t->sad);
    }
      return t;

}
#endif
