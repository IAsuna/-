#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"manager.h"
#include"employee.h"
#include"boss.h"

using namespace std;


int main()
{

	//�����߽���
	WorkerManager wm;

	//����ѡ�����
	int choice(0);
	while (true)
	{
		//�˵�
		wm.Show_Menu();
		
		cout << "����������ѡ��" << endl;
		
		//����choice
		cin >> choice;
		
		//switch����ѡ��
		switch (choice)
		{
		case 0://�˳�
			wm.exitSystem();
			break;
		case 1://���
			wm.Add_Emp();
			break;
		case 2://��ʾ
			wm.ShowEmp();
			break;
		case 3://ɾ��		
			wm.Del_Emp();
			break;
		case 4://�޸�
			wm.Mod_Emp();
			break;
		case 5://����
			wm.Find_Emo();
			break;
		case 6://����
			wm.Sort_Emp();
			break;
		case 7://���
			wm.Clean_File();
			break;
		default://ˢ��
			system("cls");
			break;
		}
	}
	

	system("pause");//�ȴ�
}