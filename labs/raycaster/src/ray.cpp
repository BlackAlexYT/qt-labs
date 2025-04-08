//
// Created by blalex on 4/6/25.
//

#include "ray.h"

#include <cmath>
#include <QPointF>

Ray::Ray(const QPointF& begin, const QPointF& end, double angle)
    : begin_(begin), end_(end), angle_(angle) {
}

QPointF Ray::GetBegin() const {
    return begin_;
}

QPointF Ray::GetEnd() const {
    return end_;
}

double Ray::GetAngle() const {
    return angle_;
}

void Ray::SetBegin(const QPointF& begin) {
    begin_ = begin;
}

void Ray::SetEnd(const QPointF& end) {
    end_ = end;
}

void Ray::SetAngle(const double angle) {
    angle_ = angle;
}

Ray Ray::Rotate(const double angle) const {
    double const new_angle = angle + angle_;
    const double length = sqrt(
        ((end_.x() - begin_.x()) * (end_.x() - begin_.x())) +
        ((end_.y() - begin_.y()) * (end_.y() - begin_.y())));
    const double dx = length * cos(new_angle);
    const double dy = length * sin(new_angle);

    return Ray{begin_, QPointF{begin_.x() + dx, begin_.y() + dy}, angle_ + angle};
}
