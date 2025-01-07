#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Hàm tìm khoảng cách giữa hai thành phố dựa trên ma trận khoảng cách
double getDistance(int city1, int city2, const vector<vector<double>>& distanceMatrix) {
    return distanceMatrix[city1][city2];
}

// Hàm tìm thành phố không thuộc tour mà gần nhất với một thành phố trong tour
int findNearestCity(const vector<int>& tour, const vector<bool>& inTour, const vector<vector<double>>& distanceMatrix) {
    double nearestDistance = numeric_limits<double>::max();
    int nearestCity = -1;

    for (int city = 0; city < inTour.size(); ++city) {
        if (!inTour[city]) { // Thành phố chưa thuộc tour
            for (int inTourCity : tour) { // So với các thành phố đã trong tour
                double distance = getDistance(city, inTourCity, distanceMatrix);
                if (distance < nearestDistance) {
                    nearestDistance = distance;
                    nearestCity = city;
                }
            }
        }
    }
    return nearestCity;
}

// Hàm chèn thành phố mới vào giữa hai thành phố sao cho tổng khoảng cách tăng ít nhất
void insertCity(int newCity, vector<int>& tour, const vector<vector<double>>& distanceMatrix) {
    double bestIncrease = numeric_limits<double>::max();
    int bestPosition = -1;

    // Duyệt qua từng cặp liên tiếp trong tour để tìm vị trí chèn tốt nhất
    for (int i = 0; i < tour.size(); ++i) {
        int cityA = tour[i];
        int cityB = tour[(i + 1) % tour.size()]; // Thành phố kế tiếp (vòng tròn)

        double increase = getDistance(cityA, newCity, distanceMatrix) +
            getDistance(newCity, cityB, distanceMatrix) -
            getDistance(cityA, cityB, distanceMatrix);

        if (increase < bestIncrease) {
            bestIncrease = increase;
            bestPosition = i;
        }
    }

    // Chèn thành phố mới vào vị trí tối ưu
    tour.insert(tour.begin() + bestPosition + 1, newCity);
}

int main() {
    int n; // Số lượng thành phố
    cout << "Nhập số lượng thành phố: ";
    cin >> n;

    vector<vector<double>> distanceMatrix(n, vector<double>(n)); // Ma trận khoảng cách

    cout << "Nhập ma trận khoảng cách giữa các thành phố:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> distanceMatrix[i][j];
        }
    }

    // Thuật toán Nearest Insertion
    vector<int> tour;          // Chu trình (tour)
    vector<bool> inTour(n, false); // Đánh dấu các thành phố đã trong tour

    // Bắt đầu với 2 thành phố đầu tiên (0 và thành phố gần nhất)
    tour.push_back(0);
    inTour[0] = true;

    int nearestCity = findNearestCity(tour, inTour, distanceMatrix);
    tour.push_back(nearestCity);
    inTour[nearestCity] = true;

    // Thêm dần các thành phố còn lại vào tour
    for (int i = 2; i < n; ++i) {
        // Tìm thành phố gần nhất chưa trong tour
        int newCity = findNearestCity(tour, inTour, distanceMatrix);
        inTour[newCity] = true;

        // Chèn thành phố mới vào vị trí tối ưu trong tour
        insertCity(newCity, tour, distanceMatrix);
    }

    // In kết quả
    cout << "Chu trình tối ưu gần đúng:\n";
    double totalDistance = 0.0;
    for (int i = 0; i < tour.size(); ++i) {
        cout << tour[i];
        if (i != tour.size() - 1) cout << " -> ";
        totalDistance += getDistance(tour[i], tour[(i + 1) % tour.size()], distanceMatrix);
    }
    cout << " -> " << tour[0];
    cout << endl;
    cout << "Tổng khoảng cách: " << totalDistance << endl;

    return 0;
}
