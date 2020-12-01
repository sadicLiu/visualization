#include <iostream>
#include <string>
#include <iomanip>
#include "display.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;

#define WIDTH 224
#define HEIGHT 224
#define NUM_CLASSES 9

// 对输入图片进行分类, 获取预测结果, pred向量中各类别置信度的排列是无序的
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


float *predict(cv::Mat image)
{
    // 连接server，将图片发送到server，并从server获取分类结果，将分类结果返回
    const char *server_ip = "192.168.0.1";
    uint16_t server_port = 1235;

    // 创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));                 // 每个字节都用0填充
    server_addr.sin_family = AF_INET;                             // 使用IPv4地址
    server_addr.sin_addr.s_addr = inet_addr(server_ip);           // 具体的IP地址
    server_addr.sin_port = htons(server_port);                    // 端口

    // 连接服务器
    connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

    cv::resize(image, image, cv::Size(WIDTH, HEIGHT));
    int img_size = image.total() * image.elemSize();
    // cv::imwrite("resized.jpg", image);

    int n = write(sock, image.data, img_size);
    if (n < 0) printf("ERROR writing to socket");

    float *res = new float[NUM_CLASSES];
    read(sock, (char *) res, sizeof(float) * NUM_CLASSES);
//    for (int i = 0; i < NUM_CLASSES; ++i)
//    {
//        printf("%f\n", res[i]);
//    }
    // 关闭套接字
    close(sock);

    return res;
}

// 对视频文件进行分类并展示
void run_predict()
{
    cout << "Run pred..." << endl;

    string video_path = "./military.flv";
    VideoCapture capture(video_path);
    Mat frame;

    while (true)
    {
        if (capture.read(frame))
        {
            resize(frame, frame, Size(640, 480));

            float *pred = predict(frame);
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
    cout << "Run test..." << endl;
    int num_pos = 0;   // 正确分类的样本数量
    int num_neg = 0;   // 错误分类的样本数量

    ifstream file_txt("./testset/test.txt");
    if (!file_txt)
    {
        cerr << "Label file not exists!" << endl;
        return;
    }

    string line;
    while (getline(file_txt, line))
    {
        string path_img = line.substr(0, line.length() - 2);
        int cls_idx = stoi(line.substr(line.length() - 1, 1));

        cout << path_img << ": " << cls_idx << endl;
        Mat image = imread(path_img);
        float *pred = predict(image);

        int max_idx = 0;
        for (int i = 1; i < NUM_CLASSES; ++i)
        {
            max_idx = pred[i] > pred[max_idx] ? i : max_idx;
        }
        num_pos = (max_idx == cls_idx) ? num_pos + 1 : num_pos;
        num_neg = (max_idx == cls_idx) ? num_neg : num_neg + 1;

        delete[] pred;
    }

    float accuracy = num_pos * 1.0f / (num_pos + num_neg);
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << "Accuracy: " << accuracy * 100 << "%" << endl;
}

// 分类一张图片的demo
void run_demo()
{
    string img_path = "./tank.jpg";
    Mat img = imread(img_path);
    resize(img, img, Size(640, 480));

    float *pred = predict(img);
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