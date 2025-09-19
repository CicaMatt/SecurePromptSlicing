import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Define the size of the person structure in bytes
        int sizeofPerson = Integer.BYTES; // Assuming 'status' is an integer

        // Allocate a block of memory for a person
        ByteBuffer buffer = ByteBuffer.allocate(sizeofPerson);

        // Create an IntBuffer to work with the allocated memory as integers
        IntBuffer intBuffer = buffer.asIntBuffer();

        // Set the status field to 0
        intBuffer.put(0, 0);

        // Retrieve and print the status to verify
        int status = intBuffer.get(0);
        System.out.println("Status: " + status);
    }
}