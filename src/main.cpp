#include <iostream>
#include "display.h"
#include "utils.h"


using namespace std;

void run_predict()
{
    cout << "run pred..." << endl;

    string video_path = "./military.flv";
    process_video(video_path);
}

void run_test()
{
    cout << "run test..." << endl;

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
        fprintf(stderr, "usage: %s <pred> | <test>\n", argv[0]);
        return 0;
    }

    if (0 == strcmp(argv[1], "pred"))
    {
        run_predict();
    } else if (0 == strcmp(argv[1], "test"))
    {
        run_test();
    } else
    {
        fprintf(stderr, "Not an option: %s\n", argv[1]);
    }


    // process video
//    string video_path = "../military.flv";
//    process_video(video_path);

    // process single image
//    string img_path = "../tank.jpg";
//    process_img(img_path, true, true);

    return 0;
}