import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from math import log2

x_pow2 = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576]
x_sf = [6, 10, 15, 20, 35, 63, 175, 270, 675, 945, 2205, 3696, 6615, 10206, 19845, 33075, 70875, 496125, 826875, 918750]
x_pr = [3, 5, 7, 13, 31, 61, 127, 229, 509, 1013, 2039, 4093, 8191, 16381, 32771, 65537,131071, 262139]

config = [('black', '.', '-'), ('black', '*', '--'), ('black', 'o', '-'), ('blue', '.', '-'), ('g', '.', '-'), ('magenta', '.', '-'),
    ('orange', '.', '-'), ('purple', 'o', '-'), ('goldenrod', '*', '-'), ('red', 'x', '-')]

def parse_file(in_file_name):
    in_file = open(in_file_name, "r")
    lines = in_file.readlines()
    indices = []
    results = []
    for s in lines:
        # format [n] [time]
        tokens = s.split()
        indices.append(int(tokens[0]))
        results.append(int(tokens[1]))
    return indices, results


def get_flop(y):
    for i in range(len(x_pow2)):
        if y[i] != 0:
            y[i] = x_pow2[i] * log2(x_pow2[i]) / y[i]


def garph(lst_data):
    x = [i for i in range(1, len(x_pow2)+1)]

    fig, ax = plt.subplots()
    # set the grid in graph
    plt.grid(linestyle='dashed', color='black') 

    plt.ylabel("speed(mflops)", fontsize=12)
    plt.xlabel("size", fontsize=12)

    counter = 0
    for name, y in lst_data:
        co = config[counter][0]
        ma = config[counter][1]
        li = config[counter][2]
        get_flop(y)
        ax.plot(x, y, color=co, label=name, marker=ma, linestyle=li, fillstyle='none')
        counter = counter + 1
    ax.legend()

    labels = [i for i in x_pow2]
    plt.xticks(x, labels, rotation='vertical')

    # plt.savefig("../fft_feature/amplitudes.pdf")
    plt.show()


def plot_summary_pow2():
    fftw_cpx = "../fft_results/pow2/fftw_cpx_frt.txt"
    ffts_cpx = "../fft_results/pow2/ffts_cpx_frt.txt"
    fftss_cpx = "../fft_results/pow2/fftss_cpx_frt.txt"
    ipp_cpx = "../fft_results/pow2/ipp_cpx_frt.txt"
    # ipp_real = "../fft_results/pow2/ipp_real_frt.txt"
    gsl_cpx = "../fft_results/pow2/gsl_cpx_frt.txt"
    pocket_cpx = "../fft_results/pow2/pocket_cpx_frt.txt"
    kfr_cpx = "../fft_results/pow2/kfr_cpx_frt.txt"
    mkl_cpx = "../fft_results/pow2/mkl_cpx_frt.txt"
    original_cpx = "../fft_results/pow2/original_cpx_frt.txt"

    lst_data = []

    lst_data.append(("FFTS", parse_file(ffts_cpx)[1]))
    lst_data.append(("FFTSS", parse_file(fftss_cpx)[1]))
    lst_data.append(("FFTW", parse_file(fftw_cpx)[1]))
    lst_data.append(("Intel-IPP", parse_file(ipp_cpx)[1]))
    # lst_data.append(("Intel-IPP real", parse_file(ipp_real)[1]))
    lst_data.append(("GSL mixed radix", parse_file(gsl_cpx)[1]))
    lst_data.append(("PocketFFT", parse_file(pocket_cpx)[1]))
    lst_data.append(("KFR", parse_file(kfr_cpx)[1]))
    lst_data.append(("Intel-MKL", parse_file(mkl_cpx)[1]))
    lst_data.append(("Original", parse_file(original_cpx)[1]))

    garph(lst_data)


def main():
    plot_summary_pow2()
    

if __name__ == '__main__':
    main()