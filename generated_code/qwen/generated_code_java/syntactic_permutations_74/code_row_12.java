import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class PersonAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer = allocatePerson();
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0, 0); // Set status field to 0

        System.out.println("Status: " + intBuffer.get(0));
    }

    private static ByteBuffer allocatePerson() {
        final int SIZE_OF_PERSON = Integer.BYTES; // Assuming person has only one integer field 'status'
        return ByteBuffer.allocateDirect(SIZE_OF_PERSON);
    }
}