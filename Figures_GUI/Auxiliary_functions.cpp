#pragma once
#include "stdafx.h"
#include "Auxiliary_functions.h"


void fill_list_with_points(HWND hList, std::list<KPoint> points) {
	int number = 1;
	for (auto it = points.begin(); it != points.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}

void fill_list_with_rectangles(HWND hList, std::list<KShape> rectangles) {
	int number = 1;
	for (auto it = rectangles.begin(); it != rectangles.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		s.append("      Длина: ").append(std::to_string(it->Length())).append(" Ширина: ").append(std::to_string(it->Width()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}

void fill_list_with_squares(HWND hList, std::list<KSquare> squares) {
	int number = 1;
	for (auto it = squares.begin(); it != squares.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		s.append("      Длина: ").append(std::to_string(it->Length())).append(" Ширина: ").append(std::to_string(it->Width()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}

void fill_list_with_circles(HWND hList, std::list<KCircle> circles) {
	int number = 1;
	for (auto it = circles.begin(); it != circles.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		s.append("      Радиус: ").append(std::to_string(it->Radius()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}

void fill_list_with_triangles(HWND hList, std::list<KTriangle> triangles) {
	int number = 1;
	for (auto it = triangles.begin(); it != triangles.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		s.append("          Длины:      нижняя: ").append(std::to_string(it->Length())).append(" левая: ").append(std::to_string(it->Width()));
		s.append(" правая: ").append(std::to_string(it->Bottom()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}

void fill_list_with_parallelograms(HWND hList, std::list<Parallelogram> parallelograms) {
	int number = 1;
	for (auto it = parallelograms.begin(); it != parallelograms.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}
void fill_list_with_diagparallelograms(HWND hList, std::list<Extraparallelogram> parallelograms) {
	int number = 1;
	for (auto it = parallelograms.begin(); it != parallelograms.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}

void fill_list_with_chord_circles(HWND hList, std::list<ExtraCircle> chord_circles) {
	int number = 1;
	for (auto it = chord_circles.begin(); it != chord_circles.end(); ++it, ++number) {
		std::string s(std::to_string(number));
		s.append(".            X:").append(std::to_string(it->get_x_coord()));
		s.append(" Y:").append(std::to_string(it->get_y_coord()));
		s.append("      Радиус: ").append(std::to_string(it->Radius()));
		s.append("        Расстояние: ").append(std::to_string(it->Distance()));
		char* str = new char[s.size()];
		strcpy(str, s.c_str());
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
	}
}


//first element in returned tuple is the biggest one
const std::tuple<int, int, int> findmaxandconstructcortage(int const a, int const b, int const  c) {
	if (a > b)
		if (a > c) return std::make_tuple(a, b, c);
		else return std::make_tuple(c, a, b);
	else
		if (b > c)return std::make_tuple(b, a, c);
		else return std::make_tuple(c, a, b);
}

std::pair<int, int> find_rotation_center(int x1, int x2, int x3, int y1, int y2, int y3) {
	long int y0_nomin = (x2 + x3) * (x3 - x2) * (x2 - x1) - (x2 - x1) * (y2 - y3) * (y2 + y3) - (x1 + x2) * (x2 - x1) * (x3 - x2) + (x3 - x2) * (y1 - y2) * (y1 + y2);
	long int y0_denomin = 2 * (x3 - x2) * (y1 - y2) + 2 * (x1 - x2) * (y2 - y3);
	double y0d = y0_nomin / y0_denomin;
	int y0 = int(y0d);
	long int x0_nomin = (y1 - y2) * (2 * y0 - y1 - y2) + (x1 + x2) * (x2 - x1);
	long int x0_denomin = 2 * (x2 - x1);
	double x0d = x0_nomin / x0_denomin;
	int x0 = int(x0d);
	return std::make_pair(x0, y0);
}

void ensure_point_in_field_for_parallelogram(int  x, int  y, int  x1, int  x2, int  x3, int  x4, int  y1, int  y2, int  y3, int  y4, int angle)
{
	double angle_in_radian = angle * 3.14159265359 / 180;
	std::list<std::pair<int, int>> vertices;
	vertices.push_back({ x1 + x, y1 + y });
	vertices.push_back({ x2 + x, y2 + y });
	vertices.push_back({ x3 + x, y3 + y });
	vertices.push_back({ x4 + x, y4 + y });
	int xcenter = x; int ycenter = y;
	std::for_each(vertices.begin(), vertices.end(), [angle_in_radian, xcenter, ycenter](std::pair<int, int> const point) {
		int new_x = int(double(xcenter) + double(point.first - xcenter) * cos(angle_in_radian) - double(point.second - ycenter) * sin(angle_in_radian));
		int new_y = int(double(ycenter) + double(point.first - xcenter) * sin(angle_in_radian) + double(point.second - ycenter) * cos(angle_in_radian));
		if (new_x < 0 || new_y < 0) throw std::exception("Точка вне поля");
	});
}

void ensure_points_in_field_for_triangle(int x1, int x2, int x3, int y1, int y2, int y3, int angle, std::pair<int, int> rotation_center) {
	double angle_in_radian = angle * 3.14159265359 / 180;
	std::list<std::pair<int, int>> vertices;
	vertices.push_back({ x1, y1 });
	vertices.push_back({ x2, y2 });
	vertices.push_back({ x3, y3 });
	int xcenter = rotation_center.first, ycenter = rotation_center.second;
	std::for_each(vertices.begin(), vertices.end(), [angle_in_radian, xcenter, ycenter](std::pair<int, int> const point) {
		int new_x = int(double(xcenter) + double(point.first - xcenter) * cos(angle_in_radian) - double(point.second - ycenter) * sin(angle_in_radian));
		int new_y = int(double(ycenter) + double(point.first - xcenter) * sin(angle_in_radian) + double(point.second - ycenter) * cos(angle_in_radian));
		if (new_x < 0 || new_y < 0) throw std::exception("Точка вне поля");
	});
}

std::tuple<int, int, int, int, int, int> find_vertices_for_triangle(int x, int y, int cx, int cy, int cz) {
	long double temp = long double(cx + cy + cz) / 10 * long double(cy + cz - cx) / 10 * long double(cx + cz - cy) / 10 * long double(cx + cy - cz) / 10;
	long double heron = sqrt(temp) / 2;   //(a + b + c)*(b + c - a)*(a + c - b)*(a + b - c)
	long double singamma = heron / long double(cx * cy) * 100;    //   /ab следует из равности площади(через формулу герона и две стороны + угол между ними)
	long double gamma = asin(singamma);
	long double x1d = long double(x) - long double(cx) + cos(gamma)*cy / 3;// cy = left
	long double y1d = long double(y) - sin(gamma) * long double(cy) / 3;// cy = left
	long double y2d = y1d;
	long double x2d = x1d + long double(cx);
	long double y3d = y1d - singamma * long double(cy);
	long double x3d = x1d + cos(gamma) * long double(cy);
	int x1 = int(x1d), y1 = int(y1d), x2 = int(x2d), y2 = int(y2d),	x3 = int(x3d), y3 = int(y3d);
	return std::make_tuple(x1, x2, x3, y1, y2, y3);
}

std::tuple<int, int, int, int, int, int, int, int> find_vertices_for_parallelogram(int x, int y, int bottom, int left, int angle_btw_sides) {
	double angle = double(angle_btw_sides) * 3.14159265359 / 180;
	int x1 = x - (bottom - int(double(left) * cos(angle) / 2));
	int x2 = x + (bottom + int(double(left) * cos(angle) / 2));
	int x3 = x + (bottom - int(double(left) * cos(angle) / 2));
	int x4 = x - (bottom + int(double(left) * cos(angle) / 2));
	int y1 = y - int(double(left) * sin(angle) / 2);
	int y2 = y - int(double(left) * sin(angle) / 2);
	int y3 = y + int(double(left) * sin(angle) / 2);
	int y4 = y + int(double(left) * sin(angle) / 2);
	return std::make_tuple(x1, x2, x3, x4, y1, y2, y3, y4);
}


void ensure_points_in_field_for_shape(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, int angle, std::pair<int, int> rotation_center)
{
	double angle_in_radian = angle * 3.14159265359 / 180;
	std::list<std::pair<int, int>> vertices;
	vertices.push_back({ x1, y1 });
	vertices.push_back({ x2, y2 });
	vertices.push_back({ x3, y3 });
	vertices.push_back({ x4, y4 });
	int xcenter = rotation_center.first, ycenter = rotation_center.second;
	std::for_each(vertices.begin(), vertices.end(), [angle_in_radian, xcenter, ycenter](std::pair<int, int> const point) {
		int new_x = int(double(xcenter) + double(point.first - xcenter) * cos(angle_in_radian) - double(point.second - ycenter) * sin(angle_in_radian));
		int new_y = int(double(ycenter) + double(point.first - xcenter) * sin(angle_in_radian) + double(point.second - ycenter) * cos(angle_in_radian));
		if (new_x < 0 || new_y < 0) throw std::exception("Точка вне поля");
	});
}

void fill_points_array_with_points(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, POINT* array)
{
	array[0].x = x1; array[0].y = y1;
	array[1].x = x2; array[1].y = y2;
	array[2].x = x3; array[2].y = y3;
	array[3].x = x4; array[3].y = y4;
}


