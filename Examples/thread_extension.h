#ifndef _THREAD_EXTENSION_H_
#define _THREAD_EXTENSION_H_
#include <thread>

namespace thread
{
    /* Pour un thread donné, donne l'ensemble des processeurs logiques sur lequel on
       lui permet de s'exécuter. mask est un entier décrivant les processeurs logiques permis
       de la manière suivante : Si le ième bit (en représentation binaire) de mask est égal à 1,
       alors le thread peut s'éxécuter sur ce processeur logique, sinon il ne peut pas.

       Par exemple, si mask = (1<<2), on oblige le thread a être sur le processeur logique n°2
                    si mask = (1<<6), on oblige le thread a être sur le processeur logique n°6
                et  si mask = (1<<2) + (1<<6), le thread peut être sur les processeurs logiques n° 2 ou 6
        (Rappel : 1<<n est équivalent à écrire 2^n (2 exposant n) )
    */
    void set_affinity(std::thread::native_handle_type th, std::uint32_t mask);
    void set_current_affinity(std::uint32_t mask);
    void set_current_name(const char* thread_name);
    /* Retourne le numéro du processeur logique sur lequel s'éxécute le thread */
    int get_cpu();
}

#endif