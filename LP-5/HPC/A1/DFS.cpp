#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include <fstream>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

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

            if (visited[curr_node])
            {
                cout << curr_node << " ";
            }

#pragma omp parallel for
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

void serial_dfs(int node)
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

            if (visited[curr_node])
            {
                cout << curr_node << " ";
            }

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
    double start, stop, par_time, ser_time;

    std::ifstream file("graph.txt"); // Open the file

    if (!file)
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    cout << "Enter No of Node,Edges,and start node:";
    file >> n >> m >> start_node;
    // n: node,m:edges

    cout << "Enter Pair of edges:";
    for (int i = 0; i < m; i++)
    {
        int u, v;

        file >> u >> v;
        // u and v: Pair of edges
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    start = omp_get_wtime();
    dfs(start_node);
    stop = omp_get_wtime();
    par_time = stop - start;
    printf("\nParallel Time: %g\n", stop - start);

    start = omp_get_wtime();
    serial_dfs(start_node);
    stop = omp_get_wtime();
    ser_time = stop - start;
    printf("Serial Time: %g\n", stop - start);

    string result;
    if (par_time > ser_time)
    {
        result = "Serial Faster";
    }
    else
    {
        result = "Parallel Faster";
    }
    cout << "Time Comparison: " << result << endl;

    return 0;
}