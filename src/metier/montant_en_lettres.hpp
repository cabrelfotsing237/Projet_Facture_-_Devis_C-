/**
 * @file montant_en_lettres.hpp
 * @brief Conversion d'un nombre entier en toutes lettres (français), EOO-06.
 *
 * Module indépendant : il ne dépend que de la bibliothèque standard et de
 * erreurs.hpp. Il ne contient ni entrée/sortie ni accès à la base de données.
 *
 * Orthographe appliquée (cahier des charges, §8) :
 *  - « vingt et un », « soixante et onze » mais « quatre-vingt-un »,
 *    « quatre-vingt-onze » ;
 *  - « quatre-vingts » et « deux cents » prennent un « s » seulement lorsqu'ils
 *    ne sont suivis d'aucun autre nombre, sauf « million(s) » et
 *    « milliard(s) » (« deux cents millions ») ; devant « mille », pas de « s » ;
 *  - « mille » est invariable ; « million » et « milliard » prennent un « s »
 *    au pluriel.
 */
#ifndef ISTILE_METIER_MONTANT_EN_LETTRES_HPP
#define ISTILE_METIER_MONTANT_EN_LETTRES_HPP

#include <cstdint>
#include <string>

namespace istile::metier {

/** @brief Plus grand nombre convertible : 999 999 999 999 (jusqu'aux milliards). */
constexpr std::int64_t kNombreMaximalEnLettres = 999'999'999'999;

/**
 * @brief Écrit un nombre entier positif ou nul en toutes lettres.
 *
 * @param nombre Valeur comprise entre 0 et kNombreMaximalEnLettres.
 * @return Le nombre en lettres, en minuscules, sans unité monétaire
 *         (ex. 1988000 -> « un million neuf cent quatre-vingt-huit mille »).
 * @throws ErreurValidation si @p nombre est négatif ou trop grand.
 */
std::string nombreEnLettres(std::int64_t nombre);

/**
 * @brief Écrit un montant en FCFA en toutes lettres, avec l'unité monétaire.
 *
 * Ajoute « franc CFA » (0 et 1) ou « francs CFA » (au-delà). Pour un nombre
 * qui se termine par « million(s) » ou « milliard(s) » sans autre mot, la
 * préposition « de » est ajoutée (« deux millions de francs CFA »).
 *
 * @param montant Montant entier en FCFA, compris entre 0 et
 *        kNombreMaximalEnLettres.
 * @return Le montant en lettres (ex. 894017 ->
 *         « huit cent quatre-vingt-quatorze mille dix-sept francs CFA »).
 * @throws ErreurValidation si @p montant est négatif ou trop grand.
 */
std::string montantEnLettres(std::int64_t montant);

}  // namespace istile::montant

#endif  // ISTILE_METIER_MONTANT_EN_LETTRES_HPP