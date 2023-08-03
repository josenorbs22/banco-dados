#ifndef COMET_HPP
#define COMET_HPP

#include "astro.hpp"

using namespace std;

class Comet : public Astro {
    private:
        //Excentricidade da órbita
        double m_eccentricity;
        //Período de translação do cometa (anos)
        size_t m_period;
        //Periélio em UA (ponto da órbita mais próxima do Sol)
        double m_perihelion;
        //Afélio em UA (ponto da órbita mais distante do Sol)
        double m_aphelion;
    protected:
    public:
        Comet() {};
        Comet(Astro astro) : Astro(astro){}
        Comet(size_t id, string name, double eccentricity, size_t period, double perihelion, double aphelion) : 
            Astro(id, name), m_eccentricity(eccentricity), m_period(period), m_perihelion(perihelion), m_aphelion(aphelion) {};
        ~Comet(){};

        //Getters/Setters
        double GetEccentricity() const { return m_eccentricity; };
        void SetEccentricity(double eccentricity) { m_eccentricity = eccentricity; }; 
        size_t GetPeriod() const { return m_period; };
        void SetPeriod(size_t period) { m_period = period; };
        double GetPerihelion() const { return m_perihelion; };
        void SetPerihelion(double perihelion) { m_perihelion = perihelion; };
        double GetAphelion() const { return m_aphelion; };
        void SetAphelion(double aphelion) { m_aphelion = aphelion; };

        bool SaveComet();
        bool EditComet();
        bool DeleteComet();
};

Q_DECLARE_METATYPE(Comet*)
void LoadComets(vector<Comet*> &v_comet);
Comet* FindComet(size_t idComet, const vector<Comet*> &v_comets);

#endif
