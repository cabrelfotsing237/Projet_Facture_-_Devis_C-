#include <doctest/doctest.h>

#include "metier/arrondi.hpp"
#include "metier/erreurs.hpp"

using istile::metier::divisionArrondie;
using istile::metier::ErreurValidation;

TEST_CASE("arrondi : zéro") { CHECK(divisionArrondie(0, 10) == 0); }
TEST_CASE("arrondi : division exacte") { CHECK(divisionArrondie(20, 10) == 2); }
TEST_CASE("arrondi : en dessous de la moitié, vers le bas") { CHECK(divisionArrondie(14, 10) == 1); }
TEST_CASE("arrondi : la moitié exacte monte (half-up)")
{
    CHECK(divisionArrondie(15, 10) == 2);
    CHECK(divisionArrondie(1, 2) == 1);
    CHECK(divisionArrondie(3, 2) == 2);
}
TEST_CASE("arrondi : au-dessus de la moitié, vers le haut") { CHECK(divisionArrondie(16, 10) == 2); }
TEST_CASE("arrondi : dénominateur impair")
{
    CHECK(divisionArrondie(1, 3) == 0);
    CHECK(divisionArrondie(2, 3) == 1);
}
TEST_CASE("arrondi : exemple du cahier, 144317,25 donne 144317")
{
    CHECK(divisionArrondie(749700 * 1925, 10000) == 144317);
}
TEST_CASE("arrondi : même résultat que la formule du cahier (n*1925 + 5000) / 10000")
{
    for (std::int64_t ht = 0; ht <= 100000; ht += 37)
    {
        CHECK(divisionArrondie(ht * 1925, 10000) == (ht * 1925 + 5000) / 10000);
    }
}
TEST_CASE("arrondi : numérateur négatif refusé") { CHECK_THROWS_AS(divisionArrondie(-1, 10), ErreurValidation); }
TEST_CASE("arrondi : dénominateur nul ou négatif refusé")
{
    CHECK_THROWS_AS(divisionArrondie(5, 0), ErreurValidation);
    CHECK_THROWS_AS(divisionArrondie(5, -3), ErreurValidation);
}