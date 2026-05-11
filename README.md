# Problemas Clássicos de Sincronização em Sistemas Operacionais

## Visão Geral

Este diretório contém implementações de problemas clássicos de sincronização em sistemas operacionais. Os scripts demonstram o uso de semáforos e mecanismos de exclusão mútua para resolver problemas de concorrência entre processos e threads.

As implementações estão divididas em dois grupos:
- **ScriptC**: Implementações em C utilizando POSIX threads
- **ScriptPython**: Implementações em Python utilizando threading

## Estrutura de Diretórios

```
ProblemasClassicos/
├── ScriptC/
│   ├── barbeirodorminhoco.c       (Compilado: barbeirodorminhoco)
│   ├── leitorescritor.c           (Compilado: leitorescritor)
│   └── ...
├── ScriptPython/
│   ├── jantardosfilosofos.py
│   ├── produtoconsumidor.py
│   └── ...
└── Assets/
    └── (Saídas e resultados da execução dos scripts)
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

## Problemas Implementados

### 1. Leitor-Escritor (Reader-Writer Problem)

#### Descrição
O problema do leitor-escritor ocorre quando múltiplos leitores precisam acessar simultaneamente um recurso compartilhado para leitura, enquanto escritores precisam garantir acesso exclusivo para modificação. A solução implementa prioridade para leitores.

#### Arquivos
| Arquivo | Linguagem | Tipo |
|---------|-----------|------|
| `ScriptC/leitorescritor.c` | C | Fonte |
| `ScriptC/leitorescritor` | C | Executável |

#### Pré-requisitos
- GCC compilador
- POSIX threads (pthread)
- Semáforos (semaphore.h)

#### Compilação

```bash
cd ScriptC
gcc -pthread leitorescritor.c -o leitorescritor
```

#### Execução

```bash
./leitorescritor
```

#### Saída Esperada
```
Reader is reading: 0
Writer is writing: 1
Reader is reading: 1
Reader is reading: 1
Writer is writing: 2
...
```

A saída mostra alternância entre leitores e escritores acessando o recurso compartilhado.

---

### 2. Produtor-Consumidor (Producer-Consumer Problem)

#### Descrição
O problema do produtor-consumidor modela a situação onde um ou mais produtores geram dados e os colocam em um buffer, enquanto consumidores retiram e processam esses dados. Utiliza semáforos para controlar a capacidade do buffer.

#### Arquivos
| Arquivo | Linguagem | Tipo |
|---------|-----------|------|
| `ScriptPython/produtoconsumidor.py` | Python | Fonte |

#### Pré-requisitos
- Python 3.6 ou superior
- Módulo threading (incluído na stdlib)

#### Execução

```bash
cd ScriptPython
python3 produtoconsumidor.py
```

#### Saída Esperada
```
Producer produced: 1
Consumer consumed item: 1
Producer produced: 2
Producer produced: 3
Consumer consumed item: 2
Consumer consumed item: 3
...
```

A saída mostra a produção e consumo de itens do buffer. O consumidor aguarda itens se o buffer estiver vazio, e o produtor aguarda espaço se o buffer estiver cheio.

#### Parâmetros Configuráveis
| Parâmetro | Valor Padrão | Descrição |
|-----------|-------------|-----------|
| `CAPACITY` | 10 | Tamanho máximo do buffer |
| Items produzidos | 20 | Quantidade de itens produzidos antes de encerrar |

---

### 3. Jantar dos Filósofos (Dining Philosophers Problem)

#### Descrição
O problema do jantar dos filósofos representa um deadlock clássico onde cinco filósofos se sentam em torno de uma mesa redonda com cinco hashis. Cada filósofo alterna entre pensar e comer, precisando de ambos os hashis (esquerdo e direito) para comer. A solução evita deadlock permitindo que um filósofo desista se não conseguir ambos os hashis.

#### Arquivos
| Arquivo | Linguagem | Tipo |
|---------|-----------|------|
| `ScriptPython/jantardosfilosofos.py` | Python | Fonte |

#### Pré-requisitos
- Python 3.6 ou superior
- Módulos: threading, time, random

#### Execução

```bash
cd ScriptPython
python3 jantardosfilosofos.py
```

#### Saída Esperada
```
Filósofo 0 está pensando
Filósofo 1 está pensando
Filósofo 2 começou a comer
[0, 0, 1, 0, 0]
Filósofo 3 está pensando
Filósofo 4 está pensando
Filósofo 1 começou a comer
[0, 1, 1, 0, 0]
...
```

A saída mostra filósofos alternando entre pensar e comer, com um vetor indicando quantas vezes cada filósofo comeu.

#### Parâmetros Configuráveis
| Parâmetro | Descrição |
|-----------|-----------|
| `Tempo de reflexão` | Varia entre 5 e 15 segundos |
| `Tempo de refeição` | Varia entre 5 e 10 segundos |
| `Número de filósofos` | 5 (fixo na implementação) |

---

### 4. Barbeiro Dorminhoco (Sleeping Barber Problem)

#### Descrição
O problema do barbeiro dorminhoco modela uma barbearia onde um barbeiro atende clientes. Se não há clientes, o barbeiro dorme em sua cadeira. Quando um cliente chega, acorda o barbeiro se estiver dormindo ou aguarda em uma cadeira de espera. Após o atendimento, o cliente sai. O problema é sincronizar o barbeiro e os clientes.

#### Arquivos
| Arquivo | Linguagem | Tipo |
|---------|-----------|------|
| `ScriptC/barbeirodorminhoco.c` | C | Fonte |
| `ScriptC/barbeirodorminhoco` | C | Executável |

#### Pré-requisitos
- GCC compilador
- POSIX threads (pthread)
- Semáforos (semaphore.h)

#### Compilação

```bash
cd ScriptC
gcc -pthread barbeirodorminhoco.c -o barbeirodorminhoco
```

#### Execução

```bash
./barbeirodorminhoco
```

#### Saída Esperada
```
Customer 1 arrived
Barber is cutting hair
Customer 2 arrived
Customer 2 is waiting
Customer 1 finished haircut
Customer 2 is getting a haircut
...
```

A saída mostra chegadas de clientes, esperas em fila e o barbeiro processando os cortes de cabelo sequencialmente.

#### Parâmetros Configuráveis
| Parâmetro | Valor Padrão | Descrição |
|-----------|-------------|-----------|
| `CHAIRS` | 5 | Número de cadeiras de espera |
| Intervalo de clientes | 1 segundo | Tempo entre chegadas de novos clientes |

---

## Instruções Gerais de Execução

### Compilar todos os programas em C

```bash
cd ScriptC
gcc -pthread leitorescritor.c -o leitorescritor
gcc -pthread barbeirodorminhoco.c -o barbeirodorminhoco
```

### Executar todos os programas em Python

```bash
cd ScriptPython
python3 jantardosfilosofos.py &
python3 produtoconsumidor.py &
```

### Interromper execução

Pressione `Ctrl+C` no terminal para interromper qualquer um dos scripts.

---

## Saídas do Sistema

As saídas de execução de cada script estão documentadas na pasta `Assets/`. Esta pasta contém:

- Exemplos de saída padrão de cada programa
- Logs de execução
- Análise de sincronização entre threads
- Mensagens de erro e sincronização

Consulte os arquivos em `Assets/` para ver exemplos completos de execução e comportamento esperado.

---

## Notas Importantes

1. **Programas em C** utilizam threads POSIX e semáforos, exigindo compilação com a flag `-pthread`.

2. **Programas em Python** utilizam o módulo `threading` nativo, não requerendo compilação.

3. **Execução Contínua**: A maioria dos programas executa indefinidamente. Utilize `Ctrl+C` para interromper.

4. **Deadlock**: Os programas implementam mecanismos para evitar deadlock, mas o comportamento pode variar conforme timing de threads.

5. **Saída em Tempo Real**: A saída é exibida conforme eventos ocorrem, não sequencialmente, devido à natureza assíncrona das threads.

---

## Troubleshooting

| Problema | Solução |
|----------|---------|
| Erro: `pthread.h: No such file or directory` | Instale desenvolvimento de pthread: `sudo apt-get install libpthread-stubs0-dev` |
| Erro: `unresolved reference to 'sem_init'` | Compile com `-pthread` flag: `gcc -pthread arquivo.c -o executavel` |
| Programa em Python não inicia | Verifique versão: `python3 --version` (Python 3.6+) |
| Deadlock ocorre | Interrompa com `Ctrl+C` e releia a implementação dos semáforos |

---

**Última atualização**: 11 de maio de 2026
