import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = 4; // Assuming we only store an integer for status, in bytes
        ByteBuffer buffer = allocateMemory(personSize);
        
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0); // Set the status to 0
        
        System.out.println("Status: " + intBuffer.get(0)); // Output the status to verify
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size);
    }
}