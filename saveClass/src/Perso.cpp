#include "Perso.h"



Perso::Perso()
{
    m_nom = "pas de nom" ;
    m_age = 0 ;
    m_taille = 0 ;

   // for(int i=0 ; i<5 ; i++)
     //   m_vec.push_back(i);
}

Perso::~Perso()
{}

int Perso::getAge()const{return m_age;}
std::string Perso::getNom()const{return m_nom;}
float Perso::getTaille()const{return m_taille;}
//std::vector <int>Perso::getVec()const{return m_vec;}

void Perso::setNom(std::string nom){m_nom=nom ;}
void Perso::setAge(int age){m_age=age;}
void Perso::setTaille(float taille){m_taille=taille;}
//void Perso::setVec(std::vector <int>vec){m_vec=vec;}


void Perso::display()const
{
    std::cout <<"Nom : "<<getNom()<<std::endl<<"Age : "<<getAge()<<std::endl<<"Taille : "<<getTaille()<<std::endl;

    //for(const auto& item:getVec())
      //  std::cout<<item<<std::endl;

    std::cout<<"--------------------------------------------------------------------------------------"<<std::endl;
}

/// ///////////////////////////////////////////////////////////////////////////// ///
/// PERMET DE SAUVEGARDER UNE CLASSE DANS UN FICHIER DANS LE NOM EST EN PARAMÈTRE ///
/// ///////////////////////////////////////////////////////////////////////////// ///


void Perso::writeFile(const std::string& path)
{
    std::ofstream ofs(path.c_str(),std::ios::binary);
    if (ofs)
    {
        ofs.write((char*)this,sizeof(*this));

        ofs.close(); // fermeture du flux
    }
}


/// ////////////////////////////////////////////////////////////////////////// ///
/// PERMET DE LIRE UNE CLASSE DANS UN FICHIER DANS LE NOM EST EN PARAMÈTRE ///
/// ////////////////////////////////////////////////////////////////////////// ///

void Perso::readFile(const std::string& path)
{
    std::ifstream ifs(path.c_str());

    if (ifs)
    {
        ifs.read((char*)this, sizeof(*this));

        std::cout << "Reading " << path << " => OK" << std::endl;

        ifs.close();
    }

    else
        std::cout << "Cannot read " << path << std::endl;
}




/// On pourrait enregistrer chaque classe dans un fichier différent portant le nom du joueur.
/// Comme ça quand on se connecte, on recherche le nom du fichier suivant le nom du joueur
/// Si on le trouve on récupère, sinon on en créé un nouveau.

/// Sinon avec un seul fichier
/// On peut lire l'ensemble du fichier (tant qu'on est pas à la fin on ajoute un compte dans un vecteur.
