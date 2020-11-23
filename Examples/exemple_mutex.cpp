#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>
 
std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

// Fonction censer sauver une page html accessible par une adresse internet. 
void save_page(const std::string &url)
{
    // On simule un temps long pour l'obtention d'une page internet
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";
 
    // On a rajouté un mutex pour empêcher les threads de rajouter en même
    // temps un élément au dictionnaire.
    g_pages_mutex.lock();
    g_pages[url] = result;
    g_pages_mutex.unlock();
}
 
int main() 
{
    std::thread t1(save_page, "http://foo");
    std::thread t2(save_page, "http://bar");
    t1.join();
    t2.join();

    // Pas besoin de protéger ici, puisque les threads ont terminé
    // leur travail. 
    for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}
