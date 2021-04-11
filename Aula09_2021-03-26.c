#include <stdio.h>
#include <stdlib.h>

typedef struct _DblList {
      int value;

      struct _DblList *previous;
      struct _DblList *next;
} IntDblList;


IntDblList *head_insert( IntDblList* lst, int value );
IntDblList *list_append( IntDblList *lst, int value );
IntDblList* sorted_insert_rec(IntDblList* lst, int value);

void listar(IntDblList *lst);
void listar_rec(IntDblList *lst);
void listar_inv(IntDblList *lst);
void listar_inv_rec(IntDblList *lst);

IntDblList* remover(IntDblList *lst, int key);
IntDblList* remover_rec(IntDblList *lst, int key);
IntDblList* remover_todos(IntDblList *lst, int key);
IntDblList* remover_ord(IntDblList *lst, int key);
IntDblList* remover_todos_ord(IntDblList *lst, int key);

// -----------
IntDblList* auxiliar_remover( IntDblList* lista, int value);

int main() {
    IntDblList *list = NULL;

    list = head_insert(list,10);
    list = list_append(list,30);
    list = sorted_insert_rec(list,20); // 10 20 30
    listar(list);
    listar_inv_rec(list);  
    listar_inv(list);
     
    list = remover(list, 20);     // 10 30
    list = remover_rec(list,30);  // 10
    listar(list);

    list = head_insert(head_insert(list,7),10);   // 10 7 10
    list = list_append(list_append(list,10),23);  // 10 7 10 10 23
     list = list_append(list_append(list,10),7);  // 10 7 10 10 23 10 7
     list = remover_todos(list, 10);  // 7  23  7
     listar(list);
     list = remover_todos(list, 7 );  //  23
     listar(list);
     list = remover_todos(list, 23 );  //  Vazia
     listar(list);

    // ------------------------------------------------
    list = sorted_insert_rec(sorted_insert_rec(list,25),5);
    list = sorted_insert_rec(sorted_insert_rec(list,25),5);
    list = sorted_insert_rec(sorted_insert_rec(list,40),10);
    list = sorted_insert_rec(sorted_insert_rec(list,40),10);
    list = sorted_insert_rec(list,18); // 5 5 10 10 10 18 25 25 40 40
    listar(list);
    list = remover_ord(list, 18);    // 5 5 10 10 10  25 25 40 40
    list = remover_ord(list, 10);     // 5 5    10 10  25 25 40 40
    list = remover_todos_ord(list, 5);  //      10 10  25 25 40 40
    list = remover_todos_ord(list, 10); //             25 25 40 40
    list = remover_todos_ord(list, 40); //             25 25 
    listar(list);

    return 0;

}



// Auxiliares da função main
IntDblList* auxiliar_remover( IntDblList* lista, int value){
    IntDblList* resultado = NULL;
    listar(lista);
    printf("lista = remover(lista, %d ) \n",value);
    // lista = remover(lista, value); 
    // lista = remover_rec(lista, value);
     lista = remover_todos(lista, value);
  
    listar(lista);
    putchar('\n');
    return lista;
}
// ---------------------------------------------------

void listar_inv(IntDblList *lst) {
      // 1º deslocar para o último nodo
      if (lst) {
        for ( ; lst->next ; lst = lst->next ) {  }
        // lst tem o endereço do último nodo
        // 2º percorrer a lista por ordem inversa
        for ( ; lst ; lst = lst-> previous ) {
            printf("%d ", lst->value);
        }
        printf("\n");
      }
}


void listar_inv_rec(IntDblList *lst) {
    if (lst) {
        listar_inv_rec(lst->next);
        printf("%d ", lst->value);
        if (!lst->previous) // primeiro nodo
          printf("\n");
      } 
} 

void listar_rec(IntDblList *lst) {
    if (lst) {
        printf("%d ", lst->value);
        listar_rec(lst->next);
      } else 
        printf("\n");
} 

void listar(IntDblList *lst) {
        for ( ; lst ; lst = lst->next ) {
            printf("%d ", lst->value);
        }
        printf("\n");
} 


IntDblList * head_insert( IntDblList* lst, int value ) {
   IntDblList *new = (IntDblList*) malloc(sizeof(IntDblList));

   new->value = value;
   new->next = lst;
   if (new->next)
      new->next->previous = new;
   new->previous = NULL;

   return new;
}


IntDblList *list_append( IntDblList *lst, int value ) {
     IntDblList *aux, *new_cell;
     new_cell = (IntDblList*) malloc(sizeof(IntDblList));
     new_cell->value = value;
     new_cell->next = new_cell->previous = NULL;           

     if (lst) {
         for (aux = lst; aux->next ; aux = aux->next) { }
         aux->next = new_cell;
         new_cell->previous = aux;
     } else {
         lst = new_cell;
     }
     return lst;
 }


 IntDblList* sorted_insert_rec(IntDblList* lst, int value) {
  if (!lst || value < lst->value) {
     IntDblList* new = (IntDblList*) malloc(sizeof(IntDblList));
     new->value = value;
     new->next = lst;
     new->previous = NULL;
     lst = new;
     if (lst->next)
        lst->next->previous = new;
  }
  else {
      lst->next = sorted_insert_rec(lst->next, value);
      lst->next->previous = lst;
  }
   
  return lst;
}

  
/* função auxiliar remover
   liberta node, devolvendo node->next */
IntDblList* delete_node(IntDblList *node) {
      IntDblList* toDelete = node; 
      node = toDelete->next;
      free(toDelete);

      return node;
}


IntDblList* remover(IntDblList *lst, int key) {
    IntDblList *aux = lst;

    while(aux) {
       if (aux->value == key) { // aux é o nodo a remover
          
          if (aux -> next) // não último nodo
             aux->next -> previous =  aux-> previous;
      
          if ( aux -> previous)  // não é o primeiro nodo!
            aux->previous -> next = aux -> next;
          else // é o primeiro nodo
            lst = aux -> next;   // apenas no caso de ser o 1º

          free(aux);
          break;  // termina ciclo, após primeira ocorrência 
        }  
        aux = aux -> next;
    }
    return lst;
 }    

IntDblList* remover_todos(IntDblList *lst, int key) {
    IntDblList *aux = lst;

    while(aux) {
       if (aux->value == key) { // aux é o nodo a remover
       
          if (aux -> next) // não último nodo
             aux->next -> previous =  aux-> previous;
        
          if ( aux -> previous)  // não é o primeiro nodo!
            aux->previous -> next = aux -> next;
          else // é o primeiro nodo
            lst = aux -> next;   // apenas no caso de ser o 1º

 
           
           /* IntDblList* toDelete = aux; 
           aux = aux->next;
           free(toDelete);   */
           aux = delete_node(aux); 
        } else 
             aux = aux -> next;
    }
    return lst;
 }    


  IntDblList* remover_rec(IntDblList *lst, int key) {
    if (lst) {
      if (lst->value == key) {
        if (!lst->previous && lst->next) // 1º da lista original e não único
          lst->next->previous = NULL;
        lst = delete_node(lst);  // apenas 1 elemento
        
      }
      else {
        lst->next = remover_rec(lst->next, key);
        if (lst->next) 
              lst->next->previous = lst;
        
      }
      
    }
    return lst;
  }    


  IntDblList* remover_ord(IntDblList *lst, int key) {
    IntDblList *aux = lst;

    while(aux && aux->value <= key) {
       if (aux->value == key) { // aux é o nodo a remover
          if (aux -> next) // não último nodo
             aux->next -> previous =  aux-> previous;
        
          if ( aux -> previous)  // não é o primeiro nodo!
            aux->previous -> next = aux -> next;
          else // é o primeiro nodo
            lst = aux -> next;   // apenas no caso de ser o 1º
           
           free(aux); 
           break;  // termina ciclo, após primeira ocorrência 
        }  
             aux = aux -> next;
    }
    return lst;
 }       
 
 IntDblList* remover_todos_ord(IntDblList *lst, int key) {
    IntDblList *aux = lst;

    while(aux && aux->value < key) {  
          aux = aux -> next; 
    }
    
    while (aux && aux->value == key) { 
          if (aux -> next) // não último nodo
             aux->next -> previous =  aux-> previous;
        
          if ( aux -> previous)  // não é o primeiro nodo!
            aux->previous -> next = aux -> next;
          else // é o primeiro nodo
            lst = aux -> next;   // apenas no caso de ser o 1º
           
           /*IntDblList* toDelete = aux; 
           aux = aux->next;
           free(toDelete); */
           aux = delete_node(aux); 
    }
    return lst;
 }       //  10 20 20 20 30 


