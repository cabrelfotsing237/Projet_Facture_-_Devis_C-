/**
 * @file ligne_document.hpp
 * @brief Classe abstraite d'une ligne de devis ou de facture (EOO-03).
 */
#ifndef ISTILE_METIER_LIGNE_DOCUMENT_HPP
#define ISTILE_METIER_LIGNE_DOCUMENT_HPP

#include <memory>
#include <string>

#include "montant.hpp"

namespace istile::metier
{

    /**
     * @brief Ligne d'un document : une désignation et un montant calculé.
     *
     * Classe abstraite : on ne peut pas créer de LigneDocument directement, mais
     * seulement ses classes dérivées (LigneFourniture, LigneMainOeuvre). Le
     * montant se calcule par une méthode virtuelle pure : chaque type de ligne
     * applique sa propre formule (polymorphisme).
     */
    class LigneDocument
    {
    public:
        /** @brief Destructeur virtuel : détruire par un pointeur de base est sûr. */
        virtual ~LigneDocument() = default;

        /** @brief Texte de la ligne (jamais vide). */
        const std::string &designation() const { return designation_; }

        /** @brief Montant HT de la ligne, calculé selon le type de ligne (§8). */
        virtual Montant montant() const = 0;

        /** @brief Copie profonde, pour dupliquer un devis (EF-13). */
        virtual std::unique_ptr<LigneDocument> cloner() const = 0;

        /** @brief L'affectation est interdite (évite le « slicing »). */
        LigneDocument &operator=(const LigneDocument &) = delete;

    protected:
        /** @throws ErreurValidation si la désignation est vide. */
        explicit LigneDocument(std::string designation);

        /** @brief Copie réservée aux classes dérivées (utilisée par cloner()). */
        LigneDocument(const LigneDocument &) = default;

    private:
        std::string designation_;
    };

} // namespace istile::metier

#endif // ISTILE_METIER_LIGNE_DOCUMENT_HPP