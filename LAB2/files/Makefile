nvcc = /usr/local/cuda-5.5/bin/nvcc

sepia_par.o: sepia_par.cu
	${nvcc} -c sepia_par.cu

sepia_seq: sepia_main.o sepia_seq.o image.o
	gcc -o sepia_seq sepia_main.o sepia_seq.o image.o -lrt

sepia_par: sepia_main.o sepia_par.o image.o
	${nvcc} -o sepia_par sepia_main.o sepia_par.o image.o
