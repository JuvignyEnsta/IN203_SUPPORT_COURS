#include <thread>
#include <iostream>

void compteur_periodique( const int& nb_secondes_max, int& secondes )
{
    for ( int i = 0; i < nb_secondes_max; ++i )
    {
        secondes = i;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    int nb_secondes_max = 20;
    int secondes;

    std::thread t(compteur_periodique, std::cref(nb_secondes_max), std::ref(secondes));

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Il s'est ecoule " << secondes << " secondes" << std::flush << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(7));
    std::cout << "Il s'est ecoule " << secondes << " secondes" << std::flush << std::endl;

    t.join();
    std::cout << "Il s'est ecoule " << secondes << " secondes" << std::flush << std::endl;

    return EXIT_SUCCESS;    
}