//
//  arquivos.cpp
//  S_MEMISP+AR
//
//  Created by Rafael Stoffalette João on 1/8/15.
//  Copyright (c) 2015 Rafael Stoffalette João. All rights reserved.
//

#include "arquivos.h"





void leArqString(memorydb *m){
    ifstream arq;		        //crio objeto "arq" da classe ifstream - leitura
    
arq.open("/Users/rafaelstoffalettejoao/Documents/MESTRADO/S_MEMISP+AR-Codigos/S_MEMISP+AR/db/memisp.txt");//entrada
    
    if (arq.is_open() && arq.good())
    {
        char ch;
        string str_item;
        tipoItem *i = new tipoItem;
        inicializaItem(i);
        tipoSequencia *s1 =  new tipoSequencia;
        
        inicializaSequencia(s1);
        tipoSequencia  *aux = new tipoSequencia;
        aux = s1;
        tipoItemset *e = new tipoItemset;
        tipoItemset *e_aux =  new tipoItemset;
        inicializaItemset(e);
        inicializaItemset(e_aux);
        m->inicioMDB = s1;
        m->tamanhoMDB++;
        int fimdaLinha = 0;
        
        while (  arq.get(ch) &&  !fimdaLinha  & arq.good()  ) {
            
            ch = (char)ch;
            if(ch == ' ') arq.get(ch);
            
            
            
            else if(ch == '\n'){     //cout << "nova linha ";// aqui finaliza a sequencia
            ch = (char)ch;

                if(ch != ' '){
                   // cout << "Sequencia tem tamanho " << s1->tamanhoSequencia;
                    str_item.clear();
                    aux = new tipoSequencia;
                    inicializaSequencia(aux);
                    m->tamanhoMDB++;
                    aux = s1;
                    s1 =  new tipoSequencia;
                    inicializaSequencia(s1);
                    aux->proximaSequencia = s1;
                }else{
                    e->proximoItemset = NULL;
                    s1->proximaSequencia= NULL;
                    fimdaLinha =1;
                    
                }
            }
            else if(ch == '('){
                str_item.clear();
                i = new tipoItem;
                inicializaItem(i);
                e_aux = new tipoItemset;
                e_aux = e;
                e =  new tipoItemset;
                inicializaItemset(e);
                e_aux->proximoItemset = e;
            }
            
            else if(ch == ')'){
                
                i->item =  str_item;
                insereItemItemset(i,e);
               // countnumtran++;
                e->tamanhoItemset++;
               
                insereItemsetSequencia(e,s1);
                //s1->tamanhoSequencia =  s1->tamanhoSequencia +1;
               // cout << "aumentou seq [" << s1->tamanhoSequencia;
                
                
                
                str_item.clear();
                i = new tipoItem;
            
                inicializaItem(i);
                //cria novo itemset
            }
            
            else if(ch == ','){ // se encontrar uma vírgula é o fim do item então insere no itemset corrente e reinicia o item (string)
                i->item =  str_item;
                
                insereItemItemset(i,e);
                //countnumtran++;
               // e->tamanhoItemset++;
                
                
                str_item.clear();
                i = new tipoItem;
                inicializaItem(i);
            }
            else{
                str_item+=ch;
            }
        }
        //cout << countnumtran << "TRANSACOES";
        arq.close();
        //imprimeMDB(m);
    }
    
}