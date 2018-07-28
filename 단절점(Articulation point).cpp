#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define MV 10000

vector<int> adj[MV];
int discov[MV];
int parent[MV];
int low[MV];
vector<int> AP;
int time;

void DFS(int now) {
	discov[now] = time++;
	low[now] = time;
	int sub = 0;
	for (int it : adj[now]) {
		if (it == parent[now]) continue; 

		if (discov[it] == 0) {
			parent[it] = now;
			sub = sub + 1;

			DFS(it);

			if (parent[now] == 0 && sub > 1)
				AP.push_back(now);
			else if (parent[now] != 0 && low[it] >= discov[now])
				AP.push_back(now);

			low[now] = min(low[now], low[it]);
		}
		else {
			low[now] = min(low[now], discov[it]);
		}
	}
}

int main() {
	int V, E;
	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 0; i < V; i++)
		if (!discov[i])
			DFS(i);

	sort(AP.begin(), AP.end());
	vector<int>::iterator it;
	it = unique(AP.begin(), AP.end());
	AP.erase(it, AP.end());

	for (int it : AP)
		printf("%d\n", it);
}