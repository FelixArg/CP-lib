const long double eps = 1e-9;
const long double pi = 3.14159265358979323846;

// скалярное произведение векторов - x1 * x2 + y1 * y2

bool dequal(long double a, long double b) {
	if (abs(a - b) < eps)
		return 1;
	return 0;
}

bool dless(long double a, long double b) {
	if (!dequal(a, b) && a < b)
		return 1;
	return 0;
}

bool dgreater(long double a, long double b) {
	if (!dequal(a, b) && a > b)
		return 1;
	return 0;
}

bool dlesseq(long double a, long double b) {
	if (dequal(a, b) || a < b)
		return 1;
	return 0;
}

bool dgreatereq(long double a, long double b) {
	if (dequal(a, b) || a > b)
		return 1;
	return 0;
}

struct doublep {
	long double x;
	long double y;

	const bool operator <(doublep a) const {
		if (dequal(this->x, a.x))
			return dless(this->y, a.y);
		return dless(this->x, a.x);
	}
};

long double area(doublep a, doublep b, doublep c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

long double dist(doublep a, doublep b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

long double ang(doublep a, doublep b, doublep c) {
	// угол abc
	doublep v1 = { a.x - b.x, a.y - b.y };
	doublep v2 = { c.x - b.x, c.y - b.y };
	long double aa = sqrt(v1.x * v1.x + v1.y * v1.y);
	long double bb = sqrt(v2.x * v2.x + v2.y * v2.y);
	long double s = v1.x * v2.x + v1.y * v2.y;
	return acos(s / (aa * bb));
}

vector<doublep> hull(vector<doublep> p) {
	int n = p.size();
	if (n == 1)
		return p;
	vector<doublep> u, d;
	sort(p.begin(), p.end());

	u.emplace_back(p[0]);
	d.emplace_back(p[0]);

	for (int i = 1; i < n; i++) {
		if (i == n - 1 || dless(area(p[0], p[i], p[n - 1]), 0)) {
			while (u.size() > 1 && dgreatereq(area(u[u.size() - 2], u[u.size() - 1], p[i]), 0))
				u.pop_back();
			u.emplace_back(p[i]);
		}

		if (i == n - 1 || dgreater(area(p[0], p[i], p[n - 1]), 0)) {
			while (d.size() > 1 && dlesseq(area(d[d.size() - 2], d[d.size() - 1], p[i]), 0))
				d.pop_back();
			d.emplace_back(p[i]);
		}
	}

	vector<doublep> res;
	for (int i = 0; i < u.size(); i++) {
		res.emplace_back(u[i]);
	}

	for (int i = d.size() - 2; i > 0; i--) {
		res.emplace_back(d[i]);
	}

	return res;
}

struct intp {
	int x;
	int y;

	const bool operator <(intp a) const {
		if (this->x == a.x)
			return this->y < a.y;
		return this->x < a.x;
	}
};

ll area(intp a, intp b, intp c) {
	// |x2 - x1, y2 - y1|
	// |x3 - x1, y3 - y1|
	return (ll)(b.x - a.x) * (c.y - a.y) - (ll)(c.x - a.x) * (b.y - a.y);
	// если < 0, то по часовой стрелке, если > 0, то против часовой стрелки, если 0, то 3 точки лежат на 1 прямой
}

long double dist(intp a, intp b) {
	return sqrt((ll)(a.x - b.x) * (a.x - b.x) + (ll)(a.y - b.y) * (a.y - b.y));
}

ll distsq(intp a, intp b) {
	return (ll)(a.x - b.x) * (a.x - b.x) + (ll)(a.y - b.y) * (a.y - b.y);
}

long double ang(intp a, intp b, intp c) {
	// угол abc
	intp v1 = { a.x - b.x, a.y - b.y };
	intp v2 = { c.x - b.x, c.y - b.y };
	long double aa = sqrt(v1.x * v1.x + v1.y * v1.y);
	long double bb = sqrt(v2.x * v2.x + v2.y * v2.y);
	long double s = v1.x * v2.x + v1.y * v2.y;
	return acos(s / (aa * bb));
}

vector<intp> hull(vector<intp> p) {
	int n = p.size();
	if (n == 1)
		return p;
	vector<intp> u, d;
	sort(p.begin(), p.end());

	u.emplace_back(p[0]);
	d.emplace_back(p[0]);

	for (int i = 1; i < n; i++) {
		if (area(p[0], p[i], p[n - 1]) < 0) {
			while (u.size() > 1 && area(u[u.size() - 2], u[u.size() - 1], p[i]) >= 0)
				u.pop_back();
			u.emplace_back(p[i]);
		}

		if (area(p[0], p[i], p[n - 1]) > 0) {
			while (d.size() > 1 && area(d[d.size() - 2], d[d.size() - 1], p[i]) <= 0)
				d.pop_back();
			d.emplace_back(p[i]);
		}
	}

	vector<intp> res;
	for (int i = 0; i < u.size(); i++) {
		res.emplace_back(u[i]);
	}

	for (int i = d.size() - 2; i > 0; i--) {
		res.emplace_back(d[i]);
	}

	return res;
}