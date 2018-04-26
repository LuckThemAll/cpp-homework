#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "geometry.h"
#include <string>

TEST_CASE("Contain objects of different classes in one vector") {
    std::vector<Base*> vec(3);
    Point a, b;
    a.set_x(0);
    a.set_y(2);
    b.set_x(4);
    b.set_y(6);
    vec[0] = new Line(a, b);

    std::vector<Point> points(3);
    points[0].set_x(5);
    points[0].set_y(3);
    points[1].set_x(-6);
    points[1].set_y(8);
    points[2].set_x(11);
    points[2].set_y(-7);
    vec[1] = new PolyLine(points);

    Point c;
    c.set_x(4);
    c.set_y(-9);
    vec[2] = new Circle(c, 8.0);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            std::vector<Point> result = vec[i]->intersect(*vec[j]);
}

TEST_CASE("Intersect line with line", "[]") {
    SECTION("Simple intersection") {
        Point a, b, c, d;
        a.set_x(0);
        a.set_y(0);
        b.set_x(4);
        b.set_y(4);
        c.set_x(2);
        c.set_y(0);
        d.set_x(2);
        d.set_y(4);

        Line line1(a, b);
        Line line2(c, d);

        Point expected_point(2.0, 2.0);
        std::vector<Point> result = line1.intersect(line2);

        REQUIRE(result[0].get_x() == expected_point.get_x());
        REQUIRE(result[0].get_y() == expected_point.get_y());
    }

    SECTION("No intersection") {
        Point a, b, c, d;
        a.set_x(0);
        a.set_y(0);
        b.set_x(4);
        b.set_y(4);
        c.set_x(2);
        c.set_y(3);
        d.set_x(2);
        d.set_y(4);

        Line line1(a, b);
        Line line2(c, d);

        std::vector<Point> result = line1.intersect(line2);

        REQUIRE(result.empty());
    }

    SECTION("Same point") {
        Point a, b, c, d;

        a.set_x(0);
        a.set_y(0);
        b.set_x(4);
        b.set_y(4);
        c.set_x(0);
        c.set_y(0);
        d.set_x(0);
        d.set_y(2);


        Line line1(a, b);
        Line line2(c, d);

        Point expected_point(0.0, 0.0);
        std::vector<Point> result = line1.intersect(line2);

        REQUIRE(result[0].get_x() == expected_point.get_x());
        REQUIRE(result[0].get_y() == expected_point.get_y());
    }

    SECTION("Same lines") {
        Point a, b, c, d;
        a.set_x(0);
        a.set_y(0);
        b.set_x(4);
        b.set_y(4);
        c.set_x(0);
        c.set_y(0);
        d.set_x(4);
        d.set_y(4);

        Line line1(a, b);
        Line line2(c, d);

        std::vector<Point> result = line1.intersect(line2);

        REQUIRE(result.empty());
    }

    SECTION("Very close not intersecting lines") {
        Point a, b, c, d;
        a.set_x(0);
        a.set_y(0);
        b.set_x(4);
        b.set_y(4);
        c.set_x(2);
        c.set_y(0);
        d.set_x(2);
        d.set_y(1.999999999999999);

        Line line1(a, b);
        Line line2(c, d);

        std::vector<Point> result = line1.intersect(line2);

        REQUIRE(result.empty() == true);
    }

}

TEST_CASE("Get line from broken line with wrong index", "[]") {
    std::vector<Point> points(3);
    points[0].set_x(6);
    points[0].set_y(4);
    points[1].set_y(0);
    points[1].set_y(1);
    points[2].set_x(5);
    points[2].set_y(1);
    PolyLine broken_line(points);

    try {
        Line line = broken_line.get_line(4);
    }
    catch (std::length_error exp) {
        std::string mes = exp.what();
        REQUIRE(mes == "Index error");
    }
}

TEST_CASE("Intersect line with broken line", "[]") {
    std::vector<Point> points(4);
    points[0].set_x(0);
    points[0].set_y(0);
    points[1].set_x(4);
    points[1].set_y(4);
    points[2].set_x(2);
    points[2].set_y(0);
    points[3].set_x(2);
    points[3].set_y(4);
    PolyLine broken_line(points);

    Point a, b;
    a.set_x(0);
    a.set_y(3);
    b.set_x(4);
    b.set_y(3);
    Line line(a, b);

    std::vector<Point> expected_points(3);
    expected_points[0].set_x(3);
    expected_points[0].set_y(3);
    expected_points[1].set_x(3.5);
    expected_points[1].set_y(3);
    expected_points[2].set_x(2);
    expected_points[2].set_y(3);
    SECTION("line.intersect") {
        std::vector<Point> result = line.intersect(broken_line);
        REQUIRE(result.size() == expected_points.size());
        for (int i = 0; i < result.size(); i++) {
            REQUIRE(result[i].get_x() == expected_points[i].get_x());
            REQUIRE(result[i].get_y() == expected_points[i].get_y());
        }
        SECTION("broken_line.intersect") {
            std::vector<Point> result = broken_line.intersect(line);
            REQUIRE(result.size() == expected_points.size());
            for (int i = 0; i < result.size(); i++) {
                REQUIRE(result[i].get_x() == expected_points[i].get_x());
                REQUIRE(result[i].get_y() == expected_points[i].get_y());
            }
        }
    }
}

TEST_CASE("Intersect broken line with broken line") {
    std::vector<Point> points(3);
    points[0].set_x(6);
    points[0].set_y(4);
    points[1].set_x(0);
    points[1].set_y(1);
    points[2].set_x(5);
    points[2].set_y(1);
    PolyLine first_bline(points);

    points[0].set_x(1);
    points[0].set_y(3);
    points[1].set_x(4);
    points[1].set_y(0);
    points[2].set_x(4);
    points[2].set_y(4);
    PolyLine second_bline(points);

    std::vector<Point> expected_points(4);
    expected_points[0].set_x(2);
    expected_points[0].set_y(2);
    expected_points[1].set_x(4);
    expected_points[1].set_y(3);
    expected_points[2].set_x(3);
    expected_points[2].set_y(1);
    expected_points[3].set_x(4);
    expected_points[3].set_y(1);

    std::vector<Point> result = first_bline.intersect(second_bline);
    REQUIRE(result.size() == expected_points.size());
    for (int i = 0; i < result.size(); i++) {
        REQUIRE(result[i].get_x() == expected_points[i].get_x());
        REQUIRE(result[i].get_y() == expected_points[i].get_y());
    }
}

TEST_CASE("Intersect line with circle") {
    SECTION("Simple intersection"); {
        Point a;
        a.set_x(2);
        a.set_y(2);
        Circle circle(a, 2);

        Point b;
        b.set_x(1);
        b.set_y(5);
        Point c; c.set_x(5);
        c.set_y(1);
        Line line(b, c);

        std::vector<Point> expected_points(2);
        expected_points[0].set_x(4);
        expected_points[0].set_y(2);
        expected_points[1].set_x(2);
        expected_points[1].set_y(4);

        std::vector<Point> result = line.intersect(circle);
        REQUIRE(result.size() == 2);
        for (int i = 0; i < result.size(); i++) {
            REQUIRE(expected_points[i].get_x() == result[i].get_x());
            REQUIRE(expected_points[i].get_y() == result[i].get_y());
        }
    }

    SECTION("No intersection") {
        Point a; a.set_x(2);
        a.set_y(2);
        Circle circle(a, 2);

        Point b; b.set_x(5);
        b.set_y(5);
        Point c; c.set_x(5);
        c.set_y(1);
        Line line(b, c);

        std::vector<Point> result = circle.intersect(line);
        REQUIRE(result.size() == 0);
    }

    SECTION("In one point") {
        Point a;
        a.set_x(2);
        a.set_y(2);
        Circle circle(a, 2);

        Point b;
        b.set_x(4);
        b.set_y(5);
        Point c;
        c.set_x(4);
        c.set_y(1);
        Line line(b, c);

        Point expected_point;
        expected_point.set_x(4);
        expected_point.set_y(2);

        std::vector<Point> result = line.intersect(circle);
        REQUIRE(result.size() == 1);
        REQUIRE(expected_point.get_x() == result[0].get_x());
        REQUIRE(expected_point.get_y() == result[0].get_y());
    }
}

TEST_CASE("Intersect broken line with circle") {
    std::vector<Point> points(4);
    points[0].set_x(2);
    points[0].set_y(5);
    points[1].set_x(2);
    points[1].set_y(-1);
    points[2].set_x(4);  points[2].set_y(-1);
    points[3].set_x(4);  points[3].set_y(5);
    PolyLine broken_line(points);

    Point a; a.set_x(2);
    a.set_y(2);
    Circle circle(a, 2.0);

    std::vector<Point> expected_points(3);
    expected_points[0].set_x(2);
    expected_points[0].set_y(0);
    expected_points[1].set_x(2);
    expected_points[1].set_y(4);
    expected_points[2].set_x(4);
    expected_points[2].set_y(2);

    std::vector<Point> result = circle.intersect(broken_line);
    REQUIRE(result.size() == 3);
    for (int i = 0; i < result.size(); i++) {
        REQUIRE(expected_points[i].get_x() == result[i].get_x());
        REQUIRE(expected_points[i].get_y() == result[i].get_y());
    }
}

TEST_CASE("Intersect circle with circle", "[]") {
    SECTION("Intersect in one points") {
        Point first_centre;
        first_centre.set_x(0);
        first_centre.set_y(0);
        Circle first_circle(first_centre, 3.0);

        Point second_centre;
        second_centre.set_x(0);
        second_centre.set_y(6);
        Circle second_circle(second_centre, 3.0);

        std::vector<Point> expected_points(1);
        expected_points[0].set_x(0);
        expected_points[0].set_y(3);

        std::vector<Point> result = first_circle.intersect(second_circle);
        REQUIRE(result.size() == expected_points.size());
        for (int i = 0; i < result.size(); i++) {
            REQUIRE(result[i].get_x() == expected_points[i].get_x());
            REQUIRE(result[i].get_y() == expected_points[i].get_y());
        }
    }

    SECTION("No intersection") {
        Point first_centre;
        first_centre.set_x(0);
        first_centre.set_y(0);
        Circle first_circle(first_centre, 3.0);

        Point second_centre;
        second_centre.set_x(5);
        second_centre.set_y(0);
        Circle second_circle(second_centre, 1.0);

        std::vector<Point> result = first_circle.intersect(second_circle);
        REQUIRE(result.size() == 0);
    }

    SECTION("Nested circles") {
        Point first_centre;
        first_centre.set_x(3);
        first_centre.set_y(3);
        Circle first_circle(first_centre, 3.0);

        Point second_centre;
        second_centre.set_x(3);
        second_centre.set_y(3);
        Circle second_circle(second_centre, 1.0);

        std::vector<Point> result = first_circle.intersect(second_circle);
        REQUIRE(result.size() == 0);
    }
}