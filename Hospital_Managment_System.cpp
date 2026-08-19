
// Anas Naveed
// Muzammil Hussain

// ( DUO )
//=============================

#include <iostream>

using namespace std;

int main() {
  int patientID[50];
  int patientAge[50];
  string patientName[50];
  string disease[50];

  int patientCount = 0;

  int appID[50];
  int appPatientID[50];
  int appDoctorID[50];

  string appDate[50];
  string appTime[50];

  int appCount = 0;

  int doctorID[5] = {101, 102, 103, 104, 105};

  string doctorName[5] = {"Dr. Ahmed", "Dr. Sara", "Dr. Usman", "Dr. Ayesha",
                          "Dr. Hamza"};

  string specialization[5] = {"General Doctor", "Cardiologist", "Dermatologist",
                              "Pediatrician", "Orthopedic"};

  int doctorFee[5] = {1500, 2500, 2000, 1800, 2200};

  int choice;
  double revenue = 0;

  do {
    cout << "\n";
    cout << "=================================\n";
    cout << "   HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "=================================\n";
    cout << "1. Register Patient\n";
    cout << "2. Display Patients\n";
    cout << "3. Search Patient\n";
    cout << "4. View Doctors\n";
    cout << "5. Book Appointment\n";
    cout << "6. View Appointments\n";
    cout << "7. Generate Bill\n";
    cout << "8. Hospital Summary\n";
    cout << "9. Exit\n";
    cout << "Enter Choice: ";
    cin >> choice;

    if (choice == 1) {
      int currentPatient;
      currentPatient = patientCount;

      int generatedID;
      generatedID = 1001 + currentPatient;

      patientID[currentPatient] = generatedID;

      cout << "\nEnter Patient Name: ";
      cin >> patientName[currentPatient];

      cout << "Enter Age: ";
      cin >> patientAge[currentPatient];

      cout << "Enter Disease: ";
      cin >> disease[currentPatient];

      cout << "\nPatient ID: ";
      cout << patientID[currentPatient];

      cout << "\nPatient Name: ";
      cout << patientName[currentPatient];

      cout << "\nPatient Age: ";
      cout << patientAge[currentPatient];

      cout << "\nPatient Disease: ";
      cout << disease[currentPatient];

      cout << "\nPatient Registered Successfully!\n";

      patientCount = patientCount + 1;
    }

    else if (choice == 2) {
      bool noPatients;
      noPatients = false;

      if (patientCount == 0) {
        noPatients = true;
      }

      if (noPatients) {
        cout << "\nNo Patients Registered.\n";
      } else {
        cout << "\n===== PATIENTS =====\n";

        int i;
        i = 0;

        for (i = 0; i < patientCount; i++) {
          cout << "\nPatient Record";
          cout << "\nID: ";
          cout << patientID[i];

          cout << "\nName: ";
          cout << patientName[i];

          cout << "\nAge: ";
          cout << patientAge[i];

          cout << "\nDisease: ";
          cout << disease[i];

          cout << "\n-------------------\n";
        }
      }
    }

    else if (choice == 3) {
      int searchID;
      bool found;
      found = false;

      cout << "\nEnter Patient ID: ";
      cin >> searchID;

      int i;
      i = 0;

      for (i = 0; i < patientCount; i++) {
        int currentID;
        currentID = patientID[i];

        if (currentID == searchID) {
          found = true;

          cout << "\nPatient Found!\n";

          cout << "Patient ID: ";
          cout << patientID[i];
          cout << endl;

          cout << "Name: ";
          cout << patientName[i];
          cout << endl;

          cout << "Age: ";
          cout << patientAge[i];
          cout << endl;

          cout << "Disease: ";
          cout << disease[i];
          cout << endl;
        }
      }

      if (found == false) {
        cout << "Patient Not Found!\n";
      }
    }

    else if (choice == 4) {
      cout << "\n===== DOCTORS =====\n";

      int i;
      i = 0;

      for (i = 0; i < 5; i++) {
        int currentDoctorID;
        currentDoctorID = doctorID[i];

        string currentDoctorName;
        currentDoctorName = doctorName[i];

        string currentSpecialization;
        currentSpecialization = specialization[i];

        int currentFee;
        currentFee = doctorFee[i];

        cout << "\nID: ";
        cout << currentDoctorID;

        cout << "\nName: ";
        cout << currentDoctorName;

        cout << "\nSpecialization: ";
        cout << currentSpecialization;

        cout << "\nFee: Rs.";
        cout << currentFee;

        cout << "\n-------------------\n";
      }
    }

    else if (choice == 5) {
      int pID;
      int dID;

      bool patientFound;
      bool doctorFound;

      patientFound = false;
      doctorFound = false;

      cout << "\nEnter Patient ID: ";
      cin >> pID;

      int i;
      i = 0;

      for (i = 0; i < patientCount; i++) {
        int currentPatientID;
        currentPatientID = patientID[i];

        if (currentPatientID == pID) {
          patientFound = true;
        }
      }

      if (patientFound == false) {
        cout << "Patient Not Found!\n";
      } else {
        cout << "Enter Doctor ID: ";
        cin >> dID;

        int j;
        j = 0;

        for (j = 0; j < 5; j++) {
          int currentDoctorID;
          currentDoctorID = doctorID[j];

          if (currentDoctorID == dID) {
            doctorFound = true;
          }
        }

        if (doctorFound == false) {
          cout << "Doctor Not Found!\n";
        } else {
          int currentAppointment;
          currentAppointment = appCount;

          cout << "Enter Date: ";
          cin >> appDate[currentAppointment];

          cout << "Enter Time: ";
          cin >> appTime[currentAppointment];

          int newAppointmentID;
          newAppointmentID = 5001 + currentAppointment;

          appID[currentAppointment] = newAppointmentID;

          appPatientID[currentAppointment] = pID;

          appDoctorID[currentAppointment] = dID;

          cout << "\nAppointment ID: ";
          cout << appID[currentAppointment];

          cout << "\nPatient ID: ";
          cout << appPatientID[currentAppointment];

          cout << "\nDoctor ID: ";
          cout << appDoctorID[currentAppointment];

          cout << "\nDate: ";
          cout << appDate[currentAppointment];

          cout << "\nTime: ";
          cout << appTime[currentAppointment];

          appCount = appCount + 1;

          cout << "\nAppointment Booked Successfully!\n";
        }
      }
    }

    else if (choice == 6) {
      bool noAppointments;
      noAppointments = false;

      if (appCount == 0) {
        noAppointments = true;
      }

      if (noAppointments) {
        cout << "\nNo Appointments.\n";
      } else {
        cout << "\n===== APPOINTMENTS =====\n";

        int i;
        i = 0;

        for (i = 0; i < appCount; i++) {
          int currentAppointmentID;
          currentAppointmentID = appID[i];

          int currentPatientID;
          currentPatientID = appPatientID[i];

          int currentDoctorID;
          currentDoctorID = appDoctorID[i];

          string currentDate;
          currentDate = appDate[i];

          string currentTime;
          currentTime = appTime[i];

          cout << "\nAppointment ID: ";
          cout << currentAppointmentID;

          cout << "\nPatient ID: ";
          cout << currentPatientID;

          cout << "\nDoctor ID: ";
          cout << currentDoctorID;

          cout << "\nDate: ";
          cout << currentDate;

          cout << "\nTime: ";
          cout << currentTime;

          cout << "\n-------------------\n";
        }
      }
    }

    else if (choice == 7) {
      int dID;
      int medicine;
      int lab;

      int fee;
      fee = 0;

      bool found;
      found = false;

      cout << "\nEnter Doctor ID: ";
      cin >> dID;

      int i;
      i = 0;

      for (i = 0; i < 5; i++) {
        int currentDoctorID;
        currentDoctorID = doctorID[i];

        if (currentDoctorID == dID) {
          fee = doctorFee[i];
          found = true;
        }
      }

      if (found) {
        cout << "Medicine Charges: ";
        cin >> medicine;

        cout << "Laboratory Charges: ";
        cin >> lab;

        int doctorAmount;
        doctorAmount = fee;

        int medicineAmount;
        medicineAmount = medicine;

        int laboratoryAmount;
        laboratoryAmount = lab;

        int total;
        total = doctorAmount + medicineAmount + laboratoryAmount;

        double oldRevenue;
        oldRevenue = revenue;

        revenue = oldRevenue + doctorAmount;

        cout << "\n===== HOSPITAL BILL =====\n";

        cout << "Doctor Fee: Rs.";
        cout << doctorAmount;
        cout << endl;

        cout << "Medicine: Rs.";
        cout << medicineAmount;
        cout << endl;

        cout << "Lab Charges: Rs.";
        cout << laboratoryAmount;
        cout << endl;

        cout << "Total Bill: Rs.";
        cout << total;
        cout << endl;
      } else {
        cout << "Doctor Not Found!\n";
      }
    }

    else if (choice == 8) {
      cout << "\n===== HOSPITAL SUMMARY =====\n";

      int totalPatients;
      totalPatients = patientCount;

      cout << "Patients: ";
      cout << totalPatients;
      cout << endl;

      int totalDoctors;
      totalDoctors = 5;

      cout << "Doctors: ";
      cout << totalDoctors;
      cout << endl;

      int totalAppointments;
      totalAppointments = appCount;

      cout << "Appointments: ";
      cout << totalAppointments;
      cout << endl;

      double totalRevenue;
      totalRevenue = revenue;

      cout << "Appointment Revenue: Rs.";
      cout << totalRevenue;
      cout << endl;

      bool patientsExist;
      patientsExist = false;

      if (patientCount > 0) {
        patientsExist = true;
      }

      bool appointmentsExist;
      appointmentsExist = false;

      if (appCount > 0) {
        appointmentsExist = true;
      }

      if (patientsExist == false) {
        cout << "Status: Waiting for Patients\n";
      } else {
        if (appointmentsExist == false) {
          cout << "Status: No Appointments\n";
        } else {
          cout << "Status: ACTIVE\n";
        }
      }
    }

    else if (choice == 9) {
      cout << "\nThank You!\n";
      cout << "Hospital Management System Closed.\n";
    }

    else {
      cout << "\nInvalid Choice!\n";
    }

  } while (choice != 9);

  return 0;
}