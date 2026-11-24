/**
 * @file arrondi.hpp
 * @brief Division entière arrondie « demi vers le haut » (half-up), EOO-05.
 */
#ifndef ISTILE_METIER_ARRONDI_HPP
#define ISTILE_METIER_ARRONDI_HPP

#include <cstdint>

namespace istile::metier
{

    /**
     * @brief Calcule numerateur / denominateur arrondi à l'entier le plus proche,
     *        la moitié étant arrondie vers le haut, en arithmétique entière.
     *
     * Exemples : 14/10 -> 1 ; 15/10 -> 2 ; 144317,25 -> 144317.
     *
     * @param numerateur Entier positif ou nul.
     * @param denominateur Entier strictement positif.
     * @throws ErreurValidation si le numérateur est négatif ou le dénominateur <= 0.
     */
    std::int64_t divisionArrondie(std::int64_t numerateur, std::int64_t denominateur);

} // namespace istile::metier

#endif // ISTILE_METIER_ARRONDI_HPP