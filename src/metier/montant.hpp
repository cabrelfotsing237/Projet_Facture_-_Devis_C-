/**
 * @file montant.hpp
 * @brief Montant en FCFA, entier exact (EOO-05) : jamais de float ni de double.
 */
#ifndef ISTILE_METIER_MONTANT_HPP
#define ISTILE_METIER_MONTANT_HPP

#include <cstdint>

#include "taux.hpp"

namespace istile::metier
{

    /**
     * @brief Somme d'argent en francs CFA (aucune subdivision en usage).
     *
     * Classe valeur : copiable, comparable, sans allocation. Le constructeur est
     * explicit pour éviter qu'un entier quelconque devienne un montant sans qu'on
     * l'ait écrit.
     */
    class Montant
    {
    public:
        /** @brief Montant nul. */
        constexpr Montant() = default;

        /** @brief Montant de @p francs francs CFA. */
        constexpr explicit Montant(std::int64_t francs) : valeur_(francs) {}

        /** @brief Valeur en francs CFA. */
        constexpr std::int64_t valeur() const { return valeur_; }

        /**
         * @brief Applique un taux au montant, arrondi half-up (§8 du cahier).
         *
         * Exemple : Montant(749700).fois(Taux(1925)) vaut Montant(144317).
         * @throws ErreurValidation si le montant est négatif.
         */
        Montant fois(const Taux &taux) const;

        constexpr Montant &operator+=(Montant autre)
        {
            valeur_ += autre.valeur_;
            return *this;
        }
        constexpr Montant &operator-=(Montant autre)
        {
            valeur_ -= autre.valeur_;
            return *this;
        }

    private:
        std::int64_t valeur_{0};
    };

    constexpr Montant operator+(Montant a, Montant b) { return a += b; }
    constexpr Montant operator-(Montant a, Montant b) { return a -= b; }
    constexpr bool operator==(Montant a, Montant b) { return a.valeur() == b.valeur(); }
    constexpr bool operator!=(Montant a, Montant b) { return !(a == b); }
    constexpr bool operator<(Montant a, Montant b) { return a.valeur() < b.valeur(); }
    constexpr bool operator>(Montant a, Montant b) { return b < a; }
    constexpr bool operator<=(Montant a, Montant b) { return !(b < a); }
    constexpr bool operator>=(Montant a, Montant b) { return !(a < b); }

} // namespace istile::metier

#endif // ISTILE_METIER_MONTANT_HPP