#include <stdio.h>
#include <stdlib.h>

struct tNo
{
  char valor;
  struct tNo *esq, *dir;
};

struct tNo *inicia(char valor)
{
  struct tNo *n = (struct tNo *)malloc(sizeof(struct tNo));
  n->valor = valor;
  n->dir = NULL;
  n->esq = NULL;
  return n;
}

struct tNo *montaarvore(const char *str, int *i)
{
  struct tNo *no = NULL;

  if (str[*i] == '(')
  {
    (*i)++;
    printf("cria nó: %c \n", str[*i]);
    no = inicia(str[*i]);
    (*i)++;
    no->esq = montaarvore(str, i);
    no->dir = montaarvore(str, i);
    (*i)++;
  }
  return no;
}

void emordem(struct tNo *no)
{
  if (no != NULL)
  {
    emordem(no->esq);
    printf("%c", no->valor);
    emordem(no->dir);
  }
}

void posordem(struct tNo *no)
{
  if (no != NULL)
  {
    posordem(no->esq);
    posordem(no->dir);
    printf("%c", no->valor);
  }
}

void preordem(struct tNo *no)
{
  if (no != NULL)
  {
    printf("%c", no->valor);
    preordem(no->esq);
    preordem(no->dir);
  }
}

int main(void)
{
  struct tNo *n = NULL;
  int i = 0;
  i = 0;
  n = montaarvore("(*(5)(+(4)(3))\n", &i);
  /*n=montaarvore("(A(B(C(D(E)))))\n",&i);*/
  printf("percurso em ordem:");
  emordem(n);

  printf("percurso em pós-ordem:");
  posordem(n);

  printf("percurso em pré-ordem:");
  preordem(n);

  return 0;
}
