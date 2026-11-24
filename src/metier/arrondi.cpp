#include "arrondi.hpp"

#include "erreurs.hpp"

namespace istile::metier
{

    std::int64_t divisionArrondie(std::int64_t numerateur, std::int64_t denominateur)
    {
        if (numerateur < 0)
        {
            throw ErreurValidation("L'arrondi n'accepte pas de numérateur négatif.");
        }
        if (denominateur <= 0)
        {
            throw ErreurValidation("Le dénominateur d'une division arrondie doit être strictement positif.");
        }
        // floor(n/d + 1/2) = floor((2n + d) / 2d) : exact pour tout d > 0, pair ou impair.
        return (2 * numerateur + denominateur) / (2 * denominateur);
    }

} // namespace istile::metier