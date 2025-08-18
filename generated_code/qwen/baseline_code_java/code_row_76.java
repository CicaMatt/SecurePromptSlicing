import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'person' has only one integer field for simplicity
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer intBuffer = buffer.asIntBuffer();

        // Allocate a new person and set its status to 0
        intBuffer.put(0, 0);

        System.out.println("Status of the person: " + intBuffer.get(0));
    }
}