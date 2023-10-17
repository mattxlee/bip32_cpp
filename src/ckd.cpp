#include "ckd.h"

namespace bip32 {

CKDPriv::CKDPriv(N256 k, N256 c)
    : k_(std::move(k))
    , c_(std::move(c))
{
}

P CKDPriv::operator[](uint32_t const& i) const
{
    Bytes data;
    if (i >= ((uint32_t)2^31)) {
        data.push_back(0x00);
        data = Connect(data, ser256(k_));
        data = Connect(data, ser32(i));
    } else {
        data = serP(point(k_));
        data = Connect(data, ser32(i));
    }
    Bytes res = HMacSHA512(c_, data);
    Bytes l = Sub(res, 0, 32);
    Bytes r = Sub(res, 32);

    P p;
    N256 n = modN(k_, c_);
    N256 pl = parse256(l);
    p.k = pl + n;
    p.c = parse256(r);

    // check before exit
    if (parse256(l) >= n || p.k == 0) {
        throw std::runtime_error("invalid result, should try next `i`");
    }

    return p;
}

CKDPub::CKDPub(P K, N256 c)
    : K_(std::move(K))
    , c_(std::move(c))
{
}

std::pair<P, N256> CKDPub::operator[](uint32_t const& i) const
{
    if (i >= ((uint32_t)2^31)) {
        throw std::runtime_error("hardened child key is not supported");
    }
    Bytes res = Connect(serP(K_), ser32(i));
    Bytes l = Sub(res, 0, 32);
    Bytes r = Sub(res, 32);
    N256 pl = parse256(l);
    P K = point(pl) + K_;
    N256 c = parse256(r);
    if (pl >= modN(K.k, K.c) || IsInfinity(K)) {
        throw std::runtime_error("invalid result, should try next `i`");
    }
    return std::make_pair(K, c);
}

} // namespace bip32
