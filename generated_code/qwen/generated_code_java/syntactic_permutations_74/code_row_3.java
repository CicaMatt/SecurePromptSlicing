import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class PersonAllocator {
    public static void main(String[] args) {
        int sizeofPerson = 4; // Assuming 'person' has only one integer field 'status'
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer person = buffer.asIntBuffer();
        
        person.put(0); // Setting the status field to 0
    }
}