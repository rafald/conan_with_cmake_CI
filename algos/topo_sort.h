#pragma once
#include <vector>
#include <set>
#include <unordered_map>
#include <map> //?
#include <algorithm>
#include "boost/graph/adjacency_list.hpp"

// Adjacency List, directed, acyclic
// continuous ids for nodes starting with 0
std::vector<int> 
//topo_sort(std::unordered_multimap< int, int> adj) { 
topo_sort(std::multimap< int, int> const & adj) { 
    //find indegrees for each node 
    std::vector<int> indegrees;
    for( auto pc: adj ) { // parent/child
        auto const required_size = std::max(pc.second+1,pc.first+1);
        if(required_size > indegrees.size() ) indegrees.resize(required_size);
        ++indegrees[pc.second];
    }

    std::vector<int> result;
    // look for nodes without incoming edges
    for( auto f = std::find(indegrees.begin(), indegrees.end(), 0); 
            f!=indegrees.end();  
            f = std::find(indegrees.begin(), indegrees.end(), 0)) {
        int v = std::distance(indegrees.begin(), f);
        result.push_back(v);
        //auto [fe, le] = adj.equal_range(v);
        //std::for_each(fe, le, [&](auto e){--indegrees[e.second]; } );
        for (auto e: boost::make_iterator_range(adj.equal_range(v))) { 
            --indegrees[e.second];//remove 
        }
        *f=-1;//we do not remove processed nodes but mark as done with -1
    } 
    if( result.size() != indegrees.size()) {
        return {};
    }

    return result;
}
