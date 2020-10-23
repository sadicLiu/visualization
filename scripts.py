import os
from pathlib import Path


def gen_test_txt():
    path_test = Path('./testset')
    key_idx = {'solider': 0, 'warship': 1, 'vehicle': 2, 'tank': 3, 'missile': 4, 'warplane': 5,
               'rifle': 6, 'submarine': 7, 'cannon': 8}
    dirs = os.listdir(path_test)

    with open('./testset/test.txt', 'w', encoding='utf-8') as f:
        dirs = [d for d in dirs if os.path.isdir(path_test / d)]
        print(dirs)
        for dir in dirs:
            path_dir = path_test / dir
            label_idx = key_idx[dir]

            imgs_1cls = os.listdir(path_dir)
            for img in imgs_1cls:
                path_img = path_dir / img
                label_txt = './' + str(path_img.as_posix()) + ' ' + str(label_idx) + '\n'
                f.writelines(label_txt)


if __name__ == '__main__':
    gen_test_txt()
