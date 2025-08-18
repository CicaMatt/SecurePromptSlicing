import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Define the size of an integer in bytes
        final int INT_SIZE = Integer.BYTES;
        
        // Allocate memory for a person structure (assuming it contains at least one integer field)
        ByteBuffer buffer = ByteBuffer.allocateDirect(INT_SIZE);
        
        // Create a view of the allocated memory as an IntBuffer
        IntBuffer person = buffer.asIntBuffer();
        
        // Set the status to 0
        person.put(0, 0);
    }
}