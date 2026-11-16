#include <iostream>   // std::cout, std::endl : affichage
#include <vector>     // std::vector : liste des sommets, liste des formes
#include <cmath>      // sqrt, pow, M_PI : distances, normalisation, aire du cercle
#include <stdexcept> // pour element invalide ex rayon negatif 
#include <string>

// Le parent abstrait : il impose le "quoi", pas le "comment"
class Forme {
public:
    virtual double aire() const = 0;      // = 0 → pas de code ici
    virtual double perimetre() const = 0;
    virtual ~Forme() {}
    virtual std::string nom() const = 0;
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
    double aire() const override { return M_PI*rayon*rayon  ;}
    double perimetre() const override { return 2*M_PI*rayon ;}
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
    double aire() const override { return cote*cote ;}
    double perimetre() const override {return 4*cote ;}

};

class Rectangle : public Forme {   // (dans ton projet : via Polygone)
    double largeur;
    double hauteur;
    std::string nom() const override { return "Rectangle"; }
public:
    Rectangle(double l, double h) : largeur(l), hauteur(h) {
        if (largeur < 0 || hauteur < 0) {
            throw std::invalid_argument("Dimensions negatifs");
        }
    }
    double aire() const override { return largeur*hauteur ;}
    double perimetre() const override {return 2*(largeur+hauteur) ;}
};

int main () {
    std::vector<Forme*> formes;  // liste de pointeurs vers Forme
    formes.push_back(new Cercle(2.0));
    formes.push_back(new Carre(2.0));
    formes.push_back(new Rectangle(3.0, 4.0));

    for (const auto& forme : formes) {
        std::cout << forme->nom() << " : Aire = " << forme->aire()<< " : " << " Perimetre = " << forme->perimetre() << std::endl;
    }

    // Libération de la mémoire
    for (auto& forme : formes) {
        delete forme;
    }
    return 0;
}
