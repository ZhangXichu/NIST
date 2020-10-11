from math import log2, ceil
import matplotlib
import matplotlib.pyplot as plt


x_pr = [3, 5, 7, 13, 31, 61, 127, 229, 509, 1013, 2039, 4093, 8191, 16381, 32771, 65537,131071, 262139, 524287, 1048573, 
    2097143, 4194301, 8388593, 16777213, 33554393, 67108837]
x_sf = [6, 10, 15, 20, 35, 63, 175, 270, 675, 945, 2205, 3696, 6615, 10206, 19845, 33075, 70875, 496125, 826875, 918750,
     1929375, 3858750, 8575000, 16206750, 31513125, 63530460]

def next_pow2(n):
    pr = ceil(log2(n))
    return 2**pr


def diff(arr):
    diffs = []
    for x in arr:
        N = 2 * x - 1
        next = next_pow2(N)
        diffs.append(next - N)
        print("n: ", x, "next pow of 2 of n*2-1: ", next, "difference: ", next - N)
    return diffs


def graph(name, arr):
    y = diff(arr)

    print(y)

    fig, ax = plt.subplots()

    # set the grid in graph
    plt.grid(linestyle='dashed', color='black') 

    plt.ylabel("Distance", fontsize=12)
    plt.xlabel("Index", fontsize=12)

    x = [i for i in range(1, len(arr)+1)]
    labels = [i for i in arr]

    ax.plot(x, y, color='black', marker='*')

    plt.xticks(x, labels, rotation='vertical')

    # ax.axhline(55.38619, color='red')

    plt.savefig(name, bbox_inches='tight')
    plt.show()


def main():
    name = "next_primes_sm.pdf"
    graph(name, x_sf)


if __name__ == "__main__":
    main()