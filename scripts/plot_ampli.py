import matplotlib
import matplotlib.pyplot as plt

def parse_file_ampli(in_file_name):
    in_file = open(in_file_name, "r")
    ampls = in_file.readlines()
    amplitudes = []
    for ampl in ampls:
        # one float on each line
        amplitudes.append(float(ampl.strip()))
    return len(amplitudes), amplitudes


def garph(n, data):
    y = data
    x = [i for i in range(n)]

    fig, ax = plt.subplots()

    # set the grid in graph
    plt.grid(linestyle='dashed', color='black') 

    plt.ylabel("Amplitude", fontsize=14)
    plt.xlabel("Index", fontsize=14)

    plt.plot(x, y, color='black')

    ax.axhline(55.38619, color='red')

    # plt.savefig("../fft_feature/amplitudes.pdf")
    plt.show()


def main():
    in_file_name = "../fft_results/amplitudes0.txt"
    n, amplitudes = parse_file_ampli(in_file_name)
    garph(n, amplitudes)


if __name__ == '__main__':
    main()