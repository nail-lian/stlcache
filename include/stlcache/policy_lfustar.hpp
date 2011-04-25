//
// Copyright (C) 2011 Denis V Chapligin
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef STLCACHE_POLICY_LFUSTAR_HPP_INCLUDED
#define STLCACHE_POLICY_LFUSTAR_HPP_INCLUDED

#include <set>
#include <map>

using namespace std;

#include <stlcache/policy.hpp>

namespace stlcache {
    template <class Key,template <typename T> class Allocator> class policy_lfustar : public virtual policy_lfu<Key,Allocator> {
        typedef set<Key,less<Key>,Allocator<Key> > keySet;
    public:
        policy_lfustar(const size_t& size ) throw() : policy_lfu<Key,Allocator>(size) { }

        virtual const _victim<Key> victim() throw()  {
            //LFU* only operates on entries with references count equal to 1


            if (this->entries().find(1)==this->entries().end()) {
                return _victim<Key>();
            }
            keySet pad=(*(this->entries().find(1))).second;

            if (pad.begin()==pad.end()) {
                return _victim<Key>();
            }

            return _victim<Key>(*(pad.begin()));
        }
    };
}

#endif /* STLCACHE_POLICY_LFUSTAR_HPP_INCLUDED */
