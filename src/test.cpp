#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "common.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Parser
    CommandLineParser parser(argc, argv, parser_keys);
    string input_image = parser.get<string>("input");
    string output_image = parser.get<string>("output");
    string output_csv = parser.get<string>("csv");
    int ni = parser.get<int>("ni");

    std::vector<float> times_fft = std::vector<float>();
    std::vector<float> times_ifft = std::vector<float>();
    std::vector<float> times_total = std::vector<float>();

    //Read image
    Mat input = imread(input_image, IMREAD_GRAYSCALE);
    
    for (int iter = 0; iter < ni; iter++)
    {
        Mat planes[] = { Mat_<float>(input), Mat::zeros(input.size(), CV_32F) };
        Mat complexImage;
        merge(planes, 2, complexImage);


        auto start_total = timer::now();
        auto start_fft = timer::now();

        // Applying DFT
        dft(complexImage, complexImage);

        auto end_fft = timer::now();

        Mat invDFTimage, output;
        auto start_ifft = timer::now();

        // Applying IDFT
        idft(complexImage, invDFTimage, DFT_SCALE | DFT_REAL_OUTPUT);

        auto end_ifft = timer::now();

        invDFTimage.convertTo(output, CV_8U);

        auto end_total = timer::now();

        imwrite(output_image, output);

        float time_fft = time_msec(start_fft, end_fft);
        float time_ifft = time_msec(start_ifft, end_ifft);
        float time_total = time_msec(start_total, end_total);

        times_fft.push_back(time_fft);
        times_ifft.push_back(time_ifft);
        times_total.push_back(time_total);
    }
    sort(times_fft.begin(), times_fft.end());
    sort(times_ifft.begin(), times_ifft.end());
    sort(times_total.begin(), times_total.end());

    float time_fft = times_fft[ni/2];
    float time_ifft = times_ifft[ni / 2];
    float time_total = times_total[ni / 2];

    save_results(output_csv, input_image, CV_VERSION, ni,
        time_fft * 0.001, time_ifft * 0.001, time_total * 0.001);

	return 0;
}