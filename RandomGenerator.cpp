#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int minVal, int maxVal){
	min = minVal;
	max = maxVal;
}
int RandomGenerator::next(){
	uniform_int_distribution<int> distribution(min,max);
	return distribution(generator);
}