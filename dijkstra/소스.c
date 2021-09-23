#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // 자료형의 최댓값과 최솟값이 정의된 헤더파일로 INT_MAX를 이용하려고 사용

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 100000

int distance[MAX_VERTICES];   // 시작정점으로부터의 최단경로 거리 
int found[MAX_VERTICES];      // 방문한 정점 표시

typedef struct GraphNode
{
	int vertex, weight; // 정점, 가중치
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

//그래프 초기화
void init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		g->adj_list[i] = NULL;
}

//정점삽입연산
void insert_vertex(GraphType* g, int v)
{
	g->n++;
}

//간선삽입
void insert_edge(GraphType* g, int start, int end, int w)
{
	GraphNode* node;
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = end;
	node->weight = w;
	node->link = g->adj_list[start];
	g->adj_list[start] = node; // 정점에 노드 연결
}

//distance값중 최솟값을 구하는 함수
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) { // found가 FALSE 일때 실행
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

// Dijkstra의 최단 경로 프로그램
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	GraphNode* p = g->adj_list[start]; // 정점(start)에 연결된 인접리스트를 가리킴
	for (i = 0; i < g->n; i++)   // 초기화 
	{
		if (p != NULL) {
			distance[i] = p->weight; // distance에 정점(start)에서 다른 정점들 까지의 가중치를 초기화. 정점이 0이면, 정점0의 인접리스트들의 가중치를 입력
			p = p->link; // 정점(start)의 다음 연결리스트로 이동
		}
		found[i] = FALSE;
	}

	found[start] = TRUE;    // 시작 정점 방문 표시 
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++)
	{
		print_status(g);
		u = choose(distance, g->n, found); // distance중 최솟값
		found[u] = TRUE;
		GraphNode* s = g->adj_list[u]; // 정점 u의 인접리스트를 가리킴
		for (w = 0; w < g->n; w++) {
			if (!found[w]) {

				if (distance[u] + s->weight < distance[w])
					distance[w] = distance[u] + s->weight;

			}
			s = s->link; // 정점u의 다음 연결리스트로 이동
		}
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 6; i++)
		insert_vertex(g, i); //간선 삽입을 (0,1) (0,2) (0,3) 처럼 오른차순으로 입력하면 정점0의 인접리스트가 정점(0)=3->2->1 로 표현되고, 내림차순으로 입력하면 정점(0)=1->2->3 로 표현되기때문에 내림차순으로 입력했습니다*/
	// 연결되지 않은 간선은 INF로 표현
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