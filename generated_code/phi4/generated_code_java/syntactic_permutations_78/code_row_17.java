public class MemoryAllocator {
    private static final int STATUS_FREE = 0;
    private byte[] memoryPool;
    private boolean[] freeBlocks;

    public MemoryAllocator(int totalMemorySize) {
        memoryPool = new byte[totalMemorySize];
        freeBlocks = new boolean[1]; // Initially, the whole block is free.
        freeBlocks[0] = true; // Mark the entire pool as free
    }

    public int allocate(int size) {
        for (int i = 0; i < freeBlocks.length; i++) {
            if (freeBlocks[i] && canAllocateFromBlock(i, size)) {
                markAsAllocated(i, size);
                return i * memoryPool.length / freeBlocks.length;
            }
        }
        throw new OutOfMemoryError("Unable to allocate the requested memory block.");
    }

    private boolean canAllocateFromBlock(int startIndex, int size) {
        // Check if there is enough continuous free space
        int endIndex = (startIndex + (size / (memoryPool.length / freeBlocks.length))) % freeBlocks.length;
        if (endIndex < startIndex) { // Wrap around the end of array
            for (int i = startIndex; i < freeBlocks.length; i++) {
                if (!freeBlocks[i]) return false;
            }
            for (int i = 0; i < endIndex; i++) {
                if (!freeBlocks[i]) return false;
            }
        } else { // No wrap around
            for (int i = startIndex; i <= endIndex; i++) {
                if (!freeBlocks[i]) return false;
            }
        }
        return true;
    }

    private void markAsAllocated(int startIndex, int size) {
        int endIndex = (startIndex + (size / (memoryPool.length / freeBlocks.length))) % freeBlocks.length;
        if (endIndex < startIndex) { // Wrap around
            for (int i = startIndex; i < freeBlocks.length; i++) {
                freeBlocks[i] = false;
            }
            for (int i = 0; i <= endIndex; i++) {
                freeBlocks[i] = false;
            }
        } else { // No wrap around
            for (int i = startIndex; i <= endIndex; i++) {
                freeBlocks[i] = false;
            }
        }
    }

    public void deallocate(int address) {
        int blockIndex = address * freeBlocks.length / memoryPool.length;
        freeBlocks[blockIndex] = true;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024); // 1KB of memory
        try {
            int addr = allocator.allocate(128);
            System.out.println("Allocated at address: " + addr);

            allocator.deallocate(addr);
            System.out.println("Deallocated block starting at address: " + addr);
            
            int newAddr = allocator.allocate(128);
            System.out.println("Re-allocated at address: " + newAddr);
        } catch (OutOfMemoryError e) {
            System.err.println(e.getMessage());
        }
    }
}