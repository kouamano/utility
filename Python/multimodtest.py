import numpy as np
from scipy.stats import gaussian_kde
from scipy.signal import find_peaks
from sklearn.mixture import GaussianMixture
import argparse

def estimate_modes_gmm(data, max_components=10):
    data_2d = data.reshape(-1,1)
    models = [GaussianMixture(n_components=i).fit(data_2d) for i in range(1, max_components+1)]
    bics = [m.bic(data_2d) for m in models]
    best_model = models[np.argmin(bics)]
    return best_model.n_components

def estimate_modes_kde(data, bw_method=0.3):
    kde = gaussian_kde(data, bw_method=bw_method)
    x = np.linspace(min(data), max(data), 1000)
    y = kde(x)
    peaks, _ = find_peaks(y)
    return len(peaks)

def main():
    parser = argparse.ArgumentParser(description="ピーク数推定プログラム (GMM & KDE)")
    parser.add_argument("-f", "--file", required=True, help="入力データファイル (1列の数値)")
    parser.add_argument("-mc", "--max_components", type=int, default=10, help="GMM探索の最大成分数 (デフォルト: 10)")
    parser.add_argument("-bw", "--bandwidth", type=float, default=0.3, help="KDEの平滑化パラメータ bw_method (デフォルト: 0.3)")
    args = parser.parse_args()

    # データ読み込み
    data = np.loadtxt(args.file,delimiter=',')
    data = np.asarray(data)

    # GMM
    gmm_modes = estimate_modes_gmm(data, max_components=args.max_components)

    # KDE
    kde_modes = estimate_modes_kde(data, bw_method=args.bandwidth)

    # 結果表示
    print("=== 分布のピーク数推定 ===")
    print(f"入力ファイル: {args.file}")
    print(f"GMMによる推定モード数: {gmm_modes}")
    print(f"KDEによる推定モード数 (bw={args.bandwidth}): {kde_modes}")

if __name__ == "__main__":
    main()
