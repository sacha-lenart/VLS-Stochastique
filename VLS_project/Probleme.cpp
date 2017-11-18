#include "Probleme.h"

Probleme::Probleme()
{

}

Probleme::Probleme(Algorithme * algo)
{
    this->algo=algo;
}

void Probleme::setAlgo(Algorithme * algo)
{
    this->algo=algo;
}

Probleme::~Probleme()
{
    //dtor
}
