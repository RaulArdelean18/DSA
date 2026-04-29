#ifndef LEE_H
#define LEE_H

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class Coada;

namespace A {
class Lee {
  private:
    int n, m;
    int **road, **dist;
    std::vector<std::pair<int, int>> min_path_road;
    const int di[4] = {-1, 1, 0, 0}, dj[4] = {0, 0, -1, 1};
    /**
     * Verific daca {i,j} se afla in matrice
     * @param i - linia unde se afla punctul
     * @param j - coloana unde se afla punctul
     * @pre Nu exista
     * @post returneaza true daca punctul se afla in matrice
     * @return true, daca ii in matrice, fals daca se afla in exterior
     * Complexitate Theta(1)
     */
    bool inside(int i, int j);

    /**
     * Codific pozitia {i,j} liniar, ca sa il reduc la un indice
     * @param i - linia unde se afla punctul
     * @param j - coloana unde se afla punctul
     * @pre Nu exista
     * @post returneaza pozitia lui {i,j} daca matricea ii liniarizata
     * @return int, care reprezinta pozitia in vectorul liniar
     * Complexitate Theta(1)
     */
    int codify(int i, int j);

    /**
     * Decodific pozitia i din vectorul liniar si il transform in {i,j}
     * @param i - linia unde se afla punctul
     * @pre Nu exista
     * @post returneaza pozitia lui i in matrice
     * @return int, care reprezinta pozitia in matrice
     * Complexitate Theta(1)
     */
    std::pair<int, int> decodify(int i);

    /**
     * Aflu pozitia {i,j} pe unde pot sa ies cel mai repede din matrice
     * @pre Nu exista
     * @post returneaza pozitia unde pot iesi mai repede. daca nu exista, dam
     * return {-1,-1}
     * @return int, care reprezinta pozitia din matrice pe unde iesi cel mai
     * repede
     * Complexitate Theta(max(n,m))
     */
    std::pair<int, int> find_min_position();

  public:
    /**
     * Init la clasa lee si valorile din clasa
     * @param nrlinii - nr de linii din matrice
     * @param nrcol - nr de coloane din matrice
     * @pre nu exista
     * @return nothing
     * Complexitate Theta(n*m)
     */
    Lee(int nrlinii, int nrcol);

    /**
     * Functia de lee, de unde propag ca sa aflu drumurile din {isrc,jsrc}
     * @param isrc - linia de unde incep
     * @param jsrc - coloana de unde incep
     * @param mat - matrice booleana cu zonele unde pot intra si pe unde nu pot
     * intra
     * @pre - isrc, jsrc sa fie in matrice
     * @return nimic
     * Complexitate O(n*m)
     */
    void lee_propag(int isrc, int jsrc, bool **mat);

    /**
     * Aflu distanta cea mai scurta pentru a iesi din matrice
     * @pre nu exista
     * @post throw runtime_error daca nu exista un pct pe unde sa ies
     * @return int, distanta cea mai scurta
     * Complexitate Theta(1)
     */
    int min_path_distance();

    /**
     * Aflam drumul de la {i,j} pana la punctul de unde am pornit cu cautarea si
     * o retinem in @min_path_road
     * @param i - linia de unde pornim
     * @param j - coloana de unde pornim
     * @pre - {i,j} sa fie in matrice
     * @return nothing
     * Complexitate Theta(k), unde k ii nr de pozitii
     */
    void marsul_piticilor(int i, int j);

    /**
     * Functia ne da drumul cel mai scurt de la robot
     * @return vector<pair<int,int>> unde am pozitiile de la robot pana la
     * outside of the matrix\ Complexitate Theta(1)
     */
    std::vector<std::pair<int, int>> path();
};

} // namespace A

#endif