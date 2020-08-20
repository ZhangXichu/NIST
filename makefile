CC = gcc  #clang
GCCFLAGS = -c -g -Wall
ROOTDIR = .
SRCDIR = $(ROOTDIR)/src
BENCHDIR = $(ROOTDIR)/fft_benchmark
OBJDIR = $(ROOTDIR)/obj
VPATH  = src:obj:include:fft_benchmark:libs

# let the linker know where to find the shared libraries
LD_LIBRARY_PATH=./libs

# preload the shared libraries for MKL
LD_PRELOAD=./libs/intel_mkl/libmkl_def.so:./libs/intel_mkl/libmkl_avx2.so:./libs/intel_mkl/libmkl_core.so:./libs/intel_mkl/libmkl_intel_lp64.so:./libs/intel_mkl/libmkl_intel_thread.so:./libs/intel_mkl/libiomp5.so

OBJ = $(OBJDIR)/assess.o $(OBJDIR)/frequency.o $(OBJDIR)/blockFrequency.o \
      $(OBJDIR)/cusum.o $(OBJDIR)/runs.o $(OBJDIR)/longestRunOfOnes.o \
      $(OBJDIR)/serial.o $(OBJDIR)/rank.o $(OBJDIR)/discreteFourierTransform.o \
      $(OBJDIR)/nonOverlappingTemplateMatchings.o \
      $(OBJDIR)/overlappingTemplateMatchings.o $(OBJDIR)/universal.o \
      $(OBJDIR)/approximateEntropy.o $(OBJDIR)/randomExcursions.o \
      $(OBJDIR)/randomExcursionsVariant.o $(OBJDIR)/linearComplexity.o \
      $(OBJDIR)/dfft.o $(OBJDIR)/cephes.o $(OBJDIR)/matrix.o \
      $(OBJDIR)/utilities.o $(OBJDIR)/generators.o $(OBJDIR)/genutils.o \
      $(OBJDIR)/BMA.o $(OBJDIR)/BM.o $(OBJDIR)/LUTs.o $(OBJDIR)/main.o  $(OBJDIR)/tools.o \
	  $(OBJDIR)/benchmark.o $(OBJDIR)/timer.o $(OBJDIR)/statistics.o $(OBJDIR)/bench_ffts.o \
	  $(OBJDIR)/bench_kfr.o $(OBJDIR)/bench_intel_mkl.o $(OBJDIR)/bench_intel_ipp.o \
	  $(OBJDIR)/pocketfft.o $(OBJDIR)/bench_pocket.o $(OBJDIR)/bench_gsl.o

assess: $(OBJ)  # -Wl,--verbose
	$(CC) -o $@ $(OBJ) -m64 -lm -L./libs -lffts -lfftw3 -lkfr_capi \
	-lgsl -lgslcblas \
	-L./libs/intel_mkl -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -liomp5 \
	-L./libs/intel_ipp -lippcore -lippvm -lipps \
	-lpthread -ldl 

$(OBJDIR)/assess.o: $(SRCDIR)/assess.c defs.h decls.h utilities.h fftw3.h ffts.h config.h
	$(CC) -o $@ -c $(SRCDIR)/assess.c 

$(OBJDIR)/frequency.o: $(SRCDIR)/frequency.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/frequency.c

$(OBJDIR)/blockFrequency.o: $(SRCDIR)/blockFrequency.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/blockFrequency.c

$(OBJDIR)/cusum.o: $(SRCDIR)/cusum.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/cusum.c

$(OBJDIR)/runs.o: $(SRCDIR)/runs.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/runs.c

$(OBJDIR)/longestRunOfOnes.o: $(SRCDIR)/longestRunOfOnes.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/longestRunOfOnes.c

$(OBJDIR)/rank.o: $(SRCDIR)/rank.c defs.h externs.h matrix.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/rank.c

$(OBJDIR)/discreteFourierTransform.o: $(SRCDIR)/discreteFourierTransform.c \
        defs.h externs.h utilities.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/discreteFourierTransform.c

$(OBJDIR)/nonOverlappingTemplateMatchings.o: \
        $(SRCDIR)/nonOverlappingTemplateMatchings.c defs.h externs.h utilities.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/nonOverlappingTemplateMatchings.c

$(OBJDIR)/overlappingTemplateMatchings.o: \
        $(SRCDIR)/overlappingTemplateMatchings.c defs.h externs.h utilities.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/overlappingTemplateMatchings.c

$(OBJDIR)/universal.o: $(SRCDIR)/universal.c defs.h externs.h utilities.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/universal.c

$(OBJDIR)/approximateEntropy.o: $(SRCDIR)/approximateEntropy.c defs.h externs.h utilities.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/approximateEntropy.c

$(OBJDIR)/randomExcursions.o: $(SRCDIR)/randomExcursions.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/randomExcursions.c

$(OBJDIR)/randomExcursionsVariant.o: $(SRCDIR)/randomExcursionsVariant.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/randomExcursionsVariant.c

$(OBJDIR)/serial.o: $(SRCDIR)/serial.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/serial.c

$(OBJDIR)/linearComplexity.o: $(SRCDIR)/linearComplexity.c defs.h externs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/linearComplexity.c

$(OBJDIR)/dfft.o: $(SRCDIR)/dfft.c config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/dfft.c

$(OBJDIR)/matrix.o: $(SRCDIR)/matrix.c defs.h externs.h utilities.h matrix.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/matrix.c

$(OBJDIR)/genutils.o: $(SRCDIR)/genutils.c config.h genutils.h 
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/genutils.c

$(OBJDIR)/cephes.o: $(SRCDIR)/cephes.c cephes.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/cephes.c

$(OBJDIR)/utilities.o: $(SRCDIR)/utilities.c defs.h externs.h utilities.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/utilities.c

$(OBJDIR)/generators.o: $(SRCDIR)/generators.c defs.h externs.h utilities.h \
        config.h generators.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/generators.c

$(OBJDIR)/BMA.o: $(SRCDIR)/BMA.c BMA.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/BMA.c

$(OBJDIR)/BM.o: $(SRCDIR)/BM.c BM.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/BM.c

$(OBJDIR)/LUTs.o: $(SRCDIR)/LUTs.c
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/LUTs.c

$(OBJDIR)/main.o: $(SRCDIR)/main.c cephes.h externs.h utilities.h tools.h stat_fncs.h test_data.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/main.c

$(OBJDIR)/tools.o: $(SRCDIR)/tools.c config.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/tools.c

# benchmark
$(OBJDIR)/benchmark.o: $(BENCHDIR)/benchmark.c benchmark.h stat_fncs.h timer.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/benchmark.c

$(OBJDIR)/timer.o: $(BENCHDIR)/timer.c timer.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/timer.c

$(OBJDIR)/statistics.o: $(BENCHDIR)/statistics.c statistics.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/statistics.c

$(OBJDIR)/bench_ffts.o: $(BENCHDIR)/bench_ffts.c stat_fncs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/bench_ffts.c

$(OBJDIR)/bench_kfr.o: $(BENCHDIR)/bench_kfr.c stat_fncs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/bench_kfr.c

$(OBJDIR)/bench_intel_mkl.o: $(BENCHDIR)/bench_intel_mkl.c stat_fncs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/bench_intel_mkl.c

$(OBJDIR)/bench_intel_ipp.o: $(BENCHDIR)/bench_intel_ipp.c stat_fncs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/bench_intel_ipp.c
 
$(OBJDIR)/pocketfft.o: $(BENCHDIR)/pocketfft.c pocketfft.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/pocketfft.c

$(OBJDIR)/bench_pocket.o: $(BENCHDIR)/bench_pocket.c stat_fncs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/bench_pocket.c

$(OBJDIR)/bench_gsl.o: $(BENCHDIR)/bench_gsl.c stat_fncs.h config.h
	$(CC) -o $@ $(GCCFLAGS) $(BENCHDIR)/bench_gsl.c

clean:
	rm -f assess $(OBJDIR)/*.o

rebuild: clean assess
