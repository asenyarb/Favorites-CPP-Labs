#include "stdafx.h"
#include "Figures.h"
#include "Auxiliary_functions.h"


//KLOC
KLoc::KLoc() : x(0), y(0), color(0), chosencolor(0) {}
KLoc::KLoc(int x, int y, COLORREF color) : x(x), y(y), color(color), chosencolor(color) {}
void KLoc::setcolor(COLORREF _color)
{
	color = _color;
	chosencolor = _color;
}
int KLoc::get_x_coord() {
	return x;
}
int KLoc::get_y_coord() {
	return y;
}
//


//KPOINT
KPoint::KPoint() : KLoc() {}
KPoint::KPoint(int x, int y, COLORREF color) : KLoc(x, y, color) {}
void KPoint::Hide()
{
	color = hide;
}
void KPoint::Show()
{
	color = chosencolor;
}
void KPoint::Draw(HDC hdc) 
{
	if (color == hide)	return;
	SetPixel(hdc, x, y, color);
}
void KPoint::Move(int _x, int _y) 
{
	if (x >= 0 && y >= 0) {
		x = _x; y = _y;
	}
}
void KPoint::ShiftX(int _x) 
{
	if (x + _x >= 0)
		x += _x;
}
void KPoint::ShiftY(int _y)
{
	if (y+_y>=0)
	y += _y;
}
void KPoint::Delete()
{
	color = -1;
}
/////////////////////////



//KSHAPE
KShape::KShape():angle(0), cx(0),cy(0), KPoint(){}
KShape::KShape(int _x, int _y, int _cx, int _cy, COLORREF color): angle(0), KPoint(_x, _y, color)
{
	if (_x < _cx / 2) {
		cx = _x / 2;
		MessageBeep(0x00000010L);
	}
	else
		cx = _cx;
	if (_y < _cy / 2) {
		cy = _y * 2;
		MessageBeep(0x00000010L);
	}
	else
		cy = _cy;
}
KShape::KShape(int _x, int _y, int _cx, int _cy, int angle, COLORREF color) : angle(-angle), KPoint(_x, _y, color) 
{
	//проверка на выход за пределы пол€
	double angle_in_radian = angle * 3.14159265359 / 180;
	std::list<std::pair<int, int>> vertices;
	vertices.push_back({ _x - _cx / 2, _y + _cy / 2 });
	vertices.push_back({ _x - _cx / 2, _y - _cy / 2 });
	vertices.push_back({ _x + _cx / 2, _y + _cy / 2 });
	vertices.push_back({ _x + _cx / 2, _y - _cy / 2 });
	std::for_each(vertices.begin(), vertices.end(), [&angle_in_radian, &_x, &_y](std::pair<int,int> const &point) {
		int new_x = int(double(_x) + double(point.first - _x) * cos(angle_in_radian) - double(point.second - _y) * sin(angle_in_radian));
		int new_y = int(double(_y) + double(point.first - _x) * sin(angle_in_radian) + double(point.second - _y) * cos(angle_in_radian));
		if (new_x < 0 || new_y < 0) throw std::exception("“очка вне пол€");
	});
	cx = _cx;
	cy = _cy;
}


void KShape::Hide() 
{
	color = hide;
}
void KShape::Show()
{
	color = chosencolor;
}
void KShape::Draw(HDC hdc) 
{
	if (color == hide) return;
	double factor = (2.0 * 3.1416) / 360.0;
	double rot = angle * factor;//угол в радианах
	SetViewportOrgEx(hdc, x, y, NULL);//выбор центра вращени€
	// “рансформирующа€ матрица
	XFORM xfm = { 0.0f };
	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);

	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xfm);//поворот фигуры

	HPEN hPen = CreatePen(0, 1, color);
	HPEN hOldPen = SelectPen(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
	Rectangle(hdc, 0 - cx / 2, 0 - cy / 2, 0 + cx / 2, 0 + cy / 2);
	
	SelectBrush(hdc, hOldBrush);
	DeleteObject(hBrush);
	SelectPen(hdc, hOldPen);
	DeleteObject(hPen);
}
void KShape::Move(int _x, int _y) 
{
	if (x >= cx / 2 && y >= cy / 2) {
		x = _x; y = _y;
	}
	else throw std::exception("Unable to apply entered coordinates");
}
void KShape::ShiftX(int _x)
{
	if (x + _x >= cx / 2)
	x += _x;
	else throw std::exception("Unable to apply entered coordinate");
}
void KShape::ShiftY(int _y) 
{
	if (y + _y >= cy / 2)
	y += _y;
	else throw std::exception("Unable to apply entered coordinate");
}
void KShape::Rotate(int _angle)
{
	//проверка на выход за границы пол€
	double angle_in_radian = _angle * 3.14159265359 / 180;
	std::list<std::pair<int, int>> vertices;
	vertices.push_back({ x - cx / 2, y + cy / 2 });
	vertices.push_back({ x - cx / 2, y - cy / 2 });
	vertices.push_back({ x + cx / 2, y + cy / 2 });
	vertices.push_back({ x + cx / 2, y - cy / 2 });
	int xcenter = x, ycenter = y;
	std::for_each(vertices.begin(), vertices.end(), [&angle_in_radian, &xcenter, &ycenter](std::pair<int, int> const &point) {
		int new_x = int(double(xcenter) + double(point.first - xcenter) * cos(angle_in_radian) - double(point.second - ycenter) * sin(angle_in_radian));
		int new_y = int(double(ycenter) + double(point.first - xcenter) * sin(angle_in_radian) + double(point.second - ycenter) * cos(angle_in_radian));
		if (new_x < 0 || new_y < 0) throw std::exception("“очка вне пол€");
	});
	angle = -_angle;
}
void KShape::Delete()//удаление произойдЄт в WM_PAINT
{
	color = -1; 
}
void KShape::Explode(double coefficient)
{
	int new_cx = int(double(cx) * coefficient), new_cy = int(double(cy) * coefficient);
	ensure_points_in_field_for_shape(x - new_cx / 2, x - new_cx / 2, x + new_cx / 2, x + new_cx / 2, y - new_cy / 2, y + new_cy / 2, y - new_cy / 2, y + new_cy / 2, angle, std::make_pair(x, y));
	cx = new_cx; cy = new_cy;
}

int KShape::Length() {
	return cx;
}
int KShape::Width() {
	return cy;
}
///////////////////////////////////


//KSquare
KSquare::KSquare():KShape(){};
KSquare::KSquare(int _x, int _y, int side, COLORREF color): KShape(_x, _y, side, side, color){};
KSquare::KSquare(int _x, int _y, int side, int angle, COLORREF color) : KShape(_x, _y, side, side, angle, color) {};
void KSquare::Hide() 
{
	color = hide;
}
void KSquare::Show()
{
	color = chosencolor;
}
void KSquare::Draw(HDC hdc) 
{
	if (color == hide) return;
	double factor = (2.0 * 3.1416) / 360.0;
	double rot = angle * factor;
	SetViewportOrgEx(hdc, x, y, NULL);
	// Create a matrix for the transform we want
	XFORM xfm = { 0.0f };
	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);

	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xfm);

	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
	HPEN hPen = CreatePen(0, 1, color);
	HPEN hOldPen = SelectPen(hdc, hPen);
	Rectangle(hdc, - cx / 2, - cy / 2, cx / 2, cy / 2);
	SelectBrush(hdc, hOldBrush);
	DeleteObject(hBrush);
	SelectPen(hdc, hOldPen);
	DeleteObject(hPen);
}
void KSquare::Move(int _x, int _y)
{
	if (x >= cx/2 && y >= cy/2)
	{
		x = _x; y = _y;
	}
	else throw std::exception("Unable to apply entered coordinates");
}
void KSquare::ShiftX(int _x)
{
	if (x + _x >= cx/2)
	x += _x;
	else throw std::exception("Unable to apply entered coordinate");
}
void KSquare::ShiftY(int _y)
{
	if (y + _y >= cy/2)
	y += _y;
	else throw std::exception("Unable to apply entered coordinate");
}
void KSquare::Rotate(int _angle) {
	double angle_in_radian = _angle * 3.14159265359 / 180;
	std::list<std::pair<int, int>> vertices;
	vertices.push_back({ x - cx / 2, y + cy / 2 });
	vertices.push_back({ x - cx / 2, y - cy / 2 });
	vertices.push_back({ x + cx / 2, y + cy / 2 });
	vertices.push_back({ x + cx / 2, y - cy / 2 });
	int xcenter = x, ycenter = y;
	std::for_each(vertices.begin(), vertices.end(), [&angle_in_radian, &xcenter, &ycenter](std::pair<int, int> const &point) {
		int new_x = int(double(xcenter) + double(point.first - xcenter) * cos(angle_in_radian) - double(point.second - ycenter) * sin(angle_in_radian));
		int new_y = int(double(ycenter) + double(point.first - xcenter) * sin(angle_in_radian) + double(point.second - ycenter) * cos(angle_in_radian));
		if (new_x < 0 || new_y < 0) throw std::exception("“очка вне пол€");
	});
	angle = -_angle;
}
void KSquare::Explode(double coefficient) {
	int new_cx = int(double(cx) * coefficient), new_cy = int(double(cy) * coefficient);
	ensure_points_in_field_for_shape(x - new_cx / 2, x - new_cx / 2, x + new_cx / 2, x + new_cx / 2, y - new_cy / 2, y + new_cy / 2, y - new_cy / 2, y + new_cy / 2, angle, std::make_pair(x, y));
	cx = new_cx; cy = new_cy;
}
void KSquare::Delete() {
	color = -1;
}
////////////////////////////////


//KCircle
KCircle::KCircle(): KShape() {};
KCircle::KCircle(int x, int y, int rad, COLORREF color, int angle): KShape(x, y, rad*2, rad*2, angle, color) {};
void KCircle::Hide() 
{
	color = hide;
}
void KCircle::Show() 
{
	color = chosencolor;
}
void KCircle::Draw(HDC hdc) {
	if (color == hide) return;
	double factor = (2.0 * 3.1416) / 360.0;
	double rot = angle * factor;
	SetViewportOrgEx(hdc, x, y, NULL);
	
	XFORM xfm = { 0.0f };
	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);

	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xfm);

	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
	HPEN hPen = CreatePen(0, 1, color);
	HPEN hOldPen = SelectPen(hdc, hPen);
	Ellipse(hdc, - cx, - cy, cx, cy);

	SelectBrush(hdc, hOldBrush);
	DeleteObject(hBrush);
	SelectPen(hdc, hOldPen);
	DeleteObject(hPen);
}
void KCircle::Move(int _x, int _y)
{
	if (x >= cx/2 && y >= cy/2)
	{
		x = _x; y = _y;
	}
	else throw std::exception("Unable to apply entered coordinates");
}
void KCircle::ShiftX(int _x)
{
	if (x + _x >= cx/2)
	{
		x += _x;
	}
	else throw std::exception("Unable to apply entered coordinate");
}
void KCircle::ShiftY(int _y)
{
	if (y + _y >= cy/2)
	{
		y += _y;
	}
	else throw std::exception("Unable to apply entered coordinate");
}
//sx=rad,sy=0
void KCircle::Delete() {
	color = -1;
}
void KCircle::Explode(double coeff) {
	int new_rad = int(double(cx) * coeff);
	if (x - new_rad/2 < 0 || y - new_rad/2 < 0)
		throw std::exception("“очка фигуры вне пол€");
	cx = new_rad; cy = new_rad;
}
int KCircle::Radius() {
	return cx;
}
void KCircle::setcolor(COLORREF _color)
{
	color = _color;
	chosencolor = _color;
}
int KCircle::get_x_coord() {
	return x;
}
int KCircle::get_y_coord() {
	return y;
}
///////////////////////////



//KTriang
KTriangle::KTriangle(): cz(0), x1(0), y1(0), x2(0), y2(0), x3(0), y3(0),  KShape() {};
KTriangle::KTriangle(int _x, int _y, int bottom, int left, int right, int angle, COLORREF color) : cz(right), KShape(_x, _y, bottom, left, angle, color){
	auto[a, b, c] = findmaxandconstructcortage(bottom, left, right);
	if (a * a > b * b + c * c) {
		throw std::exception(" вадрат одной стороны больше суммы квадратов двух других!!!");
	}

	//поиск вершин треугольника на основании его центра и длин сторон
	auto [x1_,x2_,x3_,y1_,y2_,y3_] = find_vertices_for_triangle(_x, _y, bottom, left, right);
	x1 = x1_; x2 = x2_; x3 = x3_; y1 = y1_; y2 = y2_; y3 = y3_;
	//поиск центра вращени€ дл€ треугольника
	rotation_center = find_rotation_center(x1, x2, x3, y1, y2, y3);
	//проверка на выход за пределы пол€
	ensure_points_in_field_for_triangle(x1, x2, x3, y1, y2, y3, angle, rotation_center);
};
void KTriangle::Hide(){
	color = hide;
}
void KTriangle::Show() {
	color = chosencolor;
};
void KTriangle::Draw(HDC hdc) {
	if (color == hide) return;
	double factor = (2.0 * 3.1416) / 360.0;
	double rot = angle * factor;
	SetViewportOrgEx(hdc, rotation_center.first, rotation_center.second, NULL);
	// Create a matrix for the transform we want
	XFORM xfm = { 0.0f };
	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xfm);
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
	HPEN hPen = CreatePen(0, 1, color);
	HPEN hOldPen = SelectPen(hdc, hPen);
	POINT vertices[] = { {x1 - rotation_center.first, y1 - rotation_center.second}, {x2 - rotation_center.first, y2 - rotation_center.second}, {x3 - rotation_center.first, y3 - rotation_center.second} };
	Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

	SelectBrush(hdc, hOldBrush);
	DeleteObject(hBrush);
	SelectPen(hdc, hOldPen);
	DeleteObject(hPen);
}
void KTriangle::Move(int _x, int _y)
{
	int difference_x, difference_y;
	difference_x = x - _x;
	difference_y = y - _y;
	std::pair<int, int> rotation_center_temp;
	rotation_center_temp.first = rotation_center.first + difference_x;
	rotation_center_temp.second = rotation_center.second + difference_y;
	ensure_points_in_field_for_triangle(x1 + difference_x, x2 + difference_x, x3 + difference_x, y1 + difference_y, y2 + difference_y, y3 + difference_y, angle, rotation_center_temp);
	x = _x; y = _y;
	x1 += difference_x;
	x2 += difference_x;
	x3 += difference_x;
	y1 += difference_y;
	y2 += difference_y;
	y2 += difference_y;
	rotation_center.first += difference_x;
	rotation_center.second += difference_y;
}
void KTriangle::ShiftX(int _x)
{
	std::pair<int, int> rotation_center_temp;
	rotation_center_temp.first = rotation_center.first + _x;
	rotation_center_temp.second = rotation_center.second;
	ensure_points_in_field_for_triangle(x1 + _x, x2 + _x, x3 + _x, y1, y2, y3, angle, rotation_center_temp);
	x += _x;
	x1 += _x;
	x2 += _x;
	x3 += _x;
	rotation_center.first += _x;
}
void KTriangle::ShiftY(int _y)
{	
	std::pair<int, int> rotation_center_temp;
	rotation_center_temp.first = rotation_center.first;
	rotation_center_temp.second = rotation_center.second + _y;
	ensure_points_in_field_for_triangle(x1, x2, x3, y1+_y, y2+_y, y3+_y, angle, rotation_center_temp);
	y += _y;
	y1 += _y;
	y2 += _y;
	y2 += _y;
	rotation_center.second += _y;
}
void KTriangle::Rotate(int _angle)
{
	ensure_points_in_field_for_triangle(x1, x2, x3, y1, y2, y3, -_angle, rotation_center);
	angle = -_angle;
}
void KTriangle::Explode(double coefficient) {
	int new_cx = int(double(cx) * coefficient), new_cy = int(double(cy) * coefficient), new_cz = int(double(cz) * coefficient);
	auto[x1_, x2_, x3_, y1_, y2_, y3_] = find_vertices_for_triangle(x, y, new_cx, new_cy, new_cz);
	ensure_points_in_field_for_triangle(x1_, x2_, x3_, y1_, y2_, y3_, angle, rotation_center);
	x1 = x1_; x2 = x2_; x3 = x3_; y1 = y1_; y2 = y2_; y3 = y3_;
};
void KTriangle::Delete() {
	color = -1;
}

int KTriangle::Bottom() {
	return cz;
}
////////////////////////////////////




//Parallelogram
Parallelogram::Parallelogram(): angle_btw_bottom_and_left(0), array_of_points(0), KShape(){};
Parallelogram::Parallelogram(int x, int y, int bottom, int left, int angle_btw_sides, int angle, COLORREF color): angle_btw_bottom_and_left(angle_btw_sides), KShape(x, y, bottom, left, angle, color)
{
	auto [_x1, _x2, _x3, _x4, _y1, _y2, _y3, _y4] = find_vertices_for_parallelogram(0, 0, bottom, left, angle_btw_sides);
	array_of_points = new POINT[4];
	ensure_point_in_field_for_parallelogram(x, y, _x1, _x2, _x3, _x4, _y1, _y2, _y3, _y4, angle);
	fill_points_array_with_points(_x1, _x2, _x3, _x4, _y1, _y2, _y3, _y4, array_of_points);
};
void Parallelogram::Hide() {
	color = hide;
}
void Parallelogram::Show() {
	color = chosencolor;
};
void Parallelogram::Draw(HDC hdc) {
	if (color == hide) return;
	double factor = (2.0 * 3.1416) / 360.0;
	double rot = angle * factor;
	SetViewportOrgEx(hdc, x, y, NULL);
	// Create a matrix for the transform we want
	XFORM xfm = { 0.0f };
	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xfm);
	HBRUSH hOldBrush = SelectBrush(hdc, NULL_BRUSH);
	HPEN hPen = CreatePen(0, 1, color);
	HPEN hOldPen = SelectPen(hdc, hPen);
	Polygon(hdc, array_of_points, 4);

	SelectBrush(hdc, hOldBrush);
	SelectPen(hdc, hOldPen);
	DeleteObject(hPen);
}
void Parallelogram::Move(int _x, int _y)
{
	auto [x1, x2, x3, x4, y1, y2, y3, y4] = find_vertices_for_parallelogram(0, 0, cx, cy, angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(_x, _y, x1, x2, x3, x4, y1, y2, y3, y4, angle);
	fill_points_array_with_points(x1, x2, x3, x4, y1, y2, y3, y4, array_of_points);
	x = _x; y = _y;
}
void Parallelogram::ShiftX(int _x)
{
	auto[x1, x2, x3, x4, y1, y2, y3, y4] = find_vertices_for_parallelogram(0, 0, cx, cy, angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(x+_x, y, x1, x2, x3, x4, y1, y2, y3, y4, angle);
	fill_points_array_with_points(x1, x2, x3, x4, y1, y2, y3, y4, array_of_points);
}
void Parallelogram::ShiftY(int _y)
{
	auto[x1, x2, x3, x4, y1, y2, y3, y4] = find_vertices_for_parallelogram(0, 0, cx, cy, angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(x, y+_y, x1, x2, x3, x4, y1, y2, y3, y4, angle); 
	fill_points_array_with_points(x1, x2, x3, x4, y1, y2, y3, y4, array_of_points);
}
void Parallelogram::Rotate(int _angle)
{

	angle = -_angle;
}
void Parallelogram::Explode(double coefficient) {
	int new_cx = int(double(cx) * coefficient), new_cy = int(double(cy) * coefficient);
	auto[x1_, x2_, x3_, x4_, y1_, y2_, y3_, y4_] = find_vertices_for_parallelogram(0,0,new_cx,new_cy,angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(x, y, x1_, x2_, x3_, x4_, y1_, y2_, y3_, y4_, angle);
	fill_points_array_with_points(x1_, x2_, x3_, x4_, y1_, y2_, y3_, y4_, array_of_points);
};
void Parallelogram::Delete() {
	color = -1;
}


Extraparallelogram::Extraparallelogram() : color2(0), chosencolor2(0), Parallelogram(){};
Extraparallelogram::Extraparallelogram(int x, int y, int bottom, int left,  int angle_btw_sides, int angle, COLORREF color1, COLORREF color2) : color2(color2), chosencolor2(color2), Parallelogram(x, y, bottom, left, angle_btw_sides, angle, color1) {}
void Extraparallelogram::Hide() {
	color = hide;
	color2 = hide;
}
void Extraparallelogram::Show() {
	color = chosencolor;
	color2 = chosencolor2;
};
void Extraparallelogram::Draw(HDC hdc) {
	if (color == hide) return;
	double factor = (2.0 * 3.1416) / 360.0;
	double rot = angle * factor;
	SetViewportOrgEx(hdc, x, y, NULL);
	// Create a matrix for the transform we want
	XFORM xfm = { 0.0f };
	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xfm);
	HBRUSH hBrush1 = CreateSolidBrush(color);
	HBRUSH hOldBrush = SelectBrush(hdc, hBrush1);
	HPEN hPen1 = CreatePen(0, 1, color);
	HPEN hOldPen = SelectPen(hdc, hPen1);
	POINT* arr1 = new POINT[3];
	for (int i = 0; i < 3; i++)
	{
		arr1[i].x = array_of_points[i].x;
		arr1[i].y = array_of_points[i].y;
	}
	Polygon(hdc, arr1, 3);
	HBRUSH hBrush2 = CreateSolidBrush(color2);
	SelectObject(hdc, hBrush2);	
	HPEN hPen2 = CreatePen(0, 1, color2);
	SelectObject(hdc, hPen2);
	for (int i = 0; i < 2; i++)
	{
		arr1[i].x = array_of_points[i+2].x;
		arr1[i].y = array_of_points[i+2].y;
	}
	arr1[2].x = array_of_points[0].x;
	arr1[2].y = array_of_points[0].y;
	Polygon(hdc, arr1, 3);
	SelectBrush(hdc, hOldBrush);
	DeleteObject(hBrush1); DeleteObject(hBrush2);
	SelectPen(hdc, hOldPen);
	DeleteObject(hPen1); DeleteObject(hPen2);
}
void Extraparallelogram::Move(int _x, int _y)
{
	auto[x1, x2, x3, x4, y1, y2, y3, y4] = find_vertices_for_parallelogram(0, 0, cx, cy, angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(_x, _y, x1, x2, x3, x4, y1, y2, y3, y4, angle);
	x = _x; y = _y;
	fill_points_array_with_points(x1, x2, x3, x4, y1, y2, y3, y4, array_of_points);
}
void Extraparallelogram::ShiftX(int _x)
{
	auto[x1, x2, x3, x4, y1, y2, y3, y4] = find_vertices_for_parallelogram(0, 0, cx, cy, angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(x+_x, y, x1, x2, x3, x4, y1, y2, y3, y4, angle);
	x += _x;
	fill_points_array_with_points(x1, x2, x3, x4, y1, y2, y3, y4, array_of_points);
}
void Extraparallelogram::ShiftY(int _y)
{
	auto[x1, x2, x3, x4, y1, y2, y3, y4] = find_vertices_for_parallelogram(0, 0, cx, cy, angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(x, y+_y, x1, x2, x3, x4, y1, y2, y3, y4, angle);
	y += _y;
	fill_points_array_with_points(x1, x2, x3, x4, y1, y2, y3, y4, array_of_points);
}
void Extraparallelogram::Rotate(int _angle)
{
	angle = -_angle;
}
void Extraparallelogram::Explode(double coefficient) {
	int new_cx = int(double(cx) * coefficient), new_cy = int(double(cy) * coefficient);
	auto[x1_, x2_, x3_, x4_, y1_, y2_, y3_, y4_] = find_vertices_for_parallelogram(0, 0, new_cx, new_cy, angle_btw_bottom_and_left);
	ensure_point_in_field_for_parallelogram(x, y, x1_, x2_, x3_, x4_, y1_, y2_, y3_, y4_, angle);
	fill_points_array_with_points(x1_, x2_, x3_, x4_, y1_, y2_, y3_, y4_, array_of_points);
};
void Extraparallelogram::Delete() {
	color = -1;
}
COLORREF Extraparallelogram::getcolor2()
{
	return chosencolor2;
}
void Extraparallelogram::setcolor2(COLORREF color)
{
	color2 = color;
	chosencolor2 = color;
}



//ExtraCircle
ExtraCircle::ExtraCircle() : arc_points(0), distance(0), y_line(0), x1(0), x2(0), KCircle() {};
ExtraCircle::ExtraCircle(int x, int y, int rad, int distance, int _angle, COLORREF color) : distance(distance), KCircle(x, y, rad, color, _angle) 
{
	y_line = distance - rad;
	int temp = rad * rad - y_line * y_line;
	double racine = sqrt(temp);
	x1 = int(racine);
	x2 = - int(racine);
};
void ExtraCircle::Hide()
{
	color = hide;
}
void ExtraCircle::Show()
{
	color = chosencolor;
}
void ExtraCircle::Draw(HDC hdc) {
	if (color == hide) return;
	double factor = (2.0 * 3.1416) / 360.0;
	double rot = angle * factor;
	SetViewportOrgEx(hdc, x, y, NULL);

	XFORM xfm = { 0.0f };
	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);

	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xfm);

	HBRUSH hOldBrush = SelectBrush(hdc, NULL_BRUSH);
	HPEN hOldPen = SelectPen(hdc, BLACK_PEN);
	Ellipse(hdc, -cx, -cy, cx, cy);
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);
	Chord(hdc, -cx, -cy, cx, cy, x1, y_line, x2, y_line);
	SelectBrush(hdc, hOldBrush);
	DeleteObject(hBrush);
	SelectPen(hdc, hOldPen);
}
void ExtraCircle::Move(int _x, int _y)
{
	if (x >= cx / 2 && y >= cy / 2)
	{
		x = _x; y = _y;
	}
	else throw std::exception("Unable to apply entered coordinates");
}
void ExtraCircle::ShiftX(int _x)
{
	if (x + _x >= cx / 2)
	{
		x += _x;
	}
	else throw std::exception("Unable to apply entered coordinate");
}
void ExtraCircle::ShiftY(int _y)
{
	if (y + _y >= cy / 2)
	{
		y += _y;
	}
	else throw std::exception("Unable to apply entered coordinate");
}
//sx=rad,sy=0
void ExtraCircle::Delete() {
	color = -1;
}
void ExtraCircle::Rotate(int _angle) {
	angle = - _angle;
}
void ExtraCircle::Explode(double coeff) {
	int new_rad = int(double(cx) * coeff);
	if (x - new_rad < 0 || y - new_rad < 0)
		throw std::exception("“очка фигуры вне пол€");
	cx = new_rad; cy = new_rad;
	distance = int(double(distance) * coeff);
	y_line = 2 * distance - new_rad;
	double racine = sqrt(new_rad * new_rad - y_line * y_line);
	x1 = int(racine);
	x2 = -int(racine);
}

int ExtraCircle::Radius() {
	return cx/2;
}
int ExtraCircle::Distance() {
	return distance;
}
void ExtraCircle::setcolor(COLORREF _color)
{
	color = _color;
	chosencolor = _color;
}
int ExtraCircle::get_x_coord() {
	return x;
}
int ExtraCircle::get_y_coord() {
	return y;
}
///////////////////////////
