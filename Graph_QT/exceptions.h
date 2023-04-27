#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

using std::exception;

namespace exceptions {

    class PasAssezDeSommetsException : public exception
    {
    private:
        const char* what_message;
    public:
        PasAssezDeSommetsException(char const* const message = "") throw();
        virtual char const* what() const throw();
    }; // PasAssezDeSommetsException

    class SommetsNonReliesException : public exception
    {
    private:
        const char* what_message;
    public:
        SommetsNonReliesException(char const* const message = "") throw();
        virtual char const* what() const throw();
    }; // SommetsNonReliesException

}

#endif // EXCEPTIONS_H
