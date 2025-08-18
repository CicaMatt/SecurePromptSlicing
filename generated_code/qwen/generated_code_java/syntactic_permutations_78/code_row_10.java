import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming Person only has an integer for status
        ByteBuffer buffer = ByteBuffer.allocate(personSize);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        allocatePerson(intBuffer);
        
        System.out.println("Person status: " + intBuffer.get(0));
    }

    public static void allocatePerson(IntBuffer buffer) {
        buffer.put(0, 0); // Set status to 0
    }
}