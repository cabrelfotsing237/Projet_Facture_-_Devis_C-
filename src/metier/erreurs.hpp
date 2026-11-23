/**
 * @file erreurs.hpp
 * @brief Hiérarchie d'exceptions du projet (EOO-07).
 *
 * Toutes les exceptions du projet dérivent de ErreurProjet, elle-même dérivée
 * de std::runtime_error. Aucun exit() n'est utilisé dans les couches métier et
 * persistance : les erreurs remontent par exception jusqu'à la présentation.
 */
#ifndef ISTILE_METIER_ERREURS_HPP
#define ISTILE_METIER_ERREURS_HPP

#include <stdexcept>

namespace istile::metier {

/** @brief Classe de base de toutes les exceptions du projet. */
class ErreurProjet : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/**
 * @brief Violation d'un invariant du domaine (prix <= 0, quantité <= 0,
 *        remise hors de [0, 100], nombre négatif, etc.).
 */
class ErreurValidation : public ErreurProjet {
public:
    using ErreurProjet::ErreurProjet;
};

}  // namespace istile::metier

#endif  // ISTILE_METIER_ERREURS_HPP