# Proposal: [PROPOSAL TODO: SALESMAN]

## Synopsis
In this game, the player attempts to find the shortest loop around 
some number, n, of points. 
    ie the Travelling Salesman Problem
    The player clicks a city to add it to the path (right click to undo)

The game starts with the trivial case (n=3), and then adds more points as the 
player successfully finds paths. 
    The game will calculate, by brute force, the actual shortest path
    I may also implement the nearest neighbor algorithm for comparison purposes
    The game will also keep track of the amount of time that it takes the player 
    to find the path and the amount of time that it takes the algorithm
    
The brute force solution of a TSP is O(n!), so I'm thinking the game should stop
(or just disable brute force and continue with nearest neighbor) around level 10 
(if a human can get that far anyway)

[PROPOSAL TODO]

## Functional requirements
1. Randomly generate n "cities" (must not be too close together)
2. Allow player to left click a city to add it to the path
3. Allow player to remove a city by left clicking
4. Draw the path made by the player live
5. Indicate which city was last added (line from this city to the mouse position)
6. Calculate the player's path distance
7. Calculate the distance of the shortest loop
8. Display the shortest loop when asked to do so
9. Time the brute force calculation
10. If player does not have right path, 
11. Keep a running timer for the player
12. Check if the player's loop is complete
13. Do not allow the player to visit same city twice
14. Allow player to go back to starting city only when all other cities have been visited
15. Allow player to advance to next level if player has found correct path
16. If player completes an incorrect loop, show the shortest distance, offer to show the right path, and make the player retry the level

[PROPOSAL TODO]

## Open questions
When will the game become too much for the computer to reasonably handle?
How do I know what should be public/private in model.hxx?

[PROPOSAL TODO]

