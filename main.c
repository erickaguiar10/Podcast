#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "struct.h"

int main(void){
  printf("\n\tPodquest");

  int option;
  bool shuffle = false;
  List lista = Iniciar();

 do{
    printf("\n\n Opções:\n\n 0 - Sair\n 1 - Tocar\n 2 - Próximo \n 3 - Adiconar\n 4 - Shuffe\n 5 - Remover\n 6 - Mostrar episódios\n 7 - Mostrar Podcasts\n\n ");
    
    scanf("%d", &option);
  switch(option){
    case 0:
      printf("\n Você saiu");
      return 0;
      break;
    
    //Play
    case 1: 
      Tocando(lista);
      break;

    //Play next
    case 2:
      Proximo(lista, shuffle);
      break;

    //Add
    case 3:
      Adicionar(lista);
      break;

    //Shuffle
    case 4: 
      if (shuffle){
        printf("\Shuffle off\n");
        shuffle = false;
      }
      else {
        printf("\nShuffle on\n");
        shuffle = true;
      }
      break; 

    //Remove
    case 5:
      Remover(lista);
      break;

    
    //ShowPodcast
    case 6:
      Mostrar(lista);
      break;
    
    default:
      if(option != 0)
        printf("\t\nOpção Inválida!");
    }
  } while(option != 0);
    free(lista);
  return 0;
}
