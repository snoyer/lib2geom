/**
 * \file
 * \brief 
 * Implementation of Red-Black Tree as described in 
 * Intorduction to Algorithms. Cormen et al. Mc Grow Hill. 1990. pp 263-280
 * 
 * The intention is to implement interval trees mentioned in the same book, after the red-black.
 * Interval are heavily based on red-black trees (most operations are the same). So, we begin first 
 * with implementing red-black!
 *
 * Authors:
 *      ? <?@?.?>
 * 
 * Copyright 2009-2009 Evangelos Katsikaros
 *
 * This library is free software; you can redistribute it and/or
 * modify it either under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * (the "LGPL") or, at your option, under the terms of the Mozilla
 * Public License Version 1.1 (the "MPL"). If you do not alter this
 * notice, a recipient may use your version of this file under either
 * the MPL or the LGPL.
 *
 * You should have received a copy of the LGPL along with this library
 * in the file COPYING-LGPL-2.1; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * You should have received a copy of the MPL along with this library
 * in the file COPYING-MPL-1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
 * OF ANY KIND, either express or implied. See the LGPL or the MPL for
 * the specific language governing rights and limitations.
 *
 */

#include <vector>
#include <utility>


#include <2geom/d2.h>
#include <2geom/interval.h>

namespace Geom{

// used only in pick_next( )
enum enum_add_to_group { 
    ADD_TO_GROUP_A = 0, 
    ADD_TO_GROUP_B
};

class RTreeNode;

/*
R-Tree has 2 kinds of nodes
* Leaves which store:
  - the actual data
  - the bounding box of the data
* Non-Leaves which store:
  - a child node
  - the bounding box of the child node

    std::vector< std::pair<Rect, int> > children_leaves;
    std::vector< std::pair<Rect, RTreeNode*> > children_nodes;

This cuases some code duplication in rtree.cpp. There are 2 cases:
- we care whether we touch a leaf/non-leaf node, since we write data in the node, so we want to 
  write the correct thing (int or RTreeNode*)
- we do NOT care  whether we touch a leaf/non-leaf node, because we only read/write the bounding 
  boxes which is the same in both cases.

A better design would eliminate the duplication in the 2nd case, but we can't avoid the 1st probably.
*/

class RTreeNode{    
public:
    // first: bounding box, second: "data" (leaf-node) or node (NON leaf-node)
    std::vector< std::pair<Rect, int> > children_leaves; // if this is empty, then node is leaf-node
    std::vector< std::pair<Rect, RTreeNode*> > children_nodes;  // if this is empty, then node is NON-leaf node

    // TODO can this design be improved ???
    
    RTreeNode(){
    }

};


class RTree{
public:
    RTreeNode* root;

    unsigned max_nodes; // allow +1 (used during insert)
    unsigned min_nodes;

    RTree( int max_n, int min_n ): 
        root(0), max_nodes( max_n ), min_nodes( min_n ) {
    }

    void insert( Rect const &r, int shape, unsigned min_nodes, unsigned max_nodes );

private:
    // I1
    RTreeNode* choose_leaf( Rect const &r, int shape );
    double find_enlargement( Rect const &a, Rect const &b );

    // I2
    std::pair<RTreeNode, RTreeNode> quadratic_split( RTreeNode *s, unsigned min_nodes );
    std::pair<unsigned, unsigned> pick_seeds( RTreeNode *s );
    std::pair<unsigned, enum_add_to_group>  pick_next( RTreeNode group_a, RTreeNode group_b, RTreeNode *s, std::vector<bool> assigned_v );

    // I3
    bool adjust_tree(       RTreeNode* position, 
                            std::pair<RTreeNode, RTreeNode>  &splitted_groups, 
                            bool split_performed, 
                            unsigned min_nodes,
                            unsigned max_nodes );
    RTreeNode* find_parent( RTreeNode* subtree_root, Rect search_area, RTreeNode* wanted );
};



}; //close namespace

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
