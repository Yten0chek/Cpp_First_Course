#pragma once
//���������� �����, ���������� �������� ������ ����
template<class AnyT>
class Stack
{
public:
	Stack();
	~Stack();
	void push(AnyT NewData);				//1. ���������� ��������
	AnyT pop();								//2. �������� �������� ��������
	AnyT top() { return pHead->Data; }		//3. ��������� �������� �������� ��� ��������
	int size() { return lenght; }			//4. ��������� ������� �����
	bool empty() { return lenght == 0; }	//5. ��������� ���������� � �����, ���� ��� ���
	

private:
	struct Node //����, � ������� ��������� ������� ������ � ��������� �� ���������
	{
		AnyT Data;
		Node* pNext;
	};
	Node* pHead;
	int lenght;
};

template<class AnyT>
Stack<AnyT>::Stack()//������� �����������
{
	pHead = nullptr;
	lenght = 0;
}

template<class AnyT>
Stack<AnyT>::~Stack()//����������, ������� �� ������ ����� �� �����, ��������� ������
{
	while (pHead) {
		Node* pDelete = pHead;
		pHead = pHead->pNext;
		delete pDelete;
	}
	lenght = 0;
}

template<class AnyT>
inline void Stack<AnyT>::push(AnyT NewData)//���������� ��������
{
	//���������� ������ �����. ����� �������� ����� ����, ������� ������ ����� ������� �����
	++lenght;
	Node* pNewNode = new Node;
	pNewNode->Data = NewData;
	//���� ���� �� ����� ���� ��� ����, ��������� ������� ������ �������� - �������� ������. ����� ��������������� ������
	pNewNode->pNext = pHead;
	pHead = pNewNode;
}

template<class AnyT>
inline AnyT Stack<AnyT>::pop()//�������� �������� ��������
{
	--lenght;
	Node* pTop = pHead; //��������� ��������� ����, ����� �������������� ������
	pHead = pHead->pNext;
	AnyT returnedData = pTop->Data; //��������� �������� ���������� ����, ��� ������������ ��������
	delete pTop; //������� ��������������� ����
	return returnedData;
}

