/***
    * Vertex Biconnectivity :   Removing a VERTEX does not separate any pair
                                of vertices in the current component.
                                BLOCK CUT TREE Components are vertex biconnected.

    * Edge Biconnectivity :     Removing an EDGE does not separate any pair
                                of vertices in the current component.
                                BRIDGE TREE components are edge biconnected.
    * A VERTEX biconnected graph is also EDGE biconnected. But not the other way around.

    * "Biconnected Component.cpp" assigns EACH EDGE to some biconnected component (Vertex Biconnectivity).

    * Special Biconnectivity :  Two nodes are A,B are in same biconnected component if there are
                                two vertex disjoint paths between them
                                (only vertex A and B will be common between the paths)

    * To get the specially biconnected components, run "Biconnected Component.cpp".
      Discard every component of size two. Later, check if every node is in some component.
      If not, create a new component consisting of only that node.

      If there is no multiple edge in the graph, this should work.
      When there is multiple edge, count the number of edges in every component of size two.
      Discard the component if it has only one edge. The rest is same.


    PROPERTIES

    * If a biconnected component has a node( A ) having degree greater than 3, there will always
      be another node( B ) such that, there are 3 vertex disjoint paths between node A and node B

    * If A,B,C are in same BCC, there will always be a SIMPLE path from A to B through C

    * You want to know if you can go from node a to node b by traversing edge e = (x,y).
      You can not traverse an edge multiple times.

      Build bridge tree. A = compNum[a], B = compNum[b].

      If e is not a bridge edge, Let C be the component number where edge e exist.
      If C = A or C = B, answer is yes.
      Otherwise, If path A->B contains component C, the answer is yes.

      If e is a bridge edge, check if path from A to B contains e (unique path).
      Then the answer is yes.

    * If a vertex biconnected component has an odd simple cycle, then ALL edges in
      such component belong to some odd simple cycle.


    * If there is a SIMPLE path from a to b of odd length. Assuming that the graph is connected.
      Determine the distance of every node from a random root.
      If parity of distance of a and b is not same, there is an odd path.

      Build BCT. A = compNum[a], B = compNum[b].

      If A = B, the answer is yes if there is an odd cycle in this component.
      Else,
      If A has an odd cycle the answer is yes. (a is not a cut vertex in that case)
      If B has an odd cycle the answer is yes. (b is not a cut vertex in that case)
      If the path from A to B contains a component C that has an odd cycle, the answer is yes.
***/
