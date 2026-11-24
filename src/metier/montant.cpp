#include "montant.hpp"

#include "arrondi.hpp"

namespace istile::metier
{

    Montant Montant::fois(const Taux &taux) const
    {
        return Montant(divisionArrondie(valeur_ * taux.centiemesDePourcent(), Taux::kBase));
    }

} // namespace istile::metier