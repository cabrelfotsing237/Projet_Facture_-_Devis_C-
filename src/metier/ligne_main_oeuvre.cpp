#include "ligne_main_oeuvre.hpp"

#include <utility>

#include "erreurs.hpp"

namespace istile::metier
{

    LigneMainOeuvre::LigneMainOeuvre(std::string designation, std::int64_t jours,
                                     std::int64_t personnes, Montant prixJournalier)
        : LigneDocument(std::move(designation)),
          jours_(jours),
          personnes_(personnes),
          prixJournalier_(prixJournalier)
    {
        if (jours_ <= 0)
        {
            throw ErreurValidation("Le nombre de jours doit être strictement positif.");
        }
        if (personnes_ <= 0)
        {
            throw ErreurValidation("Le nombre de personnes doit être strictement positif.");
        }
        if (prixJournalier_.valeur() <= 0)
        {
            throw ErreurValidation("Le prix journalier doit être strictement positif.");
        }
    }

    Montant LigneMainOeuvre::montant() const
    {
        return Montant(jours_ * personnes_ * prixJournalier_.valeur());
    }

    std::unique_ptr<LigneDocument> LigneMainOeuvre::cloner() const
    {
        return std::make_unique<LigneMainOeuvre>(*this);
    }

} // namespace istile::metier