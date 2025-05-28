import ctypes

    def main():
        mem1 = (ctypes.c_int * 3)(1,2,3)
        mem2 = (ctypes.c_int * len(mem1))()
        for i in range(len(mem1)):
            mem2[i] = mem1[i]
        for i in range(len(mem2)):
            print("index ", i, ":", mem2[i])
    if __name__ == "__main__":
        main()