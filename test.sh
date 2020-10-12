#!/bin/bash
source env.sh
root=`dirname "$0"`
function run () {
    cd "$root"
    macro="$1"
    int="$2"
    filename="$3"
    make clean
    make "MACRO=$macro"
    $root/assess "$int" "$filename"
}


function kfr() {
    p_value="$1"
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformKFR" 2 'pow2/kfr_cpx_frt.txt'  # ok
    # [not support n>10] run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformKFR" 2 'small_factor/kfr_cpx_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformKFR" 2 'prime/kfr_cpx_frt.txt' # ok

    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformKFRr -DINIT=1" 2 'pow2/kfr_real_frt.txt' # ok (not support n = 2)
    # [not support] run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformKFR" 2 'small_factor/kfr_cpx_frt.txt'
    # [not support] run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformKFRr -DINIT=1" 2 'prime/kfr_real_frt.txt' 
}

function test_kfr() {
    kfr
}

function verify_kfr() {
    kfr "-DP_VALUE"
}

function fftss() {
    p_value="$1"
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTSS" 0 'pow2/fftss_cpx_frt.txt' # ok
}

function test_fftss() {
    fftss
}

function verify_fftss() {
    fftss "-DP_VALUE"
}

function original() {
    p_value="$1"
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransform" 0 'pow2/original_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransform" 0 'small_factor/original_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransform" 8 'prime/original_frt.txt' # very slow
}

function test_original() {
    original
}

function verify_original() {
    original "-DP_VALUE"
}

function ffts() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTS" 0 'pow2/ffts_cpx_frt.txt' # ok
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTS" 0 'small_factor/ffts_cpx_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTS" 0 'prime/ffts_cpx_frt.txt' # ok

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTSr -INIT=2" 0 'pow2/ffts_real_frt.txt' 
    # [doesn't support] run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTSr" 0 'small_factor/ffts_real_frt.txt'
    # [doesn't support] run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTSr" 0 'prime/ffts_real_frt.txt'
}

function test_ffts() {
    ffts
}

function verify_ffts() {
    ffts "-DP_VALUE"
}


function gsl() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformGSL" 0 'pow2/gsl_cpx_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformGSL" 0 'small_factor/gsl_cpx_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformGSL" 8 'prime/gsl_cpx_frt.txt' # very slow

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformGSLr" 0 'pow2/gsl_real_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformGSLr" 0 'small_factor/gsl_real_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformGSLr" 8 'prime/gsl_real_frt.txt' # very slow
}

function test_gsl() {
    gsl
}

function verify_gsl() {
    gsl "-DP_VALUE"
}


function pocket() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformPocket" 0 'pow2/pocket_cpx_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformPocket" 0 'small_factor/pocket_cpx_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformPocket" 8 'prime/pocket_cpx_frt.txt'

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformPocketr" 0 'pow2/pocket_real_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformPocketr" 0 'small_factor/pocket_real_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformPocketr" 8 'prime/pocket_real_frt.txt'
}

function test_pocket() {
    pocket
}

function verify_pocket() {
    pocket "-DP_VALUE"
}


# IPP - algirthm hint
function ipp_algorithm_hint() {
    p_value="$1"
    param="$2"
    name="$3"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformIPP $param" 0 "pow2/ipp_cpx_${name}_frt.txt"
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformIPP $param" 0 "small_factor/ipp_cpx_${name}_frt.txt"
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformIPP $param" 0 "prime/ipp_cpx_${name}_frt.txt"

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformIPPr $param" 0 "pow2/ipp_real_${name}_frt.txt"
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformIPPr $param" 2 "small_factor/ipp_real_${name}_frt.txt"
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformIPPr $param" 2 "prime/ipp_real_${name}_frt.txt"
}

#IPP - none 
function test_ipp_none(){
    ipp_algorithm_hint "" "" "none"
}

function verify_ipp_none(){
    ipp_algorithm_hint "-DP_VALUE" "" "none"
}

#IPP - none 
function test_ipp_fast(){
    ipp_algorithm_hint "" "-DFAST" "fast"
}

function verify_ipp_fast() {
    ipp_algorithm_hint "-DP_VALUE" "-DFAST" "fast"
}

#IPP - none 
function test_ipp_accurate(){
    ipp_algorithm_hint "" "-DACCURATE" "accurate"
}

function verify_ipp_accurate() {
    ipp_algorithm_hint "-DP_VALUE" "-DACCURATE" "accurate"
}

# MKL - avoid using additional workspace
function mkl_avoid() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID" 0 'pow2/mkl_cpx_avoid_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID" 0 'small_factor/mkl_cpx_avoid_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID" 0 'prime/mkl_cpx_avoid_frt.txt'

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID" 0 'pow2/mkl_real_avoid_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID" 2 'small_factor/mkl_real_avoid_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID" 2 'prime/mkl_real_avoid_frt.txt'
}

function test_mkl_avoid() {
    mkl_avoid 
}

function verify_mkl_avoid() {
    mkl_avoid "-DP_VALUE"
}

# allow using additional workspace (default) / out-of-place
function mkl_allow() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL" 0 'pow2/mkl_cpx_allow_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL" 0 'small_factor/mkl_cpx_allow_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL" 0 'prime/mkl_cpx_allow_frt.txt'

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr" 0 'pow2/mkl_real_allow_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr" 0 'small_factor/mkl_real_allow_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr" 0 'prime/mkl_real_allow_frt.txt'
}

function test_mkl_allow() {
    mkl_allow 
}

function verify_mkl_allow() {
    mkl_allow "-DP_VALUE"
}

function mkl_in_place () { 
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL_i" 0 'pow2/mkl_cpx_in_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL_i" 0 'small_factor/mkl_cpx_in_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL_i" 0 'prime/mkl_cpx_in_frt.txt'

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr_i" 0 'pow2/mkl_real_in_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr_i" 2 'small_factor/mkl_real_in_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr_i" 2 'prime/mkl_real_in_frt.txt'
}

function test_mkl_in_place() {
    mkl_in_place
}

function verify_mkl_in_place() {
    mkl_in_place "-DP_VALUE"
}

function fftw_estimate() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransform3" 0 'pow2/fftw_cpx_est_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransform3" 0 'small_factor/fftw_cpx_est_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransform3" 0 'prime/fftw_cpx_est_frt.txt'

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransform4" 0 'pow2/fftw_real_est_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransform4" 0 'small_factor/fftw_real_est_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransform4" 0 'prime/fftw_real_est_frt.txt'
}

function test_fftw_estimate() {
    fftw_estimate 
}

function verify_fftw_estimate() {
    fftw_estimate "-DP_VALUE"
}

function fftw_multi_thread() {
    p_value="$1"
    num_thread_flag="$2"
    num_thread="$3"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWm ${num_thread_flag}" 0 "pow2/fftw_mt_${num_thread}_cpx_frt.txt"
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWm ${num_thread_flag}" 0 "small_factor/fftw_mt_${num_thread}_cpx_frt.txt"
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWm ${num_thread_flag}" 0 "prime/fftw_mt_${num_thread}_cpx_frt.txt"

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWmr ${num_thread_flag}" 0 "pow2/fftw_mt_${num_thread}_real_frt.txt"
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWmr ${num_thread_flag}" 0 "small_factor/fftw_mt_${num_thread}_real_frt.txt"
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWmr ${num_thread_flag}" 0 "prime/fftw_mt_${num_thread}_real_frt.txt"
}

function test_fftw_multi_thread() {
    fftw_multi_thread "" "" 2
    fftw_multi_thread "" "-DMT4" 4
    fftw_multi_thread "" "-DMT6" 6
}

function verify_fftw_multi_thread() {
    fftw_multi_thread "-DP_VALUE" 2
    fftw_multi_thread "-DP_VALUE -DMT4" 4
    fftw_multi_thread "-DP_VALUE -DMT6" 6
}

# out-of-place
function fftw_measure() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransform3 -DMEASURE" 0 'pow2/fftw_cpx_mea_frt.txt' 
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransform3 -DMEASURE" 0 'small_factor/fftw_cpx_mea_frt.txt' # slow, not tested
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransform3 -DMEASURE" 0 'prime/fftw_cpx_mea_frt.txt' # slow, not tested

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransform4 -DMEASURE" 0 'pow2/fftw_real_mea_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransform4 -DMEASURE" 0 'small_factor/fftw_real_mea_frt.txt' # slow, not tested
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransform4 -DMEASURE" 0 'prime/fftw_real_mea_frt.txt' # slow, not tested
}

function test_fftw_measure() {
    fftw_measure 
}

function verify_fftw_measure() {
    fftw_measure "-DP_VALUE"
}

function fftw_in_place() {
    p_value="$1"
    # complex 
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTW_i" 0 'pow2/fftw_cpx_in_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTW_i" 0 'small_factor/fftw_cpx_in_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTW_i" 0 'prime/fftw_cpx_in_frt.txt'

    # real
    run "$p_value -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWr_i" 0 'pow2/fftw_real_in_frt.txt'
    run "$p_value -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWr_i" 0 'small_factor/fftw_real_in_frt.txt'
    run "$p_value -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformFFTWr_i" 0 'prime/fftw_real_in_frt.txt'
}


function test_fftw_in_place() {
    fftw_in_place
}

function verify_fftw_in_place() {
    fftw_in_place "-DP_VALUE"
}

# summary - libraries
function test_ipp() {
    test_ipp_none
    test_ipp_fast
    test_ipp_accurate
}

function verify_ipp() {
    verify_ipp_none
    verify_ipp_fast
    verify_ipp_accurate   
}

function test_mkl(){
    test_mkl_avoid
    test_mkl_allow
    test_mkl_in_place
}

function verify_mkl(){
    verify_mkl_avoid
    verify_mkl_allow
    verify_mkl_in_place
}

function test_fftw(){
    test_fftw_estimate
    test_fftw_in_place
    test_fftw_multi_thread
    test_fftw_measure
}

function verify_fftw(){
    verify_fftw_estimate
    verify_fftw_measure
    verify_fftw_in_place
}

# speed comparison and verify results
function test() {
    test_ipp # [done]
    test_mkl # out-of-place, small_factor, real - check this again
    test_fftw # [done]

    test_original # [done]
    test_ffts # [done]
    test_fftss # [done]
    test_gsl 
    test_pocket # [done]
    test_kfr # [done]
}

function verify() {
    verify_ipp # [done]
    verify_mkl # [done]
    verify_fftw # [done]

    verify_ffts # [done]
    verify_fftss # [done]
    verify_gsl # [done]
    verify_pocket # [done]
    verify_kfr # [done]
}

verify
test


