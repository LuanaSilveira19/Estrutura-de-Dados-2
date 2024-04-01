#ifndef _HPP_ARVORE
#define _HPP_ARVORE

#include <iomanip>
typedef struct arv
{
    string info;
    arv *sae;
    arv *sad;
    int Alt;
} arvore;

int testa_vazia(arvore *t)
{
    if(t == NULL)
        return 1;
    if(t->info == " ")
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

bool busca_valor(arvore *t, string num)
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

arvore *retorna_busca(arvore *t, string num)
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
int nivel_no(arvore *t, string num, int nivel)
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

void inserir(arvore **t, string num)
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

arvore* remover(arvore *t, string num)//com essa função diferente da do professor funcionou certo
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
//sempre quando for uma função pra calcular um int usar esse padrão
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
arvore* func_pai(arvore* t, string num)
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
/*void ancestrais(arvore *t,string num)
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
}*/
void descendentes(arvore *t, string num)
{

    if(!testa_vazia(t))
    {
        if(num!=t->info)
            cout << t->info<<", ";
        descendentes(t->sae, num);
        descendentes(t->sad, num);
    }

}

void grau(arvore *t)
{


    if(!testa_vazia(t))
    {
        if(t->sae !=NULL && t->sad !=NULL)
            cout <<"Nó: "<<t->info<<" com grau 2"<<endl;
        else if(t->sae !=NULL)
            cout <<"Nó: "<<t->info<<" com grau 1"<<endl;
        else if(t->sad !=NULL)
            cout <<"Nó: "<<t->info<<" com grau 1"<<endl;
        else
            cout <<"Nó: "<<t->info<<" com grau 0"<<endl;
        grau(t->sae);
        grau(t->sad);
    }



}

void exibe_parag(arvore* t, int nivel)
{
    if(!testa_vazia(t))
    {

        cout<<setw(15)<<setfill(' ');
        for(int i=0; i<nivel; i++)
            cout<<".";
        cout<<t->info<<endl;
        exibe_parag(t->sae, nivel+1);//se pedir em outra ordem é só mudar
        exibe_parag(t->sad, nivel+1);
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

void arvore_genealogica(arvore *t, string num)
{

    arvore *aux=NULL, *filhos=NULL, *avo=NULL;

    if(num==t->info)
    {
        cout<<"O elemento é o raiz e não possui pai, nem tios e nem avôs!"<<endl;
        cout<<"Seu filho a esquerda é o: "<<t->sae->info<<endl;
        cout<<"Seu filho a direita é o: "<<t->sad->info<<endl;
    }
    else
    {
        aux=func_pai(t,num);
        avo=func_pai(t,aux->info);
        cout<<"O pai do elemento é: "<<aux->info<<endl;
        if(aux->sae!=NULL && aux->sad != NULL)
        {
            if(aux->sae->info != num)
            {
                cout<<"O irmão do elemento é: "<<aux->sae->info<<endl;
                if(aux->sae->sae!=NULL && aux->sae->sad!=NULL )
                    cout<<"Os sobrinhos desse elemento são: "<< aux->sae->sae->info<<", "<<aux->sae->sad->info<<endl;
                else if(aux->sae->sae!=NULL)
                    cout<<"O sobrinho desse elemento é: "<<aux->sae->sae->info<<endl;
                else
                    cout<<"O sobrinho desse elemento é: "<<aux->sae->sad->info<<endl;

            }

            else
            {
                cout<<"O irmão do elemento é: "<<aux->sad->info<<endl;
                if(aux->sad->sae!=NULL && aux->sad->sad!=NULL )
                    cout<<"Os sobrinhos desse elemento são: "<< aux->sad->sae->info<<", "<<aux->sad->sad->info<<endl;
                else if(aux->sad->sae!=NULL)
                    cout<<"O sobrinho desse elemento é: "<<aux->sad->sae->info<<endl;
                else
                    cout<<"O sobrinho desse elemento é: "<<aux->sad->sad->info<<endl;
            }

        }
        else
            cout<<"O elemento não tem irmão e nem sobrinhos!"<<endl;

        filhos= retorna_busca(t,num);
        if(filhos->sae!=NULL && filhos->sad != NULL)
            cout<<"Os filhos desse elemento são: "<<filhos->sae->info<<", "<<filhos->sad->info<<endl;
        else if(filhos->sae!=NULL)
            cout<<"O filho desse elemento é: "<<filhos->sae->info<<endl;
        else if(filhos->sad!=NULL)
            cout<<"O filho desse elemento é: "<<filhos->sad->info<<endl;
        else
            cout<<"O elemento não posui filhos!"<<endl;
        if(aux->info!=t->info)
        {
            cout<<"O avô desse nó é: "<<avo->info<<endl;

            if(avo->sae->info != aux->info)
            {
                cout<<"O tio do nó é: "<<avo->sae->info<<endl;
                if(avo->sae->sae!=NULL)
                {
                    cout<<"Os primos desse elemento são: ";
                    descendentes(retorna_busca(t,avo->sae->info),avo->sae->info);
                    cout<<endl;
                }
                else
                    cout<<"O nó não possui primos!"<<endl;

            }
            else    if(avo->sad->info != aux->info)
            {
                cout<<"O tio do nó é: "<<avo->sad->info<<endl;//mostrar os primos
                if(avo->sae->sad!=NULL)
                {
                    cout<<"Os primos desse elemento são: ";
                    descendentes(retorna_busca(t,avo->sad->info),avo->sad->info);
                    cout<<endl;
                }
                else
                    cout<<"O nó não possui primos!"<<endl;
            }
            else
                cout<<"O nó não possui tio!"<<endl;//mostrar os primos
        }
        else
            cout<<"O elemento não possui avô, tio ou primos!"<<endl;
    }
}
int total_nos(arvore *t)
{
    if(t==NULL)
        return 0;
    else
        return 1+ total_nos(t->sae)+total_nos(t->sad);

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
int total_nos1f(arvore *t)
{
    if(t==NULL)
        return 0;
    else if(t->sae!=NULL && t->sad==NULL)
        return total_nos1f(t->sae)+ total_nos1f(t->sad)+1;
    else if(t->sad!=NULL && t->sae==NULL)
        return total_nos1f(t->sae)+ total_nos1f(t->sad)+1;
    else
        return total_nos1f(t->sae)+ total_nos1f(t->sad);

}
int total_nos2f(arvore *t)
{
    if(t==NULL)
        return 0;
    else if(t->sae!=NULL && t->sad!=NULL)
        return total_nos2f(t->sae) + total_nos2f(t->sad)+1;
    else
        return total_nos2f(t->sae) + total_nos2f(t->sad);

}

void mostra_caminho(arvore *t, string num)
{
    if(!testa_vazia(t))
    {

        if(t->info==num)
            cout<<t->info;
        else if(num>t->info)
        {
            cout<<t->info<<", ";
            mostra_caminho(t->sad, num);
        }
        else if(num<t->info)
        {
            cout<<t->info<<", ";
            mostra_caminho(t->sae, num);
        }
    }
}

void inserir2(arvore **t, string num)
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
}
arvore *copia(arvore *a, arvore *b)
{
    if(!testa_vazia(a))
    {
        inserir2(&b,a->info);//tem que ter uma função sem o balanceamento pra fazer a copia
        b=copia(a->sae,b);
        b=copia(a->sad,b);
    }
    return b;
}


#endif
