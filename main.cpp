#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <random>
using namespace std;

int main() {
  string command;
  default_random_engine generator;
  cout << "SAT Prep Help Program" << endl << "The goal of this program is to help you prepare for the SAT, and improve your prospective score." << endl;
  cout << "Enter 'help' for a list of commands, or 'practice' to start practicing." << endl;
  cout << "Loading problem sets..." << endl;
  ifstream problemSets("problems.txt");
  string currLine;
  vector<string> currProblem;
  vector<vector<string> > loadedProblems;
  int n = 0;
  while (getline(problemSets, currLine)) {
    currProblem.push_back(currLine);
    n++;
    if (n > 2) {
      n = 0;
      loadedProblems.push_back(currProblem);
      currProblem.clear();
    }
  }
  problemSets.close();

  cout << "Problem sets loaded." << endl;
  while (1) {
    cin >> command;
    cout << endl;
    for (int i = 0; i < command.length(); i++) {
      command[i] = tolower(command[i]);
    }
    if (command == "exit") exit(0);
    else if (command == "help") {
      cout << "Available commands (Not case sensitive):" << endl;
      cout << "exit: exit program" << endl <<"help: display this message" << endl << "practice: practice sat questions" << endl;
    }
    else if (command == "practice") {
      cout << "Test section to practice (reading - Reading, writing - Writing (& Language), mathnc - Math (No Calculator), mathwc - Math (Calculator), All)" << endl;
      string testtype;
      cin >> testtype;
      for (int s = 0; s < testtype.length(); s++) {
        testtype[s] = tolower(testtype[s]);
      }
      char testarea;
      if (testtype == "reading") testarea = 'R';
      else if (testtype == "writing") testarea = 'W';
      else if (testtype == "mathnc") testarea = 'N';
      else if (testtype == "mathwc") testarea = 'C';
      cout << "Practice problems to receive: ";
      int p;
      cin >> p;
      cout << endl;
      uniform_int_distribution<int> distribution(0, sizeof(loadedProblems) / sizeof(loadedProblems[0]) - 1);
      int choice;
      int correctanswers = 0;
      for (int i = 0; i < p; i++) {
        choice = distribution(generator);
        //N = no calculator, C = calculator, R = reading, W = writing and language
        if (loadedProblems[choice][0][0] != testarea) {
          i--;
          continue;
        }
        cout << "Problem #" << i + 1 << ": " + loadedProblems[choice][0].substr(1) << endl;
        vector<string> answers;
        int prev = 0;
        for (int x = 0; x < 4; x++) {
          for (int s = 0; s < loadedProblems[choice][1].length(); s++) {
            if (loadedProblems[choice][1][s] == ',' && s > prev) {
              answers.push_back(loadedProblems[choice][1].substr(prev, s - prev));
              prev = s + 1;
            }
          }
        }
        
        cout << "A. " + answers[0] + " | B. " + answers[1] + " | C. " + answers[2] + " | D. " + answers[3] << endl;
        char ans;
        cin >> ans;
        ans = tolower(ans);
        char correct = tolower(loadedProblems[choice][2][0]);
        if (ans == correct) {
          cout << endl << "Correct!" << endl;
          correctanswers++;
        }
        else cout << endl << "Incorrect. :(" << endl;
      }
      cout << "Finished practice! Correct answers: " << correctanswers << "/" << p << endl;
    }
  }
}