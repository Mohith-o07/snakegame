**Snake Game using C++**

This is a simple console-based Snake Game implemented in C++. The game allows the player to control a snake, represented by the character 'O', with the objective of eating fruits ('F') while avoiding collisions with the walls and the snake's own tail.

### Instructions:

1. **Compilation:**
   - The code is written in C++ and can be compiled using a C++ compiler (e.g., g++ for Linux, MinGW for Windows).
   - Ensure that the necessary header files and libraries are available.

2. **Controls:**
   - Use the following keys to control the snake:
     - 'W' or 'w': Move Up
     - 'S' or 's': Move Down
     - 'A' or 'a': Move Left
     - 'D' or 'd': Move Right
     - 'M' or 'm': Quit the game

3. **Game Rules:**
   - The snake should not collide with the walls or its own tail.
   - Eating a fruit increases the score by 10 points.
   - The game speed increases as the player's score reaches certain milestones.

4. **High Score:**
   - The game maintains a high score, which is stored in the "scores.txt" file.
   - If a player sets a new high score, they are prompted to enter their name.

### How to Play:

1. **Run the Game:**
   - Compile and run the source code.
   - The game will display instructions and rules on the console.

2. **Playing the Game:**
   - Control the snake using the specified keys.
   - Eat fruits to increase your score.
   - Avoid collisions with walls and your own tail.

3. **Game Over:**
   - The game ends when the snake collides with the walls or its own tail.
   - The final score is displayed along with the high score.

4. **Restart or Quit:**
   - After each game, you can choose to play again or quit.
   - Type "yes" to play again or "no" to exit.

### Notes:

- The game uses the console for input and output.
- The code utilizes C++ features such as file handling, random number generation, and basic input/output operations.
- Make sure to set up the development environment with the necessary dependencies before compiling the code.
