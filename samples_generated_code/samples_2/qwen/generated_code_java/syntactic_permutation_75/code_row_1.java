import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int sizeofPerson = 8; // Example size in bytes, assuming an integer for status and padding
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer intBuffer = buffer.asIntBuffer();

        intBuffer.put(0, 1); // Set the status to 1

        int status = intBuffer.get(0);
        System.out.println("Status: " + status);
    }
}