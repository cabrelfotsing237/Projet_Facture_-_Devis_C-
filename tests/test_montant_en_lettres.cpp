#include <doctest/doctest.h>

#include <cstdint>
#include <string>

#include "metier/erreurs.hpp"
#include "metier/montant_en_lettres.hpp"

using istile::metier::ErreurValidation;
using istile::metier::kNombreMaximalEnLettres;
using istile::metier::montantEnLettres;
using istile::metier::nombreEnLettres;

// ---------------------------------------------------------------------------
// CT-02 : les 14 cas du cahier des charges (§10), un test par ligne du tableau.
// ---------------------------------------------------------------------------
#define CT02(nombre, attendu) \
    TEST_CASE("CT-02 : " #nombre) { CHECK(nombreEnLettres(nombre) == attendu); }

CT02(21, "vingt et un")
CT02(71, "soixante et onze")
CT02(80, "quatre-vingts")
CT02(81, "quatre-vingt-un")
CT02(91, "quatre-vingt-onze")
CT02(180, "cent quatre-vingts")
CT02(200, "deux cents")
CT02(201, "deux cent un")
CT02(80000, "quatre-vingt mille")
CT02(180000, "cent quatre-vingt mille")
CT02(200000, "deux cent mille")
CT02(1988000, "un million neuf cent quatre-vingt-huit mille")
CT02(2000000, "deux millions")
CT02(5594500, "cinq millions cinq cent quatre-vingt-quatorze mille cinq cents")

// ---------------------------------------------------------------------------
// Cas limites et règles d'orthographe complémentaires.
// ---------------------------------------------------------------------------
TEST_CASE("zéro") { CHECK(nombreEnLettres(0) == "zéro"); }
TEST_CASE("un") { CHECK(nombreEnLettres(1) == "un"); }
TEST_CASE("seize, dernier mot simple") { CHECK(nombreEnLettres(16) == "seize"); }
TEST_CASE("dix-sept") { CHECK(nombreEnLettres(17) == "dix-sept"); }
TEST_CASE("soixante-dix") { CHECK(nombreEnLettres(70) == "soixante-dix"); }
TEST_CASE("soixante-douze") { CHECK(nombreEnLettres(72) == "soixante-douze"); }
TEST_CASE("quatre-vingt-dix") { CHECK(nombreEnLettres(90) == "quatre-vingt-dix"); }
TEST_CASE("quatre-vingt-dix-neuf") { CHECK(nombreEnLettres(99) == "quatre-vingt-dix-neuf"); }
TEST_CASE("cent est invariable") { CHECK(nombreEnLettres(100) == "cent"); }
TEST_CASE("cent un") { CHECK(nombreEnLettres(101) == "cent un"); }
TEST_CASE("mille est invariable et sans 'un'") { CHECK(nombreEnLettres(1000) == "mille"); }
TEST_CASE("mille un") { CHECK(nombreEnLettres(1001) == "mille un"); }
TEST_CASE("deux mille") { CHECK(nombreEnLettres(2000) == "deux mille"); }
TEST_CASE("cent mille") { CHECK(nombreEnLettres(100000) == "cent mille"); }
TEST_CASE("quatre-vingt-un mille") { CHECK(nombreEnLettres(81000) == "quatre-vingt-un mille"); }
TEST_CASE("999 999")
{
    CHECK(nombreEnLettres(999999) ==
          "neuf cent quatre-vingt-dix-neuf mille neuf cent quatre-vingt-dix-neuf");
}
TEST_CASE("un million") { CHECK(nombreEnLettres(1000000) == "un million"); }
TEST_CASE("quatre-vingts millions : le 's' s'accorde devant million")
{
    CHECK(nombreEnLettres(80000000) == "quatre-vingts millions");
}
TEST_CASE("deux cents millions : le 's' s'accorde devant million")
{
    CHECK(nombreEnLettres(200000000) == "deux cents millions");
}
TEST_CASE("un milliard") { CHECK(nombreEnLettres(1000000000) == "un milliard"); }
TEST_CASE("trois milliards") { CHECK(nombreEnLettres(3000000000) == "trois milliards"); }
TEST_CASE("plus grand nombre accepté")
{
    CHECK(nombreEnLettres(kNombreMaximalEnLettres) ==
          "neuf cent quatre-vingt-dix-neuf milliards neuf cent quatre-vingt-dix-neuf millions "
          "neuf cent quatre-vingt-dix-neuf mille neuf cent quatre-vingt-dix-neuf");
}

// ---------------------------------------------------------------------------
// Entrées invalides : exception, jamais de plantage.
// ---------------------------------------------------------------------------
TEST_CASE("nombre négatif : ErreurValidation")
{
    CHECK_THROWS_AS(nombreEnLettres(-1), ErreurValidation);
    CHECK_THROWS_AS(montantEnLettres(-5000), ErreurValidation);
}
TEST_CASE("nombre trop grand : ErreurValidation")
{
    CHECK_THROWS_AS(nombreEnLettres(kNombreMaximalEnLettres + 1), ErreurValidation);
}

// ---------------------------------------------------------------------------
// Montant avec unité monétaire.
// ---------------------------------------------------------------------------
TEST_CASE("CT-01 : TTC du devis de référence")
{
    CHECK(montantEnLettres(894017) ==
          "huit cent quatre-vingt-quatorze mille dix-sept francs CFA");
}
TEST_CASE("Anomalie A1 corrigée : 1 988 000")
{
    CHECK(montantEnLettres(1988000) == "un million neuf cent quatre-vingt-huit mille francs CFA");
}
TEST_CASE("singulier pour 0 et 1")
{
    CHECK(montantEnLettres(0) == "zéro franc CFA");
    CHECK(montantEnLettres(1) == "un franc CFA");
}
TEST_CASE("pluriel dès 2") { CHECK(montantEnLettres(2) == "deux francs CFA"); }
TEST_CASE("'de' devant francs après million(s) ou milliard(s) ronds")
{
    CHECK(montantEnLettres(2000000) == "deux millions de francs CFA");
    CHECK(montantEnLettres(1000000000) == "un milliard de francs CFA");
    CHECK(montantEnLettres(2000001) == "deux millions un francs CFA");
}