#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

using namespace std;

vector<int> freq = {0,0,0,0,0,0,0,0,0,0};
vector<int> hf = {1, 1, -1, 1, -1, 1, 1, 1, -1, -1};

int TOW(const vector<int>& stream)
{
	int x = 0;
	fprintf(stderr, "start TOW with x = %d\n", x);
	int i = 0;
	for(auto val : stream)
	{
		i++;
		fprintf(stderr, "step %d: x = x + h(%d) = %d + %d = %d\n", i, val, x, hf[val-1], x + hf[val-1]);
		x += hf[val-1];
	}

	fprintf(stderr, "TOW B estimator: B=%d\n", x*x);
	return x*x;
}
int main(int argc, char** argv)
{

	
	vector<int> stream;
	fprintf(stderr, "stream: ");
	for(int i = 1; i < argc; i++)
	{
		assert(stoi(argv[i]) >= 1 && stoi(argv[i]) <= 10);
		stream.push_back(stoi(argv[i]));
		freq[stream.back()-1]++;
		fprintf(stderr, "%d ", stream.back());
	}
	fprintf(stderr, "\n");

	for(int i = 1; i <= 10; i++)
		fprintf(stderr, "freq(%d)=%d\n", i, freq[i-1]);

	fprintf(stderr, "\n");

	//compute F0
	//compute F2
	int F0 = 0;
	int F2 = 0;
	for(auto val : freq)
	{
		F0 += (val)?1:0;
		F2 += val*val;
	}
	fprintf(stderr, "F0 = %d\n", F0);
	fprintf(stderr, "F1 = %lu\n", stream.size());
	fprintf(stderr, "F2 = %d\n", F2);

	TOW(stream);

	return 0;
}
