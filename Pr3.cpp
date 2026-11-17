#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

class Point {
private:
    double x;
    double y;
public:
    Point(double x, double y) : x(x), y(y) {}
    double getX() const { return x; }
    double getY() const { return y; }
};

class Forme {
public:
    virtual double aire() const = 0;
    virtual double perimetre() const = 0;
    virtual ~Forme() {}
};


class Cercle : public Forme {
private:
    Point centre;
    double rayon;
public:
    Cercle(const Point &centre, double rayon) : centre(centre), rayon(rayon) {
        if (rayon < 0) {
            throw std::invalid_argument("Rayon negatif");
        }
    }
    double aire() const override { return M_PI * rayon * rayon; }
    double perimetre() const override { return 2 * M_PI * rayon; }
};

class Polygone : public Forme {
private:
    std::vector<Point> sommets;
protected:
    Polygone(const std::vector<Point> &points) : sommets(points) {
        if (points.size() < 3) {
            throw std::invalid_argument("Un polygone a au moins 3 sommets");
        }
    }
    Point getSommet(int i) const { return sommets[i]; }
    static double distance(const Point &A, const Point &B) {
        return std::sqrt(std::pow(B.getX() - A.getX(), 2) + std::pow(B.getY() - A.getY(), 2));
    }
public:
    double perimetre() const override {
        double somme = 0;
        int n = sommets.size();
        for (int i = 0; i < n; i++) {
            somme += distance(getSommet(i), getSommet((i + 1) % n));
        }
        return somme;
    }
};

class Triangle : public Polygone {
public:
    Triangle(const Point &A, const Point &B, const Point &C)
        : Polygone({A, B, C}) {}
    double aire() const override {
        Point A = getSommet(0), B = getSommet(1), C = getSommet(2);
        return 0.5 * std::abs(A.getX() * (B.getY() - C.getY())
                            + B.getX() * (C.getY() - A.getY())
                            + C.getX() * (A.getY() - B.getY()));
    }
};

class Carre : public Polygone {
private:
    static std::vector<Point> construire(const Point &A, const Point &B) {
        double dx = B.getX() - A.getX();
        double dy = B.getY() - A.getY();
        return { A, B,
                 Point(B.getX() - dy, B.getY() + dx),
                 Point(A.getX() - dy, A.getY() + dx) };
    }
public:
    Carre(const Point &A, const Point &B) : Polygone(construire(A, B)) {}
    double aire() const override {
        double c = distance(getSommet(0), getSommet(1));
        return c * c;
    }
};

class Rectangle : public Polygone {
private:
    double largeur;
    static std::vector<Point> construire(const Point &A, const Point &B, double largeur) {
        if (largeur < 0) {
            throw std::invalid_argument("Largeur negative");
        }
        double dx = B.getX() - A.getX();
        double dy = B.getY() - A.getY();
        double longueur = std::sqrt(dx * dx + dy * dy);
        if (longueur == 0) {
            throw std::invalid_argument("A et B identiques");
        }
        double nx = -dy / longueur * largeur;
        double ny = dx / longueur * largeur;
        return { A, B,
                 Point(B.getX() + nx, B.getY() + ny),
                 Point(A.getX() + nx, A.getY() + ny) };
    }
public:
    Rectangle(const Point &A, const Point &B, double largeur)
        : Polygone(construire(A, B, largeur)), largeur(largeur) {}
    double aire() const override {
        return distance(getSommet(0), getSommet(1)) * largeur;
    }
};

int main() {
    std::vector<Forme*> formes;
    formes.push_back(new Cercle(Point(0, 0), 2.0));
    formes.push_back(new Carre(Point(0, 0), Point(2, 0)));
    formes.push_back(new Rectangle(Point(0, 0), Point(3, 0), 4.0));
    formes.push_back(new Triangle(Point(0, 0), Point(3, 0), Point(1.5, 4)));

    const char *noms[] = {"Cercle", "Carre", "Rectangle", "Triangle"};
    for (size_t i = 0; i < formes.size(); i++) {
        std::cout << noms[i]
                  << " : Aire = " << formes[i]->aire()
                  << " : Perimetre = " << formes[i]->perimetre()
                  << std::endl;
    }

    for (auto &forme : formes) {
        delete forme;
    }
    return 0;
}