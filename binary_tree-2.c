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
    printf("cria nó: %c \n", str[*i]); // deixamos esta impressao?
    no = inicia(str[*i]);
    (*i)++;
    no->esq = montaarvore(str, i);
    no->dir = montaarvore(str, i);
    (*i)++;
  }
  return no;
}

int transforma_inteiro(char no) // recebe um char e retorna um int agora que as chamadas sao feitas pela "posordem" ao inves da main
{
  if (no != 42 && no != 43 && no != 45 && no != 47) // nem vai precisar dessa condicional mais, ja que a funcao soh vai ser chamada pros numeros/folhas
  {
    no = no - 48;
  }
}

int posordem(struct tNo *no) // notacao polonesa reversa "A B op."
{
  //if(no != NULL){ // retirar este "if"? Nunca vai chegar num no nulo com essa implementacao, sempre retorna no caso de um numero/folha 
    if(!(41<no->valor && no->valor<48)) // os codigos ASCII dos operadores sao 42, 43, 45 e 47, e os demais caracteres ("," e ".") no intervalo nao sao numeros
      return transforma_inteiro(no->valor);
    
    else{
      int operador_esquerdo = posordem(no->esq);
      int operador_direito  = posordem(no->dir);

      printf("%d %c %d\n", operador_esquerdo, no->valor, operador_direito);

      switch(no->valor){
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
  //}
  return 0;
}

int main(void)
{
  struct tNo *n = NULL;
  int i = 0;
  i = 0; // nao foi iniciado na linha anterior ja?
  n = montaarvore("(*(5)(+(4)(3))\n", &i);
  /*n=montaarvore("(A(B(C(D(E)))))\n",&i);*/
  //printf("percurso em ordem:"); // vamos usar isto?

  printf("%d -- disse o algoritmo, com uma majestade e uma tranquilidade infinitas.\n", posordem(n)); // kkkkkkkkkkk
  return 0;
}
