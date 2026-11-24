#include "taux.hpp"

#include "erreurs.hpp"

namespace istile::metier
{

    Taux::Taux(std::int64_t centiemesDePourcent) : centiemes_(centiemesDePourcent)
    {
        if (centiemesDePourcent < 0 || centiemesDePourcent > kBase)
        {
            throw ErreurValidation("Un taux doit être compris entre 0 % et 100 %.");
        }
    }

} // namespace istile::metier