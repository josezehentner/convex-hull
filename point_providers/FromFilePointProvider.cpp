#include "FromFilePointProvider.h"

FromFilePointProvider::FromFilePointProvider(const std::string& filename)
    : m_filename(filename) {}

std::vector<Point> FromFilePointProvider::getPoints() {
    std::vector<Point> points;
    std::ifstream file(m_filename);

    if (!file.is_open()) {
        return points;
    }

    int n;
    file >> n;
    points.reserve(n);

    std::string line;
    std::getline(file, line);

    for (int i = 0; i < n; i++) {
        if (!std::getline(file, line)) break;

        std::stringstream ss(line);
        float x;
        float y;
        char comma;
        if (ss >> x >> comma >> y) {
            points.push_back({x, y});
        }
    }

    return points;
}
