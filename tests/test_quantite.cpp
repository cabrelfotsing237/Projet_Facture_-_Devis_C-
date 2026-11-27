#include <doctest/doctest.h>

#include "metier/erreurs.hpp"
#include "metier/quantite.hpp"

using istile::metier::ErreurValidation;
using istile::metier::Quantite;

TEST_CASE("quantité : en unités entières") { CHECK(Quantite::deUnites(13).centiemes() == 1300); }
TEST_CASE("quantité : en centièmes") { CHECK(Quantite(250).centiemes() == 250); }
TEST_CASE("quantité : un centième, la plus petite valeur") { CHECK(Quantite(1).centiemes() == 1); }
TEST_CASE("quantité : zéro refusé")
{
    CHECK_THROWS_AS(Quantite(0), ErreurValidation);
    CHECK_THROWS_AS(Quantite::deUnites(0), ErreurValidation);
}
TEST_CASE("CT-03 : quantité négative refusée")
{
    CHECK_THROWS_AS(Quantite(-2), ErreurValidation);
    CHECK_THROWS_AS(Quantite::deUnites(-2), ErreurValidation);
}