#!/bin/bash

echo "   _____ _                 _        ____                                     _____                          "
echo "  / ____(_)               | |      |  _ \                                   / ____|                         "
echo " | (___  _ _ __ ___  _ __ | | ___  | |_) |_ __ _____      _____  ___ _ __  | (___   ___ _ ____   _____ _ __ "
echo "  \___ \| | '_ \` _ \| '_ \| |/ _ \ |  _ <| '__/ _ \ \ /\ / / __|/ _ \ '__|  \___ \ / _ \ '__\ \ / / _ \ '__|"
echo "  ____) | | | | | | | |_) | |  __/ | |_) | | | (_) \ V  V /\__ \  __/ |     ____) |  __/ |   \ V /  __/ |   "
echo " |_____/|_|_| |_| |_| .__/|_|\___| |____/|_|  \___/ \_/\_/ |___/\___|_|    |_____/ \___|_|    \_/ \___|_|   "
echo "                    | |                                                                                     "
echo "                    |_|                                                                                     "

# Vérifier si Python est installé
if ! command -v python3 &> /dev/null
then
    echo
    echo "Error: Python not installed"
    echo -e "[ \e[31mERROR\e[0m ] Python isn't installed"
    exit 1
fi

echo -e "[ \e[32mOK\e[0m ] Python is installed"

# Vérifier si pip est installé
if ! command -v pip3 &> /dev/null
then
    echo
    echo "Installation de pip..."
    curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    python get-pip.py
    if [ $? -ne 0 ]; then
        echo "Échec de l'installation de pip."
        exit 1
    fi
    echo "Pip installé avec succès."
fi

# Vérifier les bibliothèques
libraries=("requests" "beautifulsoup4" "json" "sqlite3" "colorama")

for library in "${libraries[@]}"
do
    python3 -c "import $library" &> /dev/null
    if [ $? -ne 0 ]; then
        echo "La bibliothèque $library n'est pas installée. Installation..."
        pip3 install "$library"
        if [ $? -ne 0 ]; then
            echo "Échec de l'installation de $library."
        else
            echo "$library installée avec succès."
        fi
    else
        echo "La bibliothèque $library est déjà installée."
    fi
done

./simple_server
