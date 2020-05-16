
#include <stdexcept>

/* ************************************************************************** */

// Node specific constructors
template <typename Data>
List<Data>::Node::Node(const Data& dat)
{
    Element = dat;
    next = nullptr;
}

template <typename Data>
List<Data>::Node::Node(const Data& dat, const Node& nex)
{
    Element = dat;
    next = nex;
}

//Node copy constructor
template <typename Data>
List<Data>::Node::Node(const Node& nod)
{
    Element = nod.Element;
    next = nod.next;
}

//Node move costructor
template <typename Data>
List<Data>::Node::Node(Node&& nod) noexcept
{
    Element = new Data();
    std::swap(Element, nod.Elemet);
    std::swap(next, nod.next);
}

//Node destructor
template <typename Data>
List<Data>::Node::~Node()
{
    Element = 0;
    next = nullptr;
    delete next;
}

//Node comparison operator
template <typename Data>
bool List<Data>::Node::operator==(const Node& nod) const noexcept
{
    if (Element == nod.Element)
        return true;
    else
        return false;   
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& nod) const noexcept
{
    return !(*this == nod);
}

/* ************************************************************************** */

// Default constructor
template <typename Data>
List<Data>::List()
{
    head = nullptr;
}

//Copy constructor
template <typename Data>
List<Data>::List(const List<Data>& lis)
{
    if (lis.head == nullptr)
        head = nullptr;
    else
    {
        head = new Node(lis.head->Element);
        Node* tmpLisHead = lis.head;
        Node* tmpHead = head;
        while (tmpLisHead != nullptr)
        {
            tmpHead->next = new Node(tmpLisHead->Element);
            tmpHead = tmpHead->next;
            tmpLisHead = tmpLisHead->next;
        }
        
        size = lis.size;
    }
    
}

//Move constructor
template <typename Data>
List<Data>::List(List<Data>&& lis) noexcept
{
    std::swap(lis.head, head);
    std::swap(lis.size, size);
}

//Destructor
template <typename Data>
List<Data>::~List()
{
    Node* tmpNod = head;
    while (tmpNod != nullptr)
    {
        Node* nextNod = tmpNod->next;
        delete tmpNod;
        tmpNod = nextNod;
    }

    delete tmpNod;
}

//Copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& lis)
{
    List<Data>* tmpLis = new List<Data>(lis);
    std::swap(tmpLis, *this);
    delete tmpLis;
    return *this;
}

//Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lis) noexcept
{
    std::swap(head, lis.head);
    std::swap(size, lis.size);
    return *this;
}

//Comparison operators
template <typename Data>
bool List<Data>::operator==(const List<Data>& lis) const noexcept
{
    if (size == lis.size)
    {
        Node* tmpHead = head;
        Node* tmpLisHead = lis.head;
        while (tmpHead != nullptr)
        {
            if(tmpHead->Element != tmpLisHead->Element)
                return false;
            
            tmpHead = tmpHead->next;
            tmpLisHead = tmpLisHead->next;
        }

        return true;
    }
    else return false;
}

template <typename Data>
bool List<Data>::operator!=(const List<Data>& lis) const noexcept
{
    return !(*this == lis);
}

//Specific member function
template <typename Data>
void List<Data>::RemoveFromFront()
{
    if (size != 0)
    {
        Node* tmpNod = head;
        head = head->next;
        delete tmpNod;
        size--;
    }
    else
        throw std::length_error("Access to an empty List");
    
}

//Specific member function
template <typename Data>
Data& List<Data>::FrontNRemove()
{
    if (size != 0)
    {
        Node* tmpNod = head;
        head = head->next;
        size--;
        return tmpNod->Element;
    }
    else
        throw std::length_error("Access to an empty List");
}

//Specific member function
template <typename Data>
void List<Data>::InsertAtFront(const Data& dat) noexcept
{
    Node* newHead = new Node(dat);
    newHead->next = head;
    head = newHead;
    size++;
}

//Specific member function
template <typename Data>
void List<Data>::InsertAtFront(Data&& dat) noexcept
{
    Node* newHead = new Node(std::move(dat));
    newHead->next = head;
    head = newHead;
    size++; 
}

//Specific member function
template <typename Data>
void List<Data>::InsertAtBack(const Data& dat) noexcept
{
    Node* newTail = new Node(dat);
    Node* lastNode = head;

    while (lastNode->next != nullptr)
        lastNode = lastNode->next;

    lastNode->next = newTail;
    size++;
}

//Specific member function
template <typename Data>
void List<Data>::InsertAtBack(Data&& dat) noexcept
{
    Node* newTail = new Node(std::move(dat));
    Node* lastNode = head;
    
    while (lastNode->next != nullptr)
        lastNode = lastNode->next;
    
    lastNode->next = newTail;
    size++;
}

//Specific member function
template <typename Data>
void List<Data>::Clear()
{
    Node* tmpNod = head;
    while (head != nullptr)
    {
        tmpNod = head;
        delete head;
        head = tmpNod->next;
    }

    head = nullptr;
    size = 0;
}

//Specific member function
template <typename Data>
Data& List<Data>::Front() const
{
    if (size != 0)
        return head->Element;
    else
        throw std::length_error("Access to an empty List");
    
}

//Specific member function
template <typename Data>
Data& List<Data>::Back() const
{
    if (size != 0)
    {
        Node* lastNode = head;

        while (lastNode->next != nullptr)
            lastNode = lastNode->next;

        return lastNode->Element;
    }
    else
        throw std::length_error("Access to an empty List");
    
}

//Specific member function
template <typename Data>
Data& List<Data>::operator[](const unsigned long int index)
{
    if (index <= size)
    {
        Node* tmpNode = head;
        unsigned long int acc = 0;
        while(acc < index)
        {
            tmpNode = tmpNode->next;
            acc++;
        }
        return tmpNode->Element;
    }
    else
        throw std::out_of_range("Access to index: " + std::to_string(index) + "List size: " + std::to_string(size));   
}

//Specific member function
template <typename Data>
void List<Data>::MapPreOrder(MapFunctor func, void* par)
{
    MapPreOrder(func, par, head);
}

//Specific member function
template <typename Data>
void List<Data>::MapPostOrder(MapFunctor func, void* par)
{
    //TODO
}

//Specific member function
template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor func, const void* par, void* acc) const
{
    FoldPreOrder(func, par, acc, head);
}

//Specific member function
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor func, const void* par, void* acc) const
{
    //TODO
}

//Specific member function
template <typename Data>
void List<Data>::MapPreOrder(MapFunctor func, void* par, Node* nod)
{
    Node* tmpHead = nod;
    while (tmpHead != nullptr)
    {
        func(tmpHead->Element, par);
        tmpHead = tmpHead->next;
    }
}

//Specific member function
template <typename Data>
void List<Data>::MapPostOrder(MapFunctor func, void* par, const Node* nod, Node* rNod)
{
    if (rNod == nod)
        func(rNod->Element, par);
    else
    {
        MapPostOrder(func, par, nod, rNod->next);
        func(rNod->Element, par);
    }
    
}

//Specific member function
template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor func, const void* par, void* acc, Node* nod) const
{
    Node* tmpHead = nod;
    while(tmpHead != nullptr)
    {
        func(tmpHead->Element, par, acc);
        tmpHead = tmpHead->next;
    }
}

//Specific member function
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor func, const void* par, void* acc, const Node* nod, Node* rNod) const
{
    if(rNod == nod)
        func(rNod->Element, par, acc);
    else
    {
        FoldPostOrder(func, par, acc, nod, rNod->next);
        func(rNod->Element, par, acc);
    }
    
}