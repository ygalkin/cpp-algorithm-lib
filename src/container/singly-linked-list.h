#ifndef _CONTAINER_SINGLY_LINKED_LIST_
#define _CONTAINER_SINGLY_LINKED_LIST_

// Single-linked list implementation

namespace container {

    template< class ValT >
    class singly_linked_list {
    protected:
        template< class NodeValT >
        struct list_node {
            list_node() = delete;
            explicit list_node(const NodeValT& val) : _next{ nullptr }, _val{ val } {};
            list_node(const list_node& other) = delete;
            list_node(list_node&& other) = delete;
            list_node& operator = (const list_node& other) = delete;
            list_node& operator = (list_node&& other) = delete;
            ~list_node() = default;

            list_node<NodeValT>* _next;
            NodeValT _val;
        };

    private:
        list_node<ValT>* _head{ nullptr };

        // O(n)
        list_node<ValT>* _get_node(size_t index) noexcept {
            auto current = _head;
            decltype(index) i{ 0 };

            while (current != nullptr && i != index) {
                ++i;
                current = current->_next;
            }

            if (i != index) {
                return nullptr;
            }

            return current;
        }

    public:
        singly_linked_list() = default;
        singly_linked_list(const singly_linked_list& other) = delete;
        singly_linked_list(singly_linked_list&& other) = delete;
        singly_linked_list& operator = (const singly_linked_list& other) = delete;
        singly_linked_list& operator = (singly_linked_list&& other) = delete;
        virtual ~singly_linked_list() { clear(); }

        template<class IterT>
        class iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            //using difference_type = std::ptrdiff_t;
            using value_type = IterT;
            using pointer = value_type*;
            using reference = value_type&;

            iterator() = delete;
            explicit iterator(list_node<IterT>* ptr) : _ptr(ptr) {
            }

            reference operator*() const { return _ptr->_val; }
            pointer operator->() { return &_ptr->_val; }

            // Prefix increment
            iterator& operator++() {
                if (_ptr) {
                    _ptr = _ptr->_next;
                }
                return *this;
            }

            // Postfix increment
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const iterator& a, const iterator& b) { return a._ptr == b._ptr; };
            friend bool operator!= (const iterator& a, const iterator& b) { return a._ptr != b._ptr; };

        private:
            list_node<IterT>* _ptr;
        };

        iterator<ValT> begin() { return iterator<ValT>(_head); }
        iterator<ValT> end() { return iterator<ValT>(nullptr); }

        // Get the value of the index-th node in the linked list. 
        // If the index is invalid, std::out_of_range exception is generated.
        // O(n)
        ValT at(size_t index) {
            const auto node{ _get_node(index) };
            if (node == nullptr) {
                throw new std::out_of_range("Index is out of range: " + index);
            }

            return node->_val;
        }

        // Add a node before the first element of the linked list. 
        // After the insertion, the new node will be the first node of the linked list.
        // O(1)
        void push_front(const ValT& val) {
            const auto new_node{ new list_node<ValT>(val) };

            new_node->_next = _head;
            _head = new_node;
        }

        // Append a node to the last element of the linked list.
        // O(n)
        void push_back(const ValT& val) {
            if (_head == nullptr) {
                push_front(val);
                return;
            }

            auto current{ _head };
            while (current->_next != nullptr) {
                current = current->_next;
            }

            current->_next = new list_node<ValT>(val);
        }

        // Add a node before the index-th node in the linked list. 
        // If index equals to the length of linked list, the node will be appended to the end of linked list. 
        // If index is greater than the length, the node will not be inserted.
        // O(n)
        bool insert_before(size_t index, const ValT& val) {
            if (index == 0) {
                push_front(val);
                return true;
            }

            const auto prev{ _get_node(index - 1) }; // find previous
            if (prev == nullptr) {
                return false;
            }

            const auto new_node{ new list_node<ValT>(val) };

            new_node->_next = prev->_next;
            prev->_next = new_node;

            return true;
        }

        // Add a node after the index-th node in the linked list. 
        // O(n)
        bool insert_after(size_t index, const ValT& val) {
            const auto curr{ _get_node(index) };
            if (curr == nullptr) {
                return false;
            }

            const auto new_node{ new list_node<ValT>(val) };

            new_node->_next = curr->_next;
            curr->_next = new_node;

            return true;
        }

        // Delete the index-th node in the linked list, if the index is valid.
        // O(n)
        bool erase(size_t index) {
            if (index == 0) { // pop_front
                auto tmp = _head;
                _head = _head->_next;
                delete tmp;
                return true;
            }

            const auto prev{ _get_node(index - 1) }; // find previous
            if (prev == nullptr) {
                return false;
            }

            auto tmp = prev->_next;
            prev->_next = prev->_next->_next;
            delete tmp;

            return true;
        }

        // O(1)
        bool empty() const noexcept {
            return _head == nullptr;
        }

        // O(n)
        void clear() {
            auto current{ _head };
            decltype(current) tmp{ nullptr };

            while (current != nullptr) {
                tmp = current;
                current = current->_next;
                delete tmp;
            }
            _head = nullptr;
        }

        void for_each(std::function<void(const ValT&)> f) const noexcept {
            auto current{ _head };
            decltype(current) tmp{ nullptr };

            while (current != nullptr) {
                tmp = current;
                f(tmp->_val);
                current = current->_next;
            }
        }

        // Self diagnostic function
        bool has_cycle() const noexcept {
            if (_head == nullptr) {
                return false;
            }

            auto slow{ _head };
            auto fast{ _head };

            while (fast != nullptr && fast->_next != nullptr) {
                slow = slow->_next;
                fast = fast->_next->_next;

                if (fast == slow) {
                    return true;
                }
            }

            return false; // if fast == nullptr we have reached end of the list
        }
    };
}

#endif 
