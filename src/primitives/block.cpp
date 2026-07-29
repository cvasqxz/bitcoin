// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <crypto/scrypt.h>
#include <hash.h>
#include <tinyformat.h>
#include <util/strencodings.h>

#include <type_traits>

uint256 CBlockHeader::GetHash() const
{
    return (HashWriter{} << *this).GetHash();
}

// GetPoWHash() hashes the header's raw in-memory bytes rather than a serialized
// copy, so the members must be laid out contiguously and match the 80-byte wire
// format exactly. A mismatch here would silently change every block hash.
static_assert(std::is_standard_layout_v<CBlockHeader>);
static_assert(sizeof(CBlockHeader) == 80);
static_assert(offsetof(CBlockHeader, nVersion) == 0);

uint256 CBlockHeader::GetPoWHash() const
{
    uint256 thash;
    scrypt_1024_1_1_256(begin_ptr(nVersion), begin_ptr_mutable(thash));
    return thash;
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
