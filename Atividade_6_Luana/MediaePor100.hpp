#ifndef _HPP_ARVORE
#define _HPP_ARVORE

#include <iomanip>
typedef struct arv
{
    int info;
    arv *sae;
    arv *sad;
    int Alt;
} arvore;

int testa_vazia(arvore *t)
{
    if(t == NULL)
        return 1;
    if(t->info == NULL)
        return 1;
    return 0;
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

arvore *retorna_busca(arvore *t, int num)
{

    if(!testa_vazia(t))
    {

        if(t->info==num)
            return t;
        if(t->info>num)
            return retorna_busca(t->sae, num);
        else
            return retorna_busca(t->sad, num);
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
int FB(arvore *t)
{
    if(t)
        return (altura(t->sae)-altura(t->sad));
    else
        return 0;
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
int maior_subA(int a, int b)
{
    return (a>b)? a: b;
}
//rotação simples a direita
arvore *RSD_LL(arvore *t)
{
    arvore *y, *f;
    y= t->sae;
    f= y->sad;

    y->sad= t;
    t->sae= f;

    t->Alt= maior_subA(altura(t->sae), altura(t->sad))+1;
    y->Alt= maior_subA(altura(y->sae), altura(y->sad))+1;
    return y;//retorna a nova raiz
}

//rotação simples a esquerda
arvore *RSE_RR(arvore *t)
{
    arvore *y, *f;
    y= t->sad;
    f= y->sae;

    y->sae= t;
    t->sad= f;

    t->Alt= maior_subA(altura(t->sae), altura(t->sad))+1;
    y->Alt= maior_subA(altura(y->sae),altura(y->sad))+1;
    return y;//retorna a nova raiz
}

//rotação dupla a direita (direita, esquerda) RL
arvore *RDD_RL(arvore *t)
{
    t->sad= RSD_LL(t->sad);
    return RSE_RR(t);
}
//rotação dupla a esquerda (esquerda,direita) LR
arvore *RDE_LR(arvore *t)
{
    t->sae= RSE_RR(t->sae);
    return RSD_LL(t);
}
arvore *balancear(arvore *t)
{
    //Rotação a esquerda
    if(FB(t)< -1 && FB(t->sad)<=0)
        t=RSE_RR(t);
    //Rotação a direita
    else if(FB(t)>1 && FB(t->sae)>=0)
        t=RSD_LL(t);
    //Rotação dupla a esquerda
    else if(FB(t)>1 && FB(t->sae)<0)
        t=RDE_LR(t);
    //Rotação dupla a direita
    else if(FB(t)< -1 && FB(t->sad)>0)
        t=RDD_RL(t);

    return t;
}

void inserir(arvore **t, int num)
{
    if(*t == NULL)
    {
        *t = new arvore;
        (*t)->sae = NULL;
        (*t)->sad = NULL;
        (*t)->info = num;
        (*t)->Alt = 0;

    }

    else
    {
        if(num < (*t)->info)
            inserir(&(*t)->sae, num);
        else
            inserir(&(*t)->sad, num);

    }

   // (*t)->Alt= maior_subA(altura((*t)->sae), altura((*t)->sad))+1;
   // (*t)= balancear(*t);


    // return t;
}

arvore* remover(arvore *t, int num)//com essa função diferente da do professor funcionou certo
{

    if(t->info==num)
    {
        //verifficar quantos filhos tem
        if(t->sae==NULL && t->sad==NULL) //folha
        {
            delete(t);
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

    }

    t->Alt= maior_subA(altura(t->sae), altura(t->sad))+1;
    t= balancear(t);

    return t;
}

void imprimir(arvore *t, int nivel)
{
    int i;
    if(t)
    {
        imprimir(t->sad, nivel+1);
        cout<<"\n";
        for(i=0; i<nivel; i++)
            cout<<"\t";
        cout<<t->info;
        imprimir(t->sae, nivel+1);
    }
}

arvore* func_pai(arvore* t, int num)
{
    arvore* pai = NULL;
    while (t != NULL && t->info != num)
    {
        pai = t;
        if (num < t->info)
            t = t->sae;
        else
            t = t->sad;
    }
    // if(num==t->info)
    //    return t;
    return pai;
}
void ancestrais(arvore *t,int num)
{
    int numAx;
    if(num != t->info)
    {
        numAx=func_pai(t,num)->info;
        while(numAx!=t->info)
        {
            cout<<numAx<<", ";
            numAx=func_pai(t,numAx)->info;
        }
        cout<<numAx;

    }
    else
    {
        cout<<"O número informado é o elemento raiz e não possui ancestral"<<endl;
    }
}
void descendentes(arvore *t, int num)
{

    if(!testa_vazia(t))
    {
        if(num!=t->info)
            cout << t->info<<", ";
        descendentes(t->sae, num);
        descendentes(t->sad, num);
    }

}

void elementos_do_nivel(arvore *t, int nivel, int cont)
{
    if(t)
    {
        if(nivel==cont)
            cout<<t->info<<", ";
        elementos_do_nivel(t->sae,nivel,cont+1);
        elementos_do_nivel(t->sad,nivel,cont+1);
    }
}

int total_nos(arvore *t)
{
    if(t==NULL)
        return 0;
    else
        return 1+ total_nos(t->sae)+total_nos(t->sad);

}

int soma_elemento(arvore *t)
{
    if(t==NULL)
        return 0;
    else
    {
        return t->info + soma_elemento(t->sae)+ soma_elemento(t->sad);
    }
}

void mostra_pares(arvore *t)
{
    if(t)
    {
        if(t->info%2==0)
            cout<<t->info<<", ";

        mostra_pares(t->sae);
        mostra_pares(t->sad);
    }
}
void mostra_impares(arvore *t)
{
    if(t)
    {
        if(t->info%2!=0)
            cout<<t->info<<", ";

        mostra_impares(t->sae);
        mostra_impares(t->sad);
    }
}
int total_par(arvore *t)
{
    if(t==NULL)
        return 0;
    else
    {
        if(t->info%2==0)
            return 1+ total_par(t->sae)+total_par(t->sad);
        else
            return total_par(t->sae)+total_par(t->sad);
    }
}
int total_impar(arvore *t)
{
    if(t==NULL)
        return 0;
    else
    {
        if(t->info%2!=0)
            return 1+ total_impar(t->sae)+total_impar(t->sad);
        else
            return total_impar(t->sae)+total_impar(t->sad);
    }


}

int elemento_nivelacima(arvore *t, int nivel, int num,int cont)
{

    if(t->info==num)
        return true;
    if(t->info>num)
    {
        if(nivel==cont)
            return t->info;
        else
            return elemento_nivelacima(t->sae,nivel,num,cont+1);
    }
    else
    {
        if(nivel==cont)
            return t->info;
        else
            return elemento_nivelacima(t->sad,nivel,num,cont+1);
    }

}

int maior_elemento(arvore *t)
{
    while(t->sad!=NULL)
    {
        return maior_elemento(t->sad);
    }
    return t->info;
}
int menor_elemento(arvore *t)
{
    while(t->sae!=NULL)
    {
        return menor_elemento(t->sae);
    }
    return t->info;
}

void mostraMaioresCres(arvore * t, int v)
{

    if(!testa_vazia(t))
    {
        mostraMaioresCres(t->sae,v);
        if(t->info>=v && t->info%2!=0)
            cout << t->info<<", ";
        mostraMaioresCres(t->sad,v);
    }
}
void mostraMaioresDecres(arvore * t, int v)
{

    if(!testa_vazia(t))
    {
        mostraMaioresDecres(t->sad,v);
        if(t->info>=v && t->info%2!=0)
            cout << t->info<<", ";
        mostraMaioresDecres(t->sae,v);
    }
}

int qtd_maiores(arvore *t, int num)//se pedir pra mostrar é só adaptar
{
    if(t==NULL)
        return 0;
    else if(t->info>num)
        return qtd_maiores(t->sae,num) + qtd_maiores(t->sad,num)+1;
    else qtd_maiores(t->sae,num) + qtd_maiores(t->sad,num);
}

bool extritamente_Bin(arvore *t){

        if(t->sae !=NULL && t->sad !=NULL )
        return true;
        if(t->sae ==NULL && t->sad ==NULL )
        return extritamente_Bin(t->sae) && extritamente_Bin(t->sad);

        return false;

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

int total_folhas_do_nivel(arvore *t, int nivel, int cont)
{
    if(t==NULL)
        return 0;
    else if(t->sae==NULL && t->sad==NULL && nivel==cont)
        return 1;
    else
        return total_folhas_do_nivel(t->sae,nivel,cont+1)+total_folhas_do_nivel(t->sad,nivel,cont+1);

}

#endif



