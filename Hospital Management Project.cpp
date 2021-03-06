//Fatemeh Abbasi

#include<string>
#include<fstream>
#include<iomanip>
#include<cstdio>
using namespace std;
int n;//the number of patients
int f;//the number of doctors
struct patients {
	string patientcode;
	string firstname;
	string lastname;
	string number;
	string doctorcode;
}sick[100], X, Y;
struct physician {
	string doctorcode;
	string firstname;
	string lastname;
	string num;
	string specialty;
}doctors[50];
/*-------------------*/
bool pass();
void new_patient();
void remove_patient();
void Edit_patient();
void bubblesort1();
void show_patients();
void new_doctor();
void remove_doctor();
void Edit_doctor();
void doctor_search();
void bubblesort2();
void show_doctors();
void file_to_struct();
void file_to_struct2();
/*--------------------*/
int main() {
	if (!pass())
	{
		cout << "\a";
		cin.get();
		return 0;
	}
	cout << " Welcome to the hospital menu " << endl;
	char ans;
	int x1;
	int x2;
	int x3;
LOOP:
	cout << " Enter 1 to go to the * Patient Management section * " << endl;
	cout << " Enter 2 to go to the * Phisician Management section * " << endl;
	cout << " Enter 3 to exit .-." << endl;
	cout << " ";
	cin >> x1;
	if (x1 == 3)
	{
		cin.get();
		return 0;
	}
	while (x1 != 1 && x1 != 2)
	{
		cout << " The number entered is incorrect!" << endl;
		cout << " Try again : ";
		cin >> x1;
	}
	if (x1 == 1) {
		cout << " *Welcome to Patient Management*" << endl;
		cout << " Enter 1 to Insert a new patient" << endl;
		cout << " Enter 2 to Remove the patient" << endl;
		cout << " Enter 3 to Edit patient information" << endl;
		cout << " Enter 4 to Showing patients to a physician" << endl;
		cout << " Enter 0 to return to the main menu" << endl;
		cout << " ";
		cin >> x2;
		if (x2 == 0)
			goto LOOP;
		while (x2<1 || x2>4) {
			cout << " The number entered is incorrect!" << endl;
			cout << " Try again : ";
			cin >> x2;
		}
		switch (x2) {
		case 1:
			new_patient();
			break;
		case 2:
			remove_patient();
			break;
		case 3:
			Edit_patient();
			break;
		case 4:
			show_patients();
			break;
		}
		cout << " Return to main menu (y or n) :";
		cin >> ans;
		if (ans == 'y')
			goto LOOP;
	}//end of if
	else if (x1 == 2) {
		cout << " *Welcome to the *Physician Management section*" << endl;
		cout << " Enter 1 to Insert new doctor" << endl;
		cout << " Enter 2 to Remove the doctor" << endl;
		cout << " Enter 3 to Edit physician information" << endl;
		cout << " Enter 4 to Find a doctor" << endl;
		cout << " Enter 5 to Show the list of doctors" << endl;
		cout << " Enter 0 to return to the main menu" << endl;
		cout << " ";
		cin >> x3;
		if (x3 == 0)
			goto LOOP;
		while (x3<1 || x3>5) {
			cout << " The number entered is incorrect!" << endl;
			cout << " Try again : ";
			cin >> x3;
		}
		switch (x3) {
		case 1:
			new_doctor();
			break;
		case 2:
			remove_doctor();
			break;
		case 3:
			Edit_doctor();
			break;
		case 4:
			doctor_search();
			break;
		case 5:
			show_doctors();
			break;
		}
		cout << " Return to main menu (y or n) :";
		cin >> ans;
		if (ans == 'y')
			goto LOOP;
	}//end of else if

	cin.get();
	return 0;
}
/*--------------------*/
bool pass() {
	string x;//for the username
	string y;//for the password
	string temp;
	string temp2;
	ifstream passfile("pass.txt", ios::in);
	if (!passfile) {
		cout << " could not open the file! (for password)" << endl;
		return 0;
	}

	for (int i = 0; i < 3; i++) {
		cout << " Please Enter username and password :";
		cin >> x >> y;
		passfile >> temp >> temp;
		passfile >> temp2 >> temp2;
		if (temp == x && temp2 == y) {
			passfile.close();
			return 1;
		}
		else
		{
			if (i == 2)
				break;
			cout << " Error , Try again" << endl;
		}
	}
	return 0;
}
/*--------------------*/
void new_patient() {
	char ch;
	string temp;
	ofstream patientsfile("patients.txt", ios::app);
	if (!patientsfile) {
		cout << " could not open the file!(insert patient)" << endl;
		return;
	}
	while (true) {
		cout << " Enter patient information" << endl;
		cout << " patientcode : ";
		cin >> temp;
		patientsfile << temp << "  ";
		cout << " first name : ";
		cin >> temp;
		patientsfile << temp << "  ";
		cout << " last name : ";
		cin >> temp;
		patientsfile << temp << "  ";
		cout << " phone number (11 digits) : ";
		cin >> temp;
		patientsfile << temp << "  ";
		cout << " doctorcode : ";
		cin >> temp;
		patientsfile << temp << "  " << endl;
		cout << " Do you want to continue?(y or n) ";
		cin >> ch;
		if (ch == 'n')
			break;
	}
	patientsfile.close();
}
/*--------------------*/
void remove_patient() {
	ifstream readfile("patients.txt", ios::in);
	if (!readfile) {
		cout << " could not open the file!(for remove patient)" << endl;
		return;
	}
	ofstream writefile("data.txt", ios::app);
	if (!writefile) {
		cout << " could not open the file !(for remove patient)" << endl;
		return;
	}
	string temp;
	string code;
	string str = "";
	int i = 0;
	cout << " Enter the patient code to remove it : ";
	cin >> code;
	while (readfile >> temp)
	{
		if (temp != code)
		{
			str = str + temp + "  ";
			i++;
			if (i % 5 == 0)
				str = str + "\n";
		}
		else
			readfile >> temp >> temp >> temp >> temp;
	}
	writefile << str;
	readfile.close();
	writefile.close();
	remove("patients.txt");
	rename("data.txt", "patients.txt");
}
/*--------------------*/
void Edit_patient() {
	ifstream input("patients.txt", ios::app);
	if (!input) {
		cout << " could not open the file!(for edit patient)" << endl;
		return;
	}
	ofstream output("temp.txt", ios::app);
	if (!output) {
		cout << " could not open the file!(for edit patient)" << endl;
		return;
	}
	string thecode;
	cout << " Enter the patient code to edit the information :";
	cin >> thecode;
	while (input >> X.patientcode)
	{
		input >> X.firstname >> X.lastname >> X.number >> X.doctorcode;
		if (thecode == X.patientcode) {
			cout << " patientcode : ";
			cin >> X.patientcode;
			cout << " first name : ";
			cin >> X.firstname;
			cout << " last name : ";
			cin >> X.lastname;
			cout << " phone number : ";
			cin >> X.number;
			cout << " doctor code : ";
			cin >> X.doctorcode;
		}
		output << X.patientcode << "  " << X.firstname << "  " << X.lastname << "  " << X.number << "  " << X.doctorcode << endl;
	}
	output.close();
	input.close();
	remove("patients.txt");
	rename("temp.txt", "patients.txt");
}
/*--------------------*/
void bubblesort1() {
	file_to_struct();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (sick[j].patientcode > sick[j + 1].patientcode) {
				patients temp = sick[j];
				sick[j] = sick[j + 1];
				sick[j + 1] = temp;
			}
		}
	}
}
/*--------------------*/
void show_patients() {
	bubblesort1();
	string cod;
	int flag = 0;
	cout << " Enter the doctor code to showing their patients : ";
	cin >> cod;
	for (int i = 0; i < n; i++) {
		if (cod == sick[i].doctorcode) {
			flag++;
			if (flag == 1) {
				cout << " " << "patientcode      " << "firstname        " << "lastname          " << "phone number     " << endl;
				cout << "-------------------------------------------------------------------------------" << endl;
			}
			cout << " " << left << setw(17) << sick[i].patientcode;
			cout << left << setw(18) << sick[i].firstname;
			cout << left << setw(17) << sick[i].lastname;
			cout << left << setw(18) << sick[i].number << endl;
		}
	}
	if (flag == 0)
		cout << " your code not found!!" << endl;
}
/*--------------------*/
void new_doctor() {
	char ch;
	string temp;
	ofstream doctorsfile("physicians.txt", ios::app);
	if (!doctorsfile) {
		cout << " could not open the file!" << endl;
		return;
	}
	while (true) {
		cout << " Enter physician information" << endl;
		cout << " doctorcode : ";
		cin >> temp;
		doctorsfile << temp << "  ";
		cout << " firstname : ";
		cin >> temp;
		doctorsfile << temp << "  ";
		cout << " lastname : ";
		cin >> temp;
		doctorsfile << temp << "  ";
		cout << " phone number (11 digits) :";
		cin >> temp;
		doctorsfile << temp << "  ";
		cout << " specialty field : ";
		cin >> temp;
		doctorsfile << temp << "  " << endl;
		cout << " Do you want to continue?(y or n) ";
		cin >> ch;
		if (ch == 'n')
			break;
	}
	doctorsfile.close();
}
/*---------------------*/
void remove_doctor() {
	//remove doctor
	ifstream readfile("physicians.txt", ios::in);
	if (!readfile) {
		cout << " could not open the file!" << endl;
		return;
	}
	ofstream writefile("data.txt", ios::app);
	if (!writefile) {
		cout << " could not open the file!" << endl;
		return;
	}
	string temp;
	string code;
	string str = "";
	int i = 0;
	cout << " Enter the doctor code to remove it : ";
	cin >> code;
	while (readfile >> temp)
	{
		if (temp != code)
		{
			str = str + temp + "  ";
			i++;
			if (i % 5 == 0)
				str = str + "\n";
		}
		else
			readfile >> temp >> temp >> temp >> temp;

	}
	writefile << str;
	readfile.close();
	writefile.close();
	remove("physicians.txt");
	rename("data.txt", "physicians.txt");
	//remove their patients
	ifstream file1("patients.txt", ios::app);
	if (!file1) {
		cout << " could not open the file!(for remove patients)" << endl;
		return;
	}
	ofstream file2("information.txt", ios::app);
	if (!file2) {
		cout << " could not open the file!(for remove patients)" << endl;
		return;
	}
	while (file1 >> Y.patientcode) {
		file1 >> Y.firstname >> Y.lastname >> Y.number >> Y.doctorcode;
		if (Y.doctorcode == code) {
			continue;
		}
		file2 << Y.patientcode << "  " << Y.firstname << "  " << Y.lastname << "  " << Y.number << "  " << Y.doctorcode << endl;
	}
	file2.close();
	file1.close();
	remove("patients.txt");
	rename("information.txt", "patients.txt");
}
/*--------------------*/
void Edit_doctor() {
	file_to_struct2();
	string cod;
	while (true) {
		int flag = 0;
		cout << " Enter the physician code to edit the information : ";
		cin >> cod;
		for (int i = 0; i < f; i++) {
			if (cod == doctors[i].doctorcode) {
				cout << " firstname :";
				cin >> doctors[i].firstname;
				cout << " lastname : ";
				cin >> doctors[i].lastname;
				cout << " phone number : ";
				cin >> doctors[i].num;
				cout << " specialty field : ";
				cin >> doctors[i].specialty;
				flag = -1;
			}
		}
		if (flag == 0)
			cout << " your code not found!!" << endl;
		char ans;
		cout << " Do you want to continue?(y or n)";
		cin >> ans;
		if (ans == 'n')
			break;
	}
	ofstream output("x.txt", ios::app);
	if (!output) {
		cout << " could not open the file!(for edit doctor)" << endl;
		return;
	}
	for (int i = 0; i < f; i++) {
		output << doctors[i].doctorcode << "  " << doctors[i].firstname << "  " << doctors[i].lastname << "  " << doctors[i].num << "  " << doctors[i].specialty << endl;
	}
	output.close();
	remove("physicians.txt");
	rename("x.txt", "physicians.txt");
}
/*-------------------*/
void doctor_search() {
	file_to_struct2();
	string m;
	cout << " Enter your doctor's code : ";
	cin >> m;
	for (int h = 0; h < f; h++) {
		if (m == doctors[h].doctorcode) {
			cout << " doctorcode : " << doctors[h].doctorcode << endl;
			cout << " firstname : " << doctors[h].firstname << endl;
			cout << " lastname : " << doctors[h].lastname << endl;
			cout << " phone number : " << doctors[h].num << endl;
			cout << " specialty field : " << doctors[h].specialty << endl;
			break;
		}
	}
}
/*-----------------*/
void bubblesort2() {
	file_to_struct2();
	for (int i = 0; i < f - 1; i++) {
		for (int j = 0; j < f - i - 1; j++) {
			if (doctors[j].lastname > doctors[j + 1].lastname) {
				physician temp = doctors[j];
				doctors[j] = doctors[j + 1];
				doctors[j + 1] = temp;

			}
		}
	}
}
/*---------------------*/
void show_doctors() {
	bubblesort2();
	cout << " firstname      " << "lastname       " << "doctor code      " << "phone number      " << "specialty field    " << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < f; i++) {
		cout << " " << left << setw(16) << doctors[i].firstname;
		cout << left << setw(16) << doctors[i].lastname;
		cout << left << setw(16) << doctors[i].doctorcode;
		cout << left << setw(18) << doctors[i].num;
		cout << left << setw(20) << doctors[i].specialty << endl;
	}
}
/*-----------------------*/
void file_to_struct() {
	ifstream file("patients.txt", ios::in);
	if (!file) {
		cout << " could not open file!()" << endl;
		return;
	}
	int i = 0;
	while (file >> sick[i].patientcode) {
		file >> sick[i].firstname;
		file >> sick[i].lastname;
		file >> sick[i].number;
		file >> sick[i].doctorcode;
		i++;

	}
	file.close();
	n = i;
}
/*--------------------*/
void file_to_struct2() {
	ifstream myfile("physicians.txt", ios::in);
	if (!myfile) {
		cout << " could not open file!()" << endl;
		return;
	}
	int i = 0;
	while (myfile >> doctors[i].doctorcode) {
		myfile >> doctors[i].firstname;
		myfile >> doctors[i].lastname;
		myfile >> doctors[i].num;
		myfile >> doctors[i].specialty;
		i++;

	}
	myfile.close();
	f = i;
}
