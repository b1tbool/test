#ifndef _LIST_RAND_HPP_
#define _LIST_RAND_HPP_

#include "ListNode.hpp"
#include "Serializable.hpp"
#include <vector>
#include <map>

class ListRand : public ISerializable
{
public:

    void Serialize(std::ostream& RefOS) override;

    void Deserialize(std::istream& RefIS) override;

	// Добавление элмента в список.
	ListNode* Add(const std::string& InData);

	int GetIndexOfRandom(const ListNode* InCurrentNode, int InCurrentIndex) const;

	void PrintList(const std::string& InListName = "");

private:

	ListNode* Head = nullptr;
    ListNode* Tail = nullptr;
    int Count = 0;
};

#endif // _LIST_RAND_HPP_