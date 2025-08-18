import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class PersonAllocator {

    private static final int SIZE_OF_PERSON = Integer.BYTES; // Assuming 'status' is an integer

    public static void main(String[] args) {
        ByteBuffer buffer = allocatePerson();
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0, 0); // Set status to 0
        System.out.println("Status: " + intBuffer.get(0));
    }

    public static ByteBuffer allocatePerson() {
        return ByteBuffer.allocate(SIZE_OF_PERSON);
    }
}