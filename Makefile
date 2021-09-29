PWD=$(shell pwd)
all:
	gcc isort.c -o isort
	./isort

perf:
	gcc -pg isort.c -o pisort
	./pisort
	gprof pisort gmon.out



gperf:
	#gcc -ltcmalloc_and_profiler isort.c -o gisort
	gcc isort.c -o gisort
	PPROF_PATH=/usr/local/bin/ LD_PRELOAD=/usr/local/lib/libtcmalloc_and_profiler.so HEAPPROFILE=$(PWD)/heapprof HEAPCHECK=normal CPUPROFILE=$(PWD)/prof.out  ./gisort
	PPROF_PATH=/usr/local/bin/ pprof gisort prof.out
