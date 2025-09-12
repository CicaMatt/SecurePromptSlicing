import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class PersonAllocator {
    public static void main(String[] args) {
        // Define the size of a person structure (in this case, assuming only an integer for status)
        int sizeofPerson = Integer.BYTES;

        // Allocate memory using ByteBuffer
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);

        // Get an IntBuffer to store an integer in the allocated memory
        IntBuffer personBuffer = buffer.asIntBuffer();

        // Set the status of the person to 0
        personBuffer.put(0, 0);

        // Verify the allocation and setting
        int status = personBuffer.get(0);
        System.out.println("Person status: " + status);
    }
}