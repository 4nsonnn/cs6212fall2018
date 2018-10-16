#include<iostream>
#include<algorithm>
#include<string>
#include<time.h>
using namespace std;

bool check(int Vexnum,int edge) {
    if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}

bool check_edge(int Vexnum, int start ,int end, int weight) {
    if (start<1 || end<1 || start>Vexnum || end>Vexnum || weight < 0) {
        return false;
    }
    return true;
}

typedef struct edge_tag {
    bool visit;
    int start;
    int end;
    int weight;
}Edge;

void createGraph(Edge * &e,int Vexnum, int edge) {
    e = new Edge[edge];
    int start = 0;
    int end = 0;
    int weight = 0;

    int i = 0;
    cout << "INPUT EDGES: NODE1 NODE2 WEIGHT" << endl;
    while (i != edge)
    {
        cin >> start >> end >> weight;
        while (!check_edge(Vexnum, start, end, weight)) {
            cout << "INVALID! INPUT AGAIN: " << endl;
            cin >> start >> end >> weight;
        }
        e[i].start = start;
        e[i].end = end;
        e[i].weight = weight;
        e[i].visit = false;
        ++i;

    }
}

int cmp(const void*  first, const void * second) {
    return ((Edge *)first)->weight - ((Edge *)second)->weight;
}

int find_root(int child, int * parent) {

    if (parent[child] == child) {
        return child;
    }

    parent[child] = find_root(parent[child], parent);
    return parent[child];
}

bool union_tree(Edge  e, int * parent, int * child) {
    int root1;
    int root2;

    root1 = find_root(e.start-1, parent);
    root2 = find_root(e.end-1, parent);

    if (root1 != root2) {

        if (child[root1] > child[root2]) {
            parent[root2] = root1;
            child[root1] += child[root2] + 1;
        }
        else {
            parent[root1] = root2;
            child[root2] += child[root1] + 1;
        }
        return true;
    }
    return false;
}

void Kruskal() {
    int Vexnum = 0;
    int edge = 0;
    cout << "INPUT NUMBER OF NODES AND EDGES: NODES EDGES" << endl;
    cin >> Vexnum >> edge;
    while (!check(Vexnum, edge)) {
        cout << "INVALID! INPUT AGAIN: " << endl;
        cin >> Vexnum >> edge;
    }

    Edge * edge_tag;

    createGraph(edge_tag, Vexnum, edge);

    int * parent = new int[Vexnum];
    int * child = new int[Vexnum];
    int i;
    for (i = 0; i < Vexnum; i++) {
        parent[i] = i;
        child[i] = 0;
    }

    qsort(edge_tag, edge, sizeof(Edge), cmp);
    int count_vex;

    count_vex = i = 0;
    while (i != edge) {

        if (union_tree(edge_tag[i], parent, child)) {
            cout << ("v" + std::to_string(edge_tag[i].start))
                << "-----"
                << ("v" + std::to_string(edge_tag[i].end))
                <<"="
                << edge_tag[i].weight
                << endl;
            edge_tag[i].visit = true;
            ++count_vex;
        }

        if (count_vex == Vexnum - 1) {
            break;
        }
        ++i;
    }

    if (count_vex != Vexnum - 1) {
        cout << "NOT A CONNECTED GRAPH!" << endl;
    }
    delete [] edge_tag;
    delete [] parent;
    delete [] child;
}

int main() {
	clock_t start,finish;
	double totaltime;
	start=clock();
    Kruskal();
    finish=clock();
    totaltime=(double)(finish-start);
    cout<<"\nRUNTIME: "<<totaltime<<"ms"<<endl;
    system("pause");
    return 0;
}