# O que são OpenMP tasks
<br/>
O openMP é uma API, de programção paralela e menoria compartinhada, como CPUs multi-core e computadores clusterizados. A tasks é uma diretiva do openMP que permite que o programada crie unidades de trabalho independente que podem ser executado em paralelo.
<br/>
<br/>
<br/>

# Como utilizar

As seções independente de bloco de código, para ser resolvido por múltiplas threads pode ser declarado da seguinte forma:


```c
#pragma omp parallel sections
{
    #pragma omp section
    {
        Task 1
    }
    #pragma omp section
    {
        Tasks 2 
    }
}
```

Dentro de cada section pode ser executado uma função específica e distinta, a ser executado por uma thread distinta.

<br/>

Outra forma de ultiliza as tasks é:
```c
#pragma omp parallel 
{
    #pragma omp task
    {
        // seu codigo
    }
}
```
Como a diretiva "#pragma omp task", é adicionado no fila de tarefas openMP o bloco de código, passado pela task. E assim que uma thread esteja ociosa, ela buscará na fila de tarefa do openMP, uma tarefa para fazer.
Caso você queria que o programa espere todas task finalize, pode fazer da seguinte forma:

```c
#pragma omp parallel 
{
    #pragma omp task
    {
        // seu codigo
    }


    #pragma omp task
    {
        // seu codigo
    }

    #pragma omp taskwait // força o programa a espera todas as task serem resolvida 
}
```
Tambem é posivel fazer uma task ser dependente da outra task, da seguinte forma:
```c
#pragma omp parallel
{
    #pragma omp single default(none)
    {
        float a, b, c;
        #pragma omp task depend( OUT: a ) // "a" é a saida dessa task 
            a = 10.;
        #pragma omp task depend( IN: a, OUT: b ) // para a execução dessa taks inicia é necessario a task anterior termina, pois "a" é a entrada dessa task 
            b = a + 16.;
        #pragma omp task depend( IN: b )
        c    = b + 12.;
    }
    #pragma omp taskwait
}
``` 



<br/>

## Exemplos de utilização

```c
#include <omp.h>
#include <stdio.h>

void main(){
    int n = 10,i;
    #pragma omp parallel // inicio da regiao paralela 
    {
        #pragma omp single // Este diretiva garante que apenas uma unica thread inicia o for 
        {
            for (i = 0 ; i < n ; i++)
            #pragma omp task // 
            {
                printf("Tarefa %d executada pelo thread %d \n",i,omp_get_thread_num());
            }
        }
    }
}
```


