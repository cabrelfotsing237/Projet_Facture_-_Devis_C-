/**
 * @file ligne_main_oeuvre.hpp
 * @brief Ligne de main-d'œuvre : jours × personnes × prix journalier (RG-10).
 */
#ifndef ISTILE_METIER_LIGNE_MAIN_OEUVRE_HPP
#define ISTILE_METIER_LIGNE_MAIN_OEUVRE_HPP

#include <cstdint>
#include <memory>
#include <string>

#include "ligne_document.hpp"
#include "montant.hpp"

namespace istile::metier
{

    /** @brief Ligne qui mémorise des jours, des personnes et un prix journalier. */
    class LigneMainOeuvre final : public LigneDocument
    {
    public:
        /**
         * @param designation Texte de la ligne (non vide).
         * @param jours Nombre de jours, strictement positif.
         * @param personnes Nombre de personnes, strictement positif.
         * @param prixJournalier Prix par jour et par personne, strictement positif.
         * @throws ErreurValidation si une valeur est invalide.
         */
        LigneMainOeuvre(std::string designation, std::int64_t jours, std::int64_t personnes,
                        Montant prixJournalier);

        std::int64_t jours() const { return jours_; }
        std::int64_t personnes() const { return personnes_; }
        Montant prixJournalier() const { return prixJournalier_; }

        /** @brief jours × personnes × prix journalier (produit exact, sans arrondi). */
        Montant montant() const override;

        std::unique_ptr<LigneDocument> cloner() const override;

    private:
        std::int64_t jours_;
        std::int64_t personnes_;
        Montant prixJournalier_;
    };

} // namespace istile::metier

#endif // ISTILE_METIER_LIGNE_MAIN_OEUVRE_HPP