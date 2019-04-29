#include <iostream>
#include "WPMainCore.h"

using namespace std;

int main(){
	int ret = Roseek_MainCore_Init(1);
	cout << "Roseek_MianCore_Init return : " << ret;
	ret = Roseek_MainCore_SetLogLevel(1);
	cout << "Roseek_MainCore_SetLogLevel return : " << ret;

	ret = Roseek_ImageAcquisition_Start();
	cout << "Roseek_ImageAcquisition_Start return : " << ret;

	//����ͼ��ɼ�����ģʽ  ����֡ ��֡  ����Ϊ����֡ IA_WorkMode_ContinuousFrame  IA_WorkMode_SingleFrame
	ret = Roseek_ImageAcquisition_SetWorkMode(IA_WorkMode_ContinuousFrame);
	cout << "Roseek_ImageAcquisition_SetWorkMode return : " << ret;


	return 0;

}