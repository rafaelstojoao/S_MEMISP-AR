//
//  functions.cpp
//  S_MEMISP+AR
//
//  Created by Rafael Stoffalette João on 1/8/15.
//  Copyright (c) 2015 Rafael Stoffalette João. All rights reserved.
//
#include "arquivos.h"
#include "functions.h"


listaSequenciasFrequetes *seq_freq =  new listaSequenciasFrequetes;


void wait_on_enter(){ // Função que Aguanda um comando para continuar a execução (botão enter)
    std::string dummy;
    std::cout << "\n Pressione a tecla Enter para continuar..." << std::endl;
    std::getline(std::cin, dummy);
}


void inicializaDado(tipoItem *i){    i->proximoItem = NULL;    i->item = "";   i->item_suporte = 0.0; return; }

void inicializaDado(tipoItemset *it){
it->proximoItemset = NULL;  it->primeiroItem = NULL; it->suporteItemset = 0.0; it->tamanhoItemset = 0;  return; }

void inicializaDado(tipoSequencia *s){
s->proximaSequencia = NULL; s->primeiroItemset = NULL; s->suporteSequencia = 0.0; s->tamanhoSequencia = 0; return; }




void insereItemItemset(tipoItem *it, tipoItemset *e){ //insere um item em um itemset
    
//    cout << "\n Inserir " << it->item << " em ";
//    imprimeitemset(e);
    int contnumitem = 0;
    tipoItem *aux = e->primeiroItem;
    tipoItem *novoItem = new tipoItem; inicializaItem(novoItem);
    if(!aux){
        
        novoItem->item = it->item;
        novoItem->item_suporte = it->item_suporte;
        e->primeiroItem = novoItem;
        it->proximoItem=NULL;
        e->tamanhoItemset++;
        //imprimeitemset(e);
        
    }
    else{
        
        while(aux->proximoItem != NULL && contnumitem < e->tamanhoItemset ){
                contnumitem++;
                if(aux->proximoItem) aux = aux->proximoItem;
        }
        aux->proximoItem = it;
        it->proximoItem = NULL;
        e->tamanhoItemset++;
    }
    
    
    
    return;
}



void insereItemsetSequencia(tipoItemset *e, tipoSequencia *s){ //insere um itemset em uma sequencia
    
    tipoItemset *aux = s->primeiroItemset;
    if(!aux){
        s->primeiroItemset = e;
        e->proximoItemset = NULL;
        s->tamanhoSequencia++;
    }
    else{
        while(aux->proximoItemset != NULL) aux = aux->proximoItemset;
        aux->proximoItemset = e;
        e->proximoItemset = NULL;
        s->tamanhoSequencia++;
    }
    
    return;
}



void insereItemLista_Itens_Frequentes(tipoItem *i, lista_de_Itens *lf){
    
    //cout << "\ninserindo o elemento  na lista : " << i->it;
    //cout << " \n - " << i->it << " - " << i->i_suporte;
    tipoItem *novoItem = new tipoItem;
    inicializaDado(novoItem);
    novoItem->item_suporte = i->item_suporte;
    novoItem->proximoItem = NULL;
    novoItem->item = i->item;
    
    
    if(!lf->cabeca){
        lf->cabeca = novoItem;
        
    }else{
        tipoItem *aux =  new tipoItem;
        aux = lf->cabeca;
        
        
        
        while(aux->proximoItem) {
            aux = aux->proximoItem;
        }
        aux->proximoItem = novoItem;
    }
    lf->tamanho ++;
    
    return;
}
/******************////**********************//******************////**********************//******************////**********************/


string imprimeitemsetArq(tipoItemset *e){ // Imprime os itens contidos em um itemset e
    tipoItem *aux =  e->primeiroItem;
    string itemsetstr;
    itemsetstr = "(";
    int cont =1;
    while(aux != NULL && e->tamanhoItemset >= cont){
        cont++;
          itemsetstr.append(aux->item);
        if(aux->proximoItem)itemsetstr.append(",");
        aux = aux->proximoItem;
    }
    itemsetstr.append(")");
    return itemsetstr;
}


string imprimeSequenciaArq(tipoSequencia *s){ // Percorre a sequencia s e imprime cada um de seus itemsets
    tipoItemset *aux =  s->primeiroItemset;
    string sequenciastr;
    sequenciastr = "<";
    int cont =1;
    while(aux != NULL && s->tamanhoSequencia >= cont){
        cont++;
        sequenciastr.append(imprimeitemsetArq(aux));
        aux = aux->proximoItemset;
    }
    
    sequenciastr.append(">");
    return sequenciastr;
}


void imprimeitemset(tipoItemset *e){ // Imprime os itens contidos em um itemset e
    tipoItem *aux =  e->primeiroItem;
    
    cout << "(";
    int cont =1;
    while(aux != NULL && e->tamanhoItemset >= cont){
        cont++;
        cout <<aux->item;  if(aux->proximoItem)cout << ",";
        aux = aux->proximoItem;
    }
    cout << ")";
    return;
}


void imprimeSequencia(tipoSequencia *s){ // Percorre a sequencia s e imprime cada um de seus itemsets
    tipoItemset *aux =  s->primeiroItemset;
    
    cout << "<";
    int cont =1;
    while(aux != NULL && s->tamanhoSequencia >= cont){
        cont++;
        imprimeitemset(aux);
        aux = aux->proximoItemset;
    }
    
    cout << ">";
    return;
}

void imprimeMDB(memorydb *m){
    tipoSequencia *cab = new tipoSequencia;
    cab = m->inicioMDB;

    cout << "\n \tMDB: \n ";
    cout <<"\n----------------------------------------------------";
    
    while(cab != NULL){
        cout << "\n| sequencia: ";
        imprimeSequencia(cab);
        cout << "\n|\t\t\t [ " <<cab->tamanhoSequencia << " itemsets ]";
        cout <<"\n----------------------------------------------------";
        
        cab = cab->proximaSequencia;
    }
    if (cab == NULL) cout << "\n fim da MDB";
    cout <<"\n----------------------------------------------------\n";
}



int busca_e1_em_e2(tipoItemset *e1, tipoItemset *e2){
    int pos =1;
    
//    cout << "\n Buscando "; imprimeitemset(e1); cout << " Em "; imprimeitemset(e2);
//    cout << " ["<< e1->tamanhoItemset << "]";
    
    if(e1->tamanhoItemset > e2->tamanhoItemset) return -1;
    
    tipoItem *i1x = e1->primeiroItem;
    tipoItem *i21 = e2->primeiroItem;
    int cont_em_e1 =1;
    int cont_em_e2 =1;
    
    while(cont_em_e2 <= e2->tamanhoItemset && cont_em_e1 <= e1->tamanhoItemset){
       // cout << "\n\t Comparando " << i1x->item << " com " << i21->item;
        if(i1x->item.compare(i21->item) == 0){
            pos = cont_em_e2;
            cont_em_e1++;
         //   cout <<" o item "<< i1x->item << " foi encontrado em " << cont_em_e2;
            if(i1x->proximoItem){
                i1x = i1x->proximoItem;
            }
        }
        
        
        if (i21->proximoItem) i21 = i21->proximoItem;
        cont_em_e2++;
    }
//    cout << " -- - sai do while";
//    
//    cout << "\n\t dados de saida";
//    cout << " \n Cont_em_e1 = " <<cont_em_e1 << " e tamanho  de e1 = " << e1->tamanhoItemset   ;
//    
    if(cont_em_e1 > e1->tamanhoItemset) return pos;
    
    
    else return -1;
}




int buscaS1EmS2(sequencia *s1, sequencia *s2){
    int pos = -1;
    int posDeE1 = -1;
    tipoItemset *e1 = s1->primeiroItemset;
    tipoItemset *e2 = s2->primeiroItemset;
    int cont_em_e1 = 1, cont_em_e2 = 1;
    
    if(s1->tamanhoSequencia > s2->tamanhoSequencia) return -1;
    
    while(cont_em_e1 <= s1->tamanhoSequencia && cont_em_e2 <= s2->tamanhoSequencia){
       
        posDeE1 = busca_e1_em_e2(e1,e2);
        
        while(posDeE1 == -1 && e2->proximoItemset && cont_em_e2 < s2->tamanhoSequencia){
            pos+= e2->tamanhoItemset;
            e2 = e2->proximoItemset;
            cont_em_e2++;
            posDeE1 = busca_e1_em_e2(e1,e2);
        }//fazer a busca de e1 até o fim de s2 se for preciso...
        //verificar na saida do while se posDeE1 nao for -1 é pq encontrou o e1 em s2.
        //se encontrou é preciso incrementar e1 e e2 e refazer a busca
        //porém se e1 é o ultimo (ou unico) encontrei todo s1
       
        
        if(posDeE1 != -1){ // encontrei o itemset
            if(e1->proximoItemset && cont_em_e1 < s1->tamanhoSequencia){

                cont_em_e1++;
                e1 = e1->proximoItemset;
                pos+=e2->tamanhoItemset;
            }else{ //o ultimo itemset de s1 foi encontrado
            
                pos+=posDeE1;
              return pos +1;
            }
            
        }else{ // nao encontrei o itemset significa que cheguei ao fim de s2
            if(cont_em_e2 >= s2->tamanhoSequencia){
               // cout <<"\n Fim de s2 e e1 nao foi encontrado";
                return -1;
            
            }
        }
        e2 = e2->proximoItemset;
        cont_em_e2++;
    }
    
        
        
    return -1;
}







int buscaS1EmS2_outraversao(sequencia *s1, sequencia *s2){
    
    if(!s1 || !s2) return -1;
    tipoItemset *e1 = s1->primeiroItemset;
    tipoItemset *e2 = s2->primeiroItemset;
    int cont_e1 = 0, cont_e2 =0;
    while(e1 && e2 && cont_e1 <=s1->tamanhoSequencia && cont_e2 <= s2->tamanhoSequencia){// inicio while 1
        cont_e1++; cont_e2++;
        if(e1->tamanhoItemset > e2->tamanhoItemset){// inicio if 2
            e2 = e2->proximoItemset;
        }// fim if 2
        else{ //inicio else 1
            tipoItem *i1 = e1->primeiroItem;
            tipoItem *i2 = e2->primeiroItem;
            while(i1 && i2){ // inicio while 1
                cout << "\n \tcomparando " << i1->item << " com " << i2->item;
                if(i1->item.compare(i2->item) == 0){// inicio if 3
                    cout << "\n item encontrado";
                    
                    
                    if(i1->proximoItem){//inicio if 4
                        if(i2->proximoItem){// inicio if 5
                            i1 = i1->proximoItem;
                            i2 = i2->proximoItem;
                        }// fim if 5
                        else{// inicio else 2
                        
                            if(e1->proximoItemset){// inicio if 6
                                
                            }// fim if 6
                        }//fim else 2
                    }// fim if 4
                    
                    
                    
                    
                    
                    
                } // fim if 3
                i2= i2->proximoItem;
            }// fim while 2
        }//fim else 1
    }// fim while 1
    
    
    
    
    
return 1;
}

int buscaS1EmS2_ultimaversaofuncionando(sequencia *s1, sequencia *s2){
    
    cout  << "Dentro do procedimento buscaS1emS2";
    if(s2->tamanhoSequencia < s1->tamanhoSequencia) return -1;
    cout << "\n\n -> Buscando "; imprimeSequencia(s1); cout << " em "; imprimeSequencia(s2);
    
    
    int cont = 1,  contItEmS1 =  1;
    itemset *e1 = s1->primeiroItemset;
    itemset *e2 = s2->primeiroItemset;
    item *i1 = new item;
    item *i2 = new item;
    int cont1, cont2 ;
    int pos =1, s2_total=1;
    
    while(e1 && (e2 && cont <= s2->tamanhoSequencia)){
        
        i1 = e1->primeiroItem;
        i2 = e2->primeiroItem;
        cont1 = cont2 = 1;
      //  cout << "\n\n \t\tbuscando "; imprimeitemset(e1); cout << " em "; imprimeitemset(e2);
       // cout << " itemset " << cont << " de " << s2->tamanhoSequencia;
        
        
        while(i1 && i2 && cont1 <= e1->tamanhoItemset && cont2 <= e2->tamanhoItemset){
            //cout << "\n \tcomparando " << i1->item << " com " << i2->item;
            if(i1->item.compare(i2->item)==0){
              //  cout << "\n item encontrado  na posicao" << cont2;
                if(i1->proximoItem != NULL) {
                    i1 = i1->proximoItem;
                    
                }
                cont1++;
            }
            i2 = i2->proximoItem;
            cont2++;
            s2_total++;
            pos++;
        
        if(cont1 >= e1->tamanhoItemset){
         //   cout << " - Itemset de e1 todo percorrido";
            if(e1->proximoItemset && e2->tamanhoItemset >= cont2){
                cont1 = 1;
                pos += (e2->tamanhoItemset - cont2)+1;
                e1= e1->proximoItemset;
            }
            else{
                return pos -1;
            }
            
        }
        
        cont++;
        if(e2->proximoItemset && contItEmS1 < s1->tamanhoSequencia) {
            e2  =    e2->proximoItemset;
          ///  cout << "\n novo itemset selecionado: "; imprimeitemset(e2);
        }
        else{ // chegou ao fim de s1 e precisa retornar o pos;
            
            return pos -1;
        }
        }}
    
    if(!e1) {
        return pos-1;
    }
    
    else
        return -1;
    
}



int buscaS1EmS2_meu(tipoSequencia *s1, tipoSequencia *s2){
    int posEncontrado   = 1 ;
    int it_atual_s1     = 0;
    int it_atual_s2     = 0;
    int i_atual_it1     = 0;
    int i_atual_it2     = 0;
    int itemsetAchado   = 0;
    
    if(s1->tamanhoSequencia <= s2->tamanhoSequencia){
        
        cout << "\n\n\n buscando "; imprimeSequencia(s1);  cout << " ["<< s1->tamanhoSequencia <<"] em ";
        imprimeSequencia(s2); cout  << "["<< s2->tamanhoSequencia << "]";
        tipoItemset *it1 = s1->primeiroItemset;
        tipoItemset *it2 = s2->primeiroItemset;
        it_atual_s1 = 1;
        it_atual_s2 = 0;
        
        while(it2 != NULL && it1 != NULL && it_atual_s2 <= s1->tamanhoSequencia && it_atual_s1 <= s2->tamanhoSequencia){
       
            
        while(it2->tamanhoItemset < it1->tamanhoItemset && it_atual_s1 <= s2->tamanhoSequencia){
            it_atual_s1++;
            it2 = it2->proximoItemset;
            posEncontrado += it2->tamanhoItemset;
            cout << "itemset"; imprimeitemset(it2); cout << " pequeno demais para comparar a "; imprimeitemset(it1);
        }
        
        
        it_atual_s2++;
        cout <<"\n itemset [" << it_atual_s1 << "] de s1 selecionado: ";  imprimeitemset(it1);
        cout <<"\n itemset [" << it_atual_s2 << "] de s2 selecionado: ";  imprimeitemset(it2);
        
        //selecionado os itemsets agora começa a busca dos itens.
        //se nao estou no fim do s2
            tipoItem *i1 = it1->primeiroItem;
            tipoItem *i2 = it2->primeiroItem;
            i_atual_it1 = 1;
            i_atual_it2 = 1;
            itemsetAchado = 0;
        
            while(i_atual_it1 <= it1->tamanhoItemset && i_atual_it2 < it2->tamanhoItemset && itemsetAchado == 0 && i1 != NULL && i2 != NULL){
                cout << "\n comparar o item na pos [" << i_atual_it1<<"] de it1 com o item na pos ["<<i_atual_it2 << "] de it2";
            
                cout<< "\n comparando itens: " << i1->item << " com "<< i2->item;
            
                if(i1->item.compare(i2->item)== 0){
              
                if(i1->proximoItem != NULL) {
                    i_atual_it1++;
                    i1=i1->proximoItem;
                }
                else{
                    itemsetAchado = 1;
                }
            }
            
            if(i2->proximoItem != NULL && i_atual_it2 <it2->tamanhoItemset )
                    i2 = i2->proximoItem;
            i_atual_it2++;
            posEncontrado++;
            cout << "\n incrementei posencontrado: " <<posEncontrado;
            
        }//fim while compara intens
        
        if(itemsetAchado == 1){
            cout << "\n o itemset foi achado";
            itemsetAchado = 0;
            
            //verificar se a sequencia foi achada também
            if(it_atual_s1 >= s1->tamanhoSequencia){
                cout<< "\n sequencia achada";
                return posEncontrado -1;
            }
            else
            if(it1->proximoItemset != NULL){
                posEncontrado += (it2->tamanhoItemset - i_atual_it2);
                cout << "\n na posicao: " << posEncontrado ;
                cout << " - porem existem mais itemsets a serem buscados";
                it1 = it1->proximoItemset;
            }
        }
        if(it2->proximoItemset != NULL) it2 = it2->proximoItemset;
    }
    }//fim if(s1->tamanhoSequencia <= s2->tamanhoSequencia)...
    else cout << "\n tamanhos incompativeis";
    return -1; //caso a execução atinja esse ponto, significa que s1 não foi encontrada em s2, portanto return -1

}

int buscaS1EmS2_bkp(tipoSequencia *s1, tipoSequencia *s2){
    

    if(s2->tamanhoSequencia < s1->tamanhoSequencia) return -1;
    
    cout <<  "\n buscando "; imprimeSequencia(s1); imprimeSequencia(s2);
    int cont =1;
    tipoItemset *e1 = s1->primeiroItemset;
    tipoItemset *e2 = s2->primeiroItemset;
    tipoItem *i1 = new tipoItem;
    tipoItem *i2 = new tipoItem;
    int cont1, cont2 ;
    int pos =1, s2_total=1;
    
    while(e1 && (e2 && cont <= s2->tamanhoSequencia)){
        cout <<  "\n buscando "; imprimeSequencia(s1); imprimeitemset(e2);
        
        i1 = e1->primeiroItem;
        i2 = e2->primeiroItem;
        cont1 = cont2 =1;
        
        while(i1 && i2 && (cont1 <= e1->tamanhoItemset) && (cont2 <= e2->tamanhoItemset)){
            cout <<  "\ncomparando  " << i1->item << " com  " << i2->item;
            if(i1->item.compare(i2->item)==0){
                cout << "\nitem " << i1->item << " achado";
                if(i1->proximoItem != NULL) i1 = i1->proximoItem;
                cont1++;
               
                
            }
            
            i2 = i2->proximoItem;
           
            cont2++;
            s2_total++;
            pos++;
        }
        
        
        if(cont1 >= e1->tamanhoItemset){
            
            if(e1->proximoItemset && e2->tamanhoItemset >= cont2) pos += (e2->tamanhoItemset - cont2)+1;
            e1= e1->proximoItemset;
             cout << "  ---- proximo itemset de e1";
            
        }
        
        cont++;
        
        e2  =    e2->proximoItemset;
         cout << "  ---- proximo itemset de e2";
    }
    if(!e1) {
        return pos-1;
    }
    
    else
        return -1;
    
}

int buscaItemSequencia(string c, tipoSequencia *s){
    tipoItemset *aux = new tipoItemset;
    aux = s->primeiroItemset;
    int contPos = 0;
    int tamSeq =1;
    
    // cout << "\n Buscando o item ("<< c << ") na sequencia  ";
    // imprimeSequencia(s);
    
    while(aux && tamSeq <= s->tamanhoSequencia){
        tamSeq++;
        
        item *i = new item;
        i= aux->primeiroItem;
        
        while(i){
            contPos++;
            if(c.compare(i->item)==0) return contPos;
            i=i->proximoItem;
        }
        aux=aux->proximoItemset;
    }
    return -1;
}



float calculaSuporte(int type, tipoItem *i, tipoItemset *e, tipoSequencia *s, memorydb *m){

    int count = 0;
    int contSeq = 0;
    float suporte =0.0;
    tipoSequencia *cab = new tipoSequencia;
    cab = m->inicioMDB;
    
    //cout << "calculo do suporte de:"; imprimeSequencia(s);
    
    
    if(type == 1){// item
        string c = i->item;
        
        while(cab != NULL){
            contSeq++;
            if(buscaItemSequencia(c,cab) != -1){
                count++;
            }
            cab = cab->proximaSequencia;
        }
        suporte = (float)count/(float)contSeq;
        
        
    }
    
    if(type == 2){// itemset
        tipoItemset *e_aux = new tipoItemset;
        tipoItemset *e_s2 = new tipoItemset;
        e_aux = e;
        tipoItem *i_s1 = new tipoItem;
        tipoItem *i_s2 =  new tipoItem;
        int posEmS2 =1, posEmS1 = 1;
        int contSup =0;
        int qtdItemstSeq=0;
        int achou =0;
        
        tipoSequencia *s_aux = new tipoSequencia;
        s_aux = m->inicioMDB;
        e_s2 = s_aux->primeiroItemset; // primeiro itemset de s2
        
        while(s_aux != NULL){ // percorrrer todas as sequencias de MDB
            e_s2 = s_aux->primeiroItemset;
            qtdItemstSeq = 1;
            contSeq++;
            
            
            while((e_s2 != NULL && qtdItemstSeq <= s_aux->tamanhoSequencia) && (achou ==0)){
                // imprimeitemset(e_s2);
                
                
                while((e_aux->tamanhoItemset > e_s2->tamanhoItemset) && (e_s2 != NULL) && (qtdItemstSeq <= s_aux->tamanhoSequencia)) {
                    qtdItemstSeq++;
                    e_s2 = e_s2->proximoItemset; //procurando possivel itemset candidato
                }
                
                if(qtdItemstSeq <= s_aux->tamanhoSequencia && (achou ==0)){
                    i_s1 = e_aux->primeiroItem;
                    i_s2 = e_s2->primeiroItem;
                    posEmS2 = 1;
                    posEmS1 = 1;
                    
                    while((i_s1 != NULL) && (posEmS2 <= e_s2->tamanhoItemset)){
                        
                        if (i_s1->item.compare(i_s2->item)==0){
                            i_s1=i_s1->proximoItem;
                            posEmS1++;
                        }
                        
                        if(i_s2->proximoItem != NULL) i_s2=i_s2->proximoItem;
                        posEmS2++;
                    }
                    
                    
                    if(posEmS1  == e_aux->tamanhoItemset + 1) {
                        contSup++;
                        achou = 1;
                        qtdItemstSeq = s_aux->tamanhoSequencia+1;
                        //imprimeSequencia(s_aux);
                        
                        
                        
                    }// se achou pula pra proxima sequencia
                    
                    
                    else if(qtdItemstSeq <= s_aux->tamanhoSequencia){
                        qtdItemstSeq++;
                        e_s2 = e_s2->proximoItemset;
                    }
                }}
            
            if(achou == 0) {
                s_aux = s_aux->proximaSequencia;
            }
            else{
                achou =0;
                count++;
                s_aux = s_aux->proximaSequencia;
            }
            
            
        }
        
        //fazer verificaSubsequencia e criar a sequencia com itemset unico
        
        
        
    }
    if(type == 3){// sequencia
        tipoSequencia *s_aux = new tipoSequencia;
        s_aux = m->inicioMDB;
        
        
        while(s_aux != NULL){
            if(buscaS1EmS2(s,s_aux)!= -1){
                count++;
            }
            s_aux=s_aux->proximaSequencia;
            contSeq++;
        }
        
    }
    
    suporte = (float)count/(float)contSeq;
    //printf("\n\t %d ocorrencia(s). Suporte %f ",count,suporte);
     //cout  << "\n\n\n\tBusca realizada em "<< contSeq <<" sequencias na MDB\n";
    
    return suporte;
}


float calculaSuporteSequencia(tipoSequencia *s, memorydb *m){
    
    int count = 0;
    int contSeq = 0;
    float suporte =0.0;
    tipoSequencia *cab = new tipoSequencia;
    cab = m->inicioMDB;
    
    cout << "\n\t\tcalculo do suporte de:"; imprimeSequencia(s);
    // cout <<" - tamanho = " <<s->tamanhoSequencia;
    
    
        tipoSequencia *s_aux;
        s_aux = m->inicioMDB;
        
        
        while(s_aux != NULL){
            
            if(buscaS1EmS2(s,s_aux)!= -1){
                count++;
                
            }
            s_aux=s_aux->proximaSequencia;
            contSeq++;
        }
        
    
    
    suporte = (float)count/(float)contSeq;
    printf("\n\t %d ocorrencia(s). Suporte %f ",count,suporte);
    cout  << "\n\n\n\tBusca realizada em "<< contSeq <<" sequencias na MDB\n";
    
    return suporte;
}



int buscaItemLista_de_Frequentes(tipoItem *itm, lista_de_Itens *lf){
    
    
    
    tipoItem *aux = new tipoItem; inicializaDado(aux);
    aux = lf->cabeca;
    int contPos = 0;
    tipoItem *i = new tipoItem;
    
    while(aux){
        
        i= aux;
        
        while(i && contPos <= lf->tamanho ){
            contPos++;
            //cout << " - " << i->it ;
            if(itm->item.compare(i->item)==0) return contPos;
            else i=i->proximoItem;
        }
        aux=aux->proximoItem;
    }
    return -1;
}


void find_all_frequent_items(lista_de_Itens *lf, memorydb *m){
    
    tipoSequencia *cab = new tipoSequencia;
    cab = m->inicioMDB;
    tipoItemset *aux = new tipoItemset;
    tipoItem *it_aux =  new tipoItem;
    tipoItem *i_f =  new tipoItem;
    
    while(cab != NULL){
               aux =  cab->primeiroItemset;
        
        // cout << "<";
        int cont =1;
        while(aux != NULL && cab->tamanhoSequencia >= cont){
            
            cont++;
            it_aux =  aux->primeiroItem;
            
            // cout << "(";
            int cont =1;
            while(it_aux != NULL && aux->tamanhoItemset >= cont){
                
                cont++;
                
                i_f = it_aux;
                
                
                if(buscaItemLista_de_Frequentes(i_f,lf) == -1){ //Calcula Suporte do item
                    i_f->item_suporte = (float)calculaSuporte(1, i_f, NULL, NULL, m);
                    
                    
                    if(i_f->item_suporte >= (float)MIN_SUP){
                       // cout << "\no item "<< i_f->item << " eH frequente";
                        
                        insereItemLista_Itens_Frequentes(i_f,lf);
                        
                    }
                    //insere na lista de itens frequentes.
                }
                
                
                
                // else cout <<"\nitem " << i_f->it<<" ja esta na lista";
                it_aux = it_aux->proximoItem;
            }
            // cout << ")";
            aux = aux->proximoItemset;
        }
        
        // cout << ">";
        // cout << cab->s_tamanho;
        
        cab = cab->proximaSequencia;
    }
}


void inicializaItem(tipoItem *i){ // Inicializa o item  (VAZIO) com o apontamento para NULL
    i->proximoItem = NULL;
    return;
}
/******************////**********************//******************////**********************//******************////**********************/


void inicializaItemset(tipoItemset *e){ // Inicializa o itemset  (VAZIO) com o apontamento para NULL
    e->primeiroItem = NULL;
    e->suporteItemset = 0;
    e->tamanhoItemset = -1;
    e->proximoItemset = NULL;
    return;
}
/******************////**********************//******************////**********************//******************////**********************/


void inicializaSequencia(tipoSequencia *s){// Inicializa uma sequência (VAZIA) com o apontamento para NULL
    s->primeiroItemset = NULL;
    s->suporteSequencia = 0;
    s->tamanhoSequencia = 0;
    s->proximaSequencia = NULL;
    return;
}

/******************////**********************//******************////**********************//******************////**********************/



void insereIndiceIDX(pidx *p, indice_par *index, int contSeq){
    
    indice_par *aux = new indice_par;
    indice_par *novoIndice = new indice_par;
    novoIndice = index;
    novoIndice->prox = NULL;
    novoIndice->seqNum = contSeq;
    aux = p->cabeca;
    
    if(! p->cabeca) p->cabeca = novoIndice;
    else{
        while(aux->prox) aux = aux->prox;
        aux->prox = novoIndice;
    }
}

void criaIndexSetBACKUP(tipoSequencia *s, pidx *p, memorydb *m){
    int pos = 0,contSeq = 1;
    indice_par *index = new indice_par;
    
    tipoSequencia *s_aux = m->inicioMDB;
    while(s_aux){
        pos = buscaS1EmS2(s, s_aux); //recebe a posição onde o item frequente está na sequencia s_aux
        
        if(pos != -1)// toda vez que pos != -1 cria um indice e atrela a lista.
        {
            index = new indice_par;
            index->pos=pos;
            index->ptr = s_aux;
            index->prox = NULL;
            insereIndiceIDX(p,index,contSeq);
            p->tamanho++;
        }
        
        s_aux = s_aux->proximaSequencia;
        contSeq++;
    }
     //imprimeListaIndices_emArq(p,);
    
}



void criaIndexSet(sequencia *s, pidx *p, memorydb *m){
    int pos = 0,contSeq = 1;
    indice_par *index = new indice_par;
    sequencia *s_aux = m->inicioMDB;
    int percorreMdb = 1;
    

    while(percorreMdb<=m->tamanhoMDB){
        percorreMdb++;
        pos = buscaS1EmS2(s,s_aux);
        if( pos != -1){
            index = new indice_par;
            index->pos=pos;
            index->ptr = s_aux;
            index->prox = NULL;
            insereIndiceIDX(p,index,contSeq);
            p->tamanho++;
        }
        
        s_aux = s_aux->proximaSequencia;
        contSeq++;
    }
    string   nomeArq =  imprimeSequenciaArq(s);
    imprimeListaIndices_emArq(p,nomeArq);
    imprimeListaIndices(p);
}
/******************////**********************//******************////**********************//******************////**********************/



void percorreLF(lista_de_Itens *lf, memorydb *mdb){

    lista_de_Itens *aux = lf;
    item *itensfrequentes =     aux->cabeca;
    int pos=0;
    double suporte = 0.0;
    string txtArq;
    string itemFrequente;
    FILE *fp;
    
    
    
    
    while(itensfrequentes){
    //para cada um dos itens frequentes de lf é preciso marcar onde estão as ocorrências na BD.
        itemFrequente = itensfrequentes->item;
        suporte = itensfrequentes->item_suporte;
        
        txtArq ="/Users/rafaelstoffalettejoao/Documents/MESTRADO/S_MEMISP+AR-Codigos/S_MEMISP+AR/db/saidas/";
        txtArq.append(itemFrequente);
        txtArq.append("-IDX.txt");
        fp = fopen (txtArq.c_str(), "w+");
        
        if (fp != NULL) {
            
            txtArq ="\n item : ";
            txtArq.append(itemFrequente);
            txtArq.append(" - suporte [");
            txtArq.append(to_string(suporte));
            txtArq.append("] ocorre nas seguintes sequências:");
            fputs(txtArq.c_str(),fp);
        
            
            //Percorrer a MDB e cada sequencia que conter o item é armazenada em uma lista de sequencias frequentes
            sequencia *s_mdb = mdb->inicioMDB;
        
            while(s_mdb){
                // se a sequencia s_mdb contem o item imprime ela
                pos = buscaItemSequencia(itensfrequentes->item, s_mdb);
                
                if( pos != -1){
                    txtArq ="\n pos [ "+ to_string(pos) + "] ";
                    fputs(txtArq.c_str(),fp);
                    txtArq =  imprimeSequenciaArq(s_mdb);
                    fputs(txtArq.c_str(),fp);
                }
                s_mdb=s_mdb->proximaSequencia;
            }
            cout << "\n";
            itensfrequentes=itensfrequentes->proximoItem;
        }
        fclose (fp);
    }
    return;
}



void imprimeListaIndicesArq(pidx *p,string item){

    indice_par *aux = p->cabeca;
    ofstream out;
    string nomedoArq = "/Users/rafaelstoffalettejoao/Documents/MESTRADO/S_MEMISP+AR-Codigos/S_MEMISP+AR/db/saidas/"+item+"-IDX.txt";
    out.open(nomedoArq, ios::out);
    out << "\n\tLista de Itens Frequentes encontrados em MDB\n\n";                              //ios::out apaga o arquivo e escreve nele
    out.close();
    
    
    
    while(aux)
    {
        cout << "\n pos = "<< aux->pos ;
        cout << " ptr_ds: ";
        imprimeSequencia(aux->ptr);
        aux = aux->prox;
    }
    if (aux == NULL ) cout << "\n fim da lista de índices...";
    return;
    
    
}

void imprimeListaIndices_emArq(pidx *p, string nomedoArq){
    indice_par *aux = p->cabeca;
    FILE *fp;
    string txtArq ="/Users/rafaelstoffalettejoao/Documents/MESTRADO/S_MEMISP+AR-Codigos/S_MEMISP+AR/db/saidas/listas";
    txtArq.append(nomedoArq.c_str());
    txtArq.append("-IDX.txt");
    fp = fopen (txtArq.c_str(), "w+");
    
    if (fp != NULL) {
    while(aux)
    {
        txtArq ="\n pos [ "+ to_string(aux->pos) + "] ";
        fputs(txtArq.c_str(),fp);
        txtArq =  imprimeSequenciaArq(aux->ptr);
        fputs(txtArq.c_str(),fp);
        aux = aux->prox;
    }
        
    }

    //if (aux == NULL ) cout << "\n fim da lista de índices no arquivo...";
    fclose (fp);
    return;
}



void imprimeListaIndices(pidx *p){
    indice_par *aux = p->cabeca;
   cout << "\n ------------------------------------\n\t  lista de índices\n ------------------------------------\n";

    
    while(aux)
    {
        cout << "\n pos = "<< aux->pos ;
        cout << " ptr_ds: ";
        imprimeSequencia(aux->ptr);
        aux = aux->prox;
    }
    if (aux == NULL ) cout << "\n ------------------------------------\n\tfim da lista de índices\n ------------------------------------\n\n\n";
    return;
}

tipoSequencia *getSeqPidx(int posSeq,pidx *p){
    pidx *aux = p;
    indice_par *par =  aux->cabeca;
    tipoSequencia *retorno = NULL;
    
    
    while(posSeq > 0) { posSeq--; par=par->prox;}
    
    imprimeSequencia(par->ptr);
    //wait_on_enter();
    
     //analise de cada um dos pares da lista de indices
    
    if(par->ptr == NULL) return NULL;
    else{
        retorno =  par->ptr;
        return retorno;
    }
}




//
//
//void mine(tipoSequencia *sit,pidx *pid,memorydb *mdb){
//    cout << "\n minerando o padrão";  imprimeSequencia(sit);
//    wait_on_enter();
//    //int posseq = 0;
//    //tipoSequencia *seq_aux =  new tipoSequencia;
//    
//    int posPadrao;
//    int contpos;
//    
//    
//    
//    
//    
//    
//    //DAQUI
//    tipoItemset *it_pid;
//    tipoItem *i_pid ;
//    indice_par *par =  pid->cabeca;
//    int tipo1=0;
//    while(par != NULL){ //percorrendo todas as sequencias de pid pode-se pegar o elemnto seguinte a posição pos e estender o padrão sit
//        cout << "par selecionado: ";
//        posPadrao = par->pos;
//        cout << " vou até "<< par->pos;
//        //par->ptr é a sequencia da pid
//        it_pid = par->ptr->primeiroItemset;
//        i_pid = it_pid->primeiroItem;
//        contpos =0;
//        tipo1 =0;
//        int indiceitemset=1;
//        int fimdasequencia=0;
//        while(contpos < posPadrao){
//            if(i_pid->proximoItem != NULL && indiceitemset < it_pid->tamanhoItemset){
//                indiceitemset++;
//                i_pid = i_pid->proximoItem;
//            }else
//                if(it_pid->proximoItemset != NULL){
//                    it_pid = it_pid->proximoItemset;
//                    tipo1 =1;
//                    i_pid=it_pid->primeiroItem;
//                    indiceitemset =0;
//                }
//                else fimdasequencia =1;
//            contpos++;
//            cout << "\n estou em: " << i_pid->item;
//            if (fimdasequencia) cout << "porem no outro par";
//            
//            
//        } // nesse ponto o ponteiro está na posição exata do primeiro item após o padrão
//        
//        cout << i_pid->item;
//        
//        par = par->prox;
//    }
//    // ATE AQUI
//    
//    
//    
//    
//    
//    
//}

///try
int comparaSequencias(sequencia *s1, sequencia *s2){
    
    if(s2->tamanhoSequencia < s1->tamanhoSequencia) return -1;
    int cont =1;
    itemset *e1 = s1->primeiroItemset;
    itemset *e2 = s2->primeiroItemset;
    item *i1 = new item;
    item *i2 = new item;
    int cont1, cont2 ;
    int pos =1, s2_total=1;
    
    while(e1 && (e2 && cont <= s2->tamanhoSequencia)){
        if(e1->tamanhoItemset != e2->tamanhoItemset) return -1;
        i1 = e1->primeiroItem;
        i2 = e2->primeiroItem;
        cont1 = cont2 =1;
        
        while(i1 && i2 && cont1 <= e1->tamanhoItemset && cont2 <= e2->tamanhoItemset){
            if(i1->item.compare((string)i2->item)!=0)   return -1;
            
            i1 = i1->proximoItem;
            cont1++;
            i2 = i2->proximoItem;
            cont2++;
            s2_total++;
            pos++;
            
        }
        
        if(cont1 != cont2)
            return -1;
        
        e1= e1->proximoItemset;
        cont++;
        e2  =    e2->proximoItemset;
        
    }
    
    return 1;
    
}
/**/

int sequenciaJaCriada(tipoSequencia *s){
    //seq_freq é uma lista global;
    seqFreq *aux = seq_freq->cabeca;
    int cont =1;
 
    while(aux && cont <= seq_freq->qtd_seq_freq){
        if(comparaSequencias(s,aux->s) == 1){
            return 1;
        }
        cont++;
        aux=aux->prox;
    }
    
    
    return 0;
}




void insereItemsetSequencia(sequencia *s, itemset *e){ //estende a sequencia com um itemset
    
    itemset *aux = new itemset;
    aux = s->primeiroItemset;
    if(aux == NULL) s->primeiroItemset = e;
    else{
        while(aux->proximoItemset != NULL) aux= aux->proximoItemset;
        aux->proximoItemset = e;
    }
    e->proximoItemset = NULL;
    
    return;
}


void criaPadrao2(tipoSequencia **sitnova, item *i, sequencia *pat, int tipo ){

    
    
    //copia pat para novoPat.
    sequencia novoPat;
    novoPat =  *new sequencia;
    inicializaSequencia(&novoPat);
    
    itemset *aux = pat->primeiroItemset;
    itemset *ant =  aux;
    item *i_aux = aux->primeiroItem;
    int cont =1, cont_i=1;
    
    item    *novoITem       = new item;
    itemset *novoItemset    = new itemset;
    novoPat.primeiroItemset = novoItemset;
    
    
    
    while(aux && cont <= pat->tamanhoSequencia){//percorrer o padrão já existente para copiar para o novo padrão.
        i_aux=aux->primeiroItem;
        cont_i=1;
        
        
        
        while(i_aux && cont_i <= aux->tamanhoItemset) { //cada item de cada itemset
            
            novoITem =  new item;
            novoITem->item = i_aux->item;
            novoITem->item_suporte=i_aux->item_suporte;
            
            insereItemItemset(novoITem,novoItemset);
            novoItemset->tamanhoItemset++;
            i_aux=i_aux->proximoItem;
            cont_i++;
        }
        insereItemsetSequencia(&novoPat,novoItemset);
        novoPat.tamanhoSequencia++;
        
        if(aux->proximoItemset != NULL){
            novoItemset    = new itemset;
            inicializaItemset(novoItemset);
        }
        ant = aux;
        aux=aux->proximoItemset;
        cont++;
    }
    
    if(tipo==1){
        //cout << "\ncriar padrao do tipo 1  com o item " << i->it;
        novoITem =  new item;
        novoItemset =  new itemset;
        novoITem->item = i->item;
        novoITem->item_suporte=i->item_suporte;
        insereItemItemset(novoITem,novoItemset);
        novoItemset->tamanhoItemset++;
        insereItemsetSequencia(&novoPat,novoItemset);
        novoPat.tamanhoSequencia++;
    }
    else if(tipo==2){
        //cout << "\ncriar padrao do tipo 2  com o item " << i->it;
        novoITem =  new item;
        novoITem->item = i->item;
        novoITem->item_suporte=i->item_suporte;
        insereItemItemset(novoITem,novoItemset);
        novoItemset->tamanhoItemset++;
        
    }
    
    **sitnova = novoPat;
    return;

}





void indexSet(sequencia *s, pidx *p, pidx *m){
    int pos = 0;
    int contSeq =1;
    sequencia *s_aux = new sequencia;
    indice_par *index = new indice_par;
    
    cout <<"\n\n procedimento indexSet chamado para a sequencia: ";//cout << "\n\n IndexSet " ;
    imprimeSequencia(s);
    cout << "-idx" ;
    //
    indice_par *idc = new indice_par;
    idc = m->cabeca;
    int tamanhoMDB = 1;
    
    
    while(idc){ //percorre todas as sequencias da lista de indices do seu gerador e, uma a uma, confere se contem s..
        tamanhoMDB++;
        s_aux = idc->ptr;
        pos = buscaS1EmS2(s, s_aux); //recebe a posição onde o item frequente está na sequencia s_aux
        
        
       // cout << "\n encontrado em: " << pos ;
        //wait_on_enter();
        if(pos != -1)// toda vez que pos != -1 cria um indice e atrela a lista.
        {
            index = new indice_par;
            index->pos=pos;
            index->ptr = s_aux;
            index->prox = NULL;
            
            //printf("\n contseq - %d",contSeq);
            insereIndiceIDX(p,index,contSeq);
            
        }
        contSeq++;
        idc=idc->prox;
        pos =1;
    }
    
  
   
    
    imprimeListaIndices(p);
    
    string   nomeArq =  imprimeSequenciaArq(s);
    imprimeListaIndices_emArq(p,nomeArq);
    return;
}
/******************////**********************//******************////**********************//******************////**********************/




void insereSequenciaFrequenteLista(sequencia *s){
    //cout <<"\n este é o tamanho da lista de sequencias frequentes já existente" << seq_freq->qtd_seq_freq;
    //imprimeListadeSequenciasFrequentes(seq_freq);
    
    
    seqFreq *sf =  new seqFreq;
    sf->s = s;
    //
    sf->prox = NULL;
    
    if(seq_freq->cabeca == NULL){
        seq_freq->qtd_seq_freq = 0;
        
    }
    sf->prox = seq_freq->cabeca;
    seq_freq->cabeca = sf;
    seq_freq->qtd_seq_freq++;
    
    //cout <<"\n este é o tamanho da lista de sequencias frequentes já existente" << seq_freq->qtd_seq_freq;
    
    return;
    
    
}
/******************////**********************//******************////**********************//******************////**********************/




void mine2(tipoSequencia *pattern, pidx *pid, memorydb *mdb){
    /*
     sequencia *pattern é um ponteiro para uma sequencia passada como parâmetro para verificar se é padrão
     pix *pid é a lista de pares (indices) p-idx que apontam as ocorrências do padrão pattern
     mdb é a base de dados copiada para a memória interna
     listaSequenciasFrequetes *seq_freq é a lista contendo todas as sequências frequentes identificadas.
     */
    
    cout << "\n O S_MEMISP+AR irá minerar, agora, o padrão ";  imprimeSequencia(pattern);
    cout << " baseando-se na lista de indices \n\n\n";
    int
    cont = 1,
    contIt = 1; //contador que percorre o tamanho total do itemset que esta no padrao pattern
    indice_par *pares_padrao = pid->cabeca; // pares_padrao é o par (pos,pt_ds) que aponta a ocorrencia do padrão.
    
    
    if(!pares_padrao) { // cada pares_padrao aponta uma ocorrência do padrão patter na mdb
        cout <<" \n nao ha mais sequencias apontadas no indexset";
        return;
    }
    else{
        
        sequencia *ptr_ocorrencia  = pares_padrao->ptr; // ponteiro que indica a posição da ocorrência do padrão
        tipoItemset *itemset_aux    =   new tipoItemset;
        tipoItem    *item_aux       =   new tipoItem;
        pidx    *pid2               =   new pidx;
        tipoSequencia *sit          =   new tipoSequencia;
        inicializaSequencia(sit);
        int tipo1 =0; // padrão a ser criado do tipo 1 ou 2
        int pos = 0;  // posição da ocorrencia do padrão na sequencia
        
        while(pares_padrao){ //pares_padrao percorre os pares de indices (ptr_ds,pos)
            cout << string(10, '\n');
            //wait_on_enter();
           // cout << "\n Selecionanodo uma ocorrencia do padrão: ";
            pos             = pares_padrao->pos;
            ptr_ocorrencia  = pares_padrao->ptr; //sequencia apontada pelo indice
            cont            = 1;
            tipo1           = 0;
            contIt          = 1; //contador de itens do itemset
            itemset_aux     = ptr_ocorrencia->primeiroItemset; //primeiro itemset da squencia apontada no indice
            item_aux =  itemset_aux->primeiroItem; //primeiro item do itemset it_aux
            
            while(pos > 0){ //caminhar pelos itens até a posição pos que indica a ocorrencia do padrão na sequencia da mdb..
                contIt++; //primeiro item (posição da sequencia apontada)
                
                if(itemset_aux->tamanhoItemset < contIt){//terminei o itemset e preciso de um novo
                    if(pos-1 ==0) tipo1=1;
                    itemset_aux = itemset_aux->proximoItemset;
                   if(itemset_aux->primeiroItem) item_aux =  itemset_aux->primeiroItem;
                    contIt =1;
                    cont++;
                }
                else  item_aux=item_aux->proximoItem;
                pos--;
            }
            //saindo do while o ponteiro está posicionado na posicao pos da sequencia apontada pelo indice
            // A partir de agora é possível analisar todos os itens até o fim da sequencia
            
            //aqui criar o padrao do tipo especifico e continuar pegando os itens da sequencia
            
            //até aqui ok...
            
            
            while(itemset_aux != NULL && ptr_ocorrencia->tamanhoSequencia >= cont){ // percorrer o resto da sequencia.
               
                int tamanhoItemset = 1;
                while(item_aux != NULL && itemset_aux->tamanhoItemset >= tamanhoItemset){//continuar a partir do item em pos
                    sit = new sequencia;
                    inicializaSequencia(sit);
                    tipoSequencia *sitnova = new tipoSequencia; inicializaSequencia(sitnova);
                    
                    itemset *aux = pattern->primeiroItemset;
                    itemset *ant =  aux;
                    item *i_aux = aux->primeiroItem;
                    int cont =1, cont_i=1;
                    
                    item    *novoITem       = new item;
                    itemset *novoItemset    = new itemset;
                    //sitnova->primeiroItemset = novoItemset;
                    
                    cont =1; //indice para percorrer o padrão que já existe...
                    while(cont <= pattern->tamanhoSequencia){//percorrer o padrão já existente para copiar para o novo padrão.
                        
                        i_aux=aux->primeiroItem;
                        cont_i=1; //indice para percorrer os itens de cada itemset do padrão que ja existe
                        
                      
                        while(cont_i <= aux->tamanhoItemset) { //cada item de cada itemset
                           
                            novoITem =  new item;
                            novoITem->item = i_aux->item;
                            novoITem->item_suporte = i_aux->item_suporte;
                            
                            
                            insereItemItemset(novoITem,novoItemset);
                            //imprimeitemset(novoItemset);
                            i_aux=i_aux->proximoItem;
                            cont_i++;
                        }
                        
                        
                        
                        insereItemsetSequencia(novoItemset,sitnova);
                        //cout << "\n - -- - - -- - -- - -- - \n";
                       // imprimeitemset(novoItemset);
                       // cout << "\n - -- - - -- - -- - -- -\n ";
                       // imprimeSequencia(sitnova);
                       // cout << "\n - -- - - -- - -- - -- - ";
                        
                      
                        //imprimeSequencia(sitnova);
                        if(cont < pattern->tamanhoSequencia){
                            novoItemset    = new tipoItemset;
                            inicializaDado(novoItemset);
                        }
                        
                        aux=aux->proximoItemset;
                        cont++;
                    }
                   // cout << " \n  o padrao recebido é " << pattern->tamanhoSequencia;
                   // imprimeSequencia(pattern);

                    
                    if(tipo1==1){
                    //    cout << "\ncriar padrao do tipo 1  com o item " << item_aux->item;
                        novoITem =  new item;
                        novoItemset =  new itemset;
                        novoITem->item = item_aux->item;
                        novoITem->item_suporte=item_aux->item_suporte;
                        insereItemItemset(novoITem,novoItemset);
                       // cout << "\n tamanho do novo itemset" <<novoItemset->tamanhoItemset;
                       // imprimeitemset(novoItemset);
                        //novoItemset->tamanhoItemset++;
                        insereItemsetSequencia(sitnova,novoItemset);
                        sitnova->tamanhoSequencia++;
                       // imprimeSequencia(sitnova);
                        //cout <<" tamanho  = " <<sitnova->tamanhoSequencia;
                    }
                    else if(tipo1==0){
                      //  cout << "\ncriar padrao do tipo 2  com o item " << item_aux->item;
                        novoITem =  new item;
                        novoITem->item = item_aux->item;
                        novoITem->item_suporte=item_aux->item_suporte;
                        insereItemItemset(novoITem,novoItemset);
                        //cout << " - o tamanho de novoItemset  é : " << novoItemset->tamanhoItemset;
                       // imprimeitemset(novoItemset);
                        
                        
                        
                    }
                   
                    //cout << "esse é o novo padrao: ";imprimeSequencia(sitnova);
                    float suporte_temp = 0.0;
                    
                    if(sequenciaJaCriada(sitnova)){
                     cout << "\n Essa sequencia já foi considerada anteriormente";
                    }
                    else{
                       // cout << "\n Essa sequencia ainda nao foi considerada";
                        insereSequenciaFrequenteLista(sitnova);
                        suporte_temp = calculaSuporteSequencia(sitnova,mdb);
                        sitnova->suporteSequencia = suporte_temp;
                        if(sitnova->suporteSequencia >= (float)MIN_SUP){
                            pid2 =  new pidx;
                            indexSet(sitnova, pid2, pid);
                            cout << "\n Retornei da lista de indices";
                            mine2(sitnova,pid2,mdb);
                           // wait_on_enter();
                        }
                    }
                    
/*
                    cout << "\n\n -----------------------------------\n ";
                    suporte_temp = calculaSuporteSequencia(sitnova,mdb);
                    sitnova->suporteSequencia = suporte_temp;
                    cout << "\n-------------------------------------\n";
                  
                    if(sitnova->suporteSequencia >= (float)MIN_SUP){
                        cout << " - - - Frequente\n\n";
                        if(sequenciaJaCriada(sitnova)==0) {
                            
                            insereSequenciaFrequenteLista(sitnova);
                            wait_on_enter();
                            //imprimeListadeSequenciasFrequentes(seq_freq);
                            // seq_freq->qtd_seq_freq++;
                            pid2 =  new pidx;
                            indexSet(sitnova, pid2, pid);
                            wait_on_enter();
                            //mine2(sitnova,pid2,mdb);
                            
                            
                        }
                        else cout << " - - - Sequencia ja analisada";
                        
                        
                    } //if min_sup
                    else cout << " - - - Não Frequente (suporte baixo) \n\n";
                    */
                    contIt++;
                    tamanhoItemset++;
                    
                    if(item_aux->proximoItem && contIt <= itemset_aux->tamanhoItemset)
                        item_aux=item_aux->proximoItem;
                    else item_aux = NULL;
                    
                }
                
                if(itemset_aux->proximoItemset != NULL)    itemset_aux = itemset_aux->proximoItemset;
                tipo1 = 1;
                item_aux =  itemset_aux->primeiroItem;
                contIt =0;
                cont++;
            }
            cont=1;
            
            if(pares_padrao->prox) pares_padrao = pares_padrao->prox;
            else return;
        }
        
        
        return;
    }
}


