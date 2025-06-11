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

	bool SetRule(bool (*MyRule)(AnyT, AnyT));//Метод, которым можно задать правило очереди. Для сравнения: первым идёт элемент очереди, вторым - сравниваемый элемент
	//Если не изменять правило (не писать своё правило), то очередь будет работать как обычная очередь
	bool operator$(AnyT first, AnyT second) { return Rule_ptr(first, second); }//Оператор проверки правила

	//Стандартные методы Queue
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

	Node* pTop;//Голова/конец очереди(первый элемент, который будет выполнен раньше)
	Node* pDown;//Хвост/начало очереди

	int lenght;

	bool constLock = false; //блокировка от изменений правила во время экспоатации очереди
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

template<class AnyT> //Можно создать своё правило, по которому новому элементу будет присвоено своё мессто в очереди
inline bool Queue<AnyT>::SetRule(bool(*MyRule)(AnyT, AnyT))// true - означает, что элемент двигается дальше, от конца очереди (от первого элеммента) 
{
	if (constLock) {
		throw QueueExeption{"You can't to change the rule again"};
	}
	Rule_ptr = MyRule;
	constLock = true;
	return true;
}
//Важно заметить, что смена правила, уже после обозначения правила или после использования очереди (например добавления в очередб элемента)
//Может ухудшить читаемость кода и привести к ошибкам. Поэтому изменение правила доступно только в самом начале (до переобозначения)

template<class AnyT>
void Queue<AnyT>::push(AnyT NewData)
{
	++lenght;
	constLock = true;

	Node* pNewNode = new Node;
	pNewNode->Data = NewData;
	pNewNode->pNext = nullptr;

	Node* pTemp = pTop;

	while (pTemp && Rule_ptr(pTemp->Data, NewData)) { //Прокрутка очереди до нужного элемента, пока элементы очереди есть и новый элемент соответствует правилу 
		pTemp = pTemp->pNext;
	}

	if (!pTemp) {//Если после прокрутки очереди до нужного элемента, из цикла вишло, что pTemp == nullptr, на это есть две причины
		if (!pTop) {//Очередь изначально не имеет элементов
			pTop = pNewNode;
			pDown = pNewNode;
			return;
		}
		//Очередь прокрутилась до конца
		pDown->pNext = pNewNode;
		pDown = pNewNode;
		return;
	}

	//Если добавление начинается с головы (новый верхний элемент)
	if (pTemp == pTop) {
		pNewNode->pNext = pTop;
		pTop = pNewNode;
		return;
	}
	//Вставка между:
	//Значение, узла, удовлетворяющего условию (pTemp), меняется с добавляемым значением 
	pNewNode->Data = pTemp->Data;
	pTemp->Data = NewData;

	pNewNode->pNext = pTemp->pNext;//Связка следующего от узла, удовлетворяющего условию (pTemp), с новым узлом (в новом узле уже прошлое значение pTemp)
	pTemp->pNext = pNewNode;//Пересвязка узла, удовлетворяющего условию (pTemp) с новым значением, с новым узлом (в новом узле уже прошлое значение pTemp)

	//Если пересвязка была с концом очереди
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

