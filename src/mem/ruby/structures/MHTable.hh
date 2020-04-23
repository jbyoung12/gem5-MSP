/*
 * Copyright (c) 1999-2008 Mark D. Hill and David A. Wood
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MEM_RUBY_STRUCTURES_MHTABLE_HH__
#define __MEM_RUBY_STRUCTURES_MHTABLE_HH__

#include <iostream>
#include <unordered_map>

#include "mem/ruby/common/Address.hh"

template<class ENTRY>
class MHTable
{
  public:
    MHTable(int number_of_MHTEntries)
        : m_number_of_MHTEntries(number_of_MHTEntries)
    {
      m_array.resize(number_of_MHTEntries, nullptr);
    }

    bool isPresent(Addr address) const;

    ENTRY *lookup(Addr address);

    // Print cache contents
    void print(std::ostream& out) const;

  private:
    // Private copy constructor and assignment operator
    MHTable(const MHTable& obj);
    MHTable& operator=(const MHTable& obj);

    // Data Members (m_prefix)
    std::vector<ENTRY> m_array;

  private:
    int m_number_of_MHEntries;
};

template<class ENTRY>
inline std::ostream&
operator<<(std::ostream& out, const MHTable<ENTRY>& obj)
{
    obj.print(out);
    out << std::flush;
    return out;
}

template<class ENTRY>
inline bool
MHTable<ENTRY>::isPresent(Addr address) const
{
    assert(address < m_number_of_MHTableEntries);
    return m_array[address] != nullptr;
}


// looks an address up in the cache
template<class ENTRY>
inline ENTRY*
MHTable<ENTRY>::lookup(Addr address)
{
  if (address < m_number_of_MHTableEntries) return &(m_array[address]);
  return NULL;
}


template<class ENTRY>
inline void
MHTable<ENTRY>::print(std::ostream& out) const
{
}

#endif // __MEM_RUBY_STRUCTURES_MHTABLE_HH__
