//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main() {

    // Создаем объект VideoCapture для захвата видео с камеры
    // 0 - стандартный индекс веб-камеры
    cv::VideoCapture capOrig(0);
    cv::VideoCapture capProc(0);

    // Проверяем, открылась ли камера
    if (!capOrig.isOpened()) {
        cout << "Не удалось открыть камеру" << endl;
        return -1;
    }

    if (!capProc.isOpened()) {
        cout << "Не удалось открыть камеру" << endl;
        return -1;
    }

    // Создаем окно для отображения видеопотока
    /**
     * создает окно, которое можно использовать в качестве заполнителя для изображений и трекбаров. На созданные окна ссылаются по их именам. Если окно с таким же именем уже существует, функция ничего не делает. Вы можете вызвать cv::DestroyWindow или cv::destroyAllWindows, чтобы закрыть окно и отменить выделение любой связанной с ним памяти. Для простой программы вам на самом деле не нужно вызывать эти функции, потому что все ресурсы и окна приложения автоматически закрываются операционной системой при выходе.
     */
    cv::namedWindow("Video Stream Orig", cv::WINDOW_NORMAL);     // Video Stream - название окна; WINDOW_NORMAL - размер окна
    cv::namedWindow("Video Stream Proc", cv::WINDOW_NORMAL);

    while (true) {
        cv::Mat frameOrig;
        cv::Mat frameProc;

        // Считываем кадр из видеопотока
        capOrig.read(frameOrig);
        capProc.read(frameProc);

        // Если кадр успешно считан, отображаем его
        if (!frameOrig.empty()) {
            cv::imshow("Video Stream Orig", frameOrig);
        }

        cv::cvtColor(frameOrig, frameProc, cv::COLOR_BGR2GRAY);

        if (!frameProc.empty()) {
            cv::imshow("Video Stream Proc", frameProc);
        }

        // Для прекращения работы программы нажмите клавишу 'q'
        if (cv::waitKey(33) == 'q') {
            break;
        }
    }

    // Освобождаем ресурсы
    capOrig.release();
    capProc.release();
    cv::destroyAllWindows();

    return 0;
}

