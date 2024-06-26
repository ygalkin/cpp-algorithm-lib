#ifndef _SORT_SANDBOX_
#define _SORT_SANDBOX_

namespace sort {
    namespace sandbox {

        // It uses two loops, one going forward and the other going backward, instead of just one. It's a bit slower than cocktail_shaker_sort.
        template< class IterT >
        inline void cocktail_shaker_sort_2(IterT first, IterT last) {
            if (first == last) {
                return;
            }

            bool is_swapped{ true };
            for (auto begin{ first }, end{ std::prev(last) }; is_swapped; ++begin, --end) {
                // forward pass
                is_swapped = false;
                // for [first, last - 1)
                for (auto i = begin; i != end; ++i) {
                    const auto next_i{ std::next(i) };
                    if (*i > *next_i) {
                        std::iter_swap(i, next_i);
                        is_swapped = true;
                    }
                }

                if (!is_swapped) {
                    break;
                }

                // reverse pass
                is_swapped = false;
                // for [last - 1, first)
                for (auto j = end; j != begin; --j) {
                    const auto prev_j{ std::prev(j) };
                    if (*j < *prev_j) {
                        std::iter_swap(prev_j, j);
                        is_swapped = true;
                    }
                }
            }
        }

        template< class IterT >
        inline void selection_sort_2(IterT first, IterT last) {
            for (auto i = first; i != last; ++i) {
                std::iter_swap(i, std::min_element(i, last));
            }
        }

        // The same as selection_sort2() but "find min element" is a self-implemented loop and is used instead of std::min_element
        template< class IterT >
        inline void selection_sort_3(IterT first, IterT last) {
            if (first == last) {
                return;
            }

            // for [first, last-1)
            const auto end = std::prev(last);
            for (auto i = first; i != end; ++i) {
                auto min = i;
                // find min element [i + 1, last)
                for (auto j = std::next(i); j != last; ++j) {
                    if (*j < *min) {
                        min = j;
                    }
                }

                std::iter_swap(i, min);
            }
        }

        // It swaps elements using std::iter_swap instead of moving them using std::move. It works very slow.
        template <typename IterT>
        inline void insertion_sort_2(IterT first, IterT last) {
            if (first == last) {
                return;
            }

            // for [first + 1, last)
            for (auto i = std::next(first); i != last; ++i) {
                for (auto j = i, prev_j = std::prev(i); *prev_j > *j; --prev_j, --j) {
                    std::iter_swap(prev_j, j);
                    if (prev_j == first) {
                        break;
                    }
                }
            }
        }

        // TODO: self-implemented partitioning algorithm (Hoare or 3-way) instead of std::partition.
        template< class IterT >
        inline void quick_sort_2(IterT first, IterT last) {
            if (first == last) {
                return;
            }

            //const auto pivot = *(first + (std::distance(first, last) / 2));

            // Partitioning. Hoare partition scheme or 3-way
            // TODO:

            //quick_sort_2(first, left);
            //quick_sort_2(right, last);
        }

        // Stack overflow on a SORTED large array ~ 4000 elements. 
        // Lomuto�s partition scheme.
        template< class IterT >
        inline void quick_sort_3(IterT first, IterT last) {
            if (first == last) {
                return;
            }

            // Partitioning. Lomuto�s partition scheme
            const auto pivot = std::prev(last); // pivot element is a last element
            auto bound = std::partition(first, last, [&pivot](const auto& i) { return i < *pivot; });
            std::iter_swap(bound, pivot);

            quick_sort_3(first, bound);
            quick_sort_3(std::next(bound), last);
        }

        // Stack overflow on a SORTED large array ~ 4000 elements.
        // Lomuto�s partition scheme.
        template< class IterT >
        inline void quick_sort_4(IterT first, IterT last) {
            if (first == last) {
                return;
            }

            // Partitioning. Lomuto�s partition scheme
            const auto pivot = std::prev(last); // pivot element is a last element
            auto bound = first;
            // for [first, last)
            for (auto i = first; i != last; ++i) {
                if (*i < *pivot) {
                    std::iter_swap(bound, i);
                    ++bound;
                }
            }
            std::iter_swap(bound, pivot);

            quick_sort_4(first, bound);
            quick_sort_4(std::next(bound), last);
        }
    }
}

#endif