SECTION 3 - Exact Expressions and Combinatorial Lower Bounds

***Slide Group 1: Preliminaries and Definitions***

To Do: Form the conceptual basis for expressions and proofs in further slides. These include definitions and conceptual "Shortcuts" or properties used in Section 3 of the paper -- Definitions for Homomorphism and homomorphism number and chromatic number, Definition 2.1 (Homomorphism density), 3.1 (Stirling Number), 3.2 (edge density), The N(G) function used in the exact expression for computing the number of labelled bipartite cliques in target graph, Girth of a graph. Properties are (3), hom(K_{1,m},G) = sum of power of degrees of each vertex in G, Bipartiteness and N(G) function relation

***Slide 2: Exact Combinatorial Expression***

Slide Content - Proposition 3.1, and proof. Need not be 1 slide, can span more
ToDo: populate the slide with the expression and the combinatorial proof  below into LaTeX to be used as a beamer presentation. Add references to whatever you copy paste from the paper using the eq numbes in the paper

***Slde 3: Baseline Bound using vertex degree***

Content - Proposition 3.2 expression and proof
ToDo - populate with expression from the paper and use the notes below to populate the proof. Coordinate between the paper and the notes. Clean up the notation.

Proposition 3.2 proof
N1,1 (G) = |E(G)|
hom(K1,m, G) = summation of degree of vertex to power of m
Equality condition - if and only if G is C4-free 
IF - Statement: if C4-free, then lower bound is exact equality
Girth Requirement: To be C4-free, a graph G has to have girth g>=6
Remark 3.1 - if girth is g then any structure that requires a 4 cycle to exist (eg K2,2) cannot be found in G
Since K2,2 is the minimal bipartite cycle, its absence implies that all Kk,l (k,l >=2) are also absent. Therefore, all terms 0. “Every subgraph of a complete bipartite graph is a complete bipartite graph itself”

IFF - Statement: if the lower bound is exact then G must be C4-free.
Non-negativity of each term in the exact combinatorial formula. 
If the sum of terms is 0, each term is 0. The most basic term dropped was N2,2
If N2,2(G) = 0 then G cannot contain a K2,2 subgraph. And K2,2 is isomorphicC4

***Slide 3: Remarks - Limitations of Proposition 3.2***

Content - Remarks 3.2, 3.3, 3.4
ToDo - Populate using notes below and clean up by coordinating with the paper. Add references.

Remark 3.2 - Equality holds if G is C4 free
(eq 24) - m <= n/4 blah blah (theorem 6 on pg 165 - Proofs in the Book)
Can be verified 

Remark 3.3 - Constraint on edge density of G for lower bound to be exact 
Building on remark 3.2 - Applying Edge density to Eq 24 forms expression for bounded edge density
Delta scales with O(1/sqrt(n)) - For the bound in prop 3.1 to be exact, the graph G must be extremely sparse as n grows 

Remark 3.4 - Lower bound performs horribly on highly dense target graphs and hence the need for Entropy Based Bounds
Consider G a bipartite graphs with equal sized partite sets n1 = n/2, n2 = n/2 - extremely dense, packed with C4 cycles. 
Combinatorically, hom(Kp,p;G) = 2^(1-p)n^2p
Mapping p vertices to n1, p vertices to n2 (can be done independently since target graph has all possible edges)
Lower bound in Prop 3.2 gives, hom(Kpp,G) = 2^(1-p)n^(p+1) - n^2/2

 Ratio of Exact count to lower bound tends to infinity as n -> inf. “This is in contrast to the lower bounds derived in Section 4, for which the corresponding ratio tends, as desired, to 1.”

***Slide4: Corollaries - Showcasing the strengths of prop 3.2***

Content - Corollaries 3.1, 3.2, 3.3, 3.4
ToDo - Notes are sparse for 3.1 just summarise from the paper for 3.1. Populate Corollaries 3.2, .3 and .4 using notes below
Corollary 3.1 - Lower bound is exact for Trees 
Corollary 3.2 - Slightly refined expression using average degree
Concavity and Jenson’s inequality: f(x) is power function, x is degree of a vertex w. Applying jensons gives us the expression.
Equality condition - If G is C4 free AND G is regular (f(x) = x for all x or degree of all vertices in G are same)
Corollary 3.3 - Target Graph is cycle Cn
hom(Kpq, Cn) = n(2^p+2^q-2) if n=3 or n>=5
		= 2^(p+q+1) if n=4

C1, C2 are trivial
Even Cycles with n>=6 are freebies and directly plug into formula in prop 3.2 (C4 free)
Odd Cycles (n=3,5,...) 

Only Two structural configurations are possible:  Every single valid homomorphism into C_n (n>=3) must map all of U to a single vertex, OR map all of V to a single vertex. 
SECTION 3 - Exact Expressions and Combinatorial Lower Bounds

Introduce the concept of girth G after summarizing Proposition 3.1
Proposition 3.2 proof
N1,1 (G) = |E(G)|
hom(K1,m, G) = summation of degree of vertex to power of m
Equality condition - if and only if G is C4-free 
IF - Statement: if C4-free, then lower bound is exact equality
Girth Requirement: To be C4-free, a graph G has to have girth g>=6
Remark 3.1 - if girth is g then any structure that requires a 4 cycle to exist (eg K2,2) cannot be found in G
Since K2,2 is the minimal bipartite cycle, its absence implies that all Kk,l (k,l >=2) are also absent. Therefore, all terms 0. “Every subgraph of a complete bipartite graph is a complete bipartite graph itself”

IFF - Statement: if the lower bound is exact then G must be C4-free.
Non-negativity of each term in the exact combinatorial formula. 
If the sum of terms is 0, each term is 0. The most basic term dropped was N2,2
If N2,2(G) = 0 then G cannot contain a K2,2 subgraph. And K2,2 is isomorphicC4
Remarks - Testing the limits of prop 3.2
Remark 3.2 - Equality holds if G is C4 free
(eq 24) - m <= n/4 blah blah (theorem 6 on pg 165 - Proofs in the Book)
Can be verified 

Remark 3.3 - Constraint on edge density of G for lower bound to be exact 
Building on remark 3.2 - Applying Edge density to Eq 24 forms expression for bounded edge density
Delta scales with O(1/sqrt(n)) - For the bound in prop 3.1 to be exact, the graph G must be extremely sparse as n grows 

Remark 3.4 - Lower bound performs horribly on highly dense target graphs and hence the need for Entropy Based Bounds
Consider G a bipartite graphs with equal sized partite sets n1 = n/2, n2 = n/2 - extremely dense, packed with C4 cycles. 
Combinatorically, hom(Kp,p;G) = 2^(1-p)n^2p
Mapping p vertices to n1, p vertices to n2 (can be done independently since target graph has all possible edges)
Lower bound in Prop 3.2 gives, hom(Kpp,G) = 2^(1-p)n^(p+1) - n^2/2

 Ratio of Exact count to lower bound tends to infinity as n -> inf. “This is in contrast to the lower bounds derived in Section 4, for which the corresponding ratio tends, as desired, to 1.”

Corollaries - Showcasing the strengths of prop 3.2
Corollary 3.1 - Lower bound is exact for Trees 
Corollary 3.2 - Slightly refined expression using average degree
Concavity and Jenson’s inequality: f(x) is power function, x is degree of a vertex w. Applying jensons gives us the expression.
Equality condition - If G is C4 free AND G is regular (f(x) = x for all x or degree of all vertices in G are same)
Corollary 3.3 - Target Graph is cycle Cn
hom(Kpq, Cn) = n(2^p+2^q-2) if n=3 or n>=5
		= 2^(p+q+1) if n=4

C1, C2 are trivial
Even Cycles with n>=6 are freebies and directly plug into formula in prop 3.2 (C4 free)
Odd Cycles (n=3,5,...) 

Only Two structural configurations are possible:  Every single valid homomorphism into C_n (n>=3) must map all of U to a single vertex, OR map all of V to a single vertex. 


Question - Though the target graph is non-bipartite making application of Prop 3.2 legally invalid, hom(Kpq, Cn) reduces to the same formula anyway. Why?
Homomorphisms cannot change a graph's structural parity. Because our source contains zero odd cycles (consequence of being bipartite), its mapping cannot magically form an odd cycle in the target. The mapping is forced to leave at least one edge unused to avoid closing the loop.
The Result: The image is forced to map onto a subgraph that is a tree (a simple path). Because trees are perfectly C_4-free, this automatically yields the exact same simplified formula
Edge case, C4
				Simple counting ( Nkl(C4) = 0 for all k,l >2

Corollary 3.4 - Path Graph
Special case of Corollary 3.1 since “path graph Pℓ is a tree on ℓ vertices with ℓ − 2 vertices of degree 2, and two vertices of degree 1”
General form of expression - Homomorphism on Categorical Tensor Equality

