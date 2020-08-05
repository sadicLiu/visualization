#include <iostream>
#include "display.h"

using namespace std;

int main(int argc, char **argv)
{

    // process video
//    string video_path = "../military.flv";
//    process_video(video_path);

    // process single image
    string img_path = "../tank.jpg";
    process_img(img_path, true, true);

    return 0;
}