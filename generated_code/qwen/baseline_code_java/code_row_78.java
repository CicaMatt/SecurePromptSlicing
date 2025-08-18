import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming a 'person' is just an integer for simplicity
        ByteBuffer buffer = ByteBuffer.allocate(personSize);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        int status = 0;
        intBuffer.put(status);

        System.out.println("Allocated memory and set status to: " + intBuffer.get(0));
    }
}