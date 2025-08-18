import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate memory for a person structure (assuming 4 bytes for an integer status)
        ByteBuffer buffer = ByteBuffer.allocateDirect(4);
        IntBuffer intBuffer = buffer.asIntBuffer();

        // Set the status to 0
        intBuffer.put(0, 0);

        // Get the pointer to the beginning of the block (address in direct buffer is not accessible in Java)
        System.out.println("Memory allocated for person with status set to: " + intBuffer.get(0));
    }
}