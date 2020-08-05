#ifndef DEMO_DISPLAY_H
#define DEMO_DISPLAY_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define NUM_CLASSES 9

#define R 77
#define G 171
#define B 82

#define TOPK 5


using namespace std;
using namespace cv;

// 9分类
typedef enum
{
    SOLIDER = 0,
    WARSHIP,
    VEHICLE,
    TANK,
    MISSILE,
    WARPLANE,
    RIFLE,
    SUBMARINE,
    CANNON
} LABEL;

void show_result(Mat img, float *preds, int top_k, bool wait_key, bool show_info = false);

void process_img(string img_path, bool wait_key, bool show_info = false);

void process_img(Mat image, bool wait_key, bool show_info = false);

void process_video(string video_path);

void draw_info(Mat &img, string info_str);

void draw_prob(Mat &img, float prob, LABEL label, int rank, int top_k, string title_str);

float *predict();

// 实现argsort功能
template<typename T>
vector<int> argsort(const vector<T> &array)
{
    const int array_len(array.size());
    vector<int> array_index(array_len, 0);
    for (int i = 0; i < array_len; ++i)
        array_index[i] = i;

    sort(array_index.begin(), array_index.end(),
         [&array](int pos1, int pos2)
         { return (array[pos1] > array[pos2]); });

    return array_index;
}


template<typename _Tp>
int softmax(const _Tp *src, _Tp *dst, int length)
{
    const _Tp alpha = *std::max_element(src, src + length);
    _Tp denominator{0};

    for (int i = 0; i < length; ++i)
    {
        dst[i] = std::exp(src[i] - alpha);
        denominator += dst[i];
    }

    for (int i = 0; i < length; ++i)
    {
        dst[i] /= denominator;
    }

    return 0;
}

#endif //DEMO_DISPLAY_H
