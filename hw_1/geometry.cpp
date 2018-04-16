#include "geometry.h"

#define EPS 0.00000001

std::vector<Point> Line::intersect(Line& line) {
    std::vector<Point> result;
    double x1, y1, x2, y2, x3, y3, x4, y4;
    x1 = this->get_first_point().get_x();
    y1 = this->get_first_point().get_y();
    x2 = this->get_second_point().get_x();
    y2 = this->get_second_point().get_y();
    x3 = line.get_first_point().get_x();
    y3 = line.get_first_point().get_y();
    x4 = line.get_second_point().get_x();
    y4 = line.get_second_point().get_y();

    double d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    double u_a = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
    double u_b = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

    if (u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1) {
        Point point{};
        point.set_x(x1 + u_a * (x2 - x1));
        point.set_y(y1 + u_a * (y2 - y1));
        result.push_back(point);
    }
    return result;
}

std::vector<Point> Line::intersect(PolyLine& poly_line) {
    std::vector<Point> result;
    for (int i = 0; i < poly_line.p_counts()-1; i++) {
        Line line = poly_line.get_line(i);
        std::vector<Point> points = this->intersect(line);
        for (auto point : points)
            result.push_back(point);
    }
    return result;
}

std::vector<Point> Line::intersect(Circle& circle) {
    std::vector<Point> result;
    Point a = this->get_first_point();
    Point b = this->get_second_point();
    Point o = circle.get_center();
    double r = circle.get_radius();

    a.set_x(a.get_x() - o.get_x());
    a.set_y(a.get_y() - o.get_y());
    b.set_x(b.get_x() - o.get_x());
    b.set_y(b.get_y() - o.get_y());

    double A = a.get_y() - b.get_y();
    double B = b.get_x() - a.get_x();
    double C = a.get_x() * b.get_y() - b.get_x() * a.get_y();

    Point q{};
    q.set_x(-(A * C) / (A * A + B * B));
    q.set_y(-(B * C) / (A * A + B * B));

    if (C * C <= r * r * (A * A + B * B) + EPS) {
        if (abs(C * C - r * r * (A * A + B * B)) < EPS) {
            q.set_x(q.get_x() + o.get_x());
            q.set_y(q.get_y() + o.get_y());
            result.push_back(q);
        }
        else {
            double d = r * r - C * C / (A * A + B * B);
            double mult = sqrt(d / (A * A + B * B));
            Point v{}, w{};
            v.set_x(q.get_x() + B * mult + o.get_x());
            w.set_x(q.get_x() - B * mult + o.get_x());
            v.set_y(q.get_y() - A * mult + o.get_y());
            w.set_y(q.get_y() + A * mult + o.get_y());
            result.push_back(v);
            result.push_back(w);
        }
    }
    return result;
}

double PolyLine::length() {
    double result = 0;
    for (int i = 0; i < this->p_counts()-1; i++){
        result += this->get_line(i).length();
    }
    return result;
}

std::vector<Point> PolyLine::intersect(PolyLine& polyline) {
    std::vector<Point> result;
    for (int i = 0; i < this->p_counts()-1; i++) {
        Line line = this->get_line(i);
        std::vector<Point> points = line.intersect(polyline);
        for (auto point : points)
            result.push_back(point);
    }
    return result;
}

std::vector<Point> PolyLine::intersect(Circle& circle) {
    std::vector<Point> result;
    for (int i = 0; i < this->p_counts()-1; i++) {
        Line line = this->get_line(i);
        std::vector<Point> points = line.intersect(circle);
        for (auto point : points)
            result.push_back(point);
    }
    return result;
}

std::vector<Point> Circle::intersect(Circle& circle) {
    std::vector<Point> result;

    double d = sqrt(pow(circle.get_center().get_x() - this->get_center().get_x(), 2) +
                    pow(circle.get_center().get_y() - this->get_center().get_y(), 2));
    bool nesting = abs(circle.get_radius() - this->get_radius()) > d;
    bool no_intersection = d > circle.get_radius() + this->get_radius();
    if (!(nesting || no_intersection)) {
        double b =(pow(this->get_radius(), 2) - pow(circle.get_radius(), 2) + pow(d, 2)) / (2 * d);
        double a = d - b;
        Point p0{};
        p0.set_x(circle.get_center().get_x() + a / d * (this->get_center().get_x() - circle.get_center().get_x()));
        p0.set_y(circle.get_center().get_y() + a / d * (this->get_center().get_y() - circle.get_center().get_y()));
        if (d == circle.get_radius() + this->get_radius())
            result.push_back(p0);
        else {
            double h = sqrt(pow(circle.get_radius(), 2) - pow(a, 2));
            Point p3{}, p4{};
            p3.set_x(p0.get_x() + (this->get_center().get_y() - circle.get_center().get_y()) * h / d);
            p3.set_y(p0.get_y() - (this->get_center().get_x() - circle.get_center().get_x()) * h / d);
            p4.set_x(p0.get_x() - (this->get_center().get_y() - circle.get_center().get_y()) * h / d);
            p4.set_y(p0.get_y() + (this->get_center().get_x() - circle.get_center().get_x()) * h / d);
            result.push_back(p3);
            result.push_back(p4);
        }
        return result;
    }

    return result;
}