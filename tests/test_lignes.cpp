#include <doctest/doctest.h>

#include <memory>
#include <vector>

#include "metier/erreurs.hpp"
#include "metier/ligne_document.hpp"
#include "metier/ligne_fourniture.hpp"
#include "metier/ligne_main_oeuvre.hpp"
#include "metier/montant.hpp"
#include "metier/quantite.hpp"

using istile::metier::ErreurValidation;
using istile::metier::LigneDocument;
using istile::metier::LigneFourniture;
using istile::metier::LigneMainOeuvre;
using istile::metier::Montant;
using istile::metier::Quantite;

// --- LigneFourniture --------------------------------------------------------
TEST_CASE("fourniture : 13 disjoncteurs à 4 500")
{
    const LigneFourniture ligne("Disjoncteur DPN 16A", Quantite::deUnites(13), Montant(4500));
    CHECK(ligne.montant() == Montant(58500));
    CHECK(ligne.designation() == "Disjoncteur DPN 16A");
}
TEST_CASE("fourniture : accesseurs")
{
    const LigneFourniture ligne("Câble", Quantite(250), Montant(1000));
    CHECK(ligne.quantite().centiemes() == 250);
    CHECK(ligne.prixUnitaire() == Montant(1000));
}
TEST_CASE("fourniture : quantité décimale exacte") // 2,50 × 1000 = 2500
{
    const LigneFourniture ligne("Câble", Quantite(250), Montant(1000));
    CHECK(ligne.montant() == Montant(2500));
}
TEST_CASE("fourniture : 0,5 × 15 = 7,5 arrondi à 8 (half-up)")
{
    const LigneFourniture ligne("Colle", Quantite(50), Montant(15));
    CHECK(ligne.montant() == Montant(8));
}
TEST_CASE("CT-03 : prix nul refusé")
{
    CHECK_THROWS_AS(LigneFourniture("Article", Quantite::deUnites(1), Montant(0)), ErreurValidation);
}
TEST_CASE("fourniture : prix négatif refusé")
{
    CHECK_THROWS_AS(LigneFourniture("Article", Quantite::deUnites(1), Montant(-5)), ErreurValidation);
}
TEST_CASE("fourniture : désignation vide refusée")
{
    CHECK_THROWS_AS(LigneFourniture("", Quantite::deUnites(1), Montant(100)), ErreurValidation);
}

// --- LigneMainOeuvre --------------------------------------------------------
TEST_CASE("main-d'oeuvre : 5 jours × 3 personnes × 10 000")
{
    const LigneMainOeuvre ligne("Saignées et passage des gaines", 5, 3, Montant(10000));
    CHECK(ligne.montant() == Montant(150000));
}
TEST_CASE("main-d'oeuvre : 7 jours × 2 personnes × 12 500")
{
    const LigneMainOeuvre ligne("Pose des appareillages", 7, 2, Montant(12500));
    CHECK(ligne.montant() == Montant(175000));
}
TEST_CASE("main-d'oeuvre : accesseurs")
{
    const LigneMainOeuvre ligne("Pose", 7, 2, Montant(12500));
    CHECK(ligne.jours() == 7);
    CHECK(ligne.personnes() == 2);
    CHECK(ligne.prixJournalier() == Montant(12500));
}
TEST_CASE("main-d'oeuvre : jours ou personnes nuls refusés")
{
    CHECK_THROWS_AS(LigneMainOeuvre("Pose", 0, 2, Montant(12500)), ErreurValidation);
    CHECK_THROWS_AS(LigneMainOeuvre("Pose", 7, 0, Montant(12500)), ErreurValidation);
}
TEST_CASE("main-d'oeuvre : prix journalier nul refusé")
{
    CHECK_THROWS_AS(LigneMainOeuvre("Pose", 7, 2, Montant(0)), ErreurValidation);
}
TEST_CASE("main-d'oeuvre : désignation vide refusée")
{
    CHECK_THROWS_AS(LigneMainOeuvre("", 7, 2, Montant(12500)), ErreurValidation);
}

// --- Polymorphisme ----------------------------------------------------------
namespace
{
    Montant sousTotal(const std::vector<std::unique_ptr<LigneDocument>> &lignes)
    {
        Montant total;
        for (const auto &ligne : lignes)
        {
            total += ligne->montant(); // appel virtuel : la bonne formule selon le type
        }
        return total;
    }
} // namespace

TEST_CASE("polymorphisme : sous-total I des fournitures de CT-01 = 440 000")
{
    std::vector<std::unique_ptr<LigneDocument>> lignes;
    lignes.push_back(std::make_unique<LigneFourniture>("Disjoncteur DPN 16A", Quantite::deUnites(13), Montant(4500)));
    lignes.push_back(std::make_unique<LigneFourniture>("Câble TH 2,5 mm2", Quantite::deUnites(9), Montant(25000)));
    lignes.push_back(std::make_unique<LigneFourniture>("Interrupteur va-et-vient", Quantite::deUnites(23), Montant(1500)));
    lignes.push_back(std::make_unique<LigneFourniture>("Prise de courant 2P+T", Quantite::deUnites(28), Montant(1500)));
    lignes.push_back(std::make_unique<LigneFourniture>("Piquet de terre 2 m", Quantite::deUnites(4), Montant(20000)));
    CHECK(sousTotal(lignes) == Montant(440000));
}
TEST_CASE("polymorphisme : sous-total II de la main-d'oeuvre de CT-01 = 325 000")
{
    std::vector<std::unique_ptr<LigneDocument>> lignes;
    lignes.push_back(std::make_unique<LigneMainOeuvre>("Saignées et passage des gaines", 5, 3, Montant(10000)));
    lignes.push_back(std::make_unique<LigneMainOeuvre>("Pose, câblage, mise en service", 7, 2, Montant(12500)));
    CHECK(sousTotal(lignes) == Montant(325000));
}
TEST_CASE("polymorphisme : lignes de types différents dans un même conteneur")
{
    std::vector<std::unique_ptr<LigneDocument>> lignes;
    lignes.push_back(std::make_unique<LigneFourniture>("Piquet de terre 2 m", Quantite::deUnites(4), Montant(20000)));
    lignes.push_back(std::make_unique<LigneMainOeuvre>("Pose", 1, 2, Montant(10000)));
    CHECK(sousTotal(lignes) == Montant(100000));
}

// --- Copie profonde (EF-13) ---------------------------------------------------
TEST_CASE("cloner : une fourniture copiée garde son type et son montant")
{
    const LigneFourniture origine("Prise", Quantite::deUnites(28), Montant(1500));
    const std::unique_ptr<LigneDocument> copie = origine.cloner();
    CHECK(copie.get() != &origine);
    CHECK(copie->montant() == Montant(42000));
    CHECK(copie->designation() == "Prise");
    CHECK(dynamic_cast<LigneFourniture *>(copie.get()) != nullptr);
}
TEST_CASE("cloner : une main-d'oeuvre copiée garde son type et son montant")
{
    const LigneMainOeuvre origine("Pose", 7, 2, Montant(12500));
    const std::unique_ptr<LigneDocument> copie = origine.cloner();
    CHECK(copie->montant() == Montant(175000));
    CHECK(dynamic_cast<LigneMainOeuvre *>(copie.get()) != nullptr);
}