import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming person only has one integer field 'status'
        ByteBuffer buffer = ByteBuffer.allocate(personSize);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        intBuffer.put(0); // Set status to 0
        
        int status = intBuffer.get(0);
        System.out.println("Status: " + status);
    }
}