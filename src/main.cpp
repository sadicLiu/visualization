#include <iostream>
#include "display.h"
#include "utils.h"


using namespace std;

// 对输入图片进行分类, 获取预测结果
// TODO: 目前是模拟的结果, 分类可用之后, 使用真实分类流程替代
float *predict()
{
    float *pred = new float[NUM_CLASSES];
    float small[7] = {0.01, 0.0, 0.01, 0.01, 0.02, 0.03, 0.02};

    srand((unsigned) time(NULL));
    float top1 = (rand() % 10) / 10.f;
    float top2 = 0.9f - top1;

    srand((unsigned) time(NULL));
    int index_top1 = rand() % 9;
    int index_top2 = index_top1 / 2 == index_top1 ? index_top1 + 1 : index_top1 / 2;

    int idx_small = 0;
    int i;
    for (i = 0; i < NUM_CLASSES; i++)
    {
        pred[i] = i == index_top1 ? top1
                                  : i == index_top2 ? top2
                                                    : small[idx_small++];
    }

    return pred;
}

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