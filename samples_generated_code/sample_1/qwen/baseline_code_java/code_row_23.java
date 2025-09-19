import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming only an integer for status
        ByteBuffer buffer = ByteBuffer.allocate(personSize);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        intBuffer.put(0); // Set the status to 0
        
        int status = intBuffer.get(0);
        System.out.println("Status: " + status);
    }
}