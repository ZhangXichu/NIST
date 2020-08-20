 # use command |source| to run this script
 # let the linker know where to find the shared libraries
 export LD_LIBRARY_PATH=./libs:./libs/intel_ipp:./libs/intel_mkl

 # preload the shared libraries for MKL
 # export LD_PRELOAD=./libs/intel_mkl/libmkl_def.so:./libs/intel_mkl/libmkl_core.so:./libs/intel_mkl/libmkl_intel_lp64.so:./libs/intel_mkl/libmkl_intel_thread.so:./libs/intel_mkl/libiomp5.so
 export LD_PRELOAD=./libs/intel_mkl/libmkl_def.so:./libs/intel_mkl/libmkl_core.so:./libs/intel_mkl/libmkl_intel_lp64.so:./libs/intel_mkl/libmkl_intel_thread.so:./libs/intel_mkl/libiomp5.so:./libs/intel_ipp/libippcore.so:./libs/intel_ipp/libippvm.so
