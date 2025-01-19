#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

using namespace std;

vector<vector<char>> splitByComma(const vector<char> &input)
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

int toInt(const vector<char> &number)
{
    bool isNegative = false;
    int result = 0;
    for (int i = 0; i < number.size(); i++)
        if (number[i] != '.')
        {
            if (number[i] == '-')
            {
                isNegative = true;
                continue;
            }
            result = result * 10 + (number[i] - '0');
        }
    if (isNegative)
        result *= -1;
    return result;
}

pair<int, int> parseCoefficient(const vector<char> &coefficient)
{
    const vector<char> numerator = getNumerator(coefficient);
    const vector<char> denominator = getDenominator(coefficient);
    const int numeratorDecimalDigitCount = getDecimalDigitCount(numerator);
    const int denominatorDecimalDigitCount = getDecimalDigitCount(denominator);
    const int higher = max(numeratorDecimalDigitCount, denominatorDecimalDigitCount);

    int parsedNumerator = toInt(numerator);
    int parsedDenominator = toInt(denominator);

    parsedNumerator *= pow(10, higher - numeratorDecimalDigitCount);
    parsedDenominator *= pow(10, higher - denominatorDecimalDigitCount);

    return pair{parsedNumerator, parsedDenominator};
}

vector<pair<int, int>> parseCoefficients(const vector<char> &input)
{
    const vector<vector<char>> splitCoefficients = splitByComma(input);

    vector<pair<int, int>> convertedCoefficients;
    for (int i = 0; i < splitCoefficients.size(); i++)
        convertedCoefficients.push_back(parseCoefficient(splitCoefficients[i]));
    return convertedCoefficients;
}

int findGCD(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int findLCD(const int a, const int b)
{
    int gcd = findGCD(a, b);
    return a * b / gcd;
}

void rewriteWithCommonDenominators(pair<int, int> &a, pair<int, int> &b)
{
    const int denominatorA = a.second;
    const int denominatorB = b.second;
    const int lcd = findLCD(denominatorA, denominatorB);
    const int multiplicatorA = lcd / denominatorA;
    const int multiplicatorB = lcd / denominatorB;

    a.first *= multiplicatorA;
    a.second *= multiplicatorA;
    b.first *= multiplicatorB;
    b.second *= multiplicatorB;
}

void simplify(pair<int, int> &fraction)
{
    const int gcd = findGCD(fraction.first, fraction.second);
    fraction.first /= gcd;
    fraction.second /= gcd;
}

pair<int, int> addFractions(pair<int, int> a, pair<int, int> b) // TODO unite methods
{
    rewriteWithCommonDenominators(a, b);
    pair<int, int> sum;
    sum.first = a.first + b.first;
    sum.second = a.second;
    simplify(sum);
    return sum;
}

pair<int, int> subtractFractions(pair<int, int> a, pair<int, int> b)
{
    rewriteWithCommonDenominators(a, b);
    pair<int, int> difference;
    difference.first = a.first - b.first;
    difference.second = a.second;
    simplify(difference);
    return difference;
}

pair<int, int> multiplyFractions(pair<int, int> a, pair<int, int> b)
{
    pair<int, int> product;
    product.first = a.first * b.first;
    product.second = a.second * b.second;
    simplify(product);
    return product;
}

pair<int, int> divideFractions(pair<int, int> a, pair<int, int> b)
{
    pair<int, int> quotient;
    quotient.first = a.first * b.second;
    quotient.second = a.second * b.first;
    simplify(quotient);
    return quotient;
}

vector<pair<int, int>> divisors(const pair<int, int> &fraction)
{
    vector<pair<int, int>> divisors;
    int numerator = fraction.first;
    int denominator = fraction.second;
    for (int i = 1; i <= numerator; i++)
    {
        if (numerator % i != 0)
            continue;
        for (int j = 1; j <= denominator; j++)
        {
            if (denominator % j != 0)
                continue;
            divisors.push_back({i, j});
            divisors.push_back({-i, j});
        }
    }
    return divisors;
}

bool contains(const pair<int, int> &element, const vector<pair<int, int>> &possibleRoots)
{
    for (int i = 0; i < possibleRoots.size(); i++)
        if (possibleRoots[i] == element)
            return true;
    return false;
}

void replaceZeroDenominators(vector<pair<int, int>> &coefficients)
{
    for (int i = 0; i < coefficients.size(); i++)
        if (coefficients[i].second == 0)
            coefficients[i] = {0, 1};
}

void removeLastZeros(vector<pair<int, int>> &coefficients)
{
    int indexesToBeRemoved = 0;
    int coefficientSize = coefficients.size();
    for (int i = 0; i < coefficientSize; i++)
        if (coefficients[coefficientSize - 1 - i].first == 0)
            indexesToBeRemoved++;
        else
            break;
    vector<pair<int, int>> cleanedCoefficients(coefficientSize - indexesToBeRemoved);
    for (int i = 0; i < cleanedCoefficients.size(); i++)
        cleanedCoefficients[i] = coefficients[i];
    coefficients = cleanedCoefficients;
}

class Polynomial
{
private:
    vector<pair<int, int>> coefficients;

public:
    Polynomial(const vector<pair<int, int>> &coefficients)
    {
        this->coefficients = coefficients;
    }

    vector<pair<int, int>> getCoefficients()
    {
        return coefficients;
    }

    Polynomial add(Polynomial &other)
    {
        return operateWith(other, '+');
    }

    Polynomial subtract(Polynomial &other)
    {
        return operateWith(other, '-');
    }

    Polynomial multiply(Polynomial &other)
    {
        const int thisSize = coefficients.size();
        const int otherSize = other.getCoefficients().size();
        vector<pair<int, int>> multipliedCoefficients(thisSize + otherSize - 1);
        replaceZeroDenominators(multipliedCoefficients);
        for (int i = 0; i < coefficients.size(); i++)
            for (int j = 0; j < other.coefficients.size(); j++)
            {
                const pair<int, int> thisValue = getCoefficientAt(i);
                const pair<int, int> otherValue = other.getCoefficientAt(j);
                const pair<int, int> multipliedValue = multiplyFractions(thisValue, otherValue);
                multipliedCoefficients[i + j] = addFractions(multipliedCoefficients[i + j], multipliedValue);
            }
        return Polynomial(multipliedCoefficients).removedLastZeros();
    }

    Polynomial divide(Polynomial divisor)
    {
        const vector<pair<int, int>> divisorCoefficients = divisor.getCoefficients();
        Polynomial dividend(coefficients);
        vector<pair<int, int>> dividendCoefficients = dividend.getCoefficients();

        int dividendSize = dividendCoefficients.size();
        int divisorSize = divisorCoefficients.size();
        const int quotientSize = dividendCoefficients.size() - divisorCoefficients.size() + 1;
        if (dividendSize < divisorSize)
        {
            return Polynomial({{0, 1}});
        }
        vector<pair<int, int>> quotient(quotientSize);
        for (int i = 0; i < quotientSize; i++)
            quotient[i].second = 1;
        for (int i = 0; i < quotientSize; i++)
        {
            quotient[quotientSize - 1 - i] = divideFractions(dividendCoefficients[dividendSize - 1], divisorCoefficients[divisorSize - 1]);
            vector<pair<int, int>> tempCoefficients(dividendSize);
            for (int j = 0; j < divisorSize; j++)
                tempCoefficients[dividendSize - 1 - j] = multiplyFractions(quotient[quotientSize - 1 - i], divisorCoefficients[divisorSize - 1 - j]);
            replaceZeroDenominators(tempCoefficients);
            Polynomial tempPolynomial(tempCoefficients);
            dividend = dividend.subtract(tempPolynomial);
            dividendCoefficients = dividend.getCoefficients();
            i += dividendSize - dividendCoefficients.size() - 1;
            dividendSize = dividendCoefficients.size();
            if (dividendSize < divisorSize)
                return Polynomial(quotient).removedLastZeros();
        }
    }

    pair<int, int> valueForX(const pair<int, int> &x)
    {
        pair<int, int> value = {0, 1};
        for (int i = 0; i < coefficients.size(); i++)
            value = addFractions(value, multiplyFractions(powFraction(x, i), coefficients[i]));
        return value;
    }

    Polynomial multiply(const pair<int, int> &factor)
    {
        for (int i = 0; i < coefficients.size(); i++)
            coefficients[i] = multiplyFractions(coefficients[i], factor);
        return Polynomial(coefficients).removedLastZeros();
    }

    Polynomial remainder(Polynomial divisor, Polynomial quotient)
    {
        Polynomial toBeSubtracted = divisor.multiply(quotient);
        Polynomial toBeReturned = subtract(toBeSubtracted);
        return toBeReturned.removedLastZeros();
    }

    vector<pair<int, int>> roots()
    {
        Polynomial substitute(coefficients);
        substitute = substitute.removedLastZeros();
        vector<pair<int, int>> rootsVector;
        const vector<pair<int, int>> possibles = substitute.possibleRoots();
        for (int i = 0; i < possibles.size(); i++)
            if (substitute.valueForX(possibles[i]).first == 0)
            {
                pair<int, int> root = possibles[i];
                rootsVector.push_back(root);
                root.first *= -1;
                substitute = substitute.divide(Polynomial({root, {1, 1}}));
                i--;
            }
        return rootsVector;
    }

    void printDecomposition(const vector<pair<int, int>> &roots)
    {
        // for (int i = 0; i < roots.size(); i++)
        // {
        //     const int numerator = roots[i].first;
        //     const int denominator = roots[i].second;
        //     if (numerator == 0)
        //         cout << 'x';
        //     else if (denominator == 1)
        //         if (numerator < 0)
        //             cout << "(x + " << numerator * (-1) << ')';
        //         else
        //             cout << "(x - " << numerator << ')';
        //     else if (numerator < 0)
        //         cout
        //             << "(x + " << numerator * (-1) << '/' << denominator << ')';
        //     else
        //         cout << "(x - " << numerator << '/' << denominator << ')';
        //     int degree = 1;
        //     for (int j = i + 1; j < roots.size(); j++)
        //         if (roots[j] == roots[i])
        //             degree++;
        //     if (degree > 1)
        //     {
        //         cout << '^' << degree;
        //         i += degree - 1;
        //     }
        // }
        Polynomial dividend(coefficients);
        for (int i = 0; i < roots.size(); i++)
        {
            const int numerator = roots[i].first;
            const int denominator = roots[i].second;
            Polynomial divisor({{numerator*(-1), denominator}, {1, 1}});
            divisor.print();
            dividend = dividend.divide(divisor);
        }
        if(dividend.getCoefficients().size()!=0)
            dividend.print();
    }

    Polynomial findGCD(Polynomial divisor)
    {
        Polynomial dividend(coefficients);
        if (coefficients.size() < divisor.getCoefficients().size())
        {
            Polynomial temp = dividend;
            dividend = divisor;
            divisor = temp;
        }
        while (true)
        {
            Polynomial quotient = dividend.divide(divisor);
            Polynomial remaind = dividend.remainder(divisor, quotient);
            if (remaind.getCoefficients().size() == 0)
                return divisor.divide(divisor.getCoefficientAt(divisor.getCoefficients().size() - 1));
            dividend = divisor;
            divisor = remaind;
        }
    }

    void printVietasFormulas() // TODO the whole method
    {
        int n = 4;
        for (int i = 1; i <= 2; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                for (int k = 1; k <= j; k++)
                {
                    for (int l = k + 1; l <= n; l++)
                    {
                    }
                }
            }
            cout << endl;
        }
    }

    Polynomial changeArgument(const pair<int, int> &addend)
    {
        const int polynomialSize = coefficients.size();
        vector<pair<int, int>> toBeReturnedCoefficients(polynomialSize);
        toBeReturnedCoefficients[0] = coefficients[0];
        replaceZeroDenominators(toBeReturnedCoefficients);
        Polynomial toBeReturned(toBeReturnedCoefficients);
        Polynomial multiplicator({{addend}, {1, 1}});
        for (int i = 1; i < polynomialSize; i++)
        {
            Polynomial toBeAdded({{addend}, {1, 1}});
            for (int j = 1; j < i; j++)
                toBeAdded = toBeAdded.multiply(multiplicator);
            toBeAdded.multiply(coefficients[i]);
            toBeReturned = toBeReturned.add(toBeAdded);
        }
        return toBeReturned;
    }
    void print()
    {

        for (int i = 0; i < coefficients.size(); i++)
        {
            const int numerator = coefficients[i].first;
            const int denominator = coefficients[i].second;
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
            if (i != coefficients.size() - 1)
                cout << " + ";
        }
        cout << endl;
    }

    pair<int, int> getCoefficientAt(const int &index)
    {
        if (index < coefficients.size())
            return coefficients[index];
        return pair{0, 1};
    }

private:
    Polynomial operateWith(Polynomial other, char function)
    {
        const int thisSize = coefficients.size();
        const int otherSize = other.getCoefficients().size();
        const int higherSize = max(thisSize, otherSize);

        vector<pair<int, int>> summedCoefficients;
        for (int i = 0; i < higherSize; i++)
        {
            pair<int, int> thisValue = getCoefficientAt(i);
            pair<int, int> otherValue = other.getCoefficientAt(i);
            if (function == '+')
                summedCoefficients.push_back(addFractions(thisValue, otherValue));
            else if (function == '-')
                summedCoefficients.push_back(subtractFractions(thisValue, otherValue));
        }
        return Polynomial(summedCoefficients).removedLastZeros();
    }

    Polynomial removedLastZeros()
    {
        vector<pair<int, int>> removedLastZerosCoefficient = coefficients;
        removeLastZeros(removedLastZerosCoefficient);
        return Polynomial(removedLastZerosCoefficient);
    }

    pair<int, int> powFraction(pair<int, int> fraction, const int &n)
    {
        fraction.first = pow(fraction.first, n);
        fraction.second = pow(fraction.second, n);
        return fraction;
    }

    vector<pair<int, int>> possibleRoots()
    {
        vector<pair<int, int>> roots;
        if (coefficients.size() == 2)
        {
            pair<int, int> firstCoefficient = coefficients[0];
            firstCoefficient.first *= -1;
            pair<int, int> root = divideFractions(firstCoefficient, coefficients[1]);
            roots.push_back(root);
            return roots;
        }
        // let l = lastCoefficientDivisors and f = firstCoefficientDivisors
        const vector<pair<int, int>> l = divisors(coefficients[coefficients.size() - 1]);
        const vector<pair<int, int>> f = divisors(coefficients[0]);
        for (int i = 0; i < f.size(); i++)
            for (int j = 0; j < l.size(); j++)
            {
                pair<int, int> possibleRoot = divideFractions(f[i], l[j]);
                if (possibleRoot.second < 0)
                {
                    possibleRoot.second *= -1;
                    possibleRoot.first *= -1;
                }
                if (!contains(possibleRoot, roots))
                    roots.push_back(possibleRoot);
            }
        return roots;
    }

    Polynomial divide(const pair<int, int> &divisor)
    {
        pair<int, int> factor;
        factor.first = divisor.second;
        factor.second = divisor.first;
        return multiply(factor);
    }
};

vector<char> polynomialInput()
{
    vector<char> input;
    char symbol;
    cin >> symbol;
    while (symbol != 's')
    {
        input.push_back(symbol);
        cin >> symbol;
    }
    return input;
}

Polynomial askForPolynomial()
{
    const vector<char> input = polynomialInput();
    vector<pair<int, int>> coefficients = parseCoefficients(input);
    for (int i = 0; i < coefficients.size(); i++)
        simplify(coefficients[i]);
    return Polynomial(coefficients);
}

void startLoop()
{
    while (true)
    {
        cout << "Type:" << endl
             << "1) to add two polinomials" << endl
             << "2) to subtract two polinomials" << endl
             << "3) to multiply two polinomials" << endl
             << "4) to divide two polinomials" << endl
             << "5) to multiply polinomial by a rational number" << endl
             << "6) to find the value of a polinomial for a rational number" << endl
             << "7) to find the GCD of two polinomials" << endl
             << "8) to see Vieta's formulas for a polinomial" << endl
             << "9) to change the argument of a polinomial to (x+a) where \"a\" is a rational number" << endl
             << "10) to decompose a polinomial" << endl
             << endl;

        int option;
        cin >> option;

        cout << endl
             << "Type polinomial coefficients and then \"s\" when ending. For example:" << endl
             << "\"1, 2, 1s\" would be: 1 + 2x + x^2" << endl
             << endl;

        Polynomial polinomial = askForPolynomial();
        cout << "Your polinomial:" << endl;
        polinomial.print();
        cout << endl;

        Polynomial anotherPolinomial({{0, 0}});
        Polynomial fractionContainer({{0, 0}});
        pair<int, int> fraction;
        if (option == 1 || option == 2 || option == 3 || option == 4 || option == 7)
        {
            cout << "Type second polinomial's coefficients" << endl
                 << endl;
            anotherPolinomial = askForPolynomial();
            cout << "Your second polinomial:" << endl;
            anotherPolinomial.print();
            cout << endl;
        }

        else if (option == 5 || option == 6 || option == 9)
        {
            cout << "Type rational number" << endl
                 << endl;
            fractionContainer = askForPolynomial();
            fraction = fractionContainer.getCoefficientAt(0);
        }

        switch (option)
        {
        case 1:
        {
            Polynomial sum = polinomial.add(anotherPolinomial);
            cout << "Sum:" << endl;
            if (sum.getCoefficients().size() != 0)
                sum.print();
            else
                cout << 0 << endl;
            break;
        }
        case 2:
        {
            Polynomial difference = polinomial.subtract(anotherPolinomial);
            cout << "Difference:" << endl;
            if (difference.getCoefficients().size() != 0)
                difference.print();
            else
                cout << 0 << endl;
            break;
        }
        case 3:
        {
            Polynomial product = polinomial.multiply(anotherPolinomial);
            cout << "Product:" << endl;
            if (product.getCoefficients().size() != 0)
                product.print();
            else
                cout << 0 << endl;
            break;
        }
        case 4:
        {
            Polynomial quotient = polinomial.divide(anotherPolinomial);
            cout << "Quotient:" << endl;
            quotient.print();
            Polynomial remainde = polinomial.remainder(anotherPolinomial, quotient);
            cout << "remainder:" << endl;
            if (remainde.getCoefficients().size() != 0)
                remainde.print();
            else
                cout << 0;
            break;
        }
        case 5:
        {
            Polynomial product = polinomial.multiply(fraction);
            cout << endl
                 << "Product:" << endl;
            product.print();
            break;
        }
        case 6:
        {
            pair<int, int> valueForX = polinomial.valueForX(fraction);
            cout << endl
                 << "Value:" << endl;
            if (valueForX.second == 1)
                cout << valueForX.first;
            else
                cout << '(' << valueForX.first << '/' << valueForX.second << ')';
            break;
        }
        case 7:
        {
            Polynomial gcd = polinomial.findGCD(anotherPolinomial);
            cout << "GCD:" << endl;
            gcd.print();
            break;
        }
        case 9:
        {
            Polynomial withChangedArgument = polinomial.changeArgument(fraction);
            cout << endl
                 << "New polinomial:" << endl;
            withChangedArgument.print();
            break;
        }
        case 10:
        {
            vector<pair<int, int>> root = polinomial.roots();
            cout << endl
                 << "Decomposition:" << endl;
            polinomial.printDecomposition(root);
            break;
        }
        }
        cout << endl
             << endl;
    }
}

int main()
{
    startLoop();
    return 0;
}
