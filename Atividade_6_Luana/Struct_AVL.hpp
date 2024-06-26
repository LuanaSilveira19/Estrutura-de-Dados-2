#ifndef _HPP_ARVORE
#define _HPP_ARVORE

#include <iomanip>
typedef struct arv
{
    Alunos info;
    arv *sae;
    arv *sad;
    arv *pai;
    int Alt;
} arvore;

int testa_vazia(arvore *t)
{
    if(t == NULL)
        return 1;
    if(t->info.matricula == NULL)
        return 1;
    return 0;
}

void mostra_PreOrd(arvore *t)
{

    cout << "<";
    if(!testa_vazia(t))
    {
        cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", M�d: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]";
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
         cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", M�d: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]";
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
       cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", M�d: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]";
    }
    cout << ">";
}

bool busca_valor(arvore *t, int num)
{

    if(!testa_vazia(t))
    {

        if(t->info.matricula==num)
            return true;
        if(t->info.matricula>num)
            return busca_valor(t->sae, num);
        else
            return busca_valor(t->sad, num);
    }
}

arvore *retorna_busca(arvore *t, int num)
{

    if(!testa_vazia(t))
    {

        if(t->info.matricula==num)
            return t;
        if(t->info.matricula>num)
            return retorna_busca(t->sae, num);
        else
            return retorna_busca(t->sad, num);
    }
}

int altura (arvore *t)
{
    if (t == NULL)
        return 0; // altura da �rvore vazia
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
        //ver a quest�o quando existe n�mero repetido
        if(t->info.matricula==num)
            return nivel;
        if(t->info.matricula>num)
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
//rota��o simples a direita
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

//rota��o simples a esquerda
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

//rota��o dupla a direita (direita, esquerda) RL
arvore *RDD_RL(arvore *t)
{
    t->sad= RSD_LL(t->sad);
    return RSE_RR(t);
}
//rota��o dupla a esquerda (esquerda,direita) LR
arvore *RDE_LR(arvore *t)
{
    t->sae= RSE_RR(t->sae);
    return RSD_LL(t);
}
arvore *balancear(arvore *t)
{
    //Rota��o a esquerda
    if(FB(t)< -1 && FB(t->sad)<=0)
        t=RSE_RR(t);
    //Rota��o a direita
    else if(FB(t)>1 && FB(t->sae)>=0)
        t=RSD_LL(t);
    //Rota��o dupla a esquerda
    else if(FB(t)>1 && FB(t->sae)<0)
        t=RDE_LR(t);
    //Rota��o dupla a direita
    else if(FB(t)< -1 && FB(t->sad)>0)
        t=RDD_RL(t);

    return t;
}

void inserir(arvore **t, Alunos num)
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
        if(num.matricula < (*t)->info.matricula )
            inserir(&(*t)->sae, num);
        else
            inserir(&(*t)->sad, num);

    }
    (*t)->Alt= maior_subA(altura((*t)->sae), altura((*t)->sad))+1;
    (*t)= balancear(*t);

    // return t;
}

arvore* remover(arvore *t, Alunos num)//com essa fun��o diferente da do professor funcionou certo
{

    if(t->info.matricula ==num.matricula )
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
        if(num.matricula <t->info.matricula )
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
        cout<<"\n\n";
        for(i=0; i<nivel; i++)
            cout<<"\t";
            cout << "[Mat: "<<t->info.matricula<<", Nome: "<<t->info.nome<<", M�d: "<<t->info.media<<", Freq: "<<t->info.frequencia<<"]";
        imprimir(t->sae, nivel+1);
    }
}

int calcula_fb_zero(arvore *t)
{
    if(t)
    {
        if(t==NULL)
            return 0;
        if(FB(t)==0)
        return (calcula_fb_zero(t->sae)+ calcula_fb_zero(t->sad))+1;
        else
            return (calcula_fb_zero(t->sae)+ calcula_fb_zero(t->sad));
    }


}
int calcula_fb_Menos1(arvore *t)
{
    if(t)
    {
        if(t==NULL)
            return 0;
        if(FB(t)==-1)
        return (calcula_fb_Menos1(t->sae)+ calcula_fb_Menos1(t->sad))+1;
        else
            return (calcula_fb_Menos1(t->sae)+ calcula_fb_Menos1(t->sad));
    }


}
//sempre quando for uma fun��o pra calcular um int usar esse padr�o
int calcula_fb_Mais1(arvore *t)
{
    if(t)
    {
        if(t==NULL)
            return 0;
        if(FB(t)==1)
        return (calcula_fb_Mais1(t->sae)+ calcula_fb_Mais1(t->sad))+1;
        else
            return (calcula_fb_Mais1(t->sae)+ calcula_fb_Mais1(t->sad));
    }


}

#endif



