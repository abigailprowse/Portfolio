#include "Functions.h"

#include <string>
#include <vector>

using namespace std;

bool isValidAccount(string user, string pass, vector <string> &u, vector <string> &p) {
  // this basically checks if an account is valid or not by importing the user to check, the password to check, and then the entire vectors holding users and passwords.

  for (int i = 0; i < u.size(); i++) {
    // iterate through array

    if ((user == u[i])&&(pass == p[i])) {
      // if the user matches the inputted password, at any of the indexes and the password matches in the same index, then the account is opened.  So it must return true.

      return(true);
    }
  }

  // if it exits the loop, this means the account was not valid
  return(false);
}