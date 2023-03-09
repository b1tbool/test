____


## 1.
**Реализуйте функции сериализации и десериализации двусвязного списка, заданного следующим образом:**

```C#
class ListNode
{
    public ListNode Prev;
    public ListNode Next;
    public ListNode Rand; // произвольный элемент внутри списка
    public string Data;
}

class ListRand
{
    public ListNode Head;
    public ListNode Tail;
    public int Count;

    public void Serialize(FileStream s)
    {
    }

    public void Deserialize(FileStream s)
    {
    }
}
```

**Примечание: сериализация подразумевает сохранение и восстановление полной структуры списка, включая взаимное соотношение его элементов между собой — в том числе ссылок на Rand элементы.**

**Алгоритмическая сложность решения должна быть меньше квадратичной.**

**Нельзя добавлять новые поля в исходные классы ListNode, ListRand**

**Для выполнения задания можно использовать любой общеиспользуемый язык.**

**Тест нужно выполнить без использования библиотек/стандартных средств сериализации.**

![srlz](srlz.png)

![srlz_example](srlz_example.png)


____


## 2.
**Напишите ИИ для противника используя BhvTree (достаточно нарисовать схему, реализация в каком-либо из движков не требуется).**

**Солдат - сущность, которая может стрелять, отправиться в указанную точку и ждать.**

**Солдат проводит патруль по зацикленному маршруту по точкам А и Б**

**По прибытии на точку солдат останавливается на 5 минут в ожидании врага. Если за 5 минут враг не появился, солдат идет на следующую точку.**

**Если враг обнаружен, солдат стреляет в него с паузой в 1 секунду между каждым выстрелом**

![bt](bt.png)


____