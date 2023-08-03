#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include "planet.hpp"
#include "star.hpp"

using namespace std;

class SolarSystem {
    private:
        size_t m_id;
        //Sol ou sóis que compoem o sistema solar
        vector<Star*> m_star; 
        //Planetas presentes no sistema solar
        vector<Planet*> m_planet;
        //Nome do sistema solar
        string m_name;
    protected:
    public:
        SolarSystem() {}
        SolarSystem(size_t id, vector<Star*> stars, vector<Planet*> planets, string name) : 
            m_id(id), m_star(stars), m_planet(planets), m_name(name) {}
        ~SolarSystem(){}

        //Getters/Setters
        size_t GetId() const { return m_id; }
        void SetId(size_t id) { m_id = id; }
        vector<Star*> GetStars() const { return m_star; }
        void SetStars(vector<Star*> stars) { m_star = stars; }
        vector<Planet*> GetPlanets() const { return m_planet; }
        void SetPlanets(vector<Planet*> planets) { m_planet = planets; }
        string GetName() const { return m_name; }
        void SetName(string name) { m_name = name; }

        void UpdateStars(Star *star) { m_star.push_back(star); }
        void UpdatePlanets(Planet *planet) { m_planet.push_back(planet); }

        bool SaveSolarSystem();
        bool EditSolarSystem();
        bool DeleteSolarSystem();
};

void LoadSolarSystems(vector<SolarSystem> &v_ssystem, const vector<Star*> &v_star, const vector<Planet*> &v_planet);
size_t FindLastId(const vector<SolarSystem> &v_ssystem);

#endif
