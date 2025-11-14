import numpy as np
import pandas as pd
from sklearn.metrics import pairwise_distances
from skbio.stats.distance import DistanceMatrix, permanova
import scipy.stats  # ← ここだけでOK

def run_permanova_on_indices(X, groups, sel_idx, permutations=999):
    X_sub = X[sel_idx]
    groups_sub = groups[sel_idx]
    D = pairwise_distances(X_sub, metric='cosine', n_jobs=-1)
    dm = DistanceMatrix(D, ids=[str(i) for i in range(len(D))])
    res = permanova(dm, pd.DataFrame({'group': groups_sub}), column='group', permutations=permutations)
    return float(res['p-value'])

def repeated_sampling_test(X, groups, minor_group, major_group, n_reps=20, disjoint=False):
    rng = np.random.default_rng(0)
    minor_idx = np.where(groups == minor_group)[0]
    major_idx = np.where(groups == major_group)[0]

    p_vals = []

    if disjoint:
        max_blocks = len(major_idx) // len(minor_idx)
        if max_blocks < n_reps:
            raise ValueError(f"Cannot get {n_reps} disjoint blocks; max possible = {max_blocks}.")
        perm = rng.permutation(major_idx)
        for r in range(n_reps):
            block = perm[r*len(minor_idx):(r+1)*len(minor_idx)]
            sel_idx = np.concatenate([minor_idx, block])
            p = run_permanova_on_indices(X, groups, sel_idx)
            p_vals.append(p)
    else:
        for r in range(n_reps):
            sample_major_idx = rng.choice(major_idx, size=len(minor_idx), replace=False)
            sel_idx = np.concatenate([minor_idx, sample_major_idx])
            p = run_permanova_on_indices(X, groups, sel_idx)
            p_vals.append(p)

    p_vals = np.array(p_vals)

    # --- Fisher combine
    fisher_stat = -2 * np.sum(np.log(p_vals))
    fisher_p = 1 - scipy.stats.chi2.cdf(fisher_stat, df=2*len(p_vals))

    # --- proportion and binomial test
    alpha = 0.001
    m = np.sum(p_vals < alpha)
    prop = m / len(p_vals)
    
    # binomial test (SciPy >=1.11)
    binom_res = scipy.stats.binomtest(m, n=len(p_vals), p=alpha, alternative='greater')
    binom_p = binom_res.pvalue

    return {'p_vals': p_vals, 'fisher_p': fisher_p, 'prop': prop, 'binom_p': binom_p}

