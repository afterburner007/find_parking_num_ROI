#include "ocr_roi.h"


int bSums(Mat src,Rect rect_temp)
{
	/*imshow("src",src);
	waitKey(0);*/
	Mat img_roi;
	img_roi = src(rect_temp);
	/*imshow("roi", img_roi);
	waitKey(0);*/
	int counter = 0;
	//迭代器访问像素点  

	Mat_<uchar>::iterator it = img_roi.begin<uchar>();
	Mat_<uchar>::iterator itend = img_roi.end<uchar>();
	for (; it != itend; ++it)
	{
		if ((*it) > 0) counter += 1;//二值化后，像素点是0或者255  
	}
	return counter;
}

void find_roi(Mat src,vector<Rect> ocr_rect)
{
	Mat src_copy = src.clone();
	Mat imgdst, img_gray;

	vector<double> sigema;
	vector<double> weight;
	for (int i = 0; i < 3; i++)
		weight.push_back(1. / 3);
	sigema.push_back(30);
	sigema.push_back(150);
	sigema.push_back(300);
	Msrcr msrcr;
	msrcr.MultiScaleRetinexCR(src, imgdst, weight, sigema, 128, 128);
	imshow("msrcr", imgdst);
	waitKey(0);
	cvtColor(imgdst, img_gray, COLOR_BGR2GRAY);
	imshow("gray", img_gray);
	waitKey(0);
	Mat img_threshold;
	threshold(img_gray, img_threshold, 205, 255, CV_THRESH_BINARY);
	imshow("threshold", img_threshold);
	waitKey(0);
	Mat img_med;
	medianBlur(img_threshold, img_med, 3);
	imshow("media", img_med);
	waitKey(0);
	Mat img_out;
	Mat img_grad_x, img_grad_y;
	Mat abs_img_grad_x, abs_img_grad_y;
	//X
	Sobel(img_med, img_grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(img_grad_x, abs_img_grad_x);
	//Y
	Sobel(img_med, img_grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(img_grad_y, abs_img_grad_y);
	addWeighted(abs_img_grad_x, 0.5, abs_img_grad_y, 0.5, 0, img_out);
	imshow("sobel", img_out);
	waitKey(0);
	/*Mat Gauss;
	GaussianBlur(img_out, Gauss, Size(3, 3), 0, 0, BORDER_DEFAULT);
	imshow("Gauss", Gauss);
	waitKey(0);*/

	/*Mat img_med2;
	medianBlur(img_out, img_med2, 9);
	imshow("media2", img_med2);
	waitKey(0);*/

	Mat element = getStructuringElement(MORPH_OPEN, Size(3, 3));
	Mat img_dilate;
	Mat img_erosion;
	//erode(dst_img2, dst_img2_erosion, element);
	dilate(img_out, img_dilate, element);
	erode(img_dilate, img_erosion, element);
	Mat img_dilate_copy = img_erosion.clone();
	imshow("dilate", img_erosion);
	waitKey(0);

	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *seq = NULL;
	int conturs_num = cvFindContours(&(IplImage)img_dilate, storage, &seq, sizeof(CvContour), CV_RETR_LIST);
	cout << "conturs_num="<<conturs_num << endl;
	CvSeq *temp_seq = NULL;
	for (temp_seq = seq; temp_seq != NULL; temp_seq = temp_seq->h_next)
	{
		double l_area = fabs(cvContourArea(temp_seq, CV_WHOLE_SEQ));
		double l_length = cvArcLength(temp_seq);

		CvPoint2D32f rectpoint[4];
		CvPoint center;
		//if (l_length <= 116 && l_area >= 120 && l_area <= 360)
		if (l_length <= 116 && l_area >= 120 && l_area <= 370)
		{

			CvRect  l_rect = cvBoundingRect(temp_seq);
			//rectangle(src_copy, l_rect, CV_RGB(0, 255, 0), 1);
			/*imshow("src_copy", src_copy);
			waitKey(0);*/
			CvRect temp_rect;
			float w_h_ratio = (float)l_rect.width / l_rect.height;
			if (w_h_ratio <= 1 && w_h_ratio >= 0.4)
			{

				center.x = l_rect.x + l_rect.width / 2;
				center.y = l_rect.y + l_rect.height / 2;
				if ((center.x + 5 < src_copy.cols || center.y + 5 <src_copy.rows) && (center.x - 5 > 0 || center.y - 5 > 0))
				{   //if (bSums(img_dilate_copy, l_rect) > 205){
					if (bSums(img_dilate_copy, l_rect) > 220){
						temp_rect.x = l_rect.x;
						temp_rect.y = l_rect.y;
						temp_rect.height = l_rect.height;
						temp_rect.width = l_rect.width;
						ocr_rect.push_back(temp_rect);
						cout << temp_rect.x << " " << temp_rect.y << " " << temp_rect.height << " " << temp_rect.width << " " << endl;
						//rectangle(src_copy, l_rect, CV_RGB(0, 255, 0), 1);
						rectangle(src_copy, temp_rect, CV_RGB(0, 255, 0), 1);
						imshow("src_copy", src_copy);
						waitKey(0);
					}
				}
			}
		}
	}


}
