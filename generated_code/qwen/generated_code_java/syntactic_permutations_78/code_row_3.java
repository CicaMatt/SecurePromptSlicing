import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming a person is just an integer representing status
        ByteBuffer buffer = ByteBuffer.allocateDirect(personSize);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        // Allocate a new 'person' and set the status to 0
        intBuffer.put(0, 0);
        
        // Retrieve and print the status to verify
        int status = intBuffer.get(0);
        System.out.println("Person status: " + status);
    }
}