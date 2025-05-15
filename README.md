# catan
CS246 (Spring 2023) group project by
- Aiden Li
- Frances Wang
- Yi Bo Cheng

A C++ implementation of Catan including gameplay mechanics, including resource management, building structures (roads, settlements, cities), and trading. It also includes functionality for saving and loading game states, generating random boards, and displaying the board layout.


Commands:
- Compile using `make`
- Run the game using `./constructor`
  - Optional:
    - Load saved game: `./constructor -load savefile.txt`
    - Load specific board layout: `./constructor -board board.txt`
    - Generate a random board: `./constructor -random-board`
- Clean the build: `make clean`
