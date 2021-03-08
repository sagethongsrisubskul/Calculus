/*
Author:
    Sage Thongsrisubskul

About:
    This library contains classes and functions for approximating calculus problems. It also includes Euler's Method.

    Integration and derivation is performed using the graph class. A graph consists of a set of points approximating a function.
    Append points to the end of the graph using the build() method.

    The Euler function doesn't require graphs and instead only uses the vec3 and euler_data struct included.
    I wrote it entirely with solving problems involving projectile motion in mind so it might not match other implementations, or be useful for solving problems not related to kinematics.

Current limitations and quirks:
    -integration and derivation have O(n) runtime with n being the number of points in the graph.
    -The graph class can only integrate or derive on the x axis.
    -The graph class can only integrate or derive in 2 dimensions.
    -The graph must be generated from -x to +x for the integral() method to work correctly.
    -Due to the nature of the graph as a set of discrete points it is unable to find derivatives beyond first order.
    -if derivation occurs on the same x value as a point, it will use the line on the right of the point.
    -derivation beyond the bounds of the graph will use the last two points before the bounds of the graph.
    -integration beyond the bounds of the graph will return 0

Planned Improvements:
    -Integration/derivation with respect to any axis
    -Reduce derivation to log(n) runtime
    -Polar, cylindrical, and spherical integration and graphing function
    -a means of creating a curve between the points, allowing for approximation of derivatives beyond first order and greatly improving accuracy of derivation.
    -RK4
*/
#include <iostream>
#include <iterator>
#include <vector>
#include "calculus.hpp"
using namespace std;

vec3 operator+(vec3 v1, vec3 v2) {
    struct vec3 temp = { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
    return temp;
}

vec3 operator-(vec3 v1, vec3 v2) {
    struct vec3 temp = { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
    return temp;
}

vec3 operator*(vec3 v, double m) {
    struct vec3 temp = { v.x * m,v.y * m,v.z * m };
    return temp;
}

vec3 operator*(double m, vec3 v) {
    struct vec3 temp = { v.x * m,v.y * m,v.z * m };
    return temp;
}

void print(vec3 v) {
    std::cout << '(' << v.x << ',' << v.y << ',' << v.z << ')';
}

euler_data euler(euler_data data, double dt) {
    data.v = data.v + data.a * dt;
    data.p = data.p + data.v * dt;
    return data;
}

vec3 x_lerp(double x, vec3 v1, vec3 v2) {
    //This function provides linear interpolation. It is used when the upper and lower bounds of an integral don't match up perfectly with a point on the graph.
    double y = (v1.y * (v2.x - x) + v2.y * (x - v1.x)) / (v2.x - v1.x);
    struct vec3 temp = { x,y,0 };
    return temp;
}

graph::graph(void) {
    min_x = 0;
    max_x = 0;
}

void graph::build(vec3 vec) {
    //appends a point to the end of the graph
    points.push_back(vec);
}

void graph::build(double x, double y) {
    //alternative method for appending points to the end of a graph
    struct vec3 point = { x,y,0 };
    points.push_back(point);
}

void graph::print_points() {
    //prints the contents of a graph
    vector<vec3>::iterator i;
    int n = 0;
    for (i = points.begin(); i < points.end(); ++i) {
        cout << n << ':';
        print(*i);
        cout << "\n";
        n++;
    }
}

double graph::integral(double x1, double x2) {
    //gets the quadrature of the graph between the input bounds, x1 being the lower and x2 being the higher
    int i = 0;
    int j = points.size() - 1;
    //get the bounds
    while (points[i + 1].x <= x1 && j > i) {
        i++;
    }

    while (points[j - 1].x >= x2 && i < j) {
        j--;
    }

    cout << "i= " << i << " j= " << j << "\n";

    struct vec3 v1 = x_lerp(x1, points[i], points[i + 1]);
    struct vec3 v2 = x_lerp(x2, points[j - 1], points[j]);

    //if the bounds are on the same line segment just get the area between 2 lerps
    if (j - i == 1) {
        return ((v1.y + v2.y) * (v2.x - v1.x)) / 2;
    }
    else {
        double area_sum = 0;
        i++;
        j--;
        //area between lerp of lower bound and nearest point
        area_sum += ((v1.y + points[i].y) * (points[i].x - v1.x)) / 2;
        //area between lerp of upper bound and nearest point
        area_sum += ((v2.y + points[j].y) * (v2.x - points[j].x)) / 2;
        //sum of internal line segments
        while (i < j) {

            if (j - i > 1) {
                //j and i are on different line segments
                area_sum += ((points[i].y + points[i + 1].y) * (points[i + 1].x - points[i].x)) / 2;
                area_sum += ((points[j].y + points[j - 1].y) * (points[j].x - points[j - 1].x)) / 2;
            }
            else {
                //j and i are on the same line segment
                area_sum += ((points[i].y + points[j].y) * (points[j].x - points[i].x)) / 2;
            }
            j--;
            i++;
        }

        return area_sum;
    }
}

double graph::tangent(double x) {
    //gets the tangent(derivative) of the graph at the given x value

    //find the line containing the point
    int i = 0;
    int j = points.size() - 1;

    if (i == j) {
        return 0;
    }

    while (i < j - 1) {
        if (points[j - 1].x > x&& j - 1 > i) {
            j--;
        }
        if (points[i + 1].x <= x && i < j) {
            i++;
        }
    }

    return (points[j].y - points[i].y) / (points[j].x - points[i].x);
}