#include <thread>
#include <iostream>

void affichage_periodique(int id, int n)
{
    for ( int i = n; i >= 0; --i )
    {
        // On affiche un message toutes les secondes.
        std::cout << "Hello world from t" << id << " countdown " << i << std::flush << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Farewell from t" << id << std::flush << std::endl;
}

void thread_launcher()
{
    std::cout << "Welcome from thread_launcher" << std::flush << std::endl;
    std::cout << "t1 => thread joignable, t2 => thread detache !" << std::flush << std::endl;
    std::thread t1(affichage_periodique, 1,  5);
    std::thread t2(affichage_periodique, 2, 35);
    // On detache t2 dont la durée de vie ne dépend plus de thread_launcher
    t2.detach();
    // On attend que t1 ait fini pour quitter thread_launcher sous peine d'une exception de type system_error !
    t1.join();
    std::cout << "Farewell from thread_launcher" << std::flush << std::endl;
}

int main() 
{
    std::cout << "Hello world de main" << std::flush << std::endl;
    // Exécution de lanceur de thread en thread !(on pourrait l'appeler aussi de façon classique)
    std::thread t(thread_launcher);

    // On attend la fin du thread thread_launcher
    t.join();
    // Puis on attend une dizaine de seconde que t2 continue à faire une partie de son travail
    std::this_thread::sleep_for(std::chrono::seconds(10));
    // Avant de dire adieu et de quitter le programme, ce qui aurai pour effet de tuer t2 !
    std::cout << "Farewell from main" << std::flush << std::endl;
    return 0;
}
