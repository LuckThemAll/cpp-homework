#include <utility>
#include <vector>
#include <cmath>

class Base;
class Line;
class PolyLine;
class Circle;

class Point {
public:
    Point() = default;
    Point(double x, double y) : x(x), y(y) {};
    double get_x(){ return this->x; };
    double get_y(){ return this->y; };
    void set_x(double x){this->x = x; };
    void set_y(double y){this->y = y; };

private:
    double x, y;
};

class Base {
public:
    virtual double length() = 0;
    virtual std::vector<Point> intersect(Base&) = 0;
    virtual std::vector<Point> intersect(Line&) = 0;
    virtual std::vector<Point> intersect(PolyLine&) = 0;
    virtual std::vector<Point> intersect(Circle&) = 0;
};

class Line : public Base {
public:
    Line(Point a, Point b) : a(a), b(b){};
    Point get_first_point(){ return this->a; };
    Point get_second_point(){ return this->b; };
    double length() override { return sqrt(
                pow(this->get_first_point().get_x() - this->get_second_point().get_x(), 2) +
                pow(this->get_first_point().get_x() - this->get_second_point().get_x(), 2)); };
    std::vector<Point> intersect(Base&) override;
    std::vector<Point> intersect(Line&) override;
    std::vector<Point> intersect(PolyLine&) override;
    std::vector<Point> intersect(Circle&) override;
private:
    Point a, b;
};

class PolyLine : public Base {
public:
    explicit PolyLine(std::vector<Point> points) : points(std::move(points)){};
    int p_counts(){ return this->points.size(); };
    Point get_point(int index) { return this->points[index]; }
    Line get_line(int index);
    double length() override;
    std::vector<Point> intersect(Base&) override;
    std::vector<Point> intersect(Line&) override;
    std::vector<Point> intersect(PolyLine&) override;
    std::vector<Point> intersect(Circle&) override;

private:
    std::vector<Point> points;
};

class Circle : public Base {
public:
    Circle(Point center, double radius) : center(center), radius(radius) {};
    Point get_center() { return this->center; };
    double get_radius() { return this->radius; };
    double length() override { return 2*M_PI*this->get_radius(); };
    std::vector<Point> intersect(Base&) override;
    std::vector<Point> intersect(Line&) override;
    std::vector<Point> intersect(PolyLine&) override;
    std::vector<Point> intersect(Circle&) override;
private:
    Point center;
    double radius;
};