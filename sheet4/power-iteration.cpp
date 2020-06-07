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


	cerr << "input matrix:\n" << inpMatr.format(vecFormat) << endl;
	//start power iteration
	VectorXd evector = VectorXd::Ones(dimension);
	evector.normalize();
	fprintf(stderr, "initial eigenvector: ");
	cerr << evector.transpose().format(vecFormat) << endl << endl;
	float eval;
	for(int i = 1; i <= iterations; i++){
		//compute evector
		auto prevEvector = evector;
		evector = (inpMatr * evector);
		evector.normalize();
		
		//compute evalue
		eval = (inpMatr * evector).norm() * ((evector.dot((inpMatr*evector).normalized()) >= 0) ? 1 : -1);

		fprintf(stderr, "(eval, evec) on %d iteration: (%f, ", i, eval);
		cerr << evector.transpose().format(vecFormat) << ")" << endl;
		fprintf(stderr,"1 - |<evec@pre, evec>| after %d iterations: %f\n", 
			i, 1 - fabs(prevEvector.dot(evector)));
		fprintf(stderr, "|evec - evec@pre| after %d iterations: %f\n\n", i, (evector - prevEvector).norm());

	}
	fprintf(stderr, "check (Mu<=>l*u): ");
	cerr << (inpMatr * evector).transpose().format(vecFormat) << "<=>" << (eval * evector).transpose().format(vecFormat);
	return 0;
}