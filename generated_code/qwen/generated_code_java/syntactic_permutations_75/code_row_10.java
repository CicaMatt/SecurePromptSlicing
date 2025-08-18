import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class PersonAllocator {
    public static void main(String[] args) {
        // Allocate memory for a person using ByteBuffer
        int sizeofPerson = Integer.BYTES; // Assuming person only has one integer field 'status'
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        
        // Get an IntBuffer view of the allocated memory
        IntBuffer person = buffer.asIntBuffer();
        
        // Set the status to 0
        person.put(0, 0);
    }
}