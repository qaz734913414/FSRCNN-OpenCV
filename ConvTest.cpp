#include <string>

#include <iostream>
#include <Eigen/Dense>
#include <array>
#include <ctime>
#include "fsrcnn.h"
#include "utils.h"

#include <sys/timeb.h>

#if defined(WIN32)
#include <io.h>
#include <direct.h>
# define  TIMEB    _timeb
# define  ftime    _ftime
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define TIMEB timeb
#endif

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	/*
		VideoCapture capture;
	capture.open("C:\\Users\\think\\Documents\\�����ĵ�\\Design\\FSRCNN-OpenCV\\video\\the-grandmaster_360p_10s.mp4");//VideoCapture��ķ���


	//����Ƿ�򿪳ɹ�
	if (!capture.isOpened())
	{
		cout << "��Ƶû�д�" << endl;
		return 1;
	}


	//��ȡ��Ƶ��֡���ʣ�һ����30����60��
	double frame_rate = capture.get(CV_CAP_PROP_FPS);
	cout << frame_rate << endl;


	double codec = capture.get(CV_CAP_PROP_FOURCC);

	//��ȡ��Ƶ����֡��Ŀ
	long num_frame = static_cast<long>(capture.get(CV_CAP_PROP_FRAME_COUNT));
	cout << num_frame << endl;

	Mat frame;

	//����֡���ʼ���֮֡��ĵȴ�ʱ�䣬��λms
	int delat = 1000 / frame_rate;


	int w = 1280;
	int h = 720;

	cv::VideoWriter out(
		"C:\\Users\\think\\Documents\\�����ĵ�\\Design\\FSRCNN-OpenCV\\video\\out-1.mp4", // ����ļ���
		int(codec),  // ������ʽ��ʹ�� CV_FOURCC()��
		int(frame_rate), // �����Ƶ֡��
		cv::Size(w, h), // ��֡ͼƬ�Ĵ�С
		true // �����false,�ɴ���Ҷ�ͼ�� 
	);

	int i = 0;
	//ѭ��������Ƶ�е�ȫ��֡
	while (1)
	{
		capture.read(frame);

		if (!frame.empty())//�������ͽ���
		{
			out.write(fsutils::SR(frame));
			cout << "Finish Frame:" << i++ << endl;
		}
		else
		{
			break;
		}
	}

	capture.release();//���Ǳ���ģ�������VideoCapture��������������Ѿ������ˣ������ڹر���Ƶ�ļ�
	*/
	if (argc != 2) {
		std::cout << "Paramaters Error" << std::endl;
		return 0;
	}
	String path = String("C:\\Users\\think\\Documents\\�����ĵ�\\Design\\FSRCNN-OpenCV\\x64\\Release\\lena10p.bmp");
	Mat img = imread(argv[1]);
	if (img.empty())
	{
		cout << "fail to load image !" << endl;
		return -1;
	}

	int scale = 3;

	FSRCNN_NORMAL sr(scale);

	time_t ltime1, ltime2, tmp_time;
	struct TIMEB tstruct1, tstruct2;

	_ftime64_s(&tstruct1);            // start time ms
	time(&ltime1);               // start time s

	Mat res = fsutils::SR(img, sr, scale);

	time(&ltime2);               // end time sec
	_ftime64_s(&tstruct2);            // end time ms

	tmp_time = (ltime2 * 1000 + tstruct2.millitm) - (ltime1 * 1000 + tstruct1.millitm);
	cout << path << endl;
	cout << "����ʱ��: " << tmp_time << "ms" << endl;
	if (_access("result", 0) == -1) {
#if defined(WIN32)
		_mkdir("result");
#else
		mkdir("result", 0755);
#endif
		std::cout << "Mkdir:" << "result" << std::endl;
	}

	imwrite("result\\res_" + fsutils::GetPathOrURLShortName(path), res);
	std::cout << "Save as " << ".\result\\res_" + fsutils::GetPathOrURLShortName(path) << std::endl;
	int w = img.cols;
	int h = img.rows;

	Mat bicubic;
	resize(img, bicubic, { w * scale,h * scale }, 0, 0, cv::INTER_CUBIC);

	imwrite("result\\res_bicubic_" + fsutils::GetPathOrURLShortName(path), bicubic);
	std::cout << "Save as " << ".\result\\res_bicubic_" + fsutils::GetPathOrURLShortName(path) << std::endl;


	waitKey(0);
}