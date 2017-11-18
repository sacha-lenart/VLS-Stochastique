#ifndef LOCALISATION_H
#define LOCALISATION_H


class Localisation
{
    public:
        Localisation();
        Localisation(double x, double y);
        virtual ~Localisation();

        double GetcoordX() { return coordX; }
        void SetcoordX(double val) { coordX = val; }
        double GetcoordY() { return coordY; }
        void SetcoordY(double val) { coordY = val; }

    protected:

    private:
        double coordX;
        double coordY;
};

#endif // LOCALISATION_H
