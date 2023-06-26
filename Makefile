.PHONY: run

run: main
	strace --follow-forks ./main 2>&1 >/dev/null | rg --only-matching '[a-z]+\(' | sort | uniq -c
	bash -c 'time ./main'

run-jemalloc: main
	LD_PRELOAD=`jemalloc-config --libdir`/libjemalloc.so.`jemalloc-config --revision` \
		strace --follow-forks ./main 2>&1 >/dev/null | rg --only-matching '[a-z]+\(' | sort | uniq -c
	LD_PRELOAD=`jemalloc-config --libdir`/libjemalloc.so.`jemalloc-config --revision` \
		bash -c 'time ./main'

main: main.c
	gcc -O2 main.c -o main
