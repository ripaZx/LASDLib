
namespace lasd {

/* ************************************************************************** */

template <typename Data>
List<Data>::Node::Node(const Data& dat) {
    Element = dat;
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
    delete Element;
    next = nullptr;
    delete next;
}

template <typename Data>
bool List<Data>::Node::operator==(const Node& nod) const noexcept {
    if (Element == nod.Element)
        return true;
    else
        return false;
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& nod) const noexcept {
    return !(*this==nod);
}

/* ************************************************************************** */

template <typename Data>
List<Data>::List(const LinearContainer<Data>& con) {
    size = con.Size();
    for (unsigned long i=0; i<size; i++) 
    {
        
    }
}

/* ************************************************************************** */
}
