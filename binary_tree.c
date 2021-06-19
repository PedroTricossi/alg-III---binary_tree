#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct tNo *montaarvore(char *str, int *i)
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
    printf("%d | ", no->valor);
    emordem(no->dir);
  }
}

void transforma_inteiro(struct tNo *no)
{
  if (no != NULL)
  {
    transforma_inteiro(no->esq);
    if (no->valor != 42 && no->valor != 43 && no->valor != 45 && no->valor != 47)
    {
      no->valor = no->valor - 48;
    }
    transforma_inteiro(no->dir);
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

  transforma_inteiro(n);

  emordem(n);
  return 0;
}
