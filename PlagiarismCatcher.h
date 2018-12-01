/* plagiarism.h

  Name: Rithvik Baddam
  UT eid: rrb2442

  Name: Arul Saraf
  UT eid: as75789
*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class PlagiarismCatcher{
private:
	int n;

	string getNextWord(string s, int& pos);
	string vectorToString(vector<string> vec); 

public:
	const int SUCCESS = 0;
	const int FILE_TOO_SMALL = 1;
	const int FILE_NOT_OPENED = 2;

	PlagiarismCatcher(){
		n = 0;
	}

	PlagiarismCatcher(int n){
		this->n = n;
	}

	int generateSequences(string filename);
};

string PlagiarismCatcher::getNextWord(string s, int& pos){
	string word;
	//first look for a space
	int finder = s.find(" ", pos);
	bool found = true;

	if(finder == string::npos){
		//then check for a carriage return
		finder = s.find("\r", pos);

		if(finder == string::npos){
			//finally look for a newline
			finder == s.find("\n", pos);

			//if you still didn't find anything, that's a problem
			if(finder == string::npos){
				found = false;
			}

		}

	}
	//if you found a valid word, return it
	if(found){
		word = s.substr(pos, finder-pos);
		pos = finder+1;
	}
	//otherwise, return the empty string and increment your position
	else{
		word = "";
		pos++;
	}

	return word;
}

string PlagiarismCatcher::vectorToString(vector<string> vec){
	string s = "";
	for(int  i = 0; i < vec.size(); i++){
		cout << vec[i] << " ";
		// s.append(vec[i]);
		// s.append(" ");
	}
	cout << endl;
	return s;
}

int PlagiarismCatcher::generateSequences(string fileName){

		ifstream myFile(fileName);
		
		if(myFile.is_open()){

			vector<string> vec;
			string buf;
			int pos;

			while(getline(myFile, buf)){
				
				pos = 0;

				while(pos < buf.size()){
					//push the words into the vector
					vec.push_back(getNextWord(buf, pos));
					//when the vector is "full"
					//get the n word sequence and delete the first word
					if(vec.size() == n){
						for(int  j = 0; j < vec.size(); j++){
							cout << vec[j] << " ";
						}
						cout << endl;
						vec.erase(vec.begin());
					}

					
				}

				cout << endl;
			}

		
			myFile.close();
			return SUCCESS;
		}

		else{
			return FILE_NOT_OPENED;
		}
	}
