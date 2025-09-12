import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class PersonAllocator {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'person' only has an integer field 'status'
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer person = buffer.asIntBuffer();
        
        person.put(0, 0); // Set status to 0
    }
}