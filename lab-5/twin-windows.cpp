//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main() {

    // ������� ������ VideoCapture ��� ������� ����� � ������
    // 0 - ����������� ������ ���-������
    cv::VideoCapture capOrig(0);
    cv::VideoCapture capProc(0);

    // ���������, ��������� �� ������
    if (!capOrig.isOpened()) {
        cout << "�� ������� ������� ������" << endl;
        return -1;
    }

    if (!capProc.isOpened()) {
        cout << "�� ������� ������� ������" << endl;
        return -1;
    }

    // ������� ���� ��� ����������� �����������
    /**
     * ������� ����, ������� ����� ������������ � �������� ����������� ��� ����������� � ���������. �� ��������� ���� ��������� �� �� ������. ���� ���� � ����� �� ������ ��� ����������, ������� ������ �� ������. �� ������ ������� cv::DestroyWindow ��� cv::destroyAllWindows, ����� ������� ���� � �������� ��������� ����� ��������� � ��� ������. ��� ������� ��������� ��� �� ����� ���� �� ����� �������� ��� �������, ������ ��� ��� ������� � ���� ���������� ������������� ����������� ������������ �������� ��� ������.
     */
    cv::namedWindow("Video Stream Orig", cv::WINDOW_NORMAL);     // Video Stream - �������� ����; WINDOW_NORMAL - ������ ����
    cv::namedWindow("Video Stream Proc", cv::WINDOW_NORMAL);

    while (true) {
        cv::Mat frameOrig;
        cv::Mat frameProc;

        // ��������� ���� �� �����������
        capOrig.read(frameOrig);
        capProc.read(frameProc);

        // ���� ���� ������� ������, ���������� ���
        if (!frameOrig.empty()) {
            cv::imshow("Video Stream Orig", frameOrig);
        }

        cv::cvtColor(frameOrig, frameProc, cv::COLOR_BGR2GRAY);

        if (!frameProc.empty()) {
            cv::imshow("Video Stream Proc", frameProc);
        }

        // ��� ����������� ������ ��������� ������� ������� 'q'
        if (cv::waitKey(33) == 'q') {
            break;
        }
    }

    // ����������� �������
    capOrig.release();
    capProc.release();
    cv::destroyAllWindows();

    return 0;
}

