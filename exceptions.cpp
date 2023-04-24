#include "exceptions.h"

namespace exceptions {

    // ---------- PasAssezDeSommetsException ----------
    PasAssezDeSommetsException::PasAssezDeSommetsException(const char* message) throw() : what_message{message}
    {}

    const char* PasAssezDeSommetsException::what() const throw() {return what_message;}
    // ---------- End of PasAssezDeSommetsException ----------



    // ---------- SommetsNonReliesException ----------
    SommetsNonReliesException::SommetsNonReliesException(const char* message) throw() : what_message{message}
    {}

    const char* SommetsNonReliesException::what() const throw() {return what_message;}
    // ---------- End of SommetsNonReliesException ----------
}
