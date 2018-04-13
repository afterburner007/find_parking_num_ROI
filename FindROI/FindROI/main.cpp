#include <iostream>
#include "ocr_roi.h"



int main(){
	Mat ocr_src,ocr_dst;
	ocr_src = imread("F:\\GTtool\\raw_data\\right\\000004_R.png");
	imshow("src", ocr_src);
	waitKey(0);
	vector<Rect> RECT;
	find_roi(ocr_src,RECT);




}