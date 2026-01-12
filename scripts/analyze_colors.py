import sys
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import os

def analyze_bmp(file_path):
    if not os.path.exists(file_path):
        print(f"Error: File {file_path} not found.")
        return

    try:
        img = Image.open(file_path)
    except Exception as e:
        print(f"Error opening image: {e}")
        return

    # Convert to numpy array
    data = np.array(img)
    
    # Calculate color histograms
    colors = ('red', 'green', 'blue')
    plt.figure(figsize=(10, 6))
    
    for i, color in enumerate(colors):
        histogram, bin_edges = np.histogram(data[:, :, i], bins=256, range=(0, 256))
        plt.plot(bin_edges[0:-1], histogram, color=color, label=color)

    plt.title(f"Color Distribution: {os.path.basename(file_path)}")
    plt.xlabel("Color Value")
    plt.ylabel("Pixel Count")
    plt.legend()
    plt.grid(True, alpha=0.3)
    
    output_plot = "color_analysis.png"
    plt.savefig(output_plot)
    print(f"Analysis saved to {output_plot}")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python analyze_colors.py <bmp_file>")
    else:
        analyze_bmp(sys.argv[1])
