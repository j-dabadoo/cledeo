#include <Perso.h>

///https://codes-sources.commentcamarche.net/faq/1190-sauvegarde-binaire-d-un-objet-c
/*
void readFile(const std::string& path)
{
    std::ifstream ifs(path.c_str());
    if (ifs) // test si le fichier est bien ouvert
    {
        std::string line;
        while (std::getline(ifs, line)) // lecture ligne par ligne
        {
            std::cout << line << std::endl;
        }
        std::cout << "Reading " << path << " => OK" << std::endl;
        ifs.close(); // fermeture du flux
    }
    else // en cas d'erreur...
    {
        std::cout << "Cannot read " << path << std::endl;
    }
}

void writeFile(const std::string& path)
{
    // Ouverture fichier en mode "w"
    // pour le mode append, utiliser std::ios::app
    std::ofstream ofs(path.c_str(), std::ios::out);
    if (ofs)
    {
        // Ecriture dans le fichier
        float flottant = 123.456;
        ofs << "Coucou je suis une phrase" << std::endl;
        ofs << 50 << std::endl;
        ofs << flottant <<std::endl;
        ofs.close(); // fermeture du flux
    }
}*/
void ecriture(Perso& perso, Perso& perso2)
{
    std::ofstream ofs("azert", std::ios::binary);

    if(ofs){
            std::cout<<"ouverture reussie"<<std::endl;
    ofs.write((char*)&perso,sizeof(Perso));
    //ofs<<&perso ;
    //ofs.write((char*)&perso2,sizeof(Perso));
    ofs.close();}
}

void lecture(Perso& perso, Perso& perso2)
{
    std::ifstream ifs("azert");
    std::string nom ;
    int age ;
    int taille ;

    if(ifs){
        std::cout<<"ouverture reussie"<<std::endl;
        ifs.read((char*)&perso, sizeof(Perso));
//        ifs>>perso;
    //ifs.read((char*)&perso2, sizeof(Perso));
    ifs.close();}
}

void ecriture(int test)
{
    std::ofstream ofs("new", std::ios::binary);

    ofs.write((char*)&test,sizeof(int));
    //ofs.write((char*)&perso2,sizeof(Perso));
    ofs.close(); // fermeture du flux
}

void lecture(int & test)
{
    std::ifstream ifs("new");

    ifs.read((char*)&test, sizeof(int));
    //ifs.read((char*)&perso2, sizeof(Perso));
    ifs.close();
}

int main()
{
    Perso *alex=new Perso(), *recupAlex=new Perso(), *jade=new Perso(), *recupJade=new Perso(), ariane, recupAriane ;
    //std::vector<int> myvec;
    int test =9 ;
    int recupTest=0 ;

    //Vecteur qiu est sauvegardé dansles structures pour voir si ça marchait aussi (oui)
    /*myvec.push_back(5);
    myvec.push_back(6);
    myvec.push_back(7);
    myvec.push_back(8);
    myvec.push_back(9);*/

    alex->setNom("alex");
    alex->setAge(72);
    alex->setTaille(2.83);
    //alex.setVec(myvec);
std::cout<<"test" ;
    jade->setNom("jade");
    jade->setAge(48);
    jade->setTaille(3.17);

    ariane.setNom("ariane");
    ariane.setAge(3);
    ariane.setTaille(3.17);


    //alex->writeFile("nouveau");
    //recupAlex->readFile("nouveau");


    ecriture(*alex,*jade);
    lecture(*recupAlex,*recupJade);

    //ecriture(test) ;
    //lecture(recupTest);

    //std::cout<<"res : "<<recupTest<<std::endl;
    recupAlex->display();
    recupJade->display();
    //recupJade.display();

    delete alex ;

    return 0;
}
