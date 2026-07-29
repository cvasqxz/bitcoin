// Copyright (c) 2023 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_UTIL_CHAINTYPE_H
#define BITCOIN_UTIL_CHAINTYPE_H

#include <optional>
#include <string>

/**
 * Chaucha supports three chains. Bitcoin's testnet3/testnet4 and signet were
 * removed: their genesis blocks were mined against SHA256d and cannot satisfy
 * Chaucha's scrypt proof of work, and signet additionally depends on SegWit,
 * which Chaucha never activated.
 */
enum class ChainType {
    MAIN,
    TESTNET2,
    REGTEST,
};

std::string ChainTypeToString(ChainType chain);

std::optional<ChainType> ChainTypeFromString(std::string_view chain);

#endif // BITCOIN_UTIL_CHAINTYPE_H
