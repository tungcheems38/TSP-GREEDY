/*#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Cấu trúc lưu thông tin về cạnh
struct Edge {
    int u, v;       // Đỉnh đầu và đỉnh cuối
    double weight;  // Trọng số của cạnh (khoảng cách)
};

// Hàm so sánh để sắp xếp các cạnh theo trọng số tăng dần
bool compareEdge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Tìm tập cha của một đỉnh trong Union-Find
int findParent(vector<int>& parent, int node) {
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent, parent[node]);
}

// Hợp nhất hai tập trong Union-Find
void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        }
        else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}


int main() {
    int n; // Số lượng thành phố
    cout << "Nhập số lượng thành phố: ";
    cin >> n;

    vector<Edge> edges; // Danh sách các cạnh

    cout << "Nhập ma trận khoảng cách giữa các thành phố:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double weight;
            cin >> weight;
            if (i < j) { // Chỉ lưu cạnh một lần để tránh trùng lặp
                edges.push_back({ i, j, weight });
            }
        }
    }

    // Sắp xếp các cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end(), compareEdge);

    vector<int> parent(n);
    vector<int> rank(n, 0);

    // Khởi tạo Union-Find
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    vector<Edge> result;       // Các cạnh trong chu trình
    vector<int> degree(n, 0);  // Đếm bậc của mỗi đỉnh

    for (const Edge& edge : edges) {
        if (result.size() == n) break; // Đủ chu trình, thoát

        int u = edge.u;
        int v = edge.v;

        // Kiểm tra điều kiện:
        // - Không tạo đỉnh có bậc > 2
        // - Không tạo chu trình chưa bao gồm tất cả các thành phố
        if (degree[u] < 2 && degree[v] < 2 && findParent(parent, u) != findParent(parent, v)) {
            result.push_back(edge);
            unionSets(parent, rank, u, v);
            degree[u]++;
            degree[v]++;
        }
    }

    // Ghép các cạnh còn thiếu để hoàn thành chu trình Hamilton
    for (const Edge& edge : edges) {
        int u = edge.u;
        int v = edge.v;

        if (degree[u] < 2 && degree[v] < 2) {
            result.push_back(edge);
            degree[u]++;
            degree[v]++;
            if (result.size() == n) break;
        }
    }

    // In kết quả
    cout << "Chu trình tối ưu gần đúng:\n";
    double totalWeight = 0.0;
    for (const Edge& edge : result) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Tổng trọng số: " << totalWeight << endl;

    return 0;
}
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Cấu trúc lưu thông tin về cạnh
struct Edge {
    int u, v;       // Đỉnh đầu và đỉnh cuối
    double weight;  // Trọng số của cạnh (khoảng cách)
};

// Hàm so sánh để sắp xếp các cạnh theo trọng số tăng dần
bool compareEdge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Tìm tập cha của một đỉnh trong Union-Find
int findParent(vector<int>& parent, int node) {
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent, parent[node]);
}

// Hợp nhất hai tập trong Union-Find
void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        }
        else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int main() {
    int n; // Số lượng thành phố
    cout << "Nhập số lượng thành phố: ";
    cin >> n;

    vector<Edge> edges; // Danh sách các cạnh

    cout << "Nhập ma trận khoảng cách giữa các thành phố:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double weight;
            cin >> weight;
            if (i < j) { // Chỉ lưu cạnh một lần để tránh trùng lặp
                edges.push_back({ i, j, weight });
            }
        }
    }

    // Sắp xếp các cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end(), compareEdge);

    vector<int> parent(n);
    vector<int> rank(n, 0);

    // Khởi tạo Union-Find
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    vector<Edge> result;       // Các cạnh trong chu trình
    vector<int> degree(n, 0);  // Đếm bậc của mỗi đỉnh

    for (const Edge& edge : edges) {
        if (result.size() == n) break; // Đủ chu trình, thoát

        int u = edge.u;
        int v = edge.v;

        // Kiểm tra điều kiện:
        // - Không tạo đỉnh có bậc > 2
        // - Không tạo chu trình chưa bao gồm tất cả các thành phố
        if (degree[u] < 2 && degree[v] < 2 && findParent(parent, u) != findParent(parent, v)) {
            result.push_back(edge);
            unionSets(parent, rank, u, v);
            degree[u]++;
            degree[v]++;
        }
    }

    // Ghép các cạnh còn thiếu để hoàn thành chu trình Hamilton
    for (const Edge& edge : edges) {
        int u = edge.u;
        int v = edge.v;

        if (degree[u] < 2 && degree[v] < 2) {
            result.push_back(edge);
            degree[u]++;
            degree[v]++;
            if (result.size() == n) break;
        }
    }

    // Xây dựng chu trình từ danh sách cạnh
    vector<int> tour;
    vector<bool> visited(n, false);
    int current = 0;
    tour.push_back(current);
    visited[current] = true;

    while (tour.size() < n) {
        for (const Edge& edge : result) {
            if (edge.u == current && !visited[edge.v]) {
                tour.push_back(edge.v);
                visited[edge.v] = true;
                current = edge.v;
                break;
            }
            else if (edge.v == current && !visited[edge.u]) {
                tour.push_back(edge.u);
                visited[edge.u] = true;
                current = edge.u;
                break;
            }
        }
    }

    // Kết nối lại thành phố đầu tiên để tạo thành chu trình
    tour.push_back(tour[0]);

    // In kết quả
    cout << "Chu trình tối ưu gần đúng:\n";
    for (int i = 0; i < tour.size(); ++i) {
        cout << tour[i];
        if (i != tour.size() - 1) cout << " -> ";
    }
    cout << endl;

    // Tính tổng trọng số
    double totalWeight = 0.0;
    for (int i = 0; i < tour.size() - 1; ++i) {
        for (const Edge& edge : result) {
            if ((edge.u == tour[i] && edge.v == tour[i + 1]) ||
                (edge.v == tour[i] && edge.u == tour[i + 1])) {
                totalWeight += edge.weight;
                break;
            }
        }
    }

    cout << "Tổng trọng số: " << totalWeight << endl;

    return 0;
}
