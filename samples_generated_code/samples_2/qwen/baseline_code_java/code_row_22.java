import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'status' is an integer
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        intBuffer.put(0); // Set status to 0
        
        System.out.println("Status: " + intBuffer.get(0)); // Verify the status
    }
}