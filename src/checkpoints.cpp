// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 eBoost Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
		(    0, uint256("0x21938e71a19f0053f1ea9d2c616feba7c767ade95a20946f26747ae96aaa572b"))
		(    5, uint256("2a283ce635437c782f9e1c0c23e84b0d968a6b2444db4fa07602d302062197b1"))
		(    10, uint256("f4dfb35a1ab40c3c48a7f0034a87205686fc3aeba8802b29bdc63fa29476ade2"))
		(    50, uint256("869b80c58120339351b3f9c3c9a86313a73f6c6c41f4eca4a24a52eeac360a26"))
		(    80, uint256("8cd220a34c69f8217d6836857e619f9155cce2e81bc1726c79ba02582e438aa9"))
            	;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    uint256 GetLatestHardenedCheckpoint()
    {
        const MapCheckpoints& checkpoints = mapCheckpoints;
        return (checkpoints.rbegin()->second);
    }
}
