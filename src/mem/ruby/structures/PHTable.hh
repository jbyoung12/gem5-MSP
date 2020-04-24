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

#ifndef __MEM_RUBY_STRUCTURES_PHTABLE_HH__
#define __MEM_RUBY_STRUCTURES_PHTABLE_HH__

#include <iostream>
#include <unordered_map>

#include "mem/ruby/common/Address.hh"

class PHTable
{
  public:
    PHTable();
    ~PHTable()
    { }

    // message includes message and machineid, e.g. read_machine_p1
    bool isPresent(std::string message) const;
    std::string* allocate(std::string message);
    void deallocate(std::string message);

    std::string *lookup(std::string message);

    // Print cache contents
    void print(std::ostream& out) const;

  private:
    // Private copy constructor and assignment operator
    PHTable(const PHTable& obj);
    PHTable& operator=(const PHTable& obj);

    // Data Members (m_prefix)
    std::unordered_map<std::string, std::string> m_map;

  private:
    int m_number_of_PHTEntries = 0;
};

inline std::ostream&
operator<<(std::ostream& out, const PHTable<ENTRY>& obj)
{
    obj.print(out);
    out << std::flush;
    return out;
}

inline bool
PHTable<std::string>::isPresent(std::string message) const
{
    return !!m_map.count(message);
}

inline std::string*
PHTable<std::string>::allocate(std::string message)
{
    m_number_of_PHTEntries += 1;
    assert(!isPresent(message));
    m_map[message] = ENTRY();
    return &(m_map[message]);
}

inline void
PHTable<std::string>::deallocate(std::string message)
{
    m_number_of_PHTEntries -= 1;
    assert(isPresent(message));
    assert(m_map.size() > 0);
    m_map.erase(message);
}

// looks an address up in the cache
inline std::string*
PHTable<std::string>::lookup(std::string message)
{
  if (m_map.find(message) != m_map.end()) return &(m_map.find(message)->second);
  return NULL;
}


std::string
inline void
PHTable<std::string>::print(std::ostream& out) const
{
}

#endif // __MEM_RUBY_STRUCTURES_PHTable_HH__
