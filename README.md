# gpp_research

## Summary

I made an AI that plays Connect4 against a human player.

I use the MiniMax Algorithm and alpha-beta pruning.

The difficulty can be set in code between 0 and 6.

If you use a bigger number like 4, it will take a long time to calculate all options that's why I put alpha-beta pruning in it.
This made my Ai much faster, and now I can use levels 5-6 too.

## Algorithm

### MiniMax

With the MiniMax algorithm, the AI can see which option is best.
What is the MiniMax algorithm?

It is a recursive algorithm that calculates a score for one player its makes a score as high as possible( maximum).
For the other one, it is as low as possible( minimum).
The Ai does this by giving some moves a score.
You get more points if you can put 2 or 3 dices next to each other.
You get minus points if the enemy can have a 4 in a row.
You get many points if you can have a 4 in a row.
That is the base of the algorithm.
![image](https://user-images.githubusercontent.com/113976269/211523256-7f87164a-fe8d-4bc4-8cfb-025dda3f8a1b.png)


### Alpha Beta Pruning

But if the Ai has to Calculate every possible move from both players and give that a score, then it is more than normal that it would take a long time if we go a few steps deeper.
That's where the alpha-beta pruning comes in.
Alpha-beta pruning is a simple concept where we just cut off branches from the option tree.
If we see that we can win or block the enemy with a few moves, we don't have to calculate other options anymore. It would only take more time for the same result.
![image](https://user-images.githubusercontent.com/113976269/211522917-a6725867-7378-4078-9923-908312b47723.png)


## Solution structure

I made my algorithm in Connect4_Ai.

I made my algorithm in a different solution so that I can use it with different UIs.


In the Connect4_Console, you can find everything for the Ui.

It is a basic Ui in the console.

In the Connect4_Test, you can find unit tests.

It was the first time I used unit tests.
I had to find out first how it worked, but the moment I could use it. Everything was more clear and easier to implement.
I could test every function I wrote, so I knew my algorithm worked before making an Ui.

It was a new experience, but I'm happy I put some time into it.



## Sources
### Links
https://medium.com/analytics-vidhya/artificial-intelligence-at-play-connect-four-minimax-algorithm-explained-3b5fc32e4a4f

### videos
https://www.youtube.com/watch?v=KU9Ch59-4vw&t=8s

https://www.youtube.com/watch?v=Sim2mJDZ5Ec


