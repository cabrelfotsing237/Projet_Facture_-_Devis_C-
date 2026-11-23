#include "montant_en_lettres.hpp"

#include <array>
#include <string_view>

#include "erreurs.hpp"

namespace istile::metier
{

    namespace
    {

        // Seuils linguistiques (ils structurent les règles du français, pas des
        // « nombres magiques » métier).
        constexpr int kCent = 100;
        constexpr int kVingt = 20;
        constexpr int kSoixante = 60;
        constexpr int kSoixanteDix = 70;
        constexpr int kQuatreVingts = 80;
        constexpr int kSoixanteEtOnze = 11; // « soixante et onze »
        constexpr int kUn = 1;

        constexpr std::int64_t kMille = 1'000;
        constexpr std::int64_t kMillion = 1'000'000;
        constexpr std::int64_t kMilliard = 1'000'000'000;

        // Mots de 0 à 16 : à partir de 17, on compose (« dix-sept »).
        constexpr std::array<std::string_view, 17> kPetitsNombres{
            {"zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit",
             "neuf", "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize"}};

        // Dizaines régulières, indexées par le chiffre des dizaines (2 à 6).
        constexpr std::array<std::string_view, 7> kDizaines{
            {"", "", "vingt", "trente", "quarante", "cinquante", "soixante"}};

        /** Convertit un entier de 0 à 99. @p accord : « quatre-vingts » prend son « s ». */
        std::string moinsDeCent(int n, bool accord)
        {
            if (n < static_cast<int>(kPetitsNombres.size()))
            {
                return std::string{kPetitsNombres[static_cast<std::size_t>(n)]};
            }
            if (n < kVingt)
            { // 17, 18, 19
                return "dix-" + std::string{kPetitsNombres[static_cast<std::size_t>(n - 10)]};
            }
            if (n < kSoixanteDix)
            { // 20 à 69 : vingt, vingt et un, vingt-deux...
                const int dizaine = n / 10;
                const int unite = n % 10;
                std::string mot{kDizaines[static_cast<std::size_t>(dizaine)]};
                if (unite == kUn)
                {
                    return mot + " et un";
                }
                if (unite > 1)
                {
                    mot += "-" + std::string{kPetitsNombres[static_cast<std::size_t>(unite)]};
                }
                return mot;
            }
            if (n < kQuatreVingts)
            { // 70 à 79 : soixante + (10 à 19)
                const int reste = n - kSoixante;
                if (reste == kSoixanteEtOnze)
                {
                    return "soixante et onze";
                }
                return "soixante-" + moinsDeCent(reste, accord);
            }
            if (n == kQuatreVingts)
            {
                return accord ? "quatre-vingts" : "quatre-vingt";
            }
            return "quatre-vingt-" + moinsDeCent(n - kQuatreVingts, accord); // 81 à 99
        }

        /** Convertit un entier de 1 à 999. Même sens pour @p accord (« cents », « vingts »). */
        std::string moinsDeMille(int n, bool accord)
        {
            const int centaines = n / kCent;
            const int reste = n % kCent;
            if (centaines == 0)
            {
                return moinsDeCent(reste, accord);
            }
            std::string mot;
            if (centaines > 1)
            {
                mot = std::string{kPetitsNombres[static_cast<std::size_t>(centaines)]} + " ";
            }
            mot += "cent";
            if (reste == 0)
            {
                if (centaines > 1 && accord)
                {
                    mot += 's';
                }
                return mot;
            }
            return mot + " " + moinsDeCent(reste, accord);
        }

        /** Ajoute @p morceau à @p texte en les séparant par une espace. */
        void ajouter(std::string &texte, const std::string &morceau)
        {
            if (!texte.empty())
            {
                texte += ' ';
            }
            texte += morceau;
        }

    } // namespace

    std::string nombreEnLettres(std::int64_t nombre)
    {
        if (nombre < 0)
        {
            throw ErreurValidation("Le montant en lettres n'accepte pas de nombre négatif.");
        }
        if (nombre > kNombreMaximalEnLettres)
        {
            throw ErreurValidation("Nombre trop grand pour être écrit en lettres.");
        }
        if (nombre == 0)
        {
            return std::string{kPetitsNombres[0]};
        }

        const int milliards = static_cast<int>(nombre / kMilliard);
        const int millions = static_cast<int>((nombre % kMilliard) / kMillion);
        const int milliers = static_cast<int>((nombre % kMillion) / kMille);
        const int unites = static_cast<int>(nombre % kMille);

        std::string texte;
        if (milliards > 0)
        {
            // « million » et « milliard » sont des noms : le « s » d'accord s'applique.
            ajouter(texte, moinsDeMille(milliards, true) + " milliard" + (milliards > 1 ? "s" : ""));
        }
        if (millions > 0)
        {
            ajouter(texte, moinsDeMille(millions, true) + " million" + (millions > 1 ? "s" : ""));
        }
        if (milliers > 0)
        {
            // « mille » est invariable et ne déclenche pas le « s » (« deux cent mille »).
            ajouter(texte, milliers == 1 ? std::string{"mille"} : moinsDeMille(milliers, false) + " mille");
        }
        if (unites > 0)
        {
            ajouter(texte, moinsDeMille(unites, true));
        }
        return texte;
    }

    std::string montantEnLettres(std::int64_t montant)
    {
        std::string texte = nombreEnLettres(montant); // lève ErreurValidation si invalide

        const bool termineParMillionOuMilliard = montant > 0 && montant % kMillion == 0;
        if (termineParMillionOuMilliard)
        {
            texte += " de";
        }
        texte += (montant > 1) ? " francs CFA" : " franc CFA";
        return texte;
    }

} // namespace istile::metier
