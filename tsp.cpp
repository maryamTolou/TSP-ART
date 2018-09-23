#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip>
#include <map>
#include <deque>
#include <list>
#include <fstream>
#include <limits.h>

using namespace std;

#define pint pair<int, int> 
#define F first
#define S second
#define M int(1e3 + 10)
#define pub push_back

int path[M];
pint coordinate[M];
double dist[M][M];
int n;

void read_input() {
	ifstream input("coordinate.txt");
	input >> n;
	int x, y; 
	for (int i = 1; i <= n; i++) {
		input >> x >> y;
		coordinate[i] = {x, y};
	}

	input.close();
}

void prepare_dist() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			pint iCoor = coordinate[i];
			pint jCoor = coordinate[j];
			dist[i][j] = dist[j][i] = sqrt(pow(iCoor.F - jCoor.F, 2) + pow(iCoor.S - jCoor.S, 2));
		}
	}
}


////////////////////////// MST //////////////////////////

int parent[M];
int height[M];
priority_queue <pair <pint, int> > adjacent[M];
queue <int> min_tour;
bool mark[M];

void pre_order_walk(int ver) {
	if (mark[ver]) return;
	mark[ver] = true;

	min_tour.push(ver);
	while (!adjacent[ver].empty()) {
		int kid = adjacent[ver].top().S;
		adjacent[ver].pop();
		pre_order_walk(kid);
	}
}

int find_parent(int vertex) {
	while (vertex != parent[vertex]) vertex = parent[vertex];
	return vertex;
}

bool merge(int a, int b) {
	int parA = find_parent(a);
	int parB = find_parent(b);

	if (parA == parB) return false;

	if (height[parA] > height[parB]) {
		parent[parB] = parA;
	}
	else if (height[parA] < height[parB]) {
		parent[parA] = parB;
	}
	else {
		parent[parA] = parB;
		height[parB]++;
	}

	return true;
}

void kruskal() {
	for (int i = 1; i <= n; i++) parent[i] = i;

	vector <pair <double, pint> > edges;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			edges.pub({dist[i][j], {i, j}});
		}
	}
	sort(edges.begin(), edges.end());


	int temp_num = 0;
	for (int i = 0; i < edges.size(); i++) {
		int head = edges[i].S.F;
		int tail = edges[i].S.S;

		if (merge(head, tail)) {
			adjacent[head].push({coordinate[tail], tail});
			adjacent[tail].push({coordinate[head], head});
			temp_num++;
			if (temp_num == n - 1) 
				break;
		}
	}

	/*
	for (int i = 1; i <= n; i++) {
		cout << i << "    ";
		while (!adjacent[i].empty()) {
			int top = adjacent[i].top();
			adjacent[i].pop();
			cout << top << " ";
		}
		cout << endl;
	}

	exit(0);
	*/
}

void build_tour() {
	min_tour.push(min_tour.front());

	while (!min_tour.empty()) {
		int head = min_tour.front();
		min_tour.pop();
		//cout << head << " ";

		if (min_tour.empty()) break;

		path[head] = min_tour.front();
	}
}


void find_primary_tour() {
	kruskal();
	pre_order_walk(10);
	build_tour();

	/*
	cout << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << " ";
	} cout << endl;

	for (int i = 1; i <= n; i++) {
		cout << path[i] << " ";
	} cout << endl;
	*/
}

////////////////////////////K-Opt////////////////////////////////////////////////////



int find_first_min_dist(int distance_row[]) {

	int min = 100000;
	int ans = -1;
	for (int i = 0; i < M ; ++i) {
		if (distance_row[i]<min) {
			min = distance_row[i];
			ans = i;
		}
	}

	return ans;
}

int find_next_minimum(int distance_row[] , int index){
	int min = 100000;
	int ans = -1;
	for (int i = 0; i < M ; ++i) {
		if (distance_row[i]<min && i != index) {
			min = distance_row[i];
			ans = i;
		}
	}

	return ans;
}

int search_vertex(int i , int k){
	for(int j = 0 ; j < M ; j++){
		if(path[j] == i && j != k)
			return j;
	}

	return -1;
}

void reverce_cycle(int start , int final){
	int temp = path[start];
	int	k=0;
	while( temp != final ){
		k = search_vertex(temp, start);
		path[temp] = k;
		start = temp;
		temp = k;
	}
}

void k_opt( int path_inp[] ) {
	int t1;
	int t2;
	int tempT2;
	int tMin;
	int inp_edge;
	for(int i = 0 ; i < M ; i++){
		t1 = i;
		t2 = path[i];
		tempT2 = path[t2];
		tMin = find_first_min_dist(dist[t2]);
		if(tMin == tempT2){
			continue;
		}
		if(tMin == t1){
			tMin = find_next_minimum(dist[t2], t1);
			if(tMin == tempT2){
				continue;
			}
		}
		path[t2] = tMin;
		inp_edge = search_vertex(tMin , t2);
		path[t1] = inp_edge;
		reverce_cycle(t1 , t2);
	}
}


int main() {
	std::ios::sync_with_stdio(false);

	read_input();
	prepare_dist();
	find_primary_tour();
	//k_opt(path)

	return 0;
}
