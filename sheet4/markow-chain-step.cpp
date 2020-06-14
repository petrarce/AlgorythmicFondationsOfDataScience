#include <iostream>
#include <Eigen/Dense>
#include <cassert>

using namespace std;
using namespace Eigen;
Eigen::IOFormat vecFormat(4,
						0,
						",",
						"\n",
						"[",
						"]");

int main(int argc, char** argv)
{
	MatrixXd inpMatr;
	int dimension = stoi(argv[1]);
	int iterations = stoi(argv[2]);
	assert(argc == (dimension*dimension + 3));
	inpMatr.resize(dimension, dimension);
	for(int i = 0; i < dimension; i++)
		for(int j = 0; j < dimension; j++)
			inpMatr(i,j) = stod(argv[3 + i*dimension + j]);

	VectorXd distribution = VectorXd::Random(dimension);
	distribution = VectorXd::Ones(dimension) + distribution;
	distribution = distribution / distribution.sum();

	cerr << "input matrix:\n" << inpMatr.format(vecFormat) << endl;
	//start power iteration
	int i = 0;
	for(; i < iterations; i++){
		cerr << "p" << i << ":" << distribution.transpose().format(vecFormat) << endl;
		distribution = inpMatr.transpose() * distribution;
	}
	cerr << "p" << i << ":" << distribution.transpose().format(vecFormat) << endl;
	return 0;
}