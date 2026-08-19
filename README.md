TravelTown

A city-builder game themed around Travel & Sport, built in C++17 with SFML 3.

Concept

TravelTown is a simplified city-builder where the player constructs an international sports tourism resort. The goal: attract visitors, build sports facilities, manage finances, and grow your population.

Every building is themed around travel and sport:

Lodging: Youth hostel, sport hotel, campsite
Sport: Stadium, ski slope, climbing wall, velodrome
Transport: Regional airport, central station, marina

The visual direction is inspired by vintage travel maps and airport departure boards: beige parchment tones, ocean blue, mountain grey, gold accents.

Gameplay
Select a building from the right sidebar
Click on the grid to place it (if you have enough money)
Buildings attract visitors and generate daily tax income
Each building has a daily upkeep cost -- balance your budget
Attractiveness propagates around buildings via BFS algorithm
Population grows when housing is available and satisfaction is high
Save and reload your city at any time
Controls
Action	Control
Select a building	Left click on the sidebar
Place a building	Left click on the grid
Save the game	Click Save button
Load the game	Click Load button
Close the game	Window close button
Tech Stack
Technology	Role
C++17	Main language
SFML 3.0.2	Window, rendering, input events
nlohmann/json	Save/load JSON serialization
CMake 3.16+	Build system
doctest	Unit testing (header-only)
Architecture
TravelTown/
├── assets/
│   ├── data/
│   │   └── buildings.json     <- Building catalog (costs, types, stats)
│   └── fonts/
│       └── arial.ttf
├── include/
│   ├── buildings/
│   │   ├── Building.hpp       <- Abstract base class
│   │   ├── Lodging.hpp        <- Housing subclass
│   │   ├── SportFacility.hpp  <- Sport subclass
│   │   └── Transport.hpp      <- Transport subclass
│   ├── core/
│   │   ├── AttractivenessSystem.hpp  <- BFS diffusion
│   │   ├── BuildingCatalog.hpp       <- JSON loader + Factory
│   │   ├── EventSystem.hpp           <- Random events
│   │   ├── Grid.hpp                  <- 2D tile matrix
│   │   ├── InputHandler.hpp          <- Mouse to grid conversion
│   │   └── Tile.hpp                  <- Single grid cell
│   ├── economy/
│   │   ├── GameClock.hpp       <- Day simulation
│   │   ├── ResourceManager.hpp <- Energy, equipment
│   │   ├── TaxSystem.hpp       <- Daily tax income
│   │   ├── Treasury.hpp        <- Player money
│   │   └── UpkeepSystem.hpp    <- Building maintenance
│   ├── persistence/
│   │   └── SaveManager.hpp     <- JSON save/load
│   ├── population/
│   │   ├── Citizen.hpp           <- Individual inhabitant
│   │   ├── CitizenSorter.hpp     <- std::sort utilities
│   │   └── PopulationManager.hpp <- Growth logic
│   └── ui/
│       ├── BuildMenu.hpp        <- Right sidebar
│       ├── Button.hpp           <- Reusable UI component
│       ├── GridRenderer.hpp     <- Grid drawing
│       ├── HUD.hpp              <- Info bar at top
│       └── StatsDashboard.hpp   <- 30-day chart
├── src/
│   └── main.cpp               <- Entry point, game loop
├── tests/
│   ├── doctest.h
│   ├── test_grid.cpp
│   └── test_treasury.cpp
└── CMakeLists.txt
Class hierarchy
Building  (abstract)
├── Lodging         -> capacity (housing for visitors)
├── SportFacility   -> prestige (attractiveness boost)
└── Transport       -> visitorFlow (unlocks visitor arrivals)
Key Technical Concepts
Object-Oriented Programming

Building is an abstract class with pure virtual methods. Each subclass (Lodging, SportFacility, Transport) overrides them with override keyword. dynamic_cast is used in PopulationManager to safely downcast Building* to Lodging*.

BFS Attractiveness Diffusion

When a building is placed, its attractiveness propagates to neighboring tiles using Breadth-First Search:

A std::queue processes tiles ring by ring around the building
Attractiveness decreases by 1 per tile of distance
A visited grid prevents processing tiles twice
Complexity: O(strength squared) per building
Data Structures
Structure	Usage
vector<vector<Tile>>	2D grid
shared_ptr<Building>	Automatic memory management
unordered_map<string, int>	Resource stocks O(1) access
queue<tuple<int,int,int>>	BFS traversal
vector<Citizen>	Population list
function<void(int)>	Day callback in GameClock
File I/O and Serialization
buildings.json: external building catalog (add new buildings without recompiling)
save.json: full game state serialization (grid, treasury, resources, population)
Factory Method pattern in BuildingCatalog::createBuilding() reconstructs objects from name strings
Unit Testing

Treasury and Grid are tested with doctest independently of SFML, proving clean separation between business logic and rendering.

Build Instructions
Prerequisites (Windows + MSYS2)
Install MSYS2 from https://www.msys2.org/
Open MSYS2 MINGW64 terminal and run:
bash
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-sfml
pacman -S mingw-w64-x86_64-nlohmann-json
Add C:\msys64\mingw64\bin to your Windows PATH
Build
bash
git clone https://github.com/YOUR_USERNAME/TravelTown.git
cd TravelTown
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
./TravelTown.exe
Run unit tests
bash
cd build
mingw32-make
./TravelTown_Tests.exe
VS Code setup

Install extensions: C/C++, CMake Tools, CMake (twxs)

In VS Code:

Ctrl+Shift+P > CMake: Select a Kit > GCC MINGW64
Ctrl+Shift+P > CMake: Build (or F7)
Ctrl+Shift+P > CMake: Run Without Debugging (or Shift+F5)
Save File Format
json
{
    "version": "1.0",
    "dayCount": 42,
    "balance": 7350,
    "population": 18,
    "resources": {
        "energy": 100,
        "equipment": 50
    },
    "buildings": [
        { "x": 3, "y": 5, "name": "Youth hostel" },
        { "x": 7, "y": 2, "name": "Municipal stadium" },
        { "x": 12, "y": 8, "name": "Regional airport" }
    ]
}
Building Catalog
Name	Type	Cost	Upkeep	Stat
Youth hostel	Lodging	500	20/day	30 capacity
Sport hotel and spa	Lodging	1500	60/day	80 capacity
Nature campsite	Lodging	200	8/day	50 capacity
Municipal stadium	Sport	2000	80/day	50 prestige
Ski slope	Sport	3500	120/day	80 prestige
Climbing wall	Sport	800	30/day	25 prestige
Velodrome	Sport	1200	45/day	35 prestige
Regional airport	Transport	5000	200/day	100 visitor flow
Central station	Transport	3000	100/day	60 visitor flow
Marina	Transport	2500	80/day	40 visitor flow
Random Events
Event	Effect
Regional Olympics	+5000, x2.0 tourism for 7 days
Transport strike	-1000, x0.5 tourism for 3 days
Extreme sports fest	+2000, x1.5 tourism for 5 days
Snowstorm	-800, x0.7 tourism for 2 days
Cycling championship	+3000, x1.8 tourism for 4 days
Development

This project was built over 6 weeks following an issue-driven workflow:

32 GitHub issues, each on its own branch
Pull requests with Closes #N to track progress
Conventional Commits format (feat, fix, refactor, docs, test, chore)
Unit tests for core business logic decoupled from SFML
Author

Marino Chereau (Zacken) Bachelor Developpeur Web -- CEF Montpellier

Built with C++17 and SFML 3 -- Travel far, train hard.