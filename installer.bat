@echo off
echo "   _____ _                 _        ____                                     _____                          ";
echo "  / ____(_)               | |      |  _ \                                   / ____|                         ";
echo " | (___  _ _ __ ___  _ __ | | ___  | |_) |_ __ _____      _____  ___ _ __  | (___   ___ _ ____   _____ _ __ ";
echo "  \___ \| | '_ \` _ \| '_ \| |/ _ \ |  _ <| '__/ _ \ \ /\ / / __|/ _ \ '__|  \___ \ / _ \ '__\ \ / / _ \ '__|";
echo "  ____) | | | | | | | |_) | |  __/ | |_) | | | (_) \ V  V /\__ \  __/ |     ____) |  __/ |   \ V /  __/ |   ";
echo " |_____/|_|_| |_| |_| .__/|_|\___| |____/|_|  \___/ \_/\_/ |___/\___|_|    |_____/ \___|_|    \_/ \___|_|   ";
echo "                    | |                                                                                     ";
echo "                    |_|                                                                                     ";

:: Vérifier si Python est installé
python --version 2>NUL
if errorlevel 1 goto errorNoPython

echo [ [32mOK[0m ] Python is installed

:: Vérifier si pip est installé
pip --version 2>NUL
if errorlevel 1 goto installPip

:: Vérifier les bibliothèques
set libraries=requests beautifulsoup4 json sqlite3 colorama

for %%i in (%libraries%) do (
    python -c "import %%i" >nul 2>&1
    if errorlevel 1 (
        echo La bibliothèque %%i n'est pas installée. Installation...
        pip install %%i
        if errorlevel 1 (
            echo Échec de l'installation de %%i.
        ) else (
            echo %%i installée avec succès.
        )
    ) else (
        echo La bibliothèque %%i est déjà installée.
    )
)

./build/windows/x64/release/simple_server.exe
python crawler.py

goto :eof

:installPip
echo.
echo Installation de pip...
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python get-pip.py
if errorlevel 1 (
    echo Échec de l'installation de pip.
    exit /b
)
echo Pip installé avec succès.
goto :eof

:errorNoPython
echo.
echo Error^: Python not installed
echo [ [31mERROR[0m ] Python isn^'t installed
exit /b
