#include <iostream>   // std::cout, std::endl : affichage
#include <vector>     // std::vector : liste des formes
#include <cmath>      // sqrt, pow, M_PI
#include <stdexcept>  // std::invalid_argument : element invalide ex rayon negatif
#include <string>

// Le parent abstrait : il impose le "quoi", pas le "comment"
class Forme {
public:
    virtual double aire() const = 0;      // = 0 -> pas de code ici
    virtual double perimetre() const = 0;
    virtual std::string nom() const = 0;
    virtual ~Forme() {}

    // Ecrite UNE seule fois ici : grace aux appels virtuels,
    // nom(), aire() et perimetre() appellent la version de la vraie forme.
    void afficheInfo() const {
        std::cout << nom()
                  << " : Aire = " << aire()
                  << " : Perimetre = " << perimetre()
                  << std::endl;
    }
};

// Une classe par forme : chacune donne le "comment"
class Cercle : public Forme {
    double rayon;
    std::string nom() const override { return "Cercle"; }
public:
    Cercle(double r) : rayon(r) {
        if (rayon < 0) {
            throw std::invalid_argument("Rayon negatif");
        }
    }
    double aire() const override { return M_PI * rayon * rayon; }
    double perimetre() const override { return 2 * M_PI * rayon; }
};

class Carre : public Forme {   // (dans ton projet : via Polygone)
    double cote;
    std::string nom() const override { return "Carre"; }
public:
    Carre(double c) : cote(c) {
        if (cote < 0) {
            throw std::invalid_argument("Cote negatif");
        }
    }
    double aire() const override { return cote * cote; }
    double perimetre() const override { return 4 * cote; }
};

class Rectangle : public Forme {   // (dans ton projet : via Polygone)
    double largeur;
    double hauteur;
    std::string nom() const override { return "Rectangle"; }
public:
    Rectangle(double l, double h) : largeur(l), hauteur(h) {
        if (largeur < 0 || hauteur < 0) {
            throw std::invalid_argument("Dimensions negatives");
        }
    }
    double aire() const override { return largeur * hauteur; }
    double perimetre() const override { return 2 * (largeur + hauteur); }
};

class Triangle : public Forme {   // triangle isocele
    double base;
    double hauteur;
    std::string nom() const override { return "Triangle"; }
public:
    Triangle(double b, double h) : base(b), hauteur(h) {
        if (base < 0 || hauteur < 0) {
            throw std::invalid_argument("Dimensions negatives");
        }
    }
    double aire() const override { return 0.5 * base * hauteur; }
    double perimetre() const override { return base + 2 * sqrt(pow(hauteur, 2) + pow(base / 2, 2)); }
};

int main() {
    std::vector<Forme*> formes;  // liste de pointeurs vers Forme
    formes.push_back(new Cercle(2.0));
    formes.push_back(new Carre(2.0));
    formes.push_back(new Rectangle(3.0, 4.0));
    formes.push_back(new Triangle(3.0, 4.0));

    // Le main ne sait plus COMMENT on affiche : il demande a chaque forme
    for (const auto& forme : formes) {
        forme->afficheInfo();
    }

    // Liberation de la memoire
    for (auto& forme : formes) {
        delete forme;
    }
    return 0;
}