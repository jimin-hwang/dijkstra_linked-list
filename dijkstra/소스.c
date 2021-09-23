#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // �ڷ����� �ִ񰪰� �ּڰ��� ���ǵ� ������Ϸ� INT_MAX�� �̿��Ϸ��� ���

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 100000

int distance[MAX_VERTICES];   // �����������κ����� �ִܰ�� �Ÿ� 
int found[MAX_VERTICES];      // �湮�� ���� ǥ��

typedef struct GraphNode
{
	int vertex, weight; // ����, ����ġ
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

//�׷��� �ʱ�ȭ
void init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		g->adj_list[i] = NULL;
}

//�������Կ���
void insert_vertex(GraphType* g, int v)
{
	g->n++;
}

//��������
void insert_edge(GraphType* g, int start, int end, int w)
{
	GraphNode* node;
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = end;
	node->weight = w;
	node->link = g->adj_list[start];
	g->adj_list[start] = node; // ������ ��� ����
}

//distance���� �ּڰ��� ���ϴ� �Լ�
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) { // found�� FALSE �϶� ����
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g)
{
	static int step = 1;
	printf("step %d:", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%d ", found[i]);
	printf("\n\n");
}

// Dijkstra�� �ִ� ��� ���α׷�
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	GraphNode* p = g->adj_list[start]; // ����(start)�� ����� ��������Ʈ�� ����Ŵ
	for (i = 0; i < g->n; i++)   // �ʱ�ȭ 
	{
		if (p != NULL) {
			distance[i] = p->weight; // distance�� ����(start)���� �ٸ� ������ ������ ����ġ�� �ʱ�ȭ. ������ 0�̸�, ����0�� ��������Ʈ���� ����ġ�� �Է�
			p = p->link; // ����(start)�� ���� ���Ḯ��Ʈ�� �̵�
		}
		found[i] = FALSE;
	}

	found[start] = TRUE;    // ���� ���� �湮 ǥ�� 
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++)
	{
		print_status(g);
		u = choose(distance, g->n, found); // distance�� �ּڰ�
		found[u] = TRUE;
		GraphNode* s = g->adj_list[u]; // ���� u�� ��������Ʈ�� ����Ŵ
		for (w = 0; w < g->n; w++) {
			if (!found[w]) {

				if (distance[u] + s->weight < distance[w])
					distance[w] = distance[u] + s->weight;

			}
			s = s->link; // ����u�� ���� ���Ḯ��Ʈ�� �̵�
		}
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 6; i++)
		insert_vertex(g, i); //���� ������ (0,1) (0,2) (0,3) ó�� ������������ �Է��ϸ� ����0�� ��������Ʈ�� ����(0)=3->2->1 �� ǥ���ǰ�, ������������ �Է��ϸ� ����(0)=1->2->3 �� ǥ���Ǳ⶧���� ������������ �Է��߽��ϴ�*/
	// ������� ���� ������ INF�� ǥ��
	insert_edge(g, 0, 5, INF);
	insert_edge(g, 0, 4, INF);
	insert_edge(g, 0, 3, 10);
	insert_edge(g, 0, 2, 45);
	insert_edge(g, 0, 1, 50);
	insert_edge(g, 0, 0, INF);

	insert_edge(g, 1, 5, INF);
	insert_edge(g, 1, 4, INF);
	insert_edge(g, 1, 3, 15);
	insert_edge(g, 1, 2, 10);
	insert_edge(g, 1, 1, INF);
	insert_edge(g, 1, 0, INF);

	insert_edge(g, 2, 5, INF);
	insert_edge(g, 2, 4, 30);
	insert_edge(g, 2, 3, INF);
	insert_edge(g, 2, 2, 0);
	insert_edge(g, 2, 1, INF);
	insert_edge(g, 2, 0, INF);

	insert_edge(g, 3, 5, INF);
	insert_edge(g, 3, 4, 15);
	insert_edge(g, 3, 3, INF);
	insert_edge(g, 3, 2, INF);
	insert_edge(g, 3, 1, INF);
	insert_edge(g, 3, 0, INF);

	insert_edge(g, 4, 5, INF);
	insert_edge(g, 4, 4, INF);
	insert_edge(g, 4, 3, INF);
	insert_edge(g, 4, 2, 35);
	insert_edge(g, 4, 1, 20);
	insert_edge(g, 4, 0, INF);

	insert_edge(g, 5, 5, INF);
	insert_edge(g, 5, 4, 3);
	insert_edge(g, 5, 3, INF);
	insert_edge(g, 5, 2, INF);
	insert_edge(g, 5, 1, INF);
	insert_edge(g, 5, 0, INF);
	shortest_path(g, 0);
	free(g);
	return 0;
}