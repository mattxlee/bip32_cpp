#ifndef BIP32_CKD_HPP
#define BIP32_CKD_HPP

#include <cstdint>

#include <vector>

#include "core_funcs.h"

namespace bip32 {

class CKDPriv {
public:
    CKDPriv(N256 k, N256 c);

    P operator[](uint32_t const& i) const;

private:
    N256 k_;
    N256 c_;
};

class CKDPub {
public:
    CKDPub(P K, N256 c);

    std::pair<P, N256> operator[](uint32_t const& i) const;

private:
    P K_;
    N256 c_;
};

} // namespace bip32

#endif
