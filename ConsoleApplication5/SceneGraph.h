//////////////////////////////////////////////////////////////////////////////
//
//  --- SceneGraph.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

#include "Angel.h"
#include "Nodes.h"

namespace Scene {

//----------------------------------------------------------------------------
//
//  --- SceneGraph ---
//
/// \class SceneGraph
/// \brief Container class that is the root of the scene graph for the
///    application, and holds  all of the nodes in a scene

struct SceneGraph {

    typedef Angel::mat4         mat4;
    typedef std::vector<Node*>  Nodes;
  
    Nodes  nodes; /// Container for all nodes in the scene
    
    mat4  P;  /// Projection transformation for the scene
    mat4  MV; /// Current model-view transformation for the scene

    SceneGraph() : nodes(), P(), MV() {}

    ~SceneGraph()
        { nodes.clear(); }

    void addNode( Node* n )
        { nodes.push_back( n ); }
};

//----------------------------------------------------------------------------

};  // namespace Scene

#endif // __SCENEGRAPH_H__
