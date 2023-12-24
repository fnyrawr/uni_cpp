namespace my
{
    template<typename ValueT>
    class vector
    {
        private:
            // dataPtr_ is pointer to start of array, size_ stores the actual element count
            size_t size_ = 0;
            size_t capacity_ = 0;
            ValueT *dataPtr_;

        public:
            // default constructor without arguments
            vector<ValueT>() : size_(0), capacity_(0), dataPtr_(nullptr) {}

            // default constructor with arguments, capacity_ = 0 for reserving new memory instead of reallocating
            vector<ValueT>(const size_t& n, const ValueT& v)
            {
                ValueT* memory = static_cast<ValueT*>(malloc(sizeof(ValueT) * n));
                if(memory != nullptr)
                {
                    size_ = n;
                    capacity_ = n;
                    dataPtr_ = memory;
                    for (size_t i = 0; i < n; i++)
                    {
                        // placement new
                        new(memory + i) ValueT(v);
                    }
                }
            }

            // copy constructor
            vector(const vector& rhs) : vector()
            {
                reserve(rhs.capacity_);
                for(size_t i=0; i < rhs.size(); i++)
                {
                    push_back(rhs[i]);
                }
            }

            // move constructor
            vector(vector&& rhs) : vector()
            {
                swap(*this, rhs);
            }
            
            // destructor
            ~vector()
            {
                clear();
                free(dataPtr_);
                dataPtr_ = nullptr;
            }

            // swap function
            void swap(vector& lhs, vector& rhs)
            {
                ValueT* tempDataPtr_ = lhs.dataPtr_; 
                lhs.dataPtr_ = rhs.dataPtr_;
                rhs.dataPtr_ = tempDataPtr_;

                size_t tempSize_ = lhs.size_; 
                lhs.size_ = rhs.size_;
                rhs.size_ = tempSize_;

                size_t tempCapacity_ = lhs.capacity_; 
                lhs.capacity_ = rhs.capacity_;
                rhs.capacity_ = tempCapacity_;
            }

            // reserving memory
            void reserve(const size_t& new_capacity)
            {
                if((int)new_capacity < 0)
                {
                    // throw error if new_capacity is negative
                    throw std::out_of_range("Capacity can't be negative.");
                }
                if(new_capacity == capacity_)
                {
                    // nothing to do, since nothing is changing
                    return;
                }
                if(capacity_ == 0)
                {
                    // reserving new memory without reallocation 
                    ValueT* new_memory = static_cast<ValueT*>(malloc(sizeof(ValueT) * new_capacity));
                    if(new_memory != nullptr)
                    {
                        capacity_ = new_capacity;
                        // freeing old data pointer
                        free(dataPtr_);
                        // assigning to data pointer
                        dataPtr_ = new_memory;
                    }
                    return;
                } else
                {
                    // shrinking in size or increasing in size
                    ValueT* new_memory = static_cast<ValueT*>(malloc(sizeof(ValueT) * new_capacity));
                    if(new_memory != nullptr)
                    {
                        capacity_ = new_capacity;
                        // copying elements (only until new capacity) and freeing old memory
                        for(size_t i=0; i < size_; i++)
                        {
                            if(i < new_capacity)
                            {
                                new(new_memory + i) ValueT(dataPtr_[i]);
                            }
                            (dataPtr_ + i) -> ~ValueT();
                        }
                        if(size_ > new_capacity)
                        {
                            size_ = new_capacity;
                        }
                        // freeing old data pointer
                        free(dataPtr_);
                        // assigning to data pointer
                        dataPtr_ = new_memory;
                    }
                }
            }

            void shrink_to_fit()
            {
                reserve(size_);
            }

            // operator[]
            ValueT& operator[](const size_t& i) { return dataPtr_[i]; }
            const ValueT& operator[](const size_t& i) const { return dataPtr_[i]; }

            // operator=
            vector& operator=(vector rhs)
            {
                swap(*this, rhs);
                return *this;
            }

            // at()
            ValueT& at(const size_t& i)
            {
                if(i >= size_ || i < 0)
                {
                    throw std::out_of_range("Index is out of range.");
                }
                return dataPtr_[i];
            }

            const ValueT& at(const size_t& i) const
            {
                if(i >= size_ || i < 0)
                {
                    throw std::out_of_range("Index is out of range.");
                }
                return dataPtr_[i];
            }

            // get size()
            size_t size() const { return size_; }

            // get capacity
            size_t capacity() const { return capacity_; }
            
            // empty(): if (size_ == 0) return 1, else 0
            const bool empty() const { return (size_ == 0) ? 1 : 0; }

            // clear(): deconstruct all elements and set size to 0; capacity does't change
            void clear()
            {
                for(size_t i = 0; i < size_; i++) {
                    (dataPtr_ + i) -> ~ValueT();
                }
                size_ = 0;
            }

            // inserting a new element
            void push_back(const ValueT& new_element)
            {
                // if capacity is 0, reserve at least 1 element to insert
                if(capacity_ == 0)
                {
                    reserve(1);
                }
                // if capacity reached, double reserved capacity
                else if(size_ == capacity_)
                {
                    reserve(capacity_*2);
                }
                // inserting new element at the end
                new(dataPtr_ + size_) ValueT(new_element);
                // increase size
                size_++;
            }

            // removing and returning the last element
            ValueT pop_back()
            {
                if(size_ == 0)
                {
                    throw std::out_of_range("Empty vector. Nothing to pop back here.");
                }
                // decrease size
                size_--;
                // tmp storing the last element for returning
                ValueT last_Element(dataPtr_[size_]);
                // deconstruct last element without changing allocated memory
                (dataPtr_ + size_) -> ~ValueT();
                return last_Element;
            }
    };
}