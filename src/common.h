#pragma once

#include <chrono>
#include <fstream>
#include <istream>
#include <string>

using namespace std;

// Timer code
typedef std::chrono::steady_clock timer;

long time_msec(std::chrono::time_point<std::chrono::steady_clock> start, 
    std::chrono::time_point<std::chrono::steady_clock> end)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Parser code

static const char* parser_keys =
{
    "{input      | | Path to input image before processing }"
    "{output     | | Path to output image after processing }"
    "{ni         | | Number of iterations                  }"
    "{csv        | | Path to file with results             }"
};

// Save results

void save_results(string fileName, string imageName, string libraryName,
    int iterations, float dft, float idft, float total)
{
    std::ifstream fin;
    fin.open(fileName);
    if (fin.is_open())
    {
        fin.close();
    }
    else
    {
        ofstream fout;
        fout.open(fileName);
        fout << "Input;OpenCV version;Iterations;DFT time; IDFT time; Total time\n";
        fout.close();
    }

    ofstream fout;
    fout.open(fileName, ofstream::out | ofstream::app);
    fout.precision(4);
    fout.width(8);
    fout << imageName << ";" << libraryName << ";" << iterations << ";" << dft << ";" << idft << ";" << total << "\n";
    fout.close();
}