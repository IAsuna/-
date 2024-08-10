#include"workerManager.h"

WorkerManager::WorkerManager()
{
	//��ʼ��
	this->m_EmpNum = 0;
	this->m_EmpArray = nullptr;

	//�ļ�������ʱ
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

	//�ļ����ڵ�����Ϊ��
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

	//�ļ������Ҳ�Ϊ��
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	

	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
}

//�˵�
void WorkerManager::Show_Menu()
{
	cout << "***********************************" << endl;
	cout << "********��ӭʹ��ְ������ϵͳ!******" << endl;
	cout << "********* 0.�˳�������� **********" << endl;
	cout << "********* 1.���ְ����Ϣ **********" << endl;
	cout << "********* 2.��ʾְ����Ϣ **********" << endl;
	cout << "********* 3.ɾ����ְְ�� **********" << endl;
	cout << "********* 4.�޸�ְ����Ϣ **********" << endl;
	cout << "********* 5.����ְ����Ϣ **********" << endl;
	cout << "********* 6.���ձ������ **********" << endl;
	cout << "********* 7.��������ĵ� **********" << endl;
	cout << "***********************************" << endl;
}

void  WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");//�ȴ�
	exit(0);//ǿ���˳������۵�ǰΪ�δ��봦��ֱ�ӽ����������
}

void WorkerManager::Add_Emp()
{
	cout << "���������ְ������:" << endl;
	
	int addNum = 0;
	cin >> addNum;
	
	if(addNum>0)
	{
		//���
		//������ӵ��¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		 
		//�����¿ռ�
		Worker** newSpace =  new Worker* [newSize];

		//����Ǩ��
		if (this->m_EmpArray != nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����ְ���ı��" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "���������ְ����ְλ" << endl;
			cout << "1.Ա��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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

			//��������ְ��������������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷžɿռ�,ͬʱ����ָ��
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;

		//�������ļ�
		this->save();

		cout << "�ɹ����" << addNum << "��"<<endl;
	}
	else
	{
		cout << "�������" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	
	///��ÿ���˵�����д���ļ���

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

		//���ݶ�ȡ���ݵĲ�ͬ����ȷ��ָ��
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
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
		cout << "�ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����Ա��" << endl;
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
			cout << "ɾ���ɹ�" << endl;

		}
		else{
			cout << "ɾ��ʧ��" << endl;

		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		cout << "��������Ҫ�޸ĵ�Ա�����" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "���ҵ���" << id << "��ְ�����������µ�ְ������:" << endl;
			cin >> newId;
			cout << "����������" << endl;
			cin >> newName;
			cout << "�������λ" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			cout << "�޸ĳɹ���" << this->m_EmpArray[ret]->m_DeptId << endl;

			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Find_Emo()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
		
	}

	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1.ְ����Ų���" << endl;
		cout << "2.��������" << endl;
	}

	bool ft = false;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		int id;
		cout << "��������ҵ�ְ�����" << endl;

		cin >> id;
		int ret = IsExist(id);
		if (ret != -1)
		{
			cout << "���ҳɹ�" << endl;
			ft = true;
			this->m_EmpArray[ret]->showInfo();
		}

	
	}
	else if (select == 2)
	{
		string name;
		cout << "����������" << endl;
		cin >> name;

		
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i]->m_Name == name)
			{
				cout << "���ҳɹ�,���Ϊ��" 
					<<this->m_EmpArray[i]
					<<"�ŵ���Ϣ����" << endl;

				ft = true;
				
				this->m_EmpArray[i]->showInfo();
			}
		}
	}

	if (ft == false)
	{
		cout << "���޴���" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
		system("pasue");
		system("cls");
	}
	else
	{
		cout << "��ѡ�����򷽷�" << endl;
		cout << "1.����" << endl;
		cout << "2.����" << endl;
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

	cout << "����ɹ�" << endl;
	this->save();
	this->ShowEmp();
}


void WorkerManager::Clean_File()
{
	cout << "�Ƿ�ȷ�����" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;

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

		cout << "������" << endl;
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