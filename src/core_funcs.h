#ifndef BIP32_STDFUNCS_H
#define BIP32_STDFUNCS_H

#include <cstdint>

#include <vector>

namespace bip32 {

using Bytes = std::vector<uint8_t>;

Bytes Connect(Bytes const& lhs, Bytes const& rhs);

Bytes Sub(Bytes const& data, int from, int count = 0);

class N256 {
public:
    N256();

    N256(uint64_t n);

    N256& operator=(uint64_t n);

    N256 operator^(int n);

    bool operator>(N256 const& rhs) const;
    bool operator<(N256 const& rhs) const;
    bool operator==(N256 const& rhs) const;

    bool operator>=(N256 const& rhs) const;
    bool operator<=(N256 const& rhs) const;

    N256 operator+(N256 const& rhs) const;
};

struct P {
    N256 k;
    N256 c;
};

P operator+(P const& lhs, P const& rhs);

Bytes ser32(uint32_t i);

Bytes ser256(N256 const& p);

N256 parse256(Bytes const& bytes);

Bytes serP(P const& val);

P point(N256 const& k);

N256 modN(N256 const& k, N256 const& c);

bool IsInfinity(P const& K);

Bytes HMacSHA512(N256 const& key, Bytes const& data);

} // namespace bip32

#endif
