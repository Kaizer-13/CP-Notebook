/***
    For sum query on the path from node u to node v,
    We need keep the nodes in an array in dfs order.

    ara[i] = val[x] if i is the starting time of node x
    ara[i] = -1 * val[x] if i is the ending time of node x

    let's suppose p = lca(u, v).
    * Way 1
        The ranges [st[p], st[u]] and [st[p], st[v]] will give the answer.
        Here st[p] occurs twice. Needs to be handled.

    * Way 2
        if u == p : [st[u], st[v]]
        else [en[u], st[v]]. Here st[p] is not counted, needs to be handled.
***/
