typedef struct keyWord {
  char keyWords[64];
  struct keyWord *next;
  struct keyWord *prev;

} KeyWord;

typedef struct keyWords {
  KeyWord *ini;
  KeyWord *end;

} KeyWords;

typedef struct podcast {
  char nomepd[64];
  int idPodcast;
  
}Podcast;

typedef Podcast *Podquest;

typedef struct Episode {
  Podcast podcast;

  char nomeep[64];
  int numeroep;

} Episode;

typedef struct Celula {
  struct Celula * next;
  struct Celula * prev;

  Episode * episodio;
} Celula;

typedef struct Head {
  Podcast podcasts[64];
  Celula * curr;
  Celula * ini;
  Celula * fim;
  int shuffle;

} Head;
typedef Head * List;

List Iniciar();

void Removerlinha(char *line);

void Adicionar(List list);

void Tocando(List list);

void Proximo(List list, bool shuffle);

void Remover(List list);

void Mostrar(List list);

void Resetar(List list);