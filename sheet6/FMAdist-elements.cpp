#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

using namespace std;

int h1(int x){	return (2*x + 1)%32;}
int h2(int x){	return (3*x + 7)%32;}
int h3(int x){	return (4*x + 0)%32;}

typedef int (*hashFunction)(int);

int zeros(int x)
{
	if(x == 0)
		return 0;
	int i = 0;
	for(i = 0; i < sizeof(x)*8; i++)
	{
		if(x>>i & 0x1)
			break;
	}
	return i;
}

void FMA(const vector<int>& stream, hashFunction h)
{
	assert(h != nullptr);
	int z = 0;
	for(auto val : stream)
		z = max(z, zeros(h(val)));
	printf("estimated number of different elements:%f\n", pow(2, z + 0.5));
}

int main(int argc, char** argv)
{

	hashFunction hf;
	string hfString;
	switch(argv[1][0]){
		case 'a':
		hf = h1;
		hfString = "(2*x + 1)%32";
		break;

		case 'b':
		hf = h2;
		hfString = "(3*x + 7)%32";
		break;

		case 'c':
		hf = h3;
		hfString = "(4*x + 0)%32";
		break;

		default:
		assert(0);
	}

	vector<int> stream;
	printf("stream: ");
	for(int i = 2; i < argc; i++)
	{
		stream.push_back(stoi(argv[i]));
		printf("%d ", stream.back());
	}
	printf("\nhash function: %s\n", hfString.c_str());

	for(auto val : stream)
		printf("zeros(hf(%d)=%d) = %d\n", val, hf(val), zeros(hf(val)));
	FMA(stream, hf);
	return 0;
}
