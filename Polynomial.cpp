#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Polynomial
{
private:
    vector<int> coefficients;

public:
    Polynomial(const vector<int> &coefficients)
    {
        this->coefficients = coefficients;
    }

    vector<int> getCoefficients()
    {
        return this->coefficients;
    }

    int higher(const int &a, const int &b)
    {
        if (a > b)
            return a;
        return b;
    }

    int getCoefficientAt(int index)
    {
        if (coefficients.size() > index)
            return coefficients[index];
        return 0;
    }

    Polynomial add(Polynomial &other)
    {
        vector<int> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = higher(thisSize, otherSize);
        vector<int> sum(size);

        for (int i = 0; i < size; i++)
            sum[i] = getCoefficientAt(i) + other.getCoefficientAt(i);

        return Polynomial(sum);
    }

    Polynomial subtract(Polynomial &other)
    {
        vector<int> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = higher(thisSize, otherSize);
        vector<int> difference(size);

        for (int i = 0; i < size; i++)
            difference[i] = getCoefficientAt(i) - other.getCoefficientAt(i);
        return Polynomial(difference);
    }

    // int sum(const int &a, const int &b){
    //     return a + b;
    // }

    // vector<int> multiply(Polynomial &other){
    //     vector<int> product;
    //     int size = sum(coefficients.size(), other.getCoefficients().size());

    // }

    void print()
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            if (i == 0)
                cout << coefficients[i] << ' ';
            else if (i == 1)
                cout << coefficients[i] << 'x' << ' ';
            else
                cout << coefficients[i] << 'x' << '^' << i << ' ';
            if (i != coefficients.size() - 1)
                cout << '+' << ' ';
            else
                cout << endl;
        }
    }
};
int main()
{
    Polynomial p1({1, 2, 3, 4});
    Polynomial p2({1, 2, 3});
    Polynomial sum = p1.add(p2);
    Polynomial difference = p1.subtract(p2);

    sum.print();
    difference.print();
    // Polynomial difference = p1.subtract(p2);

    // p1.print();
    // sum.print();
    // difference.print();

    return 0;
}