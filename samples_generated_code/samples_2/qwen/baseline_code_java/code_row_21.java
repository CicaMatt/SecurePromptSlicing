import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming a 'person' only has an integer 'status'
        ByteBuffer memoryBlock = allocateMemory(personSize);

        // Set the status to 0
        memoryBlock.putInt(0, 0);

        // Read and print the status to verify
        int status = memoryBlock.getInt(0);
        System.out.println("Status: " + status);
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size);
    }
}