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

# test speed
# MKL - avoid using additional workspace
function test_mkl_avoid() {
    # complex 
    run '-DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID' 0 'pow2/mkl_cpx_avoid_frt.txt'
    run '-DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID' 0 'small_factor/mkl_cpx_avoid_frt.txt'
    run '-DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID' 0 'prime/mkl_cpx_avoid_frt.txt'

    # real
    run '-DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID' 0 'pow2/mkl_real_avoid_frt.txt'
    run '-DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID' 2 'small_factor/mkl_real_avoid_frt.txt'
    run '-DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID' 2 'prime/mkl_real_avoid_frt.txt'
}

# verify results
function verify_mkl_avoid() {
    # complex transform 
    run '-DP_VALUE -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID' 0 'pow2/mkl_cpx_avoid_frt.txt'
    run '-DP_VALUE -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID' 0 'small_factor/mkl_cpx_avoid_frt.txt'
    run '-DP_VALUE -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKL -DAVOID' 0 'prime/mkl_cpx_avoid_frt.txt'

    # real treansform 
    run '-DP_VALUE -DPOW2 -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID' 0 'pow2/mkl_real_avoid_frt.txt'
    run '-DP_VALUE -DSMALL_FACTOR -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID' 0 'small_factor/mkl_real_avoid_frt.txt'
    run '-DP_VALUE -DPRIME -DDiscreteFourierTransform_v2=DiscreteFourierTransformMKLr -DAVOID' 0 'prime/mkl_real_avoid_frt.txt'
}

# allow using additional workspace
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

function test_mkl(){
    # test_mkl_avoid
    test_mkl_allow
}

function verify_mkl(){
    # verify_mkl_avoid
    verify_mkl_allow
}

function test() {
    test_mkl
}

function verify() {
    verify_mkl
}

verify
test


