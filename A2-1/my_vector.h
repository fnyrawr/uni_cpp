namespace my {
    template<typename ValueT>
    class vector
    {
        private:
            // dataPtr_ is pointer to start of array, size_ stores the actual element count
            size_t size_;
            ValueT *dataPtr_;

        public:
            // default constructor without arguments
            vector<ValueT>() : size_(0), dataPtr_(nullptr) {};

            // default constructor with arguments
            vector<ValueT>(int n, const ValueT& v): size_(n), dataPtr_(new ValueT[n]) {
                for (size_t i = 0; i < size_; i++)
                {
                    dataPtr_[i] = ValueT(v);
                }
            };

            // copy constructor
            vector(const vector&& rhs) {
                size_ = rhs.size_;
                dataPtr_ = rhs.dataPtr_;
            };
            
            // destructor
            ~vector()
            {
                delete[] dataPtr_;
            };

            // operator[]
            auto& operator[](size_t i) { return dataPtr_[i]; }
            const auto& operator[](size_t i) const { return dataPtr_[i]; }

            // at()
            const ValueT& at(size_t i) const {
                if(i >= size_ || i < 0)
                {
                    throw std::out_of_range("Index is out of range.");
                }
                return dataPtr_[i];
            }
            ValueT& at(size_t i) {
                if(i >= size_ || i < 0)
                {
                    throw std::out_of_range("Index is out of range.");
                }
                return dataPtr_[i];
            }

            // size()
            const size_t size() const { return size_; }
            
            // empty(): if (size_ == 0) return 1, else 0
            const bool empty() const { return (size_ == 0) ? 1 : 0; }

            // clear()
            void clear() { delete[] dataPtr_; }

            // inserting a new element
            void push_back(const ValueT& new_element) {
                ValueT *elements;
                elements = new ValueT[size_ + 1];
                // copy and paste all elements to new array
                for(size_t i = 0; i < size_; i++)
                {
                    elements[i] = dataPtr_[i];
                }
                // inserting new element at the end
                elements[size_] = new_element;
                // delete previous data, then set pointer to new array
                clear();
                dataPtr_ = elements;
                // increase size
                size_++;
            }

            // removing and returning the last element
            ValueT pop_back()
            {
                if(size_ <= 0)
                {
                    throw std::out_of_range("Empty vector. Nothing to pop back here.");
                }
                ValueT *elements = new ValueT[size_ - 1];
                // copy all elements into the new array, except the last one
                for(size_t i = 0; i < size_-1; i++)
                {
                    elements[i] = dataPtr_[i];
                }
                // tmp storing the last element for returning
                ValueT last_Element = dataPtr_[size_-1];
                // delete previous data, then set pointer to new array
                clear();
                dataPtr_ = elements;
                // decrease size
                size_--;
                return last_Element;
            }

            // forbid copying and assigning of vectors
            vector(vector<ValueT> const &) = delete;
            vector<ValueT>& operator=(vector<ValueT> const &) = delete;
    };
}