#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat Desplazar(Mat image, int umbralX, int umbralY);
void funcionUmbral(int umbral, void *userData);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Pasar una imágen\n");
        return -1;
    }

    Mat image = imread(argv[1]);

    int nf = image.rows, nc = image.cols, canales = image.channels();

    int spaceX = nc * 2, spaceY = nf * 2;

    int umbralX = spaceX / 2, umbralY = spaceY / 2;

    imshow("Desplazamiento", image);

    createTrackbar("EscalaX", "Desplazamiento", &umbralX, spaceX, funcionUmbral, &umbralX);
    createTrackbar("EscalaY", "Desplazamiento", &umbralY, spaceY, funcionUmbral, &umbralY);

    while (true)
    {
        Mat result = Desplazar(image, umbralX, umbralY);
        imshow("Desplazamiento", result);

        if (waitKey(10) == 27)
            break;
    }

    return 0;
}

Mat Desplazar(Mat image, int umbralX, int umbralY)
{
    umbralX = umbralX - image.cols;
    umbralY = umbralY - image.rows;
    int jTemp;

    int nf = image.rows, nc = image.cols, canales = image.channels();
    Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));

    if (umbralY > 0)
        jTemp = nf - umbralY;
    else
        jTemp = -1 * umbralY;

    int i, j;

    for (j = 0; j < nf; j++)
    {

        if (jTemp == nf)
            jTemp = 0;

        uchar *res = result.ptr<uchar>(j);
        uchar *A = image.ptr<uchar>(jTemp);

        for (i = 0; i < nc * canales; i += canales)
        {
            if (umbralX >= 0)
            {
                if ((i + umbralX * 3) > nc * canales)
                {
                    *(res + i + (umbralX - nc) * 3) = *(A + i);
                    *(res + i + 1 + (umbralX - nc) * 3) = *(A + i + 1);
                    *(res + i + 2 + (umbralX - nc) * 3) = *(A + i + 2);
                }
                else
                {
                    *(res + i + umbralX * 3) = *(A + i);
                    *(res + i + 1 + umbralX * 3) = *(A + i + 1);
                    *(res + i + 2 + umbralX * 3) = *(A + i + 2);
                }
            }
            else
            {
                *(res + i) = *(A + i - umbralX * 3);
                *(res + i + 1) = *(A + i + 1 - umbralX * 3);
                *(res + i + 2) = *(A + i + 2 - umbralX * 3);
            }
        }
        jTemp++;
    }

    return result;
}

void funcionUmbral(int umbral, void *userData)
{
}