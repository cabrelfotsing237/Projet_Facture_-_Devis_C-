#include "quantite.hpp"

#include "erreurs.hpp"

namespace istile::metier
{

    Quantite::Quantite(std::int64_t centiemes) : centiemes_(centiemes)
    {
        if (centiemes <= 0)
        {
            throw ErreurValidation("Une quantité doit être strictement positive.");
        }
    }

    Quantite Quantite::deUnites(std::int64_t unites)
    {
        if (unites <= 0)
        {
            throw ErreurValidation("Une quantité doit être strictement positive.");
        }
        return Quantite(unites * kCentiemesParUnite);
    }

} // namespace istile::metier