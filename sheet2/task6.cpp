#include <array>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

float loss_matr[][4] = {
	{1,1,0,0},
	{0,1,1,1},
	{1,0,1,0.5}
};

array<float, 3> weights = {1,1,1};

int main(int argc, char** argv)
{
	vector<unsigned int> event_list;
	assert(argc == 2);
	for(int i = 0; argv[1][i] != 0; i++)
	{
		assert((argv[1][i] - '0') >= 0 && (argv[1][i] - '0') < 4);
		event_list.push_back(argv[1][i] - '0');
	}

	fprintf(stderr, "initial weights: [");
	for(auto w : weights)
		fprintf(stderr, "\t%f", w);
	fprintf(stderr, "]\n");

	int round = 0;
	for(auto j : event_list)
	{
		round++;
		for(int i = 0; i < weights.size(); i++)
		{
			weights[i] *= pow(0.5, loss_matr[i][j]);
		}
		fprintf(stderr, "weights at round %d: [", round);
		float sum = 0;
		for(auto w : weights)
		{
			sum += w;
			fprintf(stderr, "\t%f", w);
		}
		fprintf(stderr, "]\n");
		fprintf(stderr, "probabilities at round %d: [", round);
		for(auto w : weights)
			fprintf(stderr, "\t%f", w/sum);
		fprintf(stderr, "]\n");
	}
}