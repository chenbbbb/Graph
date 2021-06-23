#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INFINITY 65535

int dist[MAX];
int path[MAX];
int collected[MAX];

typedef struct ENode
{
	int vex;
	int weight;
	struct ENode* next;
}* Edge;

typedef struct VNode
{
	Edge firstEdge;
}AdjList[MAX];

typedef struct GNode
{
	int numVertexs;
	int numEdges;
	AdjList list;
}* Graph;

int FindMin(Graph G)
{
	int i, min, flag = 0;

	for (i = 0; i < G->numVertexs; i++)
	{
		if (!collected[i])
		{
			if (flag == 0)
			{
				flag = 1;
				min = i;
			}
			else
			{
				min = (dist[min] > dist[i]) ? i : min;
			}
		}
	}
	if (!flag)
		return -1;
	return min;
}

void Dijkstra(Graph G, int sr)
{
	while (1)
	{
		int v = FindMin(G);
		if (v == -1)
			break;
		collected[v] = 1;
		Edge p = G->list[v].firstEdge;
		while (p)
		{
			if (!collected[p->vex])
				if (dist[v] + p->weight < dist[p->vex])
				{
					dist[p->vex] = dist[v] + p->weight;
					path[p->vex] = v;
				}
			p = p->next;
		}
	}
}

int ShortestPath(Graph G, int sr, int de)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		dist[i] = INFINITY;
		path[i] = -1;
		collected[i] = 0;
	} 
	dist[sr] = 0;
	Edge p = G->list[sr].firstEdge;
	while (p)
	{
		dist[p->vex] = p->weight;
		path[p->vex] = sr;
		p = p->next;
	}
	collected[sr] = 1;
	/*for (i = 0; i < G->numVertexs; i++)
	{
		printf("%d ", dist[i]);
	}
	putchar('\n');

	for (i = 0; i < G->numVertexs; i++)
	{
		printf("%d ", path[i]);
	}
	putchar('\n');*/

	Dijkstra(G, sr);
	return dist[de];
}

Graph CreatGraph()
{
	int i, v1, v2, w;
	Graph G = (Graph)malloc(sizeof(struct GNode));
	for (i = 0; i < MAX; i++)
		G->list[i].firstEdge = NULL;
	scanf("%d%d", &G->numVertexs, &G->numEdges);
	for (i = 0; i < G->numEdges; i++)
	{
		scanf("%d%d%d", &v1, &v2, &w);
		Edge E = (Edge)malloc(sizeof(struct ENode));
		E->weight = w;
		E->vex = v2;
		E->next = G->list[v1].firstEdge;
		G->list[v1].firstEdge = E;
	}
	/*for (i = 0; i < G->numVertexs; i++)
	{
		Edge p = G->list[i].firstEdge;
		while (p)
		{
			printf("%d ", p->vex);
			p = p->next;
		}
		putchar('\n');
	}*/
	return G;
}

int main()
{
	// 7 12
	// 0 1 2 2 0 4 0 3 1 1 3 3 1 4 10 3 2 2 3 4 2 2 5 5 3 5 8 3 6 4 4 6 6 6 5 1  
	Graph G = CreatGraph();
	for (int i = 1; i < 7; i++)
	{
		int ret = ShortestPath(G, 0, i);
		printf("%d\n", ret);
	}
	
	return 0;
}