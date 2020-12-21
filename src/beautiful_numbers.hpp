#ifndef BEAUTIFUL_NUMBES_HPP
#define BEAUTIFUL_NUMBES_HPP

#include <cstdint>
#include <utility>

namespace beautiful_numbers
{
    template <unsigned N, unsigned K, class I>
    struct multibinomial;

    template <unsigned N, unsigned K, unsigned... Is>
    struct multibinomial<N, K, std::integer_sequence<unsigned, Is...>>
    {
        constexpr static uint64_t value = (static_cast<uint64_t>(0) ... + multibinomial<N - 1, K - Is, std::integer_sequence<unsigned, Is...>>::value);
    };

    template <unsigned n, unsigned... Is>
    struct multibinomial<0, n, std::integer_sequence<unsigned, Is...>>
    {
        constexpr static unsigned value = 0;
    };

    template <unsigned... Is>
    struct multibinomial<0, 0, std::integer_sequence<unsigned, Is...>>
    {
        constexpr static unsigned value = 1;
    };
    
    namespace detail
    {
        template<bool B, uint64_t T, uint64_t F>
        struct conditional_multiple { constexpr static unsigned value = T; };
         
        template<uint64_t T, uint64_t F>
        struct conditional_multiple<false, T, F> { constexpr static unsigned value = F; };
    }

    template <unsigned N>
    constexpr uint64_t count_v = multibinomial<(N / 2) * 2, (N - 1) * (N / 2), std::make_integer_sequence<unsigned, N>>::value
                       * detail::conditional_multiple< N % 2, N, 1>::value;

}

#endif