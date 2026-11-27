/**
 * @file quantite.hpp
 * @brief Quantité strictement positive, en centièmes d'unité (entier exact).
 */
#ifndef ISTILE_METIER_QUANTITE_HPP
#define ISTILE_METIER_QUANTITE_HPP

#include <cstdint>

namespace istile::metier
{

    /**
     * @brief Quantité d'un article sur une ligne de document (RG-9 : quantité > 0).
     *
     * Mémorisée en centièmes pour éviter tout nombre flottant : Quantite(250)
     * représente 2,50 ; Quantite::deUnites(13) représente 13.
     */
    class Quantite
    {
    public:
        /** @brief Nombre de centièmes dans une unité entière. */
        static constexpr std::int64_t kCentiemesParUnite = 100;

        /**
         * @brief Crée une quantité à partir de centièmes d'unité.
         * @throws ErreurValidation si @p centiemes <= 0.
         */
        explicit Quantite(std::int64_t centiemes);

        /**
         * @brief Crée une quantité en unités entières (13 -> 13,00).
         * @throws ErreurValidation si @p unites <= 0.
         */
        static Quantite deUnites(std::int64_t unites);

        /** @brief Valeur en centièmes d'unité. */
        std::int64_t centiemes() const { return centiemes_; }

    private:
        std::int64_t centiemes_;
    };

} // namespace istile::metier

#endif // ISTILE_METIER_QUANTITE_HPP