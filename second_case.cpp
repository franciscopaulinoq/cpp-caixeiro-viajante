#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int N = 18;
const int INF = numeric_limits<int>::max();

vector<vector<int>> dist = {
    {0, 20, INF, INF, INF, INF, INF, 29, INF, INF, INF, 29, 37, INF, INF, INF, INF, INF},
    {20, 0, 25, INF, INF, INF, INF, 28, INF, INF, INF, 39, INF, INF, INF, INF, INF, INF},
    {INF, 25, 0, 25, INF, INF, INF, 30, INF, INF, INF, INF, 54, INF, INF, INF, INF, INF},
    {INF, INF, 25, 0, 39, 32, 42, INF, 23, 33, INF, INF, INF, 56, INF, INF, INF, INF},
    {INF, INF, INF, 39, 0, 12, 26, INF, INF, 19, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, 32, 12, 0, 17, INF, INF, 35, 30, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, 42, 26, 17, 0, INF, INF, INF, 38, INF, INF, INF, INF, INF, INF, INF},
    {29, 28, 30, INF, INF, INF, INF, 0, INF, INF, INF, 25, 22, INF, INF, INF, INF, INF},
    {INF, INF, INF, 23, INF, INF, INF, INF, 0, 26, INF, INF, 34, INF, INF, 43, INF, INF},
    {INF, INF, INF, 33, 19, 35, INF, INF, 26, 0, 24, INF, INF, 30, 19, INF, INF, INF},
    {INF, INF, INF, INF, INF, 30, 38, INF, INF, 24, 0, INF, INF, INF, 26, INF, INF, 36},
    {29, 39, INF, INF, INF, INF, INF, 25, INF, INF, INF, 0, 27, INF, INF, 43, INF, INF},
    {INF, INF, 54, INF, INF, INF, INF, 22, 34, INF, INF, 27, 0, 24, INF, 19, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, 30, INF, INF, 24, 0, 20, 19, 17, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, 19, 26, INF, INF, 20, 0, INF, 18, 21},
    {INF, INF, INF, INF, INF, INF, INF, INF, 43, INF, INF, 43, 19, 19, INF, 0, 26, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 17, 18, 26, 0, 15},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 36, INF, INF, INF, 21, INF, 15, 0}};

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