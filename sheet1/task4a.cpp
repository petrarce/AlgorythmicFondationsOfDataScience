#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using namespace Eigen;

typedef struct
{
	vector<int> ptList;
	Vector2d center;
	void recalcCenter(const vector<Vector2d>& points){
		assert(ptList.size() != 0);
		center = Vector2d(0,0);
		for(const auto& pt : ptList)
		{
			center += points[pt];
		}
		center /= ptList.size();
	}
	void printPts(int clusterNumber)
	{
		fprintf(stderr,"cluster %d: center=[%.3f, %.3f]; points=[", clusterNumber, center(0), center(1));
		for(const auto& pt : ptList)
		{
			fprintf(stderr, "%c ", 'A' + pt);
		}
		fprintf(stderr, "]\n");
	}
} Cluster;

int main(int argc, char** argv)
{

	assert(((argc - 4)%2) == 0);
	assert((argc-4) / 2 > 3);

	vector<Vector2d> inp_points;
	for(int i = 4; i < argc; i+=2)
	{
		Vector2d newPoint = Vector2d(stod(argv[i]), stod(argv[i+1]));
		inp_points.push_back(newPoint);
	}
	const vector<Vector2d>& points = inp_points;

	for(auto& pt : points)
	{
		fprintf(stderr, "Point:[%f, %f]\n", pt(0), pt(1));
	}

	Cluster c1{
		vector<int>({stoi(argv[1])}),
		points[stoi(argv[1])]
	};
	Cluster c2{
		vector<int>({stoi(argv[2])}),
		points[stoi(argv[2])]
	};
	Cluster c3{
		vector<int>({stoi(argv[3])}),
		points[stoi(argv[3])]
	};

	bool changed = true;
	for(int iter = 0; changed; iter++)
	{
		fprintf(stderr, "\nIteration %d:\n", iter);
		c1.recalcCenter(points);
		c2.recalcCenter(points);
		c3.recalcCenter(points);			
		auto c1PtListBefore = c1.ptList;
		auto c2PtListBefore = c2.ptList;
		auto c3PtListBefore = c3.ptList;
		c1.ptList.clear();
		c2.ptList.clear();
		c3.ptList.clear();

		for(int i = 0; i < points.size(); i++)
		{
			float cl1Dist = (points[i] - c1.center).norm();
			float cl2Dist = (points[i] - c2.center).norm();
			float cl3Dist = (points[i] - c3.center).norm();
			if(cl3Dist < cl2Dist && cl3Dist < cl1Dist)
			{
				c3.ptList.push_back(i);
			} else if(cl2Dist < cl1Dist && cl2Dist < cl3Dist)
			{
				c2.ptList.push_back(i);
			} else {
				c1.ptList.push_back(i);
			}
		}
		c1.printPts(1);
		c2.printPts(2);
		c3.printPts(3);
		if(c1PtListBefore == c1.ptList && c2PtListBefore == c2.ptList && c3PtListBefore == c3.ptList)
			changed = false;

	}



}