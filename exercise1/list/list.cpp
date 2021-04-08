
namespace lasd {

/* ************************************************************************** */

template <typename Data>
List<Data>::Node::Node(const Data& dat) {
    Element = dat;
    next = nullptr;
}

template <typename Data>
List<Data>::Node::Node(Data&& dat) {
    std::swap(Element, dat);
    next = nullptr;
}

template <typename Data>
List<Data>::Node::Node(const Node& nod) {
    Element = nod.Element;
    next = nod.next;
}

template <typename Data>
List<Data>::Node::Node(Node&& nod) noexcept {
    std::swap(Element, nod.Element);
    std::swap(next, nod.next);
}

template <typename Data>
List<Data>::Node::~Node() {
    next = nullptr;
}

template <typename Data>
bool List<Data>::Node::operator==(const Node& nod) const noexcept {
    if (Element == nod.Element)
        return true;
    else
        return false;
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node& nod) const noexcept {
    return !(*this==nod);
}

/* ************************************************************************** */

template <typename Data>
List<Data>::List(const LinearContainer<Data>& con) {
    if (!con.Empty())
    {
        size = con.Size();
        unsigned long i = 0;
        Node** current = &head;
        while (i<size)
        {
            (*current) = new Node(con[i++]);
            if (i == size)
                tail = (*current);
            else
                current = &((*current)->next);
        }
    }
}

template <typename Data>
List<Data>::List(const List<Data>& lis) {
    size = lis.Size();
    if(size != 0)
    {
        Node** current = &head;
        Node* currentLis = lis.head;
        while(currentLis != nullptr)
        {
            (*current) = new Node(*currentLis);
            // if (currentLis->next == nullptr)
            //     tail = (*current);
            //else
            {
                current = &((*current)->next);
                currentLis = currentLis->next;
            }
        }
    }
}

template <typename Data>
List<Data>::List(List<Data>&& lis) noexcept {
    std::swap(head, lis.head);
    std::swap(tail, lis.tail);
    std::swap(size, lis.size);
}

template <typename Data>
List<Data>::~List() {
    Node* nextNode;
    while (head != nullptr)
    {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
    delete head;
}

template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& lis) {
    if (*this != lis)
    {   
        size = lis.Size();
        List<Data>* tmpLis = new List<Data>(lis);
        std::swap(*tmpLis, *this);
        delete tmpLis;
    }
    return *this;
}

template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lis) noexcept {
    if (*this != lis)
    {
        std::swap(head, lis.head);
        std::swap(tail, lis.tail);
        std::swap(size, lis.size);
    }
    return *this;
}

template <typename Data>
bool List<Data>::operator==(const List<Data>& lis) const noexcept {
    if (size == lis.Size())
    {
        Node* current = head;
        Node* currentLis = lis.head;
        while (current != nullptr)
        {
            if(*current != *currentLis)
                return false;
            else
            {
                current = current->next;
                currentLis = currentLis->next;
            }
        }
        return true;
    }
    else
        return false;
}

template <typename Data>
inline bool List<Data>::operator!=(const List<Data>& lis) const noexcept {
    return !(*this==lis);
}

template <typename Data>
void List<Data>::InsertAtFront(const Data& dat) {
    if (size == 0)
    {
        head = new Node(dat);
        tail = head;
    }
    else
    {
        Node* newHead = new Node(dat);
        newHead->next = head;
        head = newHead;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& dat) noexcept {
    if (size == 0)
    {
        head = new Node(std::move(dat));
        tail = head;
    }
    else
    {
        Node* newHead = new Node(std::move(dat));
        newHead->next = head;
        head = newHead;
    }
    size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
    if (size != 0)
    {
        Node* newHead = head->next;
        delete head;
        head = newHead;
        size--;
    }
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
Data List<Data>::FrontNRemove() {
    if (size != 0)
    {
        Data element = head->Element;
        RemoveFromFront();
        return element;
    }
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& dat) {
    if (size == 0)
    {
        head = new Node(dat);
        tail = head;
    }
    else
    {
        Node* newTail = new Node(dat);      
        tail->next = newTail;
        tail = tail->next;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& dat) noexcept {
    if (size == 0)
    {
        head = new Node(std::move(dat));
        tail = head;
    }
    else
    {
        Node* newTail = new Node(std::move(dat));
        tail->next = newTail;
        tail = tail->next;
    }
    size++;
}

template <typename Data>
void List<Data>::Clear() {
    if (size != 0)
    {
        Node* current;
        while (head != nullptr)
        {
            current = head->next;
            delete head;
            head = current;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
}

template <typename Data>
Data& List<Data>::Front() const {
    if (size != 0)
        return head->Element;
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
Data& List<Data>::Back() const {
    if (size != 0)
        return tail->Element;
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
Data& List<Data>::operator[](const unsigned long index) const {
    if (index == size-1)
        return Back();
    else if (index == 0)
        return Front();
    else if (index < size-1)
    {
        Node* current = head;
        unsigned long acc = 0;
        while (acc < index)
        {
            current = current->next;
            acc++;
        }
        return current->Element;
    }
    else
        throw std::out_of_range("Access at index "+ std::to_string(index) + "; list size " + std::to_string(size) + ".");
}

template <typename Data>
void List<Data>::MapPreOrder(const MapFunctor func, void* par) {
    MapPreOrder(func, par, head);
}

template <typename Data>
void List<Data>::MapPostOrder(const MapFunctor func, void* par) {
    MapPostOrder(func, par, head);
}

template <typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc) const {
    FoldPreOrder(func, par, acc, head);
}

template <typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc) const {
    FoldPostOrder(func, par, acc, head);
}

template <typename Data>
void List<Data>::MapPreOrder(const MapFunctor func, void* par, Node* nod) {
        if (nod != nullptr)
        {
            func(nod->Element, par);
            if (nod->next != nullptr)
                MapPreOrder(func, par, nod->next);
        }
}

template <typename Data>
void List<Data>::MapPostOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        if (nod->next != nullptr)
            MapPostOrder(func, par, nod->next);
        func(nod->Element, par);
    }
}

template <typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        func(nod->Element, par, acc);
        if (nod->next != nullptr)
            FoldPreOrder(func, par, acc, nod->next);
    }
}

template <typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        if (nod->next != nullptr)
            FoldPostOrder(func, par, acc, nod->next);
        func(nod->Element, par, acc);
    }
}
/* ************************************************************************** */
}
