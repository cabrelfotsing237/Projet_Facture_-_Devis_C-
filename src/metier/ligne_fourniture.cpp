#include "ligne_fourniture.hpp"

#include <utility>

#include "arrondi.hpp"
#include "erreurs.hpp"

namespace istile::metier
{

    LigneFourniture::LigneFourniture(std::string designation, Quantite quantite, Montant prixUnitaire)
        : LigneDocument(std::move(designation)), quantite_(quantite), prixUnitaire_(prixUnitaire)
    {
        if (prixUnitaire_.valeur() <= 0)
        {
            throw ErreurValidation("Le prix unitaire d'une ligne doit être strictement positif.");
        }
    }

    Montant LigneFourniture::montant() const
    {
        // quantité en centièmes × prix, ramené à l'unité avec arrondi half-up.
        return Montant(divisionArrondie(quantite_.centiemes() * prixUnitaire_.valeur(),
                                        Quantite::kCentiemesParUnite));
    }

    std::unique_ptr<LigneDocument> LigneFourniture::cloner() const
    {
        return std::make_unique<LigneFourniture>(*this);
    }

} // namespace istile::metier