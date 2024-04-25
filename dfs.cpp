#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

vector<bool> visited(1000); // Correctly declare visited vector

vector<int> graph[1000];

void dfs(int node)
{
    stack<int> s;
    s.push(node);

    while (!s.empty())
    {
        int curr_node = s.top();
        s.pop();

        if (!visited[curr_node])
        {
            visited[curr_node] = true;
            cout << curr_node << " "; // Output visited node here

#pragma omp parallel for // Parallelize visiting adjacent nodes
            for (int i = 0; i < graph[curr_node].size(); i++)
            {
                int adj_node = graph[curr_node][i];
                if (!visited[adj_node])
                {
                    s.push(adj_node);
                }
            }
        }
    }
}

int main()
{
    int n, m, start_node;
    cout << "Enter No. of nodes, edges, and start node: ";
    cin >> n >> m >> start_node;

    cout << "Enter pairs of edges: ";
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    dfs(start_node);

    // Optionally output all visited nodes after DFS
    // for (int i = 0; i < n; i++) {
    //     if (visited[i]) {
    //         cout << i << " ";
    //     }
    // }

    return 0;
}
