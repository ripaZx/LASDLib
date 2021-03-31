
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

//TODO: DA CONTROLLARE
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
    size = con.Size();
    unsigned long i = size-1;

    head = new Node(con[i]);
    while (i>1)
    {
        i--;
        head->next = new Node(con[i]);
        head = head->next;
    }
}

template <typename Data>
List<Data>::List(const List<Data>& lis) {
    size = lis.Size();
    if(size != 0)
    {
        head = new Node(lis.head->Element);
        Node* current = head;
        Node* currentLis = lis.head;
        while(currentLis != nullptr)
        {
            current->next = new Node(currentLis->Element);
            current = current->next;
            currentLis = currentLis->next;
        }
    }
}

template <typename Data>
List<Data>::List(List<Data>&& lis) noexcept {
    std::swap(head, lis.head);
    std::swap(size, lis.size);
}

//TODO: DA CONTROLLARE INSIEME AL DISTRUTTORE DI NODE
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
    List<Data>* tmpLis = new List<Data>(lis);
    std::swap(*tmpLis, *this);
    delete tmpLis;
    return *this;
}

template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lis) noexcept {
    std::swap(head, lis.head);
    std::swap(size, lis.size);
    return *this;
}

template <typename Data>
bool List<Data>::operator==(const List<Data>& lis) const noexcept {
    if (size == lis.size)
    {
        Node* current = head;
        Node* currentLis = lis.head;
        while (current != nullptr)
        {
            if(current->Element != currentLis->Element)
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
    Node* newHead = new Node(dat);
    newHead->next = head;
    head = newHead;
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& dat) noexcept {
    Node* newHead = new Node(std::move(dat));
    newHead->next = head;
    head = newHead;
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
        Node* newHead = head->next;
        Data element = head->Element;
        delete head;
        head = newHead;
        size--;
        return element;
    }
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& dat) {
    if (head == nullptr)
        head = new Node(dat);
    else
    {
        Node* newTail = new Node(dat);
        Node* current = head;

        while (current->next != nullptr)
            current = current->next;
        
        current->next = newTail;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& dat) noexcept {
    if (head == nullptr)
        head = new Node(std::move(dat));
    else
    {
        Node* newTail = new Node(std::move(dat));
        Node* current = head;

        while (current->next != nullptr)
            current = current->next;
        
        current->next = newTail;
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
    {
        Node* current = head;
        while (current->next != nullptr)
            current = current->next;
        return current->Element;
    }
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
Data& List<Data>::operator[](const unsigned long index) const {
    if (index < size)
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
void List<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc, Node* nod) const {
    if (nod != nullptr)
    {
        func(nod->Element, par, acc);
        if (nod->next != nullptr)
            FoldPreOrder(func, par, acc, nod->next);
    }
}

template <typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc, Node* nod) const {
    if (nod != nullptr)
    {
        if (nod->next != nullptr)
            FoldPostOrder(func, par, acc, nod->next);
        func(nod->Element, par, acc);
    }
}
/* ************************************************************************** */
}
