import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming a 'person' is just an integer for status
        ByteBuffer buffer = ByteBuffer.allocateDirect(personSize);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        intBuffer.put(0, 0); // Set the status to 0
        
        System.out.println("Status: " + intBuffer.get(0));
    }
}