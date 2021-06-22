#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int visted[MAX];

typedef struct EdgeNode
{
    int num;
    struct EdgeNode* next;
}*Edge[MAX];

typedef struct ALGraph
{
    Edge  edges;
    int numVertexs;
    int numEdges;
}*Graph;

typedef struct Queue
{
    int data[MAX];
    int front;
    int rear;
}* Queue;

struct EdgeNode* insert(struct EdgeNode* p, int v)
{
    struct EdgeNode* t, *e;
    if (!p)
    {
        p = (struct EdgeNode*)malloc(sizeof(struct EdgeNode));
        p->num = v;
        p->next = NULL;
    }
    else
    {
        t = (struct EdgeNode*)malloc(sizeof(struct EdgeNode));
        t->num = v;
        e = p->next;
        p->next = t;
        t->next = e;
    }
    return p;
}

Graph CreatGraph(Graph G)
{
    int i, v1, v2;
    if (!G)
        G = (Graph)malloc(sizeof(struct ALGraph));
    scanf("%d%d", &G->numVertexs, &G->numEdges);

    for (i = 0; i < G->numVertexs; i++)
        G->edges[i] = NULL;

    for (i = 0; i < G->numEdges; i++)
    {
        scanf("%d%d", &v1, &v2);
        G->edges[v1 - 1] = insert(G->edges[v1 - 1], v2 - 1);
        G->edges[v2 - 1] = insert(G->edges[v2 - 1], v1 - 1);
    }
  /*  printf("============================\n");
    for (i = 0; i < G->numVertexs; i++)
    {
        while (G->edges[i])
        {
            printf("%d ", G->edges[i]->num);
            G->edges[i] = G->edges[i]->next;
        }
        putchar('\n');
    }*/
    return G;
}

void InitQueue(Queue Q)
{
    Q->front = Q->rear = 0;
}

void ResetVist()
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        visted[i] = 0;
    }
}

void EnQueue(Queue Q, int i)
{
    if ((Q->rear + 1) % MAX == Q->front)
        return;
    Q->rear = (Q->rear + 1) % MAX;
    Q->data[Q->rear] = i;
}

int IsEmpty(Queue Q)
{
    if (Q->front == Q->rear)
        return 1;
    else
        return 0;
}

int DeQueue(Queue Q)
{
    Q->front = (Q->front + 1) % MAX;
    return Q->data[Q->front];
}

int BFS(Graph G, int i)
{
    int count = 1, tail = i, last = i, level= 0;

    Queue Q = (Queue)malloc(sizeof(struct Queue));
    InitQueue(Q);

    ResetVist();

    visted[i] = 1;
    EnQueue(Q, i);
    while (!IsEmpty(Q))
    {
        i = DeQueue(Q);
        struct EdgeNode* p = G->edges[i];
        while (p)
        {
            if (!visted[p->num])
            {
                visted[p->num] = 1;
                EnQueue(Q, p->num);
                count++;
                tail = p->num;
            }
            p = p->next;
        }
        if (i == last)
        {
            level++;
            last = tail;
        }
        if (level == 6)
            break;

    }
    return count;
}

void SDS(Graph G)
{
    int i, count;
    for (i = 0; i < G->numVertexs; i++)
    {
        count = BFS(G, i);
        printf("%d: %.2lf%%\n", i+1, ((double)count / G->numVertexs*100.0));
    }
}

int main()
{
    Graph G = NULL;
    G = CreatGraph(G);
    SDS(G);
    return 0;
}