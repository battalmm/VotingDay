#include <iostream>
#include <string>
#include "person.h"
#include "proposal.h"

	Proposal::Proposal() {};
	Proposal::Proposal(string proposal, Person* personList, int numberOfPeople) {
		this->proposal = proposal;
		this->numberOfPeople = numberOfPeople;
		this->yesCount = 0;
		this->noCount = 0;

		Person* copyListFromPersonList;
		copyListFromPersonList = new Person[numberOfPeople];

		for (int index = 0; index < numberOfPeople; index++) {
			copyListFromPersonList[index] = personList[index];
		}
		this->personList = copyListFromPersonList;
	}
	Proposal::Proposal(string proposal, Person* personList, int numberOfPeople, bool isAboutMechanic) {
		this->proposal = proposal;
		this->numberOfPeople = numberOfPeople;
		this->yesCount = 0;
		this->noCount = 0;

		Person* copyListFromPersonList;
		copyListFromPersonList = new Person[numberOfPeople];

		for (int index = 0; index < numberOfPeople; index++) {
			copyListFromPersonList[index] = personList[index];
		}
		this->personList = copyListFromPersonList;
		this->isAboutMechanic = isAboutMechanic;
	}
	void Proposal::increaseYesCount(Person whoVotes) {
		for (int i = 0; i < numberOfPeople; i++) {
			if (personList[i].getName() == whoVotes.getName()) {
				for (int j = i; j < numberOfPeople - 1; j++)
				{
					personList[j] = personList[j + 1];
				}
				yesCount++;
				numberOfPeople--;
			}

		}

	}
	void Proposal::increaseNoCount(Person whoVotes) {
		for (int i = 0; i < numberOfPeople; i++) {
			if (personList[i].getName() == whoVotes.getName()) {
				for (int j = i; j < numberOfPeople - 1; j++)
				{
					personList[j] = personList[j + 1];
				}
				noCount++;
				if (i > 0) {
					i--;
				}
				else {
					i = 0;
				}
				numberOfPeople--;
			}
		}
	}
	void Proposal::voteForMechanics(Person whoVotes) {
		for (int i = 0; i < numberOfPeople; i++) {
			if (personList[i].getName() == whoVotes.getName()) {
				for (int j = i; j < numberOfPeople - 1; j++)
				{
					personList[j] = personList[j + 1];
				}

				if (i > 0) {
					i--;
				}
				else {
					i = 0;
				}
				numberOfPeople--;
			}
		}
	}
	string Proposal::getProposal() {
		return proposal;
	}
	Person* Proposal::getPersonList() {
		return this->personList;
	}
	bool Proposal::getIsAboutMechanic() {
		return this->isAboutMechanic;
	}
	int Proposal::getYesCount() {
		return this->yesCount;
	}
	int Proposal::getNoCount() {
		return this->noCount;
	}
