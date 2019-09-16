#pragma once
#ifndef FIGURES_H__
#define FIGURES_H__
#define hide RGB(255,255,255)

class KLoc {
public:
	KLoc();
	KLoc(int x, int y, COLORREF color);
	virtual void Hide() {}
	virtual void Show() {}
	virtual void Draw(HDC hdc) {}
	virtual void Move(int _x, int _y) {}
	virtual void ShiftX(int _x) {}
	virtual void ShiftY(int _y) {}
	virtual void Rotate(int angle) {}
	virtual void Explode() {};
	virtual void Delete() { color = -1; }
	COLORREF getcolor() { return color; }
	void setcolor(COLORREF color);
	int get_x_coord();
	int get_y_coord();
	virtual ~KLoc() {}
protected:
	int x, y;
	COLORREF color;//Текущий цвет
	COLORREF chosencolor;//Выбранный пользователем(нужен для show)
};


class KPoint:public KLoc {
public:
	KPoint();
	KPoint(int x, int y, COLORREF color);
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Rotate(int angle) {}
	virtual void Delete();
	virtual ~KPoint() {}
};


class KShape :public KPoint {
public:
	KShape();
	KShape(int x, int y, int cx, int cy, COLORREF color);
	KShape(int x, int y, int cx, int cy, int angle, COLORREF color);
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Rotate(int angle);
	virtual void Delete();
	virtual void Explode(double coefficient);
	int Length();
	int Width();
	virtual ~KShape() {}
protected:	
	int angle, cx, cy;
};


class KSquare: public KShape {
public:
	KSquare();
	KSquare(int x, int y, int side, COLORREF color);
	KSquare(int _x, int _y, int side, int angle, COLORREF color);
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Rotate(int angle);
	virtual void Explode(double coeff);
	virtual void Delete();
	virtual ~KSquare() {}
};


class KCircle : public KShape {
public:
	KCircle();
	KCircle(int x, int y, int rad, COLORREF color, int angle = 0);
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);//sx=rad,sy=0
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Explode(double coeff);
	virtual void Delete();
	int Radius();
	COLORREF getcolor() { return color; }
	void setcolor(COLORREF color);
	int get_x_coord();
	int get_y_coord();
	virtual ~KCircle() {}
private:
	virtual void Rotate(HDC hdc, int angle) {}
};


class KTriangle :public KShape {
public:
	KTriangle();
	KTriangle(int x, int y, int bottom, int left, int right, int angle, COLORREF color);
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Rotate(int angle);
	virtual void Explode(double coeff);
	virtual void Delete();
	int Bottom();
	virtual ~KTriangle() {}
protected:
	int cz;
	int x1, y1, x2, y2, x3, y3;
	std::pair<int, int> rotation_center;
};

class Parallelogram : public KShape
{
protected:
	POINT* array_of_points;
	int angle_btw_bottom_and_left;
public:
	Parallelogram();
	Parallelogram(int x, int y, int bottom, int left, int angle, int angle_btw_bottom_and_left, COLORREF color = 0);
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Rotate(int angle);
	virtual void Explode(double coefficient);
	virtual void Delete();
};

class Extraparallelogram : public Parallelogram
{
protected:
	COLORREF color2;
	COLORREF chosencolor2;
public:
	Extraparallelogram();
	Extraparallelogram(int x, int y, int bottom, int left,  int angle_btw_bottom_and_left, int angle, COLORREF color1 = RGB(210,210,210), COLORREF color2 = RGB(130,130,130));
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Rotate(int angle);
	virtual void Explode(double coefficient);
	virtual void Delete();
	void setcolor2(COLORREF color2);
	COLORREF getcolor2();
};

class ExtraCircle : public KCircle {
protected:
	int distance;
	int y_line;
	int x1, x2;
	POINT* arc_points;
public:
	ExtraCircle();
	ExtraCircle(int x, int y, int rad, int distance, int angle, COLORREF color = RGB(130, 130, 130));
	virtual void Hide();
	virtual void Show();
	virtual void Draw(HDC hdc);//sx=rad,sy=0
	virtual void Move(int _x, int _y);
	virtual void ShiftX(int _x);
	virtual void ShiftY(int _y);
	virtual void Rotate(int _angle);
	virtual void Explode(double coeff);
	virtual void Delete();
	int Radius();
	COLORREF getcolor() { return color; }
	void setcolor(COLORREF color);
	int get_x_coord();
	int get_y_coord();
	int Distance();
	virtual ~ExtraCircle() {}
private:
	virtual void Rotate(HDC hdc, int angle) {}
};

#endif