#pragma once
void fill_list_with_points(HWND hList, std::list<KPoint> points);
void fill_list_with_rectangles(HWND hList, std::list<KShape> rectangles);
void fill_list_with_squares(HWND hList, std::list<KSquare> squares);
void fill_list_with_circles(HWND hList, std::list<KCircle> circles);
void fill_list_with_triangles(HWND hList, std::list<KTriangle> triangles);
void fill_list_with_parallelograms(HWND hList, std::list<Parallelogram> parallelograms);
void fill_list_with_diagparallelograms(HWND hList, std::list<Extraparallelogram> diagonal_parallelograms);
void fill_list_with_chord_circles(HWND hList, std::list<ExtraCircle> circles);
const std::tuple<int, int, int> findmaxandconstructcortage(int const a, int const b, int const  c);
std::pair<int, int> find_rotation_center(int x1, int x2, int x3, int y1, int y2, int y3);
void ensure_point_in_field_for_parallelogram(int x, int y, int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, int angle);
void ensure_points_in_field_for_triangle(int x1, int x2, int x3, int y1, int y2, int y3, int angle, std::pair<int, int> rotation_center);
void ensure_points_in_field_for_shape(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, int angle, std::pair<int, int> rotation_center);
std::tuple<int, int, int, int, int, int> find_vertices_for_triangle(int x_center, int y_center, int bottom, int left, int right);
std::tuple<int, int, int, int, int, int, int, int> find_vertices_for_parallelogram(int x_center, int y_center, int bottom, int left, int angle_btw_sides);
void fill_points_array_with_points(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, POINT* array);
