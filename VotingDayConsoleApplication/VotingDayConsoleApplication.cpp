#include <iostream>
#include <string>
#include <random>
#include "person.h"
#include "proposal.h"

using namespace std;

enum Regim { DirectDemocracy, RepresentativeDemocracy, Dictatorship };

void voteFunctionForDictator(int index, bool* regimProposalController, int* givenPorposalCount, Person* personList, Proposal* proposalList, int proposalListCount, string* constitution, int* maddeSayisi, Regim* regim, bool* isElectionOn, int numberOfPeople);
void createPerson(Person* personArray, int size);
void giveProposal(int index, Person* personList, int numOfPeople, bool* regimProposalController, Proposal* proposalList, int* proposalCount);
void voteFunctionDirectDemocracy(int index, bool* regimProposalController, int* givenPorposalCount, Person* personList, int numberOfPeople, Regim* regim, Proposal* proposalList, int proposalListCount, string* constitution, int* maddeSayisi, int* dictator, int* repres, int* direct, bool* isElectionOn);
void voteFunctionForRepresentetiveDemocracy(int index, int* givenPorposalCount, Person* personList, Proposal* proposalList, int proposalListCount, string* constitution, int* maddeSayisi, int numberOfPeople, int* dictator, int* repres, int* direct, Regim* regim, bool* isElectionOn, bool* regimProposalController);
void electionVote(Person* personList, int numberOfPeople, int peopleIndex, Regim regim, bool* isElectionOn);
void swap(Person* xp, Person* yp);
void bubbleSort(Person arr[], int n);
void deleteProposalFunction(Proposal* proposalList, int proposalListCount);

int main()
{
	string* constitution;
	constitution = new string[100];
	int maddeSayisi = 0;
	int numberOfPeople;
	Person* personList;

	cout << "How many people are there in the council: ";
	cin >> numberOfPeople;
	if (numberOfPeople < 4) {
		cout << "Number of people must be bigger than 3. Now, number of people will be set to 4 by default !!!" << endl;
		numberOfPeople = 4;
	}
	personList = new Person[numberOfPeople];
	createPerson(personList, numberOfPeople);
	Regim regim = DirectDemocracy;

	bool regimProposalController = false;
	bool isElectionOn = false;

	Proposal* proposalList;
	int proposalCount = 0;
	int proposalListCount = 15;
	proposalList = new Proposal[proposalListCount];

	int isRunning = 1;
	while (isRunning == 1) {
		bool regimProposalController = false;
		int dictatorVote = 0;
		int directDemocracyVote = 0;
		int representativeDemocracyVote = 0;
		int accountPanel = 1;
		while (accountPanel == 1) {
			int adminPanelLoginAnotherPersonController;
			string name;
			string password;
			cout << "Please log in with your name and password... \nName:  ";
			cin >> name;
			cin.ignore();
			cout << "Password: ";
			cin >> password;
			for (int index = 0; index < numberOfPeople; index++) {

				if (name == personList[index].getName() && password == personList[index].getPassword()) {
					int logginPanel = 1;
					while (logginPanel == 1) {
						int accountSettingsController;
						cout << "\n1. Change Name and Password\n" << "2. Constitution\n" << "3. Give Proposal\n" << "4. Vote Proposal \n" << "5. Election \n" << "6. Proposals \n" << "0. Logout" << endl;
						cin >> accountSettingsController;
						switch (accountSettingsController)
						{
						case 1:
							cout << "New Name: ";
							cin >> name;
							personList[index].setName(name);
							cout << "Successful. You can use your new name!\n";
							cout << "New Password: ";
							cin >> password;
							personList[index].setPassword(password);
							cout << "Successful. Your new password is ready to use!\n";
							break;
						case 2:
							cout << "Constitutions: " << "\n\n";
							for (int i = 0; i < 100; i++) {
								if (constitution[i].size() > 5) {
									cout << constitution[i] << endl;
								}
							}
							break;
						case 3:
							if (proposalCount < proposalListCount) {
								giveProposal(index, personList, numberOfPeople, &regimProposalController, proposalList, &proposalCount);
							}
							else {
								cout << "Proposal list limit has been reached. Please vote for active proposals to reduce congestion in the council." << endl;
							}
							break;
						case 4:
							if (isElectionOn == false) {
								switch (regim) {
								case DirectDemocracy:
									voteFunctionDirectDemocracy(index, &regimProposalController, &proposalCount, personList, numberOfPeople, &regim, proposalList, proposalListCount, constitution, &maddeSayisi, &dictatorVote, &representativeDemocracyVote, &directDemocracyVote, &isElectionOn);
									break;

								case Dictatorship:

									voteFunctionForDictator(index, &regimProposalController, &proposalCount, personList, proposalList, proposalListCount, constitution, &maddeSayisi, &regim, &isElectionOn, numberOfPeople);
									break;

								case RepresentativeDemocracy:

									voteFunctionForRepresentetiveDemocracy(index, &proposalCount, personList, proposalList, proposalListCount, constitution, &maddeSayisi, numberOfPeople, &dictatorVote, &representativeDemocracyVote, &directDemocracyVote, &regim, &isElectionOn, &regimProposalController);
									break;
								}
							}
							else {
								cout << "There is an election going on. Please attend the election." << endl;
							}

							break;
						case 5:

							if (isElectionOn == true) {
								electionVote(personList, numberOfPeople, index, regim, &isElectionOn);
							}
							else {
								cout << "There is no active election for now !!!" << endl;
							}

							break;
						case 6:
							for (int i = 0; i < proposalListCount; i++) {
								if (proposalList[i].getProposal() != "") {
									cout << i + 1 << "- " << "Proposal: " << proposalList[i].getProposal() << " | Yes Count: " << proposalList[i].getYesCount() << " | No Count: " << proposalList[i].getNoCount() << "\n" << endl;
								}

							}
							break;
						case 0:
							cout << "Logging out...\n";
							logginPanel = 0;
							break;
						default:
							cout << "You pressed wrong button. Choose wisely..:)\n";
							break;
						}
					}
				}
			}

			cout << "Chose your action: \n1 - Log in \n2 - Exit Program \n";
			cin >> adminPanelLoginAnotherPersonController;
			switch (adminPanelLoginAnotherPersonController) {
			case 1:
				break;
			case 2:
				accountPanel = 0;
				cout << "Exiting..." << endl;
				break;
			default:
				cout << "You pressed wrong button. You redirect to log in..." << endl;
				break;
			}
		}
		isRunning = 0;
	}
	return 0;
}

void createPerson(Person* personArray, int size) {
	string name;
	string password;
	int defaultOrNamedPersonController;

	for (int index = 0; index < size; index++) {
		cout << "For " << to_string(index + 1) << " Person Create Name and Password or Use default admin" << to_string(index + 1) << ", admin" << to_string(index + 1) << "\n1.Create \n2.Default\n";
		cin >> defaultOrNamedPersonController;
		if (defaultOrNamedPersonController == 1) {
			cout << index + 1 << ". Person Name: ";
			cin >> name;
			cout << index + 1 << ". Person Password: ";
			cin >> password;
			Person newPerson = Person(password, name);
			personArray[index] = newPerson;

		}
		else if (defaultOrNamedPersonController == 2) {
			Person newPerson = Person(to_string(index + 1));
			personArray[index] = newPerson;

		}
		else {
			Person newPerson = Person(to_string(index + 1));
			personArray[index] = newPerson;
		}
	}
}

void giveProposal(int index, Person* personList, int numOfPeople, bool* regimProposalController, Proposal* proposalList, int* proposalCount) {

	string proposal;
	int proposalController;
	cout << "Dear, " << personList[index].getName() << ",\nWhat would you like to present a proposal about? \n\n1- Constitution \n2- Voting Mechanics" << endl;
	cin >> proposalController;
	switch (proposalController) {
	case 1:
		cout << "What is your proposal?" << endl;
		cin >> proposal;

		proposalList[*proposalCount] = Proposal(proposal, personList, numOfPeople);
		*proposalCount = *proposalCount + 1;
		break;

	case 2:

		if (*regimProposalController == false) {
			cout << "Your proposal to change the voting mechanism system has been received. " << endl;
			proposal = "A proposal has been submitted to change the voting mechanism system.";

			proposalList[*proposalCount] = Proposal(proposal, personList, numOfPeople, true);
			*proposalCount = *proposalCount + 1;
			*regimProposalController = true;
		}
		else {
			cout << "There is already a proposal on changing the voting mechanism system. Check voting system!\n" << endl;
		}
		break;

	default:
		cout << "You pressed a wrong button. Please use available buttons! " << personList[index].getName() << endl;
		break;
	}

}

void voteFunctionDirectDemocracy(int index, bool* regimProposalController, int* givenPorposalCount, Person* personList, int numberOfPeople, Regim* regim, Proposal* proposalList, int proposalListCount, string* constitution, int* maddeSayisi, int* dictator, int* repres, int* direct, bool* isElectionOn) {

	string passwordController;

	cout << personList[index].getName() << ", \n Please, confirm your action with your password! \n password:";
	cin >> passwordController;

	for (int trial = 2; trial >= 0; trial--) {
		if (passwordController == personList[index].getPassword()) {

			cout << "Welcome, " << personList[index].getName() << "Which proposal you want to vote?\n" << endl;
			for (int i = 0; i < proposalListCount; i++) {

				if (proposalList[i].getProposal() != "") {
					for (int j = 0; j < numberOfPeople; j++) {

						if (proposalList[i].getPersonList()[j].getName() == personList[index].getName()) {

							cout << i + 1 << "- " << "Proposal: " << proposalList[i].getProposal() << " | Yes Count: " << proposalList[i].getYesCount() << " | No Count: " << proposalList[i].getNoCount() << "\n" << endl;

						}

					}

				}
			}


			int proposalIndex;
			cin >> proposalIndex;

			if (proposalIndex > 0 && proposalIndex < *givenPorposalCount + 1) {

				for (int j = 0; j < numberOfPeople; j++) {

					if ((proposalList[proposalIndex - 1].getProposal() != "")) {
						if (proposalList[proposalIndex - 1].getPersonList()[j].getName() == personList[index].getName()) {
							if (proposalList[proposalIndex - 1].getIsAboutMechanic() == true) {

								cout << "Please select the next system:\n1-Dictatorship\n2-DirectDemocracy\n3-RepresentativeDemocracy\n\n" << endl;

								int vote;
								cin >> vote;

								switch (vote)
								{
								case 1:
									*dictator = *dictator + 1;
									proposalList[proposalIndex - 1].voteForMechanics(personList[index]);
									if (*dictator > numberOfPeople / 3) {
										*regim = Dictatorship;
										*isElectionOn = true;
										//	PROPOSAL DELETING FROM PROPOSALLIST
										for (int i = 0; i < proposalListCount; i++) {
											if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

												for (int j = i; j < proposalListCount - 1; j++)
												{
													proposalList[j] = proposalList[j + 1];
												}

												proposalListCount--;
											}
										}
										*givenPorposalCount = *givenPorposalCount - 1;
										*dictator = 0;
										*direct = 0;
										*repres = 0;
										*regimProposalController = false;
										for (int i = 0; i < numberOfPeople; i++) {
											personList[i].setCanVoteTrue();
										}
									}
									break;
								case 2:
									*direct = *direct + 1;
									proposalList[proposalIndex - 1].voteForMechanics(personList[index]);
									if (*direct > numberOfPeople / 3) {
										*regim = DirectDemocracy;
										*isElectionOn = true;
										//	PROPOSAL DELETING FROM PROPOSALLIST
										for (int i = 0; i < proposalListCount; i++) {
											if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

												for (int j = i; j < proposalListCount - 1; j++)
												{
													proposalList[j] = proposalList[j + 1];
												}

												proposalListCount--;
											}
										}
										*givenPorposalCount = *givenPorposalCount - 1;
										*dictator = 0;
										*direct = 0;
										*repres = 0;
										*regimProposalController = false;
										for (int i = 0; i < numberOfPeople; i++) {
											personList[i].setCanVoteTrue();
										}
									}
									break;

								case 3:
									*repres = *repres + 1;
									proposalList[proposalIndex - 1].voteForMechanics(personList[index]);
									if (*repres > numberOfPeople / 3) {
										*regim = RepresentativeDemocracy;
										*isElectionOn = true;
										//	PROPOSAL DELETING FROM PROPOSALLIST
										for (int i = 0; i < proposalListCount; i++) {
											if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

												for (int j = i; j < proposalListCount - 1; j++)
												{
													proposalList[j] = proposalList[j + 1];
												}

												proposalListCount--;
											}
										}
										*givenPorposalCount = *givenPorposalCount - 1;
										*dictator = 0;
										*direct = 0;
										*repres = 0;
										*regimProposalController = false;
										for (int i = 0; i < numberOfPeople; i++) {
											personList[i].setCanVoteTrue();
										}
									}
									break;
								default:

									cout << "Your vote is invalid." << endl;
									break;
								}

							}

							// CONSTITUTION VOTE
							else {
								cout << "Vote the proposal\n1-Yes\n2-No" << endl;
								int decision;
								cin >> decision;

								switch (decision) {
								case 1:
									proposalList[proposalIndex - 1].increaseYesCount(personList[index]);
									if (proposalList[proposalIndex - 1].getYesCount() > numberOfPeople / 2) {
										constitution[*maddeSayisi] = proposalList[proposalIndex - 1].getProposal();
										*maddeSayisi = *maddeSayisi + 1;
										// DELETING PROPOSAL 

										for (int i = 0; i < proposalListCount; i++) {
											if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

												for (int j = i; j < proposalListCount - 1; j++)
												{
													proposalList[j] = proposalList[j + 1];
												}

												proposalListCount--;
											}
										}
										*givenPorposalCount = *givenPorposalCount - 1;
									}

									break;
								case 2:
									proposalList[proposalIndex - 1].increaseNoCount(personList[index]);
									if (proposalList[proposalIndex - 1].getNoCount() > numberOfPeople / 2) {
										// DELETING PROPOSAL
										for (int i = 0; i < proposalListCount; i++) {
											if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

												for (int j = i; j < proposalListCount - 1; j++)
												{
													proposalList[j] = proposalList[j + 1];
												}

												proposalListCount--;
											}
										}
										*givenPorposalCount = *givenPorposalCount - 1;
									}
									break;
								default:
									break;
								}
							}
						}
					}
				}
				break;
			}
			break;
		}
		else {
			if (trial == 0) {
				cout << "Wrong password, next time remember your password... \n";
			}
			else {
				cout << "Wrong password, you have " << trial << " more change \n password:";
				cin >> passwordController;
			}
		}
	}
}

void voteFunctionForDictator(int index, bool* regimProposalController, int* givenPorposalCount, Person* personList, Proposal* proposalList, int proposalListCount, string* constitution, int* maddeSayisi, Regim* regim, bool* isElectionOn, int numberOfPeople) {

	if (personList[index].getIsDictator() == true) {
		cout << "Welcome, our dear Lord, " << personList[index].getName() << ". Which proposal you want to consider? " << endl;
		for (int i = 0; i < proposalListCount; i++) {
			if (proposalList[i].getProposal() != "") {
				cout << i + 1 << "- " << "Proposal: " << proposalList[i].getProposal() << endl;
			}

		}
		int proposalIndex;
		cin >> proposalIndex;

		if (proposalIndex > 0 && proposalIndex < *givenPorposalCount + 1) {

			if (proposalList[proposalIndex - 1].getIsAboutMechanic() == true) {

				cout << "Please select the next system:\n1-Dictatorship\n2-DirectDemocracy\n3-RepresentativeDemocracy\n" << endl;

				int vote;
				cin >> vote;

				switch (vote)
				{
				case 1:
					*regim = Dictatorship;
					personList[index].setIsDictatorFalse();
					*isElectionOn = true;
					//	PROPOSAL DELETING FROM PROPOSALLIST
					for (int i = 0; i < proposalListCount; i++) {
						if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

							for (int j = i; j < proposalListCount - 1; j++)
							{
								proposalList[j] = proposalList[j + 1];
							}

							proposalListCount--;
						}
					}
					*givenPorposalCount = *givenPorposalCount - 1;
					*regimProposalController = false;
					for (int i = 0; i < numberOfPeople; i++) {
						personList[i].setCanVoteTrue();
					}
					break;
				case 2:
					*regim = DirectDemocracy;
					personList[index].setIsDictatorFalse();
					//	PROPOSAL DELETING FROM PROPOSALLIST
					for (int i = 0; i < proposalListCount; i++) {
						if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

							for (int j = i; j < proposalListCount - 1; j++)
							{
								proposalList[j] = proposalList[j + 1];
							}

							proposalListCount--;
						}
					}
					*givenPorposalCount = *givenPorposalCount - 1;
					*regimProposalController = false;
					for (int i = 0; i < numberOfPeople; i++) {
						personList[i].setCanVoteTrue();
					}
					break;


				case 3:

					*regim = RepresentativeDemocracy;
					personList[index].setIsDictatorFalse();
					*isElectionOn = true;
					//	PROPOSAL DELETING FROM PROPOSALLIST
					for (int i = 0; i < proposalListCount; i++) {
						if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

							for (int j = i; j < proposalListCount - 1; j++)
							{
								proposalList[j] = proposalList[j + 1];
							}

							proposalListCount--;
						}
					}
					*givenPorposalCount = *givenPorposalCount - 1;
					*regimProposalController = false;
					for (int i = 0; i < numberOfPeople; i++) {
						personList[i].setCanVoteTrue();
					}
					break;

				default:
					cout << "There is no possible decision to vote my Lord." << endl;
					break;
				}

			}
			else {
				cout << "My Lord, your decision? \n1-Yes\n2-No" << endl;
				int decision;
				cin >> decision;

				switch (decision) {
				case 1:

					constitution[*maddeSayisi] = proposalList[proposalIndex - 1].getProposal();
					*maddeSayisi = *maddeSayisi + 1;

					// DELETING PROPOSAL
					for (int i = 0; i < proposalListCount; i++) {
						if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

							for (int j = i; j < proposalListCount - 1; j++)
							{
								proposalList[j] = proposalList[j + 1];
							}

							proposalListCount--;
						}
					}
					*givenPorposalCount = *givenPorposalCount - 1;
					break;
				case 2:
					// DELETING PROPOSAL
					for (int i = 0; i < proposalListCount; i++) {
						if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

							for (int j = i; j < proposalListCount - 1; j++)
							{
								proposalList[j] = proposalList[j + 1];
							}

							proposalListCount--;
						}
					}
					*givenPorposalCount = *givenPorposalCount - 1;
					break;
				default:
					break;
				}
			}

		}
	}
	else {
		cout << "Fortunately, you are not the dictator. You are going to be punishment for this behave ..:)" << endl;
	}
}

void voteFunctionForRepresentetiveDemocracy(int index, int* givenPorposalCount, Person* personList, Proposal* proposalList, int proposalListCount, string* constitution, int* maddeSayisi, int numberOfPeople, int* dictator, int* repres, int* direct, Regim* regim, bool* isElectionOn, bool* regimProposalController) {

	if (personList[index].getCanVote() == true) {

		string passwordController;

		cout << personList[index].getName() << ", \n Please, confirm your action with your password! \n Password:";
		cin >> passwordController;

		for (int trial = 2; trial >= 0; trial--) {
			if (passwordController == personList[index].getPassword()) {

				cout << "Welcome, " << personList[index].getName() << ". Which proposal you want to vote? " << endl;
				for (int i = 0; i < proposalListCount; i++) {

					if (proposalList[i].getProposal() != "") {
						for (int j = 0; j < numberOfPeople; j++) {

							if (proposalList[i].getPersonList()[j].getName() == personList[index].getName()) {

								cout << i + 1 << "- " << "Proposal: " << proposalList[i].getProposal() << " | Yes Count: " << proposalList[i].getYesCount() << " | No Count: " << proposalList[i].getNoCount() << "\n" << endl;

							}

						}

					}
				}

				int proposalIndex;
				cin >> proposalIndex;

				if (proposalIndex > 0 && proposalIndex < *givenPorposalCount + 1) {

					for (int j = 0; j < numberOfPeople; j++) {

						if ((proposalList[proposalIndex - 1].getProposal() != "")) {
							if (proposalList[proposalIndex - 1].getPersonList()[j].getName() == personList[index].getName()) {
								// MEKANÝK VOTE
								if (proposalList[proposalIndex - 1].getIsAboutMechanic() == true) {

									cout << "Please select the next system:\n1-Dictatorship\n2-DirectDemocracy\n3-RepresentativeDemocracy\n" << endl;

									int vote;
									cin >> vote;

									switch (vote)
									{
									case 1:
										*dictator = *dictator + 1;
										proposalList[proposalIndex - 1].voteForMechanics(personList[index]);
										if (*dictator > (numberOfPeople / 2) / 3) {
											*regim = Dictatorship;
											*isElectionOn = true;
											//	PROPOSAL DELETING FROM PROPOSALLIST
											for (int i = 0; i < proposalListCount; i++) {
												if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

													for (int j = i; j < proposalListCount - 1; j++)
													{
														proposalList[j] = proposalList[j + 1];
													}

													proposalListCount--;
												}
											}
											*givenPorposalCount = *givenPorposalCount - 1;
											*dictator = 0;
											*direct = 0;
											*repres = 0;
											*regimProposalController = false;
											for (int i = 0; i < numberOfPeople; i++) {
												personList[i].setCanVoteTrue();
											}
										}
										break;
									case 2:
										*direct = *direct + 1;
										proposalList[proposalIndex - 1].voteForMechanics(personList[index]);
										if (*direct > (numberOfPeople / 2) / 3) {
											*regim = DirectDemocracy;
											*isElectionOn = true;
											//	PROPOSAL DELETING FROM PROPOSALLIST
											for (int i = 0; i < proposalListCount; i++) {
												if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

													for (int j = i; j < proposalListCount - 1; j++)
													{
														proposalList[j] = proposalList[j + 1];
													}

													proposalListCount--;
												}
											}
											*givenPorposalCount = *givenPorposalCount - 1;
											*dictator = 0;
											*direct = 0;
											*repres = 0;
											*regimProposalController = false;
											for (int i = 0; i < numberOfPeople; i++) {
												personList[i].setCanVoteTrue();
											}
										}
										break;

									case 3:
										*repres = *repres + 1;
										proposalList[proposalIndex - 1].voteForMechanics(personList[index]);
										if (*repres > (numberOfPeople / 2) / 3) {
											*regim = RepresentativeDemocracy;
											*isElectionOn = true;
											//	PROPOSAL DELETING FROM PROPOSALLIST
											for (int i = 0; i < proposalListCount; i++) {
												if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

													for (int j = i; j < proposalListCount - 1; j++)
													{
														proposalList[j] = proposalList[j + 1];
													}
													proposalListCount--;
												}
											}
											*givenPorposalCount = *givenPorposalCount - 1;
											*dictator = 0;
											*direct = 0;
											*repres = 0;
											*regimProposalController = false;
											for (int i = 0; i < numberOfPeople; i++) {
												personList[i].setCanVoteTrue();
											}
										}
										break;
									default:

										cout << "Your vote is invalid." << endl;
										break;
									}

								}

								// CONSTITUTION VOTE
								else {
									cout << "Vote the proposal\n1-Yes\n2-No" << endl;
									int decision;
									cin >> decision;

									switch (decision) {
									case 1:
										proposalList[proposalIndex - 1].increaseYesCount(personList[index]);
										if (proposalList[proposalIndex - 1].getYesCount() > numberOfPeople / 4) {
											constitution[*maddeSayisi] = proposalList[proposalIndex - 1].getProposal();
											*maddeSayisi = *maddeSayisi + 1;
											// DELETING PROPOSAL 

											for (int i = 0; i < proposalListCount; i++) {
												if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

													for (int j = i; j < proposalListCount - 1; j++)
													{
														proposalList[j] = proposalList[j + 1];
													}

													proposalListCount--;
												}
											}
											*givenPorposalCount = *givenPorposalCount - 1;
										}

										break;
									case 2:
										proposalList[proposalIndex - 1].increaseNoCount(personList[index]);
										if (proposalList[proposalIndex - 1].getNoCount() > numberOfPeople / 4) {
											// DELETING PROPOSAL
											for (int i = 0; i < proposalListCount; i++) {
												if (proposalList[i].getProposal() == proposalList[proposalIndex - 1].getProposal()) {

													for (int j = i; j < proposalListCount - 1; j++)
													{
														proposalList[j] = proposalList[j + 1];
													}

													proposalListCount--;
												}
											}
											*givenPorposalCount = *givenPorposalCount - 1;
										}
										break;
									default:
										break;
									}
								}



							}
						}
					}

					break;
				}
				break;
			}
			else {
				if (trial == 0) {
					cout << "Wrong password, next time remember your password... \n";
				}
				else {
					cout << "Wrong password, you have " << trial << " more change \n password:";
					cin >> passwordController;
				}
			}
		}
	}
	else {
		cout << "You do not have the right to vote. You can give a proposal if you want." << endl;
	}
}

void electionVote(Person* personList, int numberOfPeople, int peopleIndex, Regim regim, bool* isElectionOn) {

	switch (regim)
	{
	case Dictatorship:

		if (personList[peopleIndex].getCanGiveElectionVote() == true) {
			cout << "Please, enter the number of person that you want to vote to choose your Great Lord... " << endl;

			for (int index = 0; index < numberOfPeople; index++) {

				cout << personList[index].getName() << "-> No: " << index << endl;
			}
			cout << "No Vote  -1" << endl;
			int votedPerson;
			cin >> votedPerson;

			if (votedPerson > -1 && votedPerson < numberOfPeople) {
				personList[votedPerson].increaseVoteCount();
				personList[peopleIndex].toggleCanGiveElectionVote();

				int totalVote = 0;
				for (int index = 0; index < numberOfPeople; index++) {
					totalVote = totalVote + personList[index].getVoteCount();
				}

				cout << "Total Vote : " << totalVote << "\nThe result will be seen when everyone votes..." << endl;

				if (totalVote == numberOfPeople) {

					Person* voteList;
					voteList = new Person[numberOfPeople];
					for (int i = 0; i < numberOfPeople; i++) {
						voteList[i] = personList[i];
					}

					bubbleSort(voteList, numberOfPeople);

					cout << "Election Result:" << endl;
					for (int i = 0; i < numberOfPeople; i++) {

						cout << "Name: " << voteList[i].getName() << " Vote: " << voteList[i].getVoteCount() << endl;

					}


					if (voteList[numberOfPeople - 1].getVoteCount() == voteList[numberOfPeople - 2].getVoteCount()) {
						int lower = 0, upper = 1;
						int num = (rand() % (upper - lower + 1)) + lower;

						for (int i = 0; i < numberOfPeople; i++) {

							if (personList[i].getName() == voteList[numberOfPeople - 1 - num].getName()) {

								personList[i].setIsDictatorTrue();

								cout << "The new dictator is " << personList[i].getName() << endl;
							};

						}
					}
					else {
						for (int i = 0; i < numberOfPeople; i++) {

							if (personList[i].getName() == voteList[numberOfPeople - 1].getName()) {

								personList[i].setIsDictatorTrue();

								cout << "The new dictator is " << personList[i].getName() << endl;
							};
						}
					}

					for (int i = 0; i < numberOfPeople; i++) {

						if (personList[i].getName() == voteList[numberOfPeople - 1].getName()) {

							personList[i].setIsDictatorTrue();
						};

					}

					*isElectionOn = false;

					// Refreshing
					for (int i = 0; i < numberOfPeople; i++) {

						personList[i].refreshCanGiveElectionVote();
						personList[i].refreshVoteCount();
					}

				}

				break;
			}
			else if (votedPerson == -1) {
				personList[peopleIndex].toggleCanGiveElectionVote();
			}
		}
		else {
			cout << "You already voted !!!" << endl;
		}

		break;
	case RepresentativeDemocracy:

		if (personList[peopleIndex].getCanGiveElectionVote() == true) {
			cout << "Please enter the number of person you want to vote for your representative person : " << endl;
			for (int index = 0; index < numberOfPeople; index++) {

				cout << personList[index].getName() << "-> No: " << index << endl;

			}
			int votedPerson;
			cin >> votedPerson;

			if (votedPerson > -1 && votedPerson < numberOfPeople) {
				personList[votedPerson].increaseVoteCount();
				personList[peopleIndex].toggleCanGiveElectionVote();

				int totalVote = 0;
				for (int index = 0; index < numberOfPeople; index++) {
					totalVote = totalVote + personList[index].getVoteCount();
				}

				cout << "Total Vote : " << totalVote << "\nResults will be seen when everybody give their vote..." << endl;


				if (totalVote == numberOfPeople) {

					Person* voteList;
					voteList = new Person[numberOfPeople];
					for (int i = 0; i < numberOfPeople; i++) {
						voteList[i] = personList[i];
					}

					bubbleSort(voteList, numberOfPeople);

					cout << "Election Result:" << endl;
					for (int i = numberOfPeople - 1; i >= 0; i--) {

						cout << "Name: " << voteList[i].getName() << " Vote: " << voteList[i].getVoteCount() << endl;

					}

					for (int i = 0; i < numberOfPeople / 2; i++) {

						for (int j = 0; j < numberOfPeople; j++) {
							if (personList[j].getName() == voteList[i].getName()) {
								personList[j].setCanVoteFalse();
								break;
							}
						}

					}

					cout << "The representetive people in council are :" << endl;

					for (int i = 0; i < numberOfPeople; i++) {

						if (personList[i].getCanVote() == true) {
							cout << "Name : " << personList[i].getName() << endl;
						}

					}

					// Refreshing
					*isElectionOn = false;
					for (int i = 0; i < numberOfPeople; i++) {
						personList[i].refreshCanGiveElectionVote();
						personList[i].refreshVoteCount();
					}

				}

			}
		}
		else {
			cout << "You already voted !!!" << endl;
		}

		break;
	case DirectDemocracy:
		break;
	default:
		break;
	}
}

void swap(Person* xp, Person* yp)
{
	Person temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(Person arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)

			if (arr[j].getVoteCount() > arr[j + 1].getVoteCount())
				swap(&arr[j], &arr[j + 1]);
}

void deleteProposalFunction(Proposal* proposalList, int proposalListCount) {

	for (int i = 0; i < proposalListCount; i++) {

		if (proposalList[i].getProposal() == proposalList[proposalListCount].getProposal()) {

			for (int j = i; j < proposalListCount - 1; j++)
			{
				proposalList[j] = proposalList[j + 1];
			}
			if (i > 0) {
				i--;
			}
			else {
				i = 0;
			}
			proposalListCount--;
		}
	}
}