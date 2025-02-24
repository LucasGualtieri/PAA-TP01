import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import sys

def read_csv(file_path):
    """Reads the CSV file and returns a DataFrame."""
    return pd.read_csv(file_path)

def plot_runtime_vs_vertices(df):
    """Plots Runtime vs. Number of Vertices for each algorithm."""
    plt.figure(figsize=(8, 6))
    for algorithm in df['algorithm'].unique():
        subset = df[df['algorithm'] == algorithm]
        plt.plot(subset['vertices'], subset['time'], marker='o', label=algorithm)
    
    plt.xlabel('Number of Vertices')
    plt.ylabel('Time (s)')
    plt.title('Runtime vs. Number of Vertices')
    plt.legend()
    plt.grid()
    plt.savefig('runtime_vs_vertices.png')
    plt.close()

def plot_runtime_vs_density(df):
    """Plots Runtime vs. Density for each algorithm."""
    plt.figure(figsize=(8, 6))
    for algorithm in df['algorithm'].unique():
        subset = df[df['algorithm'] == algorithm]
        plt.plot(subset['density'], subset['time'], marker='o', label=algorithm)
    
    plt.xlabel('Graph Density')
    plt.ylabel('Time (s)')
    plt.title('Runtime vs. Density')
    plt.legend()
    plt.grid()
    plt.savefig('runtime_vs_density.png')
    plt.close()

def plot_heatmap(df):
    """Creates a heatmap of time based on vertices and density."""
    df_avg = df.select_dtypes(include='number').groupby(['density', 'vertices'], as_index=False).mean()
    pivot_table = df_avg.pivot(index='density', columns='vertices', values='time')
    
    plt.figure(figsize=(8, 6))
    sns.heatmap(pivot_table, cmap='viridis', annot=True, fmt='.3f')
    plt.xlabel('Number of Vertices')
    plt.ylabel('Graph Density')
    plt.title('Heatmap of Runtime')
    plt.savefig('heatmap.png')
    plt.close()

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 Graphic.py <csv_file>")
        sys.exit(1)
    
    file_path = sys.argv[1]
    df = read_csv(file_path)
    plot_runtime_vs_vertices(df)
    plot_runtime_vs_density(df)
    plot_heatmap(df)
    print("Graphs saved as PNG files.")

if __name__ == '__main__':
    main()
