// Level1_Section1.5_Exercise4.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Exercise 4: Adapters for STL algorithms
a) Given a sorted numeric vector v and a target value x ,
   find the first index i, such that:?
        v[i] <= x < v [i+1]?
   Determine the return type.

b) Find the maximum error between two vectors v1 and v2 in a given index range [i; j] .
We wish to compute the difference in some (customisable) norm, specifically the
absolute error, relative error and the index values where these errors occur.
Use:
1. move semantics instead of copy constructors
2. smart pointers
3. function objects and lambda functions
4. STL algorithms

*/

#include <iostream>
#include <vector>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iterator>

template <typename T, typename Vec, typename Return_t>
struct useAdapters
{
    // Statistical Properties 
    static Return_t tgtIndex(const Vec& inVec, T tgtVal, std::size_t N)
    {
        // Part A) sorted numeric vector v and a target value x , 
        //         find the first index i, such that: v[i] <= x < v[i + 1]?

        // Edge Cases: 
        // 1. The target value is not in the vector range (ie. x = 0 or 4 & v = {1,2,3})
        //         ** if x = 0 then will return "not in range" and output -1 
        //         ** if x = 4 then will return "not in range" and output inVecTmp.end()
        // 2. The target value is the last value in the vector range so no i+1 or upper bound
        //          (ie. x = 4 & v = {1,2,3,4) or v = {1,2,3,4,4})
        //          (ie. x = 4.3 & v = {1,2,3,4} 
        //          ** will return lower bound but "upper bound not in range" and upper bound is inVecTmp.end()


        // Change N to an int M so can use for indexing 
        int M = static_cast<int>(N);
        // first sort vector in case not sorted 
        Vec inVecTmp = inVec; // making local copy since const 
        std::sort(inVecTmp.begin(), inVecTmp.end());

        // Printing contents of vector
        std::cout << "\nVector is: "; 
        for (size_t i = 0; i < inVecTmp.size(); ++i) {std::cout << inVecTmp.at(i) << "; "; }

        // first check if the target value (x) exists in the vector
        if (std::find(inVecTmp.begin(), inVecTmp.end(), tgtVal) != inVecTmp.end())
            // since target exists can work to finding i-1 and i+1 
        {
            // checking to see if there are multiple target values 
            std::cout << "\nEntered if loop";
            auto lBnd = std::find(inVecTmp.begin(), inVecTmp.end(), tgtVal);
            auto nxtVal = std::find(inVecTmp.begin(), inVecTmp.end(), tgtVal);

            std::cout << "\nTarget is: " << tgtVal;
            std::cout << "\nLower bound is: " << lBnd - inVecTmp.begin();

            if (nxtVal != inVecTmp.end())
            {
                // setting upper bound the same as lower bound and then will increment
                auto uBnd = std::find(inVecTmp.begin(), inVecTmp.end(), tgtVal);
                
                // Part B) if multiple target values use distance to find how many  
                auto uTgt = std::upper_bound(lBnd, inVecTmp.end(), tgtVal);
                
                // finding the number of tgt values using distance (returns an int) 
                int dist = std::distance(lBnd, uTgt);
                
                // increasing lBnd by the number of tgt values to get upper bound  
                std::advance(uBnd, dist);
                std::cout << "\nUpper bound is: " << uBnd - inVecTmp.begin();
            }
            else
            {
                std::cout << "\nUpper bound is: " << nxtVal - inVecTmp.begin()<< std::endl;
            }

            // Getting return values: 
            int intIt = inVecTmp[0] + std::distance(inVecTmp.begin(), std::find(inVecTmp.begin(), inVecTmp.end(), tgtVal));

            return intIt;
        } // end of if (std::find(inVecTmp.begin(), inVecTmp.end(), tgtVal) != inVecTmp.end())

        else if ((inVecTmp[0] <= tgtVal) && (inVecTmp[M - 1] > tgtVal)) // if target does not exist then need to see if target value is btwn vector values 
        {
            std::cout << "\nEntered else loop";


            // find what indexes it is inbetween 
            for (int i = 1; i < M; i++) //iterator through finding min distance value 
            {
                // checking to see if the target value is in range & if so find upper & lower bound 
                if (tgtVal - inVecTmp[i - 1] >= 0 && tgtVal - inVecTmp[i] <= 0)
                {
                    T Lbnd = inVecTmp[i - 1];
                    T Ubnd = inVecTmp[i];
                    int Lidx = i - 1;
                    std::cout << "\nTarget is: " << tgtVal;
                    std::cout << "\nLower bound is: " << i - 1;
                    std::cout << "\nUpper bound is: " << i; 
                    std::cout << "\nLower value is: " << Lbnd;
                    std::cout << "\nUpper value is: " << Ubnd << std::endl;
                    
                    // returning lower index 
                    return Lidx;
                }
                // Do not need to check for multiple values
            }

        } // end of ((inVecTmp[0] <= tgtVal) && (inVecTmp[M - 1] > tgtVal))

        else
        {
            std::cout << "\nTarget value is not in range";
            if (tgtVal < inVecTmp[0])
            {
                std::cout << "\nTarget value is less than smallest value";
                // returning error value int error = -1 
                int error = -1; 
                return error;
            }
            else
            {
                std::cout << "\nTarget value is greater than largest value";
                int error = M-1;
                return error;
            }

        } // end of else 
    } // end function --> numAnalysis(const Vec& inVec, T tgtVal, std::size_t N)


    static std::vector<double> vectMax(const Vec& inVec1, const Vec& inVec2, std::size_t N, int i, int j)
    {
        // Change N to an int M so can use for indexing 
        int M = static_cast<int>(N);

        // first sort vector in case not sorted 
        Vec inVecTmp1 = inVec1; // making local copy since const 
        Vec inVecTmp2 = inVec2; // making local copy since const 
        std::sort(inVecTmp1.begin(), inVecTmp1.end());
        std::sort(inVecTmp2.begin(), inVecTmp2.end());

        // Printing contents of two vectors 
        std::cout << "\nVector 1 is: ";
        for (size_t i = 0; i < inVecTmp1.size(); ++i) { std::cout << inVecTmp1.at(i) << "; "; }
       
        std::cout << "\nVector 2 is: ";
        for (size_t i = 0; i < inVecTmp2.size(); ++i) { std::cout << inVecTmp2.at(i) << "; "; }

        // first check that vectors are larger than second index value 
        if (j >= inVecTmp1.end() || j >= inVecTmp2.end())
        {
            std::cout << "\nJ index is out of bounds of one of the vectors"; 
            return -1; 
        }

        else
        {
            double sum = 0; 
            for (int iter = i; iter = j; iter++)
            {

                int normDim = std::distance()
                sum += ((inVecTmp1[iter]-inVecTmp2[iter])^normDim)
            }
        }
    }
};

int main()
{
    // creating use case where target value exists 
    std::cout << "\nFour element vector tgt exists:";
    const std::size_t M = 4;
    std::vector<double> b4(M);
    double val4 = 3;
    std::vector<double> incr = { 0.1, 1.8, 1, 1};
    int j = 0;
    std::for_each(b4.begin(), b4.end(), [&val4, &incr, &j](double& k) {k = val4 + incr[j]; j++; });
    double tgtExst = 4; 
        
    double b4Out1 = useAdapters<double, std::vector<double>, double>::tgtIndex(b4, tgtExst, M);

    // creating use case where target value is between elements in vector
    std::cout << "\nFour element vector tgt is btwn elements:";
    double tgtBtwn = 4.5;
    double b4Out2 = useAdapters<double, std::vector<double>, double>::tgtIndex(b4, tgtBtwn, M);

    // creating use case where target value is smaller than first element in vector
    std::cout << "\nFour element vector tgt is smallest than first element:";
    double tgtSmall = 0.1;
    double b4Out3 = useAdapters<double, std::vector<double>, double>::tgtIndex(b4, tgtSmall, M);

    // creating use case where target value is greater than first element in a vector
    std::cout << "\nFour element vector tgt is larger than greatest element:";
    double tgtLarge = 10.1;
    double b4Out4 = useAdapters<double, std::vector<double>, double>::tgtIndex(b4, tgtLarge, M);

    // Printing all the index values and types 
    std::cout<<"\n";
    std::cout << "\nb4Out1 is: " << b4Out1 << " Type is: " << typeid(b4Out1).name(); 
    std::cout << "\nb4Out2 is: " << b4Out2 << " Type is: " << typeid(b4Out2).name();
    std::cout << "\nb4Out3 is: " << b4Out3 << " Type is: " << typeid(b4Out3).name();
    std::cout << "\nb4Out3 is: " << b4Out4 << " Type is: " << typeid(b4Out4).name();

}
