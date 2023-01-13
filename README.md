# VotingDay

This project was given in a lecture at the university. It was requested to make a console-based platform using C++.

-> Each user can use a username and a password to login to the platform.

-> Each platform have a "constitution", a string which can only be changed through accepted proposal. 

-> The constitution is just a symbolic text and does not affect the mechanics of platform. 

-> Each user is allowed to create a new proposal to be voted. The proposals that can be created by a user falls into two categories:

	-> Proposals that change the constitution

	-> Proposals that change the voting mechanics

-> When a proposal is accepted by the majority of a group the suggested changes take place automatically

-> The platform allow the 3 following voting mechanisms. The active voting mechanisms effect who can vote for the proposals 

	-> Direct democracy: All members have the right to vote

	-> Representative democracy: Half of the users have the right to vote (Triggers election)

	-> Dictatorship: Only a single user have the right to vote (Triggers election)


-> Changing the voting mechanics to either dictatorship or representative democracy should trigger an election where the users vote for whom they want as representative or dictator.

-> While there is an active election, no other proposals can be voted 

-> All members able to view the current constitution via console

-> All members able to view all proposal still open to vote, even if they do not have the right to vote

-> The current status of the vote (number of people who voted yes and no) not be visible by the members until the vote is concluded.
