#ifndef PERSO_H
#define PERSO_H

#include <iostream>

#include <fstream>
#include <vector>

class Perso
{
    public:
        Perso();
        virtual ~Perso();

        std::string getNom()const;
        int getAge()const ;
        float getTaille()const;
        std::vector <int>getVec()const;

        void setNom(std::string nom);
        void setAge(int age);
        void setTaille(float taille);
        void setVec(std::vector <int>vec);

        void display()const;

        void writeFile(const std::string& path);
        void readFile(const std::string& path);

    private:
        std::string m_nom ;
        int m_age ;
        float m_taille ;
        //std::vector <int> m_vec ;
};

#endif // PERSO_H
