#include "ListRand.hpp"
#include <iostream>
#include <functional>

void ListRand::Serialize(std::ostream &RefOS)
{
	// Сохранениие кол-ва элементов в списке.
	Save(RefOS, &Count, sizeof(Count));

	int LIndex = 0;

	for (ListNode* LNode = Head; LNode; LNode = LNode->Next, ++LIndex)
	{
		// Сохранение Data.
		std::string::size_type LLength = LNode->Data.length();
		Save(RefOS, &LLength, sizeof(LLength));
		Save(RefOS, LNode->Data.data(), LLength);

		// Сохранение индекса случайного элемента.
		int LIndexRandom = GetIndexOfRandom(LNode, LIndex); 
		Save(RefOS, &LIndexRandom, sizeof(LIndexRandom));
	} 

	return;
}

void ListRand::Deserialize(std::istream &RefIS)
{
	// Массив элементов, необходим для быстрого доступа ко всем существующим элементам в списке.
	std::vector<ListNode*> LNodesArray;
	// Мапа элементов, которым необходимо указать ссылку на рандомные элементы (например, если у 2 элемента должна быть ссылка на 4, но его ещё нет
	// , то записываем элемент в ключ и индекс рандомного элемента в значение).
	std::map<ListNode*, int> LNodeRandomMap;

	// Загрузка кол-ва элементов в списке.
	int LCount;
	Load(RefIS, &LCount, sizeof(LCount));

	int LRandomIndex;
	size_t LLength;
	std::string LData;

	for (int LIndex = 0; LIndex < LCount; ++LIndex)
	{
		// Загрузка Data.
		Load(RefIS, &LLength, sizeof(LLength));
		LData.resize(LLength);
		Load(RefIS, (void*)LData.data(), LLength);

		// Загрузка индексов рандомных элементов.
		Load(RefIS, &LRandomIndex, sizeof(LRandomIndex));

		ListNode* LNewNode = Add(LData);

		LNodesArray.push_back(LNewNode);

		// Если случайного элемента нет, то идём дальшее по циклу.
		if (LRandomIndex == -1) continue;

		// Если элемент указывает сам на себя в рандоме, то так и присваиваем.
		if (LIndex == LRandomIndex)
			LNewNode->Rand = LNewNode;
		// Если текущий индекс < , то запоминаем это в мапу.
		else if (LIndex < LRandomIndex)
			LNodeRandomMap.insert_or_assign(LNewNode, static_cast<int>(LRandomIndex));
		// В ином случае присваем элементу рандом.
	    else
		    LNewNode->Rand = LNodesArray[LRandomIndex];
	}

	// Для оставшихся нод задаём рандом из мапы.
	for (std::pair<ListNode*, int> LNodeRandom : LNodeRandomMap)
	{
		LNodeRandom.first->Rand = LNodesArray[LNodeRandom.second];
	}
}

// Добавление элмента в список.
ListNode *ListRand::Add(const std::string &InData)
{
    ListNode* LResult = new ListNode();
    LResult->Data = InData;

    if (Count == 0)
    {
    	Head = LResult;
    }
    else
    {
    	Tail->Next = LResult;
    	LResult->Prev = Tail;
    }
    
    Tail = LResult;
    ++Count;

	return LResult;
}

int ListRand::GetIndexOfRandom(const ListNode *InCurrentNode, int InCurrentIndex) const
{
	if (!InCurrentNode || !InCurrentNode->Rand || InCurrentIndex < 0 || InCurrentIndex >= Count) return -1;

	if (InCurrentNode == InCurrentNode->Next)
		return InCurrentIndex;

	int LResult = ++InCurrentIndex;

	for (const ListNode* LNode = InCurrentNode->Next; LNode; LNode = LNode->Next, ++LResult)
	{
		if (InCurrentNode->Rand == LNode)
			return LResult;
	}

	LResult = --InCurrentIndex;

	for (const ListNode* LNode = InCurrentNode->Prev; LNode; LNode = LNode->Prev, --LResult)
	{
		if (InCurrentNode->Rand == LNode)
			return LResult;
	}

	return -1;
}

void ListRand::PrintList(const std::string &InListName)
{
	if (InListName.length() > 0)
	    std::cout << InListName << '\n';

    std::cout << "List count: " << Count << '\n';
    std::string LRandData = "nullptr";
    ListNode* LNode = Head;

    for (int LIndex = 1; LNode; LNode = LNode->Next, ++LIndex)
    {
        std::cout << LIndex << ") " << LNode->Data << '\n';

        LRandData = (LNode->Rand ? LNode->Rand->Data : "nullptr"); 

        std::cout << "Rand: " << LRandData << '\n';
    }
}