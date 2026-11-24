#include <doctest/doctest.h>

#include "metier/erreurs.hpp"
#include "metier/montant.hpp"
#include "metier/montant_en_lettres.hpp"
#include "metier/taux.hpp"

using istile::metier::ErreurValidation;
using istile::metier::Montant;
using istile::metier::montantEnLettres;
using istile::metier::Taux;

// --- Taux -----------------------------------------------------------------
TEST_CASE("taux : valeurs limites acceptées")
{
    CHECK(Taux(0).centiemesDePourcent() == 0);
    CHECK(Taux(10000).centiemesDePourcent() == 10000);
    CHECK(Taux(1925).centiemesDePourcent() == 1925);
}
TEST_CASE("taux : par défaut, 0 %") { CHECK(Taux().centiemesDePourcent() == 0); }
TEST_CASE("taux : hors de [0 %, 100 %] refusé")
{
    CHECK_THROWS_AS(Taux(-1), ErreurValidation);
    CHECK_THROWS_AS(Taux(10001), ErreurValidation);
}

// --- Montant --------------------------------------------------------------
TEST_CASE("montant : par défaut, nul") { CHECK(Montant().valeur() == 0); }
TEST_CASE("montant : valeur conservée") { CHECK(Montant(4500).valeur() == 4500); }
TEST_CASE("montant : addition et soustraction")
{
    CHECK(Montant(440000) + Montant(325000) == Montant(765000));
    CHECK(Montant(765000) - Montant(15300) == Montant(749700));
}
TEST_CASE("montant : comparaisons")
{
    CHECK(Montant(1) < Montant(2));
    CHECK(Montant(2) > Montant(1));
    CHECK(Montant(2) <= Montant(2));
    CHECK(Montant(2) >= Montant(2));
    CHECK(Montant(2) != Montant(3));
}
TEST_CASE("montant : taux de 0 % et de 100 %")
{
    CHECK(Montant(12345).fois(Taux(0)) == Montant(0));
    CHECK(Montant(12345).fois(Taux(10000)) == Montant(12345));
}
TEST_CASE("montant : remise de 2 % sur 765 000")
{
    CHECK(Montant(765000).fois(Taux(200)) == Montant(15300));
}
TEST_CASE("montant : TVA 19,25 % sur 749 700, arrondi half-up")
{
    CHECK(Montant(749700).fois(Taux(1925)) == Montant(144317));
}
TEST_CASE("montant : la moitié exacte est arrondie vers le haut")
{
    CHECK(Montant(10).fois(Taux(5000)) == Montant(5)); // 50 % de 10 = 5 exactement
    CHECK(Montant(1).fois(Taux(5000)) == Montant(1));  // 0,5 -> 1
}
TEST_CASE("montant : montant négatif refusé pour un taux")
{
    CHECK_THROWS_AS(Montant(-100).fois(Taux(1925)), ErreurValidation);
}

// --- CT-01 : totaux du devis de référence, en mémoire, sans base ------------
TEST_CASE("CT-01 : totaux du devis de référence")
{
    const Montant sousTotalFournitures(440000);
    const Montant sousTotalMainOeuvre(325000);

    const Montant totalHtBrut = sousTotalFournitures + sousTotalMainOeuvre;
    CHECK(totalHtBrut == Montant(765000));

    const Montant remise = totalHtBrut.fois(Taux(200)); // 2 %
    CHECK(remise == Montant(15300));

    const Montant netHt = totalHtBrut - remise;
    CHECK(netHt == Montant(749700));

    const Montant tva = netHt.fois(Taux(1925)); // 19,25 %
    CHECK(tva == Montant(144317));

    const Montant ttc = netHt + tva;
    CHECK(ttc == Montant(894017));

    CHECK(montantEnLettres(ttc.valeur()) ==
          "huit cent quatre-vingt-quatorze mille dix-sept francs CFA");
}