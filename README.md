[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/AEYJWtQZ)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=13793830&assignment_repo_type=AssignmentRepo)

# Atividade
Com base no exemplo pth_pool.c, implemente o modelo de comunicação entre threads Produtor/Consumidor usando uma fila intermediária controlada por variáveis de condição. Enquanto um grupo de 3 threads produzirá relógios vetoriais que serão colocados na fila, outro grupo de 3 threads consumirá esses relógios da fila e os imprimirá na saída padrão. Para verificar o uso correto das variáveis de condição na sua tarefa de sincronização entre produtores e consumidores, crie dois cenários de teste:
 - **Cenário onde a fila ficará cheia:** Threads produtoras produzem relógios na fila em uma taxa maior que as threads consumidoras. Por exemplo, em quanto cada thread produtora produz 1 relógio na fila a cada segundo, cada thread consome 1 relógio da fila a cada dois segundos.
 - **Cenário onde a fila ficará vazia:** Threads produtoras produzem relógios na fila em uma taxa menor que as threads consumidoras. Por exemplo, em quanto cada thread produtora produz 1 relógio na fila a cada 2 segundos, cada thread consome 1 relógio da fila a cada 1 segundo. 

### Observações
 - Buffer limitado
 - 3 Produtoras
 - 3 Consumidoras

# Integrantes
- Gabriel de Souza Teles
- Matheus Lima da Cruz
