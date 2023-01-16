#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person {
private:
	string name;
	string password;
	int voteCount = 0;
	bool canGiveElectionVote = true;
	bool canVote = true;
	bool isDictator;

public:
	Person();
	Person(string indexNumber);
	Person(string password, string name);

	void setName(string name);
	string getName();

	void setPassword(string password);
	string getPassword();

	int getVoteCount();
	void increaseVoteCount();
	void refreshVoteCount();

	bool getCanGiveElectionVote();
	void toggleCanGiveElectionVote();
	void refreshCanGiveElectionVote();

	bool getCanVote();
	void setCanVoteFalse();
	void setCanVoteTrue();

	bool getIsDictator();
	void setIsDictatorTrue();
	void setIsDictatorFalse();
};