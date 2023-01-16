#include <iostream>
#include <string>
#include "person.h"

using namespace std;

	Person::Person() {
		this->name = "admin";
		this->password = "admin";
		this->isDictator = false;
	}
	Person::Person(string indexNumber) {
		this->name = "admin" + indexNumber;
		this->password = "admin" + indexNumber;
		this->isDictator = false;
	}
	Person::Person(string password, string name) {
		this->name = name;
		this->password = password;
		this->isDictator = false;
	}
	void Person::setName(string name) {
		this->name = name;
	}
	string Person::getName() {
		return this->name;
	}
	void Person::setPassword(string password) {
		this->password = password;
	}
	string Person::getPassword() {
		return this->password;
	}
	int Person::getVoteCount() {
		return voteCount;
	}
	void Person::increaseVoteCount() {
		voteCount++;
	}
	void Person::refreshVoteCount() {
		voteCount = 0;
	}
	bool Person::getCanGiveElectionVote() {
		return this->canGiveElectionVote;
	}
	void Person::toggleCanGiveElectionVote() {
		this->canGiveElectionVote = !canGiveElectionVote;
	}
	void Person::refreshCanGiveElectionVote() {
		this->canGiveElectionVote = true;
	}
	bool Person::getCanVote() {
		return this->canVote;
	}
	void Person::setCanVoteFalse() {
		this->canVote = false;
	}
	void Person::setCanVoteTrue() {
		this->canVote = true;
	}
	bool Person::getIsDictator() {
		return this->isDictator;
	}
	void Person::setIsDictatorTrue() {
		this->isDictator = true;
	}
	void Person::setIsDictatorFalse() {
		this->isDictator = false;
	}
