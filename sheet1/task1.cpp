#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <map>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

float euclidNorm(const Vector3d& v1, const Vector3d& v2)
{
	Vector3d distVec = v1 - v2;
	return distVec.norm();
}

float manhatenNorm(const Vector3d& v1, const Vector3d& v2)
{
	return fabs(v1(0) - v2(0)) + fabs(v1(1) - v2(1)) + fabs(v1(2) - v2(2));
}

typedef float (*NormFunction)(const Vector3d& v1, const Vector3d& v2);

int main(int argc, char** argv)
{
	assert(((argc-4)%3) == 0);

	//read points, which should be classified
	vector<Vector3d> inpPoints;
	for(int i = 4; i < argc; i+=3)
	{
		inpPoints.push_back(Vector3d(stod(argv[i]), stod(argv[i+1]), stod(argv[i+2])));
	}

	//read number of nearest neighbors
	int kNearestNeighbors = stoi(argv[3]);

	//read norm type
	NormFunction norm = nullptr;
	if(string(argv[2]) == "euclid")
		norm = euclidNorm;
	else if (string(argv[2]) == "manhetten")
		norm = manhatenNorm;

	assert(norm != nullptr);
	fprintf(stderr, "Using %s norm\n", argv[2]);

	//read datapoints from file
	ifstream file;
	file.open(string(argv[1]));
	if(!file.is_open())
	{
		cout << "dailed to open file for parsing";
		return 0;
	}


	string floatRegexpStr = "(\\+|-)?[0-9]+(.[0-9]*)?";
	string vectorRegExpStr = "\\[" + floatRegexpStr + "\\, " + floatRegexpStr + "\\, " + floatRegexpStr + "\\]";
	string entrieRegExpStr = "\\(" + vectorRegExpStr + ", " + floatRegexpStr + "\\)";
	regex floatRegexp(floatRegexpStr);
	regex vectorRegExp(vectorRegExpStr);
	regex entrieRegExp(entrieRegExpStr);

	int num = 0;
	string line;
	vector<pair<Vector3d, float>> dataSet;
	while(getline(file, line, '\n'))
	{

		smatch entrie;
		if(!regex_search(line, entrie, entrieRegExp))
		{
			//cout << line << "doesnt match\n";
			continue;
		}

		smatch vect;
		string entrieStr = entrie.str(0);
		
		//deparse [%f,%f,%f]
		regex_search(entrieStr, vect, vectorRegExp);
		string vecStr = vect.str(0);
		smatch val;
		Vector3d point;

		for(int i = 0; i < 3; i++)
		{
			regex_search(vecStr, val, floatRegexp);
			point(i) = stod(val.str(0));
			vecStr = val.suffix().str();				
		}

		//fprintf(stderr, "%d: %f,%f,%f -> ", num, point(0), point(1), point(2));
		entrieStr = vect.suffix().str();

		//deparse [...], %f
		regex_search(entrieStr, vect, floatRegexp);
		//fprintf(stderr, "%f\n", stod(vect.str(0)));
		//num++;
		dataSet.push_back(make_pair(point, stod(vect.str(0))));
	}

/*	for(const auto& inpt : inpPoints)
	{
		fprintf(stderr, "input point: [%f, %f, %f]\n", inpt(0), inpt(1), inpt(2));
	}
	for(const auto& datasetEntrie : dataSet)
	{
		fprintf(stderr, "data: [%f, %f, %f]->%f\n", 
			datasetEntrie.first(0), 
			datasetEntrie.first(1), 
			datasetEntrie.first(2),
			datasetEntrie.second);
	}
*/

	//start k-nearest-neighbors alhorythm

	for(const auto& point : inpPoints)
	{
		auto compare = [point, norm](const pair<Vector3d, float>& e1, const pair<Vector3d, float>& e2)
		{
			return norm(e1.first, point) < norm(e2.first, point);
		};
		sort(dataSet.begin(), dataSet.end(), compare);
		fprintf(stderr, "%d nearest neighbors for [%f, %f, %f]:\n", kNearestNeighbors, point(0), point(1), point(2));
		float totalVal;
		for(int i = 0; i < kNearestNeighbors; i++)
		{
			fprintf(stderr, "\t[%f, %f, %f]->%f (dist:%f)\n", 
				dataSet[i].first(0), 
				dataSet[i].first(1), 
				dataSet[i].first(2),
				dataSet[i].second,
				norm(dataSet[i].first,point));
		}
	}

}