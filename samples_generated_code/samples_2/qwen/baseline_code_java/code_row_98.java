import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'status' is an integer field
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer person = buffer.asIntBuffer();
        person.put(0, 0); // Set the status field to 0
    }
}