#include "distance.h"
#include "iostream"
using namespace std;


void main(){
	point2d<float> cs[3],a(-10,0),b(0.9,-1);
	cs[0].x = -0.91;
	cs[0].y = -0.89;
	cs[1].x = -10;
	cs[1].y = -10;
	cs[2].x = 10;
	cs[2].y = 9.5;
	/*cout << distance_point_to_point(a, b);
	cout << distance_point_to_point(cs[0], a);*/
	//radius �뾶
	//shiftpos = 2 ǰ��������ֵ��ʾ����
	//wheelangle >0 ��ʾ��ת��<0��ʾ��ת
	//Point2f* objpoints,int ObjNUM �ϰ����
	float distance = get_mindistance_code(10, 1, 1, cs, 1);
	cout << "�������ײ��ľ���Ϊ��"<<distance << endl;



}