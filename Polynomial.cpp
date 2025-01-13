#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Polynomial
{
private:
    vector<double> coefficients;

    int getLastNecessaryElement(vector<double> &coefficients)
    {
        for (int i = coefficients.size() - 1; i > 0; i--)
            if (coefficients[i] != 0)
                return i;
        return 0;
    }
    void deleteUnnecessaryELements(vector<double> &coefficients)
    {
        int begin = getLastNecessaryElement(coefficients) + 1;
        coefficients.erase(coefficients.begin() + begin, coefficients.end());

    }

public:
    Polynomial(const vector<double> &coefficients)
    {
        vector<double> temp = coefficients;
        deleteUnnecessaryELements(temp);
        this->coefficients = temp;
    }

    vector<double> getCoefficients()
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
        vector<double> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = higher(thisSize, otherSize);
        vector<double> sum(size);

        for (int i = 0; i < size; i++)
            sum[i] = getCoefficientAt(i) + other.getCoefficientAt(i);

        return Polynomial(sum);
    }

    Polynomial subtract(Polynomial &other)
    {
        vector<double> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = higher(thisSize, otherSize);
        vector<double> difference(size);

        for (int i = 0; i < size; i++)
            difference[i] = getCoefficientAt(i) - other.getCoefficientAt(i);
        return Polynomial(difference);
    }

    int sum(const int &a, const int &b)
    {
        return a + b;
    }

    Polynomial multiply(Polynomial &other)
    {
        vector<double> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = thisSize + otherSize - 1;
        vector<double> product(size);

        for (int i = 0; i < thisSize; i++)
            for (int j = 0; j < otherSize; j++)
                product[i + j] += getCoefficientAt(i) * other.getCoefficientAt(j);
        return Polynomial(product);
    }

     Polynomial divide(Polynomial &other)
    {
        vector<double> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = thisSize - otherSize + 1;
        vector<double> quotient(size);

        
        return Polynomial(quotient);
    }

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
    Polynomial p1({1, 2, 0, 0});
    Polynomial p2({1, 2, 0});
    Polynomial sum = p1.add(p2);
    Polynomial difference = p1.subtract(p2);
    Polynomial product = p1.multiply(p2);

    p1.print();
    p2.print();
    difference.print();

    return 0;
}