import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# Load the CSV
df = pd.read_csv("hashattack_results.csv")

sns.set_theme(style="whitegrid")

def plot_attack(attack_type, theory_func, filename):
    data = df[df["type"] == attack_type]

    plt.figure(figsize=(10,6))

    # Box plot showing distribution (variance)
    sns.boxplot(
        data=data,
        x="bits",
        y="iterations",
        color="lightblue"
    )

    # Mean values
    means = data.groupby("bits")["iterations"].mean()

    plt.plot(
        range(len(means)),
        means.values,
        marker='o',
        linewidth=2,
        label="Experimental Mean",
        color="blue"
    )

    bits = means.index.values

    theoretical = [theory_func(b) for b in bits]

    plt.plot(
        range(len(bits)),
        theoretical,
        marker='s',
        linestyle='--',
        linewidth=2,
        label="Theoretical",
        color="red"
    )

    plt.xticks(range(len(bits)), bits)

    plt.yscale("log")

    plt.xlabel("Hash Size (bits)")
    plt.ylabel("Iterations (log scale)")
    plt.title(f"{attack_type.capitalize()} Attack")
    plt.legend()

    plt.tight_layout()
    plt.savefig(filename, dpi=300)
    plt.show()


plot_attack(
    "collision",
    lambda n: 2**(n/2),
    "collision_plot.png"
)

plot_attack(
    "preimage",
    lambda n: 2**n,
    "preimage_plot.png"
)