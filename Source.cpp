#include<iostream>
#include<string>
#include<fstream>
using namespace std;


//Files Name 
const string patientFile = "Patients_Record.txt";
const string doctorFile = "Doctors_Record.txt";
const string adminFile = "Admin_Record.txt";
const string apptFile = "Appointments_Record.txt";
const string roomFile = "Rooms_Record.txt";
const string recordFile = "Medical_Records.txt";
const string billFile = "Bills_Record.txt";
const string authFile = "Users_Credentials.txt";
//===========================================
//1.Person Classs
//Abstract Class and Pure Virtual Function
//===========================================

class Person {

	//Encapsulation : Data is Private
	string name;
	int age;
	string address;
	string phoneNumber;
public:

	//Default Constructor
	Person():name(" "),age(0),address(" "),phoneNumber(" "){}

	//Perametrized Constructor

	Person(string n, int a, string addr, string phon) {
		name = n;
		age = a;
		address = addr;
		phoneNumber = phon;
	}

	//Setters

	void setName(string n) {
		name = n;
	}
	void setAge(int a) {
		age = a;
	}
	void setAddress(string addr) {
		address = addr;
	}
	void setPhoneNumber(string phon) {
		phoneNumber = phon;
	}

	//Getters

	string getName()const {
		return name;
	}
	int getAge()const {
		return age;
	}
	string getAddress()const {
		return address;
	}
	string getPhoneNumber()const {
		return phoneNumber;
	}


	// Pure Virtual Function (Makes this class Abstract)
    // Polymorphism: Every child MUST define how to display their details
	virtual void display() = 0;

};




//===========================================
//1.Patient Classs
// Inheritance: Derived from Person
//===========================================

class Patient :public Person {
	// Encapsulation: Data is private
	string patientId;
	string bloodGroup;
	string dateOfAdmission;
	string username;
	string password;

	string medicalHistory[50];
	int historyCount;
public:
	//Default Constructor
	Patient() :Person(), patientId(" "), bloodGroup(" "), dateOfAdmission(" "),username(" "),password(" ") {
		historyCount = 0;
	}
	//Perametrized Constructor
	Patient(string n, int a, string addr, string phon,
		string pId, string bGroup, string doa,string user,string pass)
		:Person(n, a, addr, phon) {
		patientId = pId;
		bloodGroup = bGroup;
		dateOfAdmission = doa;
		historyCount = 0;
		username = user;
		password = pass;
	}

	//Setters

	void setPatientId(string pId) {
		patientId = pId;
	}
	void setBloodGroup(string bGroup) {
		bloodGroup = bGroup;
	}
	void setDateOfAdmission(string doa) {
		dateOfAdmission = doa;
	}
	void setUsername(string user) {
		username = user;
	}
	void setpassword(string pass) {
		password = pass;
	}

	//Getters
	string getPatientId()const {
		return patientId;
	}
	string getBloodGroup()const {
		return bloodGroup;
	}
	string getDateOfAdmission()const {
		return dateOfAdmission;
	}
	int getHistoryCount() const {
		return historyCount;
	}
	string getUsername()const {
		return username;
	}
	string getPassword()const {
		return password;
	}

	//Its just a simple function that display success after patient Register.
	void Register() {
		cout << "=========Patient Register Successfully.=========" << endl;
		cout << "Patient Name:" << getName() << endl;
		cout << "Patient ID:" << patientId << endl;
	}


	//Function to add Medical History
	void addMedicalHistory(string record) {
		if (historyCount < 50) {
			medicalHistory[historyCount] = record;
			historyCount++;
		}
		else {
			cout << "Medical history is full. Cannot add more records." << endl;
		}
	}

	//for file handling
	string getHistoryItem(int index) const {
		if (index >= 0 && index < historyCount) {
			return medicalHistory[index];
		}
		return "";
	}

	//Function to get Medical History

	void getMedicalHistory() {
		cout << "=========Medical History for " << " " << getName()<<"=========" << endl;
		if (historyCount == 0) {
			cout << "No Record Found." << endl;
		}
		else {
			for(int i=0;i<historyCount;i++){
				cout << i + 1 << ". " << medicalHistory[i] << endl;
			}
		}
	}


	void saveData() {
		ofstream ofile(patientFile, ios::app);
		if (ofile.is_open()) {
			ofile << getName() << endl;
			ofile << getAge() << endl;
			ofile << getAddress() << endl;
			ofile << getPhoneNumber() << endl;
			ofile << patientId << endl;
			ofile << bloodGroup << endl;
			ofile << dateOfAdmission << endl;
			ofile << username << endl;
			ofile << password << endl;
			ofile << historyCount << endl;
			for (int i = 0; i < historyCount; i++) {
				ofile << medicalHistory[i] << endl;
			}
			ofile.close();
		}
		else {
			cout << "Error! While opening the"<<" " << patientFile<<"." << endl;
		}
	}



	bool loadFromFile(ifstream& inFile) {
		string n, addr, ph, pid, bg, doa, hist,user,pass;
		int a, tempCount;

		if (!getline(inFile, n)) return false;

		setName(n);
		inFile >> a;
		inFile.ignore();
		setAge(a);
		getline(inFile, addr);
		setAddress(addr);
		getline(inFile, ph); 
		setPhoneNumber(ph);
		getline(inFile, pid);
		setPatientId(pid);
		getline(inFile, bg);   
		setBloodGroup(bg);
		getline(inFile, doa); 
		setDateOfAdmission(doa);
		getline(inFile, user);
		username = user;
		getline(inFile, pass);
		password = pass;

		inFile >> tempCount; inFile.ignore();
		historyCount = 0;
		for (int i = 0; i < tempCount; i++) {
			getline(inFile, hist);
			addMedicalHistory(hist);
		}
		return true;
	}





	// Overriding displayInfo() from Person

	void display() {
		cout << "=========Patient Whole Details.=========" << endl;
		cout << "Patient Name:" << getName() << endl;
		cout << "Patient Age:" << getAge() << endl;
		cout << "Patient Address:" << getAddress() << endl;
		cout << "Patient Phone Number:" << getPhoneNumber() << endl;
		cout << "Patient ID:" << patientId << endl;
		cout << "Patient Blood group:" << bloodGroup << endl;
		cout << "Patient Date_Of_Admission:" << dateOfAdmission << endl;
	}

};





//===========================================
//1.Employee Classs
// Inheritance: Derived from Person
//===========================================


class Employee:public Person {
	// Encapsulation: Data is private
	string employeeId;
	double salary;
	string dateOfJoining;
public:
	//Default Constructor
      Employee():Person(),employeeId(" "),salary(0),dateOfJoining(" "){}

   //Perameterized Constructor
	  Employee(string n, int ag, string addr, string pho,   
		  string eid, double sa, string doj)
		  :Person(n,ag,addr,pho) {
		  employeeId = eid;
		  salary = sa;
		  dateOfJoining = doj;
	  }

	  //Setters
	  void setEmployeeId(string eid) {
		  employeeId = eid;
	  }
	  void setSalary(double sa) {
		  salary = sa;
	  }
	  void setDateOfJoining(string doj) {
		  dateOfJoining = doj;
	  }

	  //Getters
	  string getEmployeeId()const {
		  return employeeId;
	  }
	  double getSalary()const {
		  return salary;
	  }
	  string getDateOfJoining()const {
		  return dateOfJoining;
	  }


	  //Virtual Function
	  // "virtual" means: "If a child class has a better version of this, use that one instead."
	  virtual double calculateSalary() {
		  return salary;
	  }


	  

	  // Overriding displayInfo() from Person

	  void display() {
		  cout << "=========Employee Whole Details.=========" << endl;
		  cout << "Employee Name:" << getName() << endl;
		  cout << "Employee Age:" << getAge() << endl;
		  cout << "Employee Address:" << getAddress() << endl;
		  cout << "Employee Phone Number:" << getPhoneNumber() << endl;
		  cout << "Employee ID:" << employeeId << endl;
		  cout << "Employee Salary:" << salary << endl;
		  cout << "Employee Date_Of_Joining:" << dateOfJoining << endl;
	  }



};








//===========================================
//4.Doctor Class
// Inheritance: Derived from Employee
//===========================================

class Doctor :public Employee {
	// Encapsulation: Data is private
	string username;
	string specialization;
	string licenseNumber;
	string scheduale;
	string password;
public:
	//Default Constructor
	Doctor():Employee(),specialization(" "),licenseNumber(" "),scheduale(" "),username(" "),password(" ") {}

	//Paramterized Constructor
	Doctor(string n, int ag, string addr, string pho,
		string eid, double sa, string doj,
		string spec, string ln, string sched,string user,string pass) :Employee(n, ag, addr, pho, eid, sa, doj) {
		specialization = spec;
		licenseNumber = ln;
		scheduale = sched;
		username = user;
		password = pass;
	}

	//setters
	void setSpecialization(string spec) {
		specialization = spec;
	}
	void setLicenseNumber(string ln) {
		licenseNumber = ln;
	}
	void setScheduale(string sched) {
		scheduale = sched;
	}
	void setUserName(string user) {
		username = user;
	}
	void setPassword(string pass) {
		password = pass;
	}

	//Getters
	string getSpecialization()const {
		return specialization;
	}
	string getLicenseNumber()const {
		return licenseNumber;
	}
	string getSchedual()const {
		return scheduale;
	}
	string getUserName()const {
		return username;
	}
	string getPassword()const {
		return password;
	}

	void addDiagnosis(string patientName,string diagnose) {
		cout << "Dr." << getName() << " (" << specialization << ")" << " " << "Reports:" << endl;
		cout << "Patient:" << patientName << endl;
		cout << "Diagnosis:" << diagnose << endl;
		cout << "Saved to Medical Records." << endl;
	}


	void viewSchedual() {
		cout << "Schedual for Dr." << getName() << " :" << endl;
		cout << "Availablity:" << " " << scheduale << endl;
	}


	// 5. Overriding calculateSalary (Polymorphism)
	// Doctors might get a 20% bonus allowance on top of base salary

	double calculateSalary() {
		double base = getSalary();
		return base + (base * 0.20);
	}


	

	void saveToFile() {
		ofstream ofile(doctorFile, ios::app);
		if (ofile.is_open()) {
			ofile << getName() << endl;
			ofile << getAge() << endl;
			ofile << getAddress() << endl;
			ofile << getPhoneNumber() << endl;
			ofile << getEmployeeId() << endl;
			ofile << getSalary() << endl;
			ofile << getDateOfJoining() << endl;
			ofile << specialization << endl;
			ofile << licenseNumber << endl;
			ofile << scheduale << endl;
			ofile << username << endl;
			ofile << password << endl;
			ofile.close(); 
		}
		else {
			cout << "Error! While opening the" << " " << doctorFile << "." << endl;
		}
	}



	bool loadFile(ifstream& ifile) {
		string n, addr, ph, eid, doj, spec, lic, sch,user,pass;
		int a;
		double sal;
		if (!getline(ifile, n)) {
			return false;
		}
		else {
			setName(n);
			ifile >> a;
			ifile.ignore();
			setAge(a);
			getline(ifile, addr);
			setAddress(addr);
			getline(ifile, ph);
			setPhoneNumber(ph);
			getline(ifile, eid);
			setEmployeeId(eid);
			ifile >> sal;
			ifile.ignore(); 
			setSalary(sal);
			getline(ifile, doj);
			setDateOfJoining(doj);
			getline(ifile, spec);
			setSpecialization(spec);
			getline(ifile, lic);
			setLicenseNumber(lic);
			getline(ifile, sch);
			setScheduale(sch);
			getline(ifile, user);
			username = user;
			getline(ifile, pass);
			password = pass;
			return true;
		}
	}

	//Overriding Display
	void display() {
		cout << "Dr.Name:" << getName() << endl;
		cout << "Dr.Age:" << getAge() << endl;
		cout << "Doctor_Id:" << getEmployeeId() << endl;
		cout << "Specialization:" << specialization << endl;
		cout << "License Number #:" << licenseNumber << endl;
		cout << "Schedual:" << scheduale << endl;
		cout << "Base Salary:$" << getSalary() << endl;
		cout << "Total Salary(Including Allowance):$" << calculateSalary() << endl;
	}


};






//===========================================
//5.Admin Staff Class
// Inheritance: Derived from Employee
//===========================================

class AdminStaff :public Employee {
	// Encapsulation: Data is private
	string departmentName;

public:
	//Default Constructor
	AdminStaff() {
		departmentName = " ";
	}

	//Paramterized Constructor 
	AdminStaff(string d, string e, double s, string doj, string n, int a, string addr, string p)
		: Employee(n, a, addr, p, e, s, doj), departmentName(d) {
	}

	//setter
	void setDepName(string depName) {
		departmentName = depName;
	}

	//Getter
	string getDepName() const {
		return departmentName;
	}

	//Funtion to manage the staff
	void manageStaff() {
		cout << "Admin Staff: Managing hospital personnel for " << departmentName << ".\n";
	}

	//Funtion to handle billing
	void handleBilling() {
		cout << "Admin Staff: Processing medical invoices and billing.\n";
	}

	// 5. Overriding function "calculateSalary" (Polymorphism)
	double calculateSalary() {
		// Admin staff might have a flat 10% administrative bonus
		return getSalary() * 1.10;
	}



	void saveToFile() {
		ofstream ofile(adminFile, ios::app);
		if (ofile.is_open()) {
			ofile << getName() << endl;
			ofile << getAge() << endl;
			ofile << getAddress() << endl;
			ofile << getPhoneNumber() << endl;

			// 2. Employee Data
			ofile << getEmployeeId() << endl;
			ofile << getSalary() << endl;
			ofile << getDateOfJoining() << endl;

			// 3. Admin Specific Data
			ofile << departmentName << endl;

			ofile.close();
		}
		else {
			cout << "Error! While opening " << adminFile << endl;
		}
	}

	bool loadFromFile(ifstream& ifile) {
		string n, addr, ph, eid, doj, dept;
		int a;
		double sal;

		
		if (!getline(ifile, n)) {
			return false;
		}

		setName(n);
		ifile >> a;
		ifile.ignore();
		setAge(a);

		getline(ifile, addr);
		setAddress(addr);
		getline(ifile, ph);  
		setPhoneNumber(ph);

		getline(ifile, eid);  
		setEmployeeId(eid);
		ifile >> sal;
		ifile.ignore();
		setSalary(sal);

		getline(ifile, doj); 
		setDateOfJoining(doj);

		
		getline(ifile, dept); departmentName = dept;

		return true;
	}


	//Overriding function "display"
	void display() {
		cout << "=========Admin Staff Details=========" << endl;
		cout << "Name: " << getName() << " | ID: " << getEmployeeId() << endl;
		cout << "Department: " << departmentName << " | Salary: $" << calculateSalary() << endl;
		cout << "Date of joining: " << getDateOfJoining() << endl;
		cout << "Base Salary: $" << getSalary() << endl;
		cout << "Total Salary: $" << calculateSalary() << endl;
	}
};





//===========================================
//6.Appointment
// Composition: Links Patient and Doctor
//===========================================

class Appointment {
	// Encapsulation: Data is private
	string appointmentID;
	string date;
	string time;
	string status;
	Patient patient;
	Doctor doctor;

public:

	//Default Constructor
	Appointment():patient(),doctor() {
		appointmentID = " ";
		date = " ";
		time = " ";
		status = "Available";
	}

	//Paramterized Constructor
	Appointment(string a, string d, string t, string s, Patient p, Doctor doc)
		: appointmentID(a), date(d), time(t), status(s), patient(p), doctor(doc) {
	}


	// Setters
	void setAppointmentID(string a) {
		appointmentID = a;
	}

	void setDate(string d) {
		date = d;
	}

	void setTime(string t) {
		time = t;
	}

	void setStatus(string s) {
		status = s;
	}

	void setPatient(const Patient& p) {
		patient = p;
	}

	void setDoctor(const Doctor& d) {
		doctor = d;
	}


	//Getters
	string getAppointmentID() const {
		return appointmentID;
	}

	string getDate() const {
		return date;
	}

	string getTime() const {
		return time;
	}

	string getStatus() const {
		return status;
	}

	Patient getPatient() const {
		return patient;
	}

	Doctor getDoctor() const {
		return doctor;
	}




	//Funtion to book appointment
	void bookAppointment() {
		status = "Confirmed";
		cout << "Appointment " << appointmentID << " booked successfully for Patient: " << patient.getName() << endl;
	}


	//Funtion to cancel appointment
	void cancelAppointment() {
		if (status == "Booked") {
			status = "Cancelled";
			cout << ">> Appointment [" << appointmentID << "] has been cancelled." << endl;
		}
		else {
			cout << ">> Error: Appointment is not currently booked." << endl;
		}
	}



	void saveToFile() {
		ofstream ofile(apptFile, ios::app);
		if (ofile.is_open()) {
			ofile << appointmentID << endl;
			ofile << date << endl;
			ofile << time << endl;
			ofile << status << endl;
			ofile << patient.getName() << endl;
			ofile << doctor.getName() << endl;
			ofile.close();
			cout<< "Appointment data Saved Successfully." << endl;
		}
		else {
			cout << "Error opening file!" << endl;
		}
	}


	bool loadFile(ifstream& ifile) {
		string id, d, t, s, pName, dName;
		if (!getline(ifile, id)) {
			return false;
		}
		else {
			appointmentID = id;
			getline(ifile, d);
			date = d;
			getline(ifile, t);
			time = t;
			getline(ifile, s);
			status = s;
			getline(ifile, pName);
			patient.setName(pName);
			getline(ifile, dName);
			doctor.setName(dName);
			return true;
		}
	}




	void display() {
		cout << "Appointment ID: " << appointmentID<<endl;
		cout << "Status: " << status << endl;
		cout << "Date: " << date << " at " << time << endl;
		cout << "Patient: " << patient.getName() << endl;
		cout << "Doctor: " << doctor.getName() << endl;
	}
};




//===========================================
//7.Room
// Standalone
//===========================================

class Room {
	// Encapsulation: Data is private
	string roomNumber;
	string roomType;
	bool isOccupied;

public:

	//default constructors
	Room() {
		roomNumber = " ";
		roomType = " ";
		isOccupied = false;
	}

	//Paramterized Constructor 

	Room(string n, string t, bool i)
		: roomNumber(n), roomType(t), isOccupied(i) {
	}


	//setters
	void setRoomNumber(string n) {
		roomNumber = n;
	}

	void setRoomType(string t) {
		roomType = t;
	}

	void setIsOccupied(bool i) {
		isOccupied = i;
	}


	//Getters
	string getRoomNumber() const {
		return roomNumber;
	}

	string getRoomType() const {
		return roomType;
	}

	bool getIsOccupied() const {
		return isOccupied;
	}



	//Funtion to book appointment
	void checkAvailability() {
		if (!isOccupied)
			cout << "Room " << roomNumber << " (" << roomType << ") is Available."<<endl;

		else
			cout << "Room " << roomNumber << " is currently Occupied."<<endl;
	}

	//Funtion to cancel appointment
	void assignPatient(string patientName) {
		if (!isOccupied) {
			isOccupied = true;
			cout << ">> Success: Patient " << patientName << " assigned to Room " << roomNumber << "." << endl;
		}
		else {
			cout << ">> Error: Room " << roomNumber << " is already occupied!" << endl;
		}
	}


	void saveFile() {
		ofstream ofile(roomFile, ios::app);
		if (ofile.is_open()) {
			ofile << roomNumber << endl;
			ofile << roomType<<endl;
			ofile << isOccupied << endl;
		    ofile.close();
			cout << "Room Data Saved Successfully." << endl;
		}
		else {
			cout << "Error opening " << roomFile << endl;
		}
	}

	bool loadFile(ifstream& ifile) {
		string rNum, rType;
		bool status;
		if (!getline(ifile,rNum)) {
			return false;
		}
		else {
			roomNumber = rNum;
			getline(ifile, rType);
			roomType = rType;
			ifile >> status;
			ifile.ignore();
			isOccupied = status;
			return true;
		}
	}



	void display() {
		cout << "Room No: " << roomNumber << endl;
		cout << " Type: " << roomType<<endl;
		cout << " Status: " << (isOccupied ? "Occupied" : "Vacant") << endl;
	}
};





//===========================================
//8. MedicalRecord Class
// Association: Linked to Patient
//===========================================

class MedicalRecord {
	// Encapsulation: Data is private
	string recordID;
	string diagnosis;
	string prescription;
	string date;

	string patientName;
	string patientID;

public:

	//Default Constructor
	MedicalRecord() {
		recordID = " ";
		diagnosis = " ";
		prescription = " ";
		date = " ";
		patientName = " ";
		patientID = " ";
	}

	// Parameterized Constructor
	MedicalRecord(string r, string d, string p, string dat, string pName, string pID)
		: recordID(r), diagnosis(d), prescription(p), date(dat),patientName(pName),patientID(pID)  {
	}
	


	//Setters
	void setRecordID(string r) {
		recordID = r;
	}

	void setDiagnosis(string d) {
		diagnosis = d;
	}

	void setPrescription(string p) {
		prescription = p;
	}

	void setDate(string d) {
		date = d;
	}

	void setPatientName(string pName) {
		patientName = pName;
	}
	void setPatientId(string pID) {
		patientID = pID;
	}


	//Getters
	string getRecordID() const {
		return recordID;
	}

	string getDiagnosis() const {
		return diagnosis;
	}

	string getPrescription() const {
		return prescription;
	}

	string getDate() const {
		return date;
	}

	

	void addEntry(string id, string diag, string rx, string d, Patient& p) {
		recordID = id;
		diagnosis = diag;
		prescription = rx;
		date = d;

		patientName = p.getName();
		patientID = p.getPatientId();

		cout << " Success: Medical Record [" << recordID << "] added for " << patientName << "." << endl;
	}
	void getRecordByDate(string d) {
		if (date == d)
			display();

		else
			cout << "No record found for date: " << d << endl;
	}


	void saveFile() {
		ofstream ofile(recordFile, ios::app);
		if (ofile.is_open()) {
			ofile << recordID << endl;
			ofile << diagnosis << endl;
			ofile << prescription << endl;
			ofile << date << endl;
			ofile << patientName << endl;
			ofile << patientID << endl;
			ofile.close();

			cout << "Record Saved Successfully." << endl;
		}
		else {
			cout << "Error opening " << recordFile << endl;
		}
	}



	bool loadFile(ifstream& ifile) {
		string ri, d, pre, dat, pName, pID;
		if (!getline(ifile, ri)) {
			return false;
		}
		else {
			recordID = ri;
			getline(ifile, d);
			diagnosis = d;
			getline(ifile, pre);
			prescription = pre;
			getline(ifile, dat);
			date = dat;
			getline(ifile, pName);
			patientName = pName;
			getline(ifile, pID);
			patientID = pID;
			return true;
		}
	}



	void display() {
		cout << "========= Medical Record [" << date << "] =========" << endl;
		cout << "ID: " << recordID << endl;
		cout << "Patient: " << patientName << " (ID: " << patientID << ")" << endl;
		cout << "Diagnosis: " << diagnosis << endl;
		cout << "Prescription: " << prescription << endl;
		cout << "===========================================" << endl;
	}
};





//===========================================
//9.Bill Class
// Composition (links to Patient and Room)
//===========================================

class Bill {
	// Encapsulation: Data is private

	string billId;
	double amount;
	string paymentStatus;
	string itemList[50];
	int itemCount;
	double roomCharges;//not important just add roomCharges by roomType
	Patient patient;
	Room room;

public:
	//Default Constructor

	Bill() : patient(), room() {
		billId = " ";
		amount = 0;
		paymentStatus = "Pending";
		itemCount = 0;
		paymentStatus = "Pending";
		amount = 0;
	}

	//Parametrized Constructor
	Bill(string bi, Patient p, Room r) :patient(p), room(r) {
		billId = bi;
		itemCount = 0;
		amount = 0;
		paymentStatus = "Pending";
	}

	void AddItems(string item) {
		if (itemCount < 50) {
			itemList[itemCount] = item;
			itemCount++;
			cout << "Item Added: " << item << endl;
		}
		else {
			cout << "Error: Bill is full (Max 50 items)." << endl;
		}
	}



	//setters 
	void setBillId(string bi) {
		billId = bi;
	}
	
	

	//Getters
	string getBillId()const {
		return billId;
	}
	double getAmount()const {
		return amount;
	}
	string getPaymentStatus()const {
		return paymentStatus;
	}
	string getPatientID() const {
		return patient.getPatientId();
	}

	//Genrate Bill
	void genrateBill() {
		if (room.getRoomType() == "Ward") {
			roomCharges = 600;
		}
		else if (room.getRoomType() == "ICU") {
			roomCharges = 1000;
		}
		else {
			roomCharges = 1500;
		}
		amount = itemCount * 100 + roomCharges;
		cout << "========= Bill Generated =========" << endl;
		cout << "Bill ID: " << billId << endl;
		cout << "Patient: " << patient.getName() << endl;
		cout << "Room Type: " << room.getRoomType() << endl;
		cout << "Room Charges: $" << roomCharges << endl;
		cout << "Items (" << itemCount << "): ";
		for (int i = 0; i < itemCount; i++) {
			cout << itemList[i];
			if (i != itemCount - 1) cout << ", ";
		}
		cout << "Total Amount: $" << amount << endl;
		cout << "===========================================" << endl;

	}
	void makePayment() {
		if (room.getRoomType() == "Ward") {
			roomCharges = 600;
		}
		else if (room.getRoomType() == "ICU") {
			roomCharges = 1000;
		}
		else {
			roomCharges = 1500;
		}
		double amou;
		amou = 100 + roomCharges;
		if (paymentStatus == "Pending") {
			paymentStatus = "Paid";
			cout << "=========Payment Receipt=========" << endl;
			cout << "Success: Payment of $" << amou << " received." << endl;
			cout << "Bill ID: " << billId << endl;
			cout << "Patient Name:" << patient.getName();
			cout << "Amount Paid: $" << amou << endl;
			cout << "===========================================" << endl;

		}
		else {
			cout << "This bill is already paid." << endl;
		}
	}
	void display() {
		cout << "========= Hospital Bill [" << billId << "] =========" << endl;
		cout << "Patient: " << patient.getName() << " (ID: " << patient.getPatientId() << ")" << endl;
		cout << "Room: " << room.getRoomNumber() << " (" << room.getRoomType() << ")" << endl;

		cout << "========= Items List =========" << endl;
		if (itemCount == 0) {
			cout << "(No items added)" << endl;
		}
		else {
			for (int i = 0; i < itemCount; i++) {
				cout << itemList[i];
				if (i != itemCount - 1) cout << ", ";
			}
		}
		cout << endl;

		cout << "===========================================" << endl;
		cout << "Total Amount: $" << amount << endl;
		cout << "Status: " << paymentStatus << endl;
		cout << "===========================================" << endl;
	}

	void saveFile() {
		ofstream ofile(billFile, ios::app);
		if (ofile.is_open()) {
			ofile << billId << endl;
			ofile << amount << endl;
			ofile << paymentStatus << endl;
			ofile << itemCount << endl;
			ofile << roomCharges << endl;
			ofile << patient.getName() << endl;
			ofile << patient.getPatientId() << endl;
			ofile << room.getRoomNumber() << endl;
			ofile << room.getRoomType() << endl;
			for (int i = 0; i < itemCount; i++) {
				ofile << itemList[i] << endl;
			}
			ofile.close();
			cout << "Bill Saved Successfully." << endl;
		}
		else {
			cout << "Error opening " << billFile << endl;
		}
	}

	bool loadFile(ifstream& ifile) {
		string id, status, pName, pid, rNum, rType, item;
		double amt, rc;
		int count;
		if (!getline(ifile, id)) {
			return false;
		}
		else {
			billId = id;
			ifile >> amt;
			ifile.ignore();
			amount = amt;
			getline(ifile, status);
			paymentStatus = status;
			ifile >> count;
			ifile.ignore();
			itemCount = 0;
			ifile >> rc;
			ifile.ignore();
			roomCharges = rc;
			getline(ifile, pName);
			patient.setName(pName);
			getline(ifile, pid);
			patient.setPatientId(pid);
			getline(ifile, rNum);
			room.setRoomNumber(rNum);
			getline(ifile, rType);
			room.setRoomType(rType);
			for (int i = 0; i < count; i++) {
				getline(ifile, item);
				AddItems(item);
			}
			return true;
		}

	}



};




//===========================================
//10.Hospital Class
// Aggregation (holds lists of other objects)
//===========================================

class Hospital {
	// Encapsulation: Data is private
	Patient* patient[100];
	int pCount;
	Doctor* doctor[50];
	int dCount;
	Room* room[50];
	int rCount;
	AdminStaff* staff[100];
	int eCount;
public:
	//Default Constructor
	Hospital(){
		pCount = 0;
		dCount = 0;
		rCount = 0;
		eCount = 0;
	}

	

	void addDoctor(Doctor* d) {
		if (dCount < 50) {
			doctor[dCount] = d;
			dCount++;
			d->saveToFile();
				
			cout << "Success: Doctor " << d->getName() << " added to system and saved to file." << endl;
			
			
		}
		else {
			cout << "Error: Doctor Limit Reached." << endl;
		}
	}

	void viewAllDoctors() {
		ifstream ifile(doctorFile);
		if (!ifile.is_open()) {
			cout << "Error: No doctor records found (File missing)." << endl;
			return;
		}
		cout << "=========All Doctors=========" << endl;
		Doctor tempDoc;
		int count = 0;
		while (tempDoc.loadFile(ifile)) {
			count++;
			cout << "Doctor:" << count << endl;
			tempDoc.display();
			cout << "===========================================" << endl;
		}
		if (count == 0) {
			cout << "The File is Empty." << endl;
		}
		ifile.close();

	}



	void addPatient(Patient* p) {
		if (pCount < 100) {
			patient[pCount] = p;
			pCount++;
			p->saveData();
			cout << " Patient " << p->getName() << " added to Hospital system." << endl;

		}
		else {
			cout << "Patient Limit Reached" << endl;

		}
	}



	void viewAllPatient() {
		ifstream ifile(patientFile);
		if (!ifile.is_open()) {
			cout << "Error: No Patient records found (File missing)." << endl;
			return;
		}
		cout << "=========All Patients=========" << endl;
		Patient patient;
		int count = 0;
		while (patient.loadFromFile(ifile)) {
			count++;
			cout << "Patient:" << count << endl;
			patient.display();
			cout << "===========================================" << endl;
		}
		if (count == 0) {
			cout << "The File is Empty." << endl;
		}
		ifile.close();
	}

	void viewAllAppointments() {
		ifstream ifile(apptFile);
		if (!ifile.is_open()) {
			cout << "Error: No Appointment records found (File missing)." << endl;
			return;
		}
		cout << "=========All Appointments=========" << endl;
		Appointment appoint;
		int count = 0;
		while (appoint.loadFile(ifile)) {
			count++;
			cout << "Appointment" << count << endl;
			appoint.display();
			cout << "===========================================" << endl;
		}
		if (count == 0) {
			cout << "The File is Empty." << endl;
		}
		ifile.close();
	}

	void addRoom(Room* r) {
		if (rCount < 50) {
			room[rCount] = r;
			rCount++;
			r->saveFile();
			cout << "Room:" << r->getRoomType() << " " << "Added to the Hospital System." << endl;
		}
		else {
			cout << "Romms Limit Reached" << endl;
		}
	}

	void addEmployee(AdminStaff* a) {
		if (eCount < 100) {
			staff[eCount] = a;
			eCount++;
			a->saveToFile();
			cout << " Employee " << a->getName() << " added to Hospital system." << endl;
		}
		else {
			cout << "Employee Limit Reached" << endl;
		}
	}

	void viewAllEmployes() {
		ifstream ifile(adminFile);
		if (!ifile.is_open()) {
			cout << "Error: No Employee records found (File missing)." << endl;
			return;
		}
		AdminStaff adm;
		int count = 0;
		while (adm.loadFromFile(ifile)) {
			count++;
			cout << "Employee:" << count;
			adm.display();
			cout << "===========================================" << endl;
		}
		if (count == 0) {
			cout << "The File is Empty." << endl;
		}
		ifile.close();
	}


	void viewDetails() {
		int choic;
		do {
			system("cls");
			cout << "=============Hospital Details==============" << endl;
			cout << "1. View All Doctors" << endl;
			cout << "2. View All Patients" << endl;
			cout << "3. View All Appointments" << endl;
			cout << "4. All Employees" << endl;
			cout << "5. Exit" << endl;
			cout << "===========================================" << endl;
			cout << "Enter Choice:";
			cin >> choic;
			cin.ignore();
			switch (choic) {
			case 1: {
				viewAllDoctors();
				system("pause");
				break;
			}
			case 2: {
				viewAllPatient();
				system("pause");
				break;
			}
			case 3: {
				viewAllAppointments();
				system("pause");
				break;
			}
			case 4: {
				viewAllEmployes();
				system("pause");
				break;
			}
			case 5: {
				return;
			}
			default: {
				cout << "Invalid Choice!" << endl;
				system("pause");
			}
			}
		} while (choic != 5);
	}

	

	void checkRoomStatus() {
		string rNum;
		cout << "Enter Room Number to Check: ";
		getline(cin, rNum);

		ifstream ifile(roomFile);
		if (!ifile.is_open()) {
			cout << "Error: Room records file missing or empty." << endl;
			return;
		}

		Room r;
		bool found = false;

		while (r.loadFile(ifile)) {
			if (r.getRoomNumber() == rNum) {
				r.checkAvailability();
				found = true;
				break;
			}
		}

		ifile.close();

		if (!found) {
			cout << "Error: Room " << rNum << " does not exist in records." << endl;
		}
	}
	
	void bookNewAppointment() {
		string appointmentID;
		string date;
		string time;
		string status;
		string pName;
		string dName;
		cout << "Enter The Appointment_ID:";
		cin >> appointmentID;
		cin.ignore();
		cout << "Enter Date(DD-MM-YYYY):";
		getline(cin, date);
		cout << "Enter Time(HH:MM):";
		getline(cin, time);
		cout << "Enter Patient Name:";
		getline(cin, pName);
		cout << "Enter Doctor Name:";
		getline(cin, dName);

		Patient p(pName, 0, " ", " ",
			" ", " ", " "," "," ");
		Doctor d(dName, 0, " ", " ",
			" ", 0, " ",
			" ", " ", " "," "," ");
		Appointment ap(appointmentID, date, time, "Scheduled", p, d);
		ap.bookAppointment();
		ap.saveToFile();
		cout << "Appointment booked successfully!" << endl;
	}


	bool isPatientIdValid(string id) {
		ifstream ifile(patientFile);
		Patient p;
		if (!ifile.is_open()) {
			return false;
		}

		while (p.loadFromFile(ifile)) {
			if (p.getPatientId() == id) {
				ifile.close();
				return true;
			}
		}
		ifile.close();
		return false;

	}


	void updatePatient() {
		string targetId;
		cout << "Enter Patient ID to Update:";
		getline(cin, targetId);

		ifstream ifile(patientFile);
		ofstream ofile("Temp_Patient.txt",ios::app);
		Patient p;
		bool found = false;

		if (!ifile.is_open() || !ofile.is_open()) {
			cout << "Error While Opening The Files." << endl;
			return;
		}
		while (p.loadFromFile(ifile)) {
			if (p.getPatientId() == targetId) {
				found = true;
				cout << "Current Address: " << p.getAddress() << endl;
				cout << "Enter New Address: ";
				string newAddr;
				getline(cin, newAddr);
				p.setAddress(newAddr); 
				cout << "Address updated." << endl;
			}
			ofile << p.getName() << endl;
			ofile << p.getAge() << endl;
			ofile << p.getAddress() << endl;
			ofile << p.getPhoneNumber() << endl;
			ofile << p.getPatientId() << endl;
			ofile << p.getBloodGroup() << endl;
			ofile << p.getDateOfAdmission() << endl;
			ofile << p.getHistoryCount() << endl; 
			for (int i = 0; i < p.getHistoryCount(); i++) {
				ofile << p.getHistoryItem(i) << endl; 
			}
		}
		ifile.close();
		ofile.close();
		if (found) {
			remove(patientFile.c_str());
			rename("Temp_Patient.txt", patientFile.c_str());
			cout << "Success: Patient record updated." << endl;
		}
		else {
			cout << "Error:Patient Id Not Found." << endl;
			remove("Temp_Patient.txt");
		}
	}

	


	void dischargePatient() {
		string targetId;
		cout << "Enter Patient ID to Discharge (Delete): ";
		getline(cin, targetId);

		ifstream ifile(patientFile);
		ofstream ofile("Temp_Patient.txt");
		Patient p;
		bool found = false;

		if (!ifile.is_open() || !ofile.is_open()) {
			cout << "Error While Opening The Files." << endl;
			return;
		}
		while (p.loadFromFile(ifile)) {
			if (p.getPatientId() == targetId) {
				found = true;
				cout << "Patient " << p.getName() << " has been discharged ." << endl;
				continue;
			}
			
			ofile << p.getName() << endl;
			ofile << p.getAge() << endl;
			ofile << p.getAddress() << endl;
			ofile << p.getPhoneNumber() << endl;
			ofile << p.getPatientId() << endl;
			ofile << p.getBloodGroup() << endl;
			ofile << p.getDateOfAdmission() << endl;
			ofile << p.getHistoryCount() << endl;
			for (int i = 0; i < p.getHistoryCount(); i++) {
				ofile << p.getHistoryItem(i) << endl;
			}
		}

		ifile.close();
		ofile.close();

		if (found) {
			remove(patientFile.c_str());
			rename("Temp_Patient.txt", patientFile.c_str());
		}
		else {
			cout << "Error: Patient ID not found." << endl;
			remove("Temp_Patient.txt");
		}
	}


	void deleteDoctor() {
		string targetId;
		cout << "Enter Doctor ID to Remove: ";
		getline(cin, targetId);

		ifstream ifile(doctorFile);
		ofstream ofile("Temp_Doctor.txt");

		Doctor d;
		bool found = false;

		if (!ifile.is_open() || !ofile.is_open()) {
			cout << "Error opening files!" << endl;
			return;
		}

		while (d.loadFile(ifile)) {
			if (d.getEmployeeId() == targetId) {
				found = true;
				cout << "Doctor " << d.getName() << " removed from system." << endl;
				continue; 
			}

			ofile << d.getName() << endl;
			ofile << d.getAge() << endl;
			ofile << d.getAddress() << endl;
			ofile << d.getPhoneNumber() << endl;
			ofile << d.getEmployeeId() << endl;
			ofile << d.getSalary() << endl;
			ofile << d.getDateOfJoining() << endl;
			ofile << d.getSpecialization() << endl;
			ofile << d.getLicenseNumber() << endl;
			ofile << d.getSchedual() << endl;
			ofile << d.getUserName() << endl;
		}

		ifile.close();
		ofile.close();

		if (found) {
			remove(doctorFile.c_str());
			rename("Temp_Doctor.txt", doctorFile.c_str());
		}
		else {
			cout << "Error: Doctor ID not found." << endl;
			remove("Temp_Doctor.txt");
		}
	}

	void viewMedicalRecords() {
		ifstream ifile(recordFile);
		if (!ifile.is_open()) {
			cout << "No medical records found." << endl;
			return;
		}
		MedicalRecord mr;
		cout << "========= Medical History =========" << endl;
		while (mr.loadFile(ifile)) {
			mr.display();
		}
		ifile.close();
	}


	void cancelAppointment() {
		string targetID;
		cout << "Enter Appointment ID to Cancel: ";
		getline(cin, targetID);

		ifstream ifile(apptFile);
		ofstream ofile("Temp_Appt.txt");
		Appointment ap;
		bool found = false;

		if (!ifile.is_open() || !ofile.is_open()) return;

		while (ap.loadFile(ifile)) {
			if (ap.getAppointmentID() == targetID) {
				ap.setStatus("Cancelled"); 
				found = true;
				cout << "Appointment Cancelled Successfully." << endl;
			}
			
			ofile << ap.getAppointmentID() << endl;
			ofile << ap.getDate() << endl;
			ofile << ap.getTime() << endl;
			ofile << ap.getStatus() << endl;
			ofile << ap.getPatient().getName() << endl;
			ofile << ap.getDoctor().getName() << endl;
		}
		ifile.close(); ofile.close();
		if (found) {
			remove(apptFile.c_str());
			rename("Temp_Appt.txt", apptFile.c_str());
		}
		else {
			cout << "ID Not Found." << endl;
			remove("Temp_Appt.txt");
		}
	}







	void viewMyDetails(string myID) {
		ifstream ifile(patientFile);
		if (!ifile.is_open()) {
			cout << "Error: Records file missing." << endl;
			return;
		}

		Patient p;
		bool found = false;
		cout << "========= My Profile =========" << endl;

		while (p.loadFromFile(ifile)) {
			if (p.getPatientId() == myID) {
				p.display();
				found = true;
				break;
			}
		}
		ifile.close();

		if (!found) cout << "Profile not found." << endl;
	}

	void viewMyHistory(string myID) {
		ifstream ifile(patientFile);
		if (!ifile.is_open()) {
			cout << "Error: Records file missing." << endl;
			return;
		}

		Patient p;
		bool found = false;

		while (p.loadFromFile(ifile)) {
			if (p.getPatientId() == myID) {
				p.getMedicalHistory(); 
				found = true;
				break;
			}
		}
		ifile.close();

		if (!found) cout << "No medical history record found." << endl;
	}

	void viewMyAppointments(string myName) {
		ifstream ifile(apptFile);
		if (!ifile.is_open()) {
			cout << "No appointment records found." << endl;
			return;
		}

		Appointment ap;
		bool found = false;
		cout << "========= My Appointments =========" << endl;

		while (ap.loadFile(ifile)) {
			
			if (ap.getPatient().getName() == myName) {
				ap.display();
				cout << "==========================================" << endl;
				found = true;
			}
		}
		ifile.close();

		if (!found) cout << "No appointments booked." << endl;
	}

	
	void viewMyBills(string myID) {
		ifstream ifile(billFile);
		if (!ifile.is_open()) {
			cout << "No bill records found." << endl;
			return;
		}

		Bill b;
		bool found = false;
		cout << "========= My Bills =========" << endl;

		while (b.loadFile(ifile)) {
			if (b.getPatientID() == myID) {
				b.display();
				cout << "==========================================" << endl;
				found = true;
			}
		}
		ifile.close();

		if (!found) cout << "No bills found." << endl;
	}





	//Destructor
	~Hospital() {
		for (int i = 0; i < pCount; i++) {
			delete patient[i];
		}
		for (int i = 0; i < dCount; i++) {
			delete doctor[i];
		}
		for (int i = 0; i < eCount; i++) {
			delete staff[i];
		}
	}
};


//===========================================
//11.Authentication Class
//===========================================
class Authentication {
	// Encapsulation: Data is private
	string username;
	string password;
	string userrole;
public:
	//Default Constructor
	Authentication() {
		username = " ";
		password = " ";
		userrole = " ";
	}
	//parameterized Constructor
	Authentication(string user, string pass, string role) {
		username = user;
		password = pass;
		userrole = role;
	}


	//Setters

	void setUserName(string user) {
		username = user;
	}

	void setPassword(string pass) {
		password = pass;
	}

	void setUserRoll(string role) {
		userrole = role;
	}



	//Getters
	string getUsername() {
		return username;
	}

	string getPassword() {
		return password;
	}

	string getUserRole() {
		return userrole;
	}


	void registerUser(string user, string pass, string role) {
		username = user;
		password = pass;
		userrole = role;
		ofstream ofile(authFile, ios::app);
		if (ofile.is_open()) {
			ofile << username << endl;
			ofile << password << endl;
			ofile << userrole << endl;
			ofile.close();
			cout << "User " << username << " registered successfully with role " << userrole << "." << endl;
		}
		else {
			cout << "Error: Could not open auth file." << endl;
		}
	}
	bool verifyRole(string requiredRole) {
		if (userrole == requiredRole) {
			return true;
		}
		else {
			cout << "Access Denied: Requires " << requiredRole << " role." << endl;
			return false;
		}
	}

	bool login(string user, string pass) {
		ifstream ifile(authFile);

		if (!ifile.is_open()) {
			cout << "No user database found!" << endl;
			return false;
		}

		string fUser, fPass, fRole;
		bool found = false;

		while (getline(ifile, fUser)) {
			getline(ifile, fPass);
			getline(ifile, fRole);

			if (user == fUser && pass == fPass) {
				username = fUser;
				password = fPass;
				userrole = fRole;

				found = true;
				break; 
			}
		}
		ifile.close();

		if (found) {
			cout << "Login Successful! Welcome " << username << "." << endl;
			return true;
		}
		else {
			cout << "Error: Invalid Username or Password." << endl;
			return false;
		}
	}

	void logout() {
		cout << "User " << username << " logged out successfully." << endl;
		username = "";
		password = "";
		userrole = "";
	}

};


void Admin(Hospital& hospital) {
	int choice;
	do {
		system("cls");
		cout << "================Admin Menu=================" << endl;
		cout << "1. Add New Doctor" << endl;
		cout << "2. Add New Employee" << endl;
		cout << "3. Add New Operator" << endl;
		cout << "4. Add New Room" << endl;       
		cout << "5. Hospital Details" << endl;
		cout << "6. Remove Doctor" << endl; 
		cout << "7. LogOut" << endl;
		cout << "===========================================" << endl;
		cout << "Enter Your Choice:";
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case 1: {
			cout << "=========Add New Doctor=========" << endl;
			string n, addr, ph, eid, doj, spec, lic, sch,user,pass;
			int age;
			double sal;
			cout << "Enter Name: ";
			getline(cin, n);
			cout << "Enter Username:";
			getline(cin, user);
			cout << "Enter Password:";
			getline(cin, pass);
			cout << "Enter Age: ";
			cin >> age;
			cin.ignore();
			cout << "Enter Address: ";
			getline(cin, addr);
			cout << "Enter Phone: ";
			getline(cin, ph);
			cout << "Enter Doctor ID: ";
			getline(cin, eid);
			cout << "Enter Salary: ";
			cin >> sal;
			cin.ignore();
			cout << "Enter Joining Date: ";
			getline(cin, doj);
			cout << "Enter Specialization: ";
			getline(cin, spec);
			cout << "Enter License #: ";
			getline(cin, lic);
			cout << "Enter Schedule: ";
			getline(cin, sch);
			

			Doctor* d = new Doctor(n, age, addr, ph, eid, sal, doj, spec, lic, sch,user,pass);
			hospital.addDoctor(d);

			Authentication auth;
			auth.registerUser(user, pass, "Doctor");
			cout << "Doctor Added & Login Account Created." << endl;

			system("pause");
			break;
		}
		case 2: {
			cout << "=========Add New Employee=========" << endl;
			string dep, eid, doj, name, addr, phon;
			double sal;
			int ag;
			cout << "Enter Name:";
			getline(cin, name);
			cout << "Enter Employee_Id:";
			getline(cin, eid);
			cout << "Enter Department:";
			getline(cin, dep);
			cout << "Enter Age:";
			cin >> ag;
			cin.ignore();
			cout << "Enter Salary:";
			cin >> sal;
			cin.ignore();
			cout << "Enter Date OF Joining:";
			getline(cin, doj);
			cout << "Enter Address:";
			getline(cin, addr);
			cout << "Enter Phone_Number:";
			getline(cin, phon);
			AdminStaff* admin = new AdminStaff(dep, eid, sal, doj, name, ag, addr, phon);
			hospital.addEmployee(admin);
			system("pause");
			break;
		}
		case 3: {
			cout << "=========Add New Operator=========" << endl;
			string username, password;

			cout << "Enter Username: "; cin >> username;
			cout << "Enter Password: "; cin >> password;

			Authentication auth;
			auth.registerUser(username, password, "Operator");

			cout << "New Operator Account Created." << endl;
			system("pause");
			break;
		}
		case 4: {
			cout << "========= Add New Room =========" << endl;
			string rNum, rType;

			cout << "Enter Room Number: ";
			getline(cin, rNum);

			cout << "Enter Room Type (ICU/Private/Ward): ";
			getline(cin, rType);
			Room* r = new Room(rNum, rType, false);

			hospital.addRoom(r);
			system("pause");
			break;
			
		}
		case 5: {
			hospital.viewDetails();
			system("pause");
			break;
		}
		case 6: {
			hospital.deleteDoctor();
			system("pause");
			break;
		}
		case 7: {
			cout << "Logging Out..." << endl;
			return;
		}
		default: {
			cout << "Invalid Choice! Enter Your Choice Again." << endl;
			system("pause");
		}
		}
		}while (choice != 7);
}


void doctor(Authentication& auth, Hospital& hospital) {
	int choice;
	Doctor dct;
	bool found = false;
	ifstream ifile(doctorFile);
	if (ifile.is_open()) {
		while (dct.loadFile(ifile)) {
			if (dct.getUserName() == auth.getUsername()) {
				found = true;
				break;
			}
		}
		ifile.close();
	}
	if (!found) {
		cout << "Error: No profile found for " << auth.getUsername() << endl;
        return;
	}
	do{
		system("cls");
		cout << "===============Doctor Menu=================" << endl;
		cout << "1. View Schedule" << endl;
		cout << "2. Add Diagnosis" << endl;
		cout << "3. View All Appointments" << endl;
		cout << "4. LogOut" << endl;
		cout << "===========================================" << endl;

		cout << "Enter Your Choice:";
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case 1: {
			cout << "=========My Schedule-=========" << endl;
			dct.viewSchedual();
			system("pause");
			break;
		}
		case 2: {
			cout << "=========Add Diagnosis=========" << endl;
			string patientName;
			string diagnosis;
			cout << "Enter Patient_Id:";
			getline(cin, patientName);
			cout << "Enter Diagnosis:";
			getline(cin, diagnosis);
			dct.addDiagnosis(patientName, diagnosis);
			system("pause");
			break;
		}
		case 3: {
			hospital.viewAllAppointments();
			system("pause");
			break;
		}
		case 4: {
			cout << "Logging Out..." << endl;
			auth.logout();
			return;
		}
		default: {
			cout << "Invalid Choice! Please Enter Your Choice Again." << endl;
			system("pause");
		}
		}
	} while (choice != 4);
}




void Operator(Hospital& hospital) {
	int choice;
	do {
		system("cls");
		cout << "===============Operator Menu===============" << endl;
		cout << "1. Add a Patient" << endl;
		cout << "2. Generate Bill" << endl;
		cout << "3. Book Apointment" << endl;
		cout << "4. Make Payment" << endl;
		cout << "5. Update Patient Details" << endl;
		cout << "6. Discharge Patient" << endl;
		cout << "7. Cancel Appointment" << endl;
		cout << "8. Check Room Availability" << endl; 
		cout << "9. Logout" << endl;
		cout << "===========================================" << endl;
		cout << "Enter Your Choice:";
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case 1: {
			cout << "========= Add New Patient =========" << endl;
			string n, addr, ph, pid, bg, doa,user,pass;
			int age;

			cout << "Enter Name: ";
			getline(cin, n);
			cout << "Enter Age: ";
			cin >> age;
			cin.ignore();
			cout << "Enter Address: ";
			getline(cin, addr);
			cout << "Enter Phone: ";
			getline(cin, ph);
			cout << "Enter Patient ID: ";
			getline(cin, pid);
			cout << "Enter Blood Group: ";
			getline(cin, bg);
			cout << "Enter Admission Date: ";
			getline(cin, doa);
			cout << "Enter Username:";
			getline(cin, user);
			cout << "Enter password:";
			getline(cin, pass);

			Patient* p = new Patient(n, age, addr, ph, pid, bg, doa,user,pass);
			p->Register();
			hospital.addPatient(p);

			Authentication auth;
			auth.registerUser(user, pass, "Patient");
			cout << "Patient Registered & Login Credentials Created." << endl;

			system("pause");
			break;
		}
		case 2: {
			cout << "========= Generate Bill =========" << endl;
			string patientName, patientId, rType;
			string billId;
			cout << "Enter Patient_Id:";
			getline(cin, patientId);
			if (hospital.isPatientIdValid(patientId)) {


				cout << "Enter Patient Name:";
				getline(cin, patientName);

				cout << "Enter Room Type(ICU/Private/Ward):";
				getline(cin, rType);
				cout << "Enter Bill Id:";
				getline(cin, billId);
				Patient pt(patientName, 0, " ", " ",
					patientId, " ", " "," "," ");
				Room r(" ", rType, true);
				Bill bil(billId, pt, r);

				int itemcount;
				cout << "Enter Number Of Items:";
				cin >> itemcount;
				cin.ignore();
				for (int i = 0; i < itemcount; i++) {
					string item;
					cout << "Enter Item" << " " << i + 1 << ":";
					getline(cin, item);
					bil.AddItems(item);
				}
				bil.genrateBill();
				bil.saveFile();
			}
			else {
				cout << "Error: Patient ID " << patientId << " does not exist!" << endl;
			}
			system("pause");
			break;
		}
		case 3: {
			hospital.bookNewAppointment();
			system("pause");
			break;
		}
		
		case 4: {
			cout << "=========Process Payment=========" << endl;
			string pname, rType,pId;
			string billid;
			cout << "Enter Patient_Id:";
			getline(cin, pId);
			if (hospital.isPatientIdValid(pId)) {


				cout << "Enter Patient Name:";
				getline(cin, pname);
				cout << "Enter Bill_ID:";
				getline(cin, billid);
				cout << "Enter Room Type(ICU/Private/Ward):";
				getline(cin, rType);
				Patient pt(pname, 0, " ", " ",
					" ", " ", " "," "," ");
				Room r(" ", rType, true);
				Bill bill(billid, pt, r);
				bill.makePayment();
			}
			else {
				cout << "Error: Patient ID " << pId << " does not exist!" << endl;
			}
			system("pause");
			break;
		}
		case 5: {
			hospital.updatePatient();
			system("pause");
			break;
		}
		case 6: {
			hospital.dischargePatient();

			system("pause");
			break;
		}
		case 7: {
			hospital.cancelAppointment();
			system("pause");
			break;
		}
		case 8: {
			hospital.checkRoomStatus();
			system("pause");
			break;
		}
		case 9: {
			cout << "Loging Out...." << endl;
			return;
		}
		default: {
			cout << "Invalid Choice! Enter Your Choice Again." << endl;
			system("pause");
		}
		}
	} while (choice != 9);
}




void Patient_Menu(Authentication& auth, Hospital& hospital) {
	string loggedInUser = auth.getUsername();
	string myID = "";
	string myName = "";

	
	ifstream ifile(patientFile);
	Patient temp;
	bool found = false;

	if (ifile.is_open()) {
		while (temp.loadFromFile(ifile)) {
			if (temp.getUsername() == loggedInUser) {
				myID = temp.getPatientId();  
				myName = temp.getName();     
				found = true;
				break;
			}
		}
		ifile.close();
	}

	if (!found) {
		cout << "Error: Patient record not found for username: " << loggedInUser << endl;
		system("pause");
		return;
	}

	
	int choice;
	do {
		system("cls");
		cout << "=============== Patient Menu ===============" << endl;
		cout << "Welcome, " << myName << " (ID: " << myID << ")" << endl;
		cout << "1. View My Profile" << endl;
		cout << "2. View My Appointments" << endl;
		cout << "3. View My Bills" << endl;
		cout << "4. Logout" << endl;
		cout << "============================================" << endl;
		cout << "Enter Your Choice: "; cin >> choice; cin.ignore();

		switch (choice) {
		case 1:
			hospital.viewMyDetails(myID); 
			system("pause");
			break;
		case 2:
			hospital.viewMyAppointments(myName); 
			system("pause");
			break;
		case 3:
			hospital.viewMyBills(myID); 
			system("pause");
			break;
		case 4:
			cout << "Logging out..." << endl;
			return;
		default:
			cout << "Invalid Choice!" << endl;
			system("pause");
		}
	} while (choice != 5);
}




void all() {
	Hospital hospital;
	Authentication auth;
	int choice;
	ifstream ifile(authFile);
	if (!ifile.is_open()) {
		auth.registerUser("admin", "admin123", "Admin");

		cout << "Default Admin created successfully!" << endl;

	}
	ifile.close();
	cout << "===========================================" << endl;
	cout << "            SYSTEM CREDENTIALS             " << endl;
	cout << "===========================================" << endl;
	cout << "Admin:    admin    / admin123" << endl;
	cout << "===========================================" << endl;
	system("pause");
	do {
		system("cls");
		cout << "=========Hospital Managment System=========" << endl;
		cout << "1. Admin Login" << endl;
		cout << "2. Doctor Login" << endl;
		cout << "3. Operator Login" << endl;
		cout << "4. Patient Login" << endl;
		cout << "5. Exit" << endl;
		cout << "===========================================" << endl;
		cout << "Enter Your choice:";
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case 1: {
			string username, password;
			cout << "=========Admin Login=========" << endl;
			cout << "User_Name:";
			cin >> username;
			cout << "Password:";
			cin >> password;
			if (auth.login(username, password)) {
				if (auth.verifyRole("Admin")) {
					cout << "Admin Login Successful." << endl;
					system("pause");
					Admin(hospital);
				}
				else {
					cout << "Acsess Denied! Admoin Role required." << endl;
				}
			}
			else {
				cout << "Login Failed! Invalid Credentials." << endl;
			}
			system("pause");
			break;
		}
		case 2: {
			string username, password;
			cout << "=========Doctor Login=========" << endl;
			cout << "User_Name:";
			cin >> username;
			cout << "Password:";
			cin >> password;
			if (auth.login(username, password)) {
				if (auth.verifyRole("Doctor")) {
					cout << "Doctor Login Successful." << endl;
					system("pause");
					doctor(auth,hospital);
				}
				else {
					cout << "Acsess Denied! Doctor Role required." << endl;
				}
			}
			else {
				cout << "Login Failed! Invalid Credentials." << endl;
			}
			system("pause");
			break;
		}
		case 3: {
			string username, password;
			cout << "=========Operator Login=========" << endl;
			cout << "User_Name:";
			cin >> username;
			cout << "Password:";
			cin >> password;
			if (auth.login(username, password)) {
				if (auth.verifyRole("Operator")) {
					cout << "Operator Login Successful." << endl;
					system("pause");
					Operator(hospital);
				}
				else {
					cout << "Acsess Denied! Operator Role required." << endl;
				}
			}
			else {
				cout << "Login Failed! Invalid Credentials." << endl;
			}
			system("pause");
			break;
		}
		case 4: {
			string username, password;
			cout << "=========Patient Login=========" << endl;
			cout << "Username: "; cin >> username;
			cout << "Password: "; cin >> password;

			
			if (auth.login(username, password)) {
				
				if (auth.verifyRole("Patient")) {
					cout << "Login Successful." << endl;
					system("pause");
					Patient_Menu(auth, hospital);
				}
				else {
					cout << "Access Denied! Patient Role required." << endl;
				}
			}
			system("pause");
			break;
		}
		case 5: {
			cout << "GOOD BYE! Thank You for using HOSPITAL MANAGMENT SYSTEM." << endl;
			return;
		}
		default: {
			cout << "Invalid Choice Enter Your Choice Again." << endl;
			system("pause");
		}
		}
	} while (choice != 5);
}


int main() {
	all();
	return 0;
}