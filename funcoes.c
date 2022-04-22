#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include "struct.h"

void Removerlinha(char *line)
{
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

static int idPodcast = 1;

List Iniciar() {
  List lista = malloc(sizeof(List));

  lista->curr = NULL;
  lista->ini = NULL;
  lista->fim = NULL;
  lista->shuffle = 0;
  
  for(int i = 0; i < sizeof(lista->podcasts) / sizeof(Podcast); i++) {
    Podcast pdc;
    pdc.idPodcast = -1;
    lista->podcasts[i] = pdc;
  }

  return lista;
}

void Resetar(List list) {
  list->curr = NULL;
  list->ini = NULL;
  list->fim = NULL;
}

void resetCelula(Celula * celula) {
  celula->next = NULL;
  celula->prev = NULL;
}

Podcast * searchPodcast(List list, Podcast * podcast) {
  int compare; 
  for(Celula * aux = list->ini; aux != NULL; aux = aux->next) {
    compare = strcmp(aux->episodio->podcast.nomepd, podcast->nomepd);
    if(strcmp(aux->episodio->podcast.nomepd, podcast->nomepd) == 0) {
      return podcast;
    }
  }
  return NULL;
}

Celula * createCelula() {
  Episode * newEp = malloc(sizeof(Episode));
  Celula * newCelula = malloc(sizeof(Celula));
  Podcast podcast;

  printf("\n Qual o ID do Podcast: ");
  scanf("%d", &podcast.idPodcast);
  getchar();  
  
  printf("\n Qual o nome do Podcast : ");
  fgets(podcast.nomepd, 64, stdin);
  Removerlinha(podcast.nomepd);
  
  
  printf("\n Qual o número do episódio: ");
  scanf("%d", &newEp->numeroep);
  getchar();
  
  printf("\n Qual o nome do episódio: ");
  fgets(newEp->nomeep, 64, stdin);
  Removerlinha(newEp->nomeep);

  
  newCelula->episodio = newEp;
  podcast.idPodcast = idPodcast;
  newEp->podcast = podcast;
  
  return newCelula;
}

void Adicionar(List list) {  
  Celula * newCelula = createCelula();
  Podcast * resultSearch = searchPodcast(list, &newCelula->episodio->podcast);
  
  if(resultSearch != NULL) {
    newCelula->episodio->podcast = *resultSearch;
  }
  else {
    idPodcast++;
  }
  
  if(list->ini == NULL) {  
    
    list->curr = newCelula;
    list->ini = newCelula;
    list->fim = newCelula;

    newCelula->prev = NULL;
    newCelula->next = NULL;


  } else {
    newCelula->prev = list->fim;
    newCelula->next = NULL;
    list->fim->next = newCelula;
    list->fim = newCelula;
  }
  printf("\n Você adicionou um novo episódio :)\n");
}

void Tocando(List list) {

  if(list->curr != NULL) {
    printf("\n Você está no episódio %s do podcast %s\n", list->curr->episodio->nomeep, list->curr->episodio->podcast.nomepd);
    
  }
  else {
    printf("\n Não há podcasts");
  }
}

void Proximo(List list, bool shuffle) {
  
  if (list->ini != NULL) {
    if (shuffle) {
      while (true) {
        srand(time(NULL));
        int aux = rand() % sizeof(list) + 1;
           list->fim->next = list->ini;
          Celula * ep = list->curr;

        for (int i = 0; i < aux; i++) {
          list->curr = list->curr->next;
        }

        if (ep != list->curr) {
          
          Tocando(list);
          return;
        }
      }
    } else {
      if (list->curr->next != NULL) {
        list->curr = list->curr->next;

        if (list->curr == list->fim) {
          printf("\n Terminou\n");
        }
        
        Tocando(list);
        
      } else {
        printf("\n Terminou\n");

        list->curr = list->ini;

        Tocando(list);
      }
    }
    
  } else {
    printf("\n Não há podcasts");
  }
}

void Mostrar(List lista) {
  if(lista->ini != NULL) {
    for(Celula * aux = lista->ini; aux != NULL; aux=aux->next) {
      Episode * ep = aux->episodio;
      Episode * epCurr = lista->curr->episodio;

      if(ep->numeroep == epCurr->numeroep && ep->podcast.idPodcast == epCurr->podcast.idPodcast) {
      printf("\n Episódio número: %d - %s, do podcast %d - %s, está tocando\n", ep->numeroep, ep->nomeep, ep->podcast.idPodcast, ep->podcast.nomepd);
      }
      else {
      printf("\n Episódio número: %d - %s, do podcast %d - %s\n", ep->numeroep, ep->nomeep, ep->podcast.idPodcast, ep->podcast.nomepd);
      }
    }
  } 
  else {
    printf("\n Não há podcasts");
 } 
  
}

void Remover(List list) {
 if(list) {
    
    int numeroep, idPodcast;
    Celula * removido;
    printf("\n Qual o número do episódio: ");
    scanf("%d", &numeroep);
    getchar();
    printf("\n Qual o ID do Podcast: ");
    scanf("%d", &idPodcast);
    getchar();

    
      if(list->ini->next == NULL) {
        if(list->ini->episodio->numeroep == numeroep && list->ini->episodio->podcast.idPodcast) {
          removido = list->ini;
          Resetar(list);
          printf("\n Episódio %d do %s removido!", removido->episodio->numeroep, removido->episodio->podcast.nomepd);
          return;
        }
      }
      else {
        for(Celula * aux = list->ini; aux != NULL; aux = aux->next){
          if(list->ini->episodio->numeroep == numeroep && list->ini->episodio->podcast.idPodcast == idPodcast) {
              removido = list->ini;
              list->ini = list->ini->next;
            if(list->curr->episodio->numeroep == numeroep && list->curr->episodio->podcast.idPodcast == idPodcast ) {
              list->curr= list->curr->next;
            }
              printf("\n Episódio %d do podcast %s removido!", removido->episodio->numeroep, removido->episodio->podcast.nomepd);
              resetCelula(removido);
            }
            
          else if(aux->next->episodio->numeroep == numeroep && aux->next->episodio->podcast.idPodcast == idPodcast) {
            removido= aux->next;
            aux->next = aux->next->next;
            resetCelula(removido);
            
            if(list->curr->episodio->numeroep == numeroep && list->curr->episodio->podcast.idPodcast == idPodcast ) {
              list->curr = list->curr->next;
            }
            printf("\n Episódio %d do podcast %s removido!", removido->episodio->numeroep, removido->episodio->podcast.nomepd);
            resetCelula(removido);
            return;
          }
        }
      }
    free(removido);
    }
  else {
    printf("\n Não há Podcasts");
  }
}