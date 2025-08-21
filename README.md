Ukázkové miniaplikace v SFML 3.0.0 (CMake).
Repo obsahuje lokální kopii knihovny v ./SFML-3.0.0, takže není nutná systémová instalace.

Struktura
SFML-3.0.0/           # lokální SFML (používá se automaticky)
APP1/                 # 1) Hello okno (bílé pozadí)
APP2/                 # 2) Smyčka + dt + FPS + červený obdélník (wrap)
assets/               # sdílená data (fonty ap.)
build.bat             # Windows build skript
build.sh              # Linux/macOS build skript
CMakeLists.txt        # root CMake

**Požadavky**

CMake ≥ 3.20

Git

Windows: Visual Studio 2022 / Build Tools (MSVC x64)

Linux: GCC/Clang + make/ninja (balík build-essential)

**Spuštění (doporučené: skripty):**
_Windows_

Otevři kořen repa a dvakrát klikni na build.bat
(nebo v PowerShellu/CMD spusť build.bat)

Po dojetí buildu spusť programy:

build\bin\Release\APP1.exe
build\bin\Release\APP2.exe

_Linux / macOS_

Uděl skript spustitelný (jen poprvé):

chmod +x build.sh


Spusť build:

./build.sh


Spusť programy:

./build/bin/APP1
./build/bin/APP2


Skripty dělají: konfiguraci CMake, překlad, zkopírování DLL (Windows) a zkopírování assets do build/bin/assets.

**Alternativa: ručně přes CMake**
_Windows (MSVC)_
cmake -S . -B build
cmake --build build --config Release
build\bin\Release\APP1.exe
build\bin\Release\APP2.exe

_Linux_
cmake -S . -B build
cmake --build build
./build/bin/APP1
./build/bin/APP2

**Co aplikace dělají:**

APP1 – vytvoří bílé okno („SFML Cvičné okno“).

APP2 – zobrazuje HUD s dt a FPS a červený obdélník se pohybuje doprava; po opuštění pravého okraje se teleportuje mimo levý okraj.

**Užitečné:**

Build jen konkrétní appky:

Windows: cmake --build build --config Release --target APP2

Linux: cmake --build build --target APP2

**Čistý rebuild:**

Linux/macOS: rm -rf build

Windows (CMD): rmdir /S /Q build

**Troubleshooting:**

„Failed to load font“ – app hledá font v assets/fonts/.... Skripty kopírují assets do build/bin/assets. Spouštěj z build/bin (nebo měj assets po ruce).

Chybí sfml-*.dll (Windows) – spusť build skriptem znovu; kopírování DLL probíhá automaticky po překladu.

CMake nenašel SFML – ověř, že SFML-3.0.0/ je v kořeni repa a obsahuje lib/cmake/SFML/SFMLConfig.cmake.

**Poznámky k přenositelnosti:**

CMake je nastavený tak, aby bral SFML z ./SFML-3.0.0 (stejně na Windows i Linuxu).

Spustitelné soubory jdou do build/bin[/Release|Debug].

assets/ se kopírují do build/bin/assets.
