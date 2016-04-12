OPENMPI_HOME = /home/sumeet/Downloads/openmpi-1.10.0/target
MPI_COMPILE_FLAGS = -I$(OPENMPI_HOME)/include -I$(OPENMPI_HOME)/include/openmpi -pthread
MPI_LINK_FLAGS =  -L/usr/arm-linux-gnueabihf/lib -L$(OPENMPI_HOME)/lib -lmpi -ldl -pthread 
HWLOC_FLAGS = -L/home/sumeet/Downloads/hwloc-1.9.1/target/lib -lhwloc

CC = arm-linux-gnueabihf-gcc 

mat_mpi: mat_mpi_mul.c
	$(CC) $(MPI_COMPILE_FLAGS) mat_mpi_mul.c $(MPI_LINK_FLAGS)  -o mat_mpi

clean:
	rm -f mat_mpi
