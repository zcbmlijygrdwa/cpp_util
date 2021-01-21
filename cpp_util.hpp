#ifndef CPP_UTIL_HPP
#define CPP_UTIL_HPP

#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using Milliseconds = std::chrono::milliseconds;
using Nanoseconds = std::chrono::nanoseconds;

inline Clock::time_point tic()
{
    return Clock::now();
}


inline double toc(Clock::time_point t0)
{
    Clock::time_point t1 = std::chrono::high_resolution_clock::now();
    //Milliseconds ms = std::chrono::duration_cast<Milliseconds>(t1 - t0);
    Nanoseconds ns = std::chrono::duration_cast<Nanoseconds>(t1 - t0);
    //std::cout <<"\nElapsed time is "<< ms.count() << " milliseconds\n";

    return ns.count()/1000000000.0f;
    //return ms.count()/1000.0f;
}

template <class T>
void printVector(std::vector<T> vec, std::string message = "")
{
    std::cout<<" --- vector "<<message<< " ("<<vec.size()<<" elements) ---" <<std::endl;
    for(int i = 0 ; i < vec.size() ; i++)
    {
        std::cout<<message<<"["<<i<<"] = "<<vec[i]<<std::endl;
    }
}
#define printvec(variable) printVector(variable, #variable)

template<class T>
void printVariable(T variable, std::string message="")
{
    std::cout<<std::setprecision(16)<<message<<" = "<<variable<<std::endl;
}

#define printv(variable) printVariable(variable, #variable)

template<class T>
void printVariablePause(T variable, std::string message="")
{
    std::cout<<std::setprecision(16)<<message<<" = "<<variable<<std::endl;
    std::cout<<"paused here, enter to continue..."<<std::endl;
    std::cin.get();
}

#define printvP(variable) printVariablePause(variable, #variable)

template<class T>
void assertEquals(T expected, T actual,std::string message="")
{
    if(std::abs(expected - actual)<0.0001)
    {
        std::cout << "[PASSED]: " << message << std::endl;;
    } else {
        std::cout << "   [FAILED...]: " << message << std::endl
            << "     Expected: " << expected << " Actual: " << actual << std::endl;
    }
}

#define ASSERT_EQUALS(expected,actual) assertEquals(expected,actual,#actual)

void readFileToBuffer(char* file_path, char** file_data_buffer, size_t* file_size_bytes)
{
    //open file
    std::ifstream infile(file_path);

    //get length of file
    infile.seekg(0, std::ios::end);
    *file_size_bytes = infile.tellg();
    infile.seekg(0, std::ios::beg);

    printv(*file_size_bytes);

    *file_data_buffer = (char*)calloc(*file_size_bytes, sizeof(char));

    //read file
    infile.read(*file_data_buffer, *file_size_bytes);

    infile.close();
}


char computeChecksum(void* buffer, long data_size_byte)
{
    char checksum = 0;
    for(long i = 0 ; i < data_size_byte ; i++)
    {
        checksum = checksum + ((char*)buffer)[i];
    }

    return checksum;
}

#endif
