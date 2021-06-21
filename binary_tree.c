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

/* Recebe um nó e altera seu valor para o valor inteiro representado pelo char */
void transforma_inteiro(struct tNo *no)
{
  no->valor = no->valor - 48;
}

/* Ajusta o valor do nó em que as entradas estão [10, 99] */
void ajusta_no(struct tNo *no, char decimal)
{
  decimal = decimal - 48;
  no->valor = (no->valor * 10) + decimal;
}

struct tNo *montaarvore(char *str, int *i)
{
  struct tNo *no = NULL;

  /*(*(51)(+(4)(3))*/

  if (str[*i] == '(')
  {
    (*i)++;
    no = inicia(str[*i]);

    if (no->valor > 47)
    {
      transforma_inteiro(no);
      if (str[(*i + 1)] > 47)
      {
        (*i)++;
        ajusta_no(no, str[*i]);
      }
    }

    (*i)++;

    no->esq = montaarvore(str, i);
    no->dir = montaarvore(str, i);

    (*i)++;
  }
  return no;
}

int posordem(struct tNo *no) /*notacao polonesa reversa "A B op."*/
{
  /* os codigos ASCII dos operadores sao 42, 43, 45 e 47, e os demais caracteres ("," e ".") no intervalo nao sao numeros */

  if ((41 < no->valor && no->valor < 48))
  {
    int operador_esquerdo = posordem(no->esq);
    int operador_direito = posordem(no->dir);

    printf("%d %c %d\n", operador_esquerdo, no->valor, operador_direito);

    switch (no->valor)
    {
    case '*':
      return operador_esquerdo * operador_direito;
    case '+':
      return operador_esquerdo + operador_direito;
    case '-':
      return operador_esquerdo - operador_direito;
    case '/':
      return operador_esquerdo / operador_direito;
    default:

      return 0;
    }
  }
}

int main(void)
{
  struct tNo *n = NULL;
  int i = 0;

  n = montaarvore("(*(5)(+(40)(3))\n", &i);
  /*n=montaarvore("(A(B(C(D(E)))))\n",&i);*/

  printf("%d -- disse o algoritmo, com uma majestade e uma tranquilidade infinitas.\n", posordem(n));
  return 0;
}
