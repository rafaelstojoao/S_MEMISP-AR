//
//  main.cpp
//  S_MEMISP+AR
//
//  Created by Rafael Stoffalette João on 1/8/15.
//  Copyright (c) 2015 Rafael Stoffalette João. All rights reserved.
//

#include <iostream>
#include "functions.h"
#include "arquivos.h"
#include <stdlib.h>
#include <string>

using namespace std;






int main(int argc, const char * argv[]) {
    fflush(stdin);
    int cont_item_frequente =1;
    memorydb  *mdb = new memorydb;
    mdb->tamanhoMDB = 0;
    mdb->inicioMDB = NULL;
    lista_de_Itens *lf = new lista_de_Itens;
    leArqString(mdb);
    imprimeMDB(mdb);
    find_all_frequent_items(lf,mdb);
    
   // percorreLF(lf,mdb); //  Cria arquivos com a lista de indices para cada padrão.
    
    

//    tipoItem *itemsup =  new tipoItem;
//    inicializaDado(itemsup);
//    
//    itemsup->item = "presuntokg";
//
//    tipoItemset *itemsetsuporte =  new tipoItemset; inicializaDado(itemsetsuporte);
//    insereItemItemset(itemsup, itemsetsuporte);
//    tipoItem *itemsup2 =  new tipoItem;
//    inicializaDado(itemsup2);
//    itemsup2->item = "refrigerante";
//    insereItemItemset(itemsup2, itemsetsuporte);
//    
//    tipoItem *itemsup3 =  new tipoItem;
//    inicializaDado(itemsup3);
//    itemsup3->item = "sabaoempo";
//    insereItemItemset(itemsup3, itemsetsuporte);
//    imprimeitemset(itemsetsuporte);
//    cout << "\n o suporte da cebola é de : "<<  calculaSuporte(2, NULL, itemsetsuporte, NULL, mdb);
//    
//    
//    
//    
    

    //Imprime os itens frequentes encontrados com seus respectivos valores de suporte
    tipoItem *it_aux = lf->cabeca;
    ofstream out;
    out.open("/Users/rafaelstoffalettejoao/Documents/MESTRADO/S_MEMISP+AR-Codigos/S_MEMISP+AR/db/saidas/itensFrequentes.txt", ios::out);
    out << "\n\tLista de Itens Frequentes encontrados em MDB\n\n";                              //ios::out apaga o arquivo e escreve nele
    while(it_aux){
        out << "\n Item  [" << it_aux->item << "] Suporte = " << it_aux->item_suporte;
        cout << "\n Item  [" << it_aux->item << "] Suporte = " << it_aux->item_suporte;

        it_aux = it_aux->proximoItem;
    }
    if (it_aux == NULL)
        out << "\n Fim dos itens frequentes...";
    out.close();
    
    
    //listaSequenciasFrequetes    *seq_freq   = new listaSequenciasFrequetes;
   // seq_freq->qtd_seq_freq =0;
    
    it_aux = lf->cabeca;
    //cout << lf->tamanho;
    item      *it    =  new item;
    itemset   *itemset_aux =  new itemset;
    sequencia *sit   =  new sequencia;
    pidx *pid =  new pidx;
    cout << "\n\n \tNesse próximo passo, cada um dos itemsets frequentes é utilizado para formar padrões:\n\n";
    
    while(cont_item_frequente <= lf->tamanho){
        cont_item_frequente++;
        it = new item;
        sit =  new sequencia; inicializaDado(sit);
        itemset_aux = new tipoItemset;
        pid = new pidx;
        
        
        it->item = it_aux->item;
        insereItemItemset(it,itemset_aux);
        insereItemsetSequencia(itemset_aux,sit);
        cout << "ITEM FREQUENTE ";
        imprimeSequencia(sit); cout  << " a ser minerado " << sit->tamanhoSequencia ;

        
        pid->s.primeiroItemset = sit->primeiroItemset;
        criaIndexSet(sit, pid, mdb);
        //mine2(sit,pid,mdb);
      
        
        
        //imprimeListaIndices(pid);
        it_aux = it_aux->proximoItem;
        cout << "\n o proximo será " << it_aux->item;
          wait_on_enter();
    }

    free(mdb);
   // free(lf);
    
    
    return 0;
}