#include <random>

using namespace std;

class RandomGenerator{
private:
	default_random_engine generator;
	int min, max;
	

public:
	RandomGenerator(int minVal, int maxVal);
	int next();
};