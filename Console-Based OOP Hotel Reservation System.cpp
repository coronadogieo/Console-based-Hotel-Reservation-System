/*
############################################################################################################
#                                                                                                          #
# This program is developed by Gieo Coronado. Please refrain from using it without permission. Thank you!  #
#                                                                                                          #                
############################################################################################################
*/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
#include <Windows.h>

using namespace std;


bool isContinue, isInvalidInput;
int clients = 0;
string inputName, inputAddress, inputContactNum, inputEmail;

void clearInput() {
	inputName = "";
	inputAddress = "";
	inputEmail = "";
};

//structs, variables and functions needed for date input
struct Date {
	int d, m, y;
};

const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int countLeapYears(Date d) {
	int year = d.y;

	if (d.m <= 2) {
		year--;
	}

	return year / 4
		- year / 100
		+ year / 400;
}
int getNumberOfNights(Date dt1, Date dt2) {
	long int var1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++) {
		var1 += monthDays[i];
	};

	var1 += countLeapYears(dt1);


	long int var2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++) {
		var2 += monthDays[i];
	};
	var2 += countLeapYears(dt2);

	return (var2 - var1);
}

//contact number input validation
void inputContactNumber() {
	system("CLS");
	bool isInvalid;
	do {
		isInvalid = false;
		string temp;

		cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
		cout << "	11 DIGIT CONTACT NUMBER [09XXXXXXXXXX]: ";
		cin >> temp;

		if (temp.length() == 11 && ((temp[0] == '0') && (temp[1] == '9'))) {
			for (int i = 0; i < temp.length(); i++) {
				if (!(temp[i] >= 0)) {
					cout << "\n	---------------------------------------------------------------------------------------" << endl;
					cout << "		INVALID INPUT, PLEASE ENTER A VALID 11-DIGIT MOBILE NUMBER [09xxxxxxxxx]" << endl;
					cout << "	---------------------------------------------------------------------------------------" << endl;
					isInvalid = true;
					break;
				}
			}
			inputContactNum = temp;
		}
		else {
			cout << "\n	---------------------------------------------------------------------------------------" << endl;
			cout << "		INVALID INPUT, PLEASE ENTER A VALID 11-DIGIT MOBILE NUMBER [09xxxxxxxxx]" << endl;
			cout << "	---------------------------------------------------------------------------------------" << endl;
			isInvalid = true;
		}
	} while (isInvalid);
};



class Client {
private:
	string name, address, contactNum, email, type, paymentType;
	int guestNum, transactionNum, numDaysReserved, additionalGuestNum;
	float totalBillAmount;
	bool isBreakfast, isLunchDinner;
public:
	Date date1, date2;
	bool isCancelled = false;

	string getName();
	string getType();
	int getTransactionNum();
	int getGuestNum();
	string getPaymentType();
	string getAddress();
	string getContactNum();
	string getEmail();
	string getIsBreakdast();
	string getIsLunchDinner();
	int getNumDaysReserved();
	int getAdditionalGuestNum();

	void setType(string);
	void setPaymentType(string);
	void setGuestNum(int);
	void setTransactionNum(int);
	void setIsBreakdast(int);
	void setIsLunchDinner(int);
	void setNumDaysReserved(Date*, Date*);
	void setAdditionalGuestNum(int);

	void inputDate(Date*, Date*);

	Client(string Name, string Address, string ContactNum, string Email) {
		name = Name;
		address = Address;
		contactNum = ContactNum;
		email = Email;
	}
	~Client() {}
};

class Employee {
public:
	string name;
	string position;
};

class ReservationTransactionsIncharge: public Employee {
public:

	bool disapproveRescheduleOrCancellationRequest() {
		return false;
	}
};


class HotelManager : public ReservationTransactionsIncharge {
public:
	string position = "Hotel Manager";
	bool AttachSignatureInTheForm() { 
		return true;
	};

	bool approveReservationCancellation() { 
		if (AttachSignatureInTheForm() && !disapproveRescheduleOrCancellationRequest()) {
			return true;
		}
		else {
			cout << "Reservation Cancellation cannot proceed, it requires signature from a Hotel Manager.";
		}
	};
	bool approveRescheduleReservation() { 
		if (AttachSignatureInTheForm() && !disapproveRescheduleOrCancellationRequest()) {
			return true;
		}
		else {
			cout << "Reservation Reschedule cannot proceed, it requires signature from a Hotel Manager.";
		}

	};

};

class FrontDeskOfficer: public ReservationTransactionsIncharge {
public:
	string position = "Front Desk Officer";

	void makeAReservation(Client*);
	void cancelReservation(Client*, HotelManager*);
	void moveReservation(Client*, HotelManager*);
	void printReservationStatus(Client);
	int calculateTotalBillAmount(Client*);
};

int main() {
	do {
		while (inputName.empty()) {
			system("CLS");
			cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
			cout << "	NAME: ";
			getline(cin, inputName);
		}
		while (inputAddress.empty()) {
			system("CLS");
			cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
			cout << "	ADDRESS: ";
			getline(cin, inputAddress);
		}

		inputContactNumber();

		while (inputEmail.empty()) {
			system("CLS");
			cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
			cout << "	EMAIL: ";
			getline(cin, inputEmail);
		}
		Client Gieo(inputName, inputAddress, inputContactNum, inputEmail);
		FrontDeskOfficer Juan;
		HotelManager Ben;

		Juan.makeAReservation(&Gieo);

		do {
			char continueinput;
			cout << "\n\n	----------------------------------------" << endl;
			cout << "		WHAT WOULD YOU LIKE TO DO?" << endl;
			cout << "	----------------------------------------" << endl << endl;
			cout << "	Please enter : \n\n	[C] Cancel you room\n	[M] Move your reservation\n	[S] Check reservation status and details\n	[R] Restart the program\n	[E] Exit the program\n\n	INPUT: ";
			cin >> continueinput;
			if (toupper(continueinput) == 'C') {
				system("CLS");
				isInvalidInput = true;
				Juan.cancelReservation(&Gieo, &Ben);
			}
			else if (toupper(continueinput) == 'M') {
				system("CLS");
				Juan.moveReservation(&Gieo, &Ben);
				isInvalidInput = true;
			}
			else if (toupper(continueinput) == 'S') {
				system("CLS");
				isInvalidInput = true;
				Juan.printReservationStatus(Gieo);
			}
			else if (toupper(continueinput) == 'R') {
				system("CLS");
				clearInput();
				isContinue = true;
				isInvalidInput = false;
			}
			else if (toupper(continueinput) == 'E') {
				return 0;
			}
			else if (isdigit(continueinput) || toupper(continueinput) != 'C' || toupper(continueinput) != 'M' || toupper(continueinput) != 'S' || toupper(continueinput) != 'R' || toupper(continueinput) != 'E') {
				system("CLS");
				isInvalidInput = true;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "	INVALID INPUT! Please enter among the available inputs below...\n";
				cout << "-------------------------------------------------------------------" << endl << endl;
				continueinput = NULL;
			}
		} while (isInvalidInput);
	} while (isContinue);
	return 0;
};
void FrontDeskOfficer::makeAReservation(Client* Gieo) {
	bool isInputValid = false, isInvalid = true;
	string Date, PaymentType;
	int GuestNum;

	system("CLS");
	cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
	Gieo->inputDate(&Gieo->date1, &Gieo->date2);

	do {
		int inputtype;
		cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
		cout << "	ROOM TYPE\n	[0] Single  1 pax; PHP 800/night\n	[1] Double - 2 pax; PHP 1200/night\n	[2] Twin - 2 pax; PHP 1500/night\n	[3] King - 3 pax; PHP 2000/night\n	[4] Suite - 4 pax; PHP 2500/night\n\n	WHAT ROOM WOULD YOU LIKE TO RESERVE: ";
		cin >> inputtype;
		if (cin.good() && (inputtype >= 0 && inputtype <= 4)) {
			switch (inputtype) {
			case 0:
				Gieo->setType("Single");
				Gieo->setGuestNum(1);
				break;
			case 1:
				Gieo->setType("Double");
				Gieo->setGuestNum(2);
				break;
			case 2:
				Gieo->setType("Twin");
				Gieo->setGuestNum(2);
				break;
			case 3:
				Gieo->setType("King");
				Gieo->setGuestNum(3);
				break;
			case 4:
				Gieo->setType("Suite");
				Gieo->setGuestNum(4);
				break;
			default:
				break;
			}
			isInvalid = false;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n-------------------------------------------------------------------" << endl;
			cout << "	***INVALID, ENTER A VALID ROOM TYPE OPTION...***\n";
			cout << "-------------------------------------------------------------------\n\n" << endl;
		}
	} while (isInvalid);

	system("CLS");
	isInvalid = true;

	do {
		int inputIsBreakFast;
		cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
		cout << "	DO YOU WANT TO AVAIL HOTEL BREAKFAST? (250 PHP PER PAX) \n	[0] NO\n	[1] YES\n	INPUT: ";
		cin >> inputIsBreakFast;
		if (cin.good() && (inputIsBreakFast == 0 || inputIsBreakFast == 1)) {
			switch (inputIsBreakFast) {
			case 0:
				Gieo->setIsBreakdast(0);
				break;
			case 1:
				Gieo->setIsBreakdast(1);
				break;
			default:
				break;
			}
			isInvalid = false;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n	------------------------------------------------------------------------------" << endl;
			cout << "		***INVALID, ENTER A VALID OPTION... [0] NO or [1] YES...***\n";
			cout << "	------------------------------------------------------------------------------\n\n" << endl;
		}
	} while (isInvalid);

	system("CLS");
	isInvalid = true;

	do {
		int inputIsLunchDinner;
		cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
		cout << "	DO YOU WANT TO AVAIL HOTEL LUNCH AND DINNER? (800 PHP PER PAX) \n	[0] NO\n	[1] YES\n	INPUT: ";
		cin >> inputIsLunchDinner;
		if (cin.good() && (inputIsLunchDinner == 0 || inputIsLunchDinner == 1)) {
			switch (inputIsLunchDinner) {
			case 0:
				Gieo->setIsLunchDinner(0);
				break;
			case 1:
				Gieo->setIsLunchDinner(1);
				break;
			default:
				break;
			}
			isInvalid = false;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n	------------------------------------------------------------------------------" << endl;
			cout << "		***INVALID, ENTER A VALID OPTION... [0] NO or [1] YES...***\n";
			cout << "	------------------------------------------------------------------------------\n\n" << endl;
		}
	} while (isInvalid);

	isInvalid = true;
	system("CLS");
	do {
		int inputtype;
		cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
		cout << "	PAYMENT TYPE ([0] 30% DP, [1] Full Payment): ";
		cin >> inputtype;
		if (cin.good() && (inputtype == 0 || inputtype == 1)) {
			switch (inputtype) {
			case 0:
				PaymentType = "30% DP";
				break;
			case 1:
				PaymentType = "Full Payment";
				break;
			default:
				break;
			}
			isInvalid = false;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n	-------------------------------------------------------------------" << endl;
			cout << "		***INVALID, ENTER A VALID PAYMENT TYPE OPTION...***\n";
			cout << "	-------------------------------------------------------------------\n\n" << endl;
		}
	} while (isInvalid);
	
	system("CLS");
	do {
		int temptotal;
		int inputAdditionalGuestNum;
		cout << "\n		WELCOME TO DLSL HOTEL\n\n		ENTER YOUR DETAILS! \n";
		cout << "\n	DO YOU WANT TO AVAIL ADDITIONAL NUMBER OF GUEST? "<<endl;
		cout << "\n	----------------------------------------------------------------------------------";
		cout << "\n		NOTE: "<<Gieo->getGuestNum()<<" guest are currently allowed to check in into you room of choice.";
		cout << "\n		If you don't want additional guests, please enter \"0\"";
		cout << "\n	----------------------------------------------------------------------------------" << endl;
		cout << "\n	ADDITIONAL NUMBER OF GUEST: ";
		cin >> inputAdditionalGuestNum;
		if (cin.good() && inputAdditionalGuestNum >= 0) {
			Gieo->setAdditionalGuestNum(inputAdditionalGuestNum);
			temptotal = (Gieo->getGuestNum() + Gieo->getAdditionalGuestNum());
			Gieo->setGuestNum(temptotal);
			isInputValid = true;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n	-------------------------------------------------------------------" << endl;
			cout << "		***INVALID, ENTER A VALID NUMBER OF GUEST...***\n";
			cout << "	-------------------------------------------------------------------\n\n" << endl;
		}
	} while (!isInputValid);

	clients++;

	Gieo->setPaymentType(PaymentType);
	Gieo->setTransactionNum(clients);

	system("CLS");
	cout << "-------------------------------------------------------------------" << endl;
	cout << "	A " << Gieo->getType() << " room for " << Gieo->getName() << " has been reserved...\n		Transaction Number: " << Gieo->getTransactionNum() << endl;
	cout << "-------------------------------------------------------------------" << endl;
}
void FrontDeskOfficer::cancelReservation(Client* x, HotelManager* y) {
	int inputTransctNum;
	bool isInputValid = false;

	if (!(x->isCancelled)) {

		do {
			cout << "\n	Enter Transaction Number: ";
			cin >> inputTransctNum;
			if (cin.good() && inputTransctNum >= 0) {
				isInputValid = true;
			}
			else {
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout << "\n\n	-------------------------------------------------------------------" << endl;
				cout << "		***INVALID, ENTER A VALID TRANSACTION NUMBER...***\n";
				cout << "	-------------------------------------------------------------------\n\n" << endl;
			}
		} while (!isInputValid);

		if (y->approveReservationCancellation()) {
			if (inputTransctNum == x->getTransactionNum()) {
				string previousRoom = x->getType();


				system("CLS");
				cout << "-------------------------------------------------------------------" << endl;
				cout << "	The " << previousRoom << " room for " << x->getName() << " has been cancelled...\n	Transaction Number: " << x->getTransactionNum() << endl;
				cout << "-------------------------------------------------------------------" << endl;

				x->isCancelled = true;
				Sleep(1000);
			}
			else {
				system("CLS");
				cout << "-------------------------------------------------------------------------" << endl;
				cout << "	Request cannot be processed. Transaction Number doesn't match...\n";
				cout << "-------------------------------------------------------------------------" << endl;
				Sleep(1000);
			}
		}
		else {
			cout << "The Reservation Cancellation has been disapproved by the Hotel Manager";
		}

	}
	else {
		system("CLS");
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "	Request cannot be processed. Reservation is already cancelled...\n";
		cout << "-------------------------------------------------------------------------" << endl;
		Sleep(1000);
	}
}
void FrontDeskOfficer::moveReservation(Client* x, HotelManager* y) {
	int inputTransctNum;
	bool isInputValid = false;

	if (!(x->isCancelled)) {
		string movedDate;

		do {
			cout << "\n	Enter Transaction Number: ";
			cin >> inputTransctNum;
			if (cin.good() && inputTransctNum >= 0) {
				isInputValid = true;
			}
			else {
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout << "\n\n-------------------------------------------------------------------" << endl;
				cout << "	***INVALID, ENTER A VALID TRANSACTION NUMBER...***\n";
				cout << "-------------------------------------------------------------------\n\n" << endl;
			}
		} while (!isInputValid);

		if (y->approveRescheduleReservation()) {
			if (inputTransctNum == x->getTransactionNum()) {
				system("CLS");
				cout << "\n	NEW RESERVATION DATE: \n";

				x->inputDate(&x->date1, &x->date2);

				system("CLS");
				cout << "------------------------------------------------------------------------------------" << endl;
				cout << "	The " << x->getType() << " room for " << x->getName() << " has been moved to " << x->date1.m << "/" << x->date1.d << "/" << x->date1.y << " to " << x->date2.m << "/" << x->date2.d << "/" << x->date2.y << "...\n		Transaction Number : " << x->getTransactionNum() << endl;
				cout << "------------------------------------------------------------------------------------" << endl;
				Sleep(1000);
			}
			else {
				system("CLS");
				cout << "-------------------------------------------------------------------------" << endl;
				cout << "	Request cannot be processed. Transaction Number doesn't match...\n";
				cout << "-------------------------------------------------------------------------" << endl;
				Sleep(1000);
			}
		}
		else {
			cout << "The Reservation Cancellation has been disapproved by the Hotel Manager";
		}
	}
	else {
		system("CLS");
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "	Request cannot be processed. Reservation is already cancelled...\n";
		cout << "-------------------------------------------------------------------------" << endl;
		Sleep(1000);
	}
}
int FrontDeskOfficer::calculateTotalBillAmount(Client* x) {

	int rate;

	if (x->getType() == "Single") {
		rate = 800;
	}
	else if (x->getType() == "Double") {
		rate = 1200;
	}
	else if (x->getType() == "Twin") {
		rate = 1500;
	}
	else if (x->getType() == "King") {
		rate = 2000;
	}
	else if (x->getType() == "Suite") {
		rate = 2500;
	}
	else {
		rate = 0;
	};

	if (x->getIsBreakdast() == "YES" && x->getIsLunchDinner() == "YES") {
		return ((rate * x->getNumDaysReserved()) + ((x->getAdditionalGuestNum() * 500) * x->getNumDaysReserved()) + ((250 * x->getGuestNum()) * (x->getNumDaysReserved() + 1 )) + ((800 * x->getGuestNum()) * (x->getNumDaysReserved() + 1)));
	}
	else if (x->getIsBreakdast() == "YES" && x->getIsLunchDinner() == "NO") {
		return ((rate * x->getNumDaysReserved()) + ((x->getAdditionalGuestNum() * 500) * x->getNumDaysReserved()) + ((250 * x->getGuestNum()) * (x->getNumDaysReserved() + 1)));
	}
	else if (x->getIsBreakdast() == "NO" && x->getIsLunchDinner() == "YES") {
		return ((rate * x->getNumDaysReserved()) + ((x->getAdditionalGuestNum() * 500) * x->getNumDaysReserved()) + ((800 * x->getGuestNum()) * (x->getNumDaysReserved() + 1)));
	}
	else {
		return ((rate * x->getNumDaysReserved()) + ((x->getAdditionalGuestNum() * 500) * x->getNumDaysReserved()));
	}

}

string Client::getName() {
	return name;
}
string Client::getType() {
	return type;
}
string Client::getPaymentType() {
	return paymentType;
}
int Client::getGuestNum() {
	return guestNum;
}
int Client::getTransactionNum() {
	return transactionNum;
};
string Client::getAddress() {
	return address;
}
string Client::getContactNum() {
	return contactNum;
}
string Client::getEmail() {
	return email;
}
string Client::getIsBreakdast() {
	return (isBreakfast == true) ? "YES" : "NO";
};
string Client::getIsLunchDinner() {
	return (isLunchDinner == true) ? "YES" : "NO";
};
int Client::getNumDaysReserved() {
	return numDaysReserved;
};
int Client::getAdditionalGuestNum() {
	return additionalGuestNum;
};

void Client::inputDate(Date* x, Date* y) {
	int inputd1, inputm1, inputy1, inputd2, inputm2, inputy2;
	bool isValid = false;

		do {
			cout << "	CHECK IN DAY (1-31): ";
			cin >> inputd1;
			if (cin.good() && (inputd1 >= 1 && inputd1 <= 31)) {
				x->d = inputd1;
				isValid = true;
			} else {
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout << "\n\n	-------------------------------------------------------------------" << endl;
				cout << "		***INVALID, ENTER A VALID CHECK IN DATE (1-31)...***\n";
				cout << "	-------------------------------------------------------------------\n\n" << endl;
			}
		} while (!isValid);

		isValid = false;

		do {
			cout << "	CHECK IN MONTH ( [1] JAN - [12] DEC ): ";
			cin >> inputm1;
			if (cin.good() && (inputm1 >= 1 && inputm1 <= 12)) {
				x->m = inputm1;
				isValid = true;
			}
			else {
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout << "\n\n	-------------------------------------------------------------------" << endl;
				cout << "		***INVALID, ENTER A VALID CHECK IN MONTH (1-12)...***\n";
				cout << "	-------------------------------------------------------------------\n\n" << endl;
			}
		} while (!isValid);

		isValid = false;

		do {
			cout << "	CHECK IN YEAR (2O22 ONWARDS): ";
			cin >> inputy1;
			if (cin.good() && inputy1 >= 2022) {
				x->y = inputy1;
				isValid = true;
			}
			else {
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout << "\n\n	-------------------------------------------------------------------" << endl;
				cout << "		***INVALID, ENTER A VALID CHECK IN YEAR (2022 ONWARDS)...***\n";
				cout << "	-------------------------------------------------------------------\n\n" << endl;
			}
		} while (!isValid);

		isValid = false;


	system("CLS");

	do {
		cout << "\n	CHECK OUT DAY (1-31): ";
		cin >> inputd2;
		if (cin.good() && (inputd2 >= 1 && inputd2 <= 31)) {
			y->d = inputd2;
			isValid = true;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n	-------------------------------------------------------------------" << endl;
			cout << "		***INVALID, ENTER A VALID CHECK OUT DATE (1-31)...***\n";
			cout << "	-------------------------------------------------------------------\n\n" << endl;
		}
	} while (!isValid);

	isValid = false;

	do {
		cout << "\n	CHECK OUT MONTH ( [1] JAN - [12] DEC ): ";
		cin >> inputm2;
		if (cin.good() && (inputm2 >= 1 && inputm2 <= 12)) {
			y->m = inputm2;
			isValid = true;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n	-------------------------------------------------------------------" << endl;
			cout << "		***INVALID, ENTER A VALID CHECK OUT MONTH (1-12)...***\n";
			cout << "	-------------------------------------------------------------------\n\n" << endl;
		}
	} while (!isValid);

	isValid = false;

	do {
		cout << "\n	CHECK OUT YEAR (2O22 ONWARDS): ";
		cin >> inputy2;
		if (cin.good() && inputy2 >= 2022) {
			y->y = inputy2;
			isValid = true;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "\n\n	-------------------------------------------------------------------" << endl;
			cout << "		***INVALID, ENTER A VALID CHECK OUT YEAR (2022 ONWARDS)...***\n";
			cout << "	-------------------------------------------------------------------\n\n" << endl;
		}
	} while (!isValid);

	system("CLS");
	setNumDaysReserved(x, y);
};
void Client::setType(string data) {
	type = data;
};
void Client::setPaymentType(string data) {
	paymentType = data;
};
void Client::setGuestNum(int data) {
	guestNum = data;
};
void Client::setTransactionNum(int data) {
	transactionNum = data;
};
void Client::setIsBreakdast(int data) {
	(data == 0) ? isBreakfast = false: isBreakfast = true;
};
void Client::setIsLunchDinner(int data) {
	(data == 0) ? isLunchDinner = false : isLunchDinner = true;
};
void Client::setNumDaysReserved(Date* d1, Date* d2) {
	numDaysReserved = getNumberOfNights(*d1, *d2);
};
void Client::setAdditionalGuestNum(int data) {
	additionalGuestNum = data;
}

void FrontDeskOfficer::printReservationStatus(Client x) {
	cout << "\n-------------------------------------------------------------------" << endl;
	cout << "	RESERVATION STATUS AND DETAILS FOR " << x.getName() << endl;
	cout << "	TRANSACTION NUMBER: " << x.getTransactionNum() << endl;
	cout << "-------------------------------------------------------------------" << endl;

	if (x.isCancelled) {
		cout << "\n	---------------------------------------------" << endl;
		cout << "		***RESERVATION IS CANCELLED***" << endl<<endl;
		cout << "		CANCELLATION FEE: PHP " << (calculateTotalBillAmount(&x) * .1 )<< endl;
		cout << "	---------------------------------------------" << endl << endl;
	}
	else {
		cout << "\n	ROOM TYPE: " << x.getType() << endl;
		cout << "	RESERVATION DATE: " << x.date1.m << "/" << x.date1.d << "/" << x.date1.y << " to " << x.date2.m << "/" << x.date2.d << "/" << x.date2.y << endl;
		cout << "	NUMBER OF NIGHTS RESERVED: " << x.getNumDaysReserved() << endl;
		cout << "	NUMBER OF DAYS RESERVED: " << x.getNumDaysReserved() + 1 << endl;
		cout << "	TOTAL NUMBER OF GUESTS: " << x.getGuestNum() << endl;
		cout << "	NUMBER OF AVAILED ADDITIONAL GUESTS: " << x.getAdditionalGuestNum() << endl;
		cout << "	PAYMENT TYPE: " << x.getPaymentType() << endl << endl;
		cout << "	PLUS BREAKFAST "<<"(GOOD FOR "<< x.getNumDaysReserved() + 1<<" DAYS) : "<<x.getIsBreakdast() << endl;
		cout << "	PLUS LUNCH AND DINNER: " << "(GOOD FOR " << x.getNumDaysReserved() + 1 << " DAYS) : " << x.getIsLunchDinner() << endl <<endl;
		cout << "	TRANSACTION NUMBER: " << x.getTransactionNum() << endl;


		cout << "	----------------------------------------------------------" << endl;
		if (x.getPaymentType() == "30% DP") {
			cout << "		DUE TODAY [30% DOWNPAYMENT]: PHP " << (calculateTotalBillAmount(&x) * 0.3) << endl;
			cout << "		TOTAL BILL: PHP " << calculateTotalBillAmount(&x) << endl;
		}
		else {
			cout << "		TOTAL BILL [FULL PAYMENT]: PHP " << calculateTotalBillAmount(&x) << endl;
		}
		cout << "	----------------------------------------------------------" << endl << endl;
	};

	cout << "	--------------------------------" << endl;
	cout << "		CLIENT DETAILS: " << endl;
	cout << "	--------------------------------" << endl << endl;
	cout << "	NAME: " << x.getName() << endl;
	cout << "	ADDRESS: " << x.getAddress() << endl;
	cout << "	CONTACT NUMBER: " << x.getContactNum() << endl;
	cout << "	EMAIL: " << x.getEmail() << endl << endl;
	cout << "-------------------------------------------------------------------" << endl;
	Sleep(2500);
}