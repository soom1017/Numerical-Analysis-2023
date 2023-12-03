'''
Sample image data from https://www.flickr.com/photos/cameralabs/39250606495/in/datetaken/.
Excecute with "$ python main.py [image path] [size x] [size y]" (x * y image will be displayed)
'''

import sys
import cv2
import numpy as np

def resize(img, new_size_x, new_size_y):
    size_y, size_x, channel = img.shape
    new_img = np.zeros((new_size_y, new_size_x, channel), np.uint8)

    x_ratio = new_size_x / size_x
    y_ratio = new_size_y / size_y

    for new_x in range(new_size_x):
        for new_y in range(new_size_y):
            # (x1, y1) = (x, y) - (dx, dy)
            #          = (new_x, new_y) / ratio - (dx, dy)
            x = new_x / x_ratio
            y = new_y / y_ratio

            x1 = int(x)
            y1 = int(y)
            dx = x - x1
            dy = y - y1

            try:
                new_img[new_y, new_x] = dx*dy*img[y1+1, x1+1] + (1-dx)*dy*img[y1+1, x1] + dx*(1-dy)*img[y1, x1+1] + (1-dx)*(1-dy)*img[y1, x1]
            except IndexError:
                new_img[new_y, new_x] = 0   # zero padding, when new size > original size

    return new_img


def main(img_path, new_size_x, new_size_y):
    img = cv2.imread(img_path, cv2.IMREAD_COLOR)
    print(f"img shape: {img.shape}")

    cv2.imshow("origin image", img)

    resize_img = resize(img, new_size_x, new_size_y)
    print(f"img shape: {resize_img.shape}")

    cv2.imshow("my resize image", resize_img)

    opencv_resize_img = cv2.resize(img, (new_size_x, new_size_y), interpolation=cv2.INTER_LINEAR)
    print(f"img shape: {opencv_resize_img.shape}")

    cv2.imshow("opencv resize image", opencv_resize_img)
    cv2.waitKey()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    # python main.py [image path] [size x] [size y]
    main(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))