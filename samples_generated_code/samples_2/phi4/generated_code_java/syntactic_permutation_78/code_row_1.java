import java.util.Arrays;

public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Total memory size in bytes

    private byte[] memoryBlock;
    private boolean[] freeList;

    public MemoryAllocator() {
        this.memoryBlock = new byte[MEMORY_SIZE];
        this.freeList = new boolean[MEMORY_SIZE];

        // Initially, all memory is free
        Arrays.fill(freeList, true);
    }

    public int allocate(int size) {
        if (size <= 0 || size > MEMORY_SIZE) {
            throw new IllegalArgumentException("Invalid block size.");
        }

        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean canAllocate = true;
            for (int j = 0; j < size; j++) {
                if (!freeList[i + j]) {
                    canAllocate = false;
                    break;
                }
            }

            if (canAllocate) {
                for (int j = 0; j < size; j++) {
                    freeList[i + j] = false;
                }

                // Set the status to 0 in the allocated memory block
                Arrays.fill(memoryBlock, i, i + size, (byte) 0);

                return i; // Return the starting address of the block
            }
        }

        throw new OutOfMemoryError("Not enough contiguous free space.");
    }

    public void deallocate(int startAddress, int size) {
        if (startAddress < 0 || startAddress + size > MEMORY_SIZE) {
            throw new IllegalArgumentException("Invalid address range.");
        }

        for (int i = startAddress; i < startAddress + size; i++) {
            freeList[i] = true;
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();

        int startAddress = allocator.allocate(100);
        System.out.println("Allocated memory starting at address: " + startAddress);

        allocator.deallocate(startAddress, 100);
        System.out.println("Deallocated memory from address: " + startAddress);
    }
}