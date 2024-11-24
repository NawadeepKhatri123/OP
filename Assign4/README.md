Conway's Game of Life in C++

Description

    This program implements Conway's Game of Life using the NCurses library for a text-based graphical interface. Users can interact with a grid where cells can be either alive (represented by "X") or dead (represented by "."). The simulation updates the grid according to the rules of the Game of Life, allowing users to create initial configurations by clicking on the grid.
    
Key Features:

    Interactive Grid: Users can toggle the state of any cell in the grid (alive or dead) by left-clicking.

    Simulation: The Game of Life runs after users click 'n' to start the simulation. 

    Exit & Statistics: Press 'q' to quit the program. When exiting, the program will display the minimum and maximum coordinates of the cells that were clicked, along with a list of those coordinates.

Installation

Installing NCurses on Ubuntu/Debian:
To install the required NCurses libraries, run the following command:


Copy code

    sudo apt-get install libncurses5-dev libncursesw5-dev

Compilation
Once NCurses is installed, compile the program using g++:

    g++ -o curses curses.cpp -lncurses

Running the Program

    ./curses

Controls
Left Click: Toggle the state of the clicked cell (alive/dead).
Press 'n': Start the Game of Life simulation.
Press 'q': Exit the program.

