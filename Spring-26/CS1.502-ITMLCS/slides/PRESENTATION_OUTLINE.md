# Technical Presentation: Graph Homomorphism Bounds
## Sections 3 & 4 – 20 Minutes

---

## I. Introduction & Context (2 min)

**Setting:** Bipartite source graph K_{p,q} → bipartite target graph G
- **Goal:** Bound the number of valid homomorphisms hom(K_{p,q}, G)
- **Challenge:** Direct enumeration is computationally expensive
- **Approach:** Two complementary techniques
  - Combinatorial bounds (Section 3)
  - Entropy-based bounds (Section 4)

---

## II. Section 3: Combinatorial Bounds (7 min)

### **Proposition 3.1: Exact Formula**

**Statement:**
$$\text{hom}(K_{p,q}, G) = \sum_{k=1}^p \sum_{\ell=1}^q k!\ell! S(p,k)S(q,\ell)[N_{k,\ell}(G) + N_{\ell,k}(G)]$$

**Intuition:** 
- Every homomorphism maps K_{p,q} to a complete bipartite subgraph (bipartite clique) in G
- The formula counts all ways to:
  1. Partition p vertices into k groups (using Stirling numbers S(p,k))
  2. Partition q vertices into ℓ groups
  3. Match these to a bipartite clique of size k×ℓ in G

**Key Insight:** Homomorphisms preserve bipartition structure
- All vertices from one partition of K_{p,q} map into the same partition of G
- This forces the image to form a complete bipartite subgraph

**Computational Reality:** Even exact formulas are expensive—need O(n^k) bipartite clique counts

---

### **Proposition 3.2: Combinatorial Lower Bound**

**Statement:**
$$\text{hom}(K_{p,q}, G) \geq \sum_{w \in V(G)} [d_G(w)^p + d_G(w)^q] - 2|E(G)|$$

**Equality Condition:** Holds with equality iff G is C₄-free (no 4-cycles)

**Intuition:**
- Focus only on "star-like" homomorphisms: map vertices to single edges
- Ignore complex structures (complete bipartite subgraphs with k,ℓ ≥ 2)
- The degree term captures stars: for each vertex w of degree d, there are d^p homomorphisms using w

**Why C₄-free matters:**
- K₂,₂ is a 4-cycle
- Absence of K₂,₂ means the "discarded" terms are zero
- Lower bound becomes exact for trees, paths, etc.

**Proof Technique:**
1. Start from Proposition 3.1
2. Drop all terms with k,ℓ ≥ 2 (they're non-negative)
3. Relate remaining sum to star graph homomorphisms via degree powers
4. Equality analysis shows C₄-freeness is necessary and sufficient

---

## III. Section 4: Entropy-Based Bounds (9 min)

### **Lemma 4.1 & 4.2: Probabilistic Framework**

**Setup:**
- Sample random edges uniformly from E(G)
- Get random vector (U,V) where U ∈ {left partition}, V ∈ {right partition}
- Construct (U^p, V^q) by independent i.i.d. copies, with clever conditioning

**Lemma 4.1 Key Properties:**
- U_i ~ U (marginal distribution preserved)
- (U_i, V_j) ~ (U,V) (joint distribution recovered)
- Allows entropy calculations on independent copies

**Lemma 4.2 Result:**
$$H(U_1, V^q) \geq \log(\delta^q n_1 n_2^q)$$

**Proof Idea:**
- Joint entropy chains as: H(U,V^q) = H(U) + qH(V|U)
- Each sample of V given U contributes H(V|U) = H(U,V) - H(U) = log(δn₁n₂) - H(U)
- Bound H(U) ≤ log n₁ universally
- Result: lower bound on entropy in terms of δ (edge density)

---

### **Proposition 4.1: First Entropy-Based Bound**

**Statement:**
$$\text{hom}(K_{p,q}, G) \geq \delta^{pq}(n_1^p n_2^q + n_1^q n_2^p) = \delta^{pq} \text{hom}(K_{p,q}, K_{n_1,n_2})$$

**Intuition:**
- A homomorphism corresponds to a realization (u,v) ∈ U^p × V^q of random vectors
- Each edge mapping must hit an actual edge in G
- Probability that all pq edge mappings hit edges ≥ δ^{pq}
- This probability directly bounds the counting problem

**Connection to Sidorenko's Conjecture:**
- Sidorenko bound: δ^{pq}(n₁+n₂)^{p+q-2} (pq)^{pq}(n₁n₂)^{pq}
- Our entropy bound improves Sidorenko by factors ≥ 2^{|p-q|} (Discussion 4.1)
- Tighter because entropy exploits structure more efficiently

**Why It Works:**
1. Valid homomorphisms form a measurable set
2. Upper bound entropy with uniform distribution bound
3. Correspondence is injective (one realization ↔ one homomorphism)

---

### **Proposition 4.2: Refined Entropy Bound**

**Statement:** (Degree-aware refinement)
$$\text{hom}(K_{p,q}, G) \geq \max\{\ldots\} + \max\{\ldots\}$$

where each max involves terms like:
$$(δn_1 n_2)^{pq} \exp[-p(q-1)H(U) - q(p-1)H(V)]$$

**Key Definitions:**
- H(U) = entropy of normalized degree profile in left partition
- H(V) = entropy of normalized degree profile in right partition
- δn₁n₂ = |E(G)|

**Intuition:**
- **The refinement:** Use actual degree entropy instead of uniform upper bounds
- Regular graphs (all vertices same degree) have H=log n, recovering Prop 4.1
- Non-regular graphs with concentrated degrees: entropy smaller → tighter bounds
- Max over multiple terms captures two "orientations" of the homomorphism

**Why Two Maxes in Final Formula:**
- First max: homomorphisms with K_{p,q} partite sets → G's (n₁,n₂) partite sets
- Second max: homomorphisms with K_{p,q} partite sets → G's (n₂,n₁) partite sets
- Two disjoint subsets partition all homomorphisms

**Proof Strategy:**
1. Replace uniform entropy bounds with actual degree entropy calculations
2. Use H(U,V^q) = qlog(δn₁n₂) - (q-1)H(U) with degree-aware H(U)
3. Chain rules for H(U^p,V^q) to get entropy bounds on both homomorphism sets
4. Convert entropy bounds to cardinality bounds via uniform distribution property
5. Take max over all derived lower bounds

---

## IV. Comparison & Key Takeaways (2 min)

| Aspect | Prop 3.2 | Prop 4.1 | Prop 4.2 |
|--------|----------|----------|----------|
| **When exact** | C₄-free | Never | Regular + C₄-free |
| **Speed** | O(n) | O(1) | O(n) |
| **Dependence** | Full structure | δ only | δ + degree profile |
| **Tightness** | Excellent on trees | Good on dense | Best overall |

**Key Insights:**
1. **Combinatorial bounds** require knowing structure (bipartite cliques)
2. **Simple entropy bound** uses only density—universally applicable
3. **Refined entropy bound** incorporates degree distribution for tighter results
4. **Trade-off:** More information → tighter bounds, but higher computational cost

---

## Notes for Delivery

- **Lemmas 4.1–4.2 are technical foundations**: Spend ~1 min on intuition, don't dwell on details
- **Proposition 4.2 complexity**: Emphasize "uses degree info" rather than parsing all max terms
- **Visual aid suggestion**: Show a K₃,₃ → random bipartite G example, compute all three bounds
- **Key punchline**: Entropy-based methods give provably better bounds than classical combinatorics for this problem
