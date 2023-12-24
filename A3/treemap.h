#pragma once

#include <memory>
#include <iostream>
#include <utility>
#include <tuple>

#include <cassert>

// forward declaration to resolve cross-referencing
namespace my {
    template<typename K, typename T>
    class treemap;
}

// forward declaration to resolve cross-referencing
template<typename K, typename T>
void
swap(my::treemap<K,T>& lhs, my::treemap<K,T>& rhs);

namespace my {

/*
 * class treemap<K,T>
 * represents an associative container (dictionary) with unique keys
 * implemented by a binary search tree
 *
 */
template<typename K, typename T>
class treemap
{
protected:
    /*
     * hierarchical node structure for class treemap
     */
    class node {
    public:
        // key and value represented as pair (so they can be easily passed along together)
        std::pair<K, T> data_;
        // smart pointer to parent
        std::weak_ptr<node> parent_;
        // smart pointers to children
        std::shared_ptr<node> leftChild_; 
        std::shared_ptr<node> rightChild_;

        node(std::shared_ptr<node> parent, std::pair<K,T> data) {
            parent_ = parent;
            data_ = data;
        }

    }; // class node

    std::shared_ptr<node> root_; 
    size_t size_;
public:

    // public type aliases
    using key_type = K;
    using mapped_type = T;
    using value_type = std::pair<K, T>;

    // iterator: references a node within the tree
    class iterator {

    protected:

        // treemap is a friend, can call protected constructor
        friend class treemap;
        std::weak_ptr<node> currentPtr_;
        std::weak_ptr<node> rootPtr_;

        // construct iterator referencing a specific node
        // - only treemap shall be allowed to do so
        iterator(std::shared_ptr<node> start, std::shared_ptr<node> root = nullptr)
        {
            currentPtr_ = start;
            rootPtr_ = root;
        }

        iterator() {};

        // non-owning reference to the actual node

        // helper function for iterator finding min element
        iterator min()
        {
            auto p = currentPtr_.lock();
            while(p->leftChild_ != nullptr) {
                p = p->leftChild_;
            }
            return p;
        }

        // helper function for iterator finding max element
        iterator max() const
        {
            auto p = currentPtr_.lock();
            while(p->rightChild_ != nullptr) {
                p = p->rightChild_;
            }
            return p;
        }

    public:

        // access data of referenced map element (node)
        value_type& operator*()
        {
            return currentPtr_.lock()-> data_;
        }
        value_type* operator->()
        {
            return &(currentPtr_.lock()-> data_);
        }

        // two iterators are equal if they point to the same node
        bool operator==(const iterator& rhs) const
        {
            return currentPtr_.lock() == rhs.currentPtr_.lock();
        }

        bool operator!=(const iterator& rhs) const
        {
            return !(*this == rhs);
        }

        // next element in map, pre-increment
        // note: must modify self!
        iterator& operator++()
        {
            auto l = currentPtr_.lock();
            if(l->rightChild_ != nullptr)
            {
                currentPtr_ = iterator(l->rightChild_).min().currentPtr_.lock();
                return *this;
            }

            auto p = l->parent_.lock();
            while(p != nullptr && l == p->rightChild_)
            {
                l = p;  
                p = p->parent_.lock();
            }
            currentPtr_ = p;
            return *this;
        }

        // prev element in map, pre-decrement
        // note: must modify self!
        iterator& operator--()
        {
            auto l = currentPtr_.lock();
            if(l == nullptr) {
                // find max element
                currentPtr_ = iterator(rootPtr_.lock()).max().currentPtr_.lock();
                return *this;
            }
            if(l->leftChild_ != nullptr)
            {
                currentPtr_ = iterator(l->leftChild_).max().currentPtr_.lock();
                return *this;
            }

            auto p = l->parent_.lock();
            while(p != nullptr && l == p->leftChild_)
            {
                l = p;
                
                p = p->parent_.lock();
            }
            currentPtr_ = p;
            return *this;
        }

    }; // class iterator


    // used for copy&move
    template<typename KK, typename TT>
    friend void ::swap(treemap<KK,TT>& lhs, treemap<KK,TT>& rhs);

    // construct empty map
    treemap();

    // move ctor
    treemap(treemap<K,T>&&);

    // helper for pre order traversal
    void pre_order_traversal(iterator it, treemap& lhs);

    // deep copy ctor
    treemap(const treemap<K,T>&);

    // how often is the element contained in the map?
    // (for this type of container, can only return 0 or 1)
    size_t count(const K&) const;

    // assignment (move & copy)
    treemap<K,T>& operator=(treemap<K,T>);

    // remove/destroy all elements
    void clear();

    // random read-only access to value by key, does not modify map
    T operator[](const K& ) const;

    // random write access to value by key
    T& operator[](const K&);

    // number of elements in map (nodes in tree)
    size_t size() const;

    // iterator referencing first element (node) in map
    iterator begin();

    // iterator referencing no element (node) in map
    iterator end() const;

    // add a new element into the tree
    // returns pair, consisting of:
    // - iterator to element
    // - bool
    //   - true if element was inserted;
    //   - false if key was already in map (will not overwrite existing value)
    std::pair<iterator,bool> insert(const K&, const T&);

    // add a new element into the tree, or overwrite existing element if key already in map
    // returns:
    // - iterator to element
    // - true if element was newly created; false if existing element was overwritten
    std::pair<iterator,bool> insert_or_assign(const K&, const T&);

    // find element with specific key. returns end() if not found.
    iterator find(const K&) const;

};

template<typename K, typename T>
treemap<K,T>::treemap()
{
    size_ = 0;
}

template<typename K, typename T>
void
treemap<K,T>::clear()
{
    root_ = nullptr;
    size_ = 0;
}

// random read-only access to value by key
template<typename K, typename T>
T
treemap<K,T>::operator[](const K& key) const
{
    iterator it = find(key);
    return it->second;
}

// random write access to value by key
template<typename K, typename T>
T&
treemap<K,T>::operator[](const K& key)
{
    // _ is not required to be used
    auto [it, _] = insert(key, T());
    return it->second;
}

// number of elements in map (nodes in tree)
template<typename K, typename T>
size_t treemap<K,T>::size() const
{
    return size_;
}

// move ctor
template<typename K, typename T>
treemap<K,T>::treemap(treemap<K,T>&& rhs)
{
    swap(*this, rhs);
}

template<typename K, typename T>
void
treemap<K,T>::pre_order_traversal(treemap<K,T>::iterator it, treemap<K,T>& lhs) {
    if(it == iterator(nullptr)) {
        return;
    }
    // copy rhs to lhs
    auto key = it.currentPtr_.lock()->data_.first;
    auto value = it.currentPtr_.lock()->data_.second;
    lhs.insert(key,value);

    treemap<K,T>::pre_order_traversal(it.currentPtr_.lock()->leftChild_, lhs);
    treemap<K,T>::pre_order_traversal(it.currentPtr_.lock()->rightChild_, lhs);    
}

// deep copy ctor
template<typename K, typename T>
treemap<K,T>::treemap(const treemap<K,T>& rhs)
{
    // traverse in pre order
    size_ = 0;
    pre_order_traversal(iterator(rhs.root_),*this);    
}

// assignment (move & copy)
template<typename K, typename T>
treemap<K,T>& 
treemap<K,T>::operator=(treemap<K,T> rhs)
{
    clear();
    // create temporary tree
    tmp = treemap(rhs);
    swap(*this, *tmp);
    *this = tmp;

    return *this;
}

// iterator referencing first element (node) in map
template<typename K, typename T>
typename treemap<K,T>::iterator
treemap<K,T>::begin()
{
    return iterator(root_).min();
}

// iterator referencing no element (node) in map
template<typename K, typename T>
typename treemap<K,T>::iterator
treemap<K,T>::end() const
{
    return iterator(nullptr, root_);
}

// add a new element into the tree
// returns:
// - iterator to element
// - true if element was inserted; false if key was already in map
template<typename K, typename T>
std::pair<typename treemap<K,T>::iterator,bool>
treemap<K,T>::insert(const K& key, const T& value)
{
    /**
     * T < current: left
     * T > current: right
     * T = current: rewrite
     */
    // check size - if 0: insert root node
    if(size_ == 0)
    {
        root_ = std::make_shared<node>(nullptr,std::make_pair(key,value));
        size_++;
        return std::make_pair(iterator(root_),true);
    }
    // make tmp unique pointer for accessing node
    auto nxt = root_;
    // until successfully inserted
    while(true) {
        if(key < nxt->data_.first) { // left side
            if(nxt->leftChild_ == nullptr) {
                nxt->leftChild_ = std::make_shared<node>(nxt,std::make_pair(key,value));
                size_++;
                return std::make_pair(iterator(nxt->leftChild_),true);
            }
            nxt = nxt->leftChild_;
        }
        else if(key > nxt->data_.first) { // right side
            if(nxt->rightChild_ == nullptr) {
                nxt->rightChild_ = std::make_shared<node>(nxt,std::make_pair(key,value));
                size_++;
                return std::make_pair(iterator(nxt->rightChild_),true);
            }
            nxt = nxt->rightChild_;
        }
        else { // equal
            return std::make_pair(iterator(nxt),false);    
        }
    }
}

// add a new element into the tree, or overwrite existing element if key already in map
// returns:
// - iterator to element
// - true if element was newly created; false if value for existing key was overwritten
template<typename K, typename T>
std::pair<typename treemap<K,T>::iterator,bool>
treemap<K,T>::insert_or_assign(const K& key, const T& value)
{
    iterator it = find(key);
    if(it == iterator(nullptr)) {
        return insert(key,value);
    }
    it->second = value;
    return std::make_pair(it,false);
}

// find element with specific key. returns end() if not found.
template<typename K, typename T>
typename treemap<K,T>::iterator
treemap<K,T>::find(const K& key) const
{
    auto nxt = root_;
    // until successfully found or nullptr
    while(nxt != nullptr) {
        if(key < nxt->data_.first) {
            // left side
            nxt = nxt->leftChild_;
        } else if(key > nxt->data_.first) {
            // right side
            nxt = nxt->rightChild_;
        } else {
            return iterator(nxt);    
        }
    }
    return iterator(nxt);
}

// how often is the element contained in the map?
template<typename K, typename T>
size_t
treemap<K,T>::count(const K& key) const
{
    iterator it = find(key);
    if(it == iterator(nullptr)) {
        return 0;
    }
    return 1;
}

} // namespace my

// swap is overloaded in global namespace
// see https://stackoverflow.com/questions/11562/how-to-overload-stdswap
// (answer by Attention Mozza314)
template<typename K, typename T>
void
swap(my::treemap<K,T>& lhs, my::treemap<K,T>& rhs)
{
    std::swap(lhs.root_,rhs.root_);
    std::swap(lhs.size_,rhs.size_);
}

