#include "noeud.h"

Noeud::Noeud(int id) : d_id{id}, d_info{}
{}

Noeud::Noeud(int id, const string& info) : d_id{id}, d_info{info}
{}

Noeud::Noeud(const Noeud& n) : d_id{n.d_id}, d_info{n.d_info}
{}

int Noeud::getId() const
{
    return d_id;
}

string Noeud::getInfo() const
{
    return d_info;
}

void Noeud::setId(int id)
{
    d_id = id;
}

void Noeud::setInfo(const string& info)
{
    d_info = info;
}

Noeud& Noeud::operator=(const Noeud& n)
{
    if(this == &n) return *this;

    d_id = n.d_id;
    d_info = n.d_info;

    return *this;
}

void Noeud::print(std::ostream& os) const
{
    os << toString();
}

string Noeud::toString() const
{
    return "Noeud{id=" + std::to_string(d_id) + ", info=\"" + d_info + "\"}";
}

std::ostream& operator<<(std::ostream& os, const Noeud& n)
{
    n.print(os);
    return os;
}
