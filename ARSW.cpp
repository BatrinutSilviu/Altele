//Merge pe arbori

#include<conio.h>
#include<iostream>
#define numarNoduri 11
bool vizitat[numarNoduri];
int matriceAdiacenta[numarNoduri+1][numarNoduri+1];


void init()
{
	for each (bool iterator in vizitat)
	{
		iterator = false;
	}
	for (short i = 1; i <= numarNoduri; i++)
	{
		for (short j = 1; j <= numarNoduri; j++)
		{
			matriceAdiacenta[i][j] = 0;
		}
	}
}

void setEdge(short x,short y)
{
	matriceAdiacenta[x][y] = 1;
	matriceAdiacenta[y][x] = 1;
}

void parcurgere(short nod,short last)
{
	if (last == 0)
	{
		vizitat[nod] = true;
		std::cout << nod<<" ";
	}
	for (short nodCurent=1;nodCurent<= numarNoduri;nodCurent++)
	{
		if (vizitat[nodCurent] == false && matriceAdiacenta[nod][nodCurent] == 1 && nodCurent!=last)
		{
			vizitat[nodCurent] = true;
			std::cout << nodCurent<<" ";
			//de procesat
			parcurgere(nodCurent,nod);
		}
	}
}

int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int iterator = 1; iterator <= numarNoduri; iterator++)
		if (sptSet[iterator] == false && dist[iterator] <= min)
			min = dist[iterator], min_index = iterator;

	return min_index;
}

void dijkstra(int graph[numarNoduri+1][numarNoduri+1], int src)
{
	int dist[numarNoduri+1];
	bool sptSet[numarNoduri+1];

	for (int i = 1; i <= numarNoduri; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 1; count <= numarNoduri - 1; count++)
	{
		int minim = minDistance(dist, sptSet);
		sptSet[minim] = true;
		for (int iterator = 1; iterator <= numarNoduri; iterator++)
			if (!sptSet[iterator] && graph[minim][iterator] && dist[minim] != INT_MAX
				&& dist[minim] + graph[minim][iterator] < dist[iterator])
				dist[iterator] = dist[minim] + graph[minim][iterator];
	}
	for (int iterator = 1; iterator <= numarNoduri; iterator++)
		if(dist[iterator]!= INT_MAX)
			std::cout<<iterator<<"\t"<< dist[iterator]<<"\n";
}

void floydWarshall(int graph[numarNoduri + 1][numarNoduri + 1])
{
	int dist[numarNoduri + 1][numarNoduri + 1], i, j, k;
	for (i = 1; i <= numarNoduri ; i++)
		for (j = 1; j <= numarNoduri; j++)
		{
			if (graph[i][j] == 0)
			{
				if (i != j)
					dist[i][j] = INT_MAX;
				else
					dist[i][j] = 0;
			}
			else
				dist[i][j] = graph[i][j];
		}

	for (k = 1; k <= numarNoduri ; k++)
	{
		for (i = 1; i <= numarNoduri ; i++)
		{
			for (j = 1; j <= numarNoduri; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j] && (dist[i][k] + dist[k][j])>0)
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	for (int i = 1; i <= numarNoduri; i++)
	{
		for (int j = 1; j <= numarNoduri; j++)
		{
			if (dist[i][j] != INT_MAX)
				std::cout<<dist[i][j]<<" ";
			else
				std::cout << "0"<<" ";
		}
		printf("\n");
	}
}

int main()
{
	init();
	setEdge(1,2);
	setEdge(1,4);
	setEdge(2,3);
	setEdge(2, 5);
	setEdge(3, 6);
	setEdge(5, 6);
	setEdge(7, 8);
	setEdge(9,10);
	setEdge(10, 11);
	setEdge(11, 9);
	for (short nodCurent = 1;nodCurent <= numarNoduri;nodCurent++)
	{
		if (vizitat[nodCurent] == false)
		{
			std::cout << "Noduri in componenta conexa: \n";
			parcurgere(nodCurent, 0);
			std::cout << "\n";
			std::cout << "Dijsktra;sursa este: " << nodCurent;
			std::cout << "\n";
			dijkstra(matriceAdiacenta, nodCurent);
			std::cout << "\n";

		}
	}
	std::cout << "Floyd-Warshall:\n";
	floydWarshall(matriceAdiacenta);

	getch();
	return 0;
}