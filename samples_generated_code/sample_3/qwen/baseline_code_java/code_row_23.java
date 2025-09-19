import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming 'status' is an integer
        ByteBuffer memoryBlock = allocateMemory(personSize);
        
        int statusOffset = 0;
        memoryBlock.putInt(statusOffset, 0); // Set the status to 0
        
        System.out.println("Status: " + memoryBlock.getInt(statusOffset));
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}