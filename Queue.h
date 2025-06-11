#pragma once

class QueueExeption
{
public:
	QueueExeption(std::string message) : message{ message } {}
	std::string getMessage() const { return message; }
private:
	std::string message;
};

template<class AnyT>
class Queue
{
public:
	Queue();
	~Queue();

	bool SetRule(bool (*MyRule)(AnyT, AnyT));//�����, ������� ����� ������ ������� �������. ��� ���������: ������ ��� ������� �������, ������ - ������������ �������
	//���� �� �������� ������� (�� ������ ��� �������), �� ������� ����� �������� ��� ������� �������
	bool operator$(AnyT first, AnyT second) { return Rule_ptr(first, second); }//�������� �������� �������

	//����������� ������ Queue
	void push(AnyT NewData);
	AnyT pop();
	AnyT front();
	AnyT back();
	int size() { return lenght; }
	bool empty() { return lenght == 0; }



private:
	struct Node
	{
		AnyT Data;
		Node* pNext;
	};

	Node* pTop;//������/����� �������(������ �������, ������� ����� �������� ������)
	Node* pDown;//�����/������ �������

	int lenght;

	bool constLock = false; //���������� �� ��������� ������� �� ����� ����������� �������
	bool (*Rule_ptr) (AnyT, AnyT);

	
};

template <class AnyM>
bool MainRule(AnyM a, AnyM b) { return true; }

template<class AnyT>
Queue<AnyT>::Queue()
{
	pTop = nullptr;
	pDown = nullptr;
	lenght = 0;
	Rule_ptr = MainRule;
}

template<class AnyT>
Queue<AnyT>::~Queue()
{
	while (pTop) {
		Node* pDelete = pTop;
		pTop = pTop->pNext;
		delete pDelete;
	}
	pDown = nullptr;
	delete pDown;
	lenght = 0;
	//delete Rule_ptr;
}

template<class AnyT> //����� ������� ��� �������, �� �������� ������ �������� ����� ��������� ��� ������ � �������
inline bool Queue<AnyT>::SetRule(bool(*MyRule)(AnyT, AnyT))// true - ��������, ��� ������� ��������� ������, �� ����� ������� (�� ������� ���������) 
{
	if (constLock) {
		throw QueueExeption{"You can't to change the rule again"};
	}
	Rule_ptr = MyRule;
	constLock = true;
	return true;
}
//����� ��������, ��� ����� �������, ��� ����� ����������� ������� ��� ����� ������������� ������� (�������� ���������� � ������� ��������)
//����� �������� ���������� ���� � �������� � �������. ������� ��������� ������� �������� ������ � ����� ������ (�� ���������������)

template<class AnyT>
void Queue<AnyT>::push(AnyT NewData)
{
	++lenght;
	constLock = true;

	Node* pNewNode = new Node;
	pNewNode->Data = NewData;
	pNewNode->pNext = nullptr;

	Node* pTemp = pTop;

	while (pTemp && Rule_ptr(pTemp->Data, NewData)) { //��������� ������� �� ������� ��������, ���� �������� ������� ���� � ����� ������� ������������� ������� 
		pTemp = pTemp->pNext;
	}

	if (!pTemp) {//���� ����� ��������� ������� �� ������� ��������, �� ����� �����, ��� pTemp == nullptr, �� ��� ���� ��� �������
		if (!pTop) {//������� ���������� �� ����� ���������
			pTop = pNewNode;
			pDown = pNewNode;
			return;
		}
		//������� ������������ �� �����
		pDown->pNext = pNewNode;
		pDown = pNewNode;
		return;
	}

	//���� ���������� ���������� � ������ (����� ������� �������)
	if (pTemp == pTop) {
		pNewNode->pNext = pTop;
		pTop = pNewNode;
		return;
	}
	//������� �����:
	//��������, ����, ���������������� ������� (pTemp), �������� � ����������� ��������� 
	pNewNode->Data = pTemp->Data;
	pTemp->Data = NewData;

	pNewNode->pNext = pTemp->pNext;//������ ���������� �� ����, ���������������� ������� (pTemp), � ����� ����� (� ����� ���� ��� ������� �������� pTemp)
	pTemp->pNext = pNewNode;//���������� ����, ���������������� ������� (pTemp) � ����� ���������, � ����� ����� (� ����� ���� ��� ������� �������� pTemp)

	//���� ���������� ���� � ������ �������
	if (pNewNode->pNext == nullptr)
		pDown = pNewNode;
}

template<class AnyT>
inline AnyT Queue<AnyT>::pop()
{
	if (lenght == 0)
		throw QueueExeption{ "Queue is null" };
	--lenght;
	Node* pDeleted = pTop;
	AnyT Returned = pDeleted->Data;
	pTop = pTop->pNext;
	delete pDeleted;
	return Returned;
}

template<class AnyT>
inline AnyT Queue<AnyT>::front()
{
	if (lenght == 0)
		throw QueueExeption{ "Queue is null" };
	return pTop->Data;
}

template<class AnyT>
inline AnyT Queue<AnyT>::back()
{
	if (lenght == 0)
		throw QueueExeption{ "Queue is null" };
	return pDown->Data;
}

