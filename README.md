# gpp_research

![image](https://user-images.githubusercontent.com/113976269/211598556-9f30304a-be7a-46b8-94c0-e175890fedd7.png)

## Summary

I made an AI that plays Connect 4 against a human player.

I use the MiniMax Algorithm and alpha-beta pruning.

The difficulty can be set in code between 0 and 6.

If you use a bigger number like 4, it will take a long time to calculate all options that's why I put alpha-beta pruning in it.
This made the AI much faster, and now I can use levels 5-6 too.


## Algorithm

### MiniMax

The MiniMax algorithm is a widely used AI algorithm in games where two players take turns. 

The algorithm needs a heuristic to score the current state of the game. It then tries to maximize the score of its own move, while minimizing the score of the opponents' turn, hence the name "MiniMax".

In this game, I built the heuristic so that win or lose were rewarded with 1,000,000 and -1,000,000 points respectively. Non-final board states get lower scores for two or three discs of the same color in a row. On top of that, a few points are added for discs in the center column, because it is a known fact that the center column gives a better chance to win the game. 


![image](https://user-images.githubusercontent.com/113976269/211523256-7f87164a-fe8d-4bc4-8cfb-025dda3f8a1b.png)


### Alpha Beta Pruning

If the Ai has to calculate every possible move from both players and give that a score, then it is expectable that it will take a long time if we go a few levels deeper.

That's where the alpha-beta pruning comes in.

Alpha-beta pruning is a simple concept where we just cut off branches from the option tree as soon as it is clear that further exploration of the tree will not give better or worse results.


![image](https://user-images.githubusercontent.com/113976269/211522917-a6725867-7378-4078-9923-908312b47723.png)


## Solution structure

I made my algorithm in Connect4_AI.

I split the code for UI and AI over different projects so that the AI logic would be reusable with another (Graphical) UI.

In the Connect4_Console, you can find everything for the Ui. It is a basic Ui in the console.

In the Connect4_Test, you can find unit tests.

It was the first time I used unit tests.
I had to find out first how it worked, but the moment I could use it, everything was more clear and easier to implement.
I could test every function I wrote, so I knew my algorithm worked before making the UI.

It was a new experience, and I'm happy I have put some time into it.



## Sources
### Links
https://medium.com/analytics-vidhya/artificial-intelligence-at-play-connect-four-minimax-algorithm-explained-3b5fc32e4a4f

### videos
https://www.youtube.com/watch?v=KU9Ch59-4vw&t=8s

https://www.youtube.com/watch?v=Sim2mJDZ5Ec


