import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from math import log2


# test data
x_pow2 = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,
     2097152, 4194304, 8388608, 16777216, 33554432, 67108864]
x_sf = [6, 10, 15, 20, 35, 63, 140, 270, 567, 945, 2205, 3969, 8505, 15309, 31752, 60025, 127575, 275625, 551250, 1071875,
     1929375, 3858750, 8575000, 16206750, 31513125, 63530460]
x_pr = [3, 5, 7, 13, 31, 61, 127, 229, 509, 1013, 2039, 4093, 8191, 16381, 32771, 65537,131071, 262139, 524287, 1048573, 
    2097143, 4194301, 8388593, 16777213, 33554393, 67108837]

config_a = [('brown', '.', '-'), ('blue', '.', '-'), ('darkgreen', '.', '-'), ('cyan', '.', '-'), ('magenta', '.', '-'),
    ('midnightblue', '.', '-'), ('purple', '.', '-'), ('dimgrey', '.', '--'), ('black', '*', '--')]

config_fftw_mt = [('black', '.', '-'), ('black', 'o', '--'), ('black', '+', ':'), ('dimgrey', '1', '-.')]

config_e = [('blue', '.', '-'), ('magenta', '.', '-'), ('black', '.', '-'), ('magenta', '*', '--'), ('black', '*', '--')]

config_param = [('blue', '.', '-'), ('blue', 'o', '--'), ('blue', '*', '-.'), ('magenta', '.', '-'), ('magenta', '*', '--'), ('black', '.', '-'), ('black', '*', '--')]

def parse_file(in_file_name):
    in_file = open(in_file_name, "r")
    lines = in_file.readlines()
    indices = []
    results = []
    num_values = 0
    for s in lines:
        # format [n] [time]
        tokens = s.split()
        indices.append(int(tokens[0]))
        results.append(int(tokens[1]))
        num_values += 1
    return indices, results, num_values


def get_flop(y, cpx, x_labels, num_values):
    if cpx:
        k = 5
    else:
        k = 2.5
    for i in range(num_values):
        if y[i] != 0:
            y[i] = k * x_labels[i] * log2(x_labels[i]) / y[i]


def graph(lst_data, cpx=True, config=config_a, name_f="", type="pow2", extended=False, whole=False):

    print(config)

    if type == "pow2":
        x_labels = x_pow2
    elif type == "small_factor":
        x_labels = x_sf
    else:  # prime
        x_labels = x_pr

    counter = 0
    num_values = len(x_labels)

    fig, ax = plt.subplots()
    fig.tight_layout()
    # set the grid in graph
    plt.grid(linestyle='dashed', color='black') 

    plt.ylabel("speed(mflops)", fontsize=12)
    plt.xlabel("size", fontsize=12)

    for name, y, num_values in lst_data:
        x = [i for i in range(1, num_values+1)]
        co = config[counter][0]
        ma = config[counter][1]
        li = config[counter][2]
        if name == "KFR":
            co = "dimgrey"
            ma = '.'
            li = '--'
        if name == "FFTW":
            co = 'black'
            ma = '.'
            li = '-'
        if name == "FFTS":
            co = 'black'
            ma = '*'
            li = '--'
        get_flop(y, cpx, x_labels, num_values)
        ax.plot(x, y, color=co, label=name, marker=ma, linestyle=li, fillstyle='none')
        counter = counter + 1
    ax.legend()

    labels = [i for i in x_labels]
    plt.xticks(x, labels, rotation='vertical')

    plt.savefig("../fft_results/plots/" + name_f, bbox_inches='tight')
    plt.show()


def plot_summary(type="pow2", cpx=True):
    if cpx:
        tr = "cpx"
    else:
        tr = "real"

    lst_data = []

    fftw = "../fft_results/{0}/fftw_{1}_est_frt.txt".format(type, tr)
    ffts = "../fft_results/{0}/ffts_{1}_frt.txt".format(type, tr)
    fftss = "../fft_results/{0}/fftss_{1}_frt.txt".format(type, tr)
    ipp = "../fft_results/{0}/ipp_{1}_none_frt.txt".format(type, tr)
    gsl = "../fft_results/{0}/gsl_{1}_frt.txt".format(type, tr)
    pocket = "../fft_results/{0}/pocket_{1}_frt.txt".format(type, tr)
    kfr = "../fft_results/{0}/kfr_{1}_frt.txt".format(type, tr)
    mkl = "../fft_results/{0}/mkl_{1}_allow_frt.txt".format(type, tr)
    original = "../fft_results/{0}/original_frt.txt".format(type)

    res_original = parse_file(original)
    lst_data.append(("Original", res_original[1], res_original[2]))
    res_ipp = parse_file(ipp)
    lst_data.append(("Intel-IPP", res_ipp[1], res_ipp[2]))
    res_gsl = parse_file(gsl)
    lst_data.append(("GSL mixed radix", res_gsl[1], res_gsl[2]))
    res_pocket = parse_file(pocket)
    lst_data.append(("PocketFFT", res_pocket[1], res_pocket[2]))
    res_mkl = parse_file(mkl)
    lst_data.append(("Intel-MKL", res_mkl[1], res_mkl[2]))

    if cpx:
        res_ffts = parse_file(ffts)
        lst_data.append(("FFTS", res_ffts[1], res_ffts[2]))

    if type == "pow2":
        if cpx:
            res_fftss = parse_file(fftss)
            lst_data.append(("FFTSS", res_fftss[1], res_fftss[2]))
        res_kfr = parse_file(kfr)
        lst_data.append(("KFR", res_kfr[1], res_kfr[2]))

    if type == "prime":
        if cpx:
            res_kfr = parse_file(kfr)
            lst_data.append(("KFR", res_kfr[1], res_kfr[2]))

    res_fftw = parse_file(fftw)
    lst_data.append(("FFTW", res_fftw[1], res_fftw[2]))
    
    graph(lst_data, name_f="summary_{0}_{1}.pdf".format(tr, type), type=type)


def plot_summary_cpx_pow2():
    plot_summary()


def plot_summary_cpx_small_factor():
    plot_summary(type="small_factor")


def plot_summary_cpx_prime():
    plot_summary(type="prime")


def plot_summary_real_pow2():
    plot_summary(cpx=False)


def plot_summary_real_small_factor():
    plot_summary(type="small_factor", cpx=False)


def plot_summary_real_prime():
    plot_summary(type="prime", cpx=False)


def plot_fftw_mt(factor="", type="pow2", cpx=True):
    if cpx:
        tr = "cpx"
    else:
        tr = "real"

    fftw_cpx = "../fft_results/{0}/fftw_{1}_est_frt.txt".format(factor, tr)
    fftw_mt_2_cpx = "../fft_results/{0}/fftw_mt_2_{1}_frt.txt".format(factor, tr)
    fftw_mt_4_cpx = "../fft_results/{0}/fftw_mt_4_{1}_frt.txt".format(factor, tr)
    fftw_mt_6_cpx = "../fft_results/{0}/fftw_mt_6_{1}_frt.txt".format(factor, tr)

    lst_data = []
    
    res_fftw_cpx = parse_file(fftw_cpx)
    lst_data.append(("1 thread", res_fftw_cpx[1], res_fftw_cpx[2]))
    res_fftw_mt_2_cpx = parse_file(fftw_mt_2_cpx)
    lst_data.append(("2 threads", res_fftw_mt_2_cpx[1], res_fftw_mt_2_cpx[2]))
    res_fftw_mt_4_cpx = parse_file(fftw_mt_4_cpx)
    lst_data.append(("4 threads", res_fftw_mt_4_cpx[1], res_fftw_mt_4_cpx[2]))
    res_fftw_mt_6_cpx = parse_file(fftw_mt_6_cpx)
    lst_data.append(("6 threads", res_fftw_mt_6_cpx[1], res_fftw_mt_6_cpx[2]))


    graph(lst_data, config=config_fftw_mt, name_f="{0}/plot_fftw_mt_{1}.pdf".format(factor, tr), type=type, whole=True)


def plot_fftw_mt_cpx_pow2():
    plot_fftw_mt("pow2", type="pow2")


def plot_fftw_mt_cpx_small_factor():
    plot_fftw_mt("small_factor", type="small_factor")


def plot_fftw_mt_cpx_prime():
    plot_fftw_mt("prime", type="prime")


def plot_fftw_mt_real_pow2():
    plot_fftw_mt("pow2", type="pow2", cpx=False)


def plot_fftw_mt_real_small_factor():
    plot_fftw_mt("small_factor", type="small_factor", cpx=False)


def plot_fftw_mt_real_prime():
    plot_fftw_mt("prime", type="prime", cpx=False)


def plot_placement(type="pow2", cpx=True):
    if cpx:
        tr = "cpx"
    else:
        tr = "real"

    lst_data = []

    # out-of-place
    ipp = "../fft_results/{0}/ipp_{1}_fast_frt.txt".format(type, tr)
    mkl = "../fft_results/{0}/mkl_{1}_allow_frt.txt".format(type, tr)
    fftw = "../fft_results/{0}/fftw_{1}_est_frt.txt".format(type, tr)

    res_ipp = parse_file(ipp)
    lst_data.append(("Intel-IPP", res_ipp[1], res_ipp[2]))
    res_mkl = parse_file(mkl)
    lst_data.append(("Intel-MKL", res_mkl[1], res_mkl[2]))
    res_fftw = parse_file(fftw)
    lst_data.append(("FFTW", res_fftw[1], res_fftw[2]))

    # in-place
    mkl_i = "../fft_results/{0}/mkl_{1}_in_frt.txt".format(type, tr)
    fftw_i = "../fft_results/{0}/fftw_{1}_in_frt.txt".format(type, tr)

    res_mkl_i = parse_file(mkl_i)
    lst_data.append(("Intel-MKL in-place", res_mkl_i[1], res_mkl_i[2]))
    res_fftw_i = parse_file(fftw_i)
    lst_data.append(("FFTW in-place", res_fftw_i[1], res_fftw_i[2]))

    graph(lst_data, config=config_e, name_f="{1}/{0}_{1}_placement.pdf".format(tr, type), type=type, whole=True)


def plot_placement_cpx_pow2():
    plot_placement()


def plot_placement_cpx_small_factor():
    plot_placement(type="small_factor")


def plot_placement_cpx_prime():
    plot_placement(type="prime")


def plot_placement_real_pow2():
    plot_placement(cpx=False)


def plot_placement_real_small_factor():
    plot_placement(cpx=False, type="small_factor")


def plot_placement_real_prime():
    plot_placement(cpx=False, type="prime")


# IPP, MKL, FFTW with different params
def plot_params(type="pow2", cpx=True):
    if cpx:
        tr = "cpx"
    else:
        tr = "real"

    lst_data = []

    ipp_none = "../fft_results/{0}/ipp_{1}_none_frt.txt".format(type, tr)
    ipp_fast = "../fft_results/{0}/ipp_{1}_fast_frt.txt".format(type, tr)
    ipp_accurate = "../fft_results/{0}/ipp_{1}_accurate_frt.txt".format(type, tr)

    mkl_allow = "../fft_results/{0}/mkl_{1}_allow_frt.txt".format(type, tr)
    mkl_avoid = "../fft_results/{0}/mkl_{1}_avoid_frt.txt".format(type, tr)

    fftw_estimate = "../fft_results/{0}/fftw_{1}_est_frt.txt".format(type, tr)

    res_ipp_none = parse_file(ipp_none)
    lst_data.append(("IPP-none", res_ipp_none[1], res_ipp_none[2]))

    res_ipp_fast = parse_file(ipp_fast)
    lst_data.append(("IPP-fast", res_ipp_fast[1], res_ipp_fast[2]))

    res_ipp_accurate = parse_file(ipp_accurate)
    lst_data.append(("IPP-accurate", res_ipp_accurate[1], res_ipp_accurate[2]))

    res_mkl_allow = parse_file(mkl_allow)
    lst_data.append(("MKL-allow", res_mkl_allow[1], res_mkl_allow[2]))

    res_mkl_avoid = parse_file(mkl_avoid)
    lst_data.append(("MKL-avoid", res_mkl_avoid[1], res_mkl_avoid[2]))

    res_fftw_estimate = parse_file(fftw_estimate)
    lst_data.append(("FFTW-estimate", res_fftw_estimate[1], res_fftw_estimate[2]))
    
    # with param MEASURE, only plot case pow2 (cpx and real)
    if type == "pow2":
            fftw_measure = "../fft_results/{0}/fftw_{1}_mea_frt.txt".format(type, tr)
            res_fftw_measure = parse_file(fftw_measure)
            lst_data.append(("FFTW-measure", res_fftw_measure[1], res_fftw_measure[2]))

    graph(lst_data, config=config_param, name_f="{1}/{0}_{1}_params.pdf".format(tr, type), type=type, whole=True)


def plot_params_cpx_pow2():
    plot_params()


def plot_params_cpx_small_factor():
    plot_params(type="small_factor")


def plot_params_cpx_prime():
    plot_params(type="prime")


def plot_params_real_pow2():
    plot_params(cpx=False)


def plot_params_real_small_factor():
    plot_params(type="small_factor", cpx=False)


def plot_params_real_prime():
    plot_params(type="prime", cpx=False)




def main():
    ##################################
    #### Summary #####################
    ##################################

    plot_summary_cpx_pow2()
    plot_summary_cpx_small_factor()
    plot_summary_cpx_prime()

    plot_summary_real_pow2()
    plot_summary_real_small_factor()
    plot_summary_real_prime()

    ##################################
    #### FFTW multi thread version ###
    ##################################

    # plot_fftw_mt_cpx_pow2()
    # plot_fftw_mt_cpx_small_factor()
    # plot_fftw_mt_cpx_prime()

    # plot_fftw_mt_real_pow2()
    # plot_fftw_mt_real_small_factor()
    # plot_fftw_mt_real_prime()

    ##################################
    ##########  Placement  ###########
    ##################################

    # plot_placement_cpx_pow2()
    # plot_placement_cpx_small_factor()
    # plot_placement_cpx_prime()

    # plot_placement_real_pow2()
    # plot_placement_real_small_factor()
    # plot_placement_real_prime()

    ##################################
    #####  Different params  #########
    ##################################

    # plot_params_cpx_pow2()
    # plot_params_cpx_small_factor()
    # plot_params_cpx_prime()

    # plot_params_real_pow2()
    # plot_params_real_small_factor()
    # plot_params_real_prime()


if __name__ == '__main__':
    main()