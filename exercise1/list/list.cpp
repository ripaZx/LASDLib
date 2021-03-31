
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
    unsigned long i = size;

    head = new Node(con[--i]);
    while (i>0)
    {
        head->next = new Node(con[--i]);
        head = head->next;
    }
}

template <typename Data>
List<Data>::List(const List<Data>& lis) {
    size = lis.Size();
    if(size != 0)
    {
        head = new Node(lis.head->Element);
        Node* tmpHead = head;
        Node* tmpLisHead = lis.head;
        while(tmpLisHead != nullptr)
        {
            tmpHead->next = new Node(tmpLisHead->Element);
            tmpHead = tmpHead->next;
            tmpLisHead = tmpLisHead->next;
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
    Node* tmpNode = head;
    Node* nextNode;
    while (tmpNode != nullptr)
    {
        nextNode = tmpNode->next;
        delete tmpNode;
        tmpNode = nextNode;
    }
    delete tmpNode;
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
        Node* tmpHead = head;
        Node* tmpLisHead = lis.head;
        while (tmpHead != nullptr)
        {
            if(tmpHead->Element != tmpLisHead->Element)
                return false;
            else
            {
                tmpHead = tmpHead->next;
                tmpLisHead = tmpLisHead->next;
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
        Node* tmpNode = head;
        head = head->next;
        delete tmpNode;
        size--;
    }
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
Data& List<Data>::FrontNRemove() {
    if (size != 0)
    {
        Node* tmpNode = head;
        Data* element = &(tmpNode->Element);
        head = head->next;
        delete tmpNode;
        size--;
        return *element;
    }
    else
        throw std::length_error("Access to an empty list.");
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& dat) {
    Node* newTail = new Node(dat);
    Node* current = head;

    while (current->next != nullptr)
        current = current->next;
    
    current->next = newTail;
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& dat) noexcept {
    Node* newTail = new Node(std::move(dat));
    Node* current = head;

    while (current->next != nullptr)
        current = current->next;
    
    current->next = newTail;
    size++;
}

template <typename Data>
void List<Data>::Clear() {
    if (size != 0)
    {
        Node* current;
        while (head != nullptr)
        {
            current = head;
            delete head;
            head = current->next;
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

/* ************************************************************************** */
}
