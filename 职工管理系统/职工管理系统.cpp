#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"manager.h"
#include"employee.h"
#include"boss.h"

using namespace std;


int main()
{

	//管理者界面
	WorkerManager wm;

	//功能选择变量
	int choice(0);
	while (true)
	{
		//菜单
		wm.Show_Menu();
		
		cout << "请输入您的选择" << endl;
		
		//输入choice
		cin >> choice;
		
		//switch功能选择
		switch (choice)
		{
		case 0://退出
			wm.exitSystem();
			break;
		case 1://添加
			wm.Add_Emp();
			break;
		case 2://显示
			wm.ShowEmp();
			break;
		case 3://删除		
			wm.Del_Emp();
			break;
		case 4://修改
			wm.Mod_Emp();
			break;
		case 5://查找
			wm.Find_Emo();
			break;
		case 6://排序
			wm.Sort_Emp();
			break;
		case 7://清空
			wm.Clean_File();
			break;
		default://刷新
			system("cls");
			break;
		}
	}
	

	system("pause");//等待
}