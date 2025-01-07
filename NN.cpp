#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Struct để lưu thông tin về cạnh
struct Edge {
    int u, v;       // Hai thành phố
    double weight;  // Khoảng cách giữa hai thành phố
};

// Hàm tìm thành phố gần nhất chưa ghé thăm
int findNearestCity(int currentCity, const vector<Edge>& edges, const vector<bool>& visited) {
    double nearestDistance = numeric_limits<double>::max();
    int nearestCity = -1;

    for (const auto& edge : edges) {
        if (edge.u == currentCity && !visited[edge.v] && edge.weight < nearestDistance) {
            nearestDistance = edge.weight;
            nearestCity = edge.v;
        }
        else if (edge.v == currentCity && !visited[edge.u] && edge.weight < nearestDistance) {
            nearestDistance = edge.weight;
            nearestCity = edge.u;
        }
    }
    return nearestCity;
}

int main() {
    int n; // Số lượng thành phố
    cout << "Nhập số lượng thành phố: ";
    cin >> n;

    vector<Edge> edges; // Danh sách các cạnh

    cout << "Nhập khoảng cách giữa các thành phố (ma trận khoảng cách):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double weight;
            cin >> weight;
            if (i < j) { // Lưu cạnh một lần (tránh trùng lặp)
                edges.push_back({ i, j, weight });
            }
        }
    }

    // Thuật toán Nearest Neighbor
    vector<bool> visited(n, false); // Đánh dấu các thành phố đã ghé thăm
    vector<int> path;               // Đường đi
    double totalDistance = 0.0;     // Tổng khoảng cách

    int currentCity = 0; // Bắt đầu từ thành phố đầu tiên
    visited[currentCity] = true;
    path.push_back(currentCity);

    for (int i = 0; i < n - 1; ++i) {
        int nearestCity = findNearestCity(currentCity, edges, visited);
        if (nearestCity != -1) {
            // Tìm cạnh phù hợp để cộng khoảng cách
            for (const auto& edge : edges) {
                if ((edge.u == currentCity && edge.v == nearestCity) ||
                    (edge.v == currentCity && edge.u == nearestCity)) {
                    totalDistance += edge.weight;
                    break;
                }
            }
            visited[nearestCity] = true;
            path.push_back(nearestCity);
            currentCity = nearestCity;
        }
    }

    // Quay trở lại thành phố ban đầu
    for (const auto& edge : edges) {
        if ((edge.u == currentCity && edge.v == path[0]) ||
            (edge.v == currentCity && edge.u == path[0])) {
            totalDistance += edge.weight;
            break;
        }
    }
    path.push_back(path[0]);

    // In kết quả
    cout << "Chu trình tối ưu gần đúng:\n";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
    cout << "Tổng khoảng cách: " << totalDistance << endl;

    return 0;
}
