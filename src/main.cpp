#include <iostream>
#include "display.h"
#include "utils.h"


using namespace std;

// 对视频文件进行分类并展示
void run_predict()
{
    cout << "run pred..." << endl;

    string video_path = "./military.flv";

    VideoCapture capture(video_path);
    Mat frame;

    while (true)
    {
        if (capture.read(frame))
        {
            resize(frame, frame, Size(640, 480));

            // float *pred = predict(network, img);  // todo: invoke network prediction here, 224x224 input
            float *pred = predict();
            show_result(frame, pred, TOPK, false, false);
            delete[]pred;
        } else
        {
            break;
        }
    }
}

// 对测试集进行分类, 并打印分类准确率
void run_test()
{
    cout << "run test..." << endl;
}

// 分类一张图片的demo
void run_demo()
{
    string img_path = "./tank.jpg";
    Mat img = imread(img_path);
    resize(img, img, Size(640, 480));

    // float *pred = predict(network, img);  // todo: invoke network prediction here, 224x224 input
    float *pred = predict();
    show_result(img, pred, TOPK, true, true);
    delete[]pred;
}


int main(int argc, char **argv)
{
    int i;
    for (i = 0; i < argc; ++i)
    {
        if (!argv[i]) continue;
        strip_args(argv[i]);
    }

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <pred> | <test> | <demo>\n", argv[0]);
        return 0;
    }

    if (0 == strcmp(argv[1], "pred"))
    {
        run_predict();
    } else if (0 == strcmp(argv[1], "test"))
    {
        run_test();
    } else if (0 == strcmp(argv[1], "demo"))
    {
        run_demo();
    } else
    {
        fprintf(stderr, "Not an option: %s\n", argv[1]);
    }

    return 0;
}