#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tNo
{
  int valor_int;
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
  no->valor_int = no->valor - 48;
}

/* Ajusta o valor do nó em que as entradas estão [10, 99] */
void ajusta_no(struct tNo *no, char decimal)
{
  decimal = decimal - 48;
  no->valor_int = (no->valor_int * 10) + decimal;
}

struct tNo *montaarvore(char *str, int *i)
{
  struct tNo *no = NULL;

  if (str[*i] == '(')
  {
    (*i)++;
    no = inicia(str[*i]);

    if (no->valor > 47) /* se eh um numero, nao um operador ou parentese */
    {
      transforma_inteiro(no);
      while (str[(*i + 1)] > 47) /*enquanto o proximo char for um numero (por ex, o "2" que viria depois do "4" em "42") */
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

  if ((41 < no->valor && no->valor < 48)) /* se eh um operador */
  {
    int operando_esquerdo = posordem(no->esq);
    int operando_direito = posordem(no->dir);
    printf("%d %c %d\n", operando_esquerdo, no->valor, operando_direito);

    switch (no->valor)
    {
    case '*':
      return operando_esquerdo * operando_direito;
    case '+':
      return operando_esquerdo + operando_direito;
    case '-':
      return operando_esquerdo - operando_direito;
    case '/':
      return operando_esquerdo / operando_direito;
    default:

      return 0;
    }
  }
  else
    return no->valor_int;
}

int main(void)
{
  struct tNo *n = NULL;
  int i = 0;
  char expressao[100];

  printf("Insira a expressao: ");
  scanf("%s", expressao);

  n = montaarvore(expressao, &i);
  /*n = montaarvore("(*(5)(+(420)(33))\n", &i);*/
  /*n=montaarvore("(A(B(C(D(E)))))\n",&i);*/

  printf("%d -- disse o algoritmo, com uma majestade e uma tranquilidade infinitas.\n", posordem(n));
  return 0;
}
