
SRC_FILE:= main.c sad_cpu.c sad_openmp.c

EXE_FILE:= sad
EXE_FILE_MP:= sad_mp

DISPARITY_LENGHT:=64

PIC_SIZE_WIDTH1:=640
PIC_SIZE_HEIGHT1:=443
INPUT_PIC_LEFT1:=./images/im0-$(PIC_SIZE_WIDTH1)x$(PIC_SIZE_HEIGHT1).raw
INPUT_PIC_RIGHT1:=./images/im1-$(PIC_SIZE_WIDTH1)x$(PIC_SIZE_HEIGHT1).raw
OUTPUT_DEPTH_MAP1:=./images/$(PIC_SIZE_WIDTH1)x$(PIC_SIZE_HEIGHT1).raw

PIC_SIZE_WIDTH2:=720
PIC_SIZE_HEIGHT2:=498
INPUT_PIC_LEFT2:=./images/im0-$(PIC_SIZE_WIDTH2)x$(PIC_SIZE_HEIGHT2).raw
INPUT_PIC_RIGHT2:=./images/im1-$(PIC_SIZE_WIDTH2)x$(PIC_SIZE_HEIGHT2).raw
OUTPUT_DEPTH_MAP2:=./images/$(PIC_SIZE_WIDTH2)x$(PIC_SIZE_HEIGHT2).raw

PIC_SIZE_WIDTH3:=960
PIC_SIZE_HEIGHT3:=664
INPUT_PIC_LEFT3:=./images/im0-$(PIC_SIZE_WIDTH3)x$(PIC_SIZE_HEIGHT3).raw
INPUT_PIC_RIGHT3:=./images/im1-$(PIC_SIZE_WIDTH3)x$(PIC_SIZE_HEIGHT3).raw
OUTPUT_DEPTH_MAP3:=./images/$(PIC_SIZE_WIDTH3)x$(PIC_SIZE_HEIGHT3).raw

PIC_SIZE_WIDTH4:=1280
PIC_SIZE_HEIGHT4:=885
INPUT_PIC_LEFT4:=./images/im0-$(PIC_SIZE_WIDTH4)x$(PIC_SIZE_HEIGHT4).raw
INPUT_PIC_RIGHT4:=./images/im1-$(PIC_SIZE_WIDTH4)x$(PIC_SIZE_HEIGHT4).raw
OUTPUT_DEPTH_MAP4:=./images/$(PIC_SIZE_WIDTH4)x$(PIC_SIZE_HEIGHT4).raw

PIC_SIZE_WIDTH5:=1920
PIC_SIZE_HEIGHT5:=1327
INPUT_PIC_LEFT5:=./images/im0-$(PIC_SIZE_WIDTH5)x$(PIC_SIZE_HEIGHT5).raw
INPUT_PIC_RIGHT5:=./images/im1-$(PIC_SIZE_WIDTH5)x$(PIC_SIZE_HEIGHT5).raw
OUTPUT_DEPTH_MAP5:=./images/$(PIC_SIZE_WIDTH5)x$(PIC_SIZE_HEIGHT5).raw

PIC_SIZE_WIDTH6:=3840
PIC_SIZE_HEIGHT6:=2653
INPUT_PIC_LEFT6:=./images/im0-$(PIC_SIZE_WIDTH6)x$(PIC_SIZE_HEIGHT6).raw
INPUT_PIC_RIGHT6:=./images/im1-$(PIC_SIZE_WIDTH6)x$(PIC_SIZE_HEIGHT6).raw
OUTPUT_DEPTH_MAP6:=./images/$(PIC_SIZE_WIDTH6)x$(PIC_SIZE_HEIGHT6).raw

INCLUDE_LIBRARY:= 

OPTION_FLAG:= -Wall
OPENMP_OPTION:= -fopenmp
OPENMP_FLAG := _SAD_OPENMP_
OPENMP_THREADS_NUM_FLAG := OMP_NUM_THREADS
BUILD:= gcc
BUILD_MP:= gcc-6

all:
	$(BUILD) -o $(EXE_FILE) $(SRC_FILE) $(INCLUDE_LIBRARY) $(OPTION_FLAG)
	$(BUILD_MP) -D $(OPENMP_FLAG) $(OPTION_FLAG) $(OPENMP_OPTION) -o $(EXE_FILE_MP) $(SRC_FILE) $(INCLUDE_LIBRARY) 

run: run1 run2 run3 run4 run5 run6


run1:
	time ./$(EXE_FILE) $(INPUT_PIC_LEFT1) $(INPUT_PIC_RIGHT1) $(OUTPUT_DEPTH_MAP1) $(PIC_SIZE_WIDTH1) $(PIC_SIZE_HEIGHT1) $(DISPARITY_LENGHT)
	
	export $(OPENMP_THREADS_NUM_FLAG)=2
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT1) $(INPUT_PIC_RIGHT1) $(OUTPUT_DEPTH_MAP1) $(PIC_SIZE_WIDTH1) $(PIC_SIZE_HEIGHT1) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=4
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT1) $(INPUT_PIC_RIGHT1) $(OUTPUT_DEPTH_MAP1) $(PIC_SIZE_WIDTH1) $(PIC_SIZE_HEIGHT1) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=6
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT1) $(INPUT_PIC_RIGHT1) $(OUTPUT_DEPTH_MAP1) $(PIC_SIZE_WIDTH1) $(PIC_SIZE_HEIGHT1) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=8
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT1) $(INPUT_PIC_RIGHT1) $(OUTPUT_DEPTH_MAP1) $(PIC_SIZE_WIDTH1) $(PIC_SIZE_HEIGHT1) $(DISPARITY_LENGHT)

run2:
	time ./$(EXE_FILE) $(INPUT_PIC_LEFT2) $(INPUT_PIC_RIGHT2) $(OUTPUT_DEPTH_MAP2) $(PIC_SIZE_WIDTH2) $(PIC_SIZE_HEIGHT2) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=2
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT2) $(INPUT_PIC_RIGHT2) $(OUTPUT_DEPTH_MAP2) $(PIC_SIZE_WIDTH2) $(PIC_SIZE_HEIGHT2) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=4
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT2) $(INPUT_PIC_RIGHT2) $(OUTPUT_DEPTH_MAP2) $(PIC_SIZE_WIDTH2) $(PIC_SIZE_HEIGHT2) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=6
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT2) $(INPUT_PIC_RIGHT2) $(OUTPUT_DEPTH_MAP2) $(PIC_SIZE_WIDTH2) $(PIC_SIZE_HEIGHT2) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=8
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT2) $(INPUT_PIC_RIGHT2) $(OUTPUT_DEPTH_MAP2) $(PIC_SIZE_WIDTH2) $(PIC_SIZE_HEIGHT2) $(DISPARITY_LENGHT)

run3:
	time ./$(EXE_FILE) $(INPUT_PIC_LEFT3) $(INPUT_PIC_RIGHT3) $(OUTPUT_DEPTH_MAP3) $(PIC_SIZE_WIDTH3) $(PIC_SIZE_HEIGHT3) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=2
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT3) $(INPUT_PIC_RIGHT3) $(OUTPUT_DEPTH_MAP3) $(PIC_SIZE_WIDTH3) $(PIC_SIZE_HEIGHT3) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=4
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT3) $(INPUT_PIC_RIGHT3) $(OUTPUT_DEPTH_MAP3) $(PIC_SIZE_WIDTH3) $(PIC_SIZE_HEIGHT3) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=6
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT3) $(INPUT_PIC_RIGHT3) $(OUTPUT_DEPTH_MAP3) $(PIC_SIZE_WIDTH3) $(PIC_SIZE_HEIGHT3) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=8
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT3) $(INPUT_PIC_RIGHT3) $(OUTPUT_DEPTH_MAP3) $(PIC_SIZE_WIDTH3) $(PIC_SIZE_HEIGHT3) $(DISPARITY_LENGHT)

run4:
	time ./$(EXE_FILE) $(INPUT_PIC_LEFT4) $(INPUT_PIC_RIGHT4) $(OUTPUT_DEPTH_MAP4) $(PIC_SIZE_WIDTH4) $(PIC_SIZE_HEIGHT4) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=2
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT4) $(INPUT_PIC_RIGHT4) $(OUTPUT_DEPTH_MAP4) $(PIC_SIZE_WIDTH4) $(PIC_SIZE_HEIGHT4) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=4
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT4) $(INPUT_PIC_RIGHT4) $(OUTPUT_DEPTH_MAP4) $(PIC_SIZE_WIDTH4) $(PIC_SIZE_HEIGHT4) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=6
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT4) $(INPUT_PIC_RIGHT4) $(OUTPUT_DEPTH_MAP4) $(PIC_SIZE_WIDTH4) $(PIC_SIZE_HEIGHT4) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=8
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT4) $(INPUT_PIC_RIGHT4) $(OUTPUT_DEPTH_MAP4) $(PIC_SIZE_WIDTH4) $(PIC_SIZE_HEIGHT4) $(DISPARITY_LENGHT)

run5:
	time ./$(EXE_FILE) $(INPUT_PIC_LEFT5) $(INPUT_PIC_RIGHT5) $(OUTPUT_DEPTH_MAP5) $(PIC_SIZE_WIDTH5) $(PIC_SIZE_HEIGHT5) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=2
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT5) $(INPUT_PIC_RIGHT5) $(OUTPUT_DEPTH_MAP5) $(PIC_SIZE_WIDTH5) $(PIC_SIZE_HEIGHT5) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=4
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT5) $(INPUT_PIC_RIGHT5) $(OUTPUT_DEPTH_MAP5) $(PIC_SIZE_WIDTH5) $(PIC_SIZE_HEIGHT5) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=6
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT5) $(INPUT_PIC_RIGHT5) $(OUTPUT_DEPTH_MAP5) $(PIC_SIZE_WIDTH5) $(PIC_SIZE_HEIGHT5) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=8
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT5) $(INPUT_PIC_RIGHT5) $(OUTPUT_DEPTH_MAP5) $(PIC_SIZE_WIDTH5) $(PIC_SIZE_HEIGHT5) $(DISPARITY_LENGHT)

run6:
	time ./$(EXE_FILE) $(INPUT_PIC_LEFT6) $(INPUT_PIC_RIGHT6) $(OUTPUT_DEPTH_MAP6) $(PIC_SIZE_WIDTH6) $(PIC_SIZE_HEIGHT6) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=2
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT6) $(INPUT_PIC_RIGHT6) $(OUTPUT_DEPTH_MAP6) $(PIC_SIZE_WIDTH6) $(PIC_SIZE_HEIGHT6) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=4
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT6) $(INPUT_PIC_RIGHT6) $(OUTPUT_DEPTH_MAP6) $(PIC_SIZE_WIDTH6) $(PIC_SIZE_HEIGHT6) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=6
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT6) $(INPUT_PIC_RIGHT6) $(OUTPUT_DEPTH_MAP6) $(PIC_SIZE_WIDTH6) $(PIC_SIZE_HEIGHT6) $(DISPARITY_LENGHT)

	export $(OPENMP_THREADS_NUM_FLAG)=8
	time ./$(EXE_FILE_MP) $(INPUT_PIC_LEFT6) $(INPUT_PIC_RIGHT6) $(OUTPUT_DEPTH_MAP6) $(PIC_SIZE_WIDTH6) $(PIC_SIZE_HEIGHT6) $(DISPARITY_LENGHT)


#allmp:
#	$(BUILD_MP) -o $(OPENMP_FLAG) $(EXE_FILE_MP) $(SRC_FILE) $(INCLUDE_LIBRARY) $(OPTION_FLAG)

