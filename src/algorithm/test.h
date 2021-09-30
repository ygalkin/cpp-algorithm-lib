#ifndef _ALGORITHM_TEST_
#define _ALGORITHM_TEST_

#include "algorithm.h"

#include <string_view>

namespace algorithm {

    inline constexpr std::pair<std::string_view, std::string_view> TEST_SEARCH_STR{ "Some books are to be tasted, others to be swallowed, and some few to be chewed and digested.", "to" };
    inline constexpr size_t TEST_SEARCH_POS = 15;

    TEST_CASE("Naive string-searching algorithm", "[algorithm]") {
        REQUIRE(algorithm::naive_string_search("abc", "") == 0);
        REQUIRE(algorithm::naive_string_search("ab", "abc") == std::string_view::npos);
        REQUIRE(algorithm::naive_string_search(TEST_SEARCH_STR.first, TEST_SEARCH_STR.second) == TEST_SEARCH_POS);
        REQUIRE(algorithm::naive_string_search("abc", "d") == std::string_view::npos);
    }

    TEST_CASE("Knuth�Morris�Pratt string-searching algorithm", "[algorithm]") {
        REQUIRE(algorithm::kmp_string_search("abc", "") == 0);
        REQUIRE(algorithm::kmp_string_search("ab", "abc") == std::string_view::npos);
        // REQUIRE(algorithm::kmp_string_search(TEST_SEARCH_STR.first, TEST_SEARCH_STR.second) == TEST_SEARCH_POS);
        REQUIRE(algorithm::kmp_string_search("abc", "d") == std::string_view::npos);
    }
}

#endif 
