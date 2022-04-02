/*
Name: Abigail Prowse
Program Name: Prowse_Abigail_Going_Beyond_the_Bank
Date: February 15, 2022
Extra: The userInfo.txt file saves the users and passwords between program runs.  It also creates individual text files for every person which can be accessed in between runs to keep a record of each person's information.  These pieces of information are transfered into vectors for data manipulation.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "GetData.h"
#include "Functions.h"

using namespace std;

int main() {
  // the main part of my program.

  // files to start with and always use.
  ofstream file;
  // used to represent a file which I think can change as I go.
  ifstream readFile;
  // used to represent a file when reading it.
  fstream printFile;
  // used to print the file later (fstream has the ability cut out empty spaces!)

  // variable declarations
  bool returnToMenu = true;
  // this is a boolean that controls whether the program should loop back to the menu.
  bool userAlreadyTaken = false;
  // this is a boolean that controls whether the program should ask the user to create a new username because its already taken by someone else.
  bool findNewRand = false;
  // this is a boolean that controls whether or not the program needs to find a new random number because it was already used by another user.
  int menuChoice = -1;
  // this is the option chosen from the menu by the user.
  int randNum = -1;
  // holds a random number between 0 and 100 (i think)
  int counter = 0;
  // a simple counter used to count various tasks.
  int lineCount = 0;
  // used to determine what line we are in the file.
  int accNumLoc;
  // this is the location of the account number according to the indexes for when I'm printing out transaction history.
  string potUser;
  // this holds a user's potential username while creating an account
  string potPass;
  // this holds the potential password for a single user.
  string currentLine;
  // this string represents the current line of the file for reading.
  string enteredUser;
  // represents a username entered by the user to be checked for credentials
  string enteredPass;
  // represents a password entered by the user to be checked for credentials
  string reload;
  // used to reload the getline function in the instance of an example where i have to user cin.
  string lastLineUser;
  // this will hold the last line of a user's information
  float depAmount;
  // this is a float used to hold the deposit of an account
  float accountBalance = 0;
  // this equals the amount of money within an account.
  float withdrawAmount = 0;
  // this is a float used to hold the withdrawal from an account

  // arrays and vectors
  int commaLocation[2] = {0, 0};
  // holds commaLocations in each line.

  vector <string> users;
  // creates a vector for all of the users.
  vector <string> passwords;
  // creates a vector to hold all of the passwords to the users.  It will be parallel to users.
  vector <int> accountNums;
  // creates a vector to hold all of the random numbers of the user.
  vector <string> transactionHistory;
  // used to hold all the transactions of the current account.

  cout << "Welcome to the Morris County National Bank!\n\n";
  // welcome message.

  cout.setf(ios::fixed);
  
  cout << setprecision(2);
  // forces all decimals to be printed with 2 trailing zeroes
  
  // first thing to do is to read all acount numbers, passwords, and users into the vectors from the text file that were saved from last time.

  readFile.open("userInfo.txt");
  // open the file

  lineCount = 0;
  // set counter to 0.

  while (getline(readFile, currentLine)) {
    // looks for the length of the entire file.

    counter = 0;
    // counter will be used to count the number of commas that have already been found.

    for (int i = 0; i < currentLine.length(); i++) {
      // iterates through the current line now.

      if (currentLine[i] == ',') {
        // if there is a comma, record location.
        commaLocation[counter] = i;
        // saves location of the commas.
        counter++;
        // up counter because we want to make sure the commas are in the right spots.
      }
    }

    // now we must translate this into the vectors.
    users.push_back(currentLine.substr(0, commaLocation[0]));
    // makes a substring out of the first element to the first comma.
    
    passwords.push_back(currentLine.substr(commaLocation[0] + 1, commaLocation[1] - commaLocation[0]-1));
    // finds the password by take the location after the first comma to the length of the value inbetween the other two commas

    accountNums.push_back(stoi(currentLine.substr(commaLocation[1] + 1)));
    // goes to the end of the end.
    
    lineCount++;
    // add counter to keep track of the index
  }

  readFile.close();
  // closes the file for now.

  do {
    // everything in the program.  this will be bridging off the main menu

    // print main menu:
    cout << "Main Menu:\n";
    cout << "[1] Create New Account\n";
    cout << "[2] Deposit Money\n";
    cout << "[3] Withdraw Money\n";
    cout << "[4] Print Bank Statement\n";
    cout << "[5] Quit Program\n\n";

    do {
      // keeps prompting user to make a choice about what to do, to either create a new account, deposit money, withdraw money, print bank statement, or quit.
      cout << "Please enter the number of the menu item you would like to complete: ";
    } while (!getValidInt(menuChoice) || menuChoice < 1 || menuChoice > 5);

    cout << "\n";
    // break it up a bit.

    switch(menuChoice) {
      // depending on the option chosen, a different part of the program will run.
      case 1:
        // the user must create a new account.

        do {
          cout << "Enter a username: ";
          getline(cin, potUser);
          // collect potential username.

          cout << "\n";

          userAlreadyTaken = false;
          // set to false until otherwise proven wrong

          for (int i = 0; i < users.size(); i++) {
            // iterate through the users.
            if (users[i] == potUser) {
              // if they match, this username can't be used
              userAlreadyTaken = true;

              cout << "This username was already taken.  Please try a new username.\n\n";
              // print out error
              break;
            }
          }
        } while (userAlreadyTaken); // continues until a unique username is entered.

        // if it gets to here, then I know that the user will have found a unique user.
        cout << "Username accepted.\n\n";

        users.push_back(potUser);
        // add the username to the vector.

        cout << "Enter a password: ";
        getline(cin, potPass);
        // records the potential passwords for the user.

        cout << "\nPassword accepted. \n\n";
        // tell the user that the password has been accepted.

        passwords.push_back(potPass);
        // pushes the password into the vector to hold all the passwords.

        // create a random account number.
        do {
          randNum = rand() % 100;
          // creates a random number between 0 and 100

          findNewRand = false;
          // going to assume it will work until proven otherwise

          for (int i = 0; i < accountNums.size(); i++) {
            // iterate through all current account numbers.
            if (accountNums[i] == randNum) {
              // aka random number is already belonging to another user.

              findNewRand = true;
              // set to true.
            }
          }
        } while (findNewRand);
        // repeats until a good unique random number is chosen.

        accountNums.push_back(randNum);
        // adds the new random number to the end of accountNums

        file.open("userInfo.txt");
        // open file (userInfo)

        // now update the textfile by rewriting the entire thing (this is so inefficent but I really don't care)
        for (int i = 0; i < users.size(); i++) {
          // iterate through the number of users, which is pulled from the vector.

          file << users[i] << "," << passwords[i] << "," << accountNums[i] << "\n";
          // enter users and passwords to the file.
        }

        file.close();
        // close file (userInfo)

        // create a file for that user with the starting bonus money
        file.open("UserFiles/" + potUser + ".txt");

        file << "Account Creation Reward: $250.00";
        // enter the first data to the record.
        file << "\nBalance: " << "$250.00";
        // write account balance in file.

        file.close();
        // close file for neatness.

        returnToMenu = true;
        // make sure the program returns to the menu.

        break;
      case 2:
        //deposit
        returnToMenu = true;
        // make sure the program returns to the menu

        transactionHistory.clear();
        // clear vector.

        // ask for user
        cout << "Enter your username: ";
        getline(cin, enteredUser);

        // ask for password
        cout << "Enter your password: ";
        getline(cin, enteredPass);

        // input into function to check if this is good credentials
        if (isValidAccount(enteredUser, enteredPass, users, passwords)){
          // do the actual deposit

          cout << "\nSigned in successfully!\n\n";

          cout << "Please enter a deposit amount: $";
          cin >> depAmount;
          // record the deposit amount.

          getline(cin, reload);
          // reloads the getline reader from the cin (there IS a reason I hate cin so much afterall)

          readFile.open("UserFiles/" + enteredUser + ".txt");
          // open up file to read.  this should be the specific file for the specific user.

          while (getline(readFile, lastLineUser)) {
            // while there's still more, takes in the next amount.

            transactionHistory.push_back(lastLineUser);
            // places everything in the current file into the transaction history
          }

          // will be left with the lastLineUser.  Yeah this is cheap and probably not efficient.

          accountBalance = stof(lastLineUser.substr(lastLineUser.find("$") + 1));
          // uses the last line to hold the balance and set that as the current value.

          readFile.close();
          // close file when done.

          if ((depAmount < 5000) && (depAmount > 0)) {
            // basically makes sure that the user isn't depositing too much.

            cout << "Your deposit has been processed.\nYour balance is now $" << depAmount + accountBalance << ".\n\n";

            file.open("UserFiles/" + enteredUser + ".txt");
            // opens current file.

            transactionHistory.push_back("\nDeposit Made for $" + to_string(depAmount).substr(0, to_string(depAmount).find(".") + 3));
            transactionHistory.push_back("\nBalance: $" + (to_string(accountBalance + depAmount).substr(0, to_string(accountBalance + depAmount).find(".") + 3)));
            // update the transaction history with the new transaction before updating the file.

            for (int i = 0; i < transactionHistory.size(); i++) {
              // reenter the new information into the file .

              file << "\n" + transactionHistory[i];
              // enters all of the data from the current transaction history into correct file.
            }

            file.close();
            // close the file.

          }
          else {
            // this is not valid my friend.
            cout << "Your deposit bounced.  Redirecting to the main menu.\n\n";
          }
        }
        else {
          cout << "\nError signing in.  Check that you have an account and that you entered your username and password correctly. You will be re-routed to the main menu where you can choose from the possible operations again.\n\n";
        }

        break;
      case 3:
        // withdraw
        returnToMenu = true;
        // make sure the program returns to the menu

        transactionHistory.clear();
        // clear vector.

        // ask for user
        cout << "Enter your username: ";
        getline(cin, enteredUser);

        // ask for password
        cout << "Enter your password: ";
        getline(cin, enteredPass);

        // input into function to check if this is good credentials
        if (isValidAccount(enteredUser, enteredPass, users, passwords)){
          // do the actual withdrawal

          cout << "\nSigned in successfully!\n\n";

          cout << "Please enter a withdrawal amount: $";
          cin >> withdrawAmount;
          // record the withdraw amount.

          getline(cin, reload);
          // reloads the getline reader from the cin (there IS a reason I hate cin so much afterall)

          readFile.open("UserFiles/" + enteredUser + ".txt");
          // open up file to read.  this should be the specific file for the specific user.

          while (getline(readFile, lastLineUser)) {
            // while there's still more, takes in the next amount.

            transactionHistory.push_back(lastLineUser);
            // places everything in the current file into the transaction history
          }

          // will be left with the lastLineUser.  Yeah this is cheap and probably not efficient.

          accountBalance = stof(lastLineUser.substr(lastLineUser.find("$") + 1));
          // uses the last line to hold the balance and set that as the current value.

          readFile.close();
          // close file when done.

          if ((withdrawAmount <= accountBalance) && (withdrawAmount > 0)) {
            // basically makes sure that the user isn't withdrawing too much.

            cout << "Your withdrawal has been processed.\nYour balance is now $" << accountBalance - withdrawAmount << ".\n\n";

            file.open("UserFiles/" + enteredUser + ".txt");
            // opens current file.

            transactionHistory.push_back("\nWithdrawal Made for $" + to_string(withdrawAmount).substr(0, to_string(withdrawAmount).find(".") + 3));
            transactionHistory.push_back("\nBalance: $" + (to_string(accountBalance - withdrawAmount).substr(0, to_string(accountBalance - withdrawAmount).find(".") + 3)));
            // update the transaction history with the new transaction before updating the file.

            for (int i = 0; i < transactionHistory.size(); i++) {
              // reenter the new information into the list.

              file << "\n" + transactionHistory[i];
              // enters all of the data from the current transaction history into correct file.
            }

            file.close();
            // close the file.

          }
          else {
            // this is not valid my friend.
            cout << "Your withdrawal bounced.  Redirecting to the main menu.\n\n";
          }
        }
        else {
          cout << "\nError signing in.  Check that you have an account and that you entered your username and password correctly. You will be re-routed to the main menu where you can choose from the possible operations again.\n\n";
        }

        break;
      case 4:
        // print transaction report
        returnToMenu = true;
        // make sure the program returns to the menu

        // ask for user
        cout << "Enter your username: ";
        getline(cin, enteredUser);

        // ask for password
        cout << "Enter your password: ";
        getline(cin, enteredPass);

        // input into function to check if this is good credentials
        if (isValidAccount(enteredUser, enteredPass, users, passwords)){
          // do the actual withdrawal

          cout << "\nSigned in successfully!\n\n";

          cout << "Your Bank Statement:\n\n";
          // header of sorts

          // find the corresponding account number
          for (int i = 0; i < users.size(); i++) {
            // iterate through all of the different usernames to find where this particular account falls since they are parallel arrays

            if (users[i] == enteredUser) {
              accNumLoc = i;
              // records the location of the account number that corresponds with the username that has already been verfied as existing.  Because they are parallel arrays, I know that this must be the correct account.
              break;
              // break out of the loop
            }
          }
          cout << "Account Number: " + to_string(accountNums[accNumLoc]) + "\n";
          // print out the account number for the account
          cout << "Username: " + enteredUser + "\n";
          // print out the username of the user

          cout << "This section will break down every deposit and withdrawal made under this account.  The last balance is your current balance.\n\n";
          // smol note

          printFile.open("UserFiles/" + enteredUser + ".txt");
          // open up corresponding account file.

          // print out relevant information
          while (getline(printFile, currentLine)) {
            // while there is still more information, grab the next line.

            // if there is nothing in the line, then it doesn't print.
            if (!(currentLine.empty())) {
              // basically it must have stuff in it.

              cout << currentLine + "\n";
              // print out the currentLine.
            }
          }
          
          cout << "\n";
          // newline just to clear stuff up.
          
          printFile.close();
          // closes file when done.
        }
        else {
          cout << "\nError signing in.  Check that you have an account and that you entered your username and password correctly. You will be re-routed to the main menu where you can choose from the possible operations again.\n\n";
        }

        break;
      case 5:
        cout << "Thank you for your business!\n";
        // thank the user for their business and exits program.

        returnToMenu = false;
        // makes sure the program does not return to the menu.

        break;
      default:
        cout << "There's been an error.  Please try again . . . \n\n";
        // tells the user that there's been an error and that they need to try again.

        returnToMenu = true;
        // make sure the program goes back to the main menu again!

        break;
    }

  } while(returnToMenu);
}