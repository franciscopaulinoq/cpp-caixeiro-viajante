#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int N = 5;
const int INF = numeric_limits<int>::max();

vector<vector<int>> dist = {
    {0, 2, INF, 3, 6},
    {2, 0, 4, 3, INF},
    {INF, 4, 0, 7, 3},
    {3, 3, 7, 0, 3},
    {6, INF, 3, 3, 0}};

int min_cost = INF;
vector<int> best_path;

void printPath()
{
    cout << "O menor custo encontrado foi: " << min_cost << endl;

    cout << "Caminho: ";
    for (int i = 0; i < best_path.size(); ++i)
    {
        cout << best_path[i] + 1;
        if (i < best_path.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

void findPath(int actual_node, vector<bool> &visited, int actual_cost, int visited_quantity, vector<int> &actual_path)
{
    if (visited_quantity == N)
    {
        if (dist[actual_node][0] != INF)
        {
            actual_cost = actual_cost + dist[actual_node][0];

            if (actual_cost < min_cost)
            {
                min_cost = actual_cost;
                best_path = actual_path;
                best_path.push_back(0);
            }

            // if (actual_cost <= min_cost)
            // {
            //     min_cost = actual_cost;
            //     best_path = actual_path;
            //     best_path.push_back(0);
            //     printPath();
            // }
        }
        return;
    }

    for (int next_node = 0; next_node < N; ++next_node)
    {
        if (visited[next_node])
        {
            continue;
        }

        if (dist[actual_node][next_node] == INF)
        {
            continue;
        }

        visited[next_node] = true;
        actual_path.push_back(next_node);

        findPath(next_node,
                 visited,
                 actual_cost + dist[actual_node][next_node],
                 visited_quantity + 1,
                 actual_path);

        visited[next_node] = false;
        actual_path.pop_back();
    }
}

int main()
{
    int start_node = 0;
    vector<bool> visited(N, false);
    vector<int> actual_path;

    visited[start_node] = true;
    actual_path.push_back(start_node);

    findPath(start_node, visited, 0, 1, actual_path);

    if (min_cost == INF)
    {
        cout << "Nao foi encontrado um caminho possivel que visite todas as cidades." << endl;
    }
    else
    {
        printPath();
    }
}