# Unbeatable-Ai---Tic-Tac-Toe
This Tic Tac Toe game features an invincible AI player that uses the Minimax algorithm and smart heuristics to analyze all possible moves and never lose. The animated GUI offers a smooth interface to play against the impossible-to-beat opponent.


## Unbeatable Tic Tac Toe
This Tic Tac Toe game features an AI opponent that is impossible to beat! The AI player leverages the Minimax algorithm to analyze all possible game outcomes and always make the optimal move.

Features
Invincible AI using Minimax and heuristic scoring
GUI gameboard built with Tkinter
Ability to play as X or O against the AI
Configurable gameboard size (3x3, 4x4, 5x5)
Animated graphics for placing pieces and game end
Implementation
The AI player uses the Minimax algorithm with depth-limited searching and heuristic board evaluation to determine the best possible moves. It calculates all possible finished game states from the current board position down to a configured depth. It then scores the end boards and propagates the scores back up the tree to determine which of its available moves produces the maximum score.

The GUI gameboard is built using Python's Tkinter module. Smooth animations are achieved by separating piece placement and board updates into threaded tasks.

The game logic is decoupled from the GUI code for easy maintainability and future expansion.

Try to beat the unstoppable AI (you won't succeed)!
