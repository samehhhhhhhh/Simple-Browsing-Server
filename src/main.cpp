#include "includes.hpp"
#include <iostream>
#include <string>
#include "processor.hpp"



int main() {

    processer process;

    // Boucle infini
    while(true) {
        system("python3 crawler.py");
        process.tf();
        
    }

    return 0;
}
