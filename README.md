# Fundamentos de Sistemas Operacionais

## Visão Geral

Este repositório contém implementações práticas de conceitos fundamentais de Sistemas Operacionais, incluindo algoritmos de escalonamento de processos, manipulação de arquivos através de system calls e problemas clássicos de sincronização entre threads.

Os projetos estão organizados em três categorias principais:

| Categoria | Descrição | Linguagens |
|-----------|-----------|-----------|
| Escalonadores | Implementações de algoritmos de escalonamento de CPU | C |
| LeitorArquivosSysCall | Leitura de arquivos usando system calls | C e Assembly |
| ProblemasClassicos | Sincronização e exclusão mútua entre threads | C e Python |

## Estrutura Geral

```
.
├── Assets/                          (Saídas e logs de execução dos programas)
├── Escalonadores/                   (Algoritmos de escalonamento)
│   ├── escalonador_base.c
│   ├── round-robin.c
│   ├── prioridade.c
│   ├── SJF.c
│   └── STRF.c
├── LeitorArquivosSysCall/           (System calls para arquivos)
│   ├── leitor.c
│   ├── leitor.asm
│   ├── leitor_c
│   ├── leitor_asm
│   └── texto.txt
├── ProblemasClassicos/              (Sincronização de threads)
│   ├── ScriptC/
│   │   ├── barbeirodorminhoco.c
│   │   ├── leitorescritor.c
│   │   └── ...
│   ├── ScriptPython/
│   │   ├── jantardosfilosofos.py
│   │   ├── produtoconsumidor.py
│   │   └── ...
│   └── README.md
└── README.md (Este arquivo)
```
## Referências Bibliográficas

As implementações utilizam as seguintes referências:

### Problema do Leitor-Escritor
- MALEWAR, Harsh. Reader-Writer Problem | Process Synchronization. *Dev.to*, 2021. Disponível em: https://dev.to/harshm03/reader-writer-problem-process-synchronization-gb. Acesso em: 10 mai. 2026.

### Problema do Produtor-Consumidor
- GUPTA, Sanket. Producer-Consumer problem in Python. *AskPython*, 2021. Disponível em: https://www.askpython.com/python/producer-consumer-problem. Acesso em: 10 mai. 2026.

### Problema do Jantar dos Filósofos
- JULEK, Gabriel; STRACK, Rafael. Jantar dos Filósofos - Python. *UEPG*, 2021. Disponível em: https://deinfo.uepg.br/~alunoso/2021/SO/Filosofos_python/. Acesso em: 10 mai. 2026.

### Problema do Barbeiro Dorminhoco
- ALVAREZ, Diego. O Problema do Barbeiro Dorminhoco com Semáforos. *Blog de Desenvolvimento*, 2009. Disponível em: https://ces33.blogspot.com/2009/05/o-problema-do-barbeiro-dorminhoco-com_07.html. Acesso em: 10 mai. 2026.

### Referências Adicionais
- TONIN, Camila R. Processos de Escalonamento. *Blog de Escalonamento de Processos*, 2010. Disponível em: http://escalonamentoprocessos.blogspot.com/search/label/*Problemas%20Cl%C3%A1ssicos. Acesso em: 10 mai. 2026.

- TANENBAUM, Andrew S. Sistemas operacionais modernos. 3. ed. São Paulo: Pearson Educación, 2009.

---

