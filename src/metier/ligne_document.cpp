#include "ligne_document.hpp"

#include <utility>

#include "erreurs.hpp"

namespace istile::metier
{

    LigneDocument::LigneDocument(std::string designation) : designation_(std::move(designation))
    {
        if (designation_.empty())
        {
            throw ErreurValidation("La désignation d'une ligne ne peut pas être vide.");
        }
    }

} // namespace istile::metier