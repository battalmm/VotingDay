#pragma once
#include <iostream>
#include <string>
#include "person.h"

using namespace std;

class Proposal {
private:
	int numberOfPeople;
	int yesCount;
	int noCount;
	string proposal;
	Person* personList;
	bool isAboutMechanic;

public:
	Proposal();
	Proposal(string proposal, Person* personList, int numberOfPeople);
	Proposal(string proposal, Person* personList, int numberOfPeople, bool isAboutMechanic);

	void increaseYesCount(Person whoVotes);
	void increaseNoCount(Person whoVotes);
	void voteForMechanics(Person whoVotes);

	string getProposal();
	Person* getPersonList();
	bool getIsAboutMechanic();
	int getYesCount();
	int getNoCount();
};
