#include <string>
#include <vector>


using namespace std;

class Course
{
public:
	string courseNum;
	string courseName;
	vector<string> preReqs;


	Course(string num, string name) : courseNum(num), courseName(name) {}

};



