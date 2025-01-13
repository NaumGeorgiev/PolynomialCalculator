#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Polynomial
{
private:
    vector<pair<int, int>> coefficients;

    int getLastNecessaryIndex(vector<pair<double, double>> &coefficients)
    {
        for (int i = coefficients.size() - 1; i > 0; i--)
            if (coefficients[i].first != 0)
                return i;
        return 0;
    }
    void deleteUnnecessaryELements(vector<pair<double, double>> &coefficients)
    {
        int begin = getLastNecessaryIndex(coefficients) + 1;
        coefficients.erase(coefficients.begin() + begin, coefficients.end());
    }

    int decimalDigitsCount(double a)
    {
        int count = 0;
        while (true)
        {
            if (a > static_cast<int>(a))
            {
                a *= 10;
                count++;
            }
        }
    }

    void removeDoubles(vector<pair<double, double>> &coefficients)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            coefficients[i].first *= 10;
            coefficients[i].second *= 10;
        }
    }

public:
    // Polynomial(const vector<pair<double, double>> &coefficients)
    // {
    //     vector<pair<double, double>> temp = coefficients;
    //     deleteUnnecessaryELements(temp);
    //     this->coefficients = temp;
    // }

    // vector<pair<int, int>> getCoefficients()
    // {
    //     return this->coefficients;
    // }

    // int higher(const int &a, const int &b)
    // {
    //     if (a > b)
    //         return a;
    //     return b;
    // }

    // pair<int, int> getCoefficientAt(int index)
    // {
    //     if (coefficients.size() > index)
    //         return coefficients[index];
    //     return {0, 1};
    // }

    // Polynomial add(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = higher(thisSize, otherSize);
    //     vector<pair<int, int>> sum(size);

    //     for (int i = 0; i < size; i++)
    //         sum[i] = getCoefficientAt(i) + other.getCoefficientAt(i);

    //     return Polynomial(sum);
    // }

    // Polynomial subtract(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = higher(thisSize, otherSize);
    //     vector<pair<int, int>> difference(size);

    //     for (int i = 0; i < size; i++)
    //         difference[i] = getCoefficientAt(i) - other.getCoefficientAt(i);
    //     return Polynomial(difference);
    // }

    // double sum(const double &a, const double &b)
    // {
    //     return a + b;
    // }

    // Polynomial multiply(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = thisSize + otherSize - 1;
    //     vector<pair<int, int>> product(size);

    //     for (int i = 0; i < thisSize; i++)
    //         for (int j = 0; j < otherSize; j++)
    //             product[i + j] += getCoefficientAt(i) * other.getCoefficientAt(j);
    //     return Polynomial(product);
    // }

    //  Polynomial divide(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = thisSize - otherSize + 1;
    //     vector<pair<int, int>> quotient(size);

    //     return Polynomial(quotient);
    // }
    //
    // void print()
    // {
    //     for (int i = 0; i < coefficients.size(); i++)
    //     {
    //         if (i == 0)
    //             cout << coefficients[i] << ' ';
    //         else if (i == 1)
    //             cout << coefficients[i] << 'x' << ' ';
    //         else
    //             cout << coefficients[i] << 'x' << '^' << i << ' ';
    //         if (i != coefficients.size() - 1)
    //             cout << '+' << ' ';
    //         else
    //             cout << endl;
    //     }
    // }
};

int decimalDigitsCount(vector<char> number)
{
    int startingIndex = 1;
    while (number[startingIndex - 1] != '\0' && number[startingIndex - 1] != '.')
        startingIndex++;
    int count = 0;
    for (int i = startingIndex; number[i] != '\0'; i++)
        count++;

    return count;
}

int main()
{
    int a = 2.540*100;
    cout << a;
    // vector<char> myVec;
    // char inputChar;

    // cout << "Enter characters (type '0' to stop):" << std::endl;

    // // Read characters until '0' is entered
    // while (true)
    // {
    //     std::cin >> inputChar;
    //     if (inputChar == '\n')
    //     {
    //         break; // Stop when the user enters '0'
    //     }
    //     myVec.push_back(inputChar);
    //     cout << myVec[0];
        // Polynomial p1({1, 0, 2, 3});
        // Polynomial p2({5, 1});
        // Polynomial sum = p1.add(p2);
        // Polynomial difference = p1.subtract(p2);
        // Polynomial product = p1.multiply(p2);
        // 2.34, 3.56/45, 98
        // p1.print();
        // p2.print();
        // difference.print();
        // vector<char> number= {'1', '2', '.', '4', '4'};
        // cout << decimalDigitsCount(number);
        // cout << decimalDigitsCount(a);

        return 0;
    }
