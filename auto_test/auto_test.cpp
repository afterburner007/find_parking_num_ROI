
#include "auto_test.h"
#include  <algorithm>
//�ж��ı����Ƿ����ı�����
bool quadix_in_quadix(Quadix quadix1, Quadix quadix2){

	return (point_in_quadix<float>(quadix1[0], quadix2) && point_in_quadix<float>(quadix1[1], quadix2) && point_in_quadix<float>(quadix1[2], quadix2) ||
		point_in_quadix<float>(quadix1[0], quadix2) && point_in_quadix<float>(quadix1[1], quadix2) && point_in_quadix<float>(quadix1[3], quadix2) ||
		point_in_quadix<float>(quadix1[1], quadix2) && point_in_quadix<float>(quadix1[2], quadix2) && point_in_quadix<float>(quadix1[3], quadix2) ||
		point_in_quadix<float>(quadix1[0], quadix2) && point_in_quadix<float>(quadix1[2], quadix2) && point_in_quadix<float>(quadix1[3], quadix2));

}
//�����ı��ε����
float area_quadix(Quadix quadix1){
	return((quadix1[0].x*(quadix1[1].y - quadix1[3].y) + quadix1[1].x*(quadix1[3].y - quadix1[0].y) + quadix1[3].x*(quadix1[0].y - quadix1[1].y)) / 2 + (quadix1[1].x*(quadix1[2].y - quadix1[3].y) + quadix1[2].x*(quadix1[3].y - quadix1[1].y) + quadix1[3].x*(quadix1[1].y - quadix1[2].y)) / 2);
}


//���������ı����غϵ����ռ��һ�����ı�������ı���     ��accuracy=0.1��׼ȷ�ʿɴ�64%��accuracy = 0.05��׼ȷ�ʿɴ�80%��accuracy = 0.01��׼ȷ�ʿɴ�98%
float proportion(Quadix quadix1, Quadix quadix2, float accuracy)  {
	quadix<float, 2> quad;
	int num = 0;
	float rate;
	vector<float> num_x, num_y;
	for (int z = 0; z < 4; z++)
	{
		num_x.push_back(quadix1[z].x);
		num_x.push_back(quadix2[z].x);
		num_y.push_back(quadix1[z].x);
		num_y.push_back(quadix2[z].x);
	}
	sort(num_x.begin(), num_x.end());
	sort(num_y.begin(), num_y.end());
	for (float j = num_y[0]; j < num_y[7]; j += accuracy){
		for (float i = num_x[0]; i < num_x[7]; i += accuracy){
			quad[0].x = i;        quad[0].y = j;
			quad[1].x = i + accuracy;    quad[1].y = j;
			quad[2].x = i + accuracy;    quad[2].y = j + accuracy;
			quad[3].x = i;        quad[3].y = j + accuracy;
			if (quadix_in_quadix(quad, quadix1) && quadix_in_quadix(quad, quadix2)){
				num++;
			}
		}
	}
	rate = num*accuracy *accuracy / area_quadix(quadix1);
	return rate;
};





//��ȡ����
string read_data(string name){
	string data;
	ifstream indata;
	indata.open(name);
	if (!indata)
	{
		std::cout << "û�д��ļ���" << endl;
	}
	indata >> data;
	return data;
	indata.close();
}

vector<string> splitEx(const string& src, string separate_character)
{
	vector<string> strs;

	int separate_characterLen = separate_character.size();//�ָ��ַ����ĳ���,�����Ϳ���֧���硰,,�����ַ����ķָ���
	int lastPosition = 0, index = -1;
	while (-1 != (index = src.find(separate_character, lastPosition)))
	{
		strs.push_back(src.substr(lastPosition, index - lastPosition));
		lastPosition = index + separate_characterLen;
	}
	string lastString = src.substr(lastPosition);//��ȡ���һ���ָ����������
	if (!lastString.empty())
		strs.push_back(lastString);//������һ���ָ����������ݾ����
	return strs;
}


//���ı������긳ֵ
quadix<float, 2> assignment_quadix(string *data){

	quadix<float, 2> quad;
	int coordinate[20];
	for (int i = 0; i < 8; i++)
	{
		stringstream stream;
		stream << data[i];
		stream >> coordinate[i];
	}


	quad[0].x = coordinate[0];
	quad[0].y = coordinate[1];
	quad[1].x = coordinate[2];
	quad[1].y = coordinate[3];
	quad[2].x = coordinate[4];
	quad[2].y = coordinate[5];
	quad[3].x = coordinate[6];
	quad[3].y = coordinate[7];

	return quad;
}

//��ȡhead
float get_header(char *data){
	char delim[] = ",";
	float head = atof(strtok(data, delim));
	return head;
}


//�ж�һ�����Ƿ�����һ�������ڴ���,���ڷ���true�������˷���false
bool judge_exist(string head, string data[]){
	bool judge = false;
	for (int i = 0; i < 3; i++)
	{

		if (head == data[i])
		{
			judge = true;
			break;
		}
	}
	return judge;

}




float distance_point_to_point(point2d<float> point1, point2d<float> point2){
	float distance;
	distance = sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y));
	return distance;
}//��������֮��ľ���


float max_distance(point2d<float> point, point2d<float> point1, point2d<float> point2, point2d<float> point3, point2d<float> point4){
	float distance1 = distance_point_to_point(point, point1), distance2 = distance_point_to_point(point, point2), distance3 = distance_point_to_point(point, point3), distance4 = distance_point_to_point(point, point4);
	float MAX = distance1;
	if (distance2 >= MAX)
	{
		MAX = distance2;
	}
	if (distance3 >= MAX)
	{
		MAX = distance3;
	}
	if (distance4 >= MAX)
	{
		MAX = distance4;
	}
	return MAX;
}//���������


float min_distance(point2d<float> point, point2d<float> point1, point2d<float> point2, point2d<float> point3, point2d<float> point4){
	float distance1 = distance_point_to_point(point, point1), distance2 = distance_point_to_point(point, point2), distance3 = distance_point_to_point(point, point3), distance4 = distance_point_to_point(point, point4);
	float MIN = distance1;
	if (distance2 <= MIN)
	{
		MIN = distance2;
	}
	if (distance3 <= MIN)
	{
		MIN = distance3;
	}
	if (distance4 <= MIN)
	{
		MIN = distance4;
	}
	return MIN;
}//�����С����


bool collision_range(circle<float> circlemin, circle<float> circlemax, point2d<float> point){
	if (point_in_circle(point, circlemax) && !point_in_circle(point, circlemin))
	{
		return true;
	}
	else
	{
		return false;
	}
}

float *solving_equations(float a, float b, float c){
	float answer[2];
	if ((b*b - 4 * a*c) >= 0)
	{
		answer[0] = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
		answer[1] = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
	}
	else
	{
		cout << "�����޽�" << endl;
	}
	return answer;
}

point2d<float> *point_of_intersection(point2d<float> point1, point2d<float> point2, circle<float> circle){
	point2d<float> point[2];
	float a = 1 + ((point2.y - point1.y) / (point2.x - point1.x))*((point2.y - point1.y) / (point2.x - point1.x));
	float b = (2 * (point2.y - point1.y)*(point1.y*point2.x - point1.x*point2.y - circle.y*point2.x - circle.y*point1.x)) / ((point2.x - point1.x)*(point2.x - point1.x)) - 2 * circle.x;
	float c = ((point1.y*point2.x - point1.x*point2.y - circle.y*point2.x - circle.y*point1.x) / (point2.x - point1.x))*((point1.y*point2.x - point1.x*point2.y - circle.y*point2.x - circle.y*point1.x) / (point2.x - point1.x)) + circle.x*circle.x - circle.radius*circle.radius;
	if (solving_equations(a, b, c)[0] == solving_equations(a, b, c)[1])
	{

		point[0].x = solving_equations(a, b, c)[0];
		point[0].y = (solving_equations(a, b, c)[0] - point1.x)*(point2.y - point1.y) / (point2.x - point1.x) + point1.y;
	}
	else
	{

		point[0].x = solving_equations(a, b, c)[0];
		point[0].y = (solving_equations(a, b, c)[0] - point1.x)*(point2.y - point1.y) / (point2.x - point1.x) + point1.y;
		point[1].x = solving_equations(a, b, c)[1];
		point[1].y = (solving_equations(a, b, c)[1] - point1.x)*(point2.y - point1.y) / (point2.x - point1.x) + point1.y;
	}
	return point;
}

point2d<float> intersection_segment_to_circle(point2d<float> pointd, point2d<float> pointc, circle<float> circle){

	point2d<float> intersection;

	for (int i = 0; i < 2; i++){
		if (point_of_intersection(pointd, pointc, circle)[i].x >= pointd.x&&point_of_intersection(pointd, pointc, circle)[i].x <= pointc.x&&point_of_intersection(pointd, pointc, circle)[i].y >= pointc.y&&point_of_intersection(pointd, pointc, circle)[i].y <= pointd.y)
		{
			intersection.x = point_of_intersection(pointd, pointc, circle)[i].x;
			intersection.y = point_of_intersection(pointd, pointc, circle)[i].y;
		}
	}
	return intersection;

}


float angle(point2d<float> point, point2d<float> collision, point2d<float> intersection){

	return (point.x*(collision.y - intersection.y) + collision.x*(intersection.y - point.y) + intersection.x*(point.y - collision.y)) / (distance_point_to_point(point, collision)*distance_point_to_point(point, intersection));

}
