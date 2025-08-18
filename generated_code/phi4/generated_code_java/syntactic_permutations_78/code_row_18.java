import java.util.ArrayList;
import java.util.List;

public class MemoryAllocator {
    private static final int FREE = 0;
    private static final int ALLOCATED = 1;
    
    private List<Integer> memoryBlocks;
    private List<Boolean> blockStatus;
    
    public MemoryAllocator(int totalSize) {
        memoryBlocks = new ArrayList<>(totalSize);
        blockStatus = new ArrayList<>(totalSize);
        
        for (int i = 0; i < totalSize; i++) {
            memoryBlocks.add(0); // Initialize memory to zero
            blockStatus.add(FREE); // Initially, all blocks are free
        }
    }
    
    public int allocateMemory(int size) {
        if (size <= 0 || size > memoryBlocks.size()) {
            throw new IllegalArgumentException("Invalid allocation size");
        }
        
        for (int i = 0; i <= memoryBlocks.size() - size; i++) {
            boolean canAllocate = true;
            
            for (int j = 0; j < size; j++) {
                if (blockStatus.get(i + j) != FREE) {
                    canAllocate = false;
                    break;
                }
            }
            
            if (canAllocate) {
                for (int j = 0; j < size; j++) {
                    blockStatus.set(i + j, ALLOCATED);
                }
                
                return i; // Return the starting index of allocated memory
            }
        }
        
        throw new OutOfMemoryError("Unable to allocate memory");
    }
    
    public void freeMemory(int startIndex, int size) {
        if (startIndex < 0 || startIndex + size > blockStatus.size()) {
            throw new IllegalArgumentException("Invalid memory range");
        }
        
        for (int i = startIndex; i < startIndex + size; i++) {
            if (blockStatus.get(i) != ALLOCATED) {
                throw new IllegalStateException("Memory block is not allocated");
            }
            
            blockStatus.set(i, FREE);
        }
    }
    
    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(100); // Create a memory pool of size 100
        
        try {
            int startIndex = allocator.allocateMemory(10); // Allocate 10 units of memory
            System.out.println("Allocated at index: " + startIndex);
            
            allocator.freeMemory(startIndex, 10); // Free the allocated memory
            System.out.println("Freed memory starting at index: " + startIndex);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}