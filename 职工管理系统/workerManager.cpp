#include"workerManager.h"

WorkerManager::WorkerManager()
{
	//初始化
	this->m_EmpNum = 0;
	this->m_EmpArray = nullptr;

	//文件不存在时
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = nullptr;
		ifs.close();
		return;
	}

	//文件存在但内容为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = nullptr;
		ifs.close();
		return;
	}

	//文件存在且不为空
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	

	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
}

//菜单
void WorkerManager::Show_Menu()
{
	cout << "***********************************" << endl;
	cout << "********欢迎使用职工管理系统!******" << endl;
	cout << "********* 0.退出管理程序 **********" << endl;
	cout << "********* 1.添加职工信息 **********" << endl;
	cout << "********* 2.显示职工信息 **********" << endl;
	cout << "********* 3.删除离职职工 **********" << endl;
	cout << "********* 4.修改职工信息 **********" << endl;
	cout << "********* 5.查找职工信息 **********" << endl;
	cout << "********* 6.按照编号排序 **********" << endl;
	cout << "********* 7.清空所有文档 **********" << endl;
	cout << "***********************************" << endl;
}

void  WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");//等待
	exit(0);//强行退出（无论当前为何代码处，直接结束这个程序）
}

void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量:" << endl;
	
	int addNum = 0;
	cin >> addNum;
	
	if(addNum>0)
	{
		//添加
		//计算添加的新空间大小
		int newSize = this->m_EmpNum + addNum;
		 
		//开辟新空间
		Worker** newSpace =  new Worker* [newSize];

		//数据迁移
		if (this->m_EmpArray != nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工的编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的名字" << endl;
			cin >> name;
			cout << "请输入该新职工的职位" << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = nullptr;

			switch (dSelect)
			{
			case 1: 
				worker = new Employee(id,name,1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工保存在数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放旧空间,同时更改指向
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;

		//保存至文件
		this->save();

		cout << "成功添加" << addNum << "人"<<endl;
	}
	else
	{
		cout << "输出有误" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	
	///将每个人的数据写入文件中

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << " "
			<< endl;
	}
	
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}

	ifs.close();

	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index(0);
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker(nullptr);

		//根据读取数据的不同，来确定指针
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);

		}
		else
		{
			worker = new Boss(id, name, dId);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}

void WorkerManager::ShowEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (size_t i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;

			break;
		}
	}

	return index;
}
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空" << endl;
	}
	else
	{
		cout << "请输入想要删除的员工" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if(index != -1)
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功" << endl;

		}
		else{
			cout << "删除失败" << endl;

		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		cout << "请输入需要修改的员工编号" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查找到：" << id << "号职工，请输入新的职工工号:" << endl;
			cin >> newId;
			cout << "请输入名称" << endl;
			cin >> newName;
			cout << "请输入岗位" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker * worker = nullptr;

			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
			default:
				break;
			}

			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << this->m_EmpArray[ret]->m_DeptId << endl;

			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Find_Emo()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
		
	}

	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1.职工编号查找" << endl;
		cout << "2.姓名查找" << endl;
	}

	bool ft = false;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		int id;
		cout << "请输入查找的职工编号" << endl;

		cin >> id;
		int ret = IsExist(id);
		if (ret != -1)
		{
			cout << "查找成功" << endl;
			ft = true;
			this->m_EmpArray[ret]->showInfo();
		}

	
	}
	else if (select == 2)
	{
		string name;
		cout << "请输入名称" << endl;
		cin >> name;

		
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i]->m_Name == name)
			{
				cout << "查找成功,编号为：" 
					<<this->m_EmpArray[i]
					<<"号的信息如下" << endl;

				ft = true;
				
				this->m_EmpArray[i]->showInfo();
			}
		}
	}

	if (ft == false)
	{
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
		system("pasue");
		system("cls");
	}
	else
	{
		cout << "请选择排序方法" << endl;
		cout << "1.升序" << endl;
		cout << "2.降序" << endl;
	}

	int selcet = 0;
	cin >> selcet;
	for (int i = 0; i < m_EmpNum; i++)
	{
		int minormax = 1; 
		for (int j = i + 1; i < m_EmpNum; j++)
		{
			if (selcet == 1)
			{
				if (m_EmpArray[minormax]->m_Id > m_EmpArray[j]->m_Id)
				{
					minormax = j;
				}
				
			}
			else
			{
				if (m_EmpArray[minormax]->m_Id < m_EmpArray[j]->m_Id)
				{
					minormax = j;
				}

			}
		}

		if (i != minormax)
		{
			Worker* worker = this->m_EmpArray[i];
			this->m_EmpArray[i] = this->m_EmpArray[minormax];
			this->m_EmpArray[minormax] = worker;
		}
	}

	cout << "排序成功" << endl;
	this->save();
	this->ShowEmp();
}


void WorkerManager::Clean_File()
{
	cout << "是否确认清空" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != nullptr)
		{
			for (int  i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != nullptr) 
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = nullptr;
			this->m_FileIsEmpty = true;
		}

		cout << "清空完成" << endl;
	}

	system("pause");
	system("cls");

}


WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != nullptr)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != nullptr)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}