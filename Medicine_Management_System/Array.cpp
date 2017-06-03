#include<string>
#include<iostream>
#include<iomanip>
#include"Array.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

int Array::numArrayOfMedicine = 0;
int Array::numArrayOfPersonnel = 0;
int Array::numArrayOfUser = 0;
int Array::current_user = NO_USERS;

////////////////////////////////////////////////
// ���� Array

// Array�ิ�ƹ��캯��
Array::Array(Array & t_array)
{
	numArrayOfMedicine = t_array.numArrayOfMedicine;
	numArrayOfPersonnel = t_array.numArrayOfPersonnel;
}

// ������
bool Array::catchError(int error_code)
{
	switch (error_code)
	{
	case E_NUMBER:
		cout << "--(����) �Ѵ��ڸñ�ţ���������ֹ--" << endl << endl;
		return false;
		break;

	case E_AUTHORITY:
		cout << "--(���ش���) û���㹻��Ȩ�ޣ���������ֹ--" << endl << endl;
		return false;
		break;

	case E_ADMIN_EXISTED:
		cout << "--(���ش���) �Ѵ���ϵͳ����Ա�˻�����������ֹ--" << endl << endl;
		return false;
		break;

	case E_ACCOUNT:
		cout << "--(����) �Ѵ���ͬ���˻�����������ֹ--" << endl << endl;
		return false;
		break;

	case E_NO_RECORD:
		cout << "--(����) δ�ҵ��ü�¼--" << endl << endl;
		return false;
		break;

	case E_AMOUNT:
		cout << "--(����)ҩƷ�����������--" << endl << endl;
		return false;
		break;

	case W_UPDATE_MEDICINE:
		cout << "--(����) �Ѵ��ڼ�¼����¼��Ϣ��������--" << endl << endl;
		return true;
		break;

	case NO_ERROR:
		return true;
		break;

	default:
		cout << "--(����) δ֪����--" << endl << endl;
		return false;
		break;
	}
}

// ��ȡ��ǰ��½�û�
int Array::getCurrentUser()
{
	return current_user;
}

// ����Array�ྲ̬���ݳ�Ա
void Array::modifyArray(int n, int type)
{
	switch (type)
	{
	case MEDICINE:
		numArrayOfMedicine += n;
		break;

	case PERSONNEL:
		numArrayOfPersonnel += n;
		break;

	case USER:
		numArrayOfUser += n;
		break;
	}
}

// ���ĵ�ǰ��½�û�
void Array::login(int type)
{
	current_user = type;
}

/////////////////////////////////////////////////
// ������ ArrayOfMedicine

// ArrayOfMedicine����޲ι��캯��
ArrayOfMedicine::ArrayOfMedicine()
{
	medicine = new Medicine[MAX_RECORD_MEDICINE];
	record_index = 0;
	num_of_medicine = 0;
	modifyArray(1, MEDICINE);
}

// ArrayOfMedicine��Ĵ�һ���βεĹ��캯��
ArrayOfMedicine::ArrayOfMedicine(int n)
{
	medicine = new Medicine[n];
	modifyArray(1, MEDICINE);
}

// ArrayOfMedicine��ĸ��ƹ��캯��
ArrayOfMedicine::ArrayOfMedicine(ArrayOfMedicine & array_of_medicine)
{
	// need to copy all the contents? or simply the header?
	record_index = array_of_medicine.record_index;
	medicine = new Medicine[MAX_RECORD_MEDICINE];
	for (int i = 0; i < record_index; i++)
	{
		medicine[i].name = array_of_medicine.medicine[i].name;
		medicine[i].number = array_of_medicine.medicine[i].number;
		medicine[i].amount = array_of_medicine.medicine[i].amount;
		medicine[i].price = array_of_medicine.medicine[i].price;
		medicine[i].accessibility = array_of_medicine.medicine[i].accessibility;
	}
}

// ArrayOfMedicine�����������
ArrayOfMedicine::~ArrayOfMedicine()
{
	modifyArray(-1, MEDICINE);
}

// ��ӻ����һ����¼
void ArrayOfMedicine::Add(int t_number, string t_name, int t_amount, double t_price)
{
	if (getCurrentUser() == IS_MANAGER)
	{
		if (t_amount > 0)
		{
			catchError(E_AUTHORITY);
		}
		else
		{
			int t_index = FindIndex(t_number);
			if (medicine[t_index].amount + t_amount < 0)
			{
				bool check_amount = catchError(E_AMOUNT);
			}
			else
			{
				medicine[t_index].name = t_name;
				medicine[t_index].amount += t_amount;
				medicine[t_index].price = t_price;
				cout << "--ҩƷ��Ϣ���³ɹ���--" << endl << endl;
			}
		}
	}
	else
	{
		int judge = checkFormat(t_number, t_name);
		if (catchError(judge))
		{
			if (record_index > 900)
			{
				cout << "�洢�ռ䲻�㣬ʣ�� " << 1000 - record_index << " ����¼�ռ�ɹ�ʹ�á�" << endl;
			}
			if (judge == W_UPDATE_MEDICINE)
			{
				int t_index = FindIndex(t_number);
				if (medicine[t_index].amount + t_amount < 0)
				{
					bool check_amount = catchError(E_AMOUNT);
				}
				else
				{
					medicine[t_index].name = t_name;
					medicine[t_index].amount += t_amount;
					medicine[t_index].price = t_price;
					cout << "--ҩƷ��Ϣ���³ɹ���--" << endl << endl;
				}
			}
			else
			{
				medicine[record_index].number = t_number;
				medicine[record_index].name = t_name;
				medicine[record_index].amount = t_amount;
				medicine[record_index].price = t_price;
				medicine[record_index].accessibility = true;
				medicine[record_index].index = record_index;
				record_index++;
				cout << "--ҩƷ���ɹ���--" << endl << endl;
			}
		}
	}
}

// ɾ��һ����¼
void ArrayOfMedicine::Delete(int index)
{
	int error_code = NO_ERROR;							// ����error_codeΪNO_ERROR
	if (index >= record_index || index < 0)							// ���������±�ֵ������ǰ����±�
	{
		error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
	}
	else if (medicine[index].accessibility == false)	// ����������ڸ�����¼���ǲ��ɷ��ʣ���ζ��������¼�ѱ�ɾ��
	{
		error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
	}
	bool judge = catchError(error_code);				// ���ò�������judge���ڽ���catchError��Ա�������жϽ��
	if (judge == true)									// ���û�д�����ִ��ɾ������
	{
		medicine[index].accessibility = false;			// ��������±��Ӧ�ļ�¼��accessibility������Ϊfalse����ζ��������¼���ɷ��ʣ�Ҳ���Ǳ�ɾ��
		cout << "ɾ���ɹ���" << endl;
	}
}

// ����ģʽѡ��������ҩƷ��Ϣ
void ArrayOfMedicine::Show(int index, int mode)
{
	bool judge = false;
	if (index != IGNORE_INDEX)
	{
		int error_code = NO_ERROR;							// ����error_codeΪNO_ERROR
		if (index >= record_index || index < 0 )
		{													// ���������±�ֵ����Ŀǰ����±�ֵ���߸����±�ֵ�ҵ��ļ�¼��ɾ��
			error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
		}
		else if (medicine[index].accessibility == false)
		{
			error_code = E_NO_RECORD;
		}
		judge = catchError(error_code);				// ���ò�������judge���ڽ���catchError��Ա�������жϽ��
	}

	if (judge == true || index == IGNORE_INDEX)
	{
		switch (mode)
		{
		case SHOW_TITLES:								// ���������¼������������
			cout << setw(20) << "ҩƷ���" << setw(20) << "ҩƷ����" << setw(20) << "ҩƷ����" << setw(20) << "ҩƷ����" << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << setw(20) << medicine[index].number << setw(20) << medicine[index].name << setw(20) << medicine[index].amount << setw(20) << medicine[index].price << endl;
			break;

		case NO_SHOW_TITLES:							// ���������¼��������������
			cout << setw(20) << medicine[index].number << setw(20) << medicine[index].name << setw(20) << medicine[index].amount << setw(20) << medicine[index].price << endl;
			break;

		case ONLY_SHOW_TITLES:							// ֻ���������
			cout << setw(20) << "ҩƷ���" << setw(20) << "ҩƷ����" << setw(20) << "ҩƷ����" << setw(20) << "ҩƷ����" << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			break;
		}
	}
	
}

// ��ʾ��ǰ����ҩƷ��Ϣ
void ArrayOfMedicine::ShowAllMedicine()
{
	Show(IGNORE_INDEX, ONLY_SHOW_TITLES);						// ���������
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼
	{
		if (medicine[i].accessibility == true)			// ����ҵ�û�б�ɾ���ļ�¼
		{	
			Show(i, NO_SHOW_TITLES);					// ���������¼����ϸ��Ϣ
		}
	}
}

// ����ҩƷ��Ų�ѯ�±�
int ArrayOfMedicine::FindIndex(int t_number)
{
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼
	{
		if (medicine[i].accessibility == true && medicine[i].number == t_number)
		{												// ����ҵ�û��ɾ���ļ�¼���Ҹü�¼�ı��������ҵı����ͬ
			return medicine[i].index;					// ����������¼���±�ֵ
		}
	}
	return E_NO_RECORD;									// ���û���ҵ��κμ�¼�����ش������E_NO_RECORD
}

// �õ���ǰ�ĺϷ���¼����
int ArrayOfMedicine::calNumberOfMedicine()
{
	num_of_medicine = 0;								// ����num_of_personnelΪ0���Է�������ͬһ�����ж�μ��㷵��ֵ��һ�µ�����
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼���в���
	{
		if (medicine[i].accessibility == true)			// ����ҵ�һ�����Է��ʵļ�¼����ζ����û�б�ɾ��
		{
			num_of_medicine++;							// �����ҵ��Ŀɷ��ʵļ�¼����1
		}
	}

	return num_of_medicine;							// �����ҵ��Ŀɷ��ʵļ�¼��
}


// ����û������벢�ҳ�����
int ArrayOfMedicine::checkFormat(int t_number, string t_name)
{
	if (getCurrentUser() == IS_WAREHOUSE || getCurrentUser() == IS_ADMIN)
	{
		for (int i = 0; i < record_index; i++)
		{
			if (medicine[i].accessibility == true)
			{
				if (medicine[i].number == t_number)
				{
					if (medicine[i].name == t_name)
					{
						return W_UPDATE_MEDICINE;
						break;
					}
					else if(t_name == IGNORE )
					{
						return NO_ERROR;
						break;
					}
					else
					{
						return E_NUMBER;
					}
				}
			}
		}
		return NO_ERROR;
	}
	else if (getCurrentUser() == IS_MANAGER)
	{
		if (t_name == IGNORE)
		{
			return NO_ERROR;
		}
		else
		{
			return E_AUTHORITY;
		}
	}
}

///////////////////////////////////////////////////
// ������ ArrayOfUser

// ArrayOfUser���޲ι��캯��
ArrayOfUser::ArrayOfUser()
{
	user = new User[MAX_RECORD_USER];					// Ĭ������¼��100��
	record_index = 0;
	num_of_user = 0;
	modifyArray(1, USER);								// ��Array�ྲ̬���ݳ�ԱnumArrayOfUser��1
}

// ArrayOfUser���һ���βεĹ��캯��
ArrayOfUser::ArrayOfUser(int n)
{
	user = new User[n];									// �ֶ�ָ������¼������ǰ�汾��δʹ�ã�Ϊ����汾Ԥ����
	modifyArray(1, USER);
}

// ArrayOfUser�ิ�ƹ��캯��
ArrayOfUser::ArrayOfUser(ArrayOfUser & array_of_user)
{
														// ��ơ��ڵ�ǰ�汾��δʹ�ã�Ϊ����汾Ԥ����
	record_index = array_of_user.record_index;
	user = new User[MAX_RECORD_USER];
	for (int i = 0; i < record_index; i++)
	{
		user[i].authority = array_of_user.user[i].authority;
		user[i].account = array_of_user.user[i].account;
		user[i].password = array_of_user.user[i].password;
		user[i].accessibility = array_of_user.user[i].accessibility;
		record_index++;
	}
}

// ArrayOfUser����������
ArrayOfUser::~ArrayOfUser()
{
	modifyArray(-1, USER);								// ��Array���о�̬���ݳ�ԱnumArrayOfUser��1
}

// ���һ����¼
void ArrayOfUser::Add(int t_authority, int t_number, string t_account, string t_password)
{
	int judge = checkFormat(t_authority, t_number, t_account);
														// �������
	if (catchError(judge))
	{
		if (record_index > 90)							// �����¼���Ѿ�����90������ʾ�洢�ռ���������
		{
			cout << "�洢�ռ䲻�㣬ʣ�� " << 1000 - record_index << " ����¼�ռ�ɹ�ʹ�á�" << endl;
		}

		user[record_index].authority = t_authority;
		if (t_authority == IS_ADMIN)					// �Ǽ�ϵͳ����Ա
		{
			admin_existed = true;
		}		
		user[record_index].number = t_number;
		user[record_index].account = t_account;
		user[record_index].password = t_password;
		user[record_index].accessibility = true;
		user[record_index].index = record_index;
		record_index++;
		cout << "--�˻������ɹ���--" << endl << endl;
	}
	
}

// ɾ��һ����¼
void ArrayOfUser::Delete(int index)
{
	int error_code = NO_ERROR;							// ����error_codeΪNO_ERROR
	if (index >= record_index || index < 0)							// ���������±�ֵ������ǰ����±�
	{
		error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
	}
	else if (user[index].accessibility == false)	// ����������ڸ�����¼���ǲ��ɷ��ʣ���ζ��������¼�ѱ�ɾ��
	{
		error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
	}
	bool judge = catchError(error_code);				// ���ò�������judge���ڽ���catchError��Ա�������жϽ��
	if (judge == true)									// ���û�д�����ִ��ɾ������
	{
		user[index].accessibility = false;			// ��������±��Ӧ�ļ�¼��accessibility������Ϊfalse����ζ��������¼���ɷ��ʣ�Ҳ���Ǳ�ɾ��
		cout << "--ɾ���ɹ���--" << endl << endl;
	}
}

// ���������ģʽѡ��������м�¼���
void ArrayOfUser::Show(int index, int mode)
{
	bool judge = false;
	if (index != IGNORE_INDEX)
	{
		int error_code = NO_ERROR;							// ����error_codeΪNO_ERROR
		if (index >= record_index || index < 0 )
		{													// ���������±�ֵ����Ŀǰ����±�ֵ���߸����±�ֵ�ҵ��ļ�¼��ɾ��
			error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
		}
		else if (user[index].accessibility == false)
		{
			error_code = E_NO_RECORD;
		}
		judge = catchError(error_code);				// ���ò�������judge���ڽ���catchError��Ա�������жϽ��
	}

	if (judge == true || index == IGNORE_INDEX)
	{
		switch (mode)
		{
		case SHOW_TITLES:								// ���������¼����������
			cout << setw(20) << "Ȩ��" << setw(20) << "�˻���" << endl;
			cout << "----------------------------------------" << endl;
			cout << setw(20) << macroToString(user[index].authority) << setw(20) << user[index].account << endl;
			break;

		case NO_SHOW_TITLES:							// ���������¼������������
			cout << setw(20) << macroToString(user[index].authority) << setw(20) << user[index].account << endl;
			break;

		case ONLY_SHOW_TITLES:							// ֻ���������
			cout << setw(20) << "Ȩ��" << setw(20) << "�˻���" << endl;
			cout << "----------------------------------------" << endl;
			break;
		}
	}

}

// ��ʾ����ע���û�����Ϣ
void ArrayOfUser::ShowAllUser()
{
	Show(IGNORE_INDEX, ONLY_SHOW_TITLES);						// ���������
	for (int i = 0; i < record_index; i++)				// ������Ч��¼
	{
		if (user[i].accessibility == true)
		{
			Show(i, NO_SHOW_TITLES);					// ����ü�¼��ϸ��Ϣ	
		}
	}
}

// ����ArrayOfUser����صĺ�תΪ�ַ���
string ArrayOfUser::macroToString(int macro_code)
{
	switch (macro_code)
	{
	case IS_ADMIN:
		return "ϵͳ����Ա";
		break;

	case IS_MANAGER:
		return "������Ա";
		break;

	case IS_WAREHOUSE:
		return "�ֿ����Ա";
		break;
	}
}

// ���ݱ�Ų����±�
int ArrayOfUser::FindIndex(int t_number)
{
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼
	{
		if (user[i].accessibility == true && user[i].number == t_number)
		{												// ����ҵ�һ����¼û�б�ɾ��������������ҵı����ͬ
			return user[i].index;						// ����������¼���±�
		}
	}
	return E_NO_RECORD;									// ����Ҳ�����ؼ�¼�����ش������E_NO_RECORD
}

// �õ���ǰ�û��ĺϷ���¼����
int ArrayOfUser::calNumberOfUser()
{
	num_of_user = 0;								// ����num_of_personnelΪ0���Է�������ͬһ�����ж�μ��㷵��ֵ��һ�µ�����
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼���в���
	{
		if (user[i].accessibility == true)			// ����ҵ�һ�����Է��ʵļ�¼����ζ����û�б�ɾ��
		{
			num_of_user++;							// �����ҵ��Ŀɷ��ʵļ�¼����1
		}
	}

	return num_of_user;							// �����ҵ��Ŀɷ��ʵļ�¼��
}

// ��⵱ǰ��¼���û���Ȩ��
int ArrayOfUser::checkAuthority()
{
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼
	{
		if (user[i].accessibility == true && user[i].is_login == true)
		{												// ���������¼û�б�ɾ�������ѵ�¼
			return user[i].authority;					// ����������¼��Ȩ����Ϣ
			break;
		}
	}
	return NO_USERS;									// ���û���ҵ��κε�¼�û����ǺϷ��û������ش���NO_USERS
}
	 
// ����û������벢�ҳ�����
int ArrayOfUser::checkFormat(int t_authority, int t_number, string t_account)
{
	if (t_authority == IS_ADMIN)						// ���������Ϣ��t_authority�Ƿ�ΪIS_ADMIN�����ж��û��Ƿ���Ҫ����ϵͳ����Ա�˻�
	{
		if (admin_existed)								// ����Ѿ�������ϵͳ����Ա�˻�
		{			
			return E_ADMIN_EXISTED;						// ���ش������E_ADMIN_EXISTED
		}
		else											// ���������û���������Ա�˻�
		{
			return NO_ERROR;							// ���ش���NO_ERROR
		}
	}
	else												// ���������Ϣ��t_authority��ΪIS_ADMIN������Ϊ�û���Ҫ����һ���˻�
	if (!admin_existed)									// ��������ڹ���Ա���������û�����һ���˻� 
	{
		return E_AUTHORITY;
	}
	else
	{
		for (int i = 0; i < record_index; i++)			// ����֮ǰ�ļ�¼���в���
		{
			if (user[i].accessibility == true)			// ����ҵ�һ�����Է��ʵļ�¼����ζ����û�б�ɾ��
			{
				if (user[i].number == t_number)			// �˶Ա�ţ��������ͬ����˻�
				{
					return E_NUMBER;					// ���ش������E_NUMBER
					break;
				}
				if (user[i].account == t_account)		// �˶��˻������������ͬ���˻�
				{
					return E_ACCOUNT;					// ���ش������E_ACCOUNT
					break;
				}
			}
		}
		return NO_ERROR;								// ���û���ҵ��κ����⣬���ش���NO_ERROR
	}
}

/////////////////////////////////////////
// ������ ArrayOfPersonnel

// ArrayOfPersonnel����޲ι��캯��
ArrayOfPersonnel::ArrayOfPersonnel()
{
	personnel = new Personnel[MAX_RECORD_PERSONNEL];	// Ĭ�����������¼����Ϊ1000��
	record_index = 0;
	num_of_personnel = 0;
	modifyArray(1, PERSONNEL);							// ������Array�еľ�̬���ݳ�ԱnumArrayOfPersonnel��1
}

// ArrayOfPersonnel��Ĵ�һ���βεĹ��캯��
ArrayOfPersonnel::ArrayOfPersonnel(int n)
{
	personnel = new Personnel[n];						// �ֶ�ָ������¼������Ŀǰ�汾��û��Ӧ�ã�Ϊ����汾Ԥ����
	modifyArray(1, PERSONNEL);
}

// ArrayOfPersonnel��ĸ��ƹ��캯��
ArrayOfPersonnel::ArrayOfPersonnel(ArrayOfPersonnel & array_of_personnel)
{				
														// ִ����ơ��ڵ�ǰ�汾û��Ӧ�ã�Ϊ����汾�е�����ת�ƺͻָ�����Ԥ����
	record_index = array_of_personnel.record_index;
	personnel = new Personnel[MAX_RECORD_PERSONNEL];
	for (int i = 0; i < record_index; i++)
	{
		personnel[i].number = array_of_personnel.personnel[i].number;
		personnel[i].name = array_of_personnel.personnel[i].name;
		personnel[i].age = array_of_personnel.personnel[i].age;
		personnel[i].identity = array_of_personnel.personnel[i].identity;
		personnel[i].accessibility = array_of_personnel.personnel[i].accessibility;
	}
}

// ArrayOfPersonnel�����������
ArrayOfPersonnel::~ArrayOfPersonnel()
{
	modifyArray(-1, PERSONNEL);							// ������Array�еľ�̬���ݳ�ԱnumArrayOfPersonnel��1
}

// ��ӻ������Ա��¼
void ArrayOfPersonnel::Add(int t_number, string t_name, int t_age, int t_identity)
{
	int judge = checkFormat(t_number, t_name, t_age, t_identity);
														// �ȼ��������Ϣ�ĺϷ��ԣ����жϲ�������
	if (catchError(judge))								// ������ͨ������ζ��������Ϣ�ǺϷ���
	{
		int t_index = FindIndex(t_number);				// �����ݱ���ҵ����±�ֵ�洢��t_index�У��Լ����ظ�����
		if (record_index > 900)							// ����¼������900ʱ�������û�ע��洢�ռ���������ǰ�汾���洢��¼��Ϊ1000����������ɾ�������ڡ�
		{
			cout << "�洢�ռ䲻�㣬ʣ�� " << 1000 - record_index << " ����¼�ռ�ɹ�ʹ�á�" << endl;
		}
		switch (judge)									// ����judge�Ľ������ѡ��
		{
		case W_UPDATE_PERSONNEL:						// ���ģʽ������Ա��Ϣ����
			personnel[t_index].name = t_name;
			personnel[t_index].age = t_age;
			personnel[t_index].identity = t_identity;
			cout << "--��Ա��Ϣ���³ɹ���--" << endl << endl;
			break;

		case NO_ERROR:									// ���ģʽ������Ա��Ϣ���
			personnel[record_index].number = t_number;
			personnel[record_index].name = t_name;
			personnel[record_index].age = t_age;
			personnel[record_index].identity = t_identity;
			personnel[record_index].accessibility = true;
			personnel[record_index].index = record_index;
			record_index++;
			cout << "--��Ա��Ϣ��ӳɹ���--" << endl << endl;
			break;
		}
	}
}

// ���������ģʽѡ��������м�¼���
void ArrayOfPersonnel::Show(int index, int mode)
{
	bool judge = false;
	if (index != IGNORE_INDEX)
	{
		int error_code = NO_ERROR;							// ����error_codeΪNO_ERROR
		if (index >= record_index || index < 0 )
		{													// ���������±�ֵ����Ŀǰ����±�ֵ���߸����±�ֵ�ҵ��ļ�¼��ɾ��
			error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
		}
		else if (personnel[index].accessibility == false)
		{
			error_code = E_NO_RECORD;
		}
		judge = catchError(error_code);				// ���ò�������judge���ڽ���catchError��Ա�������жϽ��
	}
	
	if (judge == true || index == IGNORE_INDEX)
	{
		switch (mode)
		{
		case SHOW_TITLES:								// ���ģʽ�������������¼�������������;�������
			cout << setw(20) << "��Ա���" << setw(20) << "����" << setw(20) << "����" << setw(20) << "���" << endl;		
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << setw(20) << personnel[index].number << setw(20) << personnel[index].name << setw(20) << personnel[index].age << setw(20) << macroToString(personnel[index].identity) << endl;
			break;

		case NO_SHOW_TITLES:							// ���ģʽ�������������¼������Ϣ��������������
			cout << setw(20) << personnel[index].number << setw(20) << personnel[index].name << setw(20) << personnel[index].age << setw(20) << macroToString(personnel[index].identity) << endl;
			break;

		case ONLY_SHOW_TITLES:							// ���ģʽ�������������
			cout << setw(20) << "��Ա���" << setw(20) << "����" << setw(20) << "����" << setw(20) << "���" << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			break;
		}
	}
	
}

// ɾ��һ����¼
void ArrayOfPersonnel::Delete(int index)
{
	int error_code = NO_ERROR;							// ����error_codeΪNO_ERROR
	if (index >= record_index || index < 0)							// ���������±�ֵ������ǰ����±�
	{
		error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
	}					
	else if (personnel[index].accessibility == false)	// ����������ڸ�����¼���ǲ��ɷ��ʣ���ζ��������¼�ѱ�ɾ��
	{
		error_code = E_NO_RECORD;						// ���ش������E_NO_RECORD
	}
	bool judge = catchError(error_code);				// ���ò�������judge���ڽ���catchError��Ա�������жϽ��
	if (judge == true)									// ���û�д�����ִ��ɾ������
	{
		personnel[index].accessibility = false;			// ��������±��Ӧ�ļ�¼��accessibility������Ϊfalse����ζ��������¼���ɷ��ʣ�Ҳ���Ǳ�ɾ��
		cout << "ɾ���ɹ���" << endl;
	}
}

// ��ʾ���е���Ա��Ϣ
void ArrayOfPersonnel::ShowAllPersonnel()
{
	Show(IGNORE_INDEX, ONLY_SHOW_TITLES);						// �����������ʹ�ò���ONLY_SHOW_TITLES����Show������Ա����ָ��ֻ���������
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼���в���
	{
		if (personnel[i].accessibility == true)			// ����ҵ�һ�����Է��ʵļ�¼����ζ��������¼û�б�ɾ��
		{
			Show(i, NO_SHOW_TITLES);					// ����ҵ��ļ�¼��Ϣ��ʹ�ò���NO_SHOW_TITLES����Show������Ա����ָ��ֻ�����¼�ľ�����Ϣ
		}
	}
}

// ���뱾����صĺ�ת��Ϊ�ַ���
string ArrayOfPersonnel::macroToString(int macro_code)
{
	switch (macro_code)
	{
	case CUSTOMER:
		return "�˿�";
		break;

	case STAFF:
		return "������Ա";
		break;

	case VENDOR:
		return "������";
		break;
	}
}

// ���ݱ�Ų����±�
int ArrayOfPersonnel::FindIndex(int t_number)
{
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼���в���
	{
		if (personnel[i].accessibility == true && personnel[i].number == t_number)
		{												// ����ҵ�һ�����Է��ʵļ�¼����������¼�еı��������ҵı����ͬ
			return personnel[i].index;					// �򷵻�������¼���±�
		}
	}
	return E_NO_RECORD;									// ���������δ�ҵ�����Ҫ��ļ�¼���򷵻ش������E_NO_RECORD
}

// �õ���ǰ��Ա��Ϣ�ĺϷ���¼����
int ArrayOfPersonnel::calNumberOfPersonnel()
{
	num_of_personnel = 0;								// ����num_of_personnelΪ0���Է�������ͬһ�����ж�μ��㷵��ֵ��һ�µ�����
	for (int i = 0; i < record_index; i++)				// ����֮ǰ�ļ�¼���в���
	{
		if (personnel[i].accessibility == true)			// ����ҵ�һ�����Է��ʵļ�¼����ζ����û�б�ɾ��
		{
			num_of_personnel++;							// �����ҵ��Ŀɷ��ʵļ�¼����1
		}
	}

	return num_of_personnel;							// �����ҵ��Ŀɷ��ʵļ�¼��
}

// ����û������벢�ҳ�����
int ArrayOfPersonnel::checkFormat(int t_number,string t_name,int t_age,int t_identity)
{
	if (getCurrentUser() == IS_ADMIN)					// ��鵱ǰ��¼�û���Ȩ�ޡ�ֻ��ϵͳ����Ա��Ȩ�޽�����Ա��Ϣ�޸ĵ���ز�����
	{
		for (int i = 0; i < record_index; i++)			// ����֮ǰ�ļ�¼���в���
		{
			if (personnel[i].accessibility == true)		// ����ҵ�һ�����Է��ʵļ�¼����ζ����û�б�ɾ��
			{
				if (personnel[i].number == t_number)	// �ȼ����
				{
					if (personnel[i].name == t_name)	// ����Ѵ�����ͬ�ı�ţ�������������
					{
						if (personnel[i].age == t_age)
						{
							if (personnel[i].identity - t_identity)
							{
								return E_NUMBER;		// ��������£��Ѵ�����ȫ��ͬ�ļ�¼��ϵͳ��Ϊ���û�������󣬷��ش������E_NUMBER����Ϊϵͳ�Ա����Ϊ�����ж�����
							}
							else
							{
								return W_UPDATE_PERSONNEL;
														// ��������£��Ѵ���ֻ�������Ϣ��ͬ�ļ�¼��ϵͳ��Ϊ�û���Ҫ���¸�����¼�����ؾ������W_UPDATE_PERSONNEL
							}
						}
						else
						{
							return W_UPDATE_PERSONNEL;	// ��������£��Ѵ�������ͬ�����ͬ���Ƶļ�¼��ϵͳ��Ϊ�û���Ҫ���¸�����¼�����ؾ������W_UPDATE_PERSONNEL
						}
						
					}
					else
					{
						return W_UPDATE_PERSONNEL;		// ��������£��Ѵ�����ͬ��ŵ��ǲ�ͬ���Ƶļ�¼��ϵͳ��Ϊ�û���Ҫ���¸�����¼�����ؾ������W_UPDATE_PERSONNEL
						break;
					}
				}
			}
		}
		return NO_ERROR;								// �������֮ǰ�����м�¼��û�з����쳣��ϵͳ��Ϊ�û���Ҫ���һ��ȫ�µļ�¼�����ش���NO_ERROR
	}
	else
	{
		return E_AUTHORITY;								// ���Ȩ�޼��δͨ�������ش������E_AUTHORITY
	}
}
