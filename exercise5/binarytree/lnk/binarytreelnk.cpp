
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& nod) {
    Elem = nod.Elem;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& nod) noexcept {
    std::swap(Elem, nod.Elem);
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& dat) {
    Elem = dat;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& dat) noexcept {
    std::swap(Elem, dat);
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete left;
    delete right;
    left = nullptr;
    right = nullptr;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& nod) {
    if (*this != nod)
        Elem = nod.Elem;
    return *this;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& nod) noexcept {
    if (*this != nod)
        std::swap(Elem, nod.Elem);
    return *this;
}

template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return Elem;
}

template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return Elem;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return !(left == nullptr);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return !(right == nullptr);
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if (HasLeftChild())
        return *left;
    else
        throw std::out_of_range("Access to a non existent node.");
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    if (HasRightChild())
        return *right;
    else
        throw std::out_of_range("Access to a non existent node.");
}

/* ************************************************************************** */

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& con) {
    if (!con.Empty())
    {
        size = con.Size();
        unsigned long i = 0;
        QueueLst<NodeLnk**> que;
        NodeLnk** current;
        que.Enqueue(&root);
        while(i<size)
        {
            current = que.Head();
            (*current) = new NodeLnk(con[i++]);
            que.Dequeue();

            que.Enqueue(&(*current)->left);
            que.Enqueue(&(*current)->right);
        }
    }
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt) {
    size = bt.size;
    if (size != 0)
    {
        QueueLst<NodeLnk**> que;
        QueueLst<NodeLnk*> queBt;
        NodeLnk** current;
        NodeLnk* currentBt;
        que.Enqueue(&root);
        queBt.Enqueue(bt.root);
        while (!queBt.Empty())
        {
            current = que.Head();
            currentBt = queBt.Head();
            (*current) = new NodeLnk(*currentBt);
            que.Dequeue();
            queBt.Dequeue();

            if (currentBt->HasLeftChild())
            {
                queBt.Enqueue(currentBt->left);
                que.Enqueue(&(*current)->left);
            }
            if (currentBt->HasRightChild())
            {
                queBt.Enqueue(currentBt->right);
                que.Enqueue(&(*current)->right);
            }
        }
    }
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(size, bt.size);
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    delete root;
    root = nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt) {
    if (*this != bt)
    {
        size = bt.size;
        BinaryTreeLnk<Data>* tmpBt = new BinaryTreeLnk<Data>(bt);
        std::swap(*this, *tmpBt);
        delete tmpBt;
    }
    return *this;
}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept {
    if (*this != bt)
    {
        std::swap(root, bt.root);
        std::swap(size, bt.size);
    }
    return *this;
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& bt) const noexcept {
    if (size == 0 && bt.size == 0)
        return true;
    else if (size == bt.size)
        return (*root).CompareSubTrees(*bt.root);
    else
        return false;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& bt) const noexcept {
    return !(*this == bt);
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if (size != 0)
        return *root;
    else
        throw std::length_error("Access to an empty tree (link).");
}

template <typename Data>
void BinaryTreeLnk<Data>::Clear() {
    delete root;
    root = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
