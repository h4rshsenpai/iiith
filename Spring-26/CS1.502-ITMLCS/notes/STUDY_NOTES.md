# Study Notes: Sections 4 & 4 of Graph Homomorphism Paper
## Combinatorial and Entropy-Based Bounds

---

## Section 3: Exact Expressions and Combinatorial Lower Bounds

### Definition 3.1: Stirling Numbers of the Second Kind

**Definition:** S(n,k) = number of ways to partition [n] into k nonempty, pairwise disjoint subsets

**Base cases:**
- S(n,n) = 1 (each element in its own subset)
- S(n,1) = 1 (all elements in one subset)
- S(n,0) = 0 for n > 0

**Recurrence Relation:**
$$S(n,k) = k \cdot S(n-1,k) + S(n-1,k-1)$$

**Intuition:** When placing element n:
- Join one of k existing subsets: k·S(n-1,k) ways
- Form new singleton subset: S(n-1,k-1) ways

**Closed Form:**
$$S(n,k) = \frac{1}{k!} \sum_{j=0}^{k} (-1)^{k-j} \binom{k}{j} j^n$$

---

### Proposition 3.1: Exact Formula for Homomorphisms

**Formal Statement:**
Let G be bipartite with partite sets L and R, and p,q ∈ ℕ. Then:
$$\text{hom}(K_{p,q}, G) = \sum_{k=1}^{p} \sum_{\ell=1}^{q} k!\ell! S(p,k)S(q,\ell)[N_{k,\ell}(G) + N_{\ell,k}(G)]$$

where:
- S(·,·) = Stirling numbers (Definition 3.1)
- N_{k,ℓ}(G) = number of labeled bipartite cliques with partite subsets of sizes k and ℓ in G

**Proof Outline:**

1. **Key Structural Constraint:** Every homomorphism φ: V(K_{p,q}) → V(G) must:
   - Map vertices of one partite set of K_{p,q} to vertices in the SAME partite set of G
   - Map vertices of the other partite set to the OTHER partite set
   - (Proof: If u,w in same partition of K_{p,q} but mapped to different partitions of G, then with any neighbor v of u in K_{p,q}, we get {u,w} adjacent in K_{p,q} but their images not adjacent in G, contradiction)

2. **Image is Complete Bipartite:** The image of φ forms a complete bipartite subgraph K_{k,ℓ}
   - (Proof: If not complete, there exist non-adjacent vertices from opposite partitions. But they come from adjacent vertices in K_{p,q}, so images must be adjacent, contradiction)

3. **Counting Via Surjections:** The p vertices of K_{p,q} map surjectively onto k vertices in G's left partition
   - Number of surjections [n] → [k] = k! · S(n,k)
   - Similarly for q vertices → ℓ vertices

4. **Final Count:** For each bipartite clique K_{k,ℓ} in G:
   - Count = k! · ℓ! · S(p,k) · S(q,ℓ) · h_{k,ℓ}
   - where h_{k,ℓ} = N_{k,ℓ}(G) + N_{ℓ,k}(G) (both orientations)

5. **Summation:** Sum over all possible k ∈ [p] and ℓ ∈ [q]

**Remark 3.1 (Girth Constraint):**
If G has girth g (no cycles shorter than g):
- N_{k,ℓ}(G) = 0 when min{k,ℓ} ≤ ⌊g/2⌋ - 1 and max{k,ℓ} ≤ ⌊g/2⌋
- Eliminates many terms but computing remaining N_{k,ℓ} is still expensive: O(n^{k+ℓ}) per pair

---

### Proposition 3.2: Combinatorial Lower Bound

**Formal Statement:**
Let G be bipartite with degree function d_G. Then:
$$\text{hom}(K_{p,q}, G) \geq \sum_{w \in V(G)} [d_G(w)^p + d_G(w)^q] - 2|E(G)|$$

**Equality Condition:** Equality holds if and only if G is C₄-free (contains no K_{2,2})

**Proof Strategy:**

1. **Drop Higher Terms:** Starting from Prop 3.1:
   $$\text{hom}(K_{p,q}, G) = \sum_{k=1}^p \sum_{\ell=1}^q [\ldots] + \sum_{k=1}^p [\ldots]_{k,1} + \sum_{\ell=1}^q [\ldots]_{1,\ell} - \text{(double counting term)}$$
   
   Drop all k,ℓ ≥ 2 (non-negative contribution):
   $$\geq \sum_{k=1}^p k! S(p,k)[N_{k,1}(G) + N_{1,k}(G)] + \sum_{\ell=1}^q \ell! S(q,\ell)[N_{1,\ell}(G) + N_{\ell,1}(G)] - 2|E(G)|$$

2. **Star Homomorphisms:** Define:
   $$g(m) = \sum_{k=1}^m k! S(m,k)[N_{k,1}(G) + N_{1,k}(G)]$$
   
   Claim: g(m) = ∑_{w ∈ V(G)} d_G(w)^m
   
   Proof: This equals hom(K_{1,m}, G) by Prop 3.1. By classical result, hom(K_{1,m}, G) counts m-tuples of neighbors, which equals ∑ d_G(w)^m.

3. **Final Bound:**
   $$\text{hom}(K_{p,q}, G) \geq g(p) + g(q) - 2|E(G)| = \sum_{w} d_G(w)^p + d_G(w)^q - 2|E(G)|$$

4. **Equality Characterization:**
   - Equality occurs when all dropped terms (k,ℓ ≥ 2) vanish
   - Equivalent to N_{2,2}(G) = 0 (since all larger cliques contain K_{2,2})
   - N_{2,2}(G) = 0 ⟺ no 4-cycle ⟺ G is C₄-free

**Practical Implications:**
- **Trees:** Always C₄-free ⟹ formula is exact
- **General graphs:** Often provides good lower bound
- **Dense graphs:** As example (Remark 3.4), for K_{p,p} target with n vertices:
  - Exact: 2^{1-2p}n^{2p}
  - Lower bound: ≈ 2^{1-p}n^{p+1}
  - Ratio: 2^{-p}n^{p-1} → ∞ as n → ∞ (bound gets progressively weaker)

---

### Corollaries from Section 3

**Corollary 3.1:** For trees T:
$$\text{hom}(K_{p,q}, T) = \sum_{w \in V(T)} [d_T(w)^p + d_T(w)^q] - 2(|V(T)| - 1)$$
(Exact formula since trees are C₄-free)

**Corollary 3.2:** For general G with m edges:
$$\text{hom}(K_{p,q}, G) \geq 2^p n^{1-p}m^p + 2^q n^{1-q}m^q - 2m$$

with equality iff G is C₄-free and regular.

---

## Section 4: Entropy-Based Lower Bounds

### Background: Shannon Entropy (from Section 2)

For discrete random variable X with support [n]:
$$H(X) = -\sum_{i=1}^n P(X=i) \log P(X=i)$$

**Properties used:**
- H(X) ≤ log n (uniformity maximizes entropy)
- H(X,Y) = H(X) + H(Y|X) (chain rule)
- H(X_1,...,X_n) ≤ ∑ H(X_i) (subadditivity)

---

### Lemma 4.1: Probabilistic Construction

**Setup:**
- Let (U,V) be uniform over E(G), U ∈ left partition, V ∈ right partition
- P_U = marginal PMF of U
- P_{V|U} = conditional PMF of V given U

**Construction of (U^p, V^q):**

*Part (a):* V_j (j=1,...,q) are i.i.d. given U:
$$P_{V^q|U}(v|u) = \prod_{j=1}^q P_{V|U}(v_j|u)$$

*Part (b):* U_i (i=1,...,p) are i.i.d. given V^q:
$$P_{U_i|V^q}(u|v) = \frac{P_U(u) \prod_{j=1}^q P_{V|U}(v_j|u)}{\sum_{u' \in U} P_U(u') \prod_{j=1}^q P_{V|U}(v_j|u')}$$

**Lemma 4.1 Statement:**
Under this construction:
- (i) U_i ~ U for all i ∈ [p]
- (ii) (U_i, V^q) ~ (U, V^q) and (U_i, V_j) ~ (U,V) for all i,j

**Proof Sketch for (i):**
$$P_{U_i}(u) = \sum_v P_{U_i|V^q}(u|v) P_{V^q}(v)$$

By the denominator in construction and summation over all v, cancels to give P_U(u).

**Importance:** Allows us to apply entropy bounds with correct distributions.

---

### Lemma 4.2: Entropy Bounds on Joint Distributions

**Statement:**
$$H(U_1, V^q) \geq \log(\delta^q n_1 n_2^q)$$
$$H(U^p, V^q) \geq \log(\delta^{pq} n_1^p n_2^q)$$

**Proof of First Inequality:**

1. By chain rule and conditional independence:
   $$H(U_1, V^q) = H(U) + \sum_{j=1}^q H(V_j | U) = H(U) + q H(V|U)$$

2. H(U,V) = log|E(G)| = log(δn₁n₂) when (U,V) uniform over edges

3. Chain rule: H(U,V) = H(U) + H(V|U), so H(V|U) = H(U,V) - H(U) = log(δn₁n₂) - H(U)

4. Substitute:
   $$H(U_1, V^q) = H(U) + q[\log(\delta n_1 n_2) - H(U)]$$
   $$= H(U) + q\log(\delta n_1 n_2) - q H(U)$$
   $$= q\log(\delta n_1 n_2) - (q-1)H(U)$$

5. Use H(U) ≤ log n₁:
   $$H(U_1, V^q) \geq q\log(\delta n_1 n_2) - (q-1)\log n_1 = \log(\delta^q n_1 n_2^q)$$

**Proof of Second Inequality:** Similar chain rule application:
$$H(U^p, V^q) = H(V^q) + \sum_{i=1}^p H(U_i | V^q) = H(V^q) + p H(U|V^q)$$

By parallel argument with H(V^q) ≤ log(n₂^q):
$$H(U^p, V^q) \geq \log(\delta^{pq} n_1^p n_2^q)$$

---

### Proposition 4.1: First Entropy-Based Bound

**Formal Statement:**
Let G be bipartite with partite sets of sizes n₁, n₂ and edge density δ. Then for all p,q ∈ ℕ:
$$\text{hom}(K_{p,q}, G) \geq \delta^{pq}(n_1^p n_2^q + n_1^q n_2^p)$$

**Proof Steps:**

1. **Realization-to-Homomorphism Correspondence:**
   - Each realization (u,v) ∈ U^p × V^q defines a mapping φ: V(K_{p,q}) → V(G):
     - Vertex i of first partition → u_i
     - Vertex p+j of second partition → v_j
   - Since (U_i, V_j) ~ (U,V) (by Lemma 4.1), all edges {i, p+j} map to edges in G
   - ⟹ φ is a valid homomorphism

2. **Partition into Two Sets:**
   - H₁ = homomorphisms mapping K_{p,q}'s first partition → G's left partition (size n₁)
   - H₂ = homomorphisms mapping K_{p,q}'s first partition → G's right partition (size n₂)
   - Bipartition preservation: H₁ and H₂ partition Hom(K_{p,q}, G)

3. **Count H₁ via Entropy:**
   - Number of distinct realizations (u,v) → |H₁|
   - Uniform distribution on realizations: H(U^p, V^q) ≤ log|H₁|
   - By Lemma 4.2: log(δ^{pq} n₁^p n₂^q) ≤ H(U^p, V^q) ≤ log|H₁|
   - ⟹ |H₁| ≥ δ^{pq} n₁^p n₂^q

4. **Count H₂ by Symmetry:**
   - Interchange roles of partitions: |H₂| ≥ δ^{pq} n₁^q n₂^p

5. **Final Bound:**
   $$\text{hom}(K_{p,q}, G) = |H₁| + |H₂| \geq \delta^{pq}(n_1^p n_2^q + n_1^q n_2^p)$$

**Equality Cases:**
- δ = 0: G is edgeless, hom = 0 ✓
- δ = 1: G = K_{n₁,n₂}, bound is exact ✓

---

### Discussion 4.1: Comparison to Sidorenko's Bound

**Sidorenko's Conjecture** (for complete bipartite K_{p,q}):
Every bipartite graph is Sidorenko, meaning:
$$\text{hom}(K_{p,q}, G) \geq (2\delta)^{pq} (n_1 + n_2)^{p+q-2} (pq)^{pq} (n_1 n_2)^{pq}$$

**Our Entropy Bound:**
$$\text{LB}_2 = \delta^{pq}(n_1^p n_2^q + n_1^q n_2^p)$$

**Ratio Analysis:** LB₂/LB₁ (focusing on case p=q for simplicity)
$$\frac{\text{LB}_2}{\text{LB}_1} \geq 2^{p-1} \gg 1$$

**Key Result:** Our entropy bound improves Sidorenko by exponential factors
- For p=q: improvement ≥ 2^{p-1}
- For p>q: improvement ≥ 2^{pq-(p+q)} (grows exponentially with difference |p-q|)

This validates entropy-based approach superior to classical Sidorenko for K_{p,q} bounds.

---

### Proposition 4.2: Refined Entropy Bound (Degree-Aware)

**Setup:** Define degree entropies using normalized degree profiles:

For normalized degrees: d̄_k^{(U)} = d_k^{(U)}/|E(G)| and d̄_k^{(V)} = d_k^{(V)}/|E(G)|:

$$H(U) = \sum_{k=1}^{n_1} d̄_k^{(U)} \log \frac{|E(G)|}{d_k^{(U)}}$$

$$H(V) = \sum_{k=1}^{n_2} d̄_k^{(V)} \log \frac{|E(G)|}{d_k^{(V)}}$$

Define:
$$x = \sum_{k=1}^{n_1} \frac{d_k^{(U)}}{|E(G)|} \log \frac{|E(G)|}{d_k^{(U)}} = H(U)$$

$$y = \sum_{k=1}^{n_2} \frac{d_k^{(V)}}{|E(G)|} \log \frac{|E(G)|}{d_k^{(V)}} = H(V)$$

**Statement:** For all p,q ∈ ℕ:
$$\text{hom}(K_{p,q}, G) \geq \max\{(δn_1n_2)^{pq} \exp[-p(q-1)x - q(p-1)y],$$
$$(δn_1n_2)^q \exp[-(q-1)x], (δn_1n_2)^p \exp[-(p-1)y]\}$$
$$+ \max\{(δn_1n_2)^{pq} \exp[-q(p-1)x - p(q-1)y],$$
$$(δn_1n_2)^p \exp[-(p-1)x], (δn_1n_2)^q \exp[-(q-1)y]\}$$

**Key Insight:** Two maxes account for the two partite orientations H₁ and H₂.

**Proof Outline:**

1. **Degree-Aware Entropy:** Instead of H(U) ≤ log n₁, use the actual entropy from normalized degree distribution:
   $$H(U_1, V^q) = q\log(\delta n_1 n_2) - (q-1)H(U)$$
   
   where H(U) depends on degree concentration, not just n₁.

2. **Exploit Concentration:** If degrees are balanced, H(U) ≈ log n₁ (recovers Prop 4.1)
   
   If degrees very unbalanced, H(U) << log n₁ (tighter bound)

3. **Apply Max Principle:** Derive multiple lower bounds using chain rule variants:
   - Direct: H(U^p, V^q) ≥ pq log(...) - ... (full formula)
   - Simplified 1: Just use H(U) term → (δn₁n₂)^q exp[-(q-1)x]
   - Simplified 2: Just use H(V) term → (δn₁n₂)^p exp[-(p-1)y]
   
   Take max of all three (best lower bound).

4. **Symmetry for H₂:** Interchange p ↔ q and x ↔ y to get lower bounds for the other orientation.

5. **Final Bound:** Sum maxes from both orientations.

**When Does Refinement Help?**
- **Regular graphs:** H(U) = log n₁ = H(V) = log n₂ → reverts to Prop 4.1
- **Star-like:** One vertex has very high degree → small H → exponentially tighter bound
- **Skewed degree distribution:** Non-uniform → H significantly < log n → stronger bound

**Example:** For G = star graph (one center of degree n₁, all others degree 1):
- H(U) = (1/n₁) log(n₁) + ((n₁-1)/n₁) log(1/(n₁-1)) << log n₁
- Bound becomes exponentially tighter

---

## Comparison and Practical Use

| Property | Prop 3.1 | Prop 3.2 | Prop 4.1 | Prop 4.2 |
|----------|----------|----------|----------|----------|
| **Tightness** | Exact | Good (trees perfect) | Good | Best |
| **When exact** | Always (by definition) | C₄-free | Only extremes | Regular + special structure |
| **Computation** | O(n^{max(k,ℓ)}) clique search | O(n) degree sum | O(1) | O(n) entropy sum |
| **Input needed** | Full graph structure + bipartite cliques | Degree sequence | Sizes + edge density | Degree distributions |
| **Improvement over baseline** | None (exact formula) | x1-∞ range | Fixes Sidorenko | Exponential in non-regularity |

---

## Technical Lemmas (Detailed Proofs)

### Lemma 4.1(ii) Full Proof

**Claim:** (U_i, V^q) ~ (U, V^q) for all i ∈ [p]

**Proof:**
$$P_{U_i, V^q}(u,v) = P_{U_i|V^q}(u|v) P_{V^q}(v)$$

By construction:
$$P_{U_i|V^q}(u|v) = \frac{P_U(u) \prod_j P_{V|U}(v_j|u)}{\sum_{u'} P_U(u') \prod_j P_{V|U}(v_j|u')}$$

Thus:
$$P_{U_i,V^q}(u,v) = P_U(u) \prod_j P_{V|U}(v_j|u)$$

But by definition of conditional independence from (41):
$$P_{U,V^q}(u,v) = P_U(u) \prod_j P_{V|U}(v_j|u)$$

Therefore P_{U_i,V^q} = P_{U,V^q}. ✓

---

## Key Takeaways

1. **Stirling numbers** quantify partition structure—central to exact formula
2. **C₄-free condition** makes combinatorial bound exact—eliminates higher cliques
3. **Entropy framework** translates counting to probability—enables systematic lower bounds
4. **Degree profile** in entropy refinement captures graph non-regularity
5. **Progressive improvement:** Combinatorial (expensive, exact on special graphs) → Simple entropy (cheap, universal) → Refined entropy (best, still practical)
