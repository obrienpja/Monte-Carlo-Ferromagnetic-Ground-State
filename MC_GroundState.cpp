#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;

double norm(vector<double> spin)
{
	return sqrt(pow(spin[0],2) + pow(spin[1],2) + pow(spin[2],2));
}

vector<double> normSpin()
{
  vector<double> a;
  for (int i = 0; i<3; i++)
    a.push_back((double)rand()/RAND_MAX);
  transform(a.begin(), a.end(), a.begin(), bind1st(multiplies<double>(), 1. / norm(a)));
  return a;
}

void printVector(vector<double> vec1)
{
  for (int i = 0; i < vec1.size(); i++)
    cout << vec1[i] << endl;
}

vector< vector<double> > normConfig(int Nsites)
{
  vector< vector<double> > config;
  for(int i = 0; i < Nsites; i++)
    {
      vector<double> spin = normSpin();
      printVector(spin);
      config.push_back(spin);
    }
  return config;
}

vector< vector<double> > createFerromagneticExchange(int Nsites)
{
  vector< vector<double> > jij;
  vector<double> jijRow;
  for (int i = 0; i < Nsites; i++)
    jijRow.push_back(-1.);
  for (int i = 0; i < Nsites; i++)
    jij.push_back(jijRow);
  return jij;
}

int chooseRandomIndex(int Nsites)
{
  return rand()%Nsites;
}

vector<double> chooseRandomSpin(vector< vector<double> > config, int index)
{
  return config[index];
}

double dotVectors(vector<double> vec1, vector<double> vec2)
{
    double innerProd;
    innerProd = inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0.0);
    return innerProd;
}

vector<double> subtractVectors(vector<double> vec1, vector<double> vec2)
{
    vector<double> diff(vec1.size());
    transform(vec1.begin(), vec1.end(), vec2.begin(), diff.begin(), minus<double>());
    return diff;
}

double calculateEnergy(vector< vector<double> > jij, vector< vector<double> > config)
{
  double energy = 0;
  for(int i = 0; i < jij.size(); i++)
    {
      for(int j = 0; j < jij.size(); j++)
          energy += jij[i][j]*dotVectors(config[i],config[j]);
    }
  return energy;
}

double energyChange(vector< vector<double> > jij, vector< vector<double> > config, vector<double> oldspin, vector<double> newspin, int index)
{
  double energy = 0;
  for(int i = 0; i < index; i++)
      energy += 2*jij[index][i]*dotVectors(subtractVectors(newspin, oldspin), config[i]);
  for(int i = index + 1; i < config.size(); i++)
      energy += 2*jij[index][i]*dotVectors(subtractVectors(newspin, oldspin), config[i]);
  return energy;
}

vector< vector<double> > monteCarlo(int Nsites, int Nitr)
{
	vector< vector<double> > config = normConfig(Nsites);
	vector< vector<double> > jij = createFerromagneticExchange(Nsites);
	int ind;
	vector<double> oldspin, newspin;
	for(int i = 0; i < Nitr; i++)
	{
		ind = chooseRandomIndex(Nsites);
		oldspin = chooseRandomSpin(config, ind);
		newspin = normSpin();
		if(energyChange(jij, config, oldspin, newspin, ind) < 0)
			config[ind] = newspin;
	}
	return config;
}

// MC algorithm
// 1) Random config
// 2) Define J_ij
// 3) Pick random site
// 4) Consider random spin
// 5) Calculate energy change
// 6) Accept or reject
// 7) Repeat

int main()
{
	vector< vector<double> > config2;
	vector< vector<double> > jij = createFerromagneticExchange(4);

	config2 = monteCarlo(4, 100000);

	cout << "The energy is: " << calculateEnergy(jij, config2) << endl;
	cout << "The lowest energy is: " << -pow(4, 2) << endl;

	return 0;
}
