#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <algorithm>

class Point;
class Segment;
class Line;
class Ray;
class Polygon;

class Vector {
	double x;
	double y;
public:
	Vector();
	Vector(const Point& A, const Point& B);
	Vector(double, double);
	double Module() const;
	double ScalarProduct(const Vector&) const;
	double PseudoScalarProduct(const Vector&) const;
	double TriangleArea(const Vector&) const;
	double OrientTriangleArea(const Vector&) const;
	bool IsCollinear(const Vector&) const;
	Vector operator+(const Vector);
	Vector &operator=(const Vector&);
	Vector operator*(double) const;
	friend std::ostream& operator<<(std::ostream &os, Vector obj) {
		os << obj.x << " " << obj.y;
		return os;
	}
	friend std::istream& operator>>(std::istream &is, Vector &obj) {
		is >> obj.x >> obj.y;
		return is;
	}
	friend Point;
	friend Line;
	friend Ray;
	friend Segment;
	friend Polygon;
};

class Shape {
public:
	virtual Shape &Shift(const Vector&) = 0;
	virtual bool PointInFigure(const Point&) const = 0;
	virtual bool IsIntersect(const Segment&) const = 0;
};

class Point : public Shape {
	double x;
	double y;
public:
	Point();
	Point(double, double);
	Point &Shift(const Vector&) override;
	bool PointInFigure(const Point&) const override;
	bool IsIntersect(const Segment&) const override;
	double Distance(const Point&) const;
	friend std::ostream& operator<<(std::ostream &os, Point obj) {
		os << obj.x << " " << obj.y;
		return os;
	}
	friend std::istream& operator>>(std::istream &is, Point &obj) {
		is >> obj.x >> obj.y;
		return is;
	}
	Point &operator=(const Point&);
	friend Vector;
	friend Segment;
	friend Line;
	friend Ray;
	friend Polygon;
};

class Segment : public Shape {
	Point start;
	Point end;
public:
	Segment(const Point& A, const Point& B);
	bool PointInFigure(const Point&) const override;
	bool IsIntersect(const Segment&) const override;
	Segment &Shift(const Vector&) override;
	double Distance(const Point&) const;
	double Distance(const Segment&) const;
	friend Point;
	friend Line;
	friend Ray;
};

class Line : public Shape {
	double a;
	double b;
	double c;
public:
	Line();
	Line(const Point&, const Point&);
	Line(double, double, double);
	Vector Direction() const;
	bool IsParallel(const Line&) const;
	bool IsIntersect(const Segment&) const override;
	Point IntersectPoint(const Line&) const;
	double Distance(const Line&) const;
	Line &Shift(const Vector&) override;
	bool PointInFigure(const Point&) const override;
	double Distance(const Point&) const;
	Point GetPoint() const;
};

class Ray : public Shape {
	Point start;
	Vector direct;
public:
	Ray(const Point&, const Point&);
	bool PointInFigure(const Point&) const override;
	bool IsIntersect(const Segment&) const override;
	Ray &Shift(const Vector&) override;
	double Distance(const Point&) const;
	friend Polygon;
};

class Polygon : public Shape {
	Point* points;
	int points_num;
public:
	Polygon(int);
	Polygon(const Polygon&);
	~Polygon();
	bool IsConvex() const;
	bool PointInFigure(const Point&) const override;
	bool IsIntersect(const Segment&) const override;
	Polygon &Shift(const Vector&) override;
	double PolygonArea() const;
	friend std::ostream &operator<<(std::ostream& os, Polygon obj) {
		for (int i = 0; i < obj.points_num; ++i) {
			os << obj.points[i] << "\n";
		}
		return os;
	}
	friend std::istream &operator>>(std::istream& is, Polygon& obj) {
		for (int i = 0; i < obj.points_num; ++i) {
			is >> obj.points[i];
		}
		return is;
	}
	Polygon ConvexHull() const;
};

double EPS = 1E-9;

double min(double a, double b, double c) {
	if ((a < b ? a : b) < c) {
		return a < b ? a : b;
	}
	else {
		return c;
	}
}

double min(double a, double b) {
	return a < b ? a : b;
}

double max(double a, double b) {
	return a > b ? a : b;
}

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(double a, double b) {
	x = a;
	y = b;
}

Point &Point::Shift(const Vector& obj) {
	x += obj.x;
	y += obj.y;
	return *this;
}

bool Point::PointInFigure(const Point& obj) const {
	if (x == obj.x && y == obj.y) {
		return true;
	}
	return false;
}

bool Point::IsIntersect(const Segment& obj) const {
	Line line(obj.start, obj.end);
	if (line.PointInFigure(*this)) {
		if ((x <= obj.start.x && x >= obj.end.x) || (x >= obj.start.x && x <= obj.end.x)) {
			if ((y <= obj.start.y && y >= obj.end.y) || (y >= obj.start.y && y <= obj.end.y)) {
				return true;
			}
		}
	}
	return false;
}

Point &Point::operator=(const Point& other) {
	x = other.x;
	y = other.y;
	return *this;
}

Vector::Vector() {
	x = 0;
	y = 0;
}

Vector::Vector(const Point& A, const Point& B) {
	x = B.x - A.x;
	y = B.y - A.y;
}

Vector::Vector(double q, double v) {
	x = q;
	y = v;
}

double Vector::Module() const {
	return sqrt(x * x + y * y);
}

Vector Vector::operator+(const Vector summand) {
	Vector result(summand.x + x, summand.y + y);
	return result;
}
Vector &Vector::operator=(const Vector& other) {
	x = other.x;
	y = other.y;
	return *this;
}

Vector Vector::operator*(double a) const {
	Vector result(a * x, a * y);
	return result;
}

double Vector::ScalarProduct(const Vector& other) const {
	return x * other.x + y * other.y;
}

double Vector::PseudoScalarProduct(const Vector& other) const {
	return x * other.y - y * other.x;
}

double Vector::TriangleArea(const Vector& other) const {
	return fabs(PseudoScalarProduct(other) / 2);
}

bool Vector::IsCollinear(const Vector& other) const {
	if (fabs(x * other.y - y * other.x) < EPS) {
		return true;
	}
	return false;
}

Line::Line() {
	a = 0;
	b = 0;
	c = 0;
}

Line::Line(double a_, double b_, double c_) {
	a = a_;
	b = b_;
	c = c_;
}

Vector Line::Direction() const {
	Vector direct(-b, a);
	return direct;
}

Point Line::GetPoint() const {
	if (fabs(a) < EPS) {
		Point point(1, -c / b);
		return point;
	} else {
		if (fabs(b) < EPS) {
			Point point(-c / a, 1);
			return point;
		} else {
			Point point(1, (-c - a) / b);
			return point;
		}
	}
}

bool Line::IsParallel(const Line& other) const {
	if (Direction().IsCollinear(other.Direction())) {
		return true;
	}
	return false;
}

double Line::Distance(const Line& other) const {
	if (IsParallel(other)) {
		if (fabs(other.a) > EPS) {
			if (other.c * a / other.a > c) {
				return (other.c * a / other.a - c) / sqrt(a * a + b * b);
			}
			else {
				return (c - other.c * a / other.a) / sqrt(a * a + b * b);
			}
		}
		else {
			if (other.c * b / other.b > c) {
				return (other.c * b / other.b - c) / sqrt(a * a + b * b);
			}
			else {
				return (c - other.c * b / other.b) / sqrt(a * a + b * b);
			}
		}
	}
	return 0;
}

Line &Line::Shift(const Vector& obj) {
	c -= a * obj.x + b * obj.y;
	return *this;
}

bool Line::IsIntersect(const Segment& obj) const {
	Line temp(obj.start, obj.end);
	if (IsParallel(temp)) {
		return false;
	}
	else {
		if (obj.PointInFigure(IntersectPoint(temp))) {
			return true;
		}
	}
	return false;
}

Point Line::IntersectPoint(const Line& other) const {
	if (!IsParallel(other)) {
		Point result;
		if (fabs(a) < EPS) {
			result.y = -c / b;
			result.x = (c*other.b / b - other.c) / other.a;
		}
		else {
			result.y = (other.a * c - a * other.c) / (other.b * a - b * other.a);
			result.x = -(b * result.y + c) / a;
		}
		return result;
	}
}

Segment::Segment(const Point& A, const Point& B) {
	start = A;
	end = B;
}

Line::Line(const Point& A, const Point& B) {
	a = A.y - B.y;
	b = B.x - A.x;
	c = A.x * B.y - B.x * A.y;
}

Ray::Ray(const Point& A, const Point& B) {
	start = A;
	direct = Vector(A, B);
}

bool Segment::PointInFigure(const Point& obj) const {
	if (obj.IsIntersect(*this)) {
		return true;
	}
	return false;
}

bool Line::PointInFigure(const Point& obj) const {
	if (fabs(a * obj.x + b * obj.y + c) < EPS) {
		return true;
	}
	return false;
}

bool Ray::PointInFigure(const Point& obj) const {
	Vector toPoint(start, obj);
	if (fabs(direct.PseudoScalarProduct(toPoint)) < EPS && direct.ScalarProduct(toPoint) >= 0) {
		return true;
	}
	return false;
}

double Point::Distance(const Point& obj) const {
	return sqrt((x - obj.x)*(x - obj.x) + (y - obj.y)*(y - obj.y));
}

double Line::Distance(const Point& obj) const {
	Point point = GetPoint();
	Vector AC(point, obj);
	double area = fabs(AC.PseudoScalarProduct(Direction()));
	double h = area / Direction().Module();
	return h;
}

double Segment::Distance(const Point& obj) const {
	Vector direct(start, end);
	Vector AC(start, obj);
	Vector BC(end, obj);
	if (direct.ScalarProduct(AC) >= 0 && direct.ScalarProduct(BC) <= 0) {
		Line temp(start, end);
		return temp.Distance(obj);
	}
	return min(start.Distance(obj), end.Distance(obj));
}

double Ray::Distance(const Point& obj) const {
	Vector temp(start, obj);
	if (direct.ScalarProduct(temp) <= 0) {
		return start.Distance(obj);
	}
	else {
		Point point(start.x + direct.x, start.y + direct.y);
		Line temp(start, point);
		return temp.Distance(obj);
	}
}

bool Segment::IsIntersect(const Segment& other) const {
	Vector AC(start, other.start);
	Vector AD(start, other.end);
	Vector CA(other.start, start);
	Vector CB(other.start, end);
	Vector AB(start, end);
	Vector CD(other.start, other.end);
	if (AB.PseudoScalarProduct(AC) * AB.PseudoScalarProduct(AD) <= 0) {
		if (CD.PseudoScalarProduct(CA) * CD.PseudoScalarProduct(CB) <= 0) {
			double x1 = min(start.x, end.x);
			double x2 = max(start.x, end.x);
			double x3 = min(other.start.x, other.end.x);
			double x4 = max(other.start.x, other.end.x);
			if (x1 <= x4 && x3 <= x2) {
				double y1 = min(start.y, end.y);
				double y2 = max(start.y, end.y);
				double y3 = min(other.start.y, other.end.y);
				double y4 = max(other.start.y, other.end.y);
				if (y1 <= y4 && y3 <= y2) {
					return true;
				}
			}
		}
	}
	return false;
}

Segment &Segment::Shift(const Vector& obj) {
	start.x += obj.x;
	start.y += obj.y;
	end.x += obj.x;
	end.y += obj.y;
	return *this;
}

double Segment::Distance(const Segment& other) const {
	if (IsIntersect(other)) {
		return 0;
	}
	Vector direct1(start, end);
	Vector AC(start, other.start);
	Vector BC(end, other.start);
	Vector AD(start, other.end);
	Vector BD(end, other.end);
	Vector direct2(other.start, other.end);
	Vector CA(other.start, start);
	Vector DA(other.end, start);
	Vector CB(other.start, end);
	Vector DB(other.end, end);
	double min_ = min(start.Distance(other.start), end.Distance(other.start));
	min_ = min(min_, start.Distance(other.end), end.Distance(other.end));
	if (direct1.ScalarProduct(AC) >= 0 && direct1.ScalarProduct(BC) <= 0) {
		min_ = min(min_, Distance(other.start));
	}
	if (direct1.ScalarProduct(AD) >= 0 && direct1.ScalarProduct(BD) <= 0) {
		min_ = min(min_, Distance(other.end));
	}
	if (direct2.ScalarProduct(CA) >= 0 && direct2.ScalarProduct(DA) <= 0) {
		min_ = min(min_, other.Distance(start));
	}
	if (direct2.ScalarProduct(CB) >= 0 && direct2.ScalarProduct(DB) <= 0) {
		min_ = min(min_, other.Distance(end));
	}
	return min_;
}

Ray &Ray::Shift(const Vector& obj) {
	start.x += obj.x;
	start.y += obj.y;
	return *this;
}

bool Ray::IsIntersect(const Segment& obj) const {
	Point point(start.x + direct.x, start.y + direct.y);
	Line first(start, point);
	Line second(obj.start, obj.end);
	if (!first.IsParallel(second)) {
		if (PointInFigure(first.IntersectPoint(second)) && obj.PointInFigure(first.IntersectPoint(second))) {
			return true;
		}
	}
	else {
		if (PointInFigure(obj.start) || PointInFigure(obj.end)) {
			return true;
		}
	}
	return false;
}

Polygon::Polygon(int num) {
	points_num = num;
	points = new Point[num];
	for (int i = 0; i < num; ++i) {
		points[i] = Point(0, 0);
	}
}

bool Polygon::IsConvex() const {
	if (points_num == 3) {
		return true;
	}
	int k = 0;
	if (fabs(Vector(points[0], points[1]).PseudoScalarProduct(Vector(points[1], points[2]))) < EPS) {
		k++;
	}
	for (int i = 0; i < points_num - 2; ++i) {
		if (fabs(Vector(points[i], points[i + 1]).PseudoScalarProduct(Vector(points[i + 1], points[i + 2]))) < EPS) {
			k++;
		}
	}
	if (fabs(Vector(points[points_num - 2], points[points_num - 1]).PseudoScalarProduct(Vector(points[points_num - 1], points[0]))) < EPS) {
		k++;
	}
	if (fabs(Vector(points[points_num - 1], points[0]).PseudoScalarProduct(Vector(points[0], points[1]))) < EPS) {
		k++;
	}
	if (k == points_num) {
		return false;
	}
	int one = 0;
	int two = 0;
	if (Vector(points[0], points[1]).PseudoScalarProduct(Vector(points[1], points[2])) >= 0) {
		one++;
		for (int i = 1; i < points_num - 2; ++i) {
			if (Vector(points[i], points[i + 1]).PseudoScalarProduct(Vector(points[i + 1], points[i + 2])) >= 0) {
				one++;
			}
		}
		if (Vector(points[points_num - 2], points[points_num - 1]).PseudoScalarProduct(Vector(points[points_num - 1], points[0])) >= 0) {
			one++;
		}
		if (Vector(points[points_num - 1], points[0]).PseudoScalarProduct(Vector(points[0], points[1])) >= 0) {
			one++;
		}
	}
	if (Vector(points[0], points[1]).PseudoScalarProduct(Vector(points[1], points[2])) <= 0) {
		two++;
		for (int i = 1; i < points_num - 2; ++i) {
			if (Vector(points[i], points[i + 1]).PseudoScalarProduct(Vector(points[i + 1], points[i + 2])) <= 0) {
				two++;
			}
		}
		if (Vector(points[points_num - 2], points[points_num - 1]).PseudoScalarProduct(Vector(points[points_num - 1], points[0])) <= 0) {
			two++;
		}
		if (Vector(points[points_num - 1], points[0]).PseudoScalarProduct(Vector(points[0], points[1])) <= 0) {
			two++;
		}
	}
	if (one == points_num || two == points_num) {
		return true;
	}
	return false;
}

Polygon::Polygon(const Polygon& Copy) {
	points_num = Copy.points_num;
	points = new Point[points_num];
	for (int i = 0; i < points_num; ++i) {
		points[i] = Copy.points[i];
	}
}

Polygon::~Polygon() {
	delete []points;
}

bool Polygon::PointInFigure(const Point& obj) const {
	for (int i = 0; i < points_num - 1; ++i) {
		if (Segment(points[i], points[i + 1]).PointInFigure(obj)) {
			return true;
		}
	}
	if (Segment(points[points_num - 1], points[0]).PointInFigure(obj)) {
		return true;
	}
	double sum_angles = 0;
	for (int i = 0; i < points_num - 1; ++i) {
		double module = Vector(obj, points[i]).Module() * Vector(obj, points[i + 1]).Module();
		if (Vector(obj, points[i]).PseudoScalarProduct(Vector(obj, points[i + 1])) > 0) {
			sum_angles += acos(Vector(obj, points[i]).ScalarProduct(Vector(obj, points[i + 1])) / module);
		} else {
			sum_angles -= acos(Vector(obj, points[i]).ScalarProduct(Vector(obj, points[i + 1])) / module);
		}
	}
	double module = Vector(obj, points[points_num - 1]).Module() * Vector(obj, points[0]).Module();
	if (Vector(obj, points[points_num - 1]).PseudoScalarProduct(Vector(obj, points[0])) > 0) {
		sum_angles += acos(Vector(obj, points[points_num - 1]).ScalarProduct(Vector(obj, points[0])) / module);
	}
	else {
		sum_angles -= acos(Vector(obj, points[points_num - 1]).ScalarProduct(Vector(obj, points[0])) / module);
	}
	if (fabs(fabs(sum_angles) - 2*3.14159265) < 1E-4) {
		return true;
	}
	return false;
}

double Vector::OrientTriangleArea(const Vector& other) const {
	return PseudoScalarProduct(other) / 2;
}

double Polygon::PolygonArea() const {
	Point start(0, 0);
	double s = 0;
	for (int i = 0; i < points_num - 1; i++) {
		s += Vector(start, points[i]).OrientTriangleArea(Vector(start, points[i + 1]));
	}
	s += Vector(start, points[points_num - 1]).OrientTriangleArea(Vector(start, points[0]));
	return fabs(s);
}

Polygon &Polygon::Shift(const Vector& obj) {
	for (int i = 0; i < points_num; i++) {
		points[i].x += obj.x;
		points[i].y += obj.y;
	}
	return *this;
}

bool Polygon::IsIntersect(const Segment& obj) const {
	for (int i = 0; i < points_num ; i++) {
		Segment side(points[i], points[(i + 1) % (points_num - 1)]);
		if (obj.IsIntersect(side)) {
			return true;
		}
	}
	return false;
}

Polygon Polygon::ConvexHull() const {
	Polygon temp(*this);

	return temp;
}

int main() {
	int num;
	std::cin >> num;
	Polygon polygon(num);
	std::cin >> polygon;
	std::cout << polygon.ConvexHull();
	return 0;
}