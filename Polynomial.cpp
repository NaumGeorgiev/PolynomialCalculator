#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

using namespace std;

class Polynomial
{
private:
    vector<pair<int, int>> coefficients;

public:
    Polynomial(const vector<pair<int, int>> &coefficients)
    {
        this->coefficients = coefficients;
    }

    void print()
    {

        for (int i = 0; i < coefficients.size(); i++)
        {
            int numerator = coefficients[i].first;
            int denominator = coefficients[i].second;
            if (denominator == 1)
                cout << numerator;
            else
                cout << '(' << numerator << '/' << denominator << ')';
            if (i != 0)
            {
                cout << 'x';
                if (i != 1)
                    cout << '^' << i;
            }
            if(i!=coefficients.size()-1)
                cout << " + ";
        }
        cout << endl;
    }
};

vector<vector<char>> getSplitCoefficients(const vector<char> &input)
{
    vector<vector<char>> splitCoefficients;
    vector<char> coefficients;
    for (int i = 0; i <= input.size(); i++)
    {
        if (input[i] == ',' || i == input.size())
        {
            splitCoefficients.push_back(coefficients);
            coefficients.clear();
        }
        else
            coefficients.push_back(input[i]);
    }
    return splitCoefficients;
}

vector<char> getNumerator(const vector<char> &coefficient)
{
    vector<char> numerator;
    for (int i = 0; i < coefficient.size() && coefficient[i] != '/'; i++)
        numerator.push_back(coefficient[i]);
    return numerator;
}
vector<char> getDenominator(const vector<char> &coefficient)
{
    int start = 0;
    for (int i = 0; i < coefficient.size(); i++)
    {
        start++;
        if (coefficient[i] == '/')
            break;
    }
    if (start == coefficient.size())
        return vector{'1'};

    vector<char> denominator;
    for (int i = start; i < coefficient.size(); i++)
        denominator.push_back(coefficient[i]);
    return denominator;
}

int getDecimalDigitCount(const vector<char> &number)
{
    int startingIndex = 0;
    while (startingIndex < number.size() - 1 && number[startingIndex] != '.')
        startingIndex++;
    startingIndex++;
    return number.size() - startingIndex;
}

void removeDecimalPoint(vector<char> &number)
{
    vector<char> newNumber;
    for (int i = 0; i < number.size(); i++)
        if (number[i] != '.')
            newNumber.push_back(number[i]);
    number = newNumber;
}

void shiftDecimalPoint(vector<char> &number, const int &n, const int &positionsLeft)
{
    removeDecimalPoint(number);
    for (int i = positionsLeft; i < n; i++)
        number.push_back('0');
}

int toInt(const vector<char> &number)
{
    int result = 0;
    for (int i = 0; i < number.size(); i++)
        result = result * 10 + (number[i] - '0');
    return result;
}

pair<int, int> toFraction(const vector<char> &coefficient)
{
    vector<char> numerator = getNumerator(coefficient);
    vector<char> denominator = getDenominator(coefficient);
    int numeratorDecimalDigitCount = getDecimalDigitCount(numerator);
    const int denominatorDecimalDigitCount = getDecimalDigitCount(denominator);
    const int higher = max(numeratorDecimalDigitCount, denominatorDecimalDigitCount);

    shiftDecimalPoint(numerator, higher, numeratorDecimalDigitCount);
    shiftDecimalPoint(denominator, higher, denominatorDecimalDigitCount);

    const int convertedNumerator = toInt(numerator);
    const int convertedDenominator = toInt(denominator);

    return pair{convertedNumerator, convertedDenominator};
}

vector<pair<int, int>> getConvertedCoefficients(const vector<char> &input)
{
    const vector<vector<char>> splitCoefficients = getSplitCoefficients(input);

    vector<pair<int, int>> convertedCoefficients;
    for (int i = 0; i < splitCoefficients.size(); i++)
        convertedCoefficients.push_back(toFraction(splitCoefficients[i]));
    return convertedCoefficients;
}

void startLoop()
{
    cout << "give polynomial" << endl;
    vector<char> input = {'3', '.', '1', '4', '/', ',', '1', '/', '3'};
    vector<pair<int, int>> coefficients = getConvertedCoefficients(input);
    Polynomial firstPolynomial(coefficients);
    firstPolynomial.print();
}

int main()
{
    startLoop();

    return 0;
}
