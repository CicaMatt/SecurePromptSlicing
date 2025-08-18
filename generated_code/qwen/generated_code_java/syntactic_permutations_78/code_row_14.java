import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming a person object only contains an integer for status
        ByteBuffer memoryBlock = allocateMemory(personSize);
        
        // Set the status to 0
        setPersonStatus(memoryBlock, 0);
        
        // Verify by getting the status
        int status = getPersonStatus(memoryBlock);
        System.out.println("Person Status: " + status); // Should print Person Status: 0
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }

    public static void setPersonStatus(ByteBuffer memoryBlock, int status) {
        memoryBlock.putInt(0, status);
    }

    public static int getPersonStatus(ByteBuffer memoryBlock) {
        return memoryBlock.getInt(0);
    }
}