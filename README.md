# mpi
## Estudo de computação paralela - MPI



### Pasta sc 

* Arquivos do código fonte

### Pasta utility

* Arquivo hostfile - Configuração dos hosts para execução MPI
* Arquivo makefile - Automação para compilação e execução MPI


#### Condição para uso

- Copiar hostfile e makefile para pasta compartilhada MPI;
- Ajustar conforme a necessidade;

#### Alternativas de Utilização

1) $ make
2) $ make np=n
3) $ make run
4) $ make run np=n
5) $ make runt
6) $ make runt np=n

##### onde:
##### run np=2 é a configuração default
##### n = número de processos passados para np
##### runt exibe valores de estatística da execução





