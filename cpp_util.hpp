#ifndef CPP_UTIL_HPP
#define CPP_UTIL_HPP

#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>

#include <chrono>

#include <dirent.h>
#include <sys/types.h>

#include <algorithm>

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

inline void readFileToBuffer(char* file_path, unsigned char** file_data_buffer, size_t* file_size_bytes)
{
    //open file
    std::ifstream infile(file_path);

    //get length of file
    infile.seekg(0, std::ios::end);
    *file_size_bytes = infile.tellg();
    infile.seekg(0, std::ios::beg);

    printv(*file_size_bytes);

    *file_data_buffer = (unsigned char*)calloc(*file_size_bytes, sizeof(unsigned char));

    //read file
    infile.read((char*)(*file_data_buffer), *file_size_bytes);

    infile.close();
}


inline char computeChecksum(void* buffer, long data_size_byte)
{
    char checksum = 0;
    for(long i = 0 ; i < data_size_byte ; i++)
    {
        checksum = checksum + ((char*)buffer)[i];
    }

    return checksum;
}

inline std::vector<std::string> readLinesFromTxt(std::string file_name)
{

    std::vector<std::string> output;
    std::string temp_str;

    std::ifstream myReadFile;
    myReadFile.open(file_name);
    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {

            getline(myReadFile, temp_str); // Saves the line in STRING.

            if(temp_str.length() > 0)
            {
                //printv(temp_str);
                output.push_back(temp_str);
            }
        }
    }
    myReadFile.close();

    return output;
}

inline std::vector<std::string> splitString(std::string str, std::string delimiter)
{
    std::vector<std::string> output;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        //std::cout << token << std::endl;
        output.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    //std::cout << str << std::endl;
    output.push_back(str);

    return output;
}

inline std::vector<std::string> getFileListAtDir(std::string path)
{
    std::vector<std::string> output;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
            std::string temp_name = ent->d_name;
            if(temp_name.compare(".")==0 || temp_name.compare("..")==0)
                continue;
            output.push_back(ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("Error: Could not open directory");
    }

    std::sort(output.begin(), output.end());

    return output;
}


#endif
