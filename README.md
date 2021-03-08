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
