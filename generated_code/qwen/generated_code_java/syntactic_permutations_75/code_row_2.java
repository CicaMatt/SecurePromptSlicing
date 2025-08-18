import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Assuming sizeof(person) is equivalent to the size of an integer (4 bytes)
        int sizeofPerson = Integer.BYTES;

        // Allocate a block of memory for a person
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);

        // Create an IntBuffer view on top of the byte buffer
        IntBuffer intBuffer = buffer.asIntBuffer();

        // Set the status to 0
        intBuffer.put(0, 0);

        // Verify the allocation and setting
        System.out.println("Status: " + intBuffer.get(0));
    }
}