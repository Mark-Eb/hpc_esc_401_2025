.PHONY: all clean

NVIDIA ?= 1
CRAY ?= 0
PGI  ?= 0
GCC  ?= 0
VERBOSE ?= 0
override CPPFLAGS += -I../common

ifeq ($(PE_ENV), NVIDIA))
	CXX = nvc++
	CXXFLAGS = -O3 -acc -mp -Minfo=acc -std=c++11 -gpu=cc90
endif

ifeq ($(PE_ENV), CRAY)
	CXX = CC
	FC  = ftn
	CXXFLAGS = -hstd=c++11 -O3 -homp -hacc -dynamic
	ifeq ($(VERBOSE), 1)
	CXXFLAGS += -hmsgs
	endif
endif

ifeq ($(PE_ENV), PGI)
	CXX = pgc++
	CXXFLAGS = -DPGI -std=c++11 -O3 -acc -Minfo=accel -ta=tesla:cc60,pinned
	LDFLAGS += -L$(CRAY_CUDATOOLKIT_DIR)/lib64 -lcudart
endif

ifeq ($(PE_ENV), GNU)
	CXX = g++
	CXXFLAGS = -std=c++11 -O3 -fopenmp -fopenacc -I$(CRAY_CUDATOOLKIT_DIR)/include
	LDFLAGS += -L$(CRAY_CUDATOOLKIT_DIR)/lib64 -lcudart
endif

OPENACC_BENCHMARKS= blur.openacc dot.openacc
BENCHMARKS=$(OPENACC_BENCHMARKS)

all: $(BENCHMARKS)

util.o: ../common/util.f03
	$(FC) $(CPPFLAGS) -c $(FCFLAGS) $<

blur.openacc: blur_openacc.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

dot.openacc: dot_openacc.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(BENCHMARKS) *.cub *.ptx *.o
