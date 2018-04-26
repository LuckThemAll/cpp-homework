#include <utility>
#include <vector>
#include <cmath>

class Base;
class Line;
class PolyLine;
class Circle;

class Point {
public:
    Point(){};
    Point(double x, double y) : x(x), y(y) {}
    double get_x() const { return this->x; }
    double get_y() const { return this->y; }
    void set_x(double x){this->x = x; }
    void set_y(double y){this->y = y; }

private:
    double x, y;
};

class Base {
public:
    virtual double length() const = 0;
    virtual std::vector<Point> intersect(const Base&) const = 0;
    virtual std::vector<Point> intersect(const Line&) const = 0;
    virtual std::vector<Point> intersect(const PolyLine&) const = 0;
    virtual std::vector<Point> intersect(const Circle&) const = 0;
};

class Line : public Base {
public:
    Line(Point a, Point b) : a(a), b(b){};
    Point get_first_point() const { return a; };
    Point get_second_point() const { return b; };
    double length() const override { return sqrt(
                pow(get_first_point().get_x() - get_second_point().get_x(), 2) +
                pow(get_first_point().get_x() - get_second_point().get_x(), 2)); };
    std::vector<Point> intersect(const Base& obj ) const override{ return obj.intersect(*this); };
    std::vector<Point> intersect(const Line&) const override;
    std::vector<Point> intersect(const PolyLine&) const override;
    std::vector<Point> intersect(const Circle&) const override;
private:
    Point a, b;
};

class PolyLine : public Base {
public:
    explicit PolyLine(std::vector<Point> points) : points(points){};
    int p_counts() const { return points.size(); };
    Point get_point(int index) const { return points[index]; }
    Line get_line(int index) const { return Line(get_point(index), get_point(index+1)); };
    double length() const override;
    std::vector<Point> intersect(const Base& obj) const override { return obj.intersect(*this); };
    std::vector<Point> intersect(const Line& obj) const override { return obj.intersect(*this); };
    std::vector<Point> intersect(const PolyLine&) const override;
    std::vector<Point> intersect(const Circle&) const override;

private:
    std::vector<Point> points;
};

class Circle : public Base {
public:
    Circle(Point center, double radius) : center(center), radius(radius) {};
    Point get_center() const { return center; };
    double get_radius() const { return radius; };
    double length() const override { return 2*M_PI*get_radius(); };
    std::vector<Point> intersect(const Base& obj) const override { return obj.intersect(*this); };
    std::vector<Point> intersect(const Line& line) const override { return line.intersect(*this); };
    std::vector<Point> intersect(const PolyLine& polyline) const override { return polyline.intersect(*this); };
    std::vector<Point> intersect(const Circle&) const override;
private:
    Point center;
    double radius;
};