//
// Created by blalex on 4/6/25.
//

#include "polygon.h"

#include <cstddef>
#include <optional>

Polygon::Polygon(const std::vector<QPointF>& vertices) : vertices_(vertices) {
}

std::vector<QPointF> Polygon::GetVertices() const {
    return vertices_;
}

void Polygon::AddVertex(const QPointF& vertex) {
    vertices_.push_back(vertex);
}

void Polygon::UpdateLastVertex(const QPointF& new_vertex) {
    vertices_.back() = new_vertex;
}

std::optional<QPointF> Polygon::IntersectRay(const Ray& ray) {
    double min_distance = -1;
    QPointF intersection;
    for (size_t i = 0; i < std::size(vertices_); ++i) {
        const QPointF& v1 = vertices_[i];
        const QPointF& v2 = vertices_[(i + 1) % std::size(vertices_)];
        const double a = v1.y() - v2.y();
        const double b = v2.x() - v1.x();
        const double c = v1.x() * v2.y() - v2.x() * v1.y();

        const double dx = cos(ray.GetAngle());
        const double dy = sin(ray.GetAngle());

        const double denominator = a * dx + b * dy;
        if (denominator == 0) {
            continue;
        }

        const double numerator = -(a * ray.GetBegin().x() + b * ray.GetBegin().y() + c);
        const double t = numerator / denominator;
        if (t >= 0) {
            const double x = ray.GetBegin().x() + (t * dx);
            const double y = ray.GetBegin().y() + (t * dy);

            const double x_min = std::min(v1.x(), v2.x());
            const double x_max = std::max(v1.x(), v2.x());
            const double y_min = std::min(v1.y(), v2.y());
            const double y_max = std::max(v1.y(), v2.y());

            if (x >= x_min && x <= x_max && y >= y_min && y <= y_max) {
                double current_distance = std::sqrt(
                    ((x - ray.GetBegin().x()) * (x - ray.GetBegin().x())) +
                    ((y - ray.GetBegin().y()) * (y - ray.GetBegin().y())));
                if (min_distance == -1 || current_distance < min_distance) {
                    intersection.setX(x);
                    intersection.setY(y);
                    min_distance = current_distance;
                }
            }
        }
    }
    if (min_distance == -1) {
        return std::nullopt;
    }

    return intersection;
}
