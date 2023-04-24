#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Noeud
{
public:
    Noeud(int id);
    Noeud(int id, const string& info);
    Noeud(const Noeud& n);
    int getId() const;
    string getInfo() const;
    void setId(int id);
    void setInfo(const string& info);

    Noeud& operator=(const Noeud& n);

    void print(std::ostream& os) const;
    string toString() const;
private:
    int d_id;
    string d_info;
};

std::ostream& operator<<(std::ostream& os, const Noeud& n);

#endif // NOEUD_H
