# BYOD IN203 : programmation parallèle
ENSTA Paris - édition 2020/21

## Installation des outils nécessaires aux TDs

### Linux/Debian 

    sudo apt install  build-essential make g++ gdb libopenmpi-dev

### Mac

Installer [homebrew](https://brew.sh) en suivant les instructions, puis :

    brew install gcc open-mpi
    brew update # MàJ

A mettre dans le *.bashrc* :

    export OMPI_CC=gcc-10
    export OMPI_CXX=g++-10

### Windows 10

Installation d'Ubuntu sous Windows 10 : allez sur [ce lien](https://www.numerama.com/tech/158150-le-shell-bash-sous-windows-10-ce-quil-faut-savoir.html) et suivez les instructions.

Tapez *bash* dans la barre de questionnement.
Une fois sous Linux :

    sudo apt update
    sudo apt install  build-essential make g++ gdb libopenmpi-dev 

### Windows 7 ou 8

Installer [msys 2](https://www.msys2.org/) en suivant les instructions.


Lancer le shell via *mingw64*

    pacman -Ss gcc  # donne le nom du package contenant gcc
    pacman -S mingw64/mingw-w64-x86_64-gcc   # install le package gcc avec le nom copié/collé précédent
    pacman -Syu # MàJ du système

Installer gcc, make

Pour MPI, installer MS-MPI en suivant [ce lien](https://www.microsoft.com/en-us/download/details.aspx?id=57467)

Dans .bashrc :

    export PATH=$PATH:"/c/Program Files/Microsoft MPI/Bin/"


Exemple de commande de compilation :

    g++ -o HelloWorld.exe HelloWorld.cpp -L/c/Program\ Files\ \(x86\)/Microsoft\ SDKs/MPI/Lib/x64 -I/c/Program\ Files\ \(x86\)/Microsoft\ SDKs/MPI/Include -lmsmpi

## Vérification de l'installation

Vous trouverez sur [ce lien](https://github.com/JuvignyEnsta/Installation_Test) un projet que vous pouvez télécharger afin de tester votre environnement. Les instructions pour installer ce projet
sont inclus dans le projet. Si tout se passe bien, le projet vous affichera des messages de bienvenues.
