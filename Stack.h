#pragma once
//Реализация стека, содержащий элементы одного типа
template<class AnyT>
class Stack
{
public:
	Stack();
	~Stack();
	void push(AnyT NewData);				//1. Добавление элемента
	AnyT pop();								//2. Удаление верхнего элемента
	AnyT top() { return pHead->Data; }		//3. Получение верхнего элемента без удаления
	int size() { return lenght; }			//4. Получение размера стека
	bool empty() { return lenght == 0; }	//5. Получение информации о стеке, пуст или нет
	

private:
	struct Node //Узел, в котором храниться элемент стека и указатель на следующий
	{
		AnyT Data;
		Node* pNext;
	};
	Node* pHead;
	int lenght;
};

template<class AnyT>
Stack<AnyT>::Stack()//Обычный конструктор
{
	pHead = nullptr;
	lenght = 0;
}

template<class AnyT>
Stack<AnyT>::~Stack()//Деструктор, удаляет от головы стека до конца, обнуление длинны
{
	while (pHead) {
		Node* pDelete = pHead;
		pHead = pHead->pNext;
		delete pDelete;
	}
	lenght = 0;
}

template<class AnyT>
inline void Stack<AnyT>::push(AnyT NewData)//Добавление элемента
{
	//Увеличение длинны стека. Затем создаётся новый узел, который хранит новый элемент стека
	++lenght;
	Node* pNewNode = new Node;
	pNewNode->Data = NewData;
	//Даже если до этого стек был пуст, следующий элемент нового элемента - нынешняя голова. Затем переопределение головы
	pNewNode->pNext = pHead;
	pHead = pNewNode;
}

template<class AnyT>
inline AnyT Stack<AnyT>::pop()//Удаление верхнего элемента
{
	--lenght;
	Node* pTop = pHead; //Фиксируем удаляемый узел, затем переопределяем голову
	pHead = pHead->pNext;
	AnyT returnedData = pTop->Data; //Фиксируем значение удаляемого узла, это возвращаемое значение
	delete pTop; //Удаляем зафиксированный узел
	return returnedData;
}

