import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'status' is an integer for simplicity
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer person = buffer.asIntBuffer();
        person.put(0, 0); // Setting the status field to 0
    }
}