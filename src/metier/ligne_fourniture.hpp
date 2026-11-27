/**
 * @file ligne_fourniture.hpp
 * @brief Ligne de fourniture : quantité × prix unitaire (RG-9).
 */
#ifndef ISTILE_METIER_LIGNE_FOURNITURE_HPP
#define ISTILE_METIER_LIGNE_FOURNITURE_HPP

#include <memory>
#include <string>

#include "ligne_document.hpp"
#include "montant.hpp"
#include "quantite.hpp"

namespace istile::metier
{

    /**
     * @brief Ligne qui mémorise la quantité et le prix unitaire appliqué.
     *
     * Le prix est celui de l'émission : il peut différer du prix du catalogue.
     */
    class LigneFourniture final : public LigneDocument
    {
    public:
        /**
         * @param designation Texte de la ligne (non vide).
         * @param quantite Quantité strictement positive.
         * @param prixUnitaire Prix unitaire HT, strictement positif (RG-4, A7).
         * @throws ErreurValidation si la désignation est vide ou le prix <= 0.
         */
        LigneFourniture(std::string designation, Quantite quantite, Montant prixUnitaire);

        Quantite quantite() const { return quantite_; }
        Montant prixUnitaire() const { return prixUnitaire_; }

        /** @brief Quantité × prix unitaire, arrondi half-up à l'unité (§8). */
        Montant montant() const override;

        std::unique_ptr<LigneDocument> cloner() const override;

    private:
        Quantite quantite_;
        Montant prixUnitaire_;
    };

} // namespace istile::metier

#endif // ISTILE_METIER_LIGNE_FOURNITURE_HPP