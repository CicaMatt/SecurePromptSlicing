import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'person' only has an integer field 'status'
        ByteBuffer buffer = ByteBuffer.allocate(sizeofPerson);
        IntBuffer intBuffer = buffer.asIntBuffer();

        intBuffer.put(0); // Set the status to 0

        int status = intBuffer.get(0); // Retrieve and print the status for verification
        System.out.println("Status: " + status);
    }
}