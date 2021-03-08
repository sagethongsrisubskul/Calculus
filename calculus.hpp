#pragma once
#include <vector>
using namespace std;

struct vec3 {
    double x;
    double y;
    double z;
};

vec3 operator+(vec3 v1, vec3 v2);

vec3 operator-(vec3 v1, vec3 v2);

vec3 operator*(vec3 v, double m);

vec3 operator*(double m, vec3 v);

void print(vec3 v);

struct euler_data {
    struct vec3 p;
    struct vec3 v;
    struct vec3 a;
};

euler_data euler(euler_data data, double dt);

vec3 x_lerp(double x, vec3 v1, vec3 v2);

class graph {
public:
    vector<vec3> points;
    double min_x = 0;
    double max_x = 0;

    graph();
    void print_points();
    void build(vec3);
    void build(double, double);
    double integral(double, double);
    double tangent(double);
private:
};