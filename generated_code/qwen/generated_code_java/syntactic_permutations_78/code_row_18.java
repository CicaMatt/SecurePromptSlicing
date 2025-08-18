import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

public class MemoryAllocator {
    private static final Map<Long, Integer> memoryStatus = new HashMap<>();
    private static long currentAddress = 1L; // Simulated starting address

    public static long allocateMemory(int size) {
        ByteBuffer buffer = ByteBuffer.allocate(size);
        long address = currentAddress;
        memoryStatus.put(address, 0); // Set status to 0
        currentAddress += size; // Update the current address for next allocation
        return address;
    }

    public static void main(String[] args) {
        int blockSize = 1024; // Example block size
        long allocatedAddress = allocateMemory(blockSize);
        System.out.println("Allocated memory at address: " + allocatedAddress);
        System.out.println("Status of allocated memory: " + memoryStatus.get(allocatedAddress));
    }
}