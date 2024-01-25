#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/types.hpp>
#include <iostream>
#include <string>
#include <time.h>

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        return -1;
    }

    bool camera_filter = false;
    Mat frame, edges;
    clock_t start, finish;
    double count_fps = 0, time_to_read = 0, time_to_read2 = 0, time_to_display = 0, time_to_convert = 0;
    int count_frame = 0;
    clock_t total_start, total_finish;

    total_start = clock();
    while (count_frame != 1000)
    {
        start = clock();

        cap >> frame;

        finish = clock();

        time_to_read2 = time_to_read;
        time_to_read = double(finish - start);

        start = clock();

        string text_to_read = "time to read " + to_string(time_to_read2 / CLOCKS_PER_SEC);
        string text_to_convert = "time to convert" + to_string(time_to_convert / CLOCKS_PER_SEC);
        string text_to_display = "time to display " + to_string(time_to_display / CLOCKS_PER_SEC);
        string fps =  "fps" + to_string(int(count_fps * CLOCKS_PER_SEC));

        if (camera_filter)
        {
            cvtColor(frame, edges, COLOR_BGR2GRAY);
            GaussianBlur(edges, edges, Size(7,7), 2, 2);
            Canny(edges, edges, 0, 30, 3);

            putText(edges, text_to_read, Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(edges, text_to_convert, Point(30, 60), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(edges, text_to_display, Point(30, 90), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(edges, fps, Point(30, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));

            finish = clock();
            time_to_convert = double(finish - start);

            start = clock();

            imshow("picture", edges);
        }
        else
        {
            putText(frame, text_to_read, Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(frame, text_to_convert, Point(30, 60), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(frame, text_to_display, Point(30, 90), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(frame, fps, Point(30, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));

            finish = clock();
            time_to_convert = double(finish - start);

            start = clock();

            imshow("picture", frame);
        }

        char c = waitKey(33);
        if (c == 27)
        {
            break;
        }
        else if (c == 97 && !camera_filter)
        {
            camera_filter = true;
        }
        else if (c == 97 && camera_filter)
        {
            camera_filter = false;
        }

        finish = clock();
        time_to_display = double(finish - start);
        count_fps = 1.0 / (time_to_read2 + time_to_display + time_to_convert);
        count_frame++;
    }

    total_finish = clock();
    double sr_fps = count_frame / double(total_finish - total_start) * CLOCKS_PER_SEC;
    cout << double(total_finish - total_start) / CLOCKS_PER_SEC;
    return 0;
}