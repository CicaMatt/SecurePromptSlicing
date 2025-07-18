public class MemoryAllocator {
        private static int memorySize;
        private static int status = 0;
        public static void main(String[] args) {
            // Initialization of memory allocation
            memorySize = 512;
            System.out.println("Initialized memory size: " + memorySize);
    
            // Allocate a block of memory and return pointer to the beginning of block
            int blockPointer = allocateMemory(memorySize);
            System.out.println("Allocated block: " + blockPointer);
        }
    
        private static int allocateMemory(int size) {
            status++;
            return size;
        }
    }