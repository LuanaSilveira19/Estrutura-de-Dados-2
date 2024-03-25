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
int FB(arvore *t){
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
int maior_subA(int a, int b){
    return (a>b)? a: b;
}
//rotação simples a direita
arvore *RSD_LL(arvore *t){
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
arvore *RSE_RR(arvore *t){
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
arvore *RDD_RL(arvore *t){
    t->sad= RSD_LL(t->sad);
    return RSE_RR(t);
}
//rotação dupla a esquerda (esquerda,direita) LR
arvore *RDE_LR(arvore *t){
    t->sae= RSE_RR(t->sae);
    return RSD_LL(t);
}
arvore *balancear(arvore *t){
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
    (*t)->Alt= maior_subA(altura((*t)->sae), altura((*t)->sad))+1;
    (*t)= balancear(*t);

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
/*arvore* remover(arvore **t, int num)//esse modelo não funcionou, ao tentar remover ele fecha o programa

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

    (*t)->Alt= maior_subA(altura((*t)->sae), altura((*t)->sad))+1;
    (*t)=balancear(*t);

    return *t;
}*/

//Ta imprimindo no formato de árvore só que na horizontal
void exibe_parag(arvore* t, int nivel)
{
    if(!testa_vazia(t))
    {
         if(altura(t)%2==0){
             for(int i=0; i<(altura(t)/2); i++)
                    cout<<"\t";
         cout<<"\n";
                    cout<<t->info;
                     // cout<<"\n";
                    exibe_parag(t->sae, nivel+1);

                    //exibe_parag(t->sad, nivel+1);
         }else{
             for(int i=0; i<(altura(t)/2)+1; i++)
                    cout<<"\t";
                    cout<<t->info;
         }
    }
}
void imprimir(arvore *t, int nivel){
    int i;
    if(t){
        imprimir(t->sad, nivel+1);
        cout<<"\n";
        for(i=0; i<nivel; i++)
            cout<<"\t";
        cout<<t->info;
        imprimir(t->sae, nivel+1);
    }
}


#endif

