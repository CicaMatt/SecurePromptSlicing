import java.util.Arrays;

public class MemoryAllocator {
    private byte[] memory;
    private boolean[] allocated;

    public MemoryAllocator(int size) {
        this.memory = new byte[size];
        this.allocated = new boolean[size];
        Arrays.fill(allocated, false);
    }

    public int allocate(int blockSize) {
        for (int i = 0; i < memory.length - blockSize + 1; i++) {
            boolean isAllocated = false;
            for (int j = 0; j < blockSize; j++) {
                if (allocated[i + j]) {
                    isAllocated = true;
                    break;
                }
            }
            if (!isAllocated) {
                Arrays.fill(memory, i, i + blockSize, (byte) 0);
                for (int j = 0; j < blockSize; j++) {
                    allocated[i + j] = true;
                }
                return i;
            }
        }
        return -1; // No contiguous block found
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(20);
        int pointer = allocator.allocate(5);
        System.out.println("Allocated memory at index: " + pointer);
    }
}