/**
 * @file taux.hpp
 * @brief Taux (TVA, remise) exprimé en centièmes de pour cent, sans virgule flottante.
 */
#ifndef ISTILE_METIER_TAUX_HPP
#define ISTILE_METIER_TAUX_HPP

#include <cstdint>

namespace istile::metier
{

    /**
     * @brief Pourcentage entre 0 % et 100 %, mémorisé en centièmes de pour cent.
     *
     * Taux(1925) représente 19,25 % ; Taux(200) représente 2 % ; Taux(10000) = 100 %.
     */
    class Taux
    {
    public:
        /** @brief Valeur interne de 100 % (dénominateur des calculs). */
        static constexpr std::int64_t kBase = 10'000;

        /** @brief Taux de 0 %. */
        Taux() = default;

        /**
         * @brief Crée un taux.
         * @param centiemesDePourcent Valeur comprise entre 0 et 10000.
         * @throws ErreurValidation si la valeur est hors de [0, 10000].
         */
        explicit Taux(std::int64_t centiemesDePourcent);

        /** @brief Valeur en centièmes de pour cent (19,25 % -> 1925). */
        std::int64_t centiemesDePourcent() const { return centiemes_; }

    private:
        std::int64_t centiemes_{0};
    };

} // namespace istile::metier

#endif // ISTILE_METIER_TAUX_HPP